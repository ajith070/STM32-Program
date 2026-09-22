/*
 * stm32f401re_gpio_driver.c
 *
 *  Created on: Jan 27, 2026
 *      Author: user
 */
#include "stm32f401xx_gpio_driver.h"
#include "stm32f401xx.h"

// GPIO_PerClockControl(GPIOA,ENABLE);


/*********************************************************************
 * @fn          - GPIO_PeriClockControl
 *
 * @brief       - Enables or disables peripheral clock for GPIO port(GPIOA, GPIOB,....GPIOH)
 *
 * @param[in]   - pGPIOx: GPIO port base address
 * @param[in]   - EnorDi: ENABLE or DISABLE macros
 *
 * @return      - none
 *
 * @Note        - none
 *********************************************************************/
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t  EnorDi){

	if(EnorDi == ENABLE)
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_EN();
		}
		else if(pGPIOx == GPIOB)
		{
			GPIOB_PCLK_EN();
		}
		else if(pGPIOx == GPIOC)
		{
			GPIOC_PCLK_EN();
		}
		else if(pGPIOx == GPIOD)
		{
			GPIOD_PCLK_EN();
		}
		else if(pGPIOx == GPIOE)
		{
			GPIOE_PCLK_EN();
		}
		else if(pGPIOx == GPIOH)
		{
			GPIOH_PCLK_EN();
		}


	}

	else
	{
		if(pGPIOx == GPIOA )
		{
			GPIOA_PCLK_DI();
		}

		else if(pGPIOx == GPIOB)
		{
			GPIOB_PCLK_DI();
		}
		else if(pGPIOx == GPIOC)
		{
			GPIOC_PCLK_DI();
				}
		else if(pGPIOx == GPIOD)
		{
			GPIOD_PCLK_DI();
		}
		else if(pGPIOx == GPIOE)
		{
			GPIOE_PCLK_DI();
		}

		else if(pGPIOx == GPIOH)
		{
			GPIOH_PCLK_DI();
		}


	}

}

/*********************************************************************
 * @fn          - GPIO_Init
 *
 * @brief       - this function initializes the given GPIO port
 *
 * @param[in]   - pGPIOHandle : pointer to GPIO handle structure
 * @param[in]   - EnorDi: ENABLE or DISABLE macros
 *
 * @return      - none
 *
 * @Note        - refer macros for gpio configurations
 *********************************************************************/

void GPIO_Init(GPIO_Handle_t*pGPIOHandle){

	uint32_t temp=0;

	//enable peripheral clock
	GPIO_PeriClockControl (pGPIOHandle->pGPIOx, ENABLE);

	//1. GPIO MODE
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode<=GPIO_MODE_ANALOG)
	{
		temp=(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <<(2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));// to create a temp mask
		pGPIOHandle->pGPIOx->MODER&=~(0X3<<(2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //to clear the register
		pGPIOHandle->pGPIOx->MODER|=temp;  //set the value of register
		temp=0;
	}


	//interrupt modes
	else
	{
		if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode==GPIO_MODE_IT_FT)
		{
			EXTI->FTSR|=(1<<pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->RTSR&=~(1<<pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}

		else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode==GPIO_MODE_IT_RT)
		{
			EXTI->FTSR&=~(1<<pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->RTSR|=(1<<pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);

		}

		else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode==GPIO_MODE_IT_RFT)
		{
			EXTI->FTSR|=(1<<pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->RTSR|=(1<<pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		//2. configure gpio port selection in SYSCFG_EXTICR
		uint8_t temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber/4;
		uint8_t temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber%4;
		uint8_t portcode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);
		SYSCFG_PCLK_EN();
		SYSCFG->EXTICR[temp1]  = portcode << (temp2 * 4);

		//3. enable EXTI interrupt delivery using IMR
		EXTI->IMR|= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);


	}

	//speed
	temp=(pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed <<(2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));// to create a temp mask
	pGPIOHandle->pGPIOx->OSPEEDR&=~(0X3<<(2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //to clear the register
	pGPIOHandle->pGPIOx->OSPEEDR|=temp;  //set the value of register
	temp=0;

	//configure OUTPUT TYPE
	temp=(pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType <<(1*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));// to create a temp mask
	pGPIOHandle->pGPIOx->OTYPER&=~(0X1<<(1*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //to clear the register
	pGPIOHandle->pGPIOx->OTYPER|=temp;  //set the value of register
	temp=0;


	//pupd
	temp=(pGPIOHandle->GPIO_PinConfig.GPIO_PinPupdControl <<(2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));// to create a temp mask
	pGPIOHandle->pGPIOx->PUPDR&=~(0X3<<(2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //to clear the register
	pGPIOHandle->pGPIOx->PUPDR|=temp;  //set the value of register
	temp=0;

	//Alternate function
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode==GPIO_MODE_ALT){
		uint32_t temp1, temp2;
		temp1=(pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)/8;  //AFR Index
		temp2=(pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)%8;  //position inside AFR
		pGPIOHandle->pGPIOx->AFR[temp1]&=~((0xF)<<(4*temp2));  //Clear old AFR bits
		pGPIOHandle->pGPIOx->AFR[temp1]|=(pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode<<(4*temp2));
	}



}
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx){

	if(pGPIOx == GPIOA)
	{
		GPIOA_SET();
		GPIOA_CLEAR();
	}

	else if(pGPIOx == GPIOB)
	{
		GPIOB_SET();
		GPIOB_CLEAR();

	}
	else if(pGPIOx == GPIOC)
		{
		GPIOC_SET();
		GPIOC_CLEAR();

		}

	else if(pGPIOx == GPIOD)
		{
		GPIOD_SET();
		GPIOD_CLEAR();

		}

	else if(pGPIOx == GPIOE)
		{
		GPIOE_SET();
		GPIOE_CLEAR();

		}

	else if(pGPIOx == GPIOH)
		{
		GPIOH_SET();
		GPIOH_CLEAR();

		}




}


/*********************************************************************
 * @fn          - GPIO_Readfrominputpin
 *
 * @brief       - this function is used to read value in gpio pin
 *
 * @param[in]   - pGPIOx: points to GPIO_RegDef_t structure
 * @param[in]   - pin number
 *
 * @return      - uint8_t value(value inside that pin either 0 or 1)
 *
 * @Note        - none
 *********************************************************************/
uint8_t GPIO_Readfrominputpin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber){

	uint8_t value;
	value = (uint8_t)((pGPIOx->IDR >> PinNumber)& 0x00000001);
	return value;

}


/*********************************************************************
 * @fn          - GPIO_Readfrominputport
 *
 * @brief       - this function is used to read value in gpio port
 *
 * @param[in]   - pGPIOx: GPIO port base address

 *
 * @return      - uint16_t
 *
 * @Note        - none
 *********************************************************************/
uint16_t GPIO_Readfrominputport(GPIO_RegDef_t *pGPIOx){
	uint16_t value;
	value= (uint16_t)pGPIOx->IDR;
	return value;

}

/*********************************************************************
 * @fn          - GPIO_Writetoputputpin
 *
 * @brief       - this function is used to Write value to ouput pin
 *
 * @param[in]   - pGPIOx: GPIO port base address
 * @param[in]   - pin number
 * @param[in]   - value

 *
 * @return      - none
 *
 * @Note        - none
 *********************************************************************/

void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value){
	if (Value == GPIO_SET_PIN)
	{
		pGPIOx->ODR|=(1<<PinNumber);  //write 1
	}

	else
	{
		pGPIOx->ODR&=~(1<<PinNumber);  //write 0

	}
}

/*********************************************************************
 * @fn          - GPIO_Writetoputputport
 *
 * @brief       - this function is used to Write value to ouput port
 *
 * @param[in]   - pGPIOx: GPIO port base address
 *
 * @param[in]   - value

 *
 * @return      - none
 *
 * @Note        - none
 *********************************************************************/

void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint8_t Value){
	pGPIOx->ODR= Value;
}



/*********************************************************************
 * @fn          - GPIO_Toggle outputpin
 *
 * @brief       - this function is used to toggle a pin
 *
 * @param[in]   - pGPIOx: GPIO port base address
 * @param[in]   - pin number
 *

 *
 * @return      - none
 *
 * @Note        - none
 *********************************************************************/

void GPIO_Toggleoutputpin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber){
	pGPIOx->ODR^=(1<<PinNumber);
}





/*********************************************************************
 * @fn          - GPIO_IRQInterruptConfig
 *
 * @brief       - this function IS USED TO set or clear to enable od disable interrupt register
 *
 * @param[in]   - IRQNumber
 * @param[in]   - EnorDi
 *

 *
 * @return      - none
 *
 * @Note        - none
 *********************************************************************/


void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi){
	if(EnorDi == ENABLE){

		if(IRQNumber<=31)
		{
			//program ISER0 register
			*NVIC_ISER0|= (1<<IRQNumber);

		}
		else if(IRQNumber>31 && IRQNumber<64)  // 32 to 63
		{
			*NVIC_ISER1|=(1<<(IRQNumber%32));
		}

		else if(IRQNumber>=64 && IRQNumber<96)
		{
			*NVIC_ISER2|=(1<<(IRQNumber%64));
		}
	}
	else
	{
		if(IRQNumber<=31)
		{

			*NVIC_ICER0|= (1<<IRQNumber);
		}

		else if(IRQNumber>31 && IRQNumber<64)
		{
			*NVIC_ICER1|=(1<<(IRQNumber%32));

		}
		else if(IRQNumber>=64 && IRQNumber<96){

			*NVIC_ICER2|=(1<<(IRQNumber%64));

		}

	}

}

/*********************************************************************
 * @fn          - GPIO_IRQPriorityConfig
 *
 * @brief       - this function is used to configure priority
 *
 * @param[in]   - IRQNumber
 * @param[in]   - IRQPriority
 *

 *
 * @return      - none
 *
 * @Note        - none
 *********************************************************************/
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority){

	uint8_t iprx = IRQNumber/4; // choosing which ipr register ipr[0], ipr[1]...etc
	uint8_t iprx_section = IRQNumber%4;  //inside the selected ipr register which section to be chosen among the four sections
	uint8_t shift_amount = (8*iprx_section)+(8- NO_PR_BITS_IMPLEMENTED); //since only upper 4 bits are configured for priority first the bits should be shifted to the required section starting bit and 4 is added to shift it to the upper four bits
	*(NVIC_PR_BASE_ADDR + iprx) |= (IRQPriority << shift_amount); //goes to NVIC PR BASE ADDRESS and adds ipr to go to required IPR register and priority is shifted to required bit position and OR ed

}

/*********************************************************************
 * @fn          - GPIO_IRQHandling
 *
 * @brief       - this function is used to configure priority
 *
 * @param[in]   - pinnumber
 *

 *
 * @return      - none
 *
 * @Note        - none
 *********************************************************************/
void GPIO_IRQHandling(uint8_t PinNumber){

	//clear the EXTI PR register corresponding to pin number
	if(EXTI->PR & (1<<PinNumber)){  //this line checks if the interrupt is pending if the value is 1 enter the loop

		// clear
		EXTI->PR |= (1<<PinNumber); //the PR is cleared by writing 1 and interrupt process is complete. if not cleared the interrupt will keep executing infinitely



	}



}
