#ifndef UNIXSERVERSOCKET_H_
#define UNIXSERVERSOCKET_H_

#include <UNIXSocket.h>

class UNIXServerSocket: public UNIXSocket {
public:
	UNIXServerSocket(const char*);
	virtual ~UNIXServerSocket();
	Connection* accept();
};

#endif /* UNIXSERVERSOCKET_H_ */
