#include <FdEventHandler.h>

namespace OxSocket {

FdEventHandler::FdEventHandler() {
	efd = epoll_create1(0);
	if (efd == -1) {
		perror("epoll_create");
		abort();
	}

#define MAXEVENTS 64
	/* Buffer where events are returned */
	events = (epoll_event*) calloc(MAXEVENTS, sizeof event);

}

FdEventHandler::~FdEventHandler() {
	free(events);
}

int FdEventHandler::addFd(int infd) {
	event.data.fd = infd;
	event.events = EPOLLIN | EPOLLET;
	int s = epoll_ctl(efd, EPOLL_CTL_ADD, infd, &event);
	if (s == -1) {
		perror("epoll_ctl");
		abort();
	}
	return 0;
}

int FdEventHandler::delFd(int infd) {
	int s = epoll_ctl(efd, EPOLL_CTL_DEL, infd, &event);
	if (s == -1) {
		perror("epoll_ctl");
		abort();
	}
	return 0;
}

} /* namespace OxSocket */
