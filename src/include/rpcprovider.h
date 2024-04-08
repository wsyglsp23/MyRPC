#pragma once
#include"google/protobuf/service.h"
#include<google/protobuf/descriptor.h>
#include<muduo/net/TcpServer.h>
#include<muduo/net/EventLoop.h>
#include<muduo/net/InetAddress.h> 
#include<muduo/net/TcpConnection.h>

#include<unordered_map>
#include<memory>
#include<string>
#include<iostream>
class RpcProvider
{
public:
    void NotifyService(google::protobuf::Service * service);
    void Run();
private:
    muduo::net::EventLoop m_eventLoop;

    //service服务类型信息
    struct ServiceInfo
    {
        //保存服务对象
        google::protobuf::Service *m_service;
        std::unordered_map<std::string,const google::protobuf::MethodDescriptor*> m_methodMap;
    };
    //存储注册成功的服务对象和其服务方法的所有信息
    std::unordered_map<std::string ,ServiceInfo> m_serviceMap;
    void OnConnection(const muduo::net::TcpConnectionPtr&);
    void OnMessage(const muduo::net::TcpConnectionPtr&,muduo::net::Buffer*,muduo::Timestamp);
};