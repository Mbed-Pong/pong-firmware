
#ifndef NETWORK_H
#define NETWORK_H

#include "EthernetInterface.h"
#include "mbed.h" 

#define AWS_IP  "3.128.153.185"
#define PORT    3030

#define CONNECTION_REQ  "{\"type\": \"connected\"}"
#define LOBBY_HASH      "jaredyeagersflipflop"

void initEthernet(EthernetInterface *eth, UDPSocket *sock, Endpoint *nist);
void cleanupEthernet(EthernetInterface *eth, UDPSocket *sock); 

#endif // NETWORK_H


