#include "stdfax.h"
#pragma comment(lib , "WS2_32")

int main(){
    WSADATA wsaDate;
    WSAStartup(MAKEWORD(2,2),&wsaDate);

    SOCKET sockServer = socket(AF_INET , SOCK_DGRAM , IPPROTO_UDP);

    if(sockServer == INVALID_SOCKET){
        printf("socket error\n");
        return 0;
    }

    SOCKADDR_IN addrServer;
    addrServer.sin_addr.S_un.S_addr = INADDR_ANY;
    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(3456);

    if(SOCKET_ERROR == bind(sockServer , (SOCKADDR*)&addrServer , sizeof(SOCKADDR_IN)))
    {
        printf("bind error\n");
        return 0;
    }

    char szRecvBuf[1024] = "";
    SOCKADDR_IN addrClient;
    int len = sizeof(SOCKADDR_IN);

    while(true){
        int nRecv = recvfrom(sockServer , szRecvBuf , 1024 , 0 , (SOCKADDR*)&addrClient , &len);
        if(nRecv > 0){
            szRecvBuf[nRecv] = '\n';
            printf("接收到的数据(%s)：%s\n",inet_ntoa(addrClient.sin_addr),szRecvBuf);
        }
    }
    /*
    主要不同点
    协议类型：
        recvfrom用于UDP，无连接的协议，所以需要知道数据来源。
        recv用于TCP，面向连接的协议，所以不需要担心数据来源。
    参数解释：
        recvfrom有from和fromlen参数，用于存储发送方地址信息。
        recv没有这些参数，因为TCP连接已经包含了对方的信息。
    使用场景：
        recvfrom用于从任意客户端接收数据，适用于无连接的UDP通信。
        recv用于接收已经建立连接的TCP通道中的数据，适用于面向连接的TCP通信。
    总的来说，这两个函数的设计是为了适应不同类型的网络协议，通过了解它们的区别和使用方法，可以更好地编写可靠的网络应用程序。
    */
    closesocket(sockServer);
    WSACleanup();
    return 0;
}