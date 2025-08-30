//
// Created by user on 24-8-23.
//

#ifndef MYSQLMGR_H
#define MYSQLMGR_H



#include "const.h"
#include "MysqlDao.h"
#include "Singleton.h"
#include <vector>

class MysqlMgr: public Singleton<MysqlMgr>
{
    friend class Singleton<MysqlMgr>;
public:
    ~MysqlMgr();
    int RegUser(const std::string& name, const std::string& email,  const std::string& pwd);
    bool CheckEmail(const std::string& name, const std::string & email);
    bool UpdatePwd(const std::string& name, const std::string& email);
    bool CheckPwd(const std::string& name, const std::string& pwd, UserInfo& userInfo);
    bool AddFriendApply(const int& from, const int& to);
    bool GetGuahaoList(int doctor_uid,
    std::vector<std::shared_ptr<paintInfobase>>& baseList,
    std::vector<std::shared_ptr<paintInfocheck>>& checkList,
    std::vector<std::shared_ptr<paintInfochufang>>& chufangList);
    bool AuthFriendApply(const int& from, const int& to);
    bool AddFriend(const int& from, const int& to, std::string back_name);
    bool UpdateCheckResult(int id, const std::string& paintuid, const std::string& result);
bool UpdateCheckAdivice(int id, const std::string& paintuid, const std::string& result);
    bool GetDoctorInfoByDepartment(std::shared_ptr<DepartmentInfo> pediatrics,
                                         std::shared_ptr<DepartmentInfo> internalMedicine,
                                         std::shared_ptr<DepartmentInfo> surgery,
                                         std::shared_ptr<DepartmentInfo> gynecology,
                                         std::shared_ptr<DepartmentInfo> dermatology);
    bool GetGuahaoInfo(int useruid, std::vector<std::shared_ptr<GuahaoInfo>>& guahaoList);
    bool UserGetHospitalizationInfo(int uid, std::vector<std::shared_ptr<HospitalizationInfo>>& hospitalizationList);
    bool GetUserInfo(int uid, UserInfo& userInfo);
    bool UpdateUserInfo(int uid, const std::string& name, const std::string& IDcard, const std::string& phone, const std::string& email);
    bool GetDoctorIdByName(const std::string& doctorName, int& doctoruid);
    bool GetUserInfoByUid(int uid, std::string& name, std::string& email, int& sex);
    bool InsertGuahaoData(int useruid, int doctoruid, const std::string& doctorName, const std::string& username, const std::string& useremail, int usersex, const std::string& orderTime);













    bool GetHospitalizationInfo(int doctor_uid, std::vector<HosInfobase>& hospitalList);
    bool InsertIntoHospitalization(int doctoruid, int patientuid, const std::string& patientname,
                                         const std::string& bed_number, const std::string& admission_number,
                                         const std::string& doctor_name, const std::string& room);
    bool UpdateDoctorInfo(int id, const std::string& name, const std::string& email, const std::string& department, const std::string& intr,const std::shared_ptr<int> &department_id);
    std::shared_ptr<UserInfo> GetUser(int uid);
    std::shared_ptr<UserInfo> GetUser(std::string name);
    bool GetApplyList(int touid, std::vector<std::shared_ptr<ApplyInfo>>& applyList, int begin, int limit=10);
    bool GetFriendList(int self_id, std::vector<std::shared_ptr<UserInfo> >& user_info);
    std::shared_ptr<DoctorInfo>  GetDoctor(int id);
private:
    MysqlMgr();
    MysqlDao  _dao;
};


#endif //MYSQLMGR_H
