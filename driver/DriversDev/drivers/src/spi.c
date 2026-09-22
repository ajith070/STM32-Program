/*
 * spi.c
 *
 *  Created on: Sep 14, 2026
 *      Author: user
 */
#include "stm32f401xx.h"
#include "stm32f401xx_gpio_driver.h"
#include "stm32f401xx_spi_driver.h"
#include "spi.h"


void BMP280_SPI_GPIOInits(void)
{
    GPIO_Handle_t SPIPins;

    // Enable GPIOA clock
    GPIO_PeriClockControl(GPIOA, ENABLE);


    // SPI1 GPIO pins
    SPIPins.pGPIOx = GPIOA;

    SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALT ;
    SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;   // SPI1 AF5
    SPIPins.GPIO_PinConfig.GPIO_PinOPType =  OUTPUT_PUSHPULL ;
    SPIPins.GPIO_PinConfig.GPIO_PinPupdControl =  GPIO_NOPULLUP_NOPULLDOWN;
    SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;


    // PA5 -> SPI1_SCK
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
    GPIO_Init(&SPIPins);


    // PA6 -> SPI1_MISO
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
    GPIO_Init(&SPIPins);


    // PA7 -> SPI1_MOSI
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_7;
    GPIO_Init(&SPIPins);



    // PA4 -> CSB
    SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_4;

    GPIO_Init(&SPIPins);


    // CS HIGH (inactive)
    GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_4, GPIO_PIN_SET);
}



void BMP280_SPI_Init(void)
{
    SPI_Handle_t SPI1Handle;


    SPI1Handle.pSPIx = SPI1;


    SPI1Handle.SPI_PinConfig.SPI_DeviceMode = SPI_DEVICEMODE_MASTER;


    SPI1Handle.SPI_PinConfig.SPI_BusConfig = SPI_BUSCONFIG_FD ;


    SPI1Handle.SPI_PinConfig.SPI_SclkSpeed = SPI_SCLK_PRE16;


    SPI1Handle.SPI_PinConfig.SPI_DFF = SPI_DFF_8BITS;


    SPI1Handle.SPI_PinConfig.SPI_CPOL = SPI_CPOL_LOW;


    SPI1Handle.SPI_PinConfig.SPI_CPHA =SPI_CPHA_LOW ;


    SPI1Handle.SPI_PinConfig.SPI_SSM = SPI_SSM_EN ;


    SPI_Init(&SPI1Handle);


    SPI_SSIConfig(SPI1, ENABLE);


    SPI_PeripheralControl(SPI1, ENABLE);

}



uint8_t SPI_Transfer(uint8_t data)
{
    uint8_t rx_data;

    SPI_SendData(SPI1, &data, 1);

    SPI_ReceiveData(SPI1, &rx_data, 1);


    return rx_data;
}



void BMP280_WriteRegister(uint8_t reg, uint8_t value)
{

    GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_4,GPIO_PIN_RESET);
    SPI_Transfer(reg & 0x7F);
    SPI_Transfer(value);

    GPIO_WriteToOutputPin(GPIOA,GPIO_PIN_NO_4,GPIO_PIN_SET);

}



void BMP280_ReadRegisters(uint8_t reg, uint8_t *buffer,uint8_t len)
{

    GPIO_WriteToOutputPin(GPIOA,GPIO_PIN_NO_4,GPIO_PIN_RESET);


    SPI_Transfer(reg | 0x80);


    for(uint8_t i=0;i<len;i++)
    {
        buffer[i]=SPI_Transfer(0x00);
    }


    GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_4,GPIO_PIN_SET);
}

