#include "common/Utils.h"
#include <QCryptographicHash>
#include <QRandomGenerator>

namespace Utils {
    QString randomSalt(int length) {
        static const char chars[] =
            "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        QString s; s.reserve(length);
        for (int i = 0; i < length; ++i) s.append(chars[QRandomGenerator::global()->bounded(sizeof(chars) - 1)]);
        return s;
    }
    QString hashPassword(const QString& password, const QString& salt) {
        QByteArray input = (salt + ":" + password).toUtf8();
        QByteArray hash = QCryptographicHash::hash(input, QCryptographicHash::Sha256);
        return QString::fromLatin1(hash.toHex());
    }
}