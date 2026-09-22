/*
 * stm32f401xx_spi_driver.c
 *
 *  Created on: Mar 12, 2026
 *      Author: user
 */

#include "stm32f401xx_spi_driver.h"
#include "stm32f401xx.h"

void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t  EnorDi)
{
	if(EnorDi==1)
	{
		if(pSPIx == SPI1)
		{
			SPI1_PCLK_EN();
		}

		else if(pSPIx == SPI2)
		{
			SPI2_PCLK_EN();
		}
		else if(pSPIx == SPI3)
		{
			SPI3_PCLK_EN();

		}
		else if(pSPIx == SPI4)
		{
			SPI4_PCLK_EN();
		}
	}

	else
	{
		if(pSPIx == SPI1)
	{
		SPI1_PCLK_DI();
	}

	else if(pSPIx == SPI2)
	{
		SPI2_PCLK_DI();
	}
	else if(pSPIx == SPI3)
	{
		SPI3_PCLK_DI();

	}
	else if(pSPIx == SPI4)
	{
		SPI4_PCLK_DI();
	}

	}
}


void SPI_Init(SPI_Handle_t*pSPIHandle){
	SPI_PeripheralControl(pSPIHandle->pSPIx, ENABLE);
	uint32_t tempreg=0;
	tempreg |= pSPIHandle->SPI_PinConfig.SPI_DeviceMode << SPI_CR1_MSTR; //config device mode

	if(pSPIHandle->SPI_PinConfig.SPI_BusConfig == SPI_BUSCONFIG_FD){

		tempreg &=~(1<<SPI_CR1_BIDIMODE);
	}

	else if(pSPIHandle->SPI_PinConfig.SPI_BusConfig == SPI_BUSCONFIG_HD){

			tempreg |=(1<<SPI_CR1_BIDIMODE);
		}

	else if(pSPIHandle->SPI_PinConfig.SPI_BusConfig == SPI_BUSCONFIG_SIMPLEX_RXONLY  ){

		tempreg &=~(1<<SPI_CR1_BIDIMODE);

		tempreg |=(1<<SPI_CR1_RXONLY);


	}

	tempreg |= pSPIHandle->SPI_PinConfig.SPI_SclkSpeed<< SPI_CR1_BR;

	tempreg |= pSPIHandle->SPI_PinConfig.SPI_CPOL << SPI_CR1_CPOL;

	tempreg |= pSPIHandle->SPI_PinConfig.SPI_CPHA << SPI_CR1_CPHA;

	tempreg |= pSPIHandle->SPI_PinConfig.SPI_DFF << SPI_CR1_DFF;

	pSPIHandle->pSPIx->CR1 = tempreg;





}

void SPI_DeInit(SPI_RegDef_t *pSPIx)
{
    if(pSPIx == SPI1)
    {
        SPI1_REG_RESET();
    }
    else if(pSPIx == SPI2)
    {
        SPI2_REG_RESET();
    }
    else if(pSPIx == SPI3)
    {
        SPI3_REG_RESET();
    }
    else if(pSPIx == SPI4)
    {
        SPI4_REG_RESET();
    }
}

uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName){
	if(pSPIx->SR & FlagName){
		return FLAG_SET;
	}
	return FLAG_RESET;
}

void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len){

	 while (Len > 0)
	    {
	        // 1. Wait until TXE is set (TX buffer empty)
	        while (SPI_GetFlagStatus(pSPIx, SPI_TXE_FLAG)==FLAG_RESET);

	        // 2. Check DFF bit in CR1
	        if (pSPIx->CR1 & (1 << SPI_CR1_DFF))
	        {
	            // 16-bit DFF
	            pSPIx->DR = *((uint16_t*)pTxBuffer);
	            Len --;
	            Len --;
	            (uint16_t*)pTxBuffer++;
	        }
	        else
	        {
	            // 8-bit DFF
	            pSPIx->DR = *pTxBuffer;
	            Len--;
	            pTxBuffer++;
	        }
	    }
}


void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len){

	while (Len > 0)
		    {
		        // 1. Wait until TXE is set (RX buffer empty)
		        while (SPI_GetFlagStatus(pSPIx, SPI_RXNE_FLAG)==FLAG_RESET);

		        // 2. Check DFF bit in CR1
		        if (pSPIx->CR1 & (1 << SPI_CR1_DFF))
		        {
		            // 16-bit DFF
		             *((uint16_t*)pRxBuffer)= pSPIx->DR ;
		            Len --;
		            Len --;
		            (uint16_t*)pRxBuffer++;
		        }
		        else
		        {
		            // 8-bit DFF
		            *pRxBuffer = pSPIx->DR;
		            Len--;
		            pRxBuffer++;
		        }
		    }
}


void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        pSPIx->CR1 |= (1 << SPI_CR1_SSI);
    }
    else
    {
        pSPIx->CR1 &= ~(1 << SPI_CR1_SSI);
    }
}
