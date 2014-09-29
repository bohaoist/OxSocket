#include <Common_tcp_udp.h>

Common_tcp_udp::Common_tcp_udp() {
}

Common_tcp_udp::~Common_tcp_udp() {
}

char* Common_tcp_udp::getClientAddr() {
	return (::inet_ntoa(caddr.sin_addr));
}
