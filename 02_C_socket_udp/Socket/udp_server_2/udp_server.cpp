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
            printf("���յ�������(%s): %s\n", inet_ntoa(addrClient.sin_addr), szRecvBuf);
            
            // ���ͻظ���Ϣ���ͻ���
            char szReply[1024] = "";
            printf("������Ҫ���͵�����: ");
            gets(szReply);
            sendto(sockServer, szReply, strlen(szReply) + 1, 0, (SOCKADDR*)&addrClient, sizeof(SOCKADDR_IN));
        }
    }

    closesocket(sockServer);
    WSACleanup();

    return 0;
}
/*
    ��ʼ��Winsock�⣺����WSAStartup��������ʼ��Winsock�⣬�Ա�ʹ�����繦�ܡ�
    ����Socket��ʹ��socket��������һ��UDP������Socket��
    ��Socket������SOCKADDR_IN�ṹ��addrServer��������󶨵���������IP��ַ�Ͷ˿��ϡ�����ʹ��INADDR_ANY��ʾ���������Խ�����������ӿ��ϵ����ݡ�
    ���պͷ������ݣ�
    ʹ��recvfrom�������տͻ��˷��͵���Ϣ������ӡ��Ϣ���ݺͿͻ��˵�IP��ַ��
    ʹ��sendto�������ͻظ���Ϣ���ͻ��ˣ�ȷ�Ͻ��յ���Ϣ��
    �ر�Socket�������ڳ������ǰ���ر�Socket������WSACleanup��������Winsock�⡣
    ���UDP�����������ϵؽ��տͻ��˷��͵���Ϣ�������ͻظ���Ϣȷ�Ͻ��յ��ͻ��˵���Ϣ��
*/