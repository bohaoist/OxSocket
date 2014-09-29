#ifndef COMMON_TCP_UDP_H_
#define COMMON_TCP_UDP_H_

extern "C" {
#include <netinet/in.h> /* sockaddr_in */
#include <arpa/inet.h>
}

class Common_tcp_udp {
protected:
	struct sockaddr_in cli_addr;
	Common_tcp_udp();
public:
	virtual ~Common_tcp_udp();
	char *getClientAddr();
};

#endif
