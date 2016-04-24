################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../interpreter/classic_network.cpp \
../interpreter/eval_network.cpp \
../interpreter/parser.cpp \
../interpreter/plot_square.cpp \
../interpreter/scale_network.cpp \
../interpreter/set_io.cpp \
../interpreter/train_network.cpp \
../interpreter/use_network.cpp 

OBJS += \
./interpreter/classic_network.o \
./interpreter/eval_network.o \
./interpreter/parser.o \
./interpreter/plot_square.o \
./interpreter/scale_network.o \
./interpreter/set_io.o \
./interpreter/train_network.o \
./interpreter/use_network.o 

CPP_DEPS += \
./interpreter/classic_network.d \
./interpreter/eval_network.d \
./interpreter/parser.d \
./interpreter/plot_square.d \
./interpreter/scale_network.d \
./interpreter/set_io.d \
./interpreter/train_network.d \
./interpreter/use_network.d 


# Each subdirectory must supply rules for building sources it contributes
interpreter/%.o: ../interpreter/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/gnunets/workspace/GNUNets" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


