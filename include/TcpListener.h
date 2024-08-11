#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <sstream>
#include <string>
#include <iostream>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../include/Logger.h"
#include "../include/LoggerDefineInit.h"

#define MAX_EVENTS 10
#define MAX_BUF    1024

class TcpListener {

public:
    TcpListener(const char *ip_address, int port);
    ~TcpListener();
    int init();
    int run();

protected:
    virtual int clientRawData(int user_fd) = 0;

private:
    const char*     m_server_ip_address;
    int             m_port;
    int             m_server_socket;
    int             m_epoll_file_description;
    bool            m_status;
};