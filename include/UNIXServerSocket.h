#ifndef UNIXSERVERSOCKET_H_
#define UNIXSERVERSOCKET_H_

extern "C" {
#include <sys/unistd.h> /* unlink */
#include <errno.h> /* errno */
}

#include <UNIXSocket.h>
#include <Connection.h>
#include <ServerSocket.h>

class UNIXServerSocket: public UNIXSocket, public ServerSocket {
public:
	UNIXServerSocket(const char*);
	virtual ~UNIXServerSocket();
	Connection* accept();
};

#endif
