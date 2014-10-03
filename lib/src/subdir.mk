################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Connection.cpp \
../src/ServerSocket.cpp \
../src/SocketFd.cpp \
../src/TCPClientSocket.cpp \
../src/TCPServerSocket.cpp \
../src/TCPSocket.cpp \
../src/Transceiver.cpp \
../src/UDPClientSocket.cpp \
../src/UDPServerSocket.cpp \
../src/UDPSocket.cpp \
../src/UNIXClientSocket.cpp \
../src/UNIXServerSocket.cpp 

OBJS += \
./src/Connection.o \
./src/ServerSocket.o \
./src/SocketFd.o \
./src/TCPClientSocket.o \
./src/TCPServerSocket.o \
./src/TCPSocket.o \
./src/Transceiver.o \
./src/UDPClientSocket.o \
./src/UDPServerSocket.o \
./src/UDPSocket.o \
./src/UNIXClientSocket.o \
./src/UNIXServerSocket.o 

CPP_DEPS += \
./src/Connection.d \
./src/ServerSocket.d \
./src/SocketFd.d \
./src/TCPClientSocket.d \
./src/TCPServerSocket.d \
./src/TCPSocket.d \
./src/Transceiver.d \
./src/UDPClientSocket.d \
./src/UDPServerSocket.d \
./src/UDPSocket.d \
./src/UNIXClientSocket.d \
./src/UNIXServerSocket.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DDEBUG -I../include -O0 -g -Wall -Wextra -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


