//
// Created by user on 24-8-17.
//

#ifndef CSERVER_H
#define CSERVER_H



#include <string>
#include "const.h"

class CServer:public std::enable_shared_from_this<CServer>
{
public:
    CServer(boost::asio::io_context& ioc, unsigned short& port);
    void Start();
private:
    tcp::acceptor  _acceptor;
    net::io_context& _ioc;

};



#endif //CSERVER_H
