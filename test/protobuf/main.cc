#include<iostream>
#include<string>
#include "test.pb.h"
using namespace fixbug;


#if 0
int main()
{
    //封装了login请求的数据
    LoginRequest req;
    req.set_name("zhang san");
    req.set_pwd("12456");
    std::string send_str;
    //对象数据序列化=>char*
    if(req.SerializeToString(&send_str))
    {
        std::cout << send_str.c_str() << std::endl;
    }
    //从send_str反序列化一个login请求对象
    LoginRequest reqB;
    
     if(reqB.ParseFromString(send_str))
     {
        std::cout << reqB.name() << std::endl;
        std::cout << reqB.pwd() << std::endl;
     }
    return 0;
}
#endif

int main()
{
    // LoginResponse rsp;
    // ResultCode *rc = rsp.mutable_result();
    // rc->set_errcode(1);
    // rc->set_errmsg("登录处理失败");
    GetFriendListResponse rsp;
    ResultCode *rc = rsp.mutable_result();
    rc->set_errcode(0);
    return 0;
}
