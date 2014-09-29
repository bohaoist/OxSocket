#ifndef COMMON_TCP_UDP_H_
#define COMMON_TCP_UDP_H_

extern "C" {
#include <netinet/in.h> /* sockaddr_in */
#include <arpa/inet.h>  /* inet_ntoa */
}

class Common_tcp_udp {
protected:
	sockaddr_in caddr;
	Common_tcp_udp();
public:
	virtual ~Common_tcp_udp();
	char *getClientAddr();
};

#endif
