#include "stdafx.h"
#pragma comment(lib, "WS2_32")

#include<iostream>
using namespace std;

int main(){
    // int a = 123;
    // cout << a << endl;
    system("title TCP Server");

    //检查协议栈是否可使用
    WSADATA wsaDate;
    if(0 != WSAStartup(MAKEWORD(2,2),&wsaDate)){
        printf("error: WSAStartup() faile...\n");
        return -1;
    }

    printf("服务器已经启动...\n");

    //创建套接字
    SOCKET SockServer  = socket(AF_INET , SOCK_STREAM , 0);
    if(INVALID_SOCKET == SockServer){
        printf("error: socket() faile...:%d\n", WSAGetLastError());
        return -1;
    }

    //设置服务器地址
    /*
        addrServer.sin_addr.S_un.S_addr = htonl(INADDR_ANY);: INADDR_ANY 是一个特殊的IP地址，它通常被翻译成“让操作系统选择一个地址”或者“绑定到所有的可用地址”。
        在局域网或者Internet上工作的服务器通常会使用这个值，因为它允许服务器在任何介面上接收到来自任何一个IP地址的连接。htonl 函数是将主机字节顺序转换为网络字节顺序。
        addrServer.sin_port = htons(2000);: 这行设置了服务器socket要监听的端口号。htons函数的作用是把一个16位数由主机字节顺序转换为网络字节顺序，这也是习惯的网络编程实践。
        总的来说，这个代码段在设置一个服务器端的socket地址，准备接收从任何IP地址发送到端口2000的连接。
    */
    SOCKADDR_IN addrSrever;
    addrSrever.sin_family = AF_INET;
    addrSrever.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    addrSrever.sin_port = htons(2000);

    //绑定套接字
    if(SOCKET_ERROR == bind(SockServer, (SOCKADDR *)&addrSrever, sizeof(SOCKADDR))){
        printf("error: bind() faile...:%d\n", WSAGetLastError());
        return -1;
    }

    //监听套接字
    if(SOCKET_ERROR == listen(SockServer, 5)){
        printf("error: listen() faile...:%d\n", WSAGetLastError());
        return -1;
    }
    printf("服务器监听中...\n");

    //初始化客户地址长度参数
    int len = sizeof(SOCKADDR);
    SOCKADDR_IN addrClient;
    char szSendBuf[2048] = "已经连接服务器成功";
    char szRecvBuf[2048] = "";

    //等待客户的连接请求，接受请求连接
    SOCKET sockAccept = accept(SockServer, (SOCKADDR *)&addrClient, &len);
    if(INVALID_SOCKET == sockAccept){
        printf("error: accept() faile...:%d\n", WSAGetLastError());
        return -1;
    }
    //输出连接成功的客户IP和端口号
    cout << "Accepted client IP:[" << inet_ntoa(addrClient.sin_addr) << "], prot:[" << ntohs(addrClient.sin_port) << "]" << endl;
    printf("Accepted client IP:[%s], prot:[%d]\n",inet_ntoa(addrClient.sin_addr), ntohs(addrClient.sin_port));

    //发送数据
    while(true){
        recv(sockAccept,szRecvBuf,sizeof(szRecvBuf),0);
        printf("客户端：%s\n",szRecvBuf);
    }
    
    closesocket(sockAccept);
    WSACleanup();
    return 0;
}
