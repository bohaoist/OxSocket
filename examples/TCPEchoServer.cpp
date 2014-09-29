#include "Socket.h"
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {

    int port = 1234;                  //
    char buf[255];                    // 

    TCPServerSocket serversock(port); // 

    Connection *c = NULL;             //

    while(true){
        c = serversock.accept();      // wait for Connections
        int nbytes = c->recv(buf, 4); // recv 4 Bytes
        if (nbytes >= 0) {            // 
            std::cout << "Echo Server: recved message '" //
                << std::string(buf,nbytes) << "'" << std::endl;
        }
        c->send(buf,nbytes);          // send Message back
        delete c;
    }
    
    return 0;
}
