#pragma once
#include "google/protobuf/service.h"
#include <memory>
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpConnection.h>
#include<functional>
#include<google/protobuf/descriptor.h>
#include<string>
#include<unordered_map>

// 框架提供的专门发布rpc服务的网络对象类

class RpcProvider
{
public:
    // 这里是框架提供给外部使用的，可以发布rpc方法的函数接口
    void NotifyService(google::protobuf::Service *service);

    void Run();

private:
    muduo::net::EventLoop m_eventLoop;
    //服务类型信息
    struct ServiceInfo
    {
        google::protobuf::Service *m_service;
        std::unordered_map<std::string, const google::protobuf::MethodDescriptor*> m_methodMap;//保存服务方法
    };
    std::unordered_map<std::string, ServiceInfo> m_serviceMap;



    void OnConnection(const muduo::net::TcpConnectionPtr &);
    //已经建立连接用户的读写事件回调
    void OnMessage(const muduo::net::TcpConnectionPtr &,muduo::net::Buffer *,muduo::Timestamp);
};