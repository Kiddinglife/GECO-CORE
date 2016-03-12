################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/geco_stl_unittest_main.cpp 

OBJS += \
./src/geco_stl_unittest_main.o 

CPP_DEPS += \
./src/geco_stl_unittest_main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/jakez/GECO-CORE/thirdparty/googlemock/include -I/home/jakez/GECO-CORE/thirdparty/googletest/include -I/home/jakez/GECO-CORE/thirdparty/googletest/src -I/home/jakez/GECO-CORE/thirdparty/googlemock/src -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


