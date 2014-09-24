
RM := rm -rf
CC := g++
LD := g++

# All of the sources participating in the build are defined here

CPP_SRCS += \
./Common.cpp \
./Connection.cpp \
./ServerSocket.cpp \
./Socket.cpp \
./SocketFd.cpp \
./TCPSocket.cpp \
./Transceiver.cpp \
./UDPSocket.cpp \

OBJS += \
./Common.o \
./Connection.o \
./ServerSocket.o \
./Socket.o \
./SocketFd.o \
./TCPSocket.o \
./Transceiver.o \
./UDPSocket.o \

%.o: ./%.cpp
	@echo 'Compiling file: $<'
	${CC} -O2 -g -Wall -c -fmessage-length=0 -fPIC -o "$@" "$<"
	@echo ' '

# All Target
all: libNet TCPEchoServer TCPEchoClient cleanobjs

libNet: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	${LD} -shared -o "$@.so" $(OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

TCPEchoServer: $(OBJS)
	@echo 'Building target: $@'
	${CC} -O2 -g -Wall -c -fmessage-length=0 -fPIC -o "$@.o" "./$@.cpp"
	${LD} -o "$@_dyn.exe" "$@.o" -L. -lNet
	${LD} -o "$@_static.exe" "$@.o" $(OBJS)
	-$(RM) "$@.o"
	@echo 'Finished building target: $@'
	@echo ' '

TCPEchoClient: $(OBJS)
	@echo 'Building target: $@'
	${CC} -O2 -g -Wall -c -fmessage-length=0 -fPIC -o "$@.o" "./$@.cpp"
	${LD} -o "$@_dyn.exe" "$@.o" -L. -lNet
	${LD} -o "$@_static.exe" "$@.o" $(OBJS)
	-$(RM) "$@.o"
	@echo 'Finished building target: $@'
	@echo ' '

cleanobjs:
	-$(RM) $(OBJS) 

clean:
	-$(RM) $(OBJS) libNet.so TCPEchoServer_dyn.exe TCPEchoClient_dyn.exe TCPEchoServer_static.exe TCPEchoClient_static.exe 
	-@echo ' '

.PHONY: all clean 
.SECONDARY:


