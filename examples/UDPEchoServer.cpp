#include "Socket.h"
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {

    int port = 1234;
    char buf[255];

    UDPSocket udpsock(port);

    while(true){
        int nbytes = udpsock.recv(buf,4);
        if (nbytes >= 0) {
            std::cout << "Echo Server: recved message '" //
                << std::string(buf,nbytes) << "' " <<  nbytes  << std::endl;
        }
    }
    return 0;
}
