#ifndef COMMON_H_
#define COMMON_H_

extern "C" {
#include <netinet/in.h> /* sockaddr_in */
#include <arpa/inet.h>  /* inet_ntoa */
#include <unistd.h>     /* socklen_t */
}

/**
 * \brief
 * \details
 */
class Common {
protected:
	int sockfd; // Socket FileDescriptor
	Common();
	struct sockaddr_in cli_addr;
	socklen_t cli_addrlen;
public:
	virtual ~Common();
	char *getClientAddr();
};

#endif
