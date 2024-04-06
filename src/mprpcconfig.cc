#include"mprpcconfig.h"
#include<iostream>
#include<string>
#include <algorithm> // std::find_if
#include <cctype>    // std::isspace
std::string TrimSpaces(const std::string& str) {
    auto start = std::find_if(str.begin(), str.end(), [](unsigned char ch) { return !std::isspace(ch); });
    auto end = std::find_if_not(str.rbegin(), str.rend(), [](unsigned char ch) { return std::isspace(ch); }).base();
    
    if (start < end) { // 确保找到的范围是有效的
        return std::string(start, end);
    } else {
        return std::string(); // 如果字符串全是空格或为空，则返回空字符串
    }
}

void MprpcConfig::loadConfigFile(const char* configFile)
{
    FILE * pf = fopen(configFile,"r");
    if(nullptr == pf)
    {
        std::cout << configFile << "is not exist!" << std::endl;
        return;
    }
    // 1.注释   2.正确的配置项 =    3.去掉开头的多余的空格 
    while(!feof(pf))
    {
        char buf[512] = {0};
        fgets(buf, 512, pf);

        // 去掉字符串前面多余的空格
        std::string read_buf(buf);
        TrimSpaces(read_buf);

        // 判断#的注释
        if (read_buf[0] == '#' || read_buf.empty())
        {
            continue;
        }

        // 解析配置项
        int idx = read_buf.find('=');
        if (idx == -1)
        {
            // 配置项不合法
            continue;
        }

        std::string key;
        std::string value;
        key = read_buf.substr(0, idx);
        TrimSpaces(key);
        // rpcserverip=127.0.0.1\n
        int endidx = read_buf.find('\n', idx);
        value = read_buf.substr(idx+1, endidx-idx-1);
        TrimSpaces(value);
        m_configMap.insert({key, value});
    }

    fclose(pf);
}
std::string MprpcConfig::load(std::string key)
{
    auto it = m_configMap.find(key);
    if (it == m_configMap.end())
    {
        return "";
    }
    return it->second;
}