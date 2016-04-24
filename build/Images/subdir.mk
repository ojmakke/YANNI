################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Images/EasyBMP.cpp \
../Images/bmp_handler.cpp 

OBJS += \
./Images/EasyBMP.o \
./Images/bmp_handler.o 

CPP_DEPS += \
./Images/EasyBMP.d \
./Images/bmp_handler.d 


# Each subdirectory must supply rules for building sources it contributes
Images/%.o: ../Images/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/gnunets/workspace/GNUNets" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


