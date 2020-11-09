
#include "Network.h"

int testSocket() {
    int client_fd; 
    struct sockaddr_in server_addr;

    char buffer[1024] = {0}; 

    memset(&server_addr, '\0', sizeof(server_addr));
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("3.128.153.185");

    if ((client_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    char str[] = "{\"type\": \"connected\", \"body\": \"Hey Deniz\"}";
    if (send(client_fd, str, strlen(str), 0) < 0) {
        perror("send");
        exit(EXIT_FAILURE);
    }
    int rc = read(client_fd, buffer, 1024);
    printf("bytes resad: %i\n", rc);
    printf("data: %s\n", buffer);
    return 0; 
}
