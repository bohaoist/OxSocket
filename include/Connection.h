#ifndef CONNECTION_H_
#define CONNECTION_H_

extern "C" {
#include <stdio.h>      /* perror */
#include <sys/unistd.h> /* read(),write() */
}
#include <iostream>
#include <string>
#include <SocketFd.h>
#include <cerrno>
#include <stdexcept>

#ifdef LINUXFAST
#include <sys/sendfile.h>
#include <sys/stat.h>
#endif

namespace OxSocket {
/**
 *
 */
class Connection: public SocketFd {
protected:
	int n;
	unsigned int sum;
#ifdef LINUXFAST
	int pipefd[2];
#endif
public:
	std::string targetaddr;

	Connection(const int = 0, const std::string taddr = "");
	virtual ~Connection();

	int recv(char*, const unsigned int);
	int send(const char*, const unsigned int);

#ifdef LINUXFAST
	ssize_t recvfile_fast(const std::string, const size_t);
	ssize_t sendfile_fast(const std::string);
#endif
};
}
#endif
