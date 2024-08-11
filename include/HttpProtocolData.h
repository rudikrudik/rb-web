#pragma once

#include <string>
#include <sstream>

#define RESP_OK 200
#define RESP_NOT_FOUND 404
#define RESP_NOT_AUTH 500

std::string getHttpProtoServerData(int error_code, size_t content_length){
    std::ostringstream oss;
    oss << "HTTP/1.1 " << error_code << " OK\r\n";
    oss << "Server: rb-web/0.1.1\r\n";
    oss << "Cache-Control: no-cache, private\r\n";
    oss << "Content-Type: text/html\r\n";
    oss << "Content-Length: " << content_length << " \r\n";
    oss << "\r\n";

    return std::string(oss.str());
}