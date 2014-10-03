#include <Connection.h>

Connection::Connection(const int fd, const std::string taddr) {
	targetaddr = taddr;
	sum = nbytes = 0;
	ufds.fd = fd;
	ufds.events = POLLIN | POLLOUT | POLLPRI;
}

Connection::~Connection() {
}

#define WEADMACRO(function) \
nbytes = sum = 0; \
do { \
	nbytes = ::function(ufds.fd, buf + sum, size - sum); \
	if (nbytes == 0) { \
		return (sum); /* End of File/Stream */\
	} else if (nbytes < 0) { \
		::perror(#function); \
		return (-1); /* Error */\
	} else { \
		sum += nbytes; \
	} \
} while (sum < size); \
return (sum);

int Connection::send(const char *buf, const unsigned int size) {
//	_poll(msec);
	WEADMACRO(write)
}

int Connection::recv(char *buf, const unsigned int size) {
//	_poll(msec);
	WEADMACRO(read)
}

#undef WEADMACRO

//int Connection::_poll(const int msec) {
//	int rv = ::poll(&ufds, 1, msec);
//#ifdef DEBUG
//	if (0 > rv) {
//		::perror("poll error");
//	} else if (0 == rv) {
//		::perror("poll timeout");
//	} //else 0 < rv
//#endif
//	return (rv);
//}

