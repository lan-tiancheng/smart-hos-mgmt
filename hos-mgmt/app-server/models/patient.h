#ifndef PATIENT_H
#define PATIENT_H

#include "user.h"
#include <QString>
#include <QDate>
#include <QJsonObject>

class History {
private:
    QString description;  // 记录的描述
    QDate date;           // 记录的日期

public:
    History() = default;  // 默认构造函数

    History(const QString &desc, const QDate &d)
        : description(desc), date(d) {}

    // 获取描述
    QString getDescription() const ;

    // 设置描述
    void setDescription(const QString &desc) ;

    // 获取日期
    QDate getDate() const ;

    // 设置日期
    void setDate(const QDate &d) ;
    // 将History对象转化为QJsonObject
    QJsonObject toJson() const ;
    // 从QJsonObject还原History对象
    void fromJson(const QJsonObject &json) ;
};

class Patient : public User {
public:
    Patient();

    // 获取患者的病历历史
    History medicalHistory() const ;

    // 设置患者的病历历史
    void setMedicalHistory(const History &history) ;

    // 覆盖基类方法以包含新属性（将患者信息转换为JSON）
    QJsonObject toJson() const override ;

    // 从JSON恢复患者信息
    void fromJson(const QJsonObject &json) override;

private:
    History m_medicalHistory;  // 保存患者的病历历史
};

#endif // PATIENT_H
