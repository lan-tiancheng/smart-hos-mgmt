#include "asruploader.h"
#include <QHttpMultiPart>
#include <QFileInfo>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkRequest>
#include <QUrl>



void AsrUploader::setApiBase(const QString &url)
{
    m_apiBase = url;
}

void AsrUploader::uploadFile(const QString &filePath)
{
    if (m_apiBase.isEmpty()) {
        emit asrFailed(QStringLiteral("未设置 API 基础地址"));
        return;
    }
    QFileInfo fi(filePath);
    if (!fi.exists() || !fi.isFile()) {
        emit asrFailed(QStringLiteral("音频文件不存在"));
        return;
    }

    QHttpMultiPart *multi = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart filePart;
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader,
                       QVariant(QString("form-data; name=\"audio\"; filename=\"%1\"").arg(fi.fileName())));
    filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("audio/wav"));

    QFile *file = new QFile(filePath, multi);
    if (!file->open(QIODevice::ReadOnly)) {
        multi->deleteLater();
        emit asrFailed(QStringLiteral("无法读取音频文件"));
        return;
    }
    filePart.setBodyDevice(file);
    multi->append(filePart);

    QNetworkRequest req(QUrl(m_apiBase + "/api/asr"));
    auto *reply = m_nam.post(req, multi);
    multi->setParent(reply);

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        reply->deleteLater();
        if (reply->error() != QNetworkReply::NoError) {
            emit asrFailed(reply->errorString());
            return;
        }
        const QByteArray data = reply->readAll();
        const auto doc = QJsonDocument::fromJson(data);
        if (!doc.isObject()) {
            emit asrFailed(QStringLiteral("ASR 响应格式错误"));
            return;
        }
        const auto obj = doc.object();
        if (!obj.value("success").toBool()) {
            emit asrFailed(obj.value("reason").toString(QStringLiteral("识别失败")));
            return;
        }
        emit recognizedText(obj.value("text").toString());
    });
}
