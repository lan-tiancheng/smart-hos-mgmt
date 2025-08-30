//
// Created by user on 24-8-17.
//

#ifndef LOGICSYSTEM_H
#define LOGICSYSTEM_H
#include"const.h"

class HttpConnection;
typedef std::function<void(std::shared_ptr<HttpConnection>)> HttpHandler;
class LogicSystem :public Singleton<LogicSystem>
{
    friend class Singleton<LogicSystem>;
public:
    ~LogicSystem();
    bool HandleGet(std::string, std::shared_ptr<HttpConnection>);
    bool HandlePost(std::string, std::shared_ptr<HttpConnection>);
    void RegGet(std::string, HttpHandler handler);
    void RegPost(std::string url,HttpHandler handler);
private:
    LogicSystem();
    std::map<std::string, HttpHandler> _post_handlers;
    std::map<std::string, HttpHandler> _get_handlers;
};
#endif //LOGICSYSTEM_H
