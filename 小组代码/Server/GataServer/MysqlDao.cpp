//
// Created by user on 24-8-19.
//


#include "MysqlDao.h"
#include "Config.h"

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

int MysqlDao::RegDoctor(const std::string& workID, const std::string& email, const std::string& pwd)
{
	auto con = pool_->getConnection();
	try {
		if (con == nullptr) {
			return -1; // 返回-1表示连接失败
		}

		// 准备调用存储过程
		std::unique_ptr<sql::PreparedStatement> stmt(con->_con->prepareStatement("CALL reg_doctor(?,?,?,@result,@out_workID)"));

		// 设置输入参数
		stmt->setString(1, workID);
		stmt->setString(2, email);
		stmt->setString(3, pwd);

		// 执行存储过程
		stmt->execute();

		// 获取输出参数result的值
		std::unique_ptr<sql::Statement> stmtResult(con->_con->createStatement());
		std::unique_ptr<sql::ResultSet> res(stmtResult->executeQuery("SELECT @result AS result, @out_workID AS out_workID"));

		if (res->next()) {
			int result = res->getInt("result");
			std::string returnedWorkID = res->getString("out_workID");

			std::cout << "Result: " << result << std::endl;
			if (!returnedWorkID.empty()) {
				std::cout << "Registered WorkID: " << returnedWorkID << std::endl;
			}
			pool_->returnConnection(std::move(con));
			return result;
		}

		pool_->returnConnection(std::move(con));
		return -1; // 返回-1表示没有得到输出结果
	}
	catch (sql::SQLException& e) {
		pool_->returnConnection(std::move(con));
		std::cerr << "SQLException: " << e.what();
		std::cerr << " (MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		return -1; // 返回-1表示发生SQL异常
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


bool MysqlDao::CheckDoctorEmail(const std::string& workID, const std::string& email) {
	auto con = pool_->getConnection();
	try {
		if (con == nullptr) {
			pool_->returnConnection(std::move(con));
			return false;
		}

		// 准备查询语句
		std::unique_ptr<sql::PreparedStatement> pstmt(con->_con->prepareStatement("SELECT email FROM doctors WHERE workID = ?"));

		// 绑定参数
		pstmt->setString(1, workID);

		// 执行查询
		std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

		// 遍历结果集
		while (res->next()) {
			std::cout << "Check Doctor Email: " << res->getString("email") << std::endl;
			if (email != res->getString("email")) {
				pool_->returnConnection(std::move(con));
				return false;
			}
			pool_->returnConnection(std::move(con));
			return true;
		}
	}
	catch (sql::SQLException& e) {
		pool_->returnConnection(std::move(con));
		std::cerr << "SQLException: " << e.what();
		std::cerr << " (MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		return false;
	}
	return false;  // 如果没有找到匹配的记录，返回false
}


bool MysqlDao::CheckEmail(const std::string& name, const std::string& email) {
	auto con = pool_->getConnection();
	try {
		if (con == nullptr) {
			pool_->returnConnection(std::move(con));
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
			pool_->returnConnection(std::move(con));
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

bool MysqlDao::UpdateDoctorPwd(const std::string& workID, const std::string& newpwd) {
	auto con = pool_->getConnection();
	try {
		if (con == nullptr) {
			pool_->returnConnection(std::move(con));
			return false;
		}

		// 准备更新语句
		std::unique_ptr<sql::PreparedStatement> pstmt(con->_con->prepareStatement("UPDATE doctors SET pwd = ? WHERE workID = ?"));

		// 绑定参数
		pstmt->setString(1, newpwd);
		pstmt->setString(2, workID);

		// 执行更新
		int updateCount = pstmt->executeUpdate();

		std::cout << "Updated rows: " << updateCount << std::endl;
		pool_->returnConnection(std::move(con));
		return updateCount > 0;
	}
	catch (sql::SQLException& e) {
		pool_->returnConnection(std::move(con));
		std::cerr << "SQLException: " << e.what();
		std::cerr << " (MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		return false;
	}
}




bool MysqlDao::CheckDoctorPwd(const std::string& workID, const std::string& pwd, DoctorInfo& doctorInfo) {
	auto con = pool_->getConnection();
	if (con == nullptr) {
		return false;
	}

	Defer defer([this, &con]() {
		pool_->returnConnection(std::move(con));
	});

	try {
		// 准备SQL语句
		std::unique_ptr<sql::PreparedStatement> pstmt(con->_con->prepareStatement("SELECT * FROM doctors WHERE workID = ?"));
		pstmt->setString(1, workID); // 将workID绑定为查询参数

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

		// 验证密码
		if (pwd != origin_pwd) {
			return false;
		}

		// 填充DoctorInfo结构体
		doctorInfo.id=res->getInt("ID");
		doctorInfo.name = res->getString("name");
		doctorInfo.email = res->getString("email");
		doctorInfo.workID = res->getString("workID");
		doctorInfo.pwd = origin_pwd;

		return true;
	}
	catch (sql::SQLException& e) {
		std::cerr << "SQLException: " << e.what();
		std::cerr << " (MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		return false;
	}
}





bool MysqlDao::CheckPwd(const std::string& email, const std::string& pwd, UserInfo& userInfo) {
	auto con = pool_->getConnection();
	if (con == nullptr) {
		return false;
	}

	Defer defer([this, &con]() {
		pool_->returnConnection(std::move(con));
		});

	try {


		// 准备SQL语句
		std::unique_ptr<sql::PreparedStatement> pstmt(con->_con->prepareStatement("SELECT * FROM user WHERE email = ?"));
		pstmt->setString(1, email); // 将username替换为你要查询的用户名

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
		userInfo.name = res->getString("name");
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
bool MysqlDao::UpdateDoctorDetails(const std::string& workID, const std::string& name, int sex, const std::string& year, const std::string& month, const std::string& data, const std::string& IDcard, const std::string& phone, int department_id, const std::string& intr) {
	auto con = pool_->getConnection();
	try {
		if (con == nullptr) {
			pool_->returnConnection(std::move(con));
			return false;
		}

		// 准备更新语句
		std::unique_ptr<sql::PreparedStatement> pstmt(con->_con->prepareStatement(
			"UPDATE doctors SET name = ?, sex = ?, year = ?, month = ?, day = ?, IDcard = ?, phone = ?, department_id = ?, intr = ? WHERE workID = ?"
		));

		// 绑定参数
		pstmt->setString(1, name); // 绑定 name
		pstmt->setInt(2, sex); // 绑定 sex
		pstmt->setString(3, year); // 绑定 year
		pstmt->setString(4, month); // 绑定 month
		pstmt->setString(5, data); // 绑定 data
		pstmt->setString(6, IDcard); // 绑定 IDcard
		pstmt->setString(7, phone); // 绑定 phone
		pstmt->setInt(8, department_id); // 绑定 department_id
		pstmt->setString(9, intr); // 绑定 intr
		pstmt->setString(10, workID); // 绑定 workID

		// 执行更新
		int rowsAffected = pstmt->executeUpdate();
		pool_->returnConnection(std::move(con));

		// 检查更新是否成功
		return (rowsAffected > 0);
	}
	catch (sql::SQLException& e) {
		pool_->returnConnection(std::move(con));
		std::cerr << "SQLException: " << e.what();
		std::cerr << " (MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		return false;
	}
}

bool MysqlDao::UpdateUserDetails(int uid, const std::string& realname, int sex, const std::string& year, const std::string& month, const std::string& data, const std::string& IDcard, const std::string& phone) {
	auto con = pool_->getConnection();
	try {
		if (con == nullptr) {
			pool_->returnConnection(std::move(con));
			return false;
		}

		// 准备更新语句
		std::unique_ptr<sql::PreparedStatement> pstmt(con->_con->prepareStatement(
			"UPDATE user SET realname = ?, sex = ?, year = ?, month = ?, data = ?, IDcard = ?, phone = ? WHERE uid = ?"
		));

		// 绑定参数
		pstmt->setString(1, realname); // 绑定 realname
		pstmt->setInt(2, sex); // 绑定 sex
		pstmt->setString(3, year); // 绑定 year
		pstmt->setString(4, month); // 绑定 month
		pstmt->setString(5, data); // 绑定 data
		pstmt->setString(6, IDcard); // 绑定 IDcard
		pstmt->setString(7, phone); // 绑定 phone
		pstmt->setInt(8, uid); // 绑定 uid

		// 执行更新
		int rowsAffected = pstmt->executeUpdate();
		pool_->returnConnection(std::move(con));

		// 检查更新是否成功
		return (rowsAffected > 0);
	}
	catch (sql::SQLException& e) {
		pool_->returnConnection(std::move(con));
		std::cerr << "SQLException: " << e.what();
		std::cerr << " (MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		return false;
	}
}

