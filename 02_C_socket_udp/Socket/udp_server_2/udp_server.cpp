#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "WS2_32")

int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET sockServer = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockServer == INVALID_SOCKET) {
        printf("socket error\n");
        return 0;
    }

    SOCKADDR_IN addrServer;
    addrServer.sin_addr.S_un.S_addr = INADDR_ANY;
    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(3456);

    if (SOCKET_ERROR == bind(sockServer, (SOCKADDR*)&addrServer, sizeof(SOCKADDR_IN))) {
        printf("bind error\n");
        return -1;
    }

    SOCKADDR_IN addrClient;
    int len = sizeof(SOCKADDR_IN);
    char szRecvBuf[1024] = "";

    while (true) {
        int nRecv = recvfrom(sockServer, szRecvBuf, 1024, 0, (SOCKADDR*)&addrClient, &len);
        if (nRecv > 0) {
            szRecvBuf[nRecv] = '\0';
            printf("接收到的数据(%s): %s\n", inet_ntoa(addrClient.sin_addr), szRecvBuf);
            
            // 发送回复消息给客户端
            char szReply[1024] = "";
            printf("请输入要发送的数据: ");
            gets(szReply);
            sendto(sockServer, szReply, strlen(szReply) + 1, 0, (SOCKADDR*)&addrClient, sizeof(SOCKADDR_IN));
        }
    }

    closesocket(sockServer);
    WSACleanup();

    return 0;
}
/*
    初始化Winsock库：调用WSAStartup函数来初始化Winsock库，以便使用网络功能。
    创建Socket：使用socket函数创建一个UDP服务器Socket。
    绑定Socket：定义SOCKADDR_IN结构体addrServer，并将其绑定到服务器的IP地址和端口上。这里使用INADDR_ANY表示服务器可以接收任意网络接口上的数据。
    接收和发送数据：
    使用recvfrom函数接收客户端发送的消息，并打印消息内容和客户端的IP地址。
    使用sendto函数发送回复消息给客户端，确认接收到消息。
    关闭Socket并清理：在程序结束前，关闭Socket并调用WSACleanup函数清理Winsock库。
    这个UDP服务器将不断地接收客户端发送的消息，并发送回复消息确认接收到客户端的消息。
*/