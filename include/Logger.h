#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <thread>
#include <mutex>

enum LogLevel { DEBUG, INFO, WARNING, ERROR, CRITICAL };

template <class T>
class Logger
{
public:
    static T& init() {
        static T instance;
        return instance;
    }

    Logger(T const&) = delete;
    T& operator = (T const&) = delete;

    virtual void write(LogLevel level, std::string msg) = 0;
    virtual void setLogLevel(LogLevel level) = 0;
    virtual LogLevel getLogLevel() = 0;
    static std::string levelToString(LogLevel);
    static std::string getTimeStamp();

    LogLevel m_log_level = CRITICAL;

protected:
    Logger() = default;
    ~Logger() = default;
};

// Вывод логов в консоль
class Console : public Logger<Console>
{
public:
    void write(LogLevel level, std::string msg) override;
    void setLogLevel(LogLevel level) override;
    LogLevel getLogLevel() override;
};

// Вывод логов в файл
class File : public Logger<File>
{
public:
    void write(LogLevel level, std::string msg) override;
    void setLogLevel(LogLevel level) override;
    LogLevel getLogLevel() override;
    void setPathFile(std::string &path);
    std::string getPathFile();

private:
    std::string m_path;
};

class Log{
public:
    Log(Console, File, LogLevel level, std::string msg);
};