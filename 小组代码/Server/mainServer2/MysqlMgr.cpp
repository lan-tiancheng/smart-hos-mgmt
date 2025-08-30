//
// Created by user on 24-8-23.
//

#include "MysqlMgr.h"


MysqlMgr::~MysqlMgr() {

}

int MysqlMgr::RegUser(const std::string& name, const std::string& email, const std::string& pwd)
{
    return _dao.RegUser(name, email, pwd);
}

bool MysqlMgr::CheckEmail(const std::string& name, const std::string& email) {
    return _dao.CheckEmail(name, email);
}

bool MysqlMgr::UpdatePwd(const std::string& name, const std::string& pwd) {
    return _dao.UpdatePwd(name, pwd);
}

MysqlMgr::MysqlMgr() {
}

bool MysqlMgr::CheckPwd(const std::string& name, const std::string& pwd, UserInfo& userInfo) {
    return _dao.CheckPwd(name, pwd, userInfo);
}

bool MysqlMgr::AddFriendApply(const int& from, const int& to)
{
    return _dao.AddFriendApply(from, to);
}

bool MysqlMgr::AuthFriendApply(const int& from, const int& to) {
    return _dao.AuthFriendApply(from, to);
}

bool MysqlMgr::AddFriend(const int& from, const int& to, std::string back_name) {
    return _dao.AddFriend(from, to, back_name);
}

std::shared_ptr<UserInfo> MysqlMgr::GetUser(int uid)
{
    return _dao.GetUser(uid);
}

std::shared_ptr<UserInfo> MysqlMgr::GetUser(std::string name)
{
    return _dao.GetUser(name);
}
std::shared_ptr<DoctorInfo>  MysqlMgr::GetDoctor(int id) {
    return _dao.GetDoctor(id);
}

bool MysqlMgr::GetApplyList(int touid,
    std::vector<std::shared_ptr<ApplyInfo>>& applyList, int begin, int limit) {

    return _dao.GetApplyList(touid, applyList, begin, limit);
}

bool MysqlMgr::GetGuahaoList(int doctor_uid,
    std::vector<std::shared_ptr<paintInfobase>>& baseList,
    std::vector<std::shared_ptr<paintInfocheck>>& checkList,
    std::vector<std::shared_ptr<paintInfochufang>>& chufangList) {

    return _dao.GetGuahaoList(doctor_uid, baseList, checkList, chufangList);
}

bool MysqlMgr::UpdateDoctorInfo(int id, const std::string &name, const std::string &email, const std::string &department, const std::string &intr,const std::shared_ptr<int> &department_id) {
    return _dao.UpdateDoctorInfo(id, name, email, department, intr,department_id);
}


bool MysqlMgr::GetFriendList(int self_id, std::vector<std::shared_ptr<UserInfo> >& user_info) {
    return _dao.GetFriendList(self_id, user_info);
}

bool MysqlMgr::UpdateCheckResult(int id, const std::string& paintuid, const std::string& result)
{
    return _dao.UpdateCheckResult(id, paintuid, result);
}
bool MysqlMgr::UpdateCheckAdivice(int id, const std::string& paintuid, const std::string& result) {
    return _dao.UpdateCheckAdivice(id, paintuid, result);
}

bool MysqlMgr::InsertIntoHospitalization(int doctoruid, int patientuid, const std::string& patientname,
                                         const std::string& bed_number, const std::string& admission_number,
                                         const std::string& doctor_name, const std::string& room) {
    return _dao.InsertIntoHospitalization(doctoruid,patientuid,patientname,bed_number,admission_number,doctor_name,room);
}
bool MysqlMgr::GetHospitalizationInfo(int doctor_uid, std::vector<HosInfobase>& hospitalList) {
    return _dao.GetHospitalizationInfo(doctor_uid, hospitalList);
}
bool  MysqlMgr::GetDoctorInfoByDepartment(std::shared_ptr<DepartmentInfo> pediatrics,
                                         std::shared_ptr<DepartmentInfo> internalMedicine,
                                         std::shared_ptr<DepartmentInfo> surgery,
                                         std::shared_ptr<DepartmentInfo> gynecology,
                                         std::shared_ptr<DepartmentInfo> dermatology) {
    return _dao.GetDoctorInfoByDepartment(pediatrics,internalMedicine,surgery,gynecology,dermatology);
}
bool MysqlMgr::GetGuahaoInfo(int useruid, std::vector<std::shared_ptr<GuahaoInfo>>& guahaoList) {
    return _dao.GetGuahaoInfo(useruid, guahaoList);
}
bool MysqlMgr::UserGetHospitalizationInfo(int uid, std::vector<std::shared_ptr<HospitalizationInfo>>& hospitalizationList) {
    return _dao.UserGetHospitalizationInfo(uid, hospitalizationList);
}

bool MysqlMgr::GetUserInfo(int uid, UserInfo& userInfo) {
    return _dao.GetUserInfo(uid, userInfo);
}
bool MysqlMgr::UpdateUserInfo(int uid, const std::string& name, const std::string& IDcard, const std::string& phone, const std::string& email) {
    return _dao.UpdateUserInfo(uid, name, IDcard, phone, email);
}

bool MysqlMgr::GetDoctorIdByName(const std::string& doctorName, int& doctoruid) {
    return _dao.GetDoctorIdByName(doctorName, doctoruid);
}
bool MysqlMgr::GetUserInfoByUid(int uid, std::string& name, std::string& email, int& sex) {
    return _dao.GetUserInfoByUid(uid,name,email,sex);
}
bool MysqlMgr::InsertGuahaoData(int useruid, int doctoruid, const std::string& doctorName, const std::string& username, const std::string& useremail, int usersex, const std::string& orderTime) {
    return _dao.InsertGuahaoData(useruid,doctoruid,doctorName,username,useremail,usersex,orderTime);
}


