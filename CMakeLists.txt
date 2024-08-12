cmake_minimum_required(VERSION 3.22)

if($ENV{GITHUB_RUN_NUMBER})
    set(PROJECT_VERSION 0.0.$ENV{GITHUB_RUN_NUMBER})
else()
    project(rb-web VERSION 0.0.1)
endif()

project(rb-web VERSION ${PROJECT_VERSION})

configure_file(include/Version.h.in Version.h)

set(SOURCE_FILES
        src/main.cpp
        src/TcpListener.cpp
        src/WebServer.cpp
        src/ReadData.cpp
        src/Logger.cpp
        src/Config.cpp
)


add_executable(${PROJECT_NAME} ${SOURCE_FILES})

add_library(version src/VersionServer.cpp)

set_target_properties(rb-web version PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)

target_include_directories(rb-web
        PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(rb-web PRIVATE
        version
)

install(TARGETS rb-web RUNTIME DESTINATION bin)
install(FILES config.ini DESTINATION /usr/share/rb-web)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT rudik.login@gmail.com)

include(CPack)