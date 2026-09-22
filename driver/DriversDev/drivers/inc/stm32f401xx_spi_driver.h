/*
 * stm32f401xx_spi_driver.h
 *
 *  Created on: Mar 2, 2026
 *      Author: user
 */

#ifndef INC_STM32F401XX_SPI_DRIVER_H_
#define INC_STM32F401XX_SPI_DRIVER_H_

#include "stm32f401xx.h"

/* configuration structure for SPIx peripheral*/


typedef struct{
	uint8_t SPI_DeviceMode;
	uint8_t SPI_BusConfig;
	uint8_t SPI_SclkSpeed;
	uint8_t SPI_DFF;
	uint8_t SPI_CPOL;
	uint8_t SPI_CPHA;
	uint8_t SPI_SSM;


}SPI_Config_t;

typedef struct{
	SPI_RegDef_t *pSPIx;   //pointer to spi base address
	SPI_Config_t SPI_PinConfig; //pin configuration settings

}SPI_Handle_t;

#define SPI_DEVICEMODE_MASTER           1
#define SPI_DEVICEMODE_SLAVE            0


#define SPI_BUSCONFIG_FD                1
#define SPI_BUSCONFIG_HD                2
#define SPI_BUSCONFIG_SIMPLEX_RXONLY    3



#define SPI_SCLK_PRE2                   0
#define SPI_SCLK_PRE4                   1
#define SPI_SCLK_PRE8                   2
#define SPI_SCLK_PRE16                  3
#define SPI_SCLK_PRE32                  4
#define SPI_SCLK_PRE64                  5
#define SPI_SCLK_PRE128                 6
#define SPI_SCLK_PRE256                 7

#define SPI_DFF_8BITS        0
#define SPI_DFF_16BITS       1



#define SPI_CPOL_HIGH                   1
#define SPI_CPOL_LOW                    0



#define SPI_CPHA_HIGH                   1
#define SPI_CPHA_LOW                    0



#define SPI_SSM_DI                      0
#define SPI_SSM_EN                      1

#define SPI_TXE_FLAG		(1 << SPI_SR_TXE)
#define SPI_RXNE_FLAG		(1 << SPI_SR_RXNE)
#define SPI_BUSY_FLAG		(1 << SPI_SR_BSY)


void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t  EnorDi);
void SPI_Init(SPI_Handle_t*pSPIHandle);

void SPI_DeInit(SPI_RegDef_t *pSPIx);

void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len);
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len);

void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDi);


#endif /* INC_STM32F401XX_SPI_DRIVER_H_ */
