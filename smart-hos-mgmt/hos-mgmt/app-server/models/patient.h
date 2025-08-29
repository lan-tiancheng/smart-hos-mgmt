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

    // 患者基本信息输入 实现健康评估界面
    void setHeight(double h) { height = h; }
    double getHeight() const { return height; }

    void setWeight(double w) { weight = w; }
    double getWeight() const { return weight; }

    void setLungCapacity(double lc) { lungCapacity = lc; }
    double getLungCapacity() const { return lungCapacity; }
    void setHeartRate(int hr) { heartRate = hr; }
    int getHeartRate() const { return heartRate; }

    void setBloodPressure(int systolic, int diastolic) {
        systolicBP = systolic;
        diastolicBP = diastolic;
    }
    int getSystolicBP() const { return systolicBP; }
    int getDiastolicBP() const { return diastolicBP; }
    bool isHealthy() const;// 判断病人是否健康

private:
    // 患者健康信息
    double height;       // 身高，单位米
    double weight;       // 体重，单位公斤
    double lungCapacity; // 肺活量，单位毫升
    int heartRate;       // 心率（次/分钟）
    int systolicBP;      // 收缩压（mmHg）
    int diastolicBP;     // 舒张压（mmHg）
    History m_medicalHistory;  // 保存患者的病历历史
};

#endif // PATIENT_H
