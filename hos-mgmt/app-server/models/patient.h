#pragma once
#include <QString>
#include <QJsonObject>
#include "user.h"

class History {
public:
    History();

    QString description() const;
    void setDescription(const QString&);

    QDate date() const;
    void setDate(const QDate&);

    QJsonObject toJson() const;
    void fromJson(const QJsonObject&);
private:
    QString m_description;
    QDate m_date;
};

class Patient : public User {
public:
    Patient();

    History medicalHistory() const;
    void setMedicalHistory(const History&);

    QJsonObject toJson() const override;
    void fromJson(const QJsonObject&) override;
    bool isHealthy() const;

    //数据库兼容 getter/setter
    QString id() const;
    void setId(const QString&);
    double height() const;
    void setHeight(double);
    double weight() const;
    void setWeight(double);
    int lungCapacity() const;
    void setLungCapacity(int);
    int heartRate() const;
    void setHeartRate(int);
    int systolicBP() const;
    void setSystolicBP(int);
    int diastolicBP() const;
    void setDiastolicBP(int);

private:
    QString m_id;
    History m_medicalHistory;
    double m_height = 0.0;
    double m_weight = 0.0;
    int m_lungCapacity = 0;
    int m_heartRate = 0;
    int m_systolicBP = 0;
    int m_diastolicBP = 0;
};
