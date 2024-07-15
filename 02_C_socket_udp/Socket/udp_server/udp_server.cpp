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
            printf("���յ�������(%s)��%s\n",inet_ntoa(addrClient.sin_addr),szRecvBuf);
        }
    }
    /*
    ��Ҫ��ͬ��
    Э�����ͣ�
        recvfrom����UDP�������ӵ�Э�飬������Ҫ֪��������Դ��
        recv����TCP���������ӵ�Э�飬���Բ���Ҫ����������Դ��
    �������ͣ�
        recvfrom��from��fromlen���������ڴ洢���ͷ���ַ��Ϣ��
        recvû����Щ��������ΪTCP�����Ѿ������˶Է�����Ϣ��
    ʹ�ó�����
        recvfrom���ڴ�����ͻ��˽������ݣ������������ӵ�UDPͨ�š�
        recv���ڽ����Ѿ��������ӵ�TCPͨ���е����ݣ��������������ӵ�TCPͨ�š�
    �ܵ���˵�������������������Ϊ����Ӧ��ͬ���͵�����Э�飬ͨ���˽����ǵ������ʹ�÷��������Ը��õر�д�ɿ�������Ӧ�ó���
    */
    closesocket(sockServer);
    WSACleanup();
    return 0;
}