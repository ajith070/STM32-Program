################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/gpio_assign.c \
../Src/i2c_assign.c \
../Src/spi_assign.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/usart_assign.c 

OBJS += \
./Src/gpio_assign.o \
./Src/i2c_assign.o \
./Src/spi_assign.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/usart_assign.o 

C_DEPS += \
./Src/gpio_assign.d \
./Src/i2c_assign.d \
./Src/spi_assign.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/usart_assign.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DNUCLEO_F401RE -DSTM32 -DSTM32F401RETx -DSTM32F4 -c -I../Inc -I"C:/Users/user/OneDrive/Desktop/embdsystms/STM32 programming/F401drivers/DriversDev/drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/gpio_assign.cyclo ./Src/gpio_assign.d ./Src/gpio_assign.o ./Src/gpio_assign.su ./Src/i2c_assign.cyclo ./Src/i2c_assign.d ./Src/i2c_assign.o ./Src/i2c_assign.su ./Src/spi_assign.cyclo ./Src/spi_assign.d ./Src/spi_assign.o ./Src/spi_assign.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/usart_assign.cyclo ./Src/usart_assign.d ./Src/usart_assign.o ./Src/usart_assign.su

.PHONY: clean-Src

