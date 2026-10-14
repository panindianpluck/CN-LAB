#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int server, newSock;
    char buffer[1024];
    struct sockaddr_in servAddr;
    struct sockaddr_storage store;
    socklen_t addrsize;

    server = socket(AF_INET, SOCK_STREAM, 0);
    
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(6265);
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(server, (struct sockaddr*)&servAddr, sizeof(servAddr));

    if (listen(server, 5) == 0)
        printf("listening\n");
    else
        printf("error\n");

    addrsize = sizeof(store);
    newSock = accept(server, (struct sockaddr*)&store, &addrsize);
    
    recv(newSock, buffer, 1024, 0);
    printf("2.data recieved:%s\n", buffer);

    strcpy(buffer, "hi this is server\n");
    send(newSock, buffer, strlen(buffer) + 1, 0);

    close(newSock);
    close(server);
    return 0;
}