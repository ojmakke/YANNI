################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../networks/fullhidden.cpp \
../networks/taylornet.cpp 

OBJS += \
./networks/fullhidden.o \
./networks/taylornet.o 

CPP_DEPS += \
./networks/fullhidden.d \
./networks/taylornet.d 


# Each subdirectory must supply rules for building sources it contributes
networks/%.o: ../networks/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


