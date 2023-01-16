#include <iostream>
#include "mprpcapplication.h"
#include "user.pb.h"
#include "mprpcchannel.h"

int main(int argc, char **argv)
{
    MprpcApplication::Init(argc, argv);
    fixbug::UserServiceRpc_Stub stub(new MprpcChannel());
    fixbug::LoginRequest request;
    request.set_name("zhang san");
    request.set_pwd("123456");
    fixbug::LoginResponse response;
    // 发起rpc方法的调用 同步的rpc方法
    stub.Login(nullptr, &request, &response, nullptr);
    if (0 == response.result().errcode())
    {
        std::cout << "rpc login response success" << response.success() << std::endl;
    }
    else
    {
        std::cout << "rpc login response error : " << response.result().errmsg() << std::endl;
    }

    fixbug::RegisterRequest req;
    req.set_id(2000);
    req.set_name("mprpc");
    req.set_pwd("66666");
    fixbug::RegisterResponse rsp;
    stub.Register(nullptr, &req, &rsp, nullptr);
    if (0 == rsp.result().errcode())
    {
        std::cout << "rpc register response success" << rsp.success() << std::endl;
    }
    else
    {
        std::cout << "rpc register response error : " << rsp.result().errmsg() << std::endl;
    }
    return 0;
}