#ifndef COMMON_TCP_UDP_H_
#define COMMON_TCP_UDP_H_

#include <netinet/in.h> /* sockaddr_in, htons , INADDR_ANY*/

class Common_tcp_udp {
protected:
	Common_tcp_udp();
	sockaddr_in si_me, si_other;
public:
	virtual ~Common_tcp_udp();
};

#endif
