#include "user.h"

User::User()
    : m_age(0), m_gender(""), m_phonenumber(""), m_address(""), m_id(""), m_username(""), m_passwordHash(""), m_userType(Patient) {}

User::~User() {}

int User::age() const { return m_age; }
void User::setAge(const int age) { m_age = age; }

QString User::gender() const { return m_gender; }
void User::setGender(const QString& gender) { m_gender = gender; }

QString User::phonenumber() const { return m_phonenumber; }
void User::setPhonenumber(const QString& phonenumber) { m_phonenumber = phonenumber; }

QString User::address() const { return m_address; }
void User::setAddress(const QString& address) { m_address = address; }

QString User::id() const { return m_id; }
void User::setId(const QString& id) { m_id = id; }

QString User::username() const { return m_username; }
void User::setUsername(const QString& username) { m_username = username; }

QString User::passwordHash() const { return m_passwordHash; }
void User::setPasswordHash(const QString& hash) { m_passwordHash = hash; }

User::UserType User::userType() const { return m_userType; }
void User::setUserType(const UserType& type) { m_userType = type; }

QJsonObject User::toJson() const {
    QJsonObject json;
    json["id"] = m_id;
    json["username"] = m_username;
    json["passwordHash"] = m_passwordHash;
    json["age"] = m_age;
    json["gender"] = m_gender;
    json["phonenumber"] = m_phonenumber;
    json["address"] = m_address;
    json["userType"] = static_cast<int>(m_userType);
    return json;
}

void User::fromJson(const QJsonObject& json) {
    m_id = json["id"].toString();
    m_username = json["username"].toString();
    m_passwordHash = json["passwordHash"].toString();
    m_age = json["age"].toInt();
    m_gender = json["gender"].toString();
    m_phonenumber = json["phonenumber"].toString();
    m_address = json["address"].toString();
    m_userType = static_cast<UserType>(json["userType"].toInt());
}
