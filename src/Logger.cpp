#include "../include/Logger.h"

// Реализация статических методов базового класса Logger
template<class T>
std::string Logger<T>::levelToString(LogLevel level) {
    switch (level) {
        case DEBUG:     return "DEBUG";
        case INFO:      return "INFO";
        case WARNING:   return "WARNING";
        case ERROR:     return "ERROR";
        case CRITICAL:  return "CRITICAL";
        default:        return "UNKNOWN";
    }
}

template<class T>
std::string Logger<T>::getTimeStamp() {
    time_t now = time(nullptr);
    struct tm* timeinfo = localtime(&now);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);
    return timestamp;
}


// Реализация методов вывода в консоль
void Console::write(LogLevel level, std::string msg) {
    //TODO сделать выделение цветом уровней логирования
    std::mutex console_mutex;

    console_mutex.lock();
    std::cout << "[" << getTimeStamp() << "] " << levelToString(level) << ": " << msg << std::endl;
    console_mutex.unlock();
}

void Console::setLogLevel(LogLevel level) {
    m_log_level = level;
}

LogLevel Console::getLogLevel() {
    return m_log_level;
}


// Реализация методов записи в файл
void File::write(LogLevel level, std::string msg) {
    std::mutex file_mutex;

    file_mutex.lock();
    std::ofstream file(getPathFile(), std::ios::app);

    if(file.good()){
        file << "[" << getTimeStamp() << "] " << levelToString(level) << ": " << msg << std::endl;
    }
    file.close();
    file_mutex.unlock();
}

void File::setPathFile(std::string &path) {
    if(m_path.empty()){
        m_path = path;
    }
}

std::string File::getPathFile() {
    return m_path;
}

void File::setLogLevel(LogLevel level) {
    m_log_level = level;
}

LogLevel File::getLogLevel() {
    return m_log_level;
}


// Объединение классов для сокращения кода
Log::Log(Console, File, LogLevel level, std::string msg) {
    if(Console::init().getLogLevel() <= level){
        Console::init().write(level, msg);
    }
    if(File::init().getLogLevel() <= level){
        File::init().write(level, msg);
    }
}