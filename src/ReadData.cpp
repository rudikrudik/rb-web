#include "../include/ReadData.h"


ReadData::ReadData(std::string pathOk, std::string pathError) : m_path_ok(std::move(pathOk)),
                                                                m_path_error(std::move(pathError)){
    readValidFile();
}

std::string ReadData::readFile(std::string &fileName, bool errorFlag) {
    std::string path = getCurrentOkPath();

    if(!errorFlag){
        path = getCurrentErrorPath();
    }

    std::ifstream file(path + fileName);
    std::string result;

    if(file.good()){
        std::string temp((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        result = temp;
        Log(log_console, log_file, DEBUG, "file open: " + path + fileName);
    }
    else{
        Log(log_console, log_file, ERROR, "file not found: " + path + fileName);
    }

    file.close();
    return result;
}

std::vector<std::string> ReadData::getValidFile() {
    return m_valid_file_vector;
}

std::string ReadData::getCurrentOkPath() {
    return m_path_ok;
}

std::string ReadData::getCurrentErrorPath() {
    return m_path_error;
}

void ReadData::readValidFile() {
    for(const auto &entry : std::filesystem::recursive_directory_iterator(m_path_ok)){
        std::string temp = entry.path();
        m_valid_file_vector.emplace_back(temp.erase(0, m_path_ok.size() - 1));
    }
}
