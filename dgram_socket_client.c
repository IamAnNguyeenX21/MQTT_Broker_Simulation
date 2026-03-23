#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>

#define UNIX_SOCKET_PATH "./dgram_socket"
#define BUFFER_SIZE 1024

int main (int argc, char *argv[])
{
    int client_fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    struct sockaddr_un server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sun_family = AF_UNIX;
    strncpy(server_address.sun_path, UNIX_SOCKET_PATH, sizeof(server_address.sun_path) - 1);
    if(client_fd < 0)
    {
        perror("Socket create failed");
        exit(EXIT_FAILURE);
    }

    printf("Client socket created successfully\n");

    if(argc < 2)
    {
        printf("Usage: %s <message>\n", argv[0]);
        close(client_fd);
        exit(EXIT_FAILURE);
    }
    else
    {
        ssize_t send_byte = sendto(client_fd, 
                                    argv[1], 
                                    strlen(argv[1]), 
                                    0, 
                                    (struct sockaddr *)&server_address, 
                                    sizeof(server_address.sun_path));
        
        if (send_byte < 0)
        {
            /* code */
            printf("Cannot send data to server\n");
            perror("Send failed");
        }

        printf("Sent %zd bytes: %s\n", send_byte, argv[1]);

        
    }
    close(client_fd);
    printf("Client socket closed\n");
    return 0;

}