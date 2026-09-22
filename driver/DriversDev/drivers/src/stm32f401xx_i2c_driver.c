#include "stm32f401xx_i2c_driver.h"
#include "stm32f401xx.h"
#include "stm32f401xx_rcc_driver.h"


static void I2C_GenerateStartCondition(I2C_RegDef_t *pI2Cx)
{
    pI2Cx->CR1 |= (1 << I2C_CR1_START);  // Set START bit
}

void I2C_GenerateStopCondition(I2C_RegDef_t *pI2Cx)
{
    pI2Cx->CR1 |= (1 << I2C_CR1_STOP);  // Set STOP bit
}

static void I2C_ExecuteAddressPhaseWrite(I2C_RegDef_t *pI2Cx, uint8_t SlaveAddr)
{
    SlaveAddr = SlaveAddr << 1;  // Make room for R/W bit
    SlaveAddr &= ~(1);           // Clear R/W bit (Write)
    pI2Cx->DR = SlaveAddr;
}

static void I2C_ExecuteAddressPhaseRead(I2C_RegDef_t *pI2Cx, uint8_t SlaveAddr)
{
    SlaveAddr = SlaveAddr << 1;  // Make room for R/W bit
    SlaveAddr |= 1;              // Set R/W bit (Read)
    pI2Cx->DR = SlaveAddr;
}

static void I2C_ClearADDRFlag(I2C_Handle_t *pI2CHandle)
{
    uint32_t dummy_read;

    // Read SR1 and SR2 to clear ADDR flag
    dummy_read = pI2CHandle->pI2Cx->SR1;
    dummy_read = pI2CHandle->pI2Cx->SR2;
    (void)dummy_read;  // Avoid unused variable warning
}
/*
 * Peripheral Clock Setup
 */
void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi){

	 if (EnorDi == ENABLE)
	    {
	        if (pI2Cx == I2C1)
	        {
	        	I2C1_PCLK_EN();
	        }
	        else if (pI2Cx == I2C2)
	        {
	        	I2C2_PCLK_EN();
	        }
	        else if (pI2Cx == I2C3)
	        {
	        	I2C3_PCLK_EN();
	        }



	    }
	    else
	    {
	        // Similar structure for DISABLE
	    	if (pI2Cx == I2C1)
	    	{
	    		I2C1_PCLK_DI();
	    	}
	    	else if (pI2Cx == I2C2)
	    	{
	    		I2C2_PCLK_DI();
	    	}
	    	else if (pI2Cx == I2C3)
	    	{
	    		I2C3_PCLK_DI();
	    	}


	    }
}
void I2C_PeripheralControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        pI2Cx->CR1 |= (1 << I2C_CR1_PE);
    }
    else
    {
        pI2Cx->CR1 &= ~(1 << I2C_CR1_PE);
    }
}
void I2C_ManageAcking(I2C_RegDef_t *pI2Cx, uint8_t EnorDi)
{
    if(EnorDi == I2C_ACK_ENABLE)
    {
        pI2Cx->CR1 |= (1 << I2C_CR1_ACK);
    }
    else
    {
        pI2Cx->CR1 &= ~(1 << I2C_CR1_ACK);
    }
}

void I2C_Init(I2C_Handle_t *pI2CHandle){

	uint32_t tempreg = 0;

	    // Enable clock for I2C peripheral
	    I2C_PeriClockControl(pI2CHandle->pI2Cx, ENABLE);

	    //ACK control

	    tempreg |= pI2CHandle->I2C_Config.I2C_ACKControl << 10;
	    pI2CHandle->pI2Cx->CR1 = tempreg;



	        //  Configure FREQ field in CR2
	        tempreg = 0;
	        tempreg |= RCC_GetPCLK1Value() / 1000000U;  // APB1 clock in MHz
	        pI2CHandle->pI2Cx->CR2 = (tempreg & 0x3F);

	        //  Configure device own address (for slave mode)
	        tempreg = 0;
	        tempreg |= pI2CHandle->I2C_Config.I2C_DeviceAddress << 1;
	        tempreg |= (1 << 14);  // Bit 14 should always be 1
	        pI2CHandle->pI2Cx->OAR1 = tempreg;

	        // Calculate and configure CCR
	        uint16_t ccr_value = 0;
	        tempreg = 0;

	        if (pI2CHandle->I2C_Config.I2C_SCLSpeed <= I2C_SCL_SPEED_SM)
	        {
	            // Standard mode
	            ccr_value = RCC_GetPCLK1Value() / (2 * pI2CHandle->I2C_Config.I2C_SCLSpeed);
	            tempreg |= (ccr_value & 0xFFF);
	        }
	        else
	        {
	            // Fast mode
	            tempreg |= (1 << 15);  // Set F/S bit for fast mode
	            tempreg |= (pI2CHandle->I2C_Config.I2C_FMDutyCycle << 14);

	            if (pI2CHandle->I2C_Config.I2C_FMDutyCycle == I2C_FM_DUTY_2)
	            {
	                ccr_value = RCC_GetPCLK1Value() / (3 * pI2CHandle->I2C_Config.I2C_SCLSpeed);
	            }
	            else
	            {
	                ccr_value = RCC_GetPCLK1Value() / (25 * pI2CHandle->I2C_Config.I2C_SCLSpeed);
	            }
	            tempreg |= (ccr_value & 0xFFF);
	        }
	        pI2CHandle->pI2Cx->CCR = tempreg;

	        //  Configure TRISE
	        if (pI2CHandle->I2C_Config.I2C_SCLSpeed <= I2C_SCL_SPEED_SM)
	        {
	            // Standard mode: max rise time = 1000ns
	            tempreg = (RCC_GetPCLK1Value() / 1000000U) + 1;
	        }
	        else
	        {
	            // Fast mode: max rise time = 300ns
	            tempreg = ((RCC_GetPCLK1Value() * 300) / 1000000000U) + 1;
	        }
	        pI2CHandle->pI2Cx->TRISE = (tempreg & 0x3F);




}
uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx , uint32_t FlagName)
{
	if(pI2Cx->SR1 & FlagName)
	{
		return FLAG_SET;
	}
	return FLAG_RESET;
}

void I2C_MasterSendData(I2C_Handle_t *pI2CHandle, uint8_t *pTxBuffer,
                        uint32_t Len, uint8_t SlaveAddr, uint8_t Sr)
{
    // 1. Generate START condition
    I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

    // 2. Wait until SB flag is set (START generated)
    while (!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_SB));

    // 3. Send slave address with R/W bit = 0 (Write)
    I2C_ExecuteAddressPhaseWrite(pI2CHandle->pI2Cx, SlaveAddr);

    // 4. Wait until ADDR flag is set
    while (!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_ADDR));

    // 5. Clear ADDR flag by reading SR1 then SR2
    I2C_ClearADDRFlag(pI2CHandle);

    // 6. Send data until Len = 0
    while (Len > 0)
    {
        // Wait for TXE (TX buffer empty)
        while (!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_TXE));

        pI2CHandle->pI2Cx->DR = *pTxBuffer;
        pTxBuffer++;
        Len--;
    }

    // 7. Wait for TXE and BTF before generating STOP
    while (!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_TXE));
    while (!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_BTF));

    // 8. Generate STOP condition (unless repeated start requested)
    if (Sr == I2C_DISABLE_SR)
    {
        I2C_GenerateStopCondition(pI2CHandle->pI2Cx);
    }
}

void I2C_MasterReceiveData(I2C_Handle_t *pI2CHandle,uint8_t *pRxBuffer, uint32_t Len, uint8_t SlaveAddr,uint8_t Sr)
{

	//1. Generate the START condition
	I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

	//2. confirm that start generation is completed by checking the SB flag in the SR1
	//   Note: Until SB is cleared SCL will be stretched (pulled to LOW)
	while( !  I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_FLAG_SB)   );

	//3. Send the address of the slave with r/nw bit set to R(1) (total 8 bits )
	I2C_ExecuteAddressPhaseRead(pI2CHandle->pI2Cx,SlaveAddr);

	//4. wait until address phase is completed by checking the ADDR flag in teh SR1
	while( !  I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_FLAG_ADDR)   );


	//procedure to read only 1 byte from slave
	if(Len == 1)
	{
		//Disable Acking
		I2C_ManageAcking(pI2CHandle->pI2Cx,I2C_ACK_DISABLE);


		//clear the ADDR flag
		I2C_ClearADDRFlag(pI2CHandle);

		//wait until  RXNE becomes 1
		while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_FLAG_RXNE) );

		//generate STOP condition
		if(Sr == I2C_DISABLE_SR )
			I2C_GenerateStopCondition(pI2CHandle->pI2Cx);

		//read data in to buffer
		*pRxBuffer = pI2CHandle->pI2Cx->DR;

	}


    //procedure to read data from slave when Len > 1
	if(Len > 1)
	{
		//clear the ADDR flag
		I2C_ClearADDRFlag(pI2CHandle);

		//read the data until Len becomes zero
		for ( uint32_t i = Len ; i > 0 ; i--)
		{
			//wait until RXNE becomes 1
			while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_FLAG_RXNE) );

			if(i == 2) //if last 2 bytes are remaining
			{
				//Disable Ack
				I2C_ManageAcking(pI2CHandle->pI2Cx,I2C_ACK_DISABLE);

				//generate STOP condition
				if(Sr == I2C_DISABLE_SR )
					I2C_GenerateStopCondition(pI2CHandle->pI2Cx);

			}

			//read the data from data register in to buffer
			*pRxBuffer = pI2CHandle->pI2Cx->DR;

			//increment the buffer address
			pRxBuffer++;

		}

	}

	//re-enable ACK
	if(pI2CHandle->I2C_Config.I2C_ACKControl == I2C_ACK_ENABLE)
	{
		I2C_ManageAcking(pI2CHandle->pI2Cx,I2C_ACK_ENABLE);
	}

}
