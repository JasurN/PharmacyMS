#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#define PORT 8080
int main(int argc, char const *argv[]) {
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0}, cchat[1024];
    char *bye = "bye";
    printf("CREATING CLIENT SOCKET .....\n");
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
    printf("DEFINING SOCKET FAMILY, ADDRESS & PORT .....\n");
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
// Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
    printf("CLIENT CONNECTING ON PORT 8080 TO COMMUNICATE WITH SERVER..\n");
    if (connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
    send(sock, hello, strlen(hello), 0);
    printf("Hello message sent\n");
    valread = read(sock, buffer, 1024);
    printf("%s\n", buffer);
    printf(" Ready for Chat....\n");
    while (1) {
        memset(buffer, 0, sizeof(buffer));
        memset(cchat, 0, sizeof(cchat));
        printf("CLIENT : ");
        fgets(cchat, sizeof(cchat), stdin);
        send(sock, cchat, strlen(cchat), 0);
        valread = read(sock, buffer, 1024);
        printf("%s\n", buffer);
        cchat[strlen(cchat)] = '\0';
        if (strncmp(cchat, bye, strlen(bye)) == 0)
            break;
    }
    return 0;
}