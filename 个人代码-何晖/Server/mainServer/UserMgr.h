//
// Created by user on 24-8-23.
//

#ifndef USERMGR_H
#define USERMGR_H



#include "Singleton.h"
#include <unordered_map>
#include <memory>
#include <mutex>

class CSession;
class UserMgr: public Singleton<UserMgr>
{
    friend class Singleton<UserMgr>;
public:
    ~UserMgr();
    std::shared_ptr<CSession> GetSession(int uid);
    void SetUserSession(int uid, std::shared_ptr<CSession> session);
    void RmvUserSession(int uid);
private:
    UserMgr();
    std::mutex _session_mtx;
    std::unordered_map<int, std::shared_ptr<CSession>> _uid_to_session;
};




#endif //USERMGR_H
