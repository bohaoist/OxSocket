#ifndef COMMON_TCP_UDP_UNIX_H_
#define COMMON_TCP_UDP_UNIX_H_

#include <netinet/in.h> /* sockaddr_in, htons , INADDR_ANY*/

class Common_tcp_udp_unix {
protected:
	socklen_t slen;
	Common_tcp_udp_unix();
public:
	virtual ~Common_tcp_udp_unix();
};

#endif
