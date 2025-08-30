//
// Created by user on 24-8-23.
//

#include "MysqlDao.h"
#include "ConfigMgr.h"
#include <json/json.h>


MysqlDao::MysqlDao()
{
	auto & cfg = ConfigMgr::Inst();
	const auto& host = cfg["Mysql"]["Host"];
	const auto& port = cfg["Mysql"]["Port"];
	const auto& pwd = cfg["Mysql"]["Passwd"];
	const auto& schema = cfg["Mysql"]["Schema"];
	const auto& user = cfg["Mysql"]["User"];
	pool_.reset(new MySqlPool(host+":"+port, user, pwd,schema, 5));
}

MysqlDao::~MysqlDao(){
	pool_->Close();
}

bool MysqlDao::GetUserInfo(int uid, UserInfo& userInfo) {
	auto con = pool_->getConnection();
	if (con == nullptr) {
		return false;
	}

	Defer defer([this, &con]() {
		pool_->returnConnection(std::move(con));
	});

	try {
		std::unique_ptr<sql::PreparedStatement> pstmt(con->_con->prepareStatement(
			"SELECT id, uid, name, email, pwd, realName, sex, year, month, data, IDcard, phone "
			"FROM user WHERE uid = ?"));

		pstmt->setInt(1, uid);

		std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

		if (res->next()) {
			userInfo.id = res->getInt("id");
			userInfo.uid = res->getInt("uid");
			userInfo.name = res->getString("name");
			userInfo.email = res->getString("email");
			userInfo.pwd = res->getString("pwd");
			userInfo.realName = res->getString("realName");
			userInfo.sex = res->getInt("sex");
			userInfo.year = res->getString("year");
			userInfo.month = res->getString("month");
			userInfo.data = res->getString("data");
			userInfo.IDcard = res->getString("IDcard");
			userInfo.phone = res->getString("phone");
			return true;
		} else {
			return false;  // 没有找到对应 uid 的记录
		}
	} catch (sql::SQLException& e) {
		std::cerr << "SQLException: " << e.what();
		std::cerr << " (MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		return false;
	}
}


int MysqlDao::RegUser(const std::string& name, const std::string& email, const std::string& pwd)
{
	auto con = pool_->getConnection();
	try {
		if (con == nullptr) {
			return false;
		}
		// 准备调用存储过程
		std::unique_ptr < sql::PreparedStatement > stmt(con->_con->prepareStatement("CALL reg_user(?,?,?,@result)"));
		// 设置输入参数
		stmt->setString(1, name);
		stmt->setString(2, email);
		stmt->setString(3, pwd);

		// 由于PreparedStatement不直接支持注册输出参数，我们需要使用会话变量或其他方法来获取输出参数的值

		  // 执行存储过程
		stmt->execute();
		// 如果存储过程设置了会话变量或有其他方式获取输出参数的值，你可以在这里执行SELECT查询来获取它们
	   // 例如，如果存储过程设置了一个会话变量@result来存储输出结果，可以这样获取：
	   std::unique_ptr<sql::Statement> stmtResult(con->_con->createStatement());
	  std::unique_ptr<sql::ResultSet> res(stmtResult->executeQuery("SELECT @result AS result"));
	  if (res->next()) {
	       int result = res->getInt("result");
	      std::cout << "Result: " << result << std::endl;
		  pool_->returnConnection(std::move(con));
		  return result;
	  }
	  pool_->returnConnection(std::move(con));
		return -1;
	}
	catch (sql::SQLException& e) {
		pool_->returnConnection(std::move(con));
		std::cerr << "SQLException: " << e.what();
		std::cerr << " (MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		return -1;
	}
}

bool MysqlDao::GetHospitalizationInfo(int doctor_uid, std::vector<HosInfobase>& hospitalList) {
	auto con = pool_->getConnection();
	if (con == nullptr) {
		return false;
	}

	Defer defer([this, &con]() {
		pool_->returnConnection(std::move(con));
	});

	try {
		std::unique_ptr<sql::PreparedStatement> pstmt(con->_con->prepareStatement(
			"SELECT patient_uid, patient_name, roomnum, bed_number, admission_data "
			"FROM Hospitalization WHERE doctor_uid = ?"));

		pstmt->setInt(1, doctor_uid);

		std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

		while (res->next()) {
			HosInfobase hosInfo;
			hosInfo.patient_uid = res->getInt("patient_uid");
			hosInfo.patient_name = res->getString("patient_name");
			hosInfo.roomnum = res->getString("roomnum");
			hosInfo.bed_number = res->getString("bed_number");
			hosInfo.admission_data = res->getString("admission_data");
			hospitalList.push_back(hosInfo);
		}
		return true;
	} catch (sql::SQLException& e) {
		std::cerr << "SQLException: " << e.what();
		std::cerr << " (MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		return false;
	}
}

bool MysqlDao::UserGetHospitalizationInfo(int uid, std::vector<std::shared_ptr<HospitalizationInfo>>& hospitalizationList) {
	auto con = pool_->getConnection();
	if (con == nullptr) {
		return false;
	}

	Defer defer([this, &con]() {
		pool_->returnConnection(std::move(con));
	});

	try {
		std::unique_ptr<sql::PreparedStatement> pstmt(con->_con->prepareStatement(
			"SELECT id, doctor_uid, patient_uid, patient_name, bed_number, admission_data, doctorname, roomnum "
			"FROM Hospitalization WHERE patient_uid = ?"));

		pstmt->setInt(1, uid);

		std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

		while (res->next()) {
			auto hospitalizationInfo = std::make_shared<HospitalizationInfo>();
			hospitalizationInfo->id = res->getInt("id");
			hospitalizationInfo->doctor_uid = res->getInt("doctor_uid");
			hospitalizationInfo->patient_uid = res->getInt("patient_uid");
			hospitalizationInfo->patient_name = res->getString("patient_name");
			hospitalizationInfo->bed_number = res->getString("bed_number");
			hospitalizationInfo->admission_data = res->getString("admission_data");
			hospitalizationInfo->doctorname = res->getString("doctorname");
			hospitalizationInfo->roomnum = res->getString("roomnum");

			hospitalizationList.push_back(hospitalizationInfo);
		}

		return true;
	} catch (sql::SQLException& e) {
		std::cerr << "SQLException: " << e.what();
		std::cerr << " (MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		return false;
	}
}


bool MysqlDao::GetGuahaoInfo(int useruid, std::vector<std::shared_ptr<GuahaoInfo>>& guahaoList) {
	auto con = pool_->getConnection();
	if (con == nullptr) {
		return false;
	}

	Defer defer([this, &con]() {
		pool_->returnConnection(std::move(con));
	});

	try {
		std::unique_ptr<sql::PreparedStatement> pstmt(con->_con->prepareStatement(
			"SELECT id, doctoruid, useruid, doctorname, username, useremail, usersex, userage, userorderdata, "
			"userinfo, checkresult, chufang "
			"FROM guahao WHERE useruid = ?"));

		pstmt->setInt(1, useruid);

		std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

		while (res->next()) {
			auto guahaoInfo = std::make_shared<GuahaoInfo>();
			guahaoInfo->id = res->getInt("id");
			guahaoInfo->doctoruid = res->getInt("doctoruid");
			guahaoInfo->useruid = res->getInt("useruid");
			guahaoInfo->doctorname = res->getString("doctorname");
			guahaoInfo->username = res->getString("username");
			guahaoInfo->useremail = res->getString("useremail");
			guahaoInfo->usersex = res->getInt("usersex");
			guahaoInfo->userage = res->getString("userage");
			guahaoInfo->userorderdata = res->getString("userorderdata");
			guahaoInfo->userinfo = res->getString("userinfo");
			guahaoInfo->checkresult = res->getString("checkresult");
			guahaoInfo->chufang = res->getString("chufang");

			guahaoList.push_back(guahaoInfo);
		}

		return true;
	} catch (sql::SQLException& e) {
		std::cerr << "SQLException: " << e.what();
		std::cerr << " (MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		return false;
	}
}



bool MysqlDao::GetDoctorInfoByDepartment(std::shared_ptr<DepartmentInfo> pediatrics,
                                         std::shared_ptr<DepartmentInfo> internalMedicine,
                                         std::shared_ptr<DepartmentInfo> surgery,
                                         std::shared_ptr<DepartmentInfo> gynecology,
                                         std::shared_ptr<DepartmentInfo> dermatology) {
    auto con = pool_->getConnection();
    if (con == nullptr) {
        return false;
    }

    Defer defer([this, &con]() {
        pool_->returnConnection(std::move(con));
    });

    try {
        // 执行查询，获取医生和对应科室的所有信息
        std::unique_ptr<sql::PreparedStatement> pstmt(con->_con->prepareStatement(
            "SELECT d.ID, d.workID, d.name, d.pwd, d.email, d.sex, d.year, d.month, d.day, "
            "d.IDcard, d.phone, d.department_id, d.intr, dep.department_id "
            "FROM doctors d "
            "JOIN departments dep ON d.department_id = dep.department_id "
            "WHERE dep.name IN ('儿科', '内科', '外科', '妇科', '皮肤科')"));  // 只选择五个指定科室

        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        while (res->next()) {
            auto doctor = std::make_shared<DoctorDetails>();
            doctor->id = res->getInt("ID");
            doctor->workID = res->getInt("workID");
            doctor->name = res->getString("name");
            doctor->pwd = res->getString("pwd");
            doctor->email = res->getString("email");
            doctor->sex = res->getInt("sex");
            doctor->year = res->getInt("year");
            doctor->month = res->getInt("month");
            doctor->day = res->getInt("day");
            doctor->IDcard = res->getString("IDcard");
            doctor->phone = res->getString("phone");
            doctor->department_id = res->getInt("department_id");
            doctor->intr = res->getString("intr");

            int department_id = res->getInt("department_id");

            // 根据department_id将医生信息添加到对应的科室
            switch (department_id) {
                case 1:  // 儿科
                    pediatrics->doctors.push_back(doctor);
                    break;
                case 2:  // 内科
                    internalMedicine->doctors.push_back(doctor);
                    break;
                case 3:  // 外科
                    surgery->doctors.push_back(doctor);
                    break;
                case 4:  // 妇科
                    gynecology->doctors.push_back(doctor);
                    break;
                case 5:  // 皮肤科
                    dermatology->doctors.push_back(doctor);
                    break;
                default:
                    break;
            }
        }

        return true;
    } catch (sql::SQLException& e) {
        std::cerr << "SQLException: " << e.what();
        std::cerr << " (MySQL error code: " << e.getErrorCode();
        std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
        return false;
    }
}




bool MysqlDao::CheckEmail(const std::string& name, const std::string& email) {
	auto con = pool_->getConnection();
	try {
		if (con == nullptr) {
			return false;
		}

		// 准备查询语句
		std::unique_ptr<sql::PreparedStatement> pstmt(con->_con->prepareStatement("SELECT email FROM user WHERE name = ?"));

		// 绑定参数
		pstmt->setString(1, name);

		// 执行查询
		std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

		// 遍历结果集
		while (res->next()) {
			std::cout << "Check Email: " << res->getString("email") << std::endl;
			if (email != res->getString("email")) {
				pool_->returnConnection(std::move(con));
				return false;
			}
			pool_->returnConnection(std::move(con));
			return true;
		}
		return true;
	}
	catch (sql::SQLException& e) {
		pool_->returnConnection(std::move(con));
		std::cerr << "SQLException: " << e.what();
		std::cerr << " (MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		return false;
	}
}

bool MysqlDao::UpdatePwd(const std::string& name, const std::string& newpwd) {
	auto con = pool_->getConnection();
	try {
		if (con == nullptr) {
			return false;
		}

		// 准备查询语句
		std::unique_ptr<sql::PreparedStatement> pstmt(con->_con->prepareStatement("UPDATE user SET pwd = ? WHERE name = ?"));

		// 绑定参数
		pstmt->setString(2, name);
		pstmt->setString(1, newpwd);

		// 执行更新
		int updateCount = pstmt->executeUpdate();

		std::cout << "Updated rows: " << updateCount << std::endl;
		pool_->returnConnection(std::move(con));
		return true;
	}
	catch (sql::SQLException& e) {
		pool_->returnConnection(std::move(con));
		std::cerr << "SQLException: " << e.what();
		std::cerr << " (MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		return false;
	}
}

bool MysqlDao::CheckPwd(const std::string& name, const std::string& pwd, UserInfo& userInfo) {
	auto con = pool_->getConnection();
	if (con == nullptr) {
		return false;
	}

	Defer defer([this, &con]() {
		pool_->returnConnection(std::move(con));
		});

	try {
		// 准备SQL语句
		std::unique_ptr<sql::PreparedStatement> pstmt(con->_con->prepareStatement("SELECT * FROM user WHERE name = ?"));
		pstmt->setString(1, name); // 将username替换为你要查询的用户名

		// 执行查询
		std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
		std::string origin_pwd = "";
		// 遍历结果集
		while (res->next()) {
			origin_pwd = res->getString("pwd");
			// 输出查询到的密码
			std::cout << "Password: " << origin_pwd << std::endl;
			break;
		}

		if (pwd != origin_pwd) {
			return false;
		}
		userInfo.name = name;
		userInfo.email = res->getString("email");
		userInfo.uid = res->getInt("uid");
		userInfo.pwd = origin_pwd;
		return true;
	}
	catch (sql::SQLException& e) {
		std::cerr << "SQLException: " << e.what();
		std::cerr << " (MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		return false;
	}
}

bool MysqlDao::AddFriendApply(const int& from, const int& to)
{
	auto con = pool_->getConnection();
	if (con == nullptr) {
		return false;
	}

	Defer defer([this, &con]() {
		pool_->returnConnection(std::move(con));
		});

	try {
		// 准备SQL语句
		std::unique_ptr<sql::PreparedStatement> pstmt(con->_con->prepareStatement("INSERT INTO friend_apply (from_uid, to_uid) values (?,?) "
			"ON DUPLICATE KEY UPDATE from_uid = from_uid, to_uid = to_uid"));
		pstmt->setInt(1, from); // from id
		pstmt->setInt(2, to);
		// 执行更新
		int rowAffected = pstmt->executeUpdate();
		if (rowAffected < 0) {
			return false;
		}
		return true;
	}
	catch (sql::SQLException& e) {
		std::cerr << "SQLException: " << e.what();
		std::cerr << " (MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		return false;
	}


	return true;
}

bool MysqlDao::AuthFriendApply(const int& from, const int& to) {
	auto con = pool_->getConnection();
	if (con == nullptr) {
		return false;
	}

	Defer defer([this, &con]() {
		pool_->returnConnection(std::move(con));
		});

	try {
		// 准备SQL语句
		std::unique_ptr<sql::PreparedStatement> pstmt(con->_con->prepareStatement("UPDATE friend_apply SET status = 1 "
			"WHERE from_uid = ? AND to_uid = ?"));
		//反过来的申请时from，验证时to
		pstmt->setInt(1, to); // from id
		pstmt->setInt(2, from);
		// 执行更新
		int rowAffected = pstmt->executeUpdate();
		if (rowAffected < 0) {
			return false;
		}
		return true;
	}
	catch (sql::SQLException& e) {
		std::cerr << "SQLException: " << e.what();
		std::cerr << " (MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		return false;
	}


	return true;
}

bool MysqlDao::AddFriend(const int& from, const int& to, std::string back_name) {
	auto con = pool_->getConnection();
	if (con == nullptr) {
		return false;
	}

	Defer defer([this, &con]() {
		pool_->returnConnection(std::move(con));
		});

	try {

		//开始事务
		con->_con->setAutoCommit(false);

		// 准备第一个SQL语句, 插入认证方好友数据
		std::unique_ptr<sql::PreparedStatement> pstmt(con->_con->prepareStatement("INSERT IGNORE INTO friend(self_id, friend_id, back) "
			"VALUES (?, ?, ?) "
			));
		//反过来的申请时from，验证时to
		pstmt->setInt(1, from); // from id
		pstmt->setInt(2, to);
		pstmt->setString(3, back_name);
		// 执行更新
		int rowAffected = pstmt->executeUpdate();
		if (rowAffected < 0) {
			con->_con->rollback();
			return false;
		}

		//准备第二个SQL语句，插入申请方好友数据
		std::unique_ptr<sql::PreparedStatement> pstmt2(con->_con->prepareStatement("INSERT IGNORE INTO friend(self_id, friend_id, back) "
			"VALUES (?, ?, ?) "
		));
		//反过来的申请时from，验证时to
		pstmt2->setInt(1, to); // from id
		pstmt2->setInt(2, from);
		pstmt2->setString(3, "");
		// 执行更新
		int rowAffected2 = pstmt2->executeUpdate();
		if (rowAffected2 < 0) {
			con->_con->rollback();
			return false;
		}

		// 提交事务
		con->_con->commit();
		std::cout << "addfriend insert friends success" << std::endl;

		return true;
	}
	catch (sql::SQLException& e) {
		// 如果发生错误，回滚事务
		if (con) {
			con->_con->rollback();
		}
		std::cerr << "SQLException: " << e.what();
		std::cerr << " (MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		return false;
	}


	return true;
}

bool MysqlDao::UpdateDoctorInfo(int id, const std::string& name, const std::string& email, const std::string& department, const std::string& intr, const std::shared_ptr<int>& departid) {
	auto con = pool_->getConnection();
	if (con == nullptr) {
		return true;  // 返回 true，因为这是默认值
	}

	Defer defer([this, &con]() {
		pool_->returnConnection(std::move(con));
	});

	try {
		// 首先通过 department 名称查找对应的 department_id
		std::unique_ptr<sql::PreparedStatement> pstmtDept(con->_con->prepareStatement("SELECT department_id FROM departments WHERE name = ?"));
		pstmtDept->setString(1, department);
		std::unique_ptr<sql::ResultSet> resDept(pstmtDept->executeQuery());

		int department_id = -1;
		if (resDept->next()) {
			department_id = resDept->getInt("department_id");
			if (departid) {
				*departid = department_id; // 修改 departid 所指向的 int 值
			}
		} else {
			std::cerr << "Department not found: " << department << std::endl;
			return true;  // 如果找不到 department，仍然返回 true
		}

		// 准备更新 doctors 表的 SQL 语句
		std::unique_ptr<sql::PreparedStatement> pstmt(con->_con->prepareStatement(
			"UPDATE doctors SET name = ?, email = ?, department_id = ?, intr = ? WHERE id = ?"));

		// 绑定参数
		pstmt->setString(1, name);
		pstmt->setString(2, email);
		pstmt->setInt(3, department_id);
		pstmt->setString(4, intr);
		pstmt->setInt(5, id);

		// 执行更新
		int updateCount = pstmt->executeUpdate();

		std::cout << "Updated rows: " << updateCount << std::endl;
		// 无论更新多少行，都返回 true，因为这是默认值
		return true;
	} catch (sql::SQLException& e) {
		std::cerr << "SQLException: " << e.what();
		std::cerr << " (MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		return true;  // 即使捕获到异常，也返回 true
	}
}

bool MysqlDao::UpdateUserInfo(int uid, const std::string& name, const std::string& IDcard, const std::string& phone, const std::string& email) {
	auto con = pool_->getConnection();
	if (con == nullptr) {
		return false;  // 如果无法获取连接，返回 false
	}

	Defer defer([this, &con]() {
		pool_->returnConnection(std::move(con));
	});

	try {
		// 准备更新 user 表的 SQL 语句
		std::unique_ptr<sql::PreparedStatement> pstmt(con->_con->prepareStatement(
			"UPDATE user SET name = ?, IDcard = ?, phone = ?, email = ? WHERE uid = ?"));

		// 绑定参数
		pstmt->setString(1, name);
		pstmt->setString(2, IDcard);
		pstmt->setString(3, phone);
		pstmt->setString(4, email);
		pstmt->setInt(5, uid);

		// 执行更新
		int updateCount = pstmt->executeUpdate();

		std::cout << "Updated rows: " << updateCount << std::endl;

		// 返回 true，表示成功
		return updateCount > 0;
	} catch (sql::SQLException& e) {
		std::cerr << "SQLException: " << e.what();
		std::cerr << " (MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		return false;
	}
}

bool MysqlDao::GetDoctorIdByName(const std::string& doctorName, int& doctoruid) {
	auto con = pool_->getConnection();
	if (con == nullptr) {
		return false;
	}

	Defer defer([this, &con]() {
		pool_->returnConnection(std::move(con));
	});

	try {
		std::unique_ptr<sql::PreparedStatement> pstmt(con->_con->prepareStatement(
			"SELECT ID FROM doctors WHERE name = ?"));
		pstmt->setString(1, doctorName);

		std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
		if (res->next()) {
			doctoruid = res->getInt("ID");
			return true;
		} else {
			return false; // Doctor not found
		}
	} catch (sql::SQLException& e) {
		std::cerr << "SQLException: " << e.what();
		return false;
	}
}


bool MysqlDao::GetUserInfoByUid(int uid, std::string& name, std::string& email, int& sex) {
	auto con = pool_->getConnection();
	if (con == nullptr) {
		return false;
	}

	Defer defer([this, &con]() {
		pool_->returnConnection(std::move(con));
	});

	try {
		std::unique_ptr<sql::PreparedStatement> pstmt(con->_con->prepareStatement(
			"SELECT name, email, sex FROM user WHERE uid = ?"));
		pstmt->setInt(1, uid);

		std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
		if (res->next()) {
			name = res->getString("name");
			email = res->getString("email");
			sex = res->getInt("sex");
			return true;
		} else {
			return false; // User not found
		}
	} catch (sql::SQLException& e) {
		std::cerr << "SQLException: " << e.what();
		return false;
	}
}

bool MysqlDao::InsertGuahaoData(int useruid, int doctoruid, const std::string& doctorName, const std::string& username, const std::string& useremail, int usersex, const std::string& orderTime) {
	auto con = pool_->getConnection();
	if (con == nullptr) {
		return false;
	}

	Defer defer([this, &con]() {
		pool_->returnConnection(std::move(con));
	});

	try {
		// 获取最新的 id 值
		std::unique_ptr<sql::PreparedStatement> pstmtId(con->_con->prepareStatement(
			"SELECT MAX(id) AS max_id FROM guahao"));
		std::unique_ptr<sql::ResultSet> res(pstmtId->executeQuery());

		int newId = 1;
		if (res->next()) {
			newId = res->getInt("max_id") + 1;
		}

		// 插入新行数据
		std::unique_ptr<sql::PreparedStatement> pstmt(con->_con->prepareStatement(
			"INSERT INTO guahao (id, useruid, doctoruid, doctorname, username, useremail, usersex, userorderdata) VALUES (?, ?, ?, ?, ?, ?, ?, ?)"));
		pstmt->setInt(1, newId);
		pstmt->setInt(2, useruid);
		pstmt->setInt(3, doctoruid);
		pstmt->setString(4, doctorName);
		pstmt->setString(5, username);
		pstmt->setString(6, useremail);
		pstmt->setInt(7, usersex);
		pstmt->setString(8, orderTime);

		int updateCount = pstmt->executeUpdate();
		return updateCount > 0;
	} catch (sql::SQLException& e) {
		std::cerr << "SQLException: " << e.what();
		return false;
	}
}





std::shared_ptr<UserInfo> MysqlDao::GetUser(int uid)
{
	auto con = pool_->getConnection();
	if (con == nullptr) {
		return nullptr;
	}

	Defer defer([this, &con]() {
		pool_->returnConnection(std::move(con));
		});

	try {
		// 准备SQL语句
		std::unique_ptr<sql::PreparedStatement> pstmt(con->_con->prepareStatement("SELECT * FROM user WHERE uid = ?"));
		pstmt->setInt(1, uid); // 将uid替换为你要查询的uid

		// 执行查询
		std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
		std::shared_ptr<UserInfo> user_ptr = nullptr;
		// 遍历结果集
		while (res->next()) {
			user_ptr.reset(new UserInfo);
			user_ptr->pwd = res->getString("pwd");
			user_ptr->email = res->getString("email");
			user_ptr->name= res->getString("name");
			/*user_ptr->nick = res->getString("nick");
			user_ptr->desc = res->getString("desc");
			user_ptr->sex = res->getInt("sex");
			user_ptr->icon = res->getString("icon");*/
			user_ptr->uid = uid;
			break;
		}
		return user_ptr;
	}
	catch (sql::SQLException& e) {
		std::cerr << "SQLException: " << e.what();
		std::cerr << " (MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		return nullptr;
	}
}
std::shared_ptr<DoctorInfo> MysqlDao::GetDoctor(int id)
{
	auto con = pool_->getConnection();
	if (con == nullptr) {
		return nullptr;
	}

	Defer defer([this, &con]() {
		pool_->returnConnection(std::move(con));
	});

	try {
		// 准备SQL语句
		std::unique_ptr<sql::PreparedStatement> pstmt(con->_con->prepareStatement("SELECT * FROM doctors WHERE ID = ?"));
		pstmt->setInt(1, id); // 将id替换为你要查询的id

		// 执行查询
		std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
		std::shared_ptr<DoctorInfo> doctor_ptr = nullptr;

		// 遍历结果集
		while (res->next()) {
			doctor_ptr.reset(new DoctorInfo);
			doctor_ptr->id = id;
			doctor_ptr->workID = res->getString("workID");
			doctor_ptr->name = res->getString("name");
			doctor_ptr->pwd = res->getString("pwd");
			doctor_ptr->email = res->getString("email");
			doctor_ptr->sex = res->getInt("sex");
			doctor_ptr->year = res->getString("year");
			doctor_ptr->month = res->getString("month");
			doctor_ptr->day = res->getString("day");
			doctor_ptr->IDcard = res->getString("IDcard");
			doctor_ptr->phone = res->getString("phone");
			doctor_ptr->department_id = res->getInt("department_id");
			doctor_ptr->intr = res->getString("intr");
			break; // 只处理一条记录
		}

		return doctor_ptr;
	}
	catch (sql::SQLException& e) {
		std::cerr << "SQLException: " << e.what();
		std::cerr << " (MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		return nullptr;
	}
}

std::shared_ptr<UserInfo> MysqlDao::GetUser(std::string name)
{
	auto con = pool_->getConnection();
	if (con == nullptr) {
		return nullptr;
	}

	Defer defer([this, &con]() {
		pool_->returnConnection(std::move(con));
		});

	try {
		// 准备SQL语句
		std::unique_ptr<sql::PreparedStatement> pstmt(con->_con->prepareStatement("SELECT * FROM user WHERE name = ?"));
		pstmt->setString(1, name); // 将uid替换为你要查询的uid

		// 执行查询
		std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
		std::shared_ptr<UserInfo> user_ptr = nullptr;
		// 遍历结果集
		while (res->next()) {
			user_ptr.reset(new UserInfo);
			user_ptr->pwd = res->getString("pwd");
			user_ptr->email = res->getString("email");
			user_ptr->name = res->getString("name");
			/*user_ptr->nick = res->getString("nick");
			user_ptr->desc = res->getString("desc");
			user_ptr->sex = res->getInt("sex");*/
			user_ptr->uid = res->getInt("uid");
			break;
		}
		return user_ptr;
	}
	catch (sql::SQLException& e) {
		std::cerr << "SQLException: " << e.what();
		std::cerr << " (MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		return nullptr;
	}
}


bool MysqlDao::GetApplyList(int touid, std::vector<std::shared_ptr<ApplyInfo>>& applyList, int begin, int limit) {
	auto con = pool_->getConnection();
	if (con == nullptr) {
		return false;
	}

	Defer defer([this, &con]() {
		pool_->returnConnection(std::move(con));
		});


		try {
		// 准备SQL语句, 根据起始id和限制条数返回列表
		std::unique_ptr<sql::PreparedStatement> pstmt(con->_con->prepareStatement("select apply.from_uid, apply.status, user.name, "
				"user.nick, user.sex from friend_apply as apply join user on apply.from_uid = user.uid where apply.to_uid = ? "
			"and apply.id > ? order by apply.id ASC LIMIT ? "));

		pstmt->setInt(1, touid); // 将uid替换为你要查询的uid
		pstmt->setInt(2, begin); // 起始id
		pstmt->setInt(3, limit); //偏移量
		// 执行查询
		std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
		// 遍历结果集
		while (res->next()) {
			auto name = res->getString("name");
			auto uid = res->getInt("from_uid");
			auto status = res->getInt("status");
			auto nick = res->getString("nick");
			auto sex = res->getInt("sex");
			auto apply_ptr = std::make_shared<ApplyInfo>(uid, name, "", "", nick, sex, status);
			applyList.push_back(apply_ptr);
		}
		return true;
	}
	catch (sql::SQLException& e) {
		std::cerr << "SQLException: " << e.what();
		std::cerr << " (MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		return false;
	}
}


bool MysqlDao::UpdateCheckAdivice(int id, const std::string& paintuid, const std::string& result) {
	auto con = pool_->getConnection();
	if (con == nullptr) {
		return false;
	}

	Defer defer([this, &con]() {
		pool_->returnConnection(std::move(con));
	});

	try {
		// 准备更新语句
		std::unique_ptr<sql::PreparedStatement> pstmt(con->_con->prepareStatement(
			"UPDATE guahao SET chufang = ? WHERE id = ? "));

		// 设置参数
		pstmt->setString(1, result);
		pstmt->setInt(2, id);
		//pstmt->setString(3, paintuid);

		// 执行更新操作
		int update_count = pstmt->executeUpdate();

		// 检查更新是否成功
		if (update_count > 0) {
			return true;
		} else {
			std::cerr << "No rows updated, check if id and paintuid are correct." << std::endl;
			return false;
		}
	} catch (sql::SQLException& e) {
		std::cerr << "SQLException: " << e.what();
		std::cerr << " (MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		return false;
	}
}


bool MysqlDao::InsertIntoHospitalization(int doctoruid, int patientuid, const std::string& patientname,
										 const std::string& bed_number, const std::string& admission_number,
										 const std::string& doctor_name, const std::string& room) {
	auto con = pool_->getConnection();
	if (con == nullptr) {
		return false;
	}

	Defer defer([this, &con]() {
		pool_->returnConnection(std::move(con));
	});

	try {
		// 准备插入语句
		std::unique_ptr<sql::PreparedStatement> pstmt(con->_con->prepareStatement(
			"INSERT INTO Hospitalization (doctor_uid, patient_uid, patient_name, bed_number, admission_data, doctorname, roomnum) "
			"VALUES (?, ?, ?, ?, ?, ?, ?)"));

		// 设置参数
		pstmt->setInt(1, doctoruid);
		pstmt->setInt(2, patientuid);
		pstmt->setString(3, patientname);
		pstmt->setString(4, bed_number);
		pstmt->setString(5, admission_number);
		pstmt->setString(6, doctor_name);
		pstmt->setString(7, room);

		// 执行插入操作
		int insert_count = pstmt->executeUpdate();

		// 检查插入是否成功
		if (insert_count > 0) {
			return true;
		} else {
			std::cerr << "No rows inserted, check the data provided." << std::endl;
			return false;
		}
	} catch (sql::SQLException& e) {
		std::cerr << "SQLException: " << e.what();
		std::cerr << " (MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		return false;
	}
}


bool MysqlDao::UpdateCheckResult(int id, const std::string& paintuid, const std::string& result) {
	auto con = pool_->getConnection();
	if (con == nullptr) {
		return false;
	}

	Defer defer([this, &con]() {
		pool_->returnConnection(std::move(con));
	});

	try {
		// 准备更新语句
		std::unique_ptr<sql::PreparedStatement> pstmt(con->_con->prepareStatement(
			"UPDATE guahao SET checkresult = ? WHERE id = ? "));

		// 设置参数
		pstmt->setString(1, result);
		pstmt->setInt(2, id);
		//pstmt->setString(3, paintuid);

		// 执行更新操作
		int update_count = pstmt->executeUpdate();

		// 检查更新是否成功
		if (update_count > 0) {
			return true;
		} else {
			std::cerr << "No rows updated, check if id and paintuid are correct." << std::endl;
			return false;
		}
	} catch (sql::SQLException& e) {
		std::cerr << "SQLException: " << e.what();
		std::cerr << " (MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		return false;
	}
}

bool MysqlDao::GetGuahaoList(int doctor_uid,
    std::vector<std::shared_ptr<paintInfobase>>& baseList,
    std::vector<std::shared_ptr<paintInfocheck>>& checkList,
    std::vector<std::shared_ptr<paintInfochufang>>& chufangList) {

    auto con = pool_->getConnection();
    if (con == nullptr) {
        return false;
    }

    Defer defer([this, &con]() {
        pool_->returnConnection(std::move(con));
    });

    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(con->_con->prepareStatement(
            "SELECT id, useruid, username, useremail, usersex, userage, userorderdata, userinfo, checkresult, chufang "
            "FROM guahao WHERE doctoruid = ?"));

        pstmt->setInt(1, doctor_uid);

        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        while (res->next()) {
        	int id=res->getInt("id");
            int userid = res->getInt("useruid");
            std::string username = res->getString("username");
            std::string useremail = res->getString("useremail");
            int usersex = res->getInt("usersex");
            std::string userage = res->getString("userage");
            std::string userorderdata = res->getString("userorderdata");
            std::string userinfo = res->getString("userinfo");
            std::string checkresult = res->getString("checkresult");
            std::string chufang = res->getString("chufang");

            // 构建 paintInfobase 对象
            auto base_ptr = std::make_shared<paintInfobase>(id,userid, username, useremail, usersex, userage, userorderdata, userinfo);
            baseList.push_back(base_ptr);

            // 构建 paintInfocheck 对象
            auto check_ptr = std::make_shared<paintInfocheck>(id,userid, username, useremail, usersex, userage, userorderdata, userinfo, checkresult);
            checkList.push_back(check_ptr);

            // 构建 paintInfochufang 对象
            auto chufang_ptr = std::make_shared<paintInfochufang>(id,userid, username, useremail, usersex, userage, userorderdata, userinfo, checkresult, chufang);
            chufangList.push_back(chufang_ptr);
        }
        return true;
    } catch (sql::SQLException& e) {
        std::cerr << "SQLException: " << e.what();
        std::cerr << " (MySQL error code: " << e.getErrorCode();
        std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
        return false;
    }
}

bool MysqlDao::GetFriendList(int self_id, std::vector<std::shared_ptr<UserInfo> >& user_info_list) {

	auto con = pool_->getConnection();
	if (con == nullptr) {
		return false;
	}

	Defer defer([this, &con]() {
		pool_->returnConnection(std::move(con));
		});


	try {
		// 准备SQL语句, 根据起始id和限制条数返回列表
		std::unique_ptr<sql::PreparedStatement> pstmt(con->_con->prepareStatement("select * from friend where self_id = ? "));

		pstmt->setInt(1, self_id); // 将uid替换为你要查询的uid

		// 执行查询
		std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
		// 遍历结果集
		while (res->next()) {
			auto friend_id = res->getInt("friend_id");
			auto back = res->getString("back");
			//再一次查询friend_id对应的信息
			auto user_info = GetUser(friend_id);
			if (user_info == nullptr) {
				continue;
			}

			//user_info->back = user_info->name;
			user_info_list.push_back(user_info);
		}
		return true;
	}
	catch (sql::SQLException& e) {
		std::cerr << "SQLException: " << e.what();
		std::cerr << " (MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		return false;
	}

	return true;
}