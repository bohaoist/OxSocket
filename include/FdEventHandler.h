#ifndef FDEVENTHANDLER_H_
#define FDEVENTHANDLER_H_

#include <sys/epoll.h>
#include <cstdio>
#include <cstdlib>

namespace OxSocket {

class FdEventHandler {
private:
	int efd;
	epoll_event event;
	epoll_event *events;
public:
	FdEventHandler();
	virtual ~FdEventHandler();
	int addFd(int);
	int delFd(int);
};

}

#endif
