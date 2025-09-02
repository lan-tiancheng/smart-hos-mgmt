#ifndef ASRUPLOADER_H
#define ASRUPLOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class AsrUploader : public QObject
{
    Q_OBJECT
public:
    explicit AsrUploader(QObject *parent = nullptr) : QObject(parent) {}

    Q_INVOKABLE void setApiBase(const QString &url);
    Q_INVOKABLE void uploadFile(const QString &filePath);

signals:
    void recognizedText(const QString &text);
    void asrFailed(const QString &reason);

private:
    QString m_apiBase;
    QNetworkAccessManager m_nam;
};

#endif // ASRUPLOADER_H
