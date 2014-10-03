#ifndef CONNECTION_H_
#define CONNECTION_H_

extern "C" {
#include <stdio.h>      /* perror */
#include <sys/unistd.h> /* read(),write() */
#include <poll.h>       /* poll, POLLIN, POLLOUT, POLLPRI */
}
#include <iostream>
#include <string>
#include <SocketFd.h>

namespace OxSocket {
/**
 *
 */
class Connection: public SocketFd {
private:
	int n;
	unsigned int sum;
//	int _poll(const int = -1);
public:
	std::string targetaddr;

	Connection(const int = 0, const std::string taddr = "");
	virtual ~Connection();

	int recv(char*, const unsigned int);
	int send(const char*, const unsigned int);

};
}
#endif
