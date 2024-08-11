#include "../include/WebServer.h"
#include "../include/HttpProtocolData.h"

WebServer::WebServer(const char *server_ip_address, int port, ReadData *readData) : m_read_data(readData),
                                                    TcpListener(server_ip_address, port) {}

// Обработка клиентского соединения
int WebServer::clientRawData(int user_fd){
    char buf[MAX_BUF];
    bzero(buf, MAX_BUF);
    size_t message_len = recv(user_fd, buf, MAX_BUF, 0);

    if(message_len == 0){
        Log(log_console, log_file, WARNING, "Message from user is empty");
        close(user_fd);
    }
    else {
        processing(buf, user_fd);
    }
    return 0;
}

// Обработка команд
int WebServer::processing(const char *msg, int user_fd){
    std::istringstream iss(msg);
    std::vector<std::string> parsed((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());

    if(parsed[1] == "/"){
        parsed[1] = "/index.html";
    }

    switch (httpMethod(parsed[0], parsed[1])) {
        case 1: // GET
            serverResponse(user_fd, RESP_OK, parsed[1]);
            Log(log_console, log_file, DEBUG, "Method: " + parsed[0] + " " + parsed[1] + " OK");
            break;
        case 2: // POST
            std::cout << "Function POST not ready: " << std::endl;
            close(user_fd);
            break;
        case 3: // PUT
            std::cout << "Function PUT not ready" << std::endl;
            close(user_fd);
            break;
        case 4: // DELETE
            std::cout << "Function DELETE not ready" << std::endl;
            close(user_fd);
            break;
        default:
            std::string error_path = "404.html";
            serverResponse(user_fd, RESP_NOT_FOUND, error_path);
            Log(log_console, log_file, DEBUG, "Page " + parsed[1] + " Not found");
            break;
    }
}


int WebServer::serverResponse(int user_fd, int httpCodeError, std::string file) {
    bool error_flag = false;
    if(httpCodeError != RESP_NOT_FOUND){
        error_flag = true;
    }

    std::string content = m_read_data->readFile(file, error_flag);
    std::string output = getHttpProtoServerData(httpCodeError, content.size());
    output += content;
    size_t output_size = output.size() + 1;

    sendToClient(user_fd, output, output_size);

    return 0;
}

int WebServer::sendToClient(int user_fd, std::string &response, size_t length) {
    if (send(user_fd, response.c_str(), length, 0) == -1) {
        Log(log_console, log_file, ERROR, "Send response to user: ERROR");
        close(user_fd);
        exit(1);
    }
    else{
        Log(log_console, log_file, DEBUG, "Send response to user: OK");
    }
    close(user_fd);
    return 0;
}

bool WebServer::compareUserRequestFile(const std::string &userFile) {
    for(const auto &it : m_read_data->getValidFile()){
        if(it == userFile){
            return true;
        }
    }
    return false;
}

int WebServer::httpMethod(std::string &user_request_method, std::string &compare_request_file) {
    if(compareUserRequestFile(compare_request_file)) {
        if (user_request_method == "GET") { return 1; }
        if (user_request_method == "POST") { return 2; }
        if (user_request_method == "PUT") { return 3; }
        if (user_request_method == "DELETE") { return 4; }
    }
    return 0;
}