#ifndef USERMGR_H
#define USERMGR_H
#include <QObject>
#include <memory>
#include <singleton.h>

class UserMgr:public QObject,public Singleton<UserMgr>,
        public std::enable_shared_from_this<UserMgr>
{
    Q_OBJECT
public:
    friend class Singleton<UserMgr>;
    ~ UserMgr();
    void SetName(QString name);
    void SetUid(int uid);
    void SetToken(QString token);
    void SetWorkID(QString workID);
    void setEmail(QString email);
    void setPhone(QString phone);
    void setSex(int sex);
    void setYear(QString year);
    void setMonth(QString month);
    void setDay(QString day);
    void setIDcard(QString IDcard);
    void setDepartment_id(int department_id);
    void setIntr(QString intr);
    QString getName() const { return _name; }
        //void setName(const QString& name) { _name = name; }

        QString getToken() const { return _token; }
        //void setToken(const QString& token) { _token = token; }

        int getUid()  { return _uid; }
        //void setUid(int uid) { _uid = uid; }

        QString getWorkID() const { return _workID; }
        //void setWorkID(const QString& workID) { _workID = workID; }

        QString getEmail() const { return _email; }
        //void setEmail(const QString& email) { _email = email; }

        QString getPhone() const { return _phone; }
        //void setPhone(const QString& phone) { _phone = phone; }

        int getSex() const { return _sex; }
        //void setSex(int sex) { _sex = sex; }

        QString getYear() const { return _year; }
        //void setYear(const QString& year) { _year = year; }

        QString getMonth() const { return _month; }
        //void setMonth(const QString& month) { _month = month; }

        QString getDay() const { return _day; }
        //void setDay(const QString& day) { _day = day; }

        QString getIDCard() const { return _IDcard; }
        //void setIDCard(const QString& IDcard) { _IDcard = IDcard; }

        int getDepartmentID() const { return _department_id; }
        //void setDepartmentID(const QString& departmentID) { _department_id = departmentID; }

        QString getIntr() const { return _intr; }
        //void setIntr(const QString& intr) { _intr = intr; }
        QString getDepartmentName() const {
                int deptId = getDepartmentID();
                switch (deptId) {
                    case 1: return "儿科";
                    case 2: return "内科";
                    case 3: return "外科";
                    case 4: return "妇科";
                    case 5: return "皮肤科";
                    default: return "未知科室";
                }
            }
        void setData(QVector<QVector<QString>> tmpdata){
            data=tmpdata;
        }

        void setMdata(QVector<QVector<QString>> tmpdata){
            mdata=tmpdata;
        }
        void setWdata(QVector<QVector<QString>> tmpdata){
            wdata=tmpdata;
        }
        QVector<QVector<QString>> getData(){
            return data;

        }
        QVector<QVector<QString>> getMdata(){
            return mdata;
        }
        QVector<QVector<QString>> getWdata(){
            return wdata;
        }
        void setguahaoidEdit(QString id){
            _guahaoidEdit=id;
        }
        QString getguahaoidEdit(){
            return _guahaoidEdit;
        }
        void setpaintIdp(QString id){
            paintidp=id;
        }
        QString getpainIdep(){
            return paintidp;
        }
        void sethdata(QVector<QVector<QString>> data){
            hdata=data;
        }
        QVector<QVector<QString>> gethdata(){
            return hdata;
        }


signals:
        void sig_to_paint_info_detail(const QString jsonsq);

private:
    UserMgr();
    QString _name;
    QString _token;
    int _uid;
    QString _workID;
    QString _email;
    QString _phone;
    int _sex;
    QString _year;
    QString _month;
    QString _day;
    QString _IDcard;
    QString _guahaoidEdit;
    int _department_id;
    QString _intr;
    QString paintidp;
    QVector<QVector<QString>> data;
    QVector<QVector<QString>> mdata;
    QVector<QVector<QString>> wdata;
    QVector<QVector<QString>> hdata;


};

#endif // USERMGR_H
