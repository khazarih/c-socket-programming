#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char **argv)
{
    /* get server ip and port from argument */
    if (argc < 3)
    {
        printf("Usage: %s ip_address port\n", argv[0]);
        return 1;
    }

    /* define host address and port to be connected*/
    char HOST_ADDRESS[15];
    strncpy(HOST_ADDRESS, argv[1], sizeof(HOST_ADDRESS));
    int PORT = atoi(argv[2]);

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
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = inet_addr(HOST_ADDRESS);

    /* connect to the address */
    int connection_status = connect(network_socket, (struct sockaddr *)&server_address, sizeof(server_address));
    if (connection_status == -1)
    {
        printf("Connection could not be established\n");
        return 1;
    }

    char buf[100];

    /* receive data from server */
    int receive_status = recv(network_socket, &buf, sizeof(buf), 0);
    if (receive_status == -1)
    {
        printf("Could not receive data from server\n");
        return 1;
    }

    /* print server's response to the console */
    printf("%s\n", buf);

    /* close socket */
    close(network_socket);

    return 0;
}