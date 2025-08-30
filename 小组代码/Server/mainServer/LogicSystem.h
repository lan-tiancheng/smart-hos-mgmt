//
// Created by user on 24-8-23.
//

#ifndef LOGICSYSTEM_H
#define LOGICSYSTEM_H



#include "Singleton.h"
#include <queue>
#include <thread>
#include "CSession.h"
#include <queue>
#include <map>
#include <functional>
#include "const.h"
#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>
#include <unordered_map>
#include "data.h"

typedef  function<void(shared_ptr<CSession>, const short &msg_id, const string &msg_data)> FunCallBack;
class LogicSystem:public Singleton<LogicSystem>
{
    friend class Singleton<LogicSystem>;
public:
    ~LogicSystem();
    void PostMsgToQue(shared_ptr < LogicNode> msg);
private:
    LogicSystem();
    void DealMsg();
    void RegisterCallBacks();
    void DoctorWriteAdvice(shared_ptr<CSession> session, const short &msg_id, const string &msg_data);
    void addHospi(shared_ptr<CSession> session, const short &msg_id, const string &msg_data);
    void DoctorWriteCheckResult(shared_ptr<CSession> session, const short &msg_id, const string &msg_data);
    void LoginHandler(shared_ptr<CSession> session, const short &msg_id, const string &msg_data);
    void DoctorLoginHandler(shared_ptr<CSession> session, const short &msg_id, const string &msg_data);
    void SearchInfo(std::shared_ptr<CSession> session, const short& msg_id, const string& msg_data);
    void AddFriendApply(std::shared_ptr<CSession> session, const short& msg_id, const string& msg_data);
    void AuthFriendApply(std::shared_ptr<CSession> session, const short& msg_id, const string& msg_data);
    void DealChatTextMsg(std::shared_ptr<CSession> session, const short& msg_id, const string& msg_data);
    void UpdateUserInfo(shared_ptr<CSession> session, const short &msg_id, const string &msg_data);
    void ProcessOrderRequest(shared_ptr<CSession> session, const short &msg_id, const string &msg_data);
    bool isPureDigit(const std::string& str);
    void GetUserByUid(std::string uid_str, Json::Value& rtvalue);
    void GetUserByName(std::string name, Json::Value& rtvalue);
    bool GetBaseInfo(std::string base_key, int uid, std::shared_ptr<UserInfo> &userinfo);
    bool GetFriendApplyInfo(int to_uid, std::vector<std::shared_ptr<ApplyInfo>>& list);
    bool GetFriendList(int self_id, std::vector<std::shared_ptr<UserInfo>> & user_list);
    bool GetDoctorInfo(std::string base_key, int uid, std::shared_ptr<DoctorInfo>& doctorinfo);
    void EditDoctorInfo(shared_ptr<CSession> session, const short &msg_id, const string &msg_data);
    void DoctorCallForPaintInfo(shared_ptr<CSession> session, const short &msg_id, const string &msg_data);
    bool GetGuahaoInfo(int doctor_uid,
    std::vector<std::shared_ptr<paintInfobase>>& baseList,
    std::vector<std::shared_ptr<paintInfocheck>>& checkList,
    std::vector<std::shared_ptr<paintInfochufang>>& chufangList);
   // void DoctorCallForPaintInfo(shared_ptr<CSession> session, const short &msg_id, const string &msg_data);
    std::thread _worker_thread;
    std::queue<shared_ptr<LogicNode>> _msg_que;
    std::mutex _mutex;
    std::condition_variable _consume;
    bool _b_stop;
    std::map<short, FunCallBack> _fun_callbacks;

};


#endif //LOGICSYSTEM_H
