#include "mprpcapplication.h"
#include <iostream>
#include <string>
#include <unistd.h>

MprpcConfig MprpcApplication::m_config;
void ShowHelp()
{
    std::cout << "format: command -i <configfile>" << std::endl;
    exit(EXIT_FAILURE);
}

void MprpcApplication::Init(int argc, char** argv)
{
    if( argc < 2)
    {
        ShowHelp();
    }
    int c = 0;
    std::string config_file = "";
    while((c = getopt(argc,argv,"i:")) != -1)
    {
        switch (c)
        {
            case 'i':
                config_file = optarg;
                break;
             case '?':
                std::cout << "invalid args " << std::endl;
                ShowHelp();
                break;
             case ':':
                std::cout << "invalid args " << std::endl;
                ShowHelp();
                break;         
            default:
                break;
        }
    }
    //加载配置文件 
    m_config.loadConfigFile(config_file.c_str());

    std::cout << "rpcserverIp: " << m_config.load("rpcserverIp") << std::endl;
    std::cout << "rpcserverIp: " << m_config.load("rpcserverPort") << std::endl;
    std::cout << "zookeeperIp: " << m_config.load("zookeeperIp") << std::endl;
    std::cout << "zookeeperPort: " << m_config.load("zookeeperPort") << std::endl;
}
MprpcApplication& MprpcApplication::GetInstance()
{
    static MprpcApplication app;
    return app;
}
MprpcConfig& MprpcApplication::GetConfig()
{
    return m_config;
}