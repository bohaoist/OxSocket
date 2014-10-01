#include <UDPClientSocket.h>

UDPClientSocket::UDPClientSocket(const unsigned int port, const char* addr) :
		UDPSocket(port, addr) {

}

UDPClientSocket::~UDPClientSocket() {
}

