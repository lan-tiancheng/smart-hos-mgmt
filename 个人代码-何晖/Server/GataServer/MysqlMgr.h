//
// Created by user on 24-8-19.
//

#ifndef MYSQLMGR_H
#define MYSQLMGR_H



#include "const.h"
#include "MysqlDao.h"
class MysqlMgr: public Singleton<MysqlMgr>
{
    friend class Singleton<MysqlMgr>;
public:
    ~MysqlMgr();
    int RegUser(const std::string& name, const std::string& email,  const std::string& pwd);
    int RegDoctor(const std::string& workID, const std::string& email, const std::string& pwd);
    bool CheckEmail(const std::string& name, const std::string & email);
    bool UpdatePwd(const std::string& name, const std::string& email);
    bool CheckPwd(const std::string& email, const std::string& pwd, UserInfo& userInfo);
    bool CheckDoctorPwd(const std::string& workID, const std::string& pwd, DoctorInfo& doctorInfo);
    bool CheckDoctorEmail(const std::string& workID, const std::string& email);
    bool UpdateDoctorPwd(const std::string& workID, const std::string& newpwd);
    bool UpdateDoctorDetails(const std::string& workID, const std::string& name, int sex, const std::string& year, const std::string& month, const std::string& data, const std::string& IDcard, const std::string& phone, int department_id, const std::string& intr);
    bool UpdateUserDetails(int uid, const std::string& realname, int sex, const std::string& year, const std::string& month, const std::string& data, const std::string& IDcard, const std::string& phone);
private:
    MysqlMgr();
    MysqlDao  _dao;
};



#endif //MYSQLMGR_H
