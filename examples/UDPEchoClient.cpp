#include "Socket.h"
#include  <iostream>
#include  <string>

int main(int argc, char *argv[]) {

    int port = 1234;
    char buf[255];
    std::string msg = "Echo";
    std::string server = "127.0.0.1";

    UDPSocket udpsock(port,server.c_str());
    udpsock.send(msg.c_str(),msg.size());

    return 0;
}
