################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../examples/http_client.cpp 

OBJS += \
./examples/http_client.o 

CPP_DEPS += \
./examples/http_client.d 


# Each subdirectory must supply rules for building sources it contributes
examples/%.o: ../examples/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DDEBUG -I../include -O0 -g3 -Wall -Wextra -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


