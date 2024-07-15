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
    printf("请输入服务器的IP:");
    scanf("%s",szbuf);
    addrClient.sin_addr.S_un.S_addr = inet_addr(szbuf);
    addrClient.sin_family = AF_INET;
    addrClient.sin_port = htons(3456);

    char szSendBuf[1024] = "";
    while(true){
        printf(">>");
        scanf("%s",szSendBuf);
        sendto(sockClient , szSendBuf , strlen(szSendBuf) + 1 , 0 , (SOCKADDR*)&addrClient , sizeof(SOCKADDR_IN));
        // sendto 和 send 的区别：
        // 这两个函数都是用于网络通信的，它们都用于向指定的网络套接字发送数据。
        // 首先，我们看看sendto函数。这是一个通用函数，用于UDP和TCP协议。函数中各参数的含义如下：
        // sockClient: 指定将消息发送到哪个套接字。
        // szSendBuf: 发送缓冲区指针，即指向你要发送的数据。
        // strlen(szSendBuf) + 1: 发送的数据大小。strlen返回的长度不包含字符串的结束标记\0，所以我们需要加1，因此我们会发送包括结束标记在内的字符串。
        // 0: 一般设置为0，可选的值还有MSG_OOB（发送“带外数据”）等。
        // (SOCKADDR*)&addrClient: 指定了数据接收方的地址。
        // sizeof(SOCKADDR_IN): 参数addrClient的长度。
        // 而send函数特制于TCP协议，因为TCP是面向连接的，意味着在发送数据之前必须有一个已建立的连接。所以在使用send函数时，不需要再指定接收方的地址，因为TCP连接在建立的时候就已经明确了数据的接收方。
        // 所以，send函数缺少了后面两个参数。
        // 在使用UDP协议（即数据报协议）时，每个发送的数据包都需要指定接收方的地址，因为UDP是无连接的，每个数据包的发送都是独立的。所以需要使用sendto函数。
        // 而在TCP协议中，我们使用send函数，因为有明确的连接存在。
        // 所以基本上，你可以将sendto看作是更通用的发送函数，它既可以用于已经建立连接的协议（如TCP），也可以用于无连接的协议（如UDP）。而send函数则只能用于已经建立连接的协议（如TCP）。
    }
    closesocket(sockClient);
    WSACleanup();
    return 0;
}