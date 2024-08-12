cmake_minimum_required(VERSION 3.22)

if($ENV{GITHUB_RUN_NUMBER})
    set(PROJECT_VERSION 0.0.$ENV{GITHUB_RUN_NUMBER})
else()
    set(PROJECT_VERSION 0.1.1)
endif()

project(rbweb VERSION ${PROJECT_VERSION})

configure_file(include/Version.h.in include/Version.h)

set(SOURCE_FILES
        src/main.cpp
        src/TcpListener.cpp
        src/WebServer.cpp
        src/ReadData.cpp
        src/Logger.cpp
        src/Config.cpp
        src/VersionServer.cpp

)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(rbweb PUBLIC "${PROJECT_BINARY_DIR}/include")

install(TARGETS rbweb RUNTIME DESTINATION bin)
install(FILES config.ini DESTINATION /usr/share/rbweb)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT rudik.login@gmail.com)

include(CPack)