#include "patient.h"

History::History() : m_description(""), m_date(QDate::currentDate()) {}
QString History::description() const { return m_description; }
void History::setDescription(const QString& desc) { m_description = desc; }

QDate History::date() const { return m_date; }
void History::setDate(const QDate& d) { m_date = d; }

QJsonObject History::toJson() const {
    QJsonObject json;
    json["description"] = m_description;
    json["date"] = m_date.toString(Qt::ISODate);
    return json;
}

void History::fromJson(const QJsonObject& json) {
    m_description = json["description"].toString();
    m_date = QDate::fromString(json["date"].toString(), Qt::ISODate);
}

Patient::Patient() : User() {}

History Patient::medicalHistory() const { return m_medicalHistory; }
void Patient::setMedicalHistory(const History& h) { m_medicalHistory = h; }

QString Patient::id() const { return m_id; }
void Patient::setId(const QString& id) { m_id = id; }
double Patient::height() const { return m_height; }
void Patient::setHeight(double h) { m_height = h; }
double Patient::weight() const { return m_weight; }
void Patient::setWeight(double w) { m_weight = w; }
int Patient::lungCapacity() const { return m_lungCapacity; }
void Patient::setLungCapacity(int l) { m_lungCapacity = l; }
int Patient::heartRate() const { return m_heartRate; }
void Patient::setHeartRate(int hr) { m_heartRate = hr; }
int Patient::systolicBP() const { return m_systolicBP; }
void Patient::setSystolicBP(int sbp) { m_systolicBP = sbp; }
int Patient::diastolicBP() const { return m_diastolicBP; }
void Patient::setDiastolicBP(int dbp) { m_diastolicBP = dbp; }

QJsonObject Patient::toJson() const {
    QJsonObject json = User::toJson();
    json["id"] = m_id;
    json["medicalHistory"] = m_medicalHistory.toJson();
    json["height"] = m_height;
    json["weight"] = m_weight;
    json["lungCapacity"] = m_lungCapacity;
    json["heartRate"] = m_heartRate;
    json["systolicBP"] = m_systolicBP;
    json["diastolicBP"] = m_diastolicBP;
    return json;
}
void Patient::fromJson(const QJsonObject& json) {
    User::fromJson(json);
    m_id = json["id"].toString();
    m_medicalHistory.fromJson(json["medicalHistory"].toObject());
    m_height = json["height"].toDouble();
    m_weight = json["weight"].toDouble();
    m_lungCapacity = json["lungCapacity"].toInt();
    m_heartRate = json["heartRate"].toInt();
    m_systolicBP = json["systolicBP"].toInt();
    m_diastolicBP = json["diastolicBP"].toInt();
}

bool Patient::isHealthy() const {
    double bmi = m_weight / ((m_height / 100.0) * (m_height / 100.0));
    bool bmiHealthy = (bmi >= 18.5 && bmi <= 24.9);
    bool lungHealthy = (m_lungCapacity >= 2000);
    bool heartRateHealthy = (m_heartRate >= 60 && m_heartRate <= 100);
    bool bpHealthy = (m_systolicBP >= 90 && m_systolicBP <= 120 &&
                      m_diastolicBP >= 60 && m_diastolicBP <= 80);
    return bmiHealthy && lungHealthy && heartRateHealthy && bpHealthy;
}
