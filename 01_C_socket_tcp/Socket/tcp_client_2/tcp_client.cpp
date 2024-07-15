// #include "stdafx.h"
// #pragma comment(lib, "ws2_32.lib")
// #include <iostream>
// using namespace std;

// int main(){
//     system("title TCP Client");
//     //检查协议栈是否可使用
//     /*
//         WSADATA wsaData;：   这行代码声明了一个WSADATA类型的变量wsaData。WSADATA类型是一个结构体，用于存储Winsock库的详细信息，如版本号等。
//         if(0 != WSAStartup(MAKEWORD(2,2), &wsaData)){...}：      WSAStartup函数是Winsock库的初始化函数，在使用Winsock库之前，需要首先调用这个函数。
//         MAKEWORD(2,2)：        这个宏用于指定调用者希望使用的Winsock库的版本，这里指定为2.2版本。
//         &wsaData：             这个参数是一个指向WSADATA变量的指针，当WSAStartup函数调用成功后，这个变量会被填充Winsock库的详细信息。
//         if(0 != WSAStartup(MAKEWORD(2,2), &wsaData)){...}：      如果WSAStartup函数调用成功，它会返回0，否则返回错误码。所以，这个if语句就是在检查Winsock库是否初始化成功。
//     */
//     //总的来说，这段代码的目的是初始化Winsock库，确保后续的网络编程可以成功执行。如果不先初始化Winsock库，那么你在后续网络编程中的任何Winsock函数调用都可能会失败
//     WSADATA wsaData;
//     if(0 != WSAStartup(MAKEWORD(2, 2), &wsaData)){
//         cout << "WSAStartup failed" << endl;
//         return -1;
//     }

//     //创建客户端的套接字
//     /*
//         这段代码的主要目的是创建一个套接字(socket)。套接字是进行网络通信的基本单位，你可以把它理解为网络通信的一个端点。
//         SOCKET sockClient = socket(AF_INET , SOCK_STREAM , 0);：这行代码调用socket函数来创建一个新的套接字。
//             该函数的第一个参数AF_INET代表使用的是IPv4地址，在网络通信中最常用。
//             第二个参数SOCK_STREAM表示创建的是一个面向连接的、可靠的、双向的、基于字节流的套接字，一般用于TCP协议。
//             第三个参数设为0，让操作系统自动为我们选择合适的协议。
//         if(INVALID_SOCKET == sockClient){...}：socket函数在成功时返回一个新创建的套接字的描述符，如果失败则返回INVALID_SOCKET。因此，这个if判断语句就是在检查该套接字是否成功创建。
//         printf("error: socket() faile...:%d\n", WSAGetLastError());：如果创建套接字失败，我们报告错误，并通过调用WSAGetLastError函数得到更具体的错误代码。
//         总的来说，这段代码就是在创建一个连接的套接字，以便进行后续的网络通信，并对创建过程中可能出现的错误进行检测和报告
//     */
//     SOCKET sockClient = socket(AF_INET , SOCK_STREAM , 0);
//     if(INVALID_SOCKET == sockClient){
//         printf("error: socket() faile...:%d\n", WSAGetLastError());
//         return -1;
//     }

//     //设置服务器地址
//     /*
//         SOCKADDR_IN addrServer;：这行声明了一个SOCKADDR_IN类型的变量，这个结构体类型在Windows网络编程中用来存储一个网络地址（包括IP地址和端口号）。
//         addrServer.sin_family = AF_INET;：设置地址类型为AF_INET，表明这个地址是一个IPv4网络协议的地址。
//         SOCKADDR_IN结构体的定义大致是这样的：
//             struct sockaddr_in {
//             short            sin_family;  // 2 bytes, address family
//             unsigned short   sin_port;    // 2 bytes, port number
//             struct in_addr   sin_addr;    // 4 bytes, IP address
//             char             sin_zero[8]; // 8 bytes, padding
//         };
//         在这个结构中，sin_family字段用于指定地址族，对于使用IPv4地址，其值需要被设置为AF_INET。sin_port指定端口号，sin_addr指定IPv4地址。而sin_zero是为了让该结构体与SOCKADDR保持大小相同而保留的。
//         所以上面这段代码，透过设定sin_family为AF_INET，明确了实例addrServer使用的IPv4（网际协议第四版）网络协议。
//         在后面的代码中，还需要把sin_port设定为你的应用程序将要使用的端口号，sin_addr设定为你想要绑定的IP地址。
//         这样，addrServer就能完全构造出一个我们应用程序需要使用的网络地址。
//     */
//     SOCKADDR_IN addrServer;
//     addrServer.sin_family = AF_INET;

//     /*
//         这两句代码实质上是在设置一个sockaddr_in结构体，该结构体通常用于描述Internet协议(IP)的地址。
//         在这个上下文中，inet_addr()函数和htons()函数被用来分别设置IP地址和端口号：addrServer.sin_addr.S_un.S_addr = inet_addr(szInIP);
//         inet_addr()函数用于将一个点分十进制的IP地址字符串(比如"192.168.1.1")转换为用网络字节序(binary format)表示的IP地址。
//         S_un.S_addr是sockaddr_in结构中用于存储网络字节序的IP地址的成员。这行代码意味着用inet_addr()函数将szInIP字符串转化为网络字节序的IP地址，然后将这个地址赋值给addrServer.sin_addr.S_un.S_addr。
//         addrServer.sin_port = htons(2000);
//         htons()函数用于将主机字节序的短整型数值转换为网络字节序。端口号是一个短整型值，所以需要用htons()进行转换。此行代码是将2000这个端口号转换为网络字节序格式后，赋值给addrServer.sin_port。
//         总之，这两行代码就是在设置一个IP地址和端口号到一个sockaddr_in类型的对象（addrServer）中，使其可以用于后续的socket操作，比如说连接到一个特定的服务器等等。
//     */
//     char szInIP[30] = "";
//     printf("请输入对方的IP地址（同局域网）：eg:127.0.0.1\nIP>>");
//     scanf("%s",szInIP);
//     addrServer.sin_addr.S_un.S_addr = inet_addr(szInIP);
//     addrServer.sin_port = htons(2000);
    
//     //请求与服务器建立TCP连接
//     /*
//         connect(sockClient, (SOCKADDR *)&addrServer, sizeof(SOCKADDR)): connect()函数的目的是发起到服务器的连接请求。
//         这个函数需要三个参数：第一个参数是一个socket描述符，这个socket在之前应该已经被创建；
//                             第二个参数是一个指向sockaddr结构的指针，这个结构包含了你想要连接的服务器的地址和端口号（这个地址和端口号就是你之前设置在addrServer中的）；
//                             第三个参数是sockaddr结构的大小。
//         整段代码意思是，尝试通过之前创建的socket(sockClient)连接到服务器(addrServer)，如果连接失败，将打印出错误代码并退出程序。
//     */
//     if(INVALID_SOCKET == connect(sockClient, (SOCKADDR *)&addrServer, sizeof(SOCKADDR))){
//         printf("error: connect() faile...:%d\n",WSAGetLastError());
//         return -1;
//     }

//     char szRecvBuf[2048] = "";
//     char szSendBuf[2048] = "客户端已经连接成功！";

//     //发送数据
//     while(true){
//         cout << ">>";
//         scanf("%s", szSendBuf);
//         send(sockClient, szSendBuf, strlen(szSendBuf) + 1, 0);
//         /*
//             send(sockClient, szSendBuf, strlen(szSendBuf) + 1, 0); : send()函数向一个已连接的socket发送数据。
//             第一个参数是要发送数据的socket，第二个参数是要发送的数据，第三个参数是要发送的数据量，第四个参数通常设置为0（表示没有特殊的发送方式）。
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
        printf("发送消息: ");
        gets(szBuffer);
        send(sock, szBuffer, strlen(szBuffer)+sizeof(char), 0);

        recv(sock, szBuffer, MAXBYTE, 0);
        printf("接收消息: %s\n", szBuffer);
    }

    closesocket(sock);
    WSACleanup();

    return 0;
}