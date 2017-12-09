#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 8080
int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0}, schat[1024];
    char *hello = "Hello from server";

    char *bye = "bye";
    printf("CREATING SERVER SOCKET .....\n");
// Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    printf("DEFINING SERVER SOCKET OPTIONS, FAMILY, ADDRESS & PORT .....\n");
// Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("setsockopt failed");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    printf("BINDING SERVER SOCKET TO PORT 8080 .....\n");
// Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("socket bind failed");
        exit(EXIT_FAILURE);
    }
    printf("SERVER LISTENING ON PORT 8080 FOR NEW CONNECTION.....\n");
    if (listen(server_fd, 3) < 0)
    {
        perror("sockeet listen failed ");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                             (socklen_t*)&addrlen))<0)
    {
        perror("socket accept failed");
        exit(EXIT_FAILURE);
    }
    printf("SERVER ACCEPTED Fall NEW CONNECTION FROM A CLIENT ON PORT 8080..\n");
    valread = read( new_socket , buffer, 1024);
    printf("%s\n",buffer );
    send(new_socket , hello , strlen(hello) , 0 );
    printf(" Ready for Chat....\n");
    while(1)
    {
        memset(buffer, 0, sizeof(buffer));
        valread = read( new_socket , buffer, 1024);
        printf("%s\n",buffer );
        memset(schat, 0, sizeof(schat));
        printf("server : ");
        fgets (schat, sizeof(schat), stdin);
        send(new_socket , schat , strlen(schat) , 0 );
        schat[strlen(schat)] = '\0';
        if(strncmp(schat , bye, strlen(bye))==0)
            break;
    }
    return 0;
}