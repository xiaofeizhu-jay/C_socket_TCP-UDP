#include "stdafx.h"
#pragma comment(lib , "WS2_32")
#include <windows.h>
#include <iostream>

//...
DWORD WINAPI HandlerThread(LPVOID lpParameter){
    SOCKET sockConn = (SOCKET)lpParameter;
    char szRecvBuffer[MAXBYTE] = {0};
    char szSendBuffer[MAXBYTE] = {0};
    int iLen = 0;

    while (true)
    {
        iLen = recv(sockConn, szRecvBuffer, MAXBYTE, 0);
        if(iLen <= 0){
            break;
        }
        // ������յ���Ϣ 
        printf("�ͻ��˷��͵���Ϣ: %s\n", szRecvBuffer);
        // �Ӽ��̶�ȡ��Ӧ
        printf("������Ҫ���͵��ͻ��˵���Ϣ: ");
        gets(szSendBuffer);
        send(sockConn, szSendBuffer, strlen(szSendBuffer)+sizeof(char), 0);
    }

    closesocket(sockConn);
    
    return 0;
}

int main()
{
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in addrSrv;
    addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(5000);
    bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));

    listen(sockSrv, 5);

    SOCKADDR newAddr;
    int len = sizeof(SOCKADDR);

    while (true)
    {
        SOCKET newClient;
        newClient = accept(sockSrv, (SOCKADDR*)&newAddr, &len);
        printf("�����ӿͻ���: %s \n", inet_ntoa(((struct sockaddr_in*) &newAddr)->sin_addr));

        CreateThread(NULL, 0, HandlerThread, (LPVOID)newClient, 0, NULL);  // �������߳��������¿ͻ���
    }

    closesocket(sockSrv);
    WSACleanup();

    return 0;
}