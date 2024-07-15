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
    addrServer.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); // 服务器地址
    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(3456); // 服务器�??�?

    char szSendBuf[1024] = "";
    char szRecvBuf[1024] = "";
    int addrLen = sizeof(SOCKADDR_IN);

    while (true) {
        printf("������Ҫ���͵�����: ");
        gets(szSendBuf);

        sendto(sockClient, szSendBuf, strlen(szSendBuf) + 1, 0, (SOCKADDR*)&addrServer, sizeof(SOCKADDR_IN));

        int nRecv = recvfrom(sockClient, szRecvBuf, 1024, 0, (SOCKADDR*)&addrServer, &addrLen);
        if (nRecv > 0) {
            szRecvBuf[nRecv] = '\0';
            printf("�������˵�����: %s\n", szRecvBuf);
        }
    }

    closesocket(sockClient);
    WSACleanup();

    return 0;
    /*
        ��ʼ��Winsock�⣺����WSAStartup��������ʼ��Winsock�⣬�Ա�ʹ�����繦�ܡ�
        ����Socket��ʹ��socket��������һ��UDP�ͻ���Socket��
        ���÷�������ַ������SOCKADDR_IN�ṹ��addrServer�������÷�������IP��ַ�Ͷ˿ڡ�
        ���ͺͽ������ݣ�
        ʹ��sendto�������û���������ݷ��͵���������
        ʹ��recvfrom�������շ������Ļظ���Ϣ��
        �ر�Socket�������ڳ������ǰ���ر�Socket������WSACleanup��������Winsock�⡣
        ��οͻ��˴���᲻�ϵ�������������û��������Ϣ�������ղ���ӡ�������Ļظ���
    */
}
