################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Common.cpp \
../Connection.cpp \
../ServerSocket.cpp \
../Socket.cpp \
../SocketFd.cpp \
../TCPSocket.cpp \
../Transceiver.cpp \
../UDPSocket.cpp 

OBJS += \
./Common.o \
./Connection.o \
./ServerSocket.o \
./Socket.o \
./SocketFd.o \
./TCPSocket.o \
./Transceiver.o \
./UDPSocket.o 

CPP_DEPS += \
./Common.d \
./Connection.d \
./ServerSocket.d \
./Socket.d \
./SocketFd.d \
./TCPSocket.d \
./Transceiver.d \
./UDPSocket.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


