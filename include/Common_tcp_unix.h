#ifndef COMMON_TCP_UNIX_H_
#define COMMON_TCP_UNIX_H_

extern "C" {
#include <sys/socket.h> /* socket */
}
#include <stdexcept>

class Common_tcp_unix {
protected:
	Common_tcp_unix(int&, const int);
public:
	virtual ~Common_tcp_unix();
};

#endif
