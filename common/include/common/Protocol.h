#pragma once
#include <QJsonObject>
#include <QJsonDocument>
#include <QString>

namespace Protocol {
    // 行分隔 JSON 协议
    inline QByteArray toLine(const QJsonObject& obj) {
        QJsonDocument doc(obj);
        QByteArray line = doc.toJson(QJsonDocument::Compact);
        line.append('\n');
        return line;
    }
    inline QJsonObject ok(const QString& action, const QJsonObject& data = {}) {
        QJsonObject resp; resp["ok"] = true; resp["action"] = action; resp["data"] = data; return resp;
    }
    inline QJsonObject error(const QString& action, int code, const QString& message) {
        QJsonObject resp; resp["ok"] = false; resp["action"] = action; resp["error_code"] = code; resp["error_message"] = message; return resp;
    }
}