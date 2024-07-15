#include "stdafx.h"
#pragma comment(lib, "WS2_32")

#include<iostream>
using namespace std;

int main(){
    // int a = 123;
    // cout << a << endl;
    system("title TCP Server");

    //���Э��ջ�Ƿ��ʹ��
    WSADATA wsaDate;
    if(0 != WSAStartup(MAKEWORD(2,2),&wsaDate)){
        printf("error: WSAStartup() faile...\n");
        return -1;
    }

    printf("�������Ѿ�����...\n");

    //�����׽���
    SOCKET SockServer  = socket(AF_INET , SOCK_STREAM , 0);
    if(INVALID_SOCKET == SockServer){
        printf("error: socket() faile...:%d\n", WSAGetLastError());
        return -1;
    }

    //���÷�������ַ
    /*
        addrServer.sin_addr.S_un.S_addr = htonl(INADDR_ANY);: INADDR_ANY ��һ�������IP��ַ����ͨ��������ɡ��ò���ϵͳѡ��һ����ַ�����ߡ��󶨵����еĿ��õ�ַ����
        �ھ���������Internet�Ϲ����ķ�����ͨ����ʹ�����ֵ����Ϊ��������������κν����Ͻ��յ������κ�һ��IP��ַ�����ӡ�htonl �����ǽ������ֽ�˳��ת��Ϊ�����ֽ�˳��
        addrServer.sin_port = htons(2000);: ���������˷�����socketҪ�����Ķ˿ںš�htons�����������ǰ�һ��16λ���������ֽ�˳��ת��Ϊ�����ֽ�˳����Ҳ��ϰ�ߵ�������ʵ����
        �ܵ���˵����������������һ���������˵�socket��ַ��׼�����մ��κ�IP��ַ���͵��˿�2000�����ӡ�
    */
    SOCKADDR_IN addrSrever;
    addrSrever.sin_family = AF_INET;
    addrSrever.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    addrSrever.sin_port = htons(2000);

    //���׽���
    if(SOCKET_ERROR == bind(SockServer, (SOCKADDR *)&addrSrever, sizeof(SOCKADDR))){
        printf("error: bind() faile...:%d\n", WSAGetLastError());
        return -1;
    }

    //�����׽���
    if(SOCKET_ERROR == listen(SockServer, 5)){
        printf("error: listen() faile...:%d\n", WSAGetLastError());
        return -1;
    }
    printf("������������...\n");

    //��ʼ���ͻ���ַ���Ȳ���
    int len = sizeof(SOCKADDR);
    SOCKADDR_IN addrClient;
    char szSendBuf[2048] = "�Ѿ����ӷ������ɹ�";
    char szRecvBuf[2048] = "";

    //�ȴ��ͻ����������󣬽�����������
    SOCKET sockAccept = accept(SockServer, (SOCKADDR *)&addrClient, &len);
    if(INVALID_SOCKET == sockAccept){
        printf("error: accept() faile...:%d\n", WSAGetLastError());
        return -1;
    }
    //������ӳɹ��Ŀͻ�IP�Ͷ˿ں�
    cout << "Accepted client IP:[" << inet_ntoa(addrClient.sin_addr) << "], prot:[" << ntohs(addrClient.sin_port) << "]" << endl;
    printf("Accepted client IP:[%s], prot:[%d]\n",inet_ntoa(addrClient.sin_addr), ntohs(addrClient.sin_port));

    //��������
    while(true){
        recv(sockAccept,szRecvBuf,sizeof(szRecvBuf),0);
        printf("�ͻ��ˣ�%s\n",szRecvBuf);
    }
    
    closesocket(sockAccept);
    WSACleanup();
    return 0;
}

// tcp_server.cpp : �������̨Ӧ�ó������ڵ㡣
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
//     system("title TCP������");

//     //���Э��ջ�Ƿ��ʹ��
//     WSADATA wsaData;
//     if (0 != WSAStartup(MAKEWORD(2, 2), &wsaData))
//     {
//         printf("error:  WSAStartup() faile...\n");
//         return -1;
//     }

//     printf("�������Ѿ�����...\n");

//     //�����������˵��׽���
//     SOCKET SockServer = socket(AF_INET, SOCK_STREAM, 0);

//     //�����������˵ĵ�ַ
//     SOCKADDR_IN addrSrever;
//     addrSrever.sin_family = AF_INET;
//     addrSrever.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
//     addrSrever.sin_port = htons(2000);

//     //���׽���
//     if (SOCKET_ERROR == bind(SockServer, (SOCKADDR *)&addrSrever, sizeof(SOCKADDR)))
//     {
//         printf("error:  bind() faile...:%d\n", WSAGetLastError());
//         return -1;
//     }

//     //����
//     if (SOCKET_ERROR == listen(SockServer, 5))
//     {
//         printf("error:  listen() faile...:%d\n", WSAGetLastError());
//         return -1;
//     }
//     printf("������������...\n");

//     //��ʼ���ͻ���ַ���Ȳ���
//     int len = sizeof(SOCKADDR);
//     SOCKADDR_IN addrClient;
//     char szSendBuf[2048] = "�Ѿ����ӷ������ɹ�";
//     char szRecvBuf[2048] = "";

//     //����һ������ѭ���� ���ܿͻ��˵���������
//     while (true)
//     {
//         SOCKET sockAccept = accept(SockServer, (SOCKADDR *)&addrClient, &len);
//         if (INVALID_SOCKET == sockAccept)
//         {
//             printf("error:  accept() faile...:%d\n", WSAGetLastError());
//             return -1;
//         }

//         //������ӳɹ��Ŀͻ�IP�Ͷ˿ں�
//         printf("Accepted client IP:[%s], port:[%d]\n", inet_ntoa(addrClient.sin_addr), ntohs(addrClient.sin_port));

//         //�����µ��߳��������������.
//         DWORD threadID;
//         CreateThread(NULL, 0, ClientHandler, &sockAccept, 0, &threadID);
        
//         //ע�⣬������Ҫ�����Ƿ��ӳ�
//         //Sleep(100); 
//     }

//     //�ر��׽���
//     closesocket(SockServer);
//     //�ر�Э��ջ�ļ��
//     WSACleanup();

//     return 0;
// }


// tcp_server.cpp : �������̨Ӧ�ó������ڵ㡣
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
//     system("title TCP������");

//     //���Э��ջ�Ƿ��ʹ��
//     WSADATA wsaData;
//     if (0 != WSAStartup(MAKEWORD(2, 2), &wsaData))
//     {
//         printf("error:  WSAStartup() faile...\n");
//         return -1;
//     }

//     printf("�������Ѿ�����...\n");

//     //�����������˵��׽���
//     SOCKET SockServer = socket(AF_INET, SOCK_STREAM, 0);

//     //�����������˵ĵ�ַ
//     SOCKADDR_IN addrSrever;
//     addrSrever.sin_family = AF_INET;
//     addrSrever.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
//     addrSrever.sin_port = htons(2000);

//     //���׽���
//     if (SOCKET_ERROR == bind(SockServer, (SOCKADDR *)&addrSrever, sizeof(SOCKADDR)))
//     {
//         printf("error:  bind() faile...:%d\n", WSAGetLastError());
//         return -1;
//     }

//     //����
//     if (SOCKET_ERROR == listen(SockServer, 5))
//     {
//         printf("error:  listen() faile...:%d\n", WSAGetLastError());
//         return -1;
//     }
//     printf("������������...\n");

//     //��ʼ���ͻ���ַ���Ȳ���
//     int len = sizeof(SOCKADDR);
//     SOCKADDR_IN addrClient;
//     char szSendBuf[2048] = "�Ѿ����ӷ������ɹ�";
//     char szRecvBuf[2048] = "";

//     //����һ������ѭ���� ���ܿͻ��˵���������
//     while (true)
//     {
//         SOCKET sockAccept = accept(SockServer, (SOCKADDR *)&addrClient, &len);
//         if (INVALID_SOCKET == sockAccept)
//         {
//             printf("error:  accept() faile...:%d\n", WSAGetLastError());
//             return -1;
//         }

//         //������ӳɹ��Ŀͻ�IP�Ͷ˿ں�
//         printf("Accepted client IP:[%s], port:[%d]\n", inet_ntoa(addrClient.sin_addr), ntohs(addrClient.sin_port));

//         //�����µ��߳��������������.
//         THREAD_PARAMS* params = (THREAD_PARAMS*)malloc(sizeof(THREAD_PARAMS));
//         params->socket = sockAccept;
//         params->addr = addrClient;
//         DWORD threadID;
//         CreateThread(NULL, 0, ClientHandler, params, 0, &threadID);
        
//         //ע�⣬������Ҫ�����Ƿ��ӳ�
//         //Sleep(100);
//     }

//     //�ر��׽���
//     closesocket(SockServer);
//     //�ر�Э��ջ�ļ��
//     WSACleanup();

//     return 0;
// }