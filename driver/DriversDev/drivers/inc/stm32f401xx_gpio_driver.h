/*
 * stm32f401re_gpio_driver.h
 *
 *  Created on: Jan 27, 2026
 *      Author: user
 */

#ifndef INC_STM32F401XX_GPIO_DRIVER_H_
#define INC_STM32F401XX_GPIO_DRIVER_H_

#include "stm32f401xx.h"

/*configuration structure for GPIO pin*/
typedef struct{
	uint8_t GPIO_PinNumber;   //pin number
	uint8_t GPIO_PinMode;     //mode: input/output/altin/analog
	uint8_t GPIO_PinSpeed;    // speed: low, med, high, very high
	uint8_t GPIO_PinPupdControl; //pull up/pull down cofiguration
	uint8_t GPIO_PinOPType;       //output type:push pull/open drain
	uint8_t GPIO_PinAltFunMode;    //alternate function
}GPIO_PinConfig_t;



/*handle structure for GPIO pin*/
typedef struct{
	GPIO_RegDef_t *pGPIOx;         //points to GPI port base address
	GPIO_PinConfig_t GPIO_PinConfig;       //pin configuration settings
}GPIO_Handle_t;


#define GPIO_PIN_NO_0           0
#define GPIO_PIN_NO_1           1
#define GPIO_PIN_NO_2           2
#define GPIO_PIN_NO_3           3
#define GPIO_PIN_NO_4           4
#define GPIO_PIN_NO_5           5
#define GPIO_PIN_NO_6           6
#define GPIO_PIN_NO_7           7
#define GPIO_PIN_NO_8           8
#define GPIO_PIN_NO_9           9
#define GPIO_PIN_NO_10           10
#define GPIO_PIN_NO_11          11
#define GPIO_PIN_NO_12          12
#define GPIO_PIN_NO_13          13
#define GPIO_PIN_NO_14          14
#define GPIO_PIN_NO_15          15

/* GPIO modes*/
#define GPIO_MODE_IN            0  //INPUT MODE 00
#define GPIO_MODE_OUT           1  //OUTPUT 01
#define GPIO_MODE_ALT           2  //ALT function mode 10
#define GPIO_MODE_ANALOG        3  // analog mode 11
#define GPIO_MODE_IT_FT         4  //interrupt mode for falling edge
#define GPIO_MODE_IT_RT         5  //interrupt mode for rising edge
#define GPIO_MODE_IT_RFT        6  //interrupt mode for rising and falling edge


/*GPIO SPEED*/
#define GPIO_SPEED_LOW          0
#define GPIO_SPEED_MEDIUM       1
#define GPIO_SPEED_HIGH         2
#define GPIO_SPEED_VERY_HIGH    3

/*GPIO PUPD CONTROLS*/
#define GPIO_NOPULLUP_NOPULLDOWN 0
#define GPIO_PULLUP               1
#define GPIO_PULLDOWN            2

/*GPIO PIN OUTPUT TYPE*/
#define OUTPUT_PUSHPULL          0
#define OPEN_DRAIN               1



void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t  EnorDi);

void GPIO_Init(GPIO_Handle_t*pGPIOHandle);

void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

uint8_t GPIO_Readfrominputpin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_Readfrominputport(GPIO_RegDef_t *pGPIOx);


void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint8_t Value);

void GPIO_Toggleoutputpin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);

/*IRQ configuration and ISR handling*/
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void GPIO_IRQHandling(uint8_t PinNumber);





#endif /* INC_STM32F401XX_GPIO_DRIVER_H_ */
