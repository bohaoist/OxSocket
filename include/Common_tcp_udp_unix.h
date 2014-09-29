#ifndef Common_tcp_udp_unix_H_
#define Common_tcp_udp_unix_H_

extern "C" {
#include <netinet/in.h> /* sockaddr_in */
}

class Common_tcp_udp_unix {
protected:
	Common_tcp_udp_unix();
	socklen_t cli_addrlen;
public:
	virtual ~Common_tcp_udp_unix();

};

#endif
