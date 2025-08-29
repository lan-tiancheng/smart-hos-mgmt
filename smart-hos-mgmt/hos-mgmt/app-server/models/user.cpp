#include "user.h"

User::User() {}

User::~User() {}

// ========================= age =========================
int User::age() const { return m_age; }
void User::setAge(const int age) { m_age = age; }

// ========================= gender =========================
QString User::gender() const { return m_gender; }
void User::setGender(const QString &gender) { m_gender = gender; }

// ========================= phone number =========================
QString User::phonenumber() const { return m_phonenumber; }
void User::setPhonenumber(const QString &phonenumber) { m_phonenumber = phonenumber; }

// ========================= address =========================
QString User::address() const { return m_address; }
void User::setAddress(const QString &address) { m_address = address; }

QString User::id() const { return m_id; }
void User::setId(const QString &id) { m_id = id; }

QString User::username() const { return m_username; }
void User::setUsername(const QString &username) { m_username = username; }

QString User::passwordHash() const { return m_passwordHash; }
void User::setPasswordHash(const QString &hash) { m_passwordHash = hash; }

User::UserType User::userType() const { return m_userType; }
void User::setUserType(const UserType &type) { m_userType = type; }

QJsonObject User::toJson() const {
    QJsonObject json;
    json["id"] = m_id;
    json["username"] = m_username;
    json["passwordHash"] = m_passwordHash;
    json["userType"] = (int)m_userType;
    return json;
}

void User::fromJson(const QJsonObject &json) {
    if (json.contains("id")) m_id = json["id"].toString();
    if (json.contains("username")) m_username = json["username"].toString();
    if (json.contains("passwordHash")) m_passwordHash = json["passwordHash"].toString();
    if (json.contains("userType")) m_userType = (UserType)json["userType"].toInt();
}
