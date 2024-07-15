#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "WS2_32")

int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET sockClient = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockClient == INVALID_SOCKET) {
        printf("socket error\n");
        return 0;
    }

    SOCKADDR_IN addrServer;
    addrServer.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); // 鏈嶅姟鍣ㄥ湴鍧�
    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(3456); // 鏈嶅姟鍣ㄧ??鍙?

    char szSendBuf[1024] = "";
    char szRecvBuf[1024] = "";
    int addrLen = sizeof(SOCKADDR_IN);

    while (true) {
        printf("请输入要发送的数据: ");
        gets(szSendBuf);

        sendto(sockClient, szSendBuf, strlen(szSendBuf) + 1, 0, (SOCKADDR*)&addrServer, sizeof(SOCKADDR_IN));

        int nRecv = recvfrom(sockClient, szRecvBuf, 1024, 0, (SOCKADDR*)&addrServer, &addrLen);
        if (nRecv > 0) {
            szRecvBuf[nRecv] = '\0';
            printf("服务器端的数据: %s\n", szRecvBuf);
        }
    }

    closesocket(sockClient);
    WSACleanup();

    return 0;
    /*
        初始化Winsock库：调用WSAStartup函数来初始化Winsock库，以便使用网络功能。
        创建Socket：使用socket函数创建一个UDP客户端Socket。
        设置服务器地址：定义SOCKADDR_IN结构体addrServer，并设置服务器的IP地址和端口。
        发送和接收数据：
        使用sendto函数将用户输入的数据发送到服务器。
        使用recvfrom函数接收服务器的回复消息。
        关闭Socket并清理：在程序结束前，关闭Socket并调用WSACleanup函数清理Winsock库。
        这段客户端代码会不断地向服务器发送用户输入的消息，并接收并打印服务器的回复。
    */
}
