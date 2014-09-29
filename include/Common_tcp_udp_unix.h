#ifndef COMMON_TCP_UDP_UNIX_H_
#define COMMON_TCP_UDP_UNIX_H_

extern "C" {
#include <netinet/in.h> /* sockaddr_in */
}

class Common_tcp_udp_unix {
protected:
	Common_tcp_udp_unix();
	socklen_t addrlen;
public:
	virtual ~Common_tcp_udp_unix();

};

#endif
