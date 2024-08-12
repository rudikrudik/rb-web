#include "../include/VersionServer.h"
#include "../cmake-build-debug/Version.h"

int version(){
    return PROJECT_VERSION_PATCH;
}