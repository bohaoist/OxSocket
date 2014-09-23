#ifndef CONNECTION_H_
#define CONNECTION_H_

extern "C" {
#include <stdio.h>      /* perror */
#include <sys/unistd.h> /* read(),write() */
#include <poll.h>       /* poll */
}

#include "Transceiver.h"
#include "SocketFd.h"

class Connection: public SocketFd, public Transceiver {
private:
	int n;
	unsigned sum;
	struct pollfd ufds;
	int _poll(const int = -1);

public:
	Connection(const int);
	virtual ~Connection();

	int recv(char*, const unsigned, const int = -1);
	int send(const char*, const unsigned, const int = -1);
};

#endif
