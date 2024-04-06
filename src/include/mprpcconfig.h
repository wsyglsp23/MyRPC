#pragma once

#include<unordered_map>

class MprpcConfig
{
public:
    void loadConfigFile(const char * configFile);
    std::string load(std::string key);
private:
    std::unordered_map<std::string, std::string> m_configMap;
};