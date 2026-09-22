################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/src/bmp280.c \
../drivers/src/spi.c \
../drivers/src/stm32f401xx_gpio_driver.c \
../drivers/src/stm32f401xx_i2c_driver.c \
../drivers/src/stm32f401xx_rcc_driver.c \
../drivers/src/stm32f401xx_spi_driver.c \
../drivers/src/stm32f401xx_usart_driver.c 

OBJS += \
./drivers/src/bmp280.o \
./drivers/src/spi.o \
./drivers/src/stm32f401xx_gpio_driver.o \
./drivers/src/stm32f401xx_i2c_driver.o \
./drivers/src/stm32f401xx_rcc_driver.o \
./drivers/src/stm32f401xx_spi_driver.o \
./drivers/src/stm32f401xx_usart_driver.o 

C_DEPS += \
./drivers/src/bmp280.d \
./drivers/src/spi.d \
./drivers/src/stm32f401xx_gpio_driver.d \
./drivers/src/stm32f401xx_i2c_driver.d \
./drivers/src/stm32f401xx_rcc_driver.d \
./drivers/src/stm32f401xx_spi_driver.d \
./drivers/src/stm32f401xx_usart_driver.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/src/%.o drivers/src/%.su drivers/src/%.cyclo: ../drivers/src/%.c drivers/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DNUCLEO_F401RE -DSTM32 -DSTM32F401RETx -DSTM32F4 -c -I../Inc -I"C:/Users/user/OneDrive/Desktop/embdsystms/STM32 programming/F401drivers/DriversDev/drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-drivers-2f-src

clean-drivers-2f-src:
	-$(RM) ./drivers/src/bmp280.cyclo ./drivers/src/bmp280.d ./drivers/src/bmp280.o ./drivers/src/bmp280.su ./drivers/src/spi.cyclo ./drivers/src/spi.d ./drivers/src/spi.o ./drivers/src/spi.su ./drivers/src/stm32f401xx_gpio_driver.cyclo ./drivers/src/stm32f401xx_gpio_driver.d ./drivers/src/stm32f401xx_gpio_driver.o ./drivers/src/stm32f401xx_gpio_driver.su ./drivers/src/stm32f401xx_i2c_driver.cyclo ./drivers/src/stm32f401xx_i2c_driver.d ./drivers/src/stm32f401xx_i2c_driver.o ./drivers/src/stm32f401xx_i2c_driver.su ./drivers/src/stm32f401xx_rcc_driver.cyclo ./drivers/src/stm32f401xx_rcc_driver.d ./drivers/src/stm32f401xx_rcc_driver.o ./drivers/src/stm32f401xx_rcc_driver.su ./drivers/src/stm32f401xx_spi_driver.cyclo ./drivers/src/stm32f401xx_spi_driver.d ./drivers/src/stm32f401xx_spi_driver.o ./drivers/src/stm32f401xx_spi_driver.su ./drivers/src/stm32f401xx_usart_driver.cyclo ./drivers/src/stm32f401xx_usart_driver.d ./drivers/src/stm32f401xx_usart_driver.o ./drivers/src/stm32f401xx_usart_driver.su

.PHONY: clean-drivers-2f-src

