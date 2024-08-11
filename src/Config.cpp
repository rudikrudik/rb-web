#include "../include/Config.h"

std::string readConfigFile(const std::string &config_path, const std::string pattern){
    std::string result;
    std::ifstream file(config_path);
    std::string line;

    if(file.is_open()){
        while(std::getline(file, line)){
            size_t position = line.find(pattern);
            if(position != std::string::npos){
                std::istringstream iss(line);
                std::vector<std::string> parsed((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());
                result = parsed[2];
                break;
            }
            else{
                result = "error";
            }
        }
    }
    else{
        std::cout << "File not found" << std::endl;
    }

    file.close();
    return result;
}

