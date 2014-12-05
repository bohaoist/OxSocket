#ifndef FDEVENTHANDLER_H_
#define FDEVENTHANDLER_H_

#include <sys/epoll.h>
#include <cstdio>
#include <cstdlib>
#include <stdexcept>
#include <iostream>
#include <unistd.h>
#include <map>
#include <SocketFd.h>

namespace OxSocket {

using namespace std;

class FdEventHandler {
protected:
	int efd; // event file descriptor
	int rv; // return value
	unsigned int maxevents;
	epoll_event event;
	epoll_event *events;
	int addFd(int);
	int delFd(int);

public:
	FdEventHandler(const unsigned int maxevents = 512);
	virtual ~FdEventHandler();
	int wait();
	epoll_event getEvent(int n);
	bool isError(int i);
};

}

#endif
