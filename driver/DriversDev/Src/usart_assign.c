#include "stm32f401xx.h"
#include "stm32f401xx_gpio_driver.h"
#include "stm32f401xx_usart_driver.h"
#include <string.h>

USART_Handle_t USART2_Handle;

void USART2_GPIO_Init(void)
{
    GPIO_Handle_t USART2_GPIO;

    USART2_GPIO.pGPIOx = GPIOA;

    // PA2 -> USART2_TX
    USART2_GPIO.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_2;
    USART2_GPIO.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALT;
    USART2_GPIO.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
    USART2_GPIO.GPIO_PinConfig.GPIO_PinOPType = OUTPUT_PUSHPULL;
    USART2_GPIO.GPIO_PinConfig.GPIO_PinPupdControl = GPIO_PULLUP;
    USART2_GPIO.GPIO_PinConfig.GPIO_PinAltFunMode = 7;

    GPIO_Init(&USART2_GPIO);

    // PA3 -> USART2_RX
    USART2_GPIO.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_3;

    GPIO_Init(&USART2_GPIO);
}

void USART2_Init(void)
{
    USART2_Handle.pUSARTx = USART2;

    USART2_Handle.USART_Config.USART_Mode = USART_MODE_TXRX;
    USART2_Handle.USART_Config.USART_Baud = USART_STD_BAUD_115200;
    USART2_Handle.USART_Config.USART_NoOfStopBits = USART_STOPBITS_1;
    USART2_Handle.USART_Config.USART_WordLength = USART_WORDLEN_8BITS;
    USART2_Handle.USART_Config.USART_ParityControl = USART_PARITY_DISABLE;
    USART2_Handle.USART_Config.USART_HWFlowControl = USART_HW_FLOW_CTRL_NONE;

    USART_Init(&USART2_Handle);
}

int main(void)
{
    uint8_t received_data;

    USART2_GPIO_Init();
    USART2_Init();

    char message[] = "Hello from STM32\r\n";

    USART_SendData(&USART2_Handle, (uint8_t *)message, strlen(message));

    while(1)
    {
        USART_ReceiveData(&USART2_Handle, &received_data,1);

        USART_SendData(&USART2_Handle, (uint8_t *)"Received: ", 10);

        USART_SendData(&USART2_Handle, &received_data,1);

        USART_SendData(&USART2_Handle, (uint8_t *)"\r\n",2);
    }
}
