//
// Created by user on 24-8-17.
//

#ifndef CONST_H
#define CONST_H
#include "boost/beast/http.hpp"
#include "boost/beast.hpp"
#include "boost/asio.hpp"
#include<memory>
#include<iostream>
#include"Singleton.h"
#include<functional>
#include<map>
#include<unordered_map>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/reader.h>
#define BOOST_NO_CXX11_SCOPED_ENUMS
#include <boost/filesystem.hpp>
#undef BOOST_NO_CXX11_SCOPED_ENUMS
#include<boost/property_tree/ptree.hpp>
#include<boost/property_tree/ini_parser.hpp>
#include<atomic>
#include<queue>
#include<mutex>
#include<condition_variable>
#include"hiredis.h"
#include <cassert>
#include<memory>


namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>


enum ErrorCodes {
    Success = 0,
    Error_Json = 1001,  //Json解析错误
    RPCFailed = 1002,  //RPC请求错误
    VarifyExpired = 1003, //验证码过期
    VarifyCodeErr = 1004, //验证码错误
    UserExist = 1005,       //用户已经存在
    PasswdErr = 1006,    //密码错误
    EmailNotMatch = 1007,  //邮箱不匹配
    PasswdUpFailed = 1008,  //更新密码失败
    PasswdInvalid = 1009,   //密码更新失败
    TokenInvalid = 1010,   //Token失效
    UidInvalid = 1011,  //uid无效
    UPDATA_USER_INFO_IN_REG_FAIL=1012,//在注册时更新用户数据失败
};


// Defer类
class Defer {
public:
    // 接受一个lambda表达式或者函数指针
    Defer(std::function<void()> func) : func_(func) {}

    // 析构函数中执行传入的函数
    ~Defer() {
        func_();
    }

private:
    std::function<void()> func_;
};

#define CODEPREFIX "code_"


#endif //CONST_H
