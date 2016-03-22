################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../parts/edge.cpp \
../parts/layer.cpp \
../parts/node.cpp 

OBJS += \
./parts/edge.o \
./parts/layer.o \
./parts/node.o 

CPP_DEPS += \
./parts/edge.d \
./parts/layer.d \
./parts/node.d 


# Each subdirectory must supply rules for building sources it contributes
parts/%.o: ../parts/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


