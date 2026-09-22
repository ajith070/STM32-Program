#include "stm32f401xx.h"
#include "stm32f401xx_gpio_driver.h"
#include "stm32f401xx_i2c_driver.h"
#include "stm32f401xx_usart_driver.h"

#include <stdio.h>
#include <string.h>


#define BMP280_ADDR      0x76


I2C_Handle_t i2c1;
USART_Handle_t usart2;

uint16_t dig_T1;
int16_t dig_T2;
int16_t dig_T3;

extern int32_t t_fine;



void delay_ms(void)
{
    for(uint32_t i=0;i<500000;i++);
}



void BMP280_Read(uint8_t reg,uint8_t *data,uint8_t len)
{
    char msg[]="Sending register\r\n";

    USART_SendData(&usart2, (uint8_t*)msg, strlen(msg));


    I2C_MasterSendData(&i2c1, &reg, 1, BMP280_ADDR, I2C_ENABLE_SR);


    char msg2[]="Register sent\r\n";

    USART_SendData(&usart2, (uint8_t*)msg2, strlen(msg2));


    I2C_MasterReceiveData(&i2c1, data, len, BMP280_ADDR,I2C_DISABLE_SR);


    char msg3[]="Data received\r\n";

    USART_SendData(&usart2,(uint8_t*)msg3, strlen(msg3));
}


/**************** I2C GPIO ****************/


void I2C1_GPIO_Init(void)
{

    GPIO_Handle_t gpio;


    GPIO_PeriClockControl(GPIOB,ENABLE);


    gpio.pGPIOx = GPIOB;


    gpio.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALT;


    gpio.GPIO_PinConfig.GPIO_PinAltFunMode = 4;


    gpio.GPIO_PinConfig.GPIO_PinOPType = OPEN_DRAIN;


    gpio.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;


    gpio.GPIO_PinConfig.GPIO_PinPupdControl = GPIO_PULLUP;



    // PB6 SCL

    gpio.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;

    GPIO_Init(&gpio);



    // PB7 SDA

    gpio.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_7;

    GPIO_Init(&gpio);


}



/**************** I2C INIT ****************/


void I2C1_Init(void)
{


    i2c1.pI2Cx = I2C1;


    i2c1.I2C_Config.I2C_SCLSpeed =  I2C_SCL_SPEED_SM;


    i2c1.I2C_Config.I2C_ACKControl = I2C_ACK_ENABLE;


    i2c1.I2C_Config.I2C_DeviceAddress = 0x61;


    i2c1.I2C_Config.I2C_FMDutyCycle = I2C_FM_DUTY_2;



    I2C_Init(&i2c1);



    I2C_PeripheralControl(I2C1,ENABLE);


}
/* USART2 GPIO Configuration */
void USART2_GPIO_Init(void)
{
    GPIO_Handle_t USARTPins;

    GPIO_PeriClockControl(GPIOA, ENABLE);

    USARTPins.pGPIOx = GPIOA;
    USARTPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALT;
    USARTPins.GPIO_PinConfig.GPIO_PinAltFunMode = 7;
    USARTPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
    USARTPins.GPIO_PinConfig.GPIO_PinOPType = OUTPUT_PUSHPULL;
    USARTPins.GPIO_PinConfig.GPIO_PinPupdControl = GPIO_PULLUP;

    /* PA2 as TX */
    USARTPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_2;

    GPIO_Init(&USARTPins);

    /* PA3 as RX */
    USARTPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_3;
    GPIO_Init(&USARTPins);
}

void USART2_Init(void)
{
    usart2.pUSARTx = USART2;

    usart2.USART_Config.USART_Baud = USART_STD_BAUD_115200;
    usart2.USART_Config.USART_Mode = USART_MODE_TXRX;
    usart2.USART_Config.USART_NoOfStopBits = USART_STOPBITS_1;
    usart2.USART_Config.USART_WordLength = USART_WORDLEN_8BITS;
    usart2.USART_Config.USART_ParityControl = USART_PARITY_DISABLE;
    usart2.USART_Config.USART_HWFlowControl = USART_HW_FLOW_CTRL_NONE;

    USART_Init(&usart2);

    USART_PeripheralControl(USART2, ENABLE);
}


/**************** BMP280 WRITE ****************/


void BMP280_Write(uint8_t reg,uint8_t data)
{

    uint8_t buffer[2];


    buffer[0]=reg;
    buffer[1]=data;


    I2C_MasterSendData(&i2c1, buffer,2,BMP280_ADDR,I2C_DISABLE_SR);

}



uint8_t BMP280_ReadID(void)
{
    uint8_t id = 0xFF;

    BMP280_Read(0xD0,&id,1);

    return id;
}
/**************** BMP280 INIT ****************/


void BMP280_Init(void)
{

    uint8_t calib[6];


    // Normal mode

    BMP280_Write(0xF4,0x27);



    // Read calibration

    BMP280_Read(0x88,calib,6);



    dig_T1 = (calib[1]<<8)|calib[0];


    dig_T2 = (calib[3]<<8)|calib[2];


    dig_T3 = (calib[5]<<8)|calib[4];


}



/**************** READ TEMPERATURE ****************/


float BMP280_ReadTemperature(void)
{

    uint8_t data[3];


    BMP280_Read(0xFA,data,3);



    int32_t adc_T;


    adc_T =
    ((int32_t)data[0]<<12) |
    ((int32_t)data[1]<<4) |
    ((int32_t)data[2]>>4);



    float var1,var2;



    var1 =
    (((float)adc_T/16384.0f)
    -
    ((float)dig_T1/1024.0f))
    *
    ((float)dig_T2);



    var2 =
    (((float)adc_T/131072.0f)
    -
    ((float)dig_T2/8192.0f))
    *
    ((float)dig_T3);



    t_fine = var1+var2;


    float temperature;


    temperature = t_fine/5120.0f;



    return temperature;

}

int main(void)
{
    char msg[50];

    USART2_GPIO_Init();
    USART2_Init();

    I2C1_GPIO_Init();
    I2C1_Init();

    sprintf(msg,"USART OK\r\n");
    USART_SendData(&usart2,(uint8_t*)msg,strlen(msg));

    sprintf(msg,"I2C OK\r\n");
    USART_SendData(&usart2,(uint8_t*)msg,strlen(msg));

    uint8_t id = BMP280_ReadID();

    sprintf(msg,"BMP ID = 0x%X\r\n",id);
    USART_SendData(&usart2,(uint8_t*)msg,strlen(msg));

    while(1);
}


