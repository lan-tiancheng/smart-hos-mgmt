#ifndef USERMGR_H
#define USERMGR_H
#include <QObject>
#include <memory>
#include "userdata.h"
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

    bool IsLoadChatFin();//新添加
    QString GetIcon();
    void AppendApplyList(QJsonArray array);
    void AppendFriendList(QJsonArray array);
    std::vector<std::shared_ptr<FriendInfo>> GetChatListPerPage();
    std::vector<std::shared_ptr<FriendInfo>> GetConListPerPage();
    void UpdateChatLoadedCount();
    void UpdateContactLoadedCount();
    bool AlreadyApply(int uid);
    bool CheckFriendById(int uid);
    void AddFriend(std::shared_ptr<AuthRsp> auth_rsp);
    void AddFriend(std::shared_ptr<AuthInfo> auth_info);
    void AddApplyList(std::shared_ptr<ApplyInfo> app);
    std::shared_ptr<FriendInfo> GetFriendById(int uid);
    void AppendFriendChatMsg(int friend_id,std::vector<std::shared_ptr<TextChatData>>);
    std::shared_ptr<UserInfo> GetUserInfo();
    void SetUserInfo(std::shared_ptr<UserInfo> user_info);
        int GetUid();
        QString GetName();
        std::vector<std::shared_ptr<ApplyInfo>> GetApplyList();
        bool IsLoadConFin();

        QVector<QVector<QString>> getPediatricsData() {
             return pediatricsData;
         }
         void setPediatricsData(const QVector<QVector<QString>>& tmpdata) {
             pediatricsData = tmpdata;
         }

         QVector<QVector<QString>> getInternalMedicineData() {
             return internalMedicineData;
         }
         void setInternalMedicineData(const QVector<QVector<QString>>& tmpdata) {
             internalMedicineData = tmpdata;
         }
         int getUid() const {
                return userInfo_.uid;
            }

         QVector<QVector<QString>> getSurgeryData() {
             return surgeryData;
         }
         void setSurgeryData(const QVector<QVector<QString>>& tmpdata) {
             surgeryData = tmpdata;
         }

         QVector<QVector<QString>> getGynecologyData() {
             return gynecologyData;
         }
         void setGynecologyData(const QVector<QVector<QString>>& tmpdata) {
             gynecologyData = tmpdata;
         }

         QVector<QVector<QString>> getDermatologyData() {
             return dermatologyData;
         }
         void setDermatologyData(const QVector<QVector<QString>>& tmpdata) {
             dermatologyData = tmpdata;
         }

         QVector<QVector<QString>> getGuahaoData() {
             return guahaoData;
         }
         void setGuahaoData(const QVector<QVector<QString>>& tmpdata) {
             guahaoData = tmpdata;
         }

         QVector<QVector<QString>> getHospitalizationData() {
               return hospitalizationData;
           }
           void setHospitalizationData(const QVector<QVector<QString>>& tmpdata) {
               hospitalizationData = tmpdata;
           }

           // 获取用户信息
           UserInfoNew getUserInfo() const {
               return userInfo_;
           }

           // 设置用户信息
           void setUserInfo(const UserInfoNew& userInfo) {
               userInfo_ = userInfo;
           }

           // Getters
           int getId() const {
               return userInfo_.id;
           }


           QString getName() const {
               return userInfo_.name;
           }

           QString getEmail() const {
               return userInfo_.email;
           }

           QString getPwd() const {
               return userInfo_.pwd;
           }

           QString getRealName() const {
               return userInfo_.realName;
           }

           int getSex() const {
               return userInfo_.sex;
           }

           QString getYear() const {
               return userInfo_.year;
           }

           QString getMonth() const {
               return userInfo_.month;
           }

           QString getData() const {
               return userInfo_.data;
           }

           QString getIDcard() const {
               return userInfo_.IDcard;
           }

           QString getPhone() const {
               return userInfo_.phone;
           }

           // Setters
           void setId(int id) {
               userInfo_.id = id;
           }

           void setUid(int uid) {
               userInfo_.uid = uid;
           }

           void setName(const QString& name) {
               userInfo_.name = name;
           }

           void setEmail(const QString& email) {
               userInfo_.email = email;
           }

           void setPwd(const QString& pwd) {
               userInfo_.pwd = pwd;
           }

           void setRealName(const QString& realName) {
               userInfo_.realName = realName;
           }

           void setSex(int sex) {
               userInfo_.sex = sex;
           }
           QVector<QVector<QString>> getGuahaoDataByUid(int uid) const {
                   QVector<QVector<QString>> result;
                   for (const auto& row : guahaoData) {
                       if (row.size() > 2 && row[2].toInt() == uid) {  // 假设 useruid 在第3列
                           result.append(row);
                       }
                   }
                   return result;
               }

           void setYear(const QString& year) {
               userInfo_.year = year;
           }

           void setMonth(const QString& month) {
               userInfo_.month = month;
           }

           void setData(const QString& data) {
               userInfo_.data = data;
           }

           void setIDcard(const QString& IDcard) {
               userInfo_.IDcard = IDcard;
           }

           void setPhone(const QString& phone) {
               userInfo_.phone = phone;
           }
           QVector<QVector<QString>> getHospitalizationDataByUid(int uid) const {
               QVector<QVector<QString>> result;
               for (const auto& row : hospitalizationData) {
                   if (row.size() > 2 && row[2].toInt() == uid) {  // 假设 patient_uid 在第3列
                       result.append(row);
                   }
               }
               return result;
           }


private:
    UserMgr();
       UserInfoNew userInfo_;  // 用于存储用户信息
    QString _token;

    std::shared_ptr<UserInfo> _user_info;
    std::vector<std::shared_ptr<ApplyInfo>> _apply_list;
    std::vector<std::shared_ptr<FriendInfo>> _friend_list;
    QMap<int, std::shared_ptr<FriendInfo>> _friend_map;
    int _chat_loaded;
    int _contact_loaded;
    QVector<QVector<QString>> hospitalizationData;
    QVector<QVector<QString>> pediatricsData;
        QVector<QVector<QString>> internalMedicineData;
        QVector<QVector<QString>> surgeryData;
        QVector<QVector<QString>> gynecologyData;
        QVector<QVector<QString>> dermatologyData;

        QVector<QVector<QString>> guahaoData;
public slots:
    void SlotAddFriendRsp(std::shared_ptr<AuthRsp> rsp);
    void SlotAddFriendAuth(std::shared_ptr<AuthInfo> auth);

};

#endif // USERMGR_H
