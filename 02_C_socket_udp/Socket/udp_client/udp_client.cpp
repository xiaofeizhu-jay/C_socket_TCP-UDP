#include<bits/stdc++.h>
#include "stdafx.h"
#pragma comment(lib , "WS2_32")

using namespace std;

int main(){
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2),&wsaData);

    SOCKET sockClient = socket(AF_INET , SOCK_DGRAM , IPPROTO_UDP);

    SOCKADDR_IN addrClient;
    char szbuf[20] = "";
    printf("�������������IP:");
    scanf("%s",szbuf);
    addrClient.sin_addr.S_un.S_addr = inet_addr(szbuf);
    addrClient.sin_family = AF_INET;
    addrClient.sin_port = htons(3456);

    char szSendBuf[1024] = "";
    while(true){
        printf(">>");
        scanf("%s",szSendBuf);
        sendto(sockClient , szSendBuf , strlen(szSendBuf) + 1 , 0 , (SOCKADDR*)&addrClient , sizeof(SOCKADDR_IN));
        // sendto �� send ������
        // ����������������������ͨ�ŵģ����Ƕ�������ָ���������׽��ַ������ݡ�
        // ���ȣ����ǿ���sendto����������һ��ͨ�ú���������UDP��TCPЭ�顣�����и������ĺ������£�
        // sockClient: ָ������Ϣ���͵��ĸ��׽��֡�
        // szSendBuf: ���ͻ�����ָ�룬��ָ����Ҫ���͵����ݡ�
        // strlen(szSendBuf) + 1: ���͵����ݴ�С��strlen���صĳ��Ȳ������ַ����Ľ������\0������������Ҫ��1��������ǻᷢ�Ͱ�������������ڵ��ַ�����
        // 0: һ������Ϊ0����ѡ��ֵ����MSG_OOB�����͡��������ݡ����ȡ�
        // (SOCKADDR*)&addrClient: ָ�������ݽ��շ��ĵ�ַ��
        // sizeof(SOCKADDR_IN): ����addrClient�ĳ��ȡ�
        // ��send����������TCPЭ�飬��ΪTCP���������ӵģ���ζ���ڷ�������֮ǰ������һ���ѽ��������ӡ�������ʹ��send����ʱ������Ҫ��ָ�����շ��ĵ�ַ����ΪTCP�����ڽ�����ʱ����Ѿ���ȷ�����ݵĽ��շ���
        // ���ԣ�send����ȱ���˺�������������
        // ��ʹ��UDPЭ�飨�����ݱ�Э�飩ʱ��ÿ�����͵����ݰ�����Ҫָ�����շ��ĵ�ַ����ΪUDP�������ӵģ�ÿ�����ݰ��ķ��Ͷ��Ƕ����ġ�������Ҫʹ��sendto������
        // ����TCPЭ���У�����ʹ��send��������Ϊ����ȷ�����Ӵ��ڡ�
        // ���Ի����ϣ�����Խ�sendto�����Ǹ�ͨ�õķ��ͺ��������ȿ��������Ѿ��������ӵ�Э�飨��TCP����Ҳ�������������ӵ�Э�飨��UDP������send������ֻ�������Ѿ��������ӵ�Э�飨��TCP����
    }
    closesocket(sockClient);
    WSACleanup();
    return 0;
}