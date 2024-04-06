#include <iostream>
#include <string>
#include "user.pb.h"


class UserService : public fixbug::UserServiceRpc
{
public:
    bool Login(std::string name, std::string pwd)
    {
        std::cout << " doing local service: Login" << std::endl;
        std::cout << " name :" << name << "pwd: " << pwd << std::endl;       
    }
    void Login(::google::protobuf::RpcController* controller,
                       const ::fixbug::LoginRequest* request,
                       ::fixbug::LoginResponse* response,
                       ::google::protobuf::Closure* done)
    {
        std::string name = request->name();
        std::string pwd = request->pwd();
        
        //这里就是提供服务
        bool login_result = Login(name,pwd);

        //把响应写入
        fixbug::ResultCode * code = response->mutable_result();
        code->set_errcode(0);
        code->set_errmsg("");
        response->set_sucess(login_result);

        //执行回调函数，目测是序列化和转发 
        done->Run();
    }
    
};


int main()
{


    return 0;
}