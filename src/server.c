#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char **argv)
{

    /* get bind ip and port from argument */
    if (argc < 3)
    {
        printf("Usage: %s ip_address port\n", argv[0]);
        return 1;
    }

    char BIND_HOST_ADDRESS[15];
    strncpy(BIND_HOST_ADDRESS, argv[1], sizeof(BIND_HOST_ADDRESS));
    int BIND_PORT = atoi(argv[2]);
    char SERVER_RESPONSE[] = "It is a socket server!";

    /* create a socket */
    int network_socket;

    /*
        socket function arguments
        AF_INET = IPv4 address family
        SOCK_STREAM = TCP
        0 = using default protocol which is TCP
    */
    network_socket = socket(AF_INET, SOCK_STREAM, 0);

    /* specify an address for the socket */
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(BIND_PORT);
    server_address.sin_addr.s_addr = inet_addr(BIND_HOST_ADDRESS);

    bind(network_socket, (struct sockaddr *)&server_address, sizeof(server_address));
    int listen_status = listen(network_socket, 5);
    if (listen_status == -1)
    {
        printf("Could not listen for incoming connections\n");
        return 1;
    }

    int client_socket = accept(network_socket, NULL, NULL);
    if (client_socket == -1)
    {
        printf("Could not accept incoming connection\n");
    }

    send(client_socket, &SERVER_RESPONSE, sizeof(SERVER_RESPONSE), 0);
    close(network_socket);

    return 0;
}