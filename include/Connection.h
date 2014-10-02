#ifndef CONNECTION_H_
#define CONNECTION_H_

extern "C" {
#include <stdio.h>      /* perror */
#include <sys/unistd.h> /* read(),write() */
#include <poll.h>       /* poll, POLLIN, POLLOUT, POLLPRI */
}
#include <string>
#include <Transceiver.h>
#include <SocketFd.h>

class Connection: public Transceiver, public SocketFd {
protected:

private:
	int n;
	unsigned int sum;
	int _poll(const int = -1);

public:
	std::string targetaddr;

	Connection(const int = 0, const std::string taddr = "");
	virtual ~Connection();

	int recv(char*, const unsigned, const int = -1);
	int send(const char*, const unsigned, const int = -1);

};

#endif
