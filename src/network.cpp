
#include "Network.h"

int testSocket() {
    int client_fd; 
    struct sockaddr_in server_addr;

    char buffer[1024] = {0}; 

    memset(&server_addr, '\0', sizeof(server_addr));
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if ((client_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    char str[50] = "Hey Deniz\n";
    if (send(client_fd, str, strlen(str), 0) < 0) {
        perror("send");
        exit(EXIT_FAILURE);
    }
    return 0; 
}
