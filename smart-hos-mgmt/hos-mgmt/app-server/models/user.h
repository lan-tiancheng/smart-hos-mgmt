#ifndef USER_H
#define USER_H

#include <QString>
#include <QJsonObject>
#include <QJsonArray>

// 使用 Q_GADGET 宏来启用 Qt 的元对象系统，
// 这样可以方便地进行序列化和反序列化
// 用户基类 ID 用户名 密码 用户类型
class User
{
    Q_GADGET
public:
    enum UserType {
        Patient,
        Doctor
    };
    Q_ENUM(UserType)

    User();//constructor
    virtual ~User();// destructor

    // 基础属性
    int age() const;
    void setAge(const int age);

    QString gender()const;
    void setGender(const QString&gender);

    QString phonenumber()const;
    void setPhonenumber(const QString&Phonenumber);

    QString address()const;
    void setAddress(const QString&address);

    QString id() const;
    void setId(const QString &id);

    QString username() const;
    void setUsername(const QString &username);

    QString passwordHash() const;
    void setPasswordHash(const QString &hash);

    UserType userType() const;
    void setUserType(const UserType &type);

    // 序列化为 JSON
    virtual QJsonObject toJson() const;
    // 从 JSON 反序列化
    virtual void fromJson(const QJsonObject &json);

protected:
    QString m_id;
    QString m_username;
    QString m_passwordHash;
    int m_age;
    QString m_gender;
    QString m_phonenumber;
    QString m_address;
    UserType m_userType;
};

#endif // USER_H
