//
// Created by user on 24-8-23.
//

#include "LogicSystem.h"
#include "StatusGrpcClient.h"
#include "MysqlMgr.h"
#include "const.h"
#include "RedisMgr.h"
#include "UserMgr.h"
#include "ChatGrpcClient.h"
#include"MysqlDao.h"

using namespace std;

LogicSystem::LogicSystem():_b_stop(false){
	RegisterCallBacks();
	_worker_thread = std::thread (&LogicSystem::DealMsg, this);
}

LogicSystem::~LogicSystem(){
	_b_stop = true;
	_consume.notify_one();
	_worker_thread.join();
}

void LogicSystem::PostMsgToQue(shared_ptr < LogicNode> msg) {
	std::unique_lock<std::mutex> unique_lk(_mutex);
	_msg_que.push(msg);
	//由0变为1则发送通知信号
	if (_msg_que.size() == 1) {
		unique_lk.unlock();
		_consume.notify_one();
	}
}

void LogicSystem::DealMsg() {
	for (;;) {
		std::unique_lock<std::mutex> unique_lk(_mutex);
		//判断队列为空则用条件变量阻塞等待，并释放锁
		while (_msg_que.empty() && !_b_stop) {
			_consume.wait(unique_lk);
		}

		//判断是否为关闭状态，把所有逻辑执行完后则退出循环
		if (_b_stop ) {
			while (!_msg_que.empty()) {
				auto msg_node = _msg_que.front();
				cout << "recv_msg id  is " << msg_node->_recvnode->_msg_id << endl;
				auto call_back_iter = _fun_callbacks.find(msg_node->_recvnode->_msg_id);
				if (call_back_iter == _fun_callbacks.end()) {
					_msg_que.pop();
					continue;
				}
				call_back_iter->second(msg_node->_session, msg_node->_recvnode->_msg_id,
					std::string(msg_node->_recvnode->_data, msg_node->_recvnode->_cur_len));
				_msg_que.pop();
			}
			break;
		}

		//如果没有停服，且说明队列中有数据
		auto msg_node = _msg_que.front();
		cout << "recv_msg id  is " << msg_node->_recvnode->_msg_id << endl;
		auto call_back_iter = _fun_callbacks.find(msg_node->_recvnode->_msg_id);
		if (call_back_iter == _fun_callbacks.end()) {
			_msg_que.pop();
			std::cout << "msg id [" << msg_node->_recvnode->_msg_id << "] handler not found" << std::endl;
			continue;
		}
		call_back_iter->second(msg_node->_session, msg_node->_recvnode->_msg_id,
			std::string(msg_node->_recvnode->_data, msg_node->_recvnode->_cur_len));
		_msg_que.pop();
	}
}

void LogicSystem::RegisterCallBacks() {
	_fun_callbacks[MSG_CHAT_LOGIN] = std::bind(&LogicSystem::LoginHandler, this,
		placeholders::_1, placeholders::_2, placeholders::_3);

	_fun_callbacks[ID_SEARCH_USER_REQ] = std::bind(&LogicSystem::SearchInfo, this,
		placeholders::_1, placeholders::_2, placeholders::_3);

	_fun_callbacks[ID_ADD_FRIEND_REQ] = std::bind(&LogicSystem::AddFriendApply, this,
		placeholders::_1, placeholders::_2, placeholders::_3);

	_fun_callbacks[ID_AUTH_FRIEND_REQ] = std::bind(&LogicSystem::AuthFriendApply, this,
		placeholders::_1, placeholders::_2, placeholders::_3);

	_fun_callbacks[ID_TEXT_CHAT_MSG_REQ] = std::bind(&LogicSystem::DealChatTextMsg, this,
		placeholders::_1, placeholders::_2, placeholders::_3);

	_fun_callbacks[MSG_DOCTOR_MAINSERVER_LOGIN] = std::bind(&LogicSystem::DoctorLoginHandler, this,
		placeholders::_1, placeholders::_2, placeholders::_3);
	_fun_callbacks[MSG_EDIT_DOCTOR_SELFINFO] = std::bind(&LogicSystem::EditDoctorInfo, this,
		placeholders::_1, placeholders::_2, placeholders::_3);

	_fun_callbacks[ID_DOCTOR_CALL_PAINTINFO] = std::bind(&LogicSystem::DoctorCallForPaintInfo, this,
		placeholders::_1, placeholders::_2, placeholders::_3);
	_fun_callbacks[ID_WRITE_PAINT_CHECKRESULT] = std::bind(&LogicSystem::DoctorWriteCheckResult, this,
		placeholders::_1, placeholders::_2, placeholders::_3);
	_fun_callbacks[ID_WRITE_PAINT_ADVICE] = std::bind(&LogicSystem::DoctorWriteAdvice, this,
		placeholders::_1, placeholders::_2, placeholders::_3);

	_fun_callbacks[ID_hospital] = std::bind(&LogicSystem::addHospi, this,
		placeholders::_1, placeholders::_2, placeholders::_3);

	_fun_callbacks[ID_UPDATE_USER_INFO] = std::bind(&LogicSystem::UpdateUserInfo, this,
		placeholders::_1, placeholders::_2, placeholders::_3);
	_fun_callbacks[ID_order] = std::bind(&LogicSystem::ProcessOrderRequest, this,
		placeholders::_1, placeholders::_2, placeholders::_3);


}


void LogicSystem::addHospi(shared_ptr<CSession> session, const short &msg_id, const string &msg_data) {
	Json::Reader reader;
	Json::Value root;
	reader.parse(msg_data, root);
	Json::Value  rtvalue;
	Defer defer([this, &rtvalue, session]() {
		std::string return_str = rtvalue.toStyledString();
		session->Send(return_str, ID_WRITE_PAINT_ADVICE);
		});
	auto doctoruid=root["doctor_uid"].asInt();
	auto patientuid_str = root["patient_uid"].asString();
	int patientuid = std::stoi(patientuid_str);

	auto patientname=root["patient_name"].asString();
	auto bed_number=root["bed_number"].asString();
	auto admission_number=root["admission_data"].asString();
	auto doctor_name=root["doctorname"].asString();
	auto room=root["room"].asString();

	bool tmp=MysqlMgr::GetInstance()->InsertIntoHospitalization(doctoruid,patientuid,patientname,bed_number,admission_number,doctor_name,room);


}


void LogicSystem::DoctorWriteAdvice(shared_ptr<CSession> session, const short &msg_id, const string &msg_data) {
	Json::Reader reader;
	Json::Value root;
	reader.parse(msg_data, root);
	auto id = root["id"].asString();
	int iid=std::stoi(id);
	//auto token = root["token"].asString();
	auto paintuid=root["doctorid"].asString();
	std::cout << "user login uid is  "  << endl;
	Json::Value  rtvalue;
	Defer defer([this, &rtvalue, session]() {
		std::string return_str = rtvalue.toStyledString();
		session->Send(return_str, ID_WRITE_PAINT_ADVICE);
		});
	auto result=root["result"].asString();
	bool dodd=MysqlMgr::GetInstance()->UpdateCheckAdivice(iid,paintuid,result);







}
void LogicSystem::ProcessOrderRequest(shared_ptr<CSession> session, const short &msg_id, const string &msg_data) {
	Json::Reader reader;
	Json::Value root;
	reader.parse(msg_data, root);

	auto uuseruid = root["useruid"].asString();
	std::string doctorName = root["doctorname"].asString();
	std::string username = root["username"].asString();
	std::string useremail = root["email"].asString();
	std::string usersex_str = root["usersex"].asString();
	std::string orderTime = root["time"].asString();
	int useruid=std::stoi(uuseruid);

	int usersex;
	if (usersex_str == "女") {
		usersex = 0;
	} else if (usersex_str == "男") {
		usersex = 1;
	} else {
		usersex = 2;
	}

	Json::Value rtvalue;
	Defer defer([this, &rtvalue, session, msg_id]() {
		std::string return_str = rtvalue.toStyledString();
		session->Send(return_str, msg_id);
	});

	// 查询 doctor 表中的 doctoruid
	int doctoruid = -1;
	bool doctorFound = MysqlMgr::GetInstance()->GetDoctorIdByName(doctorName, doctoruid);

	if (!doctorFound) {
		rtvalue["error"] = "Doctor not found.";
		return;
	}

	// 插入新的挂号数据
	bool insertSuccess = MysqlMgr::GetInstance()->InsertGuahaoData(useruid, doctoruid, doctorName, username, useremail, usersex, orderTime);

	if (!insertSuccess) {
		rtvalue["error"] = "Failed to insert new guahao data.";
		return;
	}

	rtvalue["error"] = "Success";
}


void LogicSystem::DoctorWriteCheckResult(shared_ptr<CSession> session, const short &msg_id, const string &msg_data) {
	Json::Reader reader;
	Json::Value root;
	reader.parse(msg_data, root);
	auto id = root["id"].asString();
	int iid=std::stoi(id);
	//auto token = root["token"].asString();
	auto paintuid=root["doctorid"].asString();
	std::cout << "user login uid is  "  << endl;
	Json::Value  rtvalue;
	Defer defer([this, &rtvalue, session]() {
		std::string return_str = rtvalue.toStyledString();
		session->Send(return_str, ID_WRITE_PAINT_CHECKRESULT);
		});
	auto result=root["result"].asString();
	bool dodd=MysqlMgr::GetInstance()->UpdateCheckResult(iid,paintuid,result);







}

void LogicSystem::DoctorCallForPaintInfo(shared_ptr<CSession> session, const short &msg_id, const string &msg_data) {
	Json::Reader reader;
	Json::Value root;
	reader.parse(msg_data, root);
	auto uid = root["uid"].asInt();
	auto token = root["token"].asString();
	std::cout << "user login uid is  " << uid << " user token  is "
		<< token << endl;

	Json::Value  rtvalue;
	Defer defer([this, &rtvalue, session]() {
		std::string return_str = rtvalue.toStyledString();
		session->Send(return_str, ID_DOCTOR_CALL_PAINTINFO);
		});

	std::vector<std::shared_ptr<paintInfobase>> baseList;
    std::vector<std::shared_ptr<paintInfocheck>> checkList;
    std::vector<std::shared_ptr<paintInfochufang>> chufangList;
	std::vector<HosInfobase> hospitalList;

    //Json::Value rtvalue;

    if (GetGuahaoInfo(uid, baseList, checkList, chufangList)) {
        Json::Value baseArray(Json::arrayValue);
        for (const auto& base : baseList) {
            Json::Value obj;
        	obj["id"]=base->_id;
            obj["userid"] = base->_uid;
            obj["username"] = base->_name;
            obj["useremail"] = base->_email;
            obj["usersex"] = base->_sex;
            obj["userage"] = base->_age;
            obj["userorderdata"] = base->_orderdata;
            obj["userinfo"] = base->_info;
            baseArray.append(obj);
        }
        rtvalue["baseList"] = baseArray;

        Json::Value checkArray(Json::arrayValue);
        for (const auto& check : checkList) {
            Json::Value obj;
        	obj["id"]=check->id;
            obj["userid"] = check->_uid;
            obj["username"] = check->_name;
            obj["useremail"] = check->_email;
            obj["usersex"] = check->_sex;
            obj["userage"] = check->_age;
            obj["userorderdata"] = check->_orderdata;
            obj["userinfo"] = check->_info;
            obj["checkresult"] = check->_checkresult;
            checkArray.append(obj);
        }
        rtvalue["checkList"] = checkArray;

        Json::Value chufangArray(Json::arrayValue);
        for (const auto& chufang : chufangList) {
            Json::Value obj;
        	obj["id"]=chufang->id;
            obj["userid"] = chufang->_uid;
            obj["username"] = chufang->_name;
            obj["useremail"] = chufang->_email;
            obj["usersex"] = chufang->_sex;
            obj["userage"] = chufang->_age;
            obj["userorderdata"] = chufang->_orderdata;
            obj["userinfo"] = chufang->_info;
            obj["checkresult"] = chufang->_checkresult;
            obj["chufang"] = chufang->_chufang;
            chufangArray.append(obj);
        }
        rtvalue["chufangList"] = chufangArray;
    }



		// 新增医院信息查询
		if (MysqlMgr::GetInstance()->GetHospitalizationInfo(uid, hospitalList)) {  // 假设uid对应doctor_uid
			Json::Value hospitalArray(Json::arrayValue);
			for (const auto& hospital : hospitalList) {
				Json::Value obj;
				obj["patient_uid"] = hospital.patient_uid;
				obj["patient_name"] = hospital.patient_name;
				obj["roomnum"] = hospital.roomnum;
				obj["bed_number"] = hospital.bed_number;
				obj["admission_data"] = hospital.admission_data;
				hospitalArray.append(obj);
			}
			rtvalue["hospitalList"] = hospitalArray;
		}


    return;



}

bool LogicSystem::GetGuahaoInfo(int doctor_uid,
	std::vector<std::shared_ptr<paintInfobase>>& baseList,
	std::vector<std::shared_ptr<paintInfocheck>>& checkList,
	std::vector<std::shared_ptr<paintInfochufang>>& chufangList) {

	return MysqlMgr::GetInstance()->GetGuahaoList(doctor_uid, baseList, checkList, chufangList);
}

void LogicSystem::EditDoctorInfo(shared_ptr<CSession> session, const short &msg_id, const string &msg_data) {
	Json::Reader reader;
	Json::Value root;
	reader.parse(msg_data, root);
	auto uid = root["uid"].asInt();
	//auto token = root["token"].asString();
	std::cout << "doctor login uid is  " << uid << " user token  is "
		 << endl;

	Json::Value  rtvalue;



	std::string uid_str = std::to_string(uid);
	Defer defer([this, &rtvalue, session]() {
		std::string return_str = rtvalue.toStyledString();

		session->Send(return_str, MSG_EDIT_DOCTOR_SELFINFO);
		});

	auto name = root["name"].asString();
	std::cout<<name<<std::endl;
	auto department= root["department"].asString();
	auto email = root["email"].asString();
	auto intro = root["intr"].asString();
	auto department_id=std::make_shared<int>();
	bool Edit_doctorinfo=true;
	Edit_doctorinfo=MysqlMgr::GetInstance()->UpdateDoctorInfo(uid,name, email,department,intro,department_id);
	Edit_doctorinfo=true;
	if (!Edit_doctorinfo) {
		rtvalue["error"] = ErrorCodes::UidInvalid;
		return ;
	}

	rtvalue["error"]=ErrorCodes::Success;
	std::string base_key = USER_BASE_INFO + uid_str;




	Json::Value redis_root;
	/////////redis_root["id"]=doctor_info->id;
	redis_root["name"]=name;
	//redis_root["pwd"]=doctor_info->pwd;
	redis_root["email"]=email;
	//////////redis_root["sex"]=doctorinfo->sex;
	//redis_root["year"]=doctorinfo->year;
	//redis_root["month"]=doctorinfo->month;
	//redis_root["day"]=doctorinfo->day;
	//redis_root["workID"]=doctorinfo->workID;
	redis_root["department"]=*department_id;
	redis_root["intr"]=intro;
	//redis_root["IDcard"]=doctorinfo->IDcard;
	RedisMgr::GetInstance()->Set(base_key, redis_root.toStyledString());
	//rtvalue["error"] = ErrorCodes::Success;
	rtvalue["name"] = name;
	rtvalue["email"] = email;
	rtvalue["department"] = *department_id;
	rtvalue["intr"] = intro;
	std::cout<<rtvalue["error"].asString()<<std::endl;
	return;


}

void LogicSystem::UpdateUserInfo(shared_ptr<CSession> session, const short &msg_id, const string &msg_data) {
	Json::Reader reader;
	Json::Value root;
	reader.parse(msg_data, root);

	auto uid = root["uid"].asInt();
	std::string name = root["name"].asString();
	std::string dob = root["dob"].asString();  // 如果需要使用 dob
	std::string IDcard = root["IDcard"].asString();
	std::string phone = root["phone"].asString();
	std::string email = root["email"].asString();

	Json::Value rtvalue;

	// 创建 Redis 缓存键
	std::string uid_str = std::to_string(uid);
	std::string base_key = "user:" + uid_str + ":info";

	Defer defer([this, &rtvalue, session, msg_id]() {
	std::string return_str = rtvalue.toStyledString();
	session->Send(return_str, msg_id);
});

	// 更新数据库
	bool updateSuccess = MysqlMgr::GetInstance()->UpdateUserInfo(uid, name, IDcard, phone, email);

	if (!updateSuccess) {
		rtvalue["error"] = "Update failed";
		return;
	}

	// 更新 Redis 缓存
	Json::Value redis_root;
	redis_root["name"] = name;
	redis_root["IDcard"] = IDcard;
	redis_root["phone"] = phone;
	redis_root["email"] = email;

	RedisMgr::GetInstance()->Set(base_key, redis_root.toStyledString());

	rtvalue["error"] = "Success";
	rtvalue["name"] = name;
	rtvalue["IDcard"] = IDcard;
	rtvalue["phone"] = phone;
	rtvalue["email"] = email;
}


void LogicSystem::DoctorLoginHandler(shared_ptr<CSession> session, const short &msg_id, const string &msg_data) {
	Json::Reader reader;
	Json::Value root;
	reader.parse(msg_data, root);
	auto uid = root["uid"].asInt();
	auto token = root["token"].asString();
	std::cout << "doctor login uid is  " << uid << " user token  is "
		<< token << endl;

	Json::Value  rtvalue;
	Defer defer([this, &rtvalue, session]() {
		std::string return_str = rtvalue.toStyledString();
		session->Send(return_str, MSG_CHAT_DOCTOR_LOGIN_RSP);
		});
	//从redis获取用户token是否正确
	std::string uid_str = std::to_string(uid);
	std::string token_key = USERTOKENPREFIX + uid_str;
	std::string token_value = "";
	bool success = RedisMgr::GetInstance()->Get(token_key, token_value);
	if (!success) {
		rtvalue["error"] = ErrorCodes::UidInvalid;
		return ;
	}

	if (token_value != token) {
		rtvalue["error"] = ErrorCodes::TokenInvalid;
		return ;
	}

	rtvalue["error"] = ErrorCodes::Success;

	std::string base_key = USER_BASE_INFO + uid_str;
	auto doctor_info=std::make_shared<DoctorInfo>();
	bool b_base=GetDoctorInfo(base_key, uid, doctor_info);
	if (!b_base) {
		rtvalue["error"] = ErrorCodes::UidInvalid;
		return;
	}

	rtvalue["ID"]=uid;
	rtvalue["workID"]=doctor_info->workID;
	rtvalue["name"]=doctor_info->name;
	rtvalue["pwd"]=doctor_info->pwd;
	rtvalue["email"]=doctor_info->email;
	rtvalue["phone"]=doctor_info->phone;
	rtvalue["sex"]=doctor_info->sex;
	rtvalue["year"]=doctor_info->year;
	rtvalue["month"]=doctor_info->month;
	rtvalue["day"]=doctor_info->day;
	rtvalue["IDcard"]=doctor_info->IDcard;
	rtvalue["department_id"]=doctor_info->department_id;
	rtvalue["intr"]=doctor_info->intr;
	auto server_name = ConfigMgr::Inst().GetValue("SelfServer", "Name");
	//将登录数量增加
	auto rd_res = RedisMgr::GetInstance()->HGet(LOGIN_COUNT, server_name);
	int count = 0;
	if (!rd_res.empty()) {
		count = std::stoi(rd_res);
	}

	count++;
	auto count_str = std::to_string(count);
	RedisMgr::GetInstance()->HSet(LOGIN_COUNT, server_name, count_str);
	//session绑定用户uid
	session->SetUserId(uid);
	//为用户设置登录ip server的名字
	std::string  ipkey = USERIPPREFIX + uid_str;
	RedisMgr::GetInstance()->Set(ipkey, server_name);
	//uid和session绑定管理,方便以后踢人操作
	UserMgr::GetInstance()->SetUserSession(uid, session);

	return;

}

void LogicSystem::LoginHandler(shared_ptr<CSession> session, const short &msg_id, const string &msg_data) {
	Json::Reader reader;
	Json::Value root;
	reader.parse(msg_data, root);
	auto uid = root["uid"].asInt();
	auto token = root["token"].asString();
	std::cout << "user login uid is  " << uid << " user token  is "
		<< token << endl;

	Json::Value  rtvalue;
	Defer defer([this, &rtvalue, session]() {
		std::string return_str = rtvalue.toStyledString();
		session->Send(return_str, MSG_CHAT_LOGIN_RSP);
		});

	//从redis获取用户token是否正确
	std::string uid_str = std::to_string(uid);
	std::string token_key = USERTOKENPREFIX + uid_str;
	std::string token_value = "";
	bool success = RedisMgr::GetInstance()->Get(token_key, token_value);
	if (!success) {
		rtvalue["error"] = ErrorCodes::UidInvalid;
		return ;
	}

	if (token_value != token) {
		rtvalue["error"] = ErrorCodes::TokenInvalid;
		return ;
	}

	rtvalue["error"] = ErrorCodes::Success;

	std::string base_key = USER_BASE_INFO + uid_str;
	auto user_info = std::make_shared<UserInfo>();
	UserInfo userInfo;

	// 获取用户信息
	if (MysqlMgr::GetInstance()->GetUserInfo(uid, userInfo)) {
		Json::Value obj;
		obj["id"] = userInfo.id;
		obj["uid"] = userInfo.uid;
		obj["name"] = userInfo.name;
		obj["email"] = userInfo.email;
		obj["pwd"] = userInfo.pwd;
		obj["realName"] = userInfo.realName;
		obj["sex"] = userInfo.sex;
		obj["year"] = userInfo.year;
		obj["month"] = userInfo.month;
		obj["data"] = userInfo.data;
		obj["IDcard"] = userInfo.IDcard;
		obj["phone"] = userInfo.phone;
		rtvalue["userInfo"] = obj;
	} else {
		rtvalue["error"] = "Failed to retrieve user information.";
	}
	auto pediatrics = std::make_shared<DepartmentInfo>(DepartmentInfo{1, "儿科", "负责儿童疾病的科室", {}});
    auto internalMedicine = std::make_shared<DepartmentInfo>(DepartmentInfo{2, "内科", "负责内科疾病的科室", {}});
    auto surgery = std::make_shared<DepartmentInfo>(DepartmentInfo{3, "外科", "负责外科手术的科室", {}});
    auto gynecology = std::make_shared<DepartmentInfo>(DepartmentInfo{4, "妇科", "负责妇女健康和疾病的科室", {}});
    auto dermatology = std::make_shared<DepartmentInfo>(DepartmentInfo{5, "皮肤科", "负责皮肤疾病的科室", {}});

    // 调用数据库操作函数，填充数据
    if (MysqlMgr::GetInstance()->GetDoctorInfoByDepartment(pediatrics, internalMedicine, surgery, gynecology, dermatology)) {
        // 将每个科室信息转换为 JSON 并添加到返回值中
        auto addDepartmentToJson = [](const std::shared_ptr<DepartmentInfo>& department, Json::Value& root) {
            Json::Value departmentJson;
            departmentJson["department_id"] = department->department_id;
            departmentJson["name"] = department->name;
            departmentJson["description"] = department->description;

            Json::Value doctorsArray(Json::arrayValue);
            for (const auto& doctor : department->doctors) {
                Json::Value doctorJson;
                doctorJson["id"] = doctor->id;
                doctorJson["workID"] = doctor->workID;
                doctorJson["name"] = doctor->name;
                doctorJson["pwd"] = doctor->pwd;
                doctorJson["email"] = doctor->email;
                doctorJson["sex"] = doctor->sex;
                doctorJson["year"] = doctor->year;
                doctorJson["month"] = doctor->month;
                doctorJson["day"] = doctor->day;
                doctorJson["IDcard"] = doctor->IDcard;
                doctorJson["phone"] = doctor->phone;
                doctorJson["department_id"] = doctor->department_id;
                doctorJson["intr"] = doctor->intr;
                doctorsArray.append(doctorJson);
            }

            departmentJson["doctors"] = doctorsArray;
            root.append(departmentJson);
        };

        // 添加所有科室到 JSON 返回值
        addDepartmentToJson(pediatrics, rtvalue["departments"]);
        addDepartmentToJson(internalMedicine, rtvalue["departments"]);
        addDepartmentToJson(surgery, rtvalue["departments"]);
        addDepartmentToJson(gynecology, rtvalue["departments"]);
        addDepartmentToJson(dermatology, rtvalue["departments"]);
    }

	std::vector<std::shared_ptr<GuahaoInfo>> guahaoList;

	// 获取挂号信息
	if (MysqlMgr::GetInstance()->GetGuahaoInfo(uid, guahaoList)) {
		Json::Value guahaoArray(Json::arrayValue);
		for (const auto& guahao : guahaoList) {
			Json::Value obj;
			obj["id"] = guahao->id;
			obj["doctoruid"] = guahao->doctoruid;
			obj["useruid"] = guahao->useruid;
			obj["doctorname"] = guahao->doctorname;
			obj["username"] = guahao->username;
			obj["useremail"] = guahao->useremail;
			obj["usersex"] = guahao->usersex;
			obj["userage"] = guahao->userage;
			obj["userorderdata"] = guahao->userorderdata;
			obj["userinfo"] = guahao->userinfo;
			obj["checkresult"] = guahao->checkresult;
			obj["chufang"] = guahao->chufang;
			guahaoArray.append(obj);
		}
		rtvalue["guahaoList"] = guahaoArray;
	} else {
		rtvalue["error"] = "Failed to retrieve guahao information.";
	}

	std::vector<std::shared_ptr<HospitalizationInfo>> hospitalizationList;

	// 获取住院信息
	if (MysqlMgr::GetInstance()->UserGetHospitalizationInfo(uid, hospitalizationList)) {
		Json::Value hospitalizationArray(Json::arrayValue);
		for (const auto& hospitalization : hospitalizationList) {
			Json::Value obj;
			obj["id"] = hospitalization->id;
			obj["doctor_uid"] = hospitalization->doctor_uid;
			obj["patient_uid"] = hospitalization->patient_uid;
			obj["patient_name"] = hospitalization->patient_name;
			obj["bed_number"] = hospitalization->bed_number;
			obj["admission_data"] = hospitalization->admission_data;
			obj["doctorname"] = hospitalization->doctorname;
			obj["roomnum"] = hospitalization->roomnum;
			hospitalizationArray.append(obj);
		}
		rtvalue["hospitalizationList"] = hospitalizationArray;
	} else {
		rtvalue["error"] = "Failed to retrieve hospitalization information.";
	}



	//rtvalue["nick"] = user_info->nick;
	//rtvalue["desc"] = user_info->desc;
	//rtvalue["sex"] = user_info->sex;
	//rtvalue["icon"] = user_info->icon;

	//从数据库获取申请列表
	/*std::vector<std::shared_ptr<ApplyInfo>> apply_list;
	auto b_apply = GetFriendApplyInfo(uid,apply_list);
	if (b_apply) {
		for (auto & apply : apply_list) {
			Json::Value obj;
			obj["name"] = apply->_name;
			obj["uid"] = apply->_uid;
			obj["icon"] = apply->_icon;
			obj["nick"] = apply->_nick;
			obj["sex"] = apply->_sex;
			obj["desc"] = apply->_desc;
			obj["status"] = apply->_status;
			rtvalue["apply_list"].append(obj);
		}
	}

	//获取好友列表
	/*std::vector<std::shared_ptr<UserInfo>> friend_list;
	bool b_friend_list = GetFriendList(uid, friend_list);
	for (auto& friend_ele : friend_list) {
		Json::Value obj;
		obj["name"] = friend_ele->name;
		obj["uid"] = friend_ele->uid;
		obj["icon"] = friend_ele->icon;
		obj["nick"] = friend_ele->nick;
		obj["sex"] = friend_ele->sex;
		obj["desc"] = friend_ele->desc;
		obj["back"] = friend_ele->back;
		rtvalue["friend_list"].append(obj);
	}*/

	auto server_name = ConfigMgr::Inst().GetValue("SelfServer", "Name");
	//将登录数量增加
	auto rd_res = RedisMgr::GetInstance()->HGet(LOGIN_COUNT, server_name);
	int count = 0;
	if (!rd_res.empty()) {
		count = std::stoi(rd_res);
	}

	count++;
	auto count_str = std::to_string(count);
	RedisMgr::GetInstance()->HSet(LOGIN_COUNT, server_name, count_str);
	//session绑定用户uid
	session->SetUserId(uid);
	//为用户设置登录ip server的名字
	std::string  ipkey = USERIPPREFIX + uid_str;
	RedisMgr::GetInstance()->Set(ipkey, server_name);
	//uid和session绑定管理,方便以后踢人操作
	UserMgr::GetInstance()->SetUserSession(uid, session);

	return;
}

void LogicSystem::SearchInfo(std::shared_ptr<CSession> session, const short& msg_id, const string& msg_data)
{
	Json::Reader reader;
	Json::Value root;
	reader.parse(msg_data, root);
	auto uid_str = root["uid"].asString();
	std::cout << "user SearchInfo uid is  " << uid_str << endl;

	Json::Value  rtvalue;

	Defer defer([this, &rtvalue, session]() {
		std::string return_str = rtvalue.toStyledString();
		session->Send(return_str, ID_SEARCH_USER_RSP);
		});

	bool b_digit = isPureDigit(uid_str);
	if (b_digit) {
		GetUserByUid(uid_str, rtvalue);
	}
	else {
		GetUserByName(uid_str, rtvalue);
	}
	return;
}

void LogicSystem::AddFriendApply(std::shared_ptr<CSession> session, const short& msg_id, const string& msg_data)
{
	Json::Reader reader;
	Json::Value root;
	reader.parse(msg_data, root);
	auto uid = root["uid"].asInt();
	auto applyname = root["applyname"].asString();
	auto bakname = root["bakname"].asString();
	auto touid = root["touid"].asInt();
	std::cout << "user login uid is  " << uid << " applyname  is "
		<< applyname << " bakname is " << bakname << " touid is " << touid << endl;

	Json::Value  rtvalue;
	rtvalue["error"] = ErrorCodes::Success;
	Defer defer([this, &rtvalue, session]() {
		std::string return_str = rtvalue.toStyledString();
		session->Send(return_str, ID_ADD_FRIEND_RSP);
		});

	//先更新数据库
	MysqlMgr::GetInstance()->AddFriendApply(uid, touid);

	//查询redis 查找touid对应的server ip
	auto to_str = std::to_string(touid);
	auto to_ip_key = USERIPPREFIX + to_str;
	std::string to_ip_value = "";
	bool b_ip = RedisMgr::GetInstance()->Get(to_ip_key, to_ip_value);
	if (!b_ip) {
		return;
	}


	auto& cfg = ConfigMgr::Inst();
	auto self_name = cfg["SelfServer"]["Name"];


	std::string base_key = USER_BASE_INFO + std::to_string(uid);
	auto apply_info = std::make_shared<UserInfo>();
	bool b_info = GetBaseInfo(base_key, uid, apply_info);

	//直接通知对方有申请消息
	if (to_ip_value == self_name) {
		auto session = UserMgr::GetInstance()->GetSession(touid);
		if (session) {
			//在内存中则直接发送通知对方
			Json::Value  notify;
			notify["error"] = ErrorCodes::Success;
			notify["applyuid"] = uid;
			notify["name"] = applyname;
			notify["desc"] = "";
			if (b_info) {
				//notify["icon"] = apply_info->icon;
				//notify["sex"] = apply_info->sex;
				//notify["nick"] = apply_info->nick;
			}
			std::string return_str = notify.toStyledString();
			session->Send(return_str, ID_NOTIFY_ADD_FRIEND_REQ);
		}

		return ;
	}


	AddFriendReq add_req;
	add_req.set_applyuid(uid);
	add_req.set_touid(touid);
	add_req.set_name(applyname);
	add_req.set_desc("");
	if (b_info) {
		//add_req.set_icon(apply_info->icon);
		//add_req.set_sex(apply_info->sex);
		//add_req.set_nick(apply_info->nick);
	}

	//发送通知
	ChatGrpcClient::GetInstance()->NotifyAddFriend(to_ip_value,add_req);

}

void LogicSystem::AuthFriendApply(std::shared_ptr<CSession> session, const short& msg_id, const string& msg_data) {

	Json::Reader reader;
	Json::Value root;
	reader.parse(msg_data, root);

	auto uid = root["fromuid"].asInt();
	auto touid = root["touid"].asInt();
	auto back_name = root["back"].asString();
	std::cout << "from " << uid << " auth friend to " << touid << std::endl;

	Json::Value  rtvalue;
	rtvalue["error"] = ErrorCodes::Success;
	auto user_info = std::make_shared<UserInfo>();

	std::string base_key = USER_BASE_INFO + std::to_string(touid);
	bool b_info = GetBaseInfo(base_key, touid, user_info);
	if (b_info) {
		rtvalue["name"] = user_info->name;
		//rtvalue["nick"] = user_info->nick;
		//rtvalue["icon"] = user_info->icon;
		//rtvalue["sex"] = user_info->sex;
		rtvalue["uid"] = touid;
	}
	else {
		rtvalue["error"] = ErrorCodes::UidInvalid;
	}


	Defer defer([this, &rtvalue, session]() {
		std::string return_str = rtvalue.toStyledString();
		session->Send(return_str, ID_AUTH_FRIEND_RSP);
		});

	//先更新数据库
	MysqlMgr::GetInstance()->AuthFriendApply(uid, touid);

	//更新数据库添加好友
	MysqlMgr::GetInstance()->AddFriend(uid, touid,back_name);

	//查询redis 查找touid对应的server ip
	auto to_str = std::to_string(touid);
	auto to_ip_key = USERIPPREFIX + to_str;
	std::string to_ip_value = "";
	bool b_ip = RedisMgr::GetInstance()->Get(to_ip_key, to_ip_value);
	if (!b_ip) {
		return;
	}

	auto& cfg = ConfigMgr::Inst();
	auto self_name = cfg["SelfServer"]["Name"];
	//直接通知对方有认证通过消息
	if (to_ip_value == self_name) {
		auto session = UserMgr::GetInstance()->GetSession(touid);
		if (session) {
			//在内存中则直接发送通知对方
			Json::Value  notify;
			notify["error"] = ErrorCodes::Success;
			notify["fromuid"] = uid;
			notify["touid"] = touid;
			std::string base_key = USER_BASE_INFO + std::to_string(uid);
			auto user_info = std::make_shared<UserInfo>();
			bool b_info = GetBaseInfo(base_key, uid, user_info);
			if (b_info) {
				notify["name"] = user_info->name;
				///notify["nick"] = user_info->nick;
				//notify["icon"] = user_info->icon;
				//notify["sex"] = user_info->sex;
			}
			else {
				notify["error"] = ErrorCodes::UidInvalid;
			}


			std::string return_str = notify.toStyledString();
			session->Send(return_str, ID_NOTIFY_AUTH_FRIEND_REQ);
		}

		return ;
	}


	AuthFriendReq auth_req;
	auth_req.set_fromuid(uid);
	auth_req.set_touid(touid);

	//发送通知
	ChatGrpcClient::GetInstance()->NotifyAuthFriend(to_ip_value, auth_req);
}

void LogicSystem::DealChatTextMsg(std::shared_ptr<CSession> session, const short& msg_id, const string& msg_data) {
	Json::Reader reader;
	Json::Value root;
	reader.parse(msg_data, root);

	auto uid = root["fromuid"].asInt();
	auto touid = root["touid"].asInt();

	const Json::Value  arrays = root["text_array"];

	Json::Value  rtvalue;
	rtvalue["error"] = ErrorCodes::Success;
	rtvalue["text_array"] = arrays;
	rtvalue["fromuid"] = uid;
	rtvalue["touid"] = touid;

	Defer defer([this, &rtvalue, session]() {
		std::string return_str = rtvalue.toStyledString();
		session->Send(return_str, ID_TEXT_CHAT_MSG_RSP);
		});


	//查询redis 查找touid对应的server ip
	auto to_str = std::to_string(touid);
	auto to_ip_key = USERIPPREFIX + to_str;
	std::string to_ip_value = "";
	bool b_ip = RedisMgr::GetInstance()->Get(to_ip_key, to_ip_value);
	if (!b_ip) {
		return;
	}

	auto& cfg = ConfigMgr::Inst();
	auto self_name = cfg["SelfServer"]["Name"];
	//直接通知对方有认证通过消息
	if (to_ip_value == self_name) {
		auto session = UserMgr::GetInstance()->GetSession(touid);
		if (session) {
			//在内存中则直接发送通知对方
			std::string return_str = rtvalue.toStyledString();
			session->Send(return_str, ID_NOTIFY_TEXT_CHAT_MSG_REQ);
		}

		return ;
	}


	TextChatMsgReq text_msg_req;
	text_msg_req.set_fromuid(uid);
	text_msg_req.set_touid(touid);
	for (const auto& txt_obj : arrays) {
		auto content = txt_obj["content"].asString();
		auto msgid = txt_obj["msgid"].asString();
		std::cout << "content is " << content << std::endl;
		std::cout << "msgid is " << msgid << std::endl;
		auto *text_msg = text_msg_req.add_textmsgs();
		text_msg->set_msgid(msgid);
		text_msg->set_msgcontent(content);
	}


	//发送通知 todo...
	ChatGrpcClient::GetInstance()->NotifyTextChatMsg(to_ip_value, text_msg_req, rtvalue);
}



bool LogicSystem::isPureDigit(const std::string& str)
{
	for (char c : str) {
		if (!std::isdigit(c)) {
			return false;
		}
	}
	return true;
}

void LogicSystem::GetUserByUid(std::string uid_str, Json::Value& rtvalue)
{
	rtvalue["error"] = ErrorCodes::Success;

	std::string base_key = USER_BASE_INFO + uid_str;

	//优先查redis中查询用户信息
	std::string info_str = "";
	bool b_base = RedisMgr::GetInstance()->Get(base_key, info_str);
	if (b_base) {
		Json::Reader reader;
		Json::Value root;
		reader.parse(info_str, root);
		auto uid = root["uid"].asInt();
		auto name = root["name"].asString();
		auto pwd = root["pwd"].asString();
		auto email = root["email"].asString();
		//auto nick = root["nick"].asString();
		//auto desc = root["desc"].asString();
		//auto sex = root["sex"].asInt();
		//auto icon = root["icon"].asString();
		std::cout << "user  uid is  " << uid << " name  is "
			<< name << " pwd is " << pwd << " email is " << email << endl;

		rtvalue["uid"] = uid;
		rtvalue["pwd"] = pwd;
		rtvalue["name"] = name;
		rtvalue["email"] = email;
		//rtvalue["nick"] = nick;
		/////rtvalue["desc"] = desc;
		//rtvalue["sex"] = sex;
		//rtvalue["icon"] = icon;
		return;
	}

	auto uid = std::stoi(uid_str);
	//redis中没有则查询mysql
	//查询数据库
	std::shared_ptr<UserInfo> user_info = nullptr;
	user_info = MysqlMgr::GetInstance()->GetUser(uid);
	if (user_info == nullptr) {
		rtvalue["error"] = ErrorCodes::UidInvalid;
		return;
	}

	//将数据库内容写入redis缓存
	Json::Value redis_root;
	redis_root["uid"] = user_info->uid;
	redis_root["pwd"] = user_info->pwd;
	redis_root["name"] = user_info->name;
	redis_root["email"] = user_info->email;
	//redis_root["nick"] = user_info->nick;
	///redis_root["desc"] = user_info->desc;
	//redis_root["sex"] = user_info->sex;
	//redis_root["icon"] = user_info->icon;

	RedisMgr::GetInstance()->Set(base_key, redis_root.toStyledString());

	//返回数据
	rtvalue["uid"] = user_info->uid;
	rtvalue["pwd"] = user_info->pwd;
	rtvalue["name"] = user_info->name;
	rtvalue["email"] = user_info->email;
	//rtvalue["nick"] = user_info->nick;
	//rtvalue["desc"] = user_info->desc;
	//rtvalue["sex"] = user_info->sex;
	//rtvalue["icon"] = user_info->icon;
}

void LogicSystem::GetUserByName(std::string name, Json::Value& rtvalue)
{
	rtvalue["error"] = ErrorCodes::Success;

	std::string base_key = NAME_INFO + name;

	//优先查redis中查询用户信息
	std::string info_str = "";
	bool b_base = RedisMgr::GetInstance()->Get(base_key, info_str);
	if (b_base) {
		Json::Reader reader;
		Json::Value root;
		reader.parse(info_str, root);
		auto uid = root["uid"].asInt();
		auto name = root["name"].asString();
		auto pwd = root["pwd"].asString();
		auto email = root["email"].asString();
		//auto nick = root["nick"].asString();
		//auto desc = root["desc"].asString();
		//auto sex = root["sex"].asInt();
		std::cout << "user  uid is  " << uid << " name  is "
			<< name << " pwd is " << pwd << " email is " << email << endl;

		rtvalue["uid"] = uid;
		rtvalue["pwd"] = pwd;
		rtvalue["name"] = name;
		rtvalue["email"] = email;
		//rtvalue["nick"] = nick;
		//rtvalue["desc"] = desc;
		//rtvalue["sex"] = sex;
		return;
	}

	//redis中没有则查询mysql
	//查询数据库
	std::shared_ptr<UserInfo> user_info = nullptr;
	user_info = MysqlMgr::GetInstance()->GetUser(name);
	if (user_info == nullptr) {
		rtvalue["error"] = ErrorCodes::UidInvalid;
		return;
	}

	//将数据库内容写入redis缓存
	Json::Value redis_root;
	redis_root["uid"] = user_info->uid;
	redis_root["pwd"] = user_info->pwd;
	redis_root["name"] = user_info->name;
	redis_root["email"] = user_info->email;
	//redis_root["nick"] = user_info->nick;
	//redis_root["desc"] = user_info->desc;
	//redis_root["sex"] = user_info->sex;

	RedisMgr::GetInstance()->Set(base_key, redis_root.toStyledString());

	//返回数据
	rtvalue["uid"] = user_info->uid;
	rtvalue["pwd"] = user_info->pwd;
	rtvalue["name"] = user_info->name;
	rtvalue["email"] = user_info->email;
	//rtvalue["nick"] = user_info->nick;
	//rtvalue["desc"] = user_info->desc;
	//rtvalue["sex"] = user_info->sex;
}
bool LogicSystem::GetDoctorInfo(std::string base_key, int uid, std::shared_ptr<DoctorInfo>& doctorinfo) {
	std::string info_str = "";
	bool b_base = RedisMgr::GetInstance()->Get(base_key, info_str);
	if (b_base) {
		Json::Reader reader;
		Json::Value root;
		reader.parse(info_str, root);
		std::cout<<"text before id "<<endl;
		doctorinfo->id=root["id"].asInt();
		std::cout<<"text after id "<< doctorinfo->id<<endl;
		doctorinfo->name=root["name"].asString();
		doctorinfo->pwd=root["pwd"].asString();
		doctorinfo->email=root["email"].asString();
		std::cout<<"text after id "<<endl;
		doctorinfo->sex=root["sex"].asInt();
		std::cout<<"sex "<<doctorinfo->sex<<std::endl;
		doctorinfo->year=root["year"].asString();
		doctorinfo->month=root["month"].asString();
		doctorinfo->day=root["day"].asString();
		doctorinfo->workID=root["workID"].asString();
		std::cout<<"text after id "<<endl;
		doctorinfo->department_id=root["department"].asInt();
		std::cout<<"ddd:"<<doctorinfo->department_id<<std::endl;
		doctorinfo->intr=root["intr"].asString();
		doctorinfo->IDcard=root["IDcard"].asString();
	}
	else {
		//redis中没有则查询mysql
		//查询数据库
		std::shared_ptr<DoctorInfo> doctor_info = nullptr;
		doctor_info = MysqlMgr::GetInstance()->GetDoctor(uid);
		if (doctor_info == nullptr) {
			return false;
		}

		doctorinfo=doctor_info;

		Json::Value redis_root;
		redis_root["id"]=doctor_info->id;
		redis_root["name"]=doctor_info->name;
		redis_root["pwd"]=doctor_info->pwd;
		redis_root["email"]=doctor_info->email;
		redis_root["sex"]=doctorinfo->sex;
		redis_root["year"]=doctorinfo->year;
		redis_root["month"]=doctorinfo->month;
		redis_root["day"]=doctorinfo->day;
		redis_root["workID"]=doctorinfo->workID;
		redis_root["department"]=doctorinfo->department_id;
		redis_root["intr"]=doctorinfo->intr;
		redis_root["IDcard"]=doctorinfo->IDcard;
		RedisMgr::GetInstance()->Set(base_key, redis_root.toStyledString());

	}
	return true;

}
bool LogicSystem::GetBaseInfo(std::string base_key, int uid, std::shared_ptr<UserInfo>& userinfo)
{
	//优先查redis中查询用户信息
	std::string info_str = "";
	bool b_base = RedisMgr::GetInstance()->Get(base_key, info_str);
	if (b_base) {
		Json::Reader reader;
		Json::Value root;
		reader.parse(info_str, root);
		userinfo->uid = root["uid"].asInt();
		userinfo->name = root["name"].asString();
		userinfo->pwd = root["pwd"].asString();
		userinfo->email = root["email"].asString();
		//userinfo->nick = root["nick"].asString();
		//userinfo->desc = root["desc"].asString();
		/////userinfo->sex = root["sex"].asInt();
		//userinfo->icon = root["icon"].asString();
		std::cout << "user login uid is  " << userinfo->uid << " name  is "
			<< userinfo->name << " pwd is " << userinfo->pwd << " email is " << userinfo->email << endl;
	}
	else {
		//redis中没有则查询mysql
		//查询数据库
		std::shared_ptr<UserInfo> user_info = nullptr;
		user_info = MysqlMgr::GetInstance()->GetUser(uid);
		if (user_info == nullptr) {
			return false;
		}

		userinfo = user_info;

		//将数据库内容写入redis缓存
		Json::Value redis_root;
		redis_root["uid"] = uid;
		redis_root["pwd"] = userinfo->pwd;
		redis_root["name"] = userinfo->name;
		redis_root["email"] = userinfo->email;
		//redis_root["nick"] = userinfo->nick;
		//redis_root["desc"] = userinfo->desc;
		//redis_root["sex"] = userinfo->sex;
		//redis_root["icon"] = userinfo->icon;
		RedisMgr::GetInstance()->Set(base_key, redis_root.toStyledString());
	}

	return true;
}

bool LogicSystem::GetFriendApplyInfo(int to_uid, std::vector<std::shared_ptr<ApplyInfo>> &list) {
	//从mysql获取好友申请列表
	return MysqlMgr::GetInstance()->GetApplyList(to_uid, list, 0, 10);
}

bool LogicSystem::GetFriendList(int self_id, std::vector<std::shared_ptr<UserInfo>>& user_list) {
	//从mysql获取好友列表
	return MysqlMgr::GetInstance()->GetFriendList(self_id, user_list);
}