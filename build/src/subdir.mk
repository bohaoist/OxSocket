################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ClientSocket.cpp \
../src/Common_tcp_udp.cpp \
../src/Common_tcp_udp_unix.cpp \
../src/Common_tcp_unix.cpp \
../src/Connection.cpp \
../src/ServerSocket.cpp \
../src/SocketFd.cpp \
../src/TCPClientSocket.cpp \
../src/TCPServerSocket.cpp \
../src/TCPSocket.cpp \
../src/Transceiver.cpp \
../src/UDPSocket.cpp \
../src/UNIXClientSocket.cpp \
../src/UNIXServerSocket.cpp \
../src/UNIXSocket.cpp 

OBJS += \
./src/ClientSocket.o \
./src/Common_tcp_udp.o \
./src/Common_tcp_udp_unix.o \
./src/Common_tcp_unix.o \
./src/Connection.o \
./src/ServerSocket.o \
./src/SocketFd.o \
./src/TCPClientSocket.o \
./src/TCPServerSocket.o \
./src/TCPSocket.o \
./src/Transceiver.o \
./src/UDPSocket.o \
./src/UNIXClientSocket.o \
./src/UNIXServerSocket.o \
./src/UNIXSocket.o 

CPP_DEPS += \
./src/ClientSocket.d \
./src/Common_tcp_udp.d \
./src/Common_tcp_udp_unix.d \
./src/Common_tcp_unix.d \
./src/Connection.d \
./src/ServerSocket.d \
./src/SocketFd.d \
./src/TCPClientSocket.d \
./src/TCPServerSocket.d \
./src/TCPSocket.d \
./src/Transceiver.d \
./src/UDPSocket.d \
./src/UNIXClientSocket.d \
./src/UNIXServerSocket.d \
./src/UNIXSocket.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../include -O0 -g -Wall -Wextra -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


