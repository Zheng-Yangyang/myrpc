#include "rpcprovider.h"
#include<string>
#include "mprpcapplication.h"
#include<functional>
#include<google/protobuf/descriptor.h>


/*
service_name => service描述
                        =>  service* 记录服务对象
                        methon_name => method方法对象
*/
void RpcProvider::NotifyService(google::protobuf::Service *service) 
{
    ServiceInfo service_info;
    const google::protobuf::ServiceDescriptor *pserviceDesc = service->GetDescriptor();
    std::string service_name = pserviceDesc->name();
    //获取服务对象的方法的数量
    int methodCnt = pserviceDesc->method_count();

    std::cout << "service_name" << service_name << std::endl;
    
    for(int i = 0; i < methodCnt; ++ i)
    {
        //获取了服务对象指定下标服务方法的描述
        const google::protobuf::MethodDescriptor* pmethodDesc = pserviceDesc->method(i);
        std::string method_name = pmethodDesc->name();
        service_info.m_methodMap.insert({method_name, pmethodDesc});
        std::cout << "method_name" << method_name << std::endl;
    }
    service_info.m_service = service;
    m_serviceMap.insert({service_name, service_info});
}

void RpcProvider::Run() 
{
    std::string ip = MprpcApplication::GetInstance().GetConfig().Load("rpcserverip");
    uint16_t port = atoi(MprpcApplication::GetInstance().GetConfig().Load("rpcserverport").c_str());
    muduo::net::InetAddress address(ip, port);
    //创建Tcpserver对象
    muduo::net::TcpServer server(&m_eventLoop, address, "RpcProvider");
    //绑定连接回调和消息读写回调方法
    //设置muduo库的线程数量
    server.setConnectionCallback(std::bind(&RpcProvider::OnConnection, this, std::placeholders::_1));
    server.setMessageCallback(std::bind(&RpcProvider::OnMessage, this, std::placeholders::_1, 
    std::placeholders::_2, std::placeholders::_3));
    server.setThreadNum(4);
    std::cout << "RpcProvider start service at ip:" << ip << " port:" <<  port << std::endl;
    //启动网络服务
    server.start();
    m_eventLoop.loop();
}

void RpcProvider::OnConnection(const muduo::net::TcpConnectionPtr &conn)
{

}
void RpcProvider::OnMessage(const muduo::net::TcpConnectionPtr &,muduo::net::Buffer *,muduo::Timestamp)
{

}