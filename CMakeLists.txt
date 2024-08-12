cmake_minimum_required(VERSION 3.22)
project(webserver_linux)

set(CMAKE_CXX_STANDARD 17)

add_executable(webserver_linux
        src/main.cpp
        include/TcpListener.h
        src/TcpListener.cpp
        include/WebServer.h
        src/WebServer.cpp
        include/HttpProtocolData.h
        include/ReadData.h
        src/ReadData.cpp
        include/Logger.h
        src/Logger.cpp
        include/LoggerDefineInit.h
        include/Config.h
        src/Config.cpp)