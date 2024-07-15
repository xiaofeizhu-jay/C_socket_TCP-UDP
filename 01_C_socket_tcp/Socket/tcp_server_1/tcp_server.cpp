#include "stdafx.h"
#pragma comment(lib, "WS2_32")
#include <windows.h>

typedef struct ThreadParams {
    SOCKET socket;
    sockaddr_in addr;
} THREAD_PARAMS;

DWORD WINAPI ClientHandler(void* pParams)
{
    THREAD_PARAMS* params = (THREAD_PARAMS*)pParams;
    char szRecvBuf[2048] = "";
    while (true)
    {
        int bytesRecv = recv(params->socket, szRecvBuf, sizeof(szRecvBuf), 0);
        if (SOCKET_ERROR == bytesRecv)
        {
            printf("Error at recv(): %d\n", WSAGetLastError());
            closesocket(params->socket);
            free(params);
            break;
        }
        else
        {
            printf("Client %s:%d: %s\n", inet_ntoa(params->addr.sin_addr), ntohs(params->addr.sin_port), szRecvBuf);
        }
    }
    return 0;
}


int main()
{
    system("title TCP服务器");

    //检查协议栈是否可使用
    WSADATA wsaData;
    if (0 != WSAStartup(MAKEWORD(2, 2), &wsaData))
    {
        printf("error:  WSAStartup() faile...\n");
        return -1;
    }

    printf("服务器已经启动...\n");

    //创建服务器端的套接字
    SOCKET SockServer = socket(AF_INET, SOCK_STREAM, 0);

    //建立服务器端的地址
    SOCKADDR_IN addrSrever;
    addrSrever.sin_family = AF_INET;
    addrSrever.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    addrSrever.sin_port = htons(2000);

    //绑定套接字
    if (SOCKET_ERROR == bind(SockServer, (SOCKADDR *)&addrSrever, sizeof(SOCKADDR)))
    {
        printf("error:  bind() faile...:%d\n", WSAGetLastError());
        return -1;
    }

    //监听
    if (SOCKET_ERROR == listen(SockServer, 5))
    {
        printf("error:  listen() faile...:%d\n", WSAGetLastError());
        return -1;
    }
    printf("服务器监听中...\n");

    //初始化客户地址长度参数
    int len = sizeof(SOCKADDR);
    SOCKADDR_IN addrClient;
    char szSendBuf[2048] = "已经连接服务器成功";
    char szRecvBuf[2048] = "";

    //进入一个无限循环， 接受客户端的连接请求
    while (true)
    {
        SOCKET sockAccept = accept(SockServer, (SOCKADDR *)&addrClient, &len);
        if (INVALID_SOCKET == sockAccept)
        {
            printf("error:  accept() faile...:%d\n", WSAGetLastError());
            return -1;
        }

        //输出连接成功的客户IP和端口号
        printf("Accepted client IP:[%s], port:[%d]\n", inet_ntoa(addrClient.sin_addr), ntohs(addrClient.sin_port));

        //启动新的线程来处理这个连接.
        THREAD_PARAMS* params = (THREAD_PARAMS*)malloc(sizeof(THREAD_PARAMS));
        params->socket = sockAccept;
        params->addr = addrClient;
        DWORD threadID;
        CreateThread(NULL, 0, ClientHandler, params, 0, &threadID);
        
        //注意，根据需要决定是否延迟
        //Sleep(100);
    }

    //关闭套接字
    closesocket(SockServer);
    //关闭协议栈的检查
    WSACleanup();

    return 0;
}