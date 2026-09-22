/*
 * STM32f401xx.h
 *
 *  Created on: Jan 20, 2026
 *      Author: user
 */

#ifndef INC_STM32F401XX_H_
#include<stdio.h>
#include<stdint.h>

#define INC_STM32F401XX_H_

#define __vo            volatile

/*processor definition*/
/*ARM cortex m4 processor NVIC ICERx register address*/
#define NVIC_ISER0        ((__vo uint32_t*)0XE000E100)
#define NVIC_ISER1        ((__vo uint32_t*)0XE000E104)
#define NVIC_ISER2        ((__vo uint32_t*)0XE000E108)
#define NVIC_ISER3        ((__vo uint32_t*)0XE000E10C)

/* ARM CORTEX M4 processor ICERx register address*/
#define NVIC_ICER0        ((__vo uint32_t*)0XE000E180)
#define NVIC_ICER1        ((__vo uint32_t*)0XE000E184)
#define NVIC_ICER2        ((__vo uint32_t*)0XE000E188)
#define NVIC_ICER3        ((__vo uint32_t*)0XE000E18C)

/*ARM CORTEX M4 processor priority register address calculation*/
#define NVIC_PR_BASE_ADDR  ((__vo uint32_t*)0XE000E400)



/* memory base addresses*/
#define FLASH_BASEADDR                       0x08000000U // all addresses from reference manual
#define ROM_BASEADDR                      	 0x1FFF0000U
#define SRAM1_BASEADDR                       0x20000000U





/*peripheral BUS base address*/
#define APB1_PERIBASEADDR                    0x40000000U
#define APB2_PERIBASEADDR                    0x40010000U
#define AHB1_PERIBASEADDR                    0x40020000U
#define AHB2_PERIBASEADDR                    0x50000000U







/*peripherals in AHB1 BUS*/
#define GPIOA_PERI_BASEADDR					(AHB1_PERIBASEADDR+0X0000)
#define GPIOB_PERI_BASEADDR					(AHB1_PERIBASEADDR+0X0400)
#define GPIOC_PERI_BASEADDR					(AHB1_PERIBASEADDR+0X0800)
#define GPIOD_PERI_BASEADDR					(AHB1_PERIBASEADDR+0X0C00)
#define GPIOE_PERI_BASEADDR					(AHB1_PERIBASEADDR+0X1000)
#define GPIOH_PERI_BASEADDR					(AHB1_PERIBASEADDR+0X1C00)
#define CRC_PERI_BASEADDR					(AHB1_PERIBASEADDR+0X3000)
#define RCC_PERI_BASEADDR					(AHB1_PERIBASEADDR+0X3800)
#define FLASH_INTER_REG_PERI_BASEADDR		(AHB1_PERIBASEADDR+0X3C00)
#define DMA1_PERI_BASEADDR					(AHB1_PERIBASEADDR+0X6000)
#define DMA2_PERI_BASEADDR					(AHB1_PERIBASEADDR+0X6400)




/*peripherals in AHB2 bus*/
#define USB_OTG_FS_PERI_BASEADDR            (AHB2_PERIBASEADDR+0X0000)





/*peripherals in APB1*/
#define TIM2_PERI_BASEADDR                  (APB1_PERIBASEADDR+0X0000)
#define TIM3_PERI_BASEADDR                  (APB1_PERIBASEADDR+0X0400)
#define TIM4_PERI_BASEADDR                  (APB1_PERIBASEADDR+0X0800)
#define TIM5_PERI_BASEADDR                  (APB1_PERIBASEADDR+0X0C00)
#define RTC_BKP_REG_PERI_BASEADDR           (APB1_PERIBASEADDR+0X2800)
#define WWDG_PERI_BASEADDR                  (APB1_PERIBASEADDR+0X2C00)
#define IWDG_PERI_BASEADDR                  (APB1_PERIBASEADDR+0X3000)
#define I2S2ext_PERI_BASEADDR               (APB1_PERIBASEADDR+0X3400)
#define SPI2_PERI_BASEADDR                  (APB1_PERIBASEADDR+0X3800)
#define SPI3_PERI_BASEADDR                  (APB1_PERIBASEADDR+0X3C00)
#define I2S3ext_PERI_BASEADDR               (APB1_PERIBASEADDR+0X4000)
#define USART2_PERI_BASEADDR                (APB1_PERIBASEADDR+0X4400)
#define I2C1_PERI_BASEADDR                  (APB1_PERIBASEADDR+0X5400)
#define I2C2_PERI_BASEADDR                  (APB1_PERIBASEADDR+0X5800)
#define I2C3_PERI_BASEADDR                  (APB1_PERIBASEADDR+0X5C00)
#define PWR_PERI_BASEADDR                   (APB1_PERIBASEADDR+0X7000)





/*peripherals in APB2*/
#define TIM1_PERI_BASEADDR                  (APB2_PERIBASEADDR+0X0000)
#define USART1_PERI_BASEADDR                (APB2_PERIBASEADDR+0X1000)
#define USART6_PERI_BASEADDR                (APB2_PERIBASEADDR+0X1400)
#define ADC1_PERI_BASEADDR                  (APB2_PERIBASEADDR+0X2000)
#define SDIO_PERI_BASEADDR                  (APB2_PERIBASEADDR+0X2C00)
#define SPI1_PERI_BASEADDR                  (APB2_PERIBASEADDR+0X3000)
#define SPI4_PERI_BASEADDR                  (APB2_PERIBASEADDR+0X3400)
#define SYSCFG_PERI_BASEADDR                (APB2_PERIBASEADDR+0X3800)
#define EXTI_PERI_BASEADDR                  (APB2_PERIBASEADDR+0X3C00)
#define TIM9_PERI_BASEADDR                  (APB2_PERIBASEADDR+0X4000)
#define TIM10_PERI_BASEADDR                 (APB2_PERIBASEADDR+0X4400)
#define TIM11_PERI_BASEADDR                 (APB2_PERIBASEADDR+0X4800)

/*GPIO register definition*/
typedef struct{
	__vo uint32_t MODER;
	__vo uint32_t OTYPER;
	__vo uint32_t OSPEEDR;
	__vo uint32_t PUPDR;
	__vo uint32_t IDR;
	__vo uint32_t ODR;
	__vo uint32_t BSRR;
	__vo uint32_t LCKR;
	__vo uint64_t AFR[2];


}GPIO_RegDef_t;

/*RCC register definitions*/
typedef struct{
	__vo uint32_t CR;
	__vo uint32_t PLLCFGR;
	__vo uint32_t CFGR;
	__vo uint32_t CIR;
	__vo uint32_t AHB1RSTR;
	__vo uint32_t AHB2RSTR;
		 uint32_t RESERVED1;
		 uint32_t RESERVED2;
	__vo uint32_t APB1RSTR;
	__vo uint32_t APB2RSTR;
		 uint32_t RESERVED3;
		 uint32_t RESERVED4;
	__vo uint32_t AHB1ENR;
	__vo uint32_t AHB2ENR;
		 uint32_t RESERVED5;
		 uint32_t RESERVED6;
	__vo uint32_t APB1ENR;
	__vo uint32_t APB2ENR;
	 	 uint32_t RESERVED7;
	 	 uint32_t RESERVED8;
	__vo uint32_t AHB1LPENR;
	__vo uint32_t AHB2LPENR;
	     uint32_t RESERVED9;
		 uint32_t RESERVED10;
	__vo uint32_t APB1LPENR;
	__vo uint32_t APB2LPENR;
	  	 uint32_t RESERVED11;
	  	 uint32_t RESERVED12;
    __vo uint32_t BDCR;
    __vo uint32_t CSR;
		 uint32_t RESERVED13;
	 	 uint32_t RESERVED14;
	__vo uint32_t SSCGR;
	__vo uint32_t PLLI2SCFGR;



}RCC_RegDef_t;

/*EXTI register configuration*/
typedef struct{
	__vo uint32_t IMR;// Interrupt Mask Register         - Offset: 0x00
	__vo uint32_t EMR;  // Event Mask Register             - Offset: 0x04
	__vo uint32_t RTSR; // Rising Trigger Selection Reg    - Offset: 0x08
	__vo uint32_t FTSR;  // Falling Trigger Selection Reg   - Offset: 0x0C
	__vo uint32_t SWIER; // Software Interrupt Event Reg    - Offset: 0x10
	__vo uint32_t PR;   // Pending Register                - Offset: 0x14
}EXTI_RegDef_t;


/*SYSCFG register configuration*/
typedef struct{
	__vo uint32_t MEMRMP; // Memory Remap Register    - Offset: 0x00
	__vo uint32_t PMC;  // Peripheral Mode Config      - Offset: 0x04
	__vo uint32_t EXTICR[4]; // External Interrupt Config   - Offset: 0x08-0x14
	__vo uint32_t CMPCR;  // Compensation Cell Control   - Offset: 0x20

}SYSCFG_RegDef_t;




#define GPIOA    (GPIO_RegDef_t *)(GPIOA_PERI_BASEADDR)
#define GPIOB    (GPIO_RegDef_t *)(GPIOB_PERI_BASEADDR)
#define GPIOC    (GPIO_RegDef_t *)(GPIOC_PERI_BASEADDR)
#define GPIOD    (GPIO_RegDef_t *)(GPIOD_PERI_BASEADDR)
#define GPIOE    (GPIO_RegDef_t *)(GPIOE_PERI_BASEADDR)
#define GPIOH    (GPIO_RegDef_t *)(GPIOH_PERI_BASEADDR)



#define RCC      ((RCC_RegDef_t*)RCC_PERI_BASEADDR)
#define EXTI     ((EXTI_RegDef_t*)EXTI_PERI_BASEADDR)
#define SYSCFG   ((SYSCFG_RegDef_t*)SYSCFG_PERI_BASEADDR)

/*clock enable and disable macros*/

#define GPIOA_PCLK_EN()   (RCC->AHB1ENR|=(1<<0))
#define GPIOB_PCLK_EN()   (RCC->AHB1ENR|=(1<<1))
#define GPIOC_PCLK_EN()   (RCC->AHB1ENR|=(1<<2))
#define GPIOD_PCLK_EN()   (RCC->AHB1ENR|=(1<<3))
#define GPIOE_PCLK_EN()   (RCC->AHB1ENR|=(1<<4))
#define GPIOH_PCLK_EN()   (RCC->AHB1ENR|=(1<<7))



#define GPIOA_PCLK_DI()   (RCC->AHB1ENR&=~(1<<0))
#define GPIOB_PCLK_DI()   (RCC->AHB1ENR&=~(1<<1))
#define GPIOC_PCLK_DI()   (RCC->AHB1ENR&=~(1<<2))
#define GPIOD_PCLK_DI()   (RCC->AHB1ENR&=~(1<<3))
#define GPIOE_PCLK_DI()   (RCC->AHB1ENR&=~(1<<4))
#define GPIOH_PCLK_DI()   (RCC->AHB1ENR&=~(1<<7))


#define GPIOA_SET()     (RCC->AHB1RSTR|=(1<<0))
#define GPIOB_SET()     (RCC->AHB1RSTR|=(1<<1))
#define GPIOC_SET()     (RCC->AHB1RSTR|=(1<<2))
#define GPIOD_SET()     (RCC->AHB1RSTR|=(1<<3))
#define GPIOE_SET()     (RCC->AHB1RSTR|=(1<<4))
#define GPIOH_SET()     (RCC->AHB1RSTR|=(1<<7))

#define GPIOA_CLEAR()     (RCC->AHB1RSTR&=~(1<<0))
#define GPIOB_CLEAR()     (RCC->AHB1RSTR&=~(1<<1))
#define GPIOC_CLEAR()     (RCC->AHB1RSTR&=~(1<<2))
#define GPIOD_CLEAR()     (RCC->AHB1RSTR&=~(1<<3))
#define GPIOE_CLEAR()     (RCC->AHB1RSTR&=~(1<<4))
#define GPIOH_CLEAR()     (RCC->AHB1RSTR&=~(1<<7))



#define ENABLE            1
#define DISABLE           0
#define SET               ENABLE
#define RESET             DISABLE
#define GPIO_PIN_SET      SET
#define GPIO_PIN_RESET    RESET
#define FLAG_RESET        RESET
#define FLAG_SET          SET

/* clock enable macros for SYSCFG peripheral*/
#define SYSCFG_PCLK_EN()  (RCC->APB2ENR|=(1<<14))


/*this macro returns a code between 0 t0 7 for given GPIO base address*/
#define GPIO_BASEADDR_TO_CODE(x) ((x == GPIOA)?0:\
	                               (x == GPIOB)?1:\
	                               (x == GPIOC)?2:\
	                               (x == GPIOD)?3:\
	                               (x == GPIOE)?4:\
	                               (x == GPIOH)?7:0)



#define GPIO_SET_PIN      1
#define GPIO_CLEAR_PIN    0
#define NO_PR_BITS_IMPLEMENTED  4


#define SPI_CR1_CPHA     0
#define SPI_CR1_CPOL     1
#define SPI_CR1_MSTR     2
#define SPI_CR1_BR       3
#define SPI_CR1_SPE      6
#define SPI_CR1_LSBFIRST 7
#define SPI_CR1_SSI      8
#define SPI_CR1_SSM      9
#define SPI_CR1_RXONLY   10
#define SPI_CR1_DFF      11
#define SPI_CR1_CRCNEXT  12
#define SPI_CR1_CRCEN    13
#define SPI_CR1_BIDIOE   14
#define SPI_CR1_BIDIMODE 15

//bit position definitions SPI_CR2


#define SPI_CR2_RXDMAEN		0
#define SPI_CR2_TXDMAEN		1
#define SPI_CR2_SSOE		2
#define SPI_CR2_FRF			4
#define SPI_CR2_ERRIE		5
#define SPI_CR2_RXNEIE		6
#define SPI_CR2_TXEIE		7

//bit position definitions SPI_SR

#define SPI_SR_RXNE			0
#define SPI_SR_TXE			1
#define SPI_SR_CHSIDE		2
#define SPI_SR_UDR			3
#define SPI_SR_CRCCERR 		4
#define SPI_SR_MODF			5
#define SPI_SR_OVR			6
#define SPI_SR_BSY			7
#define SPI_SR_FRE			8


// Bit position definitions for I2C_CR1 register

#define I2C_CR1_PE            0
#define I2C_CR1_SMBUS         1
#define I2C_CR1_SMBTYPE       3
#define I2C_CR1_ENARP         4
#define I2C_CR1_ENPEC         5
#define I2C_CR1_ENGC          6
#define I2C_CR1_NOSTRETCH     7
#define I2C_CR1_START         8
#define I2C_CR1_STOP          9
#define I2C_CR1_ACK           10
#define I2C_CR1_POS           11
#define I2C_CR1_PEC           12
#define I2C_CR1_ALERT         13
#define I2C_CR1_SWRST         15



/* Bit position definitions for I2C_CR2 register */

#define I2C_CR2_FREQ    	  0
#define I2C_CR2_ITERREN  	  8
#define I2C_CR2_ITEVTEN   	  9
#define I2C_CR2_ITBUFEN       10
#define I2C_CR2_DMAEN         11
#define I2C_CR2_LAST          12


/* Bit position definitions for I2C_OAR1  register */

#define I2C_OAR1_ADD0       0
#define I2C_OAR1_ADD71      1   // Bits 7:1
#define I2C_OAR1_ADD98      8   // Bits 9:8
#define I2C_OAR1_ADDMODE    15


/* Bit position definitions for I2C_SR1  register */


#define I2C_SR1_SB          0
#define I2C_SR1_ADDR        1
#define I2C_SR1_BTF         2
#define I2C_SR1_ADD10       3
#define I2C_SR1_STOPF       4
#define I2C_SR1_RxNE        6
#define I2C_SR1_TxE         7
#define I2C_SR1_BERR        8
#define I2C_SR1_ARLO        9
#define I2C_SR1_AF          10
#define I2C_SR1_OVR         11
#define I2C_SR1_PECERR      12
#define I2C_SR1_TIMEOUT     14
#define I2C_SR1_SMBALERT    15




#define I2C1_PCLK_EN()    (RCC->APB1ENR|=(1<<21))
#define I2C2_PCLK_EN()    (RCC->APB1ENR|=(1<<22))
#define I2C3_PCLK_EN()    (RCC->APB1ENR|=(1<<23))


#define I2C1_PCLK_DI()    (RCC->APB1ENR&=~(1<<21))
#define I2C2_PCLK_DI()    (RCC->APB1ENR&=~(1<<22))
#define I2C3_PCLK_DI()    (RCC->APB1ENR&=~(1<<23))


#define SPI2_PCLK_EN()    (RCC->APB1ENR|=(1<<14))
#define SPI3_PCLK_EN()    (RCC->APB1ENR|=(1<<15))

#define SPI2_PCLK_DI()    (RCC->APB1ENR&=~(1<<14))
#define SPI3_PCLK_DI()    (RCC->APB1ENR&=~(1<<15))


#define SPI1_PCLK_EN()    (RCC->APB2ENR|=(1<<12))
#define SPI4_PCLK_EN()    (RCC->APB2ENR|=(1<<13))


#define SPI1_PCLK_DI()    (RCC->APB1ENR&=~(1<<12))
#define SPI4_PCLK_DI()    (RCC->APB1ENR&=~(1<<13))

/* USART Clock Enable */
#define USART1_PCLK_EN()   (RCC->APB2ENR |= (1 << 4))
#define USART2_PCLK_EN()   (RCC->APB1ENR |= (1 << 17))
#define USART6_PCLK_EN()   (RCC->APB2ENR |= (1 << 5))


/* USART Clock disable */
#define USART1_PCLK_DI()   (RCC->APB2ENR &= ~(1 << 4))
#define USART2_PCLK_DI()   (RCC->APB1ENR &= ~(1 << 17))
#define USART6_PCLK_DI()   (RCC->APB2ENR &= ~(1 << 5))


/*I2C register definition*/
typedef struct{
	__vo uint32_t CR1;
	__vo uint32_t CR2;
	__vo uint32_t OAR1;
	__vo uint32_t OAR2;
	__vo uint32_t DR;
	__vo uint32_t SR1;
	__vo uint32_t SR2;
	__vo uint32_t CCR;
	__vo uint32_t TRISE;
	__vo uint32_t FLTR;


}I2C_RegDef_t;

#define I2C1   (I2C_RegDef_t*)(I2C1_PERI_BASEADDR)
#define I2C2   (I2C_RegDef_t*)(I2C2_PERI_BASEADDR)
#define I2C3   (I2C_RegDef_t*)(I2C3_PERI_BASEADDR)



/*SPI register definition*/
typedef struct{
	__vo uint32_t CR1;
		 uint32_t reserved;
	__vo uint32_t SR;
	__vo uint32_t DR;
	__vo uint32_t CRCPR;
	__vo uint32_t RXCRCR;
	__vo uint32_t TXCRCR;
	__vo uint32_t I2SCFGR;
	__vo uint32_t I2SPR;



}SPI_RegDef_t;

#define SPI1     ((SPI_RegDef_t*)SPI1_PERI_BASEADDR)
#define SPI2     ((SPI_RegDef_t*)SPI2_PERI_BASEADDR)
#define SPI3     ((SPI_RegDef_t*)SPI3_PERI_BASEADDR)
#define SPI4     ((SPI_RegDef_t*)SPI4_PERI_BASEADDR)


/*
 * Peripheral register definition structure for USART
 * */

typedef struct{

	__vo uint32_t SR;				//offset :0x00
	__vo uint32_t DR; 					//offset :0x04
	__vo uint32_t BRR; 				//offset :0x08
	__vo uint32_t CR1; 				//offset :0x0C
	__vo uint32_t CR2; 				//offset :0x10
	__vo uint32_t CR3; 				//offset :0x14
	__vo uint32_t GTPR; 				//offset :0x18


}USART_Regdef_t;

#define USART1          (USART_Regdef_t *)(USART1_PERI_BASEADDR)
#define USART2          (USART_Regdef_t *)(USART2_PERI_BASEADDR)
#define USART6          (USART_Regdef_t *)(USART6_PERI_BASEADDR)


/* SPI Reset Macros */


#define SPI1_REG_RESET()   do{ \
    (RCC->APB2RSTR |= (1 << 12)); \
    (RCC->APB2RSTR &= ~(1 << 12)); \
}while(0)

#define SPI2_REG_RESET()   do{ \
    (RCC->APB1RSTR |= (1 << 14)); \
    (RCC->APB1RSTR &= ~(1 << 14)); \
}while(0)

#define SPI3_REG_RESET()   do{ \
    (RCC->APB1RSTR |= (1 << 15)); \
    (RCC->APB1RSTR &= ~(1 << 15)); \
}while(0)

#define SPI4_REG_RESET()   do{ \
    (RCC->APB2RSTR |= (1 << 13)); \
    (RCC->APB2RSTR &= ~(1 << 13)); \
}while(0)











#endif /* INC_STM32F401XX_H_*/
