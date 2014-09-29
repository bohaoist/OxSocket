#!/bin/bash
cd bin
rm -f *.exe
make clean
make 
cd ..
# Build Examples

for x in TCPEchoServer TCPEchoClient
do
    g++ -I include/ -lSocket -L ./bin examples/${x}.cpp  -o bin/${x}.exe
done
