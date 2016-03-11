################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/gtest-all.cc \
../src/gtest-death-test.cc \
../src/gtest-filepath.cc \
../src/gtest-port.cc \
../src/gtest-printers.cc \
../src/gtest-test-part.cc \
../src/gtest-typed-test.cc \
../src/gtest.cc \
../src/gtest_main.cc 

OBJS += \
./src/gtest-all.o \
./src/gtest-death-test.o \
./src/gtest-filepath.o \
./src/gtest-port.o \
./src/gtest-printers.o \
./src/gtest-test-part.o \
./src/gtest-typed-test.o \
./src/gtest.o \
./src/gtest_main.o 

CC_DEPS += \
./src/gtest-all.d \
./src/gtest-death-test.d \
./src/gtest-filepath.d \
./src/gtest-port.d \
./src/gtest-printers.d \
./src/gtest-test-part.d \
./src/gtest-typed-test.d \
./src/gtest.d \
./src/gtest_main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -isystem ../include -I.. -g -Wall -Wextra -pthread -c ../src/gtest-all.cc -v -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


