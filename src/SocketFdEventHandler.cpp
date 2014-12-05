#include <SocketFdEventHandler.h>

namespace OxSocket {

SocketFdEventHandler::SocketFdEventHandler(const unsigned int _maxevents) :
		FdEventHandler(_maxevents) {
	iter = last_wait_value = 0;

}
int SocketFdEventHandler::add(SocketFd *sfd) {
	this->evtsocks[sfd->get_sfd()] = sfd;
	return this->addFd(sfd->get_sfd());
}

int SocketFdEventHandler::del(SocketFd *sfd) {
	this->evtsocks.erase(sfd->get_sfd());
	return this->delFd(sfd->get_sfd());

}

void SocketFdEventHandler::wait2() {
	iter = 0;
	last_wait_value = this->wait();
}

SocketFdEventHandler::~SocketFdEventHandler() {
}

SocketFd* SocketFdEventHandler::getNextEvent() {
	cout << "getNextEvent(iter:=" << iter << "," << last_wait_value << ")"
			<< endl;
	for (; iter < last_wait_value;) {
		if (this->isError(iter)) {
			iter++;
			continue;
		}
//		cout << "iter: " << iter << "  wait_value: " << last_wait_value << endl;
		iter++;
		return evtsocks[this->events[iter - 1].data.fd];
	}
	iter = last_wait_value = 0;
	return NULL;
}

} /* namespace OxSocket */
