#ifndef UNIXSERVERSOCKET_H_
#define UNIXSERVERSOCKET_H_

extern "C" {
#include <sys/unistd.h> /* unlink */
#include <errno.h> /* errno */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
}

#include <stdexcept>     /* runtime_error */

#include <SocketFd.h>
#include <Connection.h>
#include <ServerSocket.h>

class UNIXServerSocket: public SocketFd, public ServerSocket {
private:
	int last_new_sock;
	struct sockaddr_un local, remote;
public:
	UNIXServerSocket(const char*);
	virtual ~UNIXServerSocket();
	Connection* accept();
};

#endif
