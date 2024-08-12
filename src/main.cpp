#include <string>

#include "../include/WebServer.h"
#include "../include/ReadData.h"
#include "../include/Logger.h"
#include "../include/Config.h"
#include "../include/VersionServer.h"

int main(int argc, char *argv[]) {

    std::string config_file_path;
    std::string message =   "Usage: ls [OPTION]... [FILE]...\n"
                            " -c config.ini   to run server\n"
                            " -v              show version\n"
                            " -s              to stop server\n";

    if(argc < 2 || argc > 3){
        std::cout << message;
        return 0;
    }

    switch (argc) {
        case 2 :
            if(std::string(argv[1]) == "-v"){std::cout << "Version rb-web is: "
                << std::to_string(version_major()) << "."
                << std::to_string(version_minor()) << "."
                << std::to_string(version_path()) << std::endl;}
            return 0;
        case 3 :
            if(std::string(argv[1]) == "-c"){config_file_path = argv[2];}
            break;
        default:
            break;
    }

    // Путь лог файла
    std::string path_log_file(readConfigFile(config_file_path, "logfile"));
    // Путь каталога html файлов
    std::string path_to_ok_file(readConfigFile(config_file_path, "wwwroot"));
    // Путь каталога к файлу 404
    std::string path_to_error_file(readConfigFile(config_file_path, "wwwerror"));

    // Установка пути лог файла и уровень логирования в файл
    log_file.setPathFile(path_log_file);
    LogLevel file_level = static_cast<LogLevel>(std::stoi(readConfigFile(config_file_path, "file_log_level")));
    log_file.setLogLevel(file_level);

    // Установка уровня логирования с выводом в консоль
    LogLevel console_level = static_cast<LogLevel>(std::stoi(readConfigFile(config_file_path, "console_log_level")));
    log_console.setLogLevel(console_level);

    ReadData read_data(path_to_ok_file, path_to_error_file);

    // Параметры запуска сервера
    std::string ip = readConfigFile(config_file_path, "ip");
    const char *c_string = ip.c_str();
    int port = std::stoi(readConfigFile(config_file_path, "port"));

    WebServer webServer(c_string, port, &read_data);

    // Запуск сервера
    if(webServer.init() != 0){
        Log(log_console, log_file, CRITICAL, "Failed to start server");
        return 1;
    }
    else{
        Log(log_console, log_file, INFO, "Server started");
    }

    webServer.run();

    return 0;
}