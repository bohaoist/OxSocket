#ifndef UNIXCLIENTSOCKET_H_
#define UNIXCLIENTSOCKET_H_

extern "C" {
#include <sys/socket.h> /* socket, connect */
#include <sys/un.h>     /* sockaddr_un */
}

#include <cstdio>      /* perror */
#include <cstring>     /* strcpy, strlen */
#include <stdexcept>   /* runtime_error */
#include <string>

#include <Connection.h>

namespace OxSocket {
/**
 * A UNIXClientSocket establishes a connection on construct
 * Afterwards it can be used like a Connection Object.
 * It directly provides send() and recv() functions
 * on init/connection error the Constructor throws a std::runtime_error
 */
class UNIXClientSocket: public Connection {
private:
	/*
	 * unix socket struct
	 */
	sockaddr_un remote;
public:
	/**
	 * \brief  construct UNIXClientSocket throws runtime_error on failure
	 * \details construct UNIXClientSocket throws runtime_error on failure
	 * \param[in] path Path to socket file
	 */
	UNIXClientSocket(const std::string path);
	virtual ~UNIXClientSocket();
};
}
#endif
