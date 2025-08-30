//
// Created by user on 24-8-17.
//
#include"LogicSystem.h"
#include"HttpConnection.h"
#include"VerifyGrpcClient.h"
#include"RedisMgr.h"
#include"MysqlMgr.h"
#include "StatusGrpcClient.h"

void LogicSystem::RegGet(std::string url, HttpHandler handler) {
    _get_handlers.insert(make_pair(url, handler));
}

void LogicSystem::RegPost(std::string url, HttpHandler handler) {
    _post_handlers.insert(make_pair(url, handler));
}

LogicSystem::LogicSystem() {
    RegGet("/get_test", [](std::shared_ptr<HttpConnection> connection) {
        beast::ostream(connection->_response.body()) << "receive get_test req " << std::endl;
        int i = 0;
        for (auto& elem : connection->_get_params) {
            i++;
            beast::ostream(connection->_response.body()) << "param" << i << " key is " << elem.first;
            beast::ostream(connection->_response.body()) << ", " <<  " value is " << elem.second << std::endl;
        }
    });



    RegPost("/get_varifycode", [](std::shared_ptr<HttpConnection> connection) {
    auto body_str = boost::beast::buffers_to_string(connection->_request.body().data());
    std::cout << "receive body is " << body_str << std::endl;
    connection->_response.set(http::field::content_type, "text/json");
    Json::Value root;
    Json::Reader reader;
    Json::Value src_root;
    bool parse_success = reader.parse(body_str, src_root);
    if (!parse_success) {
        std::cout << "Failed to parse JSON data!" << std::endl;
        root["error"] = ErrorCodes::Error_Json;
        std::string jsonstr = root.toStyledString();
        beast::ostream(connection->_response.body()) << jsonstr;
        return true;
    }


    if(!src_root.isMember("email")) {
        std::cout << "Fail to parse JSON data!!" << std::endl;
        root["error"] = ErrorCodes::Error_Json;
        std::string jsonstr = root.toStyledString();
        beast::ostream(connection->_response.body()) << jsonstr;
        return true;
    }

        auto email = src_root["email"].asString();
        GetVarifyRsp rsp = VerifyGrpcClient::GetInstance()->GetVarifyCode(email);
        std::cout << "email is " << email << std::endl;
        root["error"] = rsp.error();
        root["email"] = src_root["email"];
        std::string jsonstr = root.toStyledString();
        beast::ostream(connection->_response.body()) << jsonstr;
        return true;
});

	//医生注册逻辑
	RegPost("/doctor_register", [](std::shared_ptr<HttpConnection> connection) {
		auto body_str = boost::beast::buffers_to_string(connection->_request.body().data());
		std::cout << "receive body is " << body_str << std::endl;
		connection->_response.set(http::field::content_type, "text/json");
		Json::Value root;
		Json::Reader reader;
		Json::Value src_root;
		bool parse_success = reader.parse(body_str, src_root);
		if (!parse_success) {
			std::cout << "Failed to parse JSON data!" << std::endl;
			root["error"] = ErrorCodes::Error_Json;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return true;
		}

		auto email = src_root["email"].asString();
		auto workID = src_root["user"].asString();
		auto pwd = src_root["passwd"].asString();
		auto confirm = src_root["confirm"].asString();
		//auto icon = src_root["icon"].asString();
		//先查找redis中email对应的验证码是否合理
		std::string  varify_code;
		bool b_get_varify = RedisMgr::GetInstance()->Get(CODEPREFIX+src_root["email"].asString(), varify_code);
		if (!b_get_varify) {
			std::cout << " get varify code expired" << std::endl;
			root["error"] = ErrorCodes::VarifyExpired;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return true;
		}

		if (varify_code != src_root["varifycode"].asString()) {
			std::cout << " varify code error" << std::endl;
			root["error"] = ErrorCodes::VarifyCodeErr;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return true;
		}

		int result=MysqlMgr::GetInstance()->RegDoctor(workID,email,pwd);
		if (result == 0 || result == -1) {
			std::cout << " user or email exist" << std::endl;
			root["error"] = ErrorCodes::UserExist;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return true;
		}
		//std::string uuid=std::to_string(uid);
		root["error"] = 0;
		root["workID"] = workID;
		root["email"] = email;
		//root ["user"]= name;
		root["passwd"] = pwd;
		root["confirm"] = confirm;
		root["varifycode"] = src_root["varifycode"].asString();
		std::string jsonstr = root.toStyledString();
		beast::ostream(connection->_response.body()) << jsonstr;
		return true;



	});

    	//day11 注册用户逻辑
	RegPost("/user_register", [](std::shared_ptr<HttpConnection> connection) {
		auto body_str = boost::beast::buffers_to_string(connection->_request.body().data());
		std::cout << "receive body is " << body_str << std::endl;
		connection->_response.set(http::field::content_type, "text/json");
		Json::Value root;
		Json::Reader reader;
		Json::Value src_root;
		bool parse_success = reader.parse(body_str, src_root);
		if (!parse_success) {
			std::cout << "Failed to parse JSON data!" << std::endl;
			root["error"] = ErrorCodes::Error_Json;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return true;
		}

		auto email = src_root["email"].asString();
		auto name = src_root["user"].asString();
		auto pwd = src_root["passwd"].asString();
		auto confirm = src_root["confirm"].asString();
		//auto icon = src_root["icon"].asString();


		if (pwd != confirm) {
			std::cout << "password err " << std::endl;
			root["error"] = ErrorCodes::PasswdErr;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return true;
		}

		//先查找redis中email对应的验证码是否合理
		std::string  varify_code;
		bool b_get_varify = RedisMgr::GetInstance()->Get(CODEPREFIX+src_root["email"].asString(), varify_code);
		if (!b_get_varify) {
			std::cout << " get varify code expired" << std::endl;
			root["error"] = ErrorCodes::VarifyExpired;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return true;
		}

		if (varify_code != src_root["varifycode"].asString()) {
			std::cout << " varify code error" << std::endl;
			root["error"] = ErrorCodes::VarifyCodeErr;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return true;
		}

		//查找数据库判断用户是否存在
		int uid = MysqlMgr::GetInstance()->RegUser(name, email, pwd);
		if (uid == 0 || uid == -1) {
			std::cout << " user or email exist" << std::endl;
			root["error"] = ErrorCodes::UserExist;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return true;
		}
		std::string uuid=std::to_string(uid);
		root["error"] = 0;
		root["uid"] = uuid;
		root["email"] = email;
		root ["user"]= name;
		root["passwd"] = pwd;
		root["confirm"] = confirm;
		//root["icon"] = icon;
		root["varifycode"] = src_root["varifycode"].asString();
		std::string jsonstr = root.toStyledString();
		beast::ostream(connection->_response.body()) << jsonstr;
		return true;
		});





	RegPost("/doctor_addInfo", [](std::shared_ptr<HttpConnection> connection) {
		auto body_str = boost::beast::buffers_to_string(connection->_request.body().data());
	std::cout << "receive body is " << body_str << std::endl;
	connection->_response.set(http::field::content_type, "text/json");
	Json::Value root;
	Json::Reader reader;
	Json::Value src_root;
	bool parse_success = reader.parse(body_str, src_root);
	if (!parse_success) {
		std::cout << "Failed to parse JSON data!" << std::endl;
		root["error"] = ErrorCodes::Error_Json;
		std::string jsonstr = root.toStyledString();
		beast::ostream(connection->_response.body()) << jsonstr;
		return true;
	}
		auto workID = src_root["workID"].asString();
		//std::cout<<"uid is "<<uid<<std::endl;
		auto name = src_root["name"].asString();
		auto lsex=src_root["sex"].asString();
		auto year = src_root["year"].asString();
		auto month = src_root["month"].asString();
		auto data = src_root["data"].asString();
		auto IDcard = src_root["IDcard"].asString();
		auto phone = src_root["phone"].asString();
		auto department = src_root["department"].asString();
		auto intr=src_root["intr"].asString();
		int sex=std::stoi(lsex);
		int department_ID;
		if(department=="儿科") {
			department_ID=1;
		}else if(department=="内科") {
			department_ID=2;
		}else if(department=="外科") {
			department_ID=3;
		}
		else if(department=="妇科") {
			department_ID=4;
		}else if(department=="皮肤科") {
			department_ID=5;
		}
		bool doctorUpdateCheck=MysqlMgr::GetInstance()->UpdateDoctorDetails(workID,name,sex,year,month,data,IDcard,phone,department_ID,intr);
		if(!doctorUpdateCheck) {
			std::cout << " doctor info updata in reg failed" << std::endl;
			root["error"] = ErrorCodes::UPDATA_USER_INFO_IN_REG_FAIL;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return true;
		}

		std::cout << " doctor info updata in reg success" << std::endl;
		root["error"] = 0;
		root["workID"] = workID;
		root["name"] = name;
		std::string jsonstr = root.toStyledString();
		beast::ostream(connection->_response.body()) << jsonstr;
		return true;


	});

	RegPost("/user_addInfo", [](std::shared_ptr<HttpConnection> connection) {
		auto body_str = boost::beast::buffers_to_string(connection->_request.body().data());
	std::cout << "receive body is " << body_str << std::endl;
	connection->_response.set(http::field::content_type, "text/json");
	Json::Value root;
	Json::Reader reader;
	Json::Value src_root;
	bool parse_success = reader.parse(body_str, src_root);
	if (!parse_success) {
		std::cout << "Failed to parse JSON data!" << std::endl;
		root["error"] = ErrorCodes::Error_Json;
		std::string jsonstr = root.toStyledString();
		beast::ostream(connection->_response.body()) << jsonstr;
		return true;
	}
		auto uid = src_root["uid"].asString();
		std::cout<<"uid is "<<uid<<std::endl;
		auto name = src_root["name"].asString();
		auto sex=src_root["sex"].asString();
		auto year = src_root["year"].asString();
		auto month = src_root["month"].asString();
		auto data = src_root["data"].asString();
		auto IDcard = src_root["IDcard"].asString();
		auto phone = src_root["phone"].asString();
		int uuid=std::stoi(uid);
		int ssex=std::stoi(sex);
		bool user_info_check=MysqlMgr::GetInstance()->UpdateUserDetails(uuid,name,ssex,year,month,data,IDcard,phone);
		if(!user_info_check) {
			std::cout << " user info updata in reg failed" << std::endl;
			root["error"] = ErrorCodes::UPDATA_USER_INFO_IN_REG_FAIL;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return true;
		}

		std::cout << " user info updata in reg success" << std::endl;
		root["error"] = 0;
		root["uid"] = uid;
		root["name"] = name;
		std::string jsonstr = root.toStyledString();
		beast::ostream(connection->_response.body()) << jsonstr;
		return true;

	});


	RegPost("/doctor_reset_pwd", [](std::shared_ptr<HttpConnection> connection) {
		auto body_str = boost::beast::buffers_to_string(connection->_request.body().data());
	std::cout << "receive body is " << body_str << std::endl;
	connection->_response.set(http::field::content_type, "text/json");
	Json::Value root;
	Json::Reader reader;
	Json::Value src_root;
	bool parse_success = reader.parse(body_str, src_root);
	if (!parse_success) {
		std::cout << "Failed to parse JSON data!" << std::endl;
		root["error"] = ErrorCodes::Error_Json;
		std::string jsonstr = root.toStyledString();
		beast::ostream(connection->_response.body()) << jsonstr;
		return true;
	}
		auto email = src_root["email"].asString();
	auto workID = src_root["workID"].asString();
	auto pwd = src_root["passwd"].asString();
		//先查找redis中email对应的验证码是否合理
		std::string  varify_code;
		bool b_get_varify = RedisMgr::GetInstance()->Get(CODEPREFIX + src_root["email"].asString(), varify_code);
		if (!b_get_varify) {
			std::cout << " get varify code expired" << std::endl;
			root["error"] = ErrorCodes::VarifyExpired;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return true;
		}

		if (varify_code != src_root["varifycode"].asString()) {
			std::cout << " varify code error" << std::endl;
			root["error"] = ErrorCodes::VarifyCodeErr;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return true;
		}

		bool email_valid = MysqlMgr::GetInstance()->CheckDoctorEmail(workID, email);
		if (!email_valid) {
		std::cout << " doctor email not match" << std::endl;
		root["error"] = ErrorCodes::EmailNotMatch;
		std::string jsonstr = root.toStyledString();
		beast::ostream(connection->_response.body()) << jsonstr;
		return true;
	}

		bool b_up = MysqlMgr::GetInstance()->UpdateDoctorPwd(workID, pwd);
	if (!b_up) {
		std::cout << " doupdate pwd failed" << std::endl;
		root["error"] = ErrorCodes::PasswdUpFailed;
		std::string jsonstr = root.toStyledString();
		beast::ostream(connection->_response.body()) << jsonstr;
		return true;
	}

	std::cout << "do succeed to update password" << pwd << std::endl;









		root["error"] = 0;
	root["email"] = email;
	root["workID"] = workID;
	root["passwd"] = pwd;
	root["varifycode"] = src_root["varifycode"].asString();
	std::string jsonstr = root.toStyledString();
	beast::ostream(connection->_response.body()) << jsonstr;
	return true;



	});
	//重置回调逻辑
	RegPost("/reset_pwd", [](std::shared_ptr<HttpConnection> connection) {
    auto body_str = boost::beast::buffers_to_string(connection->_request.body().data());
    std::cout << "receive body is " << body_str << std::endl;
    connection->_response.set(http::field::content_type, "text/json");
    Json::Value root;
    Json::Reader reader;
    Json::Value src_root;
    bool parse_success = reader.parse(body_str, src_root);
    if (!parse_success) {
        std::cout << "Failed to parse JSON data!" << std::endl;
        root["error"] = ErrorCodes::Error_Json;
        std::string jsonstr = root.toStyledString();
        beast::ostream(connection->_response.body()) << jsonstr;
        return true;
    }

    auto email = src_root["email"].asString();
    auto name = src_root["user"].asString();
    auto pwd = src_root["passwd"].asString();

    //先查找redis中email对应的验证码是否合理
    std::string  varify_code;
    bool b_get_varify = RedisMgr::GetInstance()->Get(CODEPREFIX + src_root["email"].asString(), varify_code);
    if (!b_get_varify) {
        std::cout << " get varify code expired" << std::endl;
        root["error"] = ErrorCodes::VarifyExpired;
        std::string jsonstr = root.toStyledString();
        beast::ostream(connection->_response.body()) << jsonstr;
        return true;
    }

    if (varify_code != src_root["varifycode"].asString()) {
        std::cout << " varify code error" << std::endl;
        root["error"] = ErrorCodes::VarifyCodeErr;
        std::string jsonstr = root.toStyledString();
        beast::ostream(connection->_response.body()) << jsonstr;
        return true;
    }
    //查询数据库判断用户名和邮箱是否匹配
    bool email_valid = MysqlMgr::GetInstance()->CheckEmail(name, email);
    if (!email_valid) {
        std::cout << " user email not match" << std::endl;
        root["error"] = ErrorCodes::EmailNotMatch;
        std::string jsonstr = root.toStyledString();
        beast::ostream(connection->_response.body()) << jsonstr;
        return true;
    }

    //更新密码为最新密码
    bool b_up = MysqlMgr::GetInstance()->UpdatePwd(name, pwd);
    if (!b_up) {
        std::cout << " update pwd failed" << std::endl;
        root["error"] = ErrorCodes::PasswdUpFailed;
        std::string jsonstr = root.toStyledString();
        beast::ostream(connection->_response.body()) << jsonstr;
        return true;
    }

    std::cout << "succeed to update password" << pwd << std::endl;
    root["error"] = 0;
    root["email"] = email;
    root["user"] = name;
    root["passwd"] = pwd;
    root["varifycode"] = src_root["varifycode"].asString();
    std::string jsonstr = root.toStyledString();
    beast::ostream(connection->_response.body()) << jsonstr;
    return true;
    });

	RegPost("/doctor_login", [](std::shared_ptr<HttpConnection> connection) {
		auto body_str = boost::beast::buffers_to_string(connection->_request.body().data());
		std::cout << "receive body is " << body_str << std::endl;
		connection->_response.set(http::field::content_type, "text/json");
		Json::Value root;
		Json::Reader reader;
		Json::Value src_root;
		std::cout<<"1"<<std::endl;
		//查询数据库
		bool parse_success = reader.parse(body_str, src_root);
		if (!parse_success) {
			std::cout << "Failed to parse JSON data!" << std::endl;
			root["error"] = ErrorCodes::Error_Json;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return true;
		}

		auto workID= src_root["workID"].asString();
		std::cout<<"workID is:"<<workID<<std::endl;
		auto pwd = src_root["passwd"].asString();
		DoctorInfo doctor_info;
		bool doctor_pwd_check=MysqlMgr::GetInstance()->CheckDoctorPwd(workID,pwd,doctor_info);
		if (!doctor_pwd_check) {
			std::cout << " doctor pwd not match" << std::endl;
			root["error"] = ErrorCodes::PasswdInvalid;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return true;
		}

		auto reply = StatusGrpcClient::GetInstance()->GetChatServer(doctor_info.id);
		if (reply.error()) {
			std::cout << " grpc get chat server failed, error is " << reply.error()<< std::endl;
			root["error"] = ErrorCodes::RPCFailed;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return true;
		}
		std::cout << "succeed to load userinfo uid is " << doctor_info.id << std::endl;
		root["error"] = 0;
		root["workID"] = workID;
		root["ID"]=doctor_info.id;
		root["token"] = reply.token();
		root["host"] = reply.host();
		root["port"] = reply.port();
		std::string jsonstr = root.toStyledString();
		beast::ostream(connection->_response.body()) << jsonstr;
		return true;




	});

	//用户登录逻辑
	RegPost("/user_login", [](std::shared_ptr<HttpConnection> connection) {
		auto body_str = boost::beast::buffers_to_string(connection->_request.body().data());
		std::cout << "receive body is " << body_str << std::endl;
		connection->_response.set(http::field::content_type, "text/json");
		Json::Value root;
		Json::Reader reader;
		Json::Value src_root;
		//查询数据库
		bool parse_success = reader.parse(body_str, src_root);
		if (!parse_success) {
			std::cout << "Failed to parse JSON data!" << std::endl;
			root["error"] = ErrorCodes::Error_Json;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return true;
		}

		auto email = src_root["email"].asString();
		auto pwd = src_root["passwd"].asString();
		UserInfo userInfo;
		//查询数据库判断用户名和密码是否匹配
		bool pwd_valid = MysqlMgr::GetInstance()->CheckPwd(email, pwd, userInfo);
		if (!pwd_valid) {
			std::cout << " user pwd not match" << std::endl;
			root["error"] = ErrorCodes::PasswdInvalid;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return true;
		}

		//查询StatusServer找到合适的连接
		auto reply = StatusGrpcClient::GetInstance()->GetChatServer(userInfo.uid);
		if (reply.error()) {
			std::cout << " grpc get chat server failed, error is " << reply.error()<< std::endl;
			root["error"] = ErrorCodes::RPCFailed;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return true;
		}

		std::cout << "succeed to load userinfo uid is " << userInfo.uid << std::endl;
		root["error"] = 0;
		root["email"] = email;
		root["uid"] = userInfo.uid;
		root["token"] = reply.token();
		root["host"] = reply.host();
		root["port"] = reply.port();
		std::string jsonstr = root.toStyledString();
		beast::ostream(connection->_response.body()) << jsonstr;
		return true;
		});


}

bool LogicSystem::HandleGet(std::string path, std::shared_ptr<HttpConnection> con) {
    if (_get_handlers.find(path) == _get_handlers.end()) {
        return false;
    }

    _get_handlers[path](con);
    return true;
}

bool LogicSystem::HandlePost(std::string path, std::shared_ptr<HttpConnection> con) {
    if (_post_handlers.find(path) == _post_handlers.end()) {
        return false;
    }

    _post_handlers[path](con);
    return true;
}

LogicSystem::~LogicSystem() {
    // 可以为空，或者包含任何需要的清理代码
}
