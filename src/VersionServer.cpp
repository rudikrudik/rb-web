#include "../include/VersionServer.h"
#include "../include/Version.h"

int version_path(){
    return rbweb_VERSION_PATCH;
    }

int version_minor(){
    return rbweb_VERSION_MINOR;
    }

int version_major(){
    return rbweb_VERSION_MAJOR;
    }