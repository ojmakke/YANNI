################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../interpreter/parser.cpp 

OBJS += \
./interpreter/parser.o 

CPP_DEPS += \
./interpreter/parser.d 


# Each subdirectory must supply rules for building sources it contributes
interpreter/%.o: ../interpreter/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/gnunets/workspace/GNUNets" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


