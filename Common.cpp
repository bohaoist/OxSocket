#include "Common.h"

Common::Common() {
	sockfd = -1;
}

Common::~Common() {
}

char *Common::getClientAddr() {
	return (::inet_ntoa(cli_addr.sin_addr));
}
