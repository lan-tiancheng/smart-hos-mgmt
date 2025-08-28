#include "patient.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QDate>

// ======================= History 类实现 =======================
// 获取描述
QString History::getDescription() const {
    return description;
}

// 设置描述
void History::setDescription(const QString &desc) {
    description = desc;
}

// 获取日期
QDate History::getDate() const {
    return date;
}

// 设置日期
void History::setDate(const QDate &d) {
    date = d;
}

// 将History对象转化为QJsonObject
QJsonObject History::toJson() const {
    QJsonObject jsonObj;
    jsonObj["description"] = description;
    jsonObj["date"] = date.toString();  // 使用QString格式化日期
    return jsonObj;
}

// 从QJsonObject还原History对象
void History::fromJson(const QJsonObject &json) {
    description = json["description"].toString();
    date = QDate::fromString(json["date"].toString());
}

// ======================= Patient 类实现 =======================

Patient::Patient() {
    // 默认的患者病历历史为空
    m_medicalHistory = History();
}

// 获取患者的病历历史
History Patient::medicalHistory() const {
    return m_medicalHistory;
}

// 设置患者的病历历史
void Patient::setMedicalHistory(const History &history) {
    m_medicalHistory = history;
}

// 覆盖基类方法以包含新属性（将患者信息转换为JSON）
QJsonObject Patient::toJson() const {
    QJsonObject jsonObj = User::toJson();  // 调用基类的toJson方法

    // 添加患者的病历历史到JSON
    jsonObj["medicalHistory"] = m_medicalHistory.toJson();

    return jsonObj;
}

// 从JSON恢复患者信息
void Patient::fromJson(const QJsonObject &json) {
    User::fromJson(json);  // 调用基类的fromJson方法

    // 恢复病历历史
    m_medicalHistory.fromJson(json["medicalHistory"].toObject());
}
