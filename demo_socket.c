#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
// #include <netinet/in.h>
#include <sys/un.h>

#define UNIX_SOCKET_PATH "./dgram_socket"
#define BUFFER_SIZE 1024

char buffer[BUFFER_SIZE];

int main ()
{

    int server_fd;
    struct sockaddr_un server_address, client_address;
    ssize_t received_byte;
    socklen_t client_len;
    memset(&server_address, 0, sizeof(server_address));
    server_fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if(server_fd < 0)
    {
        // printf("Socket create failed\n");
        perror("Socket create Failed");
        exit(EXIT_FAILURE);
    }
    else
    {
        unlink(UNIX_SOCKET_PATH);
        server_address.sun_family = AF_UNIX;
        strncpy(server_address.sun_path, UNIX_SOCKET_PATH, sizeof(server_address.sun_path) - 1);
        if(bind(server_fd, (struct sockaddr *)&server_address, sizeof(server_address.sun_path)) < 0)
        {
            perror("Socket blinding failed");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        printf("Binding suceeded\n");

        while (1)
        {
            /* code */
            client_len = sizeof(client_address);
            received_byte = recvfrom(server_fd, buffer, BUFFER_SIZE - 1, 0, (struct sockaddr *)&client_address, &client_len);

            if(received_byte < 0)
            {
                perror("cannot receive data from client!");
                break;
            }
            buffer[received_byte] = '\0';
            printf("Received %zd bytes: %s \n", received_byte, buffer);

            if(strncmp(buffer, "exit", 4) == 0)
            {
                printf("Server socket terminating...\n");
                break;
            }
        }
        close(server_fd);
        unlink(UNIX_SOCKET_PATH);
        printf("Server terminated!\n");
        
    }
    return 0;
}