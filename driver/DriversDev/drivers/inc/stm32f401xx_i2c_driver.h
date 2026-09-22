

#ifndef INC_STM32F401XX_I2C_DRIVER_H_
#define INC_STM32F401XX_I2C_DRIVER_H_

#include "stm32f401xx.h"

/*
 * Configuration structure for I2Cx peripheral
 */
typedef struct
{
    uint32_t I2C_SCLSpeed;       // Standard or Fast mode
    uint8_t  I2C_DeviceAddress;  // Slave mode address (7-bit)
    uint8_t  I2C_ACKControl;     // ACK enable/disable
    uint8_t  I2C_FMDutyCycle;    // Fast mode duty cycle
} I2C_Config_t;

/*
 * Handle structure for I2Cx peripheral
 */
typedef struct
{
    I2C_RegDef_t  *pI2Cx;        // Pointer to I2C peripheral
    I2C_Config_t  I2C_Config;   // Configuration settings


} I2C_Handle_t;

#define I2C_ENABLE_SR      1
#define I2C_DISABLE_SR     0
/*
 * @I2C_SCLSpeed
 */
#define I2C_SCL_SPEED_SM       100000   // Standard mode 100kHz
#define I2C_SCL_SPEED_FM4K     400000   // Fast mode 400kHz
#define I2C_SCL_SPEED_FM2K     200000   // Fast mode 200kHz

/*
 * @I2C_ACKControl
 */
#define I2C_ACK_ENABLE         1
#define I2C_ACK_DISABLE        0

/*
 * @I2C_FMDutyCycle
 */
#define I2C_FM_DUTY_2          0        // Tlow/Thigh = 2
#define I2C_FM_DUTY_16_9       1        // Tlow/Thigh = 16/9

/*
 * I2C Status Register 1 flags
 */
#define I2C_FLAG_SB            (1 << 0)  // Start bit (Master)
#define I2C_FLAG_ADDR          (1 << 1)  // Address sent/matched
#define I2C_FLAG_BTF           (1 << 2)  // Byte transfer finished
#define I2C_FLAG_STOPF         (1 << 4)  // Stop detection (Slave)
#define I2C_FLAG_RXNE          (1 << 6)  // RX not empty
#define I2C_FLAG_TXE           (1 << 7)  // TX empty
#define I2C_FLAG_BERR          (1 << 8)  // Bus error
#define I2C_FLAG_ARLO          (1 << 9)  // Arbitration lost
#define I2C_FLAG_AF            (1 << 10) // Acknowledge failure
#define I2C_FLAG_OVR           (1 << 11) // Overrun/Underrun



/*
 * Peripheral Clock Setup
 */
void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi);
void I2C_PeripheralControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi);

void I2C_Init(I2C_Handle_t *pI2CHandle);
void I2C_DeInit(I2C_RegDef_t *pI2Cx);

/*
 * Data Send and Receive (Master mode - Blocking)
 */
void I2C_MasterSendData(I2C_Handle_t *pI2CHandle, uint8_t *pTxBuffer,
                        uint32_t Len, uint8_t SlaveAddr, uint8_t Sr);
void I2C_MasterReceiveData(I2C_Handle_t *pI2CHandle, uint8_t *pRxBuffer,
                          uint32_t Len, uint8_t SlaveAddr, uint8_t Sr);


void I2C_SlaveSendData(I2C_RegDef_t *pI2Cx, uint8_t data);
uint8_t I2C_SlaveReceiveData(I2C_RegDef_t *pI2Cx);



void I2C_PeripheralControl(I2C_RegDef_t *pI2Cx, uint8_t EnOrDi);

uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx , uint32_t FlagName);



void I2C_ManageAcking(I2C_RegDef_t *pI2Cx, uint8_t EnorDi);


void I2C_GenerateStopCondition(I2C_RegDef_t *pI2Cx);

void I2C_SlaveEnableDisableCallbackEvents(I2C_RegDef_t *pI2Cx,uint8_t EnorDi);

void I2C_ManageAcking(I2C_RegDef_t *pI2Cx, uint8_t EnorDi);



#endif /* INC_STM32F401XX_I2C_DRIVER_H_ */
