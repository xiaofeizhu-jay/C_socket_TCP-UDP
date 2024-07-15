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

// tcp_server.cpp : 定义控制台应用程序的入口点。
// #include "stdafx.h"
// #pragma comment(lib, "WS2_32")
// #include <windows.h>

// DWORD WINAPI ClientHandler(void* clientSocket)
// {
//     SOCKET aClient = *(SOCKET*)clientSocket;
//     char szRecvBuf[2048] = "";
//     while (true)
//     {
//         int bytesRecv = recv(aClient, szRecvBuf, sizeof(szRecvBuf), 0);
//         if (SOCKET_ERROR == bytesRecv)
//         {
//             printf("Error at recv(): %d\n", WSAGetLastError());
//             closesocket(aClient);
//             break;
//         }
//         else
//             printf("Client: %s\n", szRecvBuf);
//     }
//     return 0;
// }


// int main()
// {
//     system("title TCP服务器");

//     //检查协议栈是否可使用
//     WSADATA wsaData;
//     if (0 != WSAStartup(MAKEWORD(2, 2), &wsaData))
//     {
//         printf("error:  WSAStartup() faile...\n");
//         return -1;
//     }

//     printf("服务器已经启动...\n");

//     //创建服务器端的套接字
//     SOCKET SockServer = socket(AF_INET, SOCK_STREAM, 0);

//     //建立服务器端的地址
//     SOCKADDR_IN addrSrever;
//     addrSrever.sin_family = AF_INET;
//     addrSrever.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
//     addrSrever.sin_port = htons(2000);

//     //绑定套接字
//     if (SOCKET_ERROR == bind(SockServer, (SOCKADDR *)&addrSrever, sizeof(SOCKADDR)))
//     {
//         printf("error:  bind() faile...:%d\n", WSAGetLastError());
//         return -1;
//     }

//     //监听
//     if (SOCKET_ERROR == listen(SockServer, 5))
//     {
//         printf("error:  listen() faile...:%d\n", WSAGetLastError());
//         return -1;
//     }
//     printf("服务器监听中...\n");

//     //初始化客户地址长度参数
//     int len = sizeof(SOCKADDR);
//     SOCKADDR_IN addrClient;
//     char szSendBuf[2048] = "已经连接服务器成功";
//     char szRecvBuf[2048] = "";

//     //进入一个无限循环， 接受客户端的连接请求
//     while (true)
//     {
//         SOCKET sockAccept = accept(SockServer, (SOCKADDR *)&addrClient, &len);
//         if (INVALID_SOCKET == sockAccept)
//         {
//             printf("error:  accept() faile...:%d\n", WSAGetLastError());
//             return -1;
//         }

//         //输出连接成功的客户IP和端口号
//         printf("Accepted client IP:[%s], port:[%d]\n", inet_ntoa(addrClient.sin_addr), ntohs(addrClient.sin_port));

//         //启动新的线程来处理这个连接.
//         DWORD threadID;
//         CreateThread(NULL, 0, ClientHandler, &sockAccept, 0, &threadID);
        
//         //注意，根据需要决定是否延迟
//         //Sleep(100); 
//     }

//     //关闭套接字
//     closesocket(SockServer);
//     //关闭协议栈的检查
//     WSACleanup();

//     return 0;
// }


// tcp_server.cpp : 定义控制台应用程序的入口点。
// #include "stdafx.h"
// #pragma comment(lib, "WS2_32")
// #include <windows.h>

// typedef struct ThreadParams {
//     SOCKET socket;
//     sockaddr_in addr;
// } THREAD_PARAMS;

// DWORD WINAPI ClientHandler(void* pParams)
// {
//     THREAD_PARAMS* params = (THREAD_PARAMS*)pParams;
//     char szRecvBuf[2048] = "";
//     while (true)
//     {
//         int bytesRecv = recv(params->socket, szRecvBuf, sizeof(szRecvBuf), 0);
//         if (SOCKET_ERROR == bytesRecv)
//         {
//             printf("Error at recv(): %d\n", WSAGetLastError());
//             closesocket(params->socket);
//             free(params);
//             break;
//         }
//         else
//         {
//             printf("Client %s:%d: %s\n", inet_ntoa(params->addr.sin_addr), ntohs(params->addr.sin_port), szRecvBuf);
//         }
//     }
//     return 0;
// }


// int main()
// {
//     system("title TCP服务器");

//     //检查协议栈是否可使用
//     WSADATA wsaData;
//     if (0 != WSAStartup(MAKEWORD(2, 2), &wsaData))
//     {
//         printf("error:  WSAStartup() faile...\n");
//         return -1;
//     }

//     printf("服务器已经启动...\n");

//     //创建服务器端的套接字
//     SOCKET SockServer = socket(AF_INET, SOCK_STREAM, 0);

//     //建立服务器端的地址
//     SOCKADDR_IN addrSrever;
//     addrSrever.sin_family = AF_INET;
//     addrSrever.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
//     addrSrever.sin_port = htons(2000);

//     //绑定套接字
//     if (SOCKET_ERROR == bind(SockServer, (SOCKADDR *)&addrSrever, sizeof(SOCKADDR)))
//     {
//         printf("error:  bind() faile...:%d\n", WSAGetLastError());
//         return -1;
//     }

//     //监听
//     if (SOCKET_ERROR == listen(SockServer, 5))
//     {
//         printf("error:  listen() faile...:%d\n", WSAGetLastError());
//         return -1;
//     }
//     printf("服务器监听中...\n");

//     //初始化客户地址长度参数
//     int len = sizeof(SOCKADDR);
//     SOCKADDR_IN addrClient;
//     char szSendBuf[2048] = "已经连接服务器成功";
//     char szRecvBuf[2048] = "";

//     //进入一个无限循环， 接受客户端的连接请求
//     while (true)
//     {
//         SOCKET sockAccept = accept(SockServer, (SOCKADDR *)&addrClient, &len);
//         if (INVALID_SOCKET == sockAccept)
//         {
//             printf("error:  accept() faile...:%d\n", WSAGetLastError());
//             return -1;
//         }

//         //输出连接成功的客户IP和端口号
//         printf("Accepted client IP:[%s], port:[%d]\n", inet_ntoa(addrClient.sin_addr), ntohs(addrClient.sin_port));

//         //启动新的线程来处理这个连接.
//         THREAD_PARAMS* params = (THREAD_PARAMS*)malloc(sizeof(THREAD_PARAMS));
//         params->socket = sockAccept;
//         params->addr = addrClient;
//         DWORD threadID;
//         CreateThread(NULL, 0, ClientHandler, params, 0, &threadID);
        
//         //注意，根据需要决定是否延迟
//         //Sleep(100);
//     }

//     //关闭套接字
//     closesocket(SockServer);
//     //关闭协议栈的检查
//     WSACleanup();

//     return 0;
// }