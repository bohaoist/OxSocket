#include "Net.h"
#include  <iostream>
#include  <string>

int main(int argc, char *argv[]) {

    int port = 1234;
    char buf[255];
    std::string msg = "Echo";
    std::string server = "127.0.0.1";

    Socket sock(server.c_str(),port);
    Connection *c = sock.connect(); 

    c->send(msg.c_str(),msg.size());
    
    int nbytes = c->recv(buf,sizeof(buf));
    if (nbytes >= 0) {
        std::cout << "Echo Client: recved message '"  //
            << std::string(buf,nbytes)  << "'" << std::endl;
    }
    delete c;

    return 0;
}

