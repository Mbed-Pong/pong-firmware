#include "network.h"

void initEthernet(EthernetInterface *eth, UDPSocket *sock, Endpoint *nist) {
    int rc; 
    rc = eth->init(); //Use DHCP
    if (rc < 0) {
        printf("\n\rFatal Error: failed to initialize ethernet via DHCP\n\r");
        return; 
    }
    rc = eth->connect();
    if (rc < 0) {
        printf("\n\rFatal Error: failed to connect\n\r");
        return; 
    }
    rc = sock->init();
    if (rc < 0) {
        printf("\n\rFatal Error: failed to initialize socket\n\r");
        return; 
    }
    rc = nist->set_address(AWS_IP, PORT);
    if (rc < 0) {
        printf("\n\rFatal Error: failed to set address\n\r");
        return; 
    }
    sock->set_blocking(false, 0);
    printf("\n\rSuccess! Connected to %s, port: %i\n\r", AWS_IP, PORT); 
}

void cleanupEthernet(EthernetInterface *eth, UDPSocket *sock) {
    sock->close(); 
    eth->disconnect(); 
}


