#include "Net.h"
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {

    int port = 1234;
    char buf[255];

    ServerSocket serversock(port);
    Connection *c = NULL;

    while(true){
        std::cout << "waiting for connections on port: " << port << std::endl;
        c = serversock.accept(); // wait for Connections
        c->setTimeout(0, 0);
        std::cout << "got connection" << std::endl;
        int nbytes = c->recv(buf, sizeof(buf));
        std::cout << "recved " << nbytes << " Bytes" << std::endl;
        if (nbytes >= 0) {
            std::cout << "Echo Server: recved message '" //
                << std::string(buf,nbytes) << "'" << std::endl;
        }

        std::cout << "resending messages to client " << std::endl;
        c->send(buf,nbytes);
        delete c;
    }
    return 0;
}
