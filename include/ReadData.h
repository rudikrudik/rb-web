#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <iterator>
#include <filesystem>

#include "../include/Logger.h"
#include "../include/LoggerDefineInit.h"

class ReadData{
public:
    ReadData(std::string pathOk, std::string pathError);

    std::string readFile(std::string &fileName, bool errorFlag);
    std::vector<std::string> getValidFile();
    std::string getCurrentOkPath();
    std::string getCurrentErrorPath();

private:
    std::string m_path_ok;
    std::string m_path_error;
    std::vector<std::string> m_valid_file_vector;
    void readValidFile();
};
