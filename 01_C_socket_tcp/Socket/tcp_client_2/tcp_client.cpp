// #include "stdafx.h"
// #pragma comment(lib, "ws2_32.lib")
// #include <iostream>
// using namespace std;

// int main(){
//     system("title TCP Client");
//     //���Э��ջ�Ƿ��ʹ��
//     /*
//         WSADATA wsaData;��   ���д���������һ��WSADATA���͵ı���wsaData��WSADATA������һ���ṹ�壬���ڴ洢Winsock�����ϸ��Ϣ����汾�ŵȡ�
//         if(0 != WSAStartup(MAKEWORD(2,2), &wsaData)){...}��      WSAStartup������Winsock��ĳ�ʼ����������ʹ��Winsock��֮ǰ����Ҫ���ȵ������������
//         MAKEWORD(2,2)��        ���������ָ��������ϣ��ʹ�õ�Winsock��İ汾������ָ��Ϊ2.2�汾��
//         &wsaData��             ���������һ��ָ��WSADATA������ָ�룬��WSAStartup�������óɹ�����������ᱻ���Winsock�����ϸ��Ϣ��
//         if(0 != WSAStartup(MAKEWORD(2,2), &wsaData)){...}��      ���WSAStartup�������óɹ������᷵��0�����򷵻ش����롣���ԣ����if�������ڼ��Winsock���Ƿ��ʼ���ɹ���
//     */
//     //�ܵ���˵����δ����Ŀ���ǳ�ʼ��Winsock�⣬ȷ�������������̿��Գɹ�ִ�С�������ȳ�ʼ��Winsock�⣬��ô���ں����������е��κ�Winsock�������ö����ܻ�ʧ��
//     WSADATA wsaData;
//     if(0 != WSAStartup(MAKEWORD(2, 2), &wsaData)){
//         cout << "WSAStartup failed" << endl;
//         return -1;
//     }

//     //�����ͻ��˵��׽���
//     /*
//         ��δ������ҪĿ���Ǵ���һ���׽���(socket)���׽����ǽ�������ͨ�ŵĻ�����λ������԰������Ϊ����ͨ�ŵ�һ���˵㡣
//         SOCKET sockClient = socket(AF_INET , SOCK_STREAM , 0);�����д������socket����������һ���µ��׽��֡�
//             �ú����ĵ�һ������AF_INET����ʹ�õ���IPv4��ַ��������ͨ������á�
//             �ڶ�������SOCK_STREAM��ʾ��������һ���������ӵġ��ɿ��ġ�˫��ġ������ֽ������׽��֣�һ������TCPЭ�顣
//             ������������Ϊ0���ò���ϵͳ�Զ�Ϊ����ѡ����ʵ�Э�顣
//         if(INVALID_SOCKET == sockClient){...}��socket�����ڳɹ�ʱ����һ���´������׽��ֵ������������ʧ���򷵻�INVALID_SOCKET����ˣ����if�ж��������ڼ����׽����Ƿ�ɹ�������
//         printf("error: socket() faile...:%d\n", WSAGetLastError());����������׽���ʧ�ܣ����Ǳ�����󣬲�ͨ������WSAGetLastError�����õ�������Ĵ�����롣
//         �ܵ���˵����δ�������ڴ���һ�����ӵ��׽��֣��Ա���к���������ͨ�ţ����Դ��������п��ܳ��ֵĴ�����м��ͱ���
//     */
//     SOCKET sockClient = socket(AF_INET , SOCK_STREAM , 0);
//     if(INVALID_SOCKET == sockClient){
//         printf("error: socket() faile...:%d\n", WSAGetLastError());
//         return -1;
//     }

//     //���÷�������ַ
//     /*
//         SOCKADDR_IN addrServer;������������һ��SOCKADDR_IN���͵ı���������ṹ��������Windows�������������洢һ�������ַ������IP��ַ�Ͷ˿ںţ���
//         addrServer.sin_family = AF_INET;�����õ�ַ����ΪAF_INET�����������ַ��һ��IPv4����Э��ĵ�ַ��
//         SOCKADDR_IN�ṹ��Ķ�������������ģ�
//             struct sockaddr_in {
//             short            sin_family;  // 2 bytes, address family
//             unsigned short   sin_port;    // 2 bytes, port number
//             struct in_addr   sin_addr;    // 4 bytes, IP address
//             char             sin_zero[8]; // 8 bytes, padding
//         };
//         ������ṹ�У�sin_family�ֶ�����ָ����ַ�壬����ʹ��IPv4��ַ����ֵ��Ҫ������ΪAF_INET��sin_portָ���˿ںţ�sin_addrָ��IPv4��ַ����sin_zero��Ϊ���øýṹ����SOCKADDR���ִ�С��ͬ�������ġ�
//         ����������δ��룬͸���趨sin_familyΪAF_INET����ȷ��ʵ��addrServerʹ�õ�IPv4������Э����İ棩����Э�顣
//         �ں���Ĵ����У�����Ҫ��sin_port�趨Ϊ���Ӧ�ó���Ҫʹ�õĶ˿ںţ�sin_addr�趨Ϊ����Ҫ�󶨵�IP��ַ��
//         ������addrServer������ȫ�����һ������Ӧ�ó�����Ҫʹ�õ������ַ��
//     */
//     SOCKADDR_IN addrServer;
//     addrServer.sin_family = AF_INET;

//     /*
//         ���������ʵ������������һ��sockaddr_in�ṹ�壬�ýṹ��ͨ����������InternetЭ��(IP)�ĵ�ַ��
//         ������������У�inet_addr()������htons()�����������ֱ�����IP��ַ�Ͷ˿ںţ�addrServer.sin_addr.S_un.S_addr = inet_addr(szInIP);
//         inet_addr()�������ڽ�һ�����ʮ���Ƶ�IP��ַ�ַ���(����"192.168.1.1")ת��Ϊ�������ֽ���(binary format)��ʾ��IP��ַ��
//         S_un.S_addr��sockaddr_in�ṹ�����ڴ洢�����ֽ����IP��ַ�ĳ�Ա�����д�����ζ����inet_addr()������szInIP�ַ���ת��Ϊ�����ֽ����IP��ַ��Ȼ�������ַ��ֵ��addrServer.sin_addr.S_un.S_addr��
//         addrServer.sin_port = htons(2000);
//         htons()�������ڽ������ֽ���Ķ�������ֵת��Ϊ�����ֽ��򡣶˿ں���һ��������ֵ��������Ҫ��htons()����ת�������д����ǽ�2000����˿ں�ת��Ϊ�����ֽ����ʽ�󣬸�ֵ��addrServer.sin_port��
//         ��֮�������д������������һ��IP��ַ�Ͷ˿ںŵ�һ��sockaddr_in���͵Ķ���addrServer���У�ʹ��������ں�����socket����������˵���ӵ�һ���ض��ķ������ȵȡ�
//     */
//     char szInIP[30] = "";
//     printf("������Է���IP��ַ��ͬ����������eg:127.0.0.1\nIP>>");
//     scanf("%s",szInIP);
//     addrServer.sin_addr.S_un.S_addr = inet_addr(szInIP);
//     addrServer.sin_port = htons(2000);
    
//     //���������������TCP����
//     /*
//         connect(sockClient, (SOCKADDR *)&addrServer, sizeof(SOCKADDR)): connect()������Ŀ���Ƿ��𵽷���������������
//         ���������Ҫ������������һ��������һ��socket�����������socket��֮ǰӦ���Ѿ���������
//                             �ڶ���������һ��ָ��sockaddr�ṹ��ָ�룬����ṹ����������Ҫ���ӵķ������ĵ�ַ�Ͷ˿ںţ������ַ�Ͷ˿ںž�����֮ǰ������addrServer�еģ���
//                             ������������sockaddr�ṹ�Ĵ�С��
//         ���δ�����˼�ǣ�����ͨ��֮ǰ������socket(sockClient)���ӵ�������(addrServer)���������ʧ�ܣ�����ӡ��������벢�˳�����
//     */
//     if(INVALID_SOCKET == connect(sockClient, (SOCKADDR *)&addrServer, sizeof(SOCKADDR))){
//         printf("error: connect() faile...:%d\n",WSAGetLastError());
//         return -1;
//     }

//     char szRecvBuf[2048] = "";
//     char szSendBuf[2048] = "�ͻ����Ѿ����ӳɹ���";

//     //��������
//     while(true){
//         cout << ">>";
//         scanf("%s", szSendBuf);
//         send(sockClient, szSendBuf, strlen(szSendBuf) + 1, 0);
//         /*
//             send(sockClient, szSendBuf, strlen(szSendBuf) + 1, 0); : send()������һ�������ӵ�socket�������ݡ�
//             ��һ��������Ҫ�������ݵ�socket���ڶ���������Ҫ���͵����ݣ�������������Ҫ���͵������������ĸ�����ͨ������Ϊ0����ʾû������ķ��ͷ�ʽ����
//         */
//     }
    
//     closesocket(sockClient);
//     WSACleanup();
//     int a = 26;
//     cout << a << endl;
//     WSACleanup();
//     return 0;
// }






#include "stdafx.h"
#pragma comment(lib, "ws2_32.lib")
#include <iostream>
using namespace std;

int main()
{
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in sockAddr;
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    sockAddr.sin_port = htons(5000);
    connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

    char szBuffer[MAXBYTE] = {0};

    while (true)
    {
        printf("������Ϣ: ");
        gets(szBuffer);
        send(sock, szBuffer, strlen(szBuffer)+sizeof(char), 0);

        recv(sock, szBuffer, MAXBYTE, 0);
        printf("������Ϣ: %s\n", szBuffer);
    }

    closesocket(sock);
    WSACleanup();

    return 0;
}