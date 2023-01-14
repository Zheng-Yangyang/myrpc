#include <iostream>
#include <string>
#include "user.pb.h"

class UserService : public fixbug::UserServiceRpc
{
public:
    bool Login(std::string name, std::string pwd)
    {
        std::cout << "doing local service: Login" << std::endl;
        std::cout << "name:" << name << "pwd" << pwd << std::endl;
        return true;
    }
    //1.caller ===> Login(Login)
    void Login(::google::protobuf::RpcController *controller,
               const ::fixbug::LoginRequest *request,
               ::fixbug::LoginResponse *response,
               ::google::protobuf::Closure *done)
    {
        std::string name = request->name();
        std::string pwd = request->pwd();
        bool login_result = Login(name, pwd);//做本地业务
        //把响应写入
        fixbug::ResultCode *code = response->mutable_result();
        code->set_errcode(0);
        code->set_errmsg("");
        response->set_success(login_result);
        done->Run();
    }
};

int main()
{
    UserService us;
    us.Login("xxx", "xxx");
    return 0;
}