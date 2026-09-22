/*
 * gpioinpt.c
 *
 *  Created on: Mar 1, 2026
 *      Author: user
 */

#include "stm32f401xx.h"
#include "stm32f401xx_gpio_driver.h"


//void delay(){
	//for(uint32_t i=0;i<50000; i++);
//}

int main()
 {

	 GPIO_Handle_t GpioLed, Gpioinpt;

	 //on board LED configuration
	 GpioLed.pGPIOx = GPIOA;
	 GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	 GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	 GpioLed.GPIO_PinConfig.GPIO_PinSpeed= GPIO_SPEED_LOW ;
	 GpioLed.GPIO_PinConfig.GPIO_PinOPType= OUTPUT_PUSHPULL;
	 GpioLed.GPIO_PinConfig.GPIO_PinPupdControl = GPIO_NOPULLUP_NOPULLDOWN;



	 GPIO_PeriClockControl(GPIOA, ENABLE);

	 GPIO_Init(&GpioLed);



	 //interrupt configuration
	 Gpioinpt.pGPIOx = GPIOC;
	 Gpioinpt.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	 Gpioinpt.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
	 Gpioinpt.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
	 Gpioinpt.GPIO_PinConfig.GPIO_PinPupdControl = GPIO_PULLUP;

	 GPIO_PeriClockControl(GPIOC, ENABLE);

	 GPIO_Init(&Gpioinpt);


	 GPIO_IRQInterruptConfig(40, ENABLE);
	 GPIO_IRQPriorityConfig(40, 10);

	 while(1);


 }

void EXTI15_10_IRQHandler(void)
{

	 GPIO_IRQHandling(GPIO_PIN_NO_13);
	 GPIO_Toggleoutputpin(GPIOA, GPIO_PIN_NO_5);
 }


