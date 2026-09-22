#include "stm32f401xx_rcc_driver.h"

/*
 * PreScaler tables
 */
uint16_t AHB_PreScaler[8] = {2,4,8,16,64,128,256,512};
uint8_t APB1_PreScaler[4] = {2,4,8,16};


uint32_t RCC_GetPLLOutputClock(void)
{
    uint32_t pllm, plln, pllp;
    uint32_t pll_input_clk;

    // PLL source: HSI or HSE?
    if((RCC->PLLCFGR >> 22) & 0x1)
        pll_input_clk = 8000000;   // HSE
    else
        pll_input_clk = 16000000;  // HSI

    pllm = (RCC->PLLCFGR >> 0) & 0x3F;
    plln = (RCC->PLLCFGR >> 6) & 0x1FF;
    pllp = (((RCC->PLLCFGR >> 16) & 0x3) + 1) * 2;  // 0→2, 1→4, 2→6, 3→8

    return (pll_input_clk / pllm) * plln / pllp;
}

/*
 * Get PCLK1 value
 */
uint32_t RCC_GetPCLK1Value(void)
{
	uint32_t pclk1 = 0, SystemClk = 0;
	uint8_t clksrc, temp, ahbp, apb1p;

	// Clock source
	clksrc = ((RCC->CFGR >> 2) & 0x3);

	if(clksrc == 0)
	{
		SystemClk = 16000000;   // HSI
	}
	else if(clksrc == 1)
	{
		SystemClk = 8000000;    // HSE
	}
	else if(clksrc == 2)
	{
		SystemClk = RCC_GetPLLOutputClock();
	}

	// AHB prescaler
	temp = ((RCC->CFGR >> 4) & 0xF);

	if(temp < 8)
	{
		ahbp = 1;
	}
	else
	{
		ahbp = AHB_PreScaler[temp - 8];
	}

	// APB1 prescaler
	temp = ((RCC->CFGR >> 10) & 0x7);

	if(temp < 4)
	{
		apb1p = 1;
	}
	else
	{
		apb1p = APB1_PreScaler[temp - 4];
	}

	pclk1 = (SystemClk / ahbp) / apb1p;

	return pclk1;
}


uint32_t RCC_GetPCLK2Value(void)
{
	uint32_t pclk2 = 0, SystemClk = 0;
	uint8_t clksrc, temp, ahbp, apb2p;

	clksrc = ((RCC->CFGR >> 2) & 0x3);

	if(clksrc == 0)
	{
		SystemClk = 16000000;
	}
	else if(clksrc == 1)
	{
		SystemClk = 8000000;
	}
	else if(clksrc == 2)
	{
		SystemClk = RCC_GetPLLOutputClock();
	}

	// AHB prescaler
	temp = ((RCC->CFGR >> 4) & 0xF);

	if(temp < 8)
	{
		ahbp = 1;
	}
	else
	{
		ahbp = AHB_PreScaler[temp - 8];
	}

	// APB2 prescaler
	temp = ((RCC->CFGR >> 13) & 0x7);

	if(temp < 4)
	{
		apb2p = 1;
	}
	else
	{
		apb2p = AHB_PreScaler[temp - 4];
	}

	pclk2 = (SystemClk / ahbp) / apb2p;

	return pclk2;
}
