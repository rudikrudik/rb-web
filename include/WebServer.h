#pragma once

#include <vector>
#include <iterator>
#include <algorithm>

#include "../include/TcpListener.h"
#include "../include/ReadData.h"
#include "../include/Logger.h"
#include "../include/LoggerDefineInit.h"


class WebServer : public TcpListener {
public:
    WebServer(const char *server_ip_address, int port, ReadData *reaData);

private:
    int clientRawData(int user_fd) override;
    int processing(const char *msg, int user_fd);
    int serverResponse(int user_fd, int httpCodeError, std::string file);
    static int sendToClient(int user_fd, std::string &response, size_t length);
    bool compareUserRequestFile(const std::string &userFile);
    int httpMethod(std::string &user_request_method, std::string &compare_request_file);

    ReadData      *m_read_data;
};