#pragma once
#include <QString>

namespace Utils {
    QString randomSalt(int length = 16);
    QString hashPassword(const QString& password, const QString& salt);
}