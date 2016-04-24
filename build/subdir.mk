################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../common.cpp \
../gnunet_test.cpp \
../gnunets.cpp 

OBJS += \
./common.o \
./gnunet_test.o \
./gnunets.o 

CPP_DEPS += \
./common.d \
./gnunet_test.d \
./gnunets.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/gnunets/workspace/GNUNets" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


