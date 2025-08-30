//
// Created by user on 24-8-23.
//

#ifndef DATA_H
#define DATA_H


#include <vector>  // 包含vector的头文件
#include <string>  // 包含string的头文件
#include <string>
/*struct UserInfo {
    //UserInfo():name(""), pwd(""),uid(0),email("")/*,nick(""),desc(""),sex(0), icon(""), back("") {}
   // std::string name;
   // std::string pwd;
   // int uid;
   // std::string email;
    //std::string nick;
    //std::string desc;
    //int sex;
    //std::string icon;
    //std::string back;
//};*/

struct DoctorInfo {
    //DoctorInfo():
    int id;
    std::string workID;
    std::string name;
    std::string pwd;
    std::string email;
    int sex;
    std::string year;
    std::string month;
    std::string day;
    std::string IDcard;
    std::string phone;
    int department_id;
    std::string intr;
};

struct ApplyInfo {
    ApplyInfo(int uid, std::string name, std::string desc,
        std::string icon, std::string nick, int sex, int status)
        :_uid(uid),_name(name),_desc(desc),
        _icon(icon),_nick(nick),_sex(sex),_status(status){}

    int _uid;
    std::string _name;
    std::string _desc;
    std::string _icon;
    std::string _nick;
    int _sex;
    int _status;
};
struct paintInfobase {
    paintInfobase(int id,int uid, std::string name, std::string email, int sex, std::string age, std::string orderdata, std::string info)
        : _id(id),_uid(uid), _name(name), _email(email), _sex(sex), _age(age), _orderdata(orderdata), _info(info) {}
    int _id;
    int _uid;
    std::string _name;
    std::string _email;
    int _sex;
    std::string _age;
    std::string _orderdata;
    std::string _info;
};

struct paintInfocheck {
    paintInfocheck(int id,int uid, std::string name, std::string email, int sex, std::string age, std::string orderdata, std::string info, std::string checkresult)
        : id(id),_uid(uid), _name(name), _email(email), _sex(sex), _age(age), _orderdata(orderdata), _info(info), _checkresult(checkresult) {}
    int id;
    int _uid;
    std::string _name;
    std::string _email;
    int _sex;
    std::string _age;
    std::string _orderdata;
    std::string _info;
    std::string _checkresult;
};

struct DoctorDetails {
    int id;
    int workID;
    std::string name;
    std::string pwd;
    std::string email;
    int sex;
    int year;
    int month;
    int day;
    std::string IDcard;
    std::string phone;
    int department_id;
    std::string intr;
};


struct DepartmentInfo {
    int department_id;
    std::string name;
    std::string description;
    std::vector<std::shared_ptr<DoctorDetails>> doctors;  // 使用智能指针存储医生信息
};

struct GuahaoInfo {
    int id;
    int doctoruid;
    int useruid;
    std::string doctorname;
    std::string username;
    std::string useremail;
    int usersex;
    std::string userage;
    std::string userorderdata;
    std::string userinfo;
    std::string checkresult;
    std::string chufang;
};


struct HospitalizationInfo {
    int id;
    int doctor_uid;
    int patient_uid;
    std::string patient_name;
    std::string bed_number;
    std::string admission_data;
    std::string doctorname;
    std::string roomnum;
};


struct UserInfo {
    int id;
    int uid;
    std::string name;
    std::string email;
    std::string pwd;
    std::string realName;
    int sex;
    std::string year;
    std::string month;
    std::string data;
    std::string IDcard;
    std::string phone;
};


struct HosInfobase {
    int patient_uid;
    std::string patient_name;
    std::string roomnum;
    std::string bed_number;
    std::string admission_data;
};


struct paintInfochufang {
    paintInfochufang(int id,int uid, std::string name, std::string email, int sex, std::string age, std::string orderdata, std::string info, std::string checkresult, std::string chufang)
        :id(id), _uid(uid), _name(name), _email(email), _sex(sex), _age(age), _orderdata(orderdata), _info(info), _checkresult(checkresult), _chufang(chufang) {}
    int id;
    int _uid;
    std::string _name;
    std::string _email;
    int _sex;
    std::string _age;
    std::string _orderdata;
    std::string _info;
    std::string _checkresult;
    std::string _chufang;
};


#endif //DATA_H
