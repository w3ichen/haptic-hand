#ifndef __STM32F446ZE_GPIO_H_
#define __STM32F446ZE_GPIO_H_

#ifdef __cplusplus
 extern "C" {
#endif

/**** Include files *****/
#include "main.h"

/**** Gpio Configuration Structures *****/

// GPIO Registers
typedef struct
{
  volatile uint32_t MODER_R;    /*!< GPIO port mode register,               Address offset: 0x00      */
  volatile uint32_t OTYPER_R;   /*!< GPIO port output type register,        Address offset: 0x04      */
  volatile uint32_t OSPEEDR_R;  /*!< GPIO port output speed register,       Address offset: 0x08      */
  volatile uint32_t PUPDR_R;    /*!< GPIO port pull-up/pull-down register,  Address offset: 0x0C      */
  volatile uint32_t IDR_R;      /*!< GPIO port input data register,         Address offset: 0x10      */
  volatile uint32_t ODR_R;      /*!< GPIO port output data register,        Address offset: 0x14      */
  volatile uint16_t BSRRL_R;    /*!< GPIO port bit set/reset low register,  Address offset: 0x18      */
  volatile uint16_t BSRRH_R;    /*!< GPIO port bit set/reset high register, Address offset: 0x1A      */
  volatile uint32_t LCKR_R;     /*!< GPIO port configuration lock register, Address offset: 0x1C      */
  volatile uint32_t AFR_R[2];   /*!< GPIO alternate function registers,     Address offset: 0x20-0x24 */
} GPIOTypeDef;


// GPIO Configuration Mode: Moder Register
typedef enum
{ 
  GPIOModeIN   = 0x00, /*!< GPIO Input Mode */
  GPIOModeOUT  = 0x01, /*!< GPIO Output Mode */
  GPIOModeAF   = 0x02, /*!< GPIO Alternate function Mode */
  GPIOModeAN   = 0x03  /*!< GPIO Analog Mode */
}GPIO_MODERTypeDef;

//GPIO Output Type: OTYPER Register
typedef enum
{ 
  GPIOOTypePP = 0x00, //Push pull
  GPIOOTypeOD = 0x01  // Open Drain 
}GPIO_OTYPERTypeDef;

//GPIO Maximum Frequency: OSPEEDR Register
typedef enum
{ 
  GPIOLowSpeed     = 0x00, /*!< Low speed : 2MHZ   */
  GPIOMediumSpeed  = 0x01, /*!< Medium speed : 25MHz*/
  GPIOFastSpeed    = 0x02, /*!< Fast speed: 50 MHz   */
  GPIOHighSpeed    = 0x03  /*!< High speed: 100 MHz   */
}GPIO_OSPEEDRTypeDef;

//GPIO PullUp, PullDown configurations: PUPDR Register
typedef enum
{ 
  GPIOPuPdNOPULL = 0x00,
  GPIOPuPdUP     = 0x01,
  GPIOPuPdDOWN   = 0x02
}GPIO_PUPDRTypeDef;


//GPPIO init structure definition:
typedef struct
{
  uint32_t GPIO_Pin;              /*!< Specifies the GPIO pins to be configured. */
  GPIO_MODERTypeDef GPIO_Mode;     /*!< Specifies the operating mode for the selected pins.*/
  GPIO_OSPEEDRTypeDef GPIO_Speed;   /*!< Specifies the speed for the selected pins.*/
  GPIO_OTYPERTypeDef GPIO_OType;   /*!< Specifies the operating output type for the selected pins.*/
  GPIO_PUPDRTypeDef GPIO_PuPd;     /*!< Specifies the operating Pull-up/Pull down for the selected pins.*/
}GPIOInitTypeDef;


/**** Gpio Configuration Flags *****/

//Pin Defines
#define GPIOPin0                 ((uint32_t)0x0001)  /* Pin 0 selected */
#define GPIOPin1                 ((uint32_t)0x0002)  /* Pin 1 selected */
#define GPIOPin2                 ((uint32_t)0x0004)  /* Pin 2 selected */
#define GPIOPin3                 ((uint32_t)0x0008)  /* Pin 3 selected */
#define GPIOPin4                 ((uint32_t)0x0010)  /* Pin 4 selected */
#define GPIOPin5                 ((uint32_t)0x0020)  /* Pin 5 selected */
#define GPIOPin6                 ((uint32_t)0x0040)  /* Pin 6 selected */
#define GPIOPin7                 ((uint32_t)0x0080)  /* Pin 7 selected */
#define GPIOPin8                 ((uint32_t)0x0100)  /* Pin 8 selected */
#define GPIOPin9                 ((uint32_t)0x0200)  /* Pin 9 selected */
#define GPIOPin10                ((uint32_t)0x0400)  /* Pin 10 selected */
#define GPIOPin11                ((uint32_t)0x0800)  /* Pin 11 selected */
#define GPIOPin12                ((uint32_t)0x1000)  /* Pin 12 selected */
#define GPIOPin13                ((uint32_t)0x2000)  /* Pin 13 selected */
#define GPIOPin14                ((uint32_t)0x4000)  /* Pin 14 selected */
#define GPIOPin15                ((uint32_t)0x8000)  /* Pin 15 selected */
#define GPIOPinAll               ((uint32_t)0xFFFF)  /* All pins selected */

//Pin Sources
#define GPIOPinSource0            ((uint8_t)0x00)
#define GPIOPinSource1            ((uint8_t)0x01)
#define GPIOPinSource2            ((uint8_t)0x02)
#define GPIOPinSource3            ((uint8_t)0x03)
#define GPIOPinSource4            ((uint8_t)0x04)
#define GPIOPinSource5            ((uint8_t)0x05)
#define GPIOPinSource6            ((uint8_t)0x06)
#define GPIOPinSource7            ((uint8_t)0x07)
#define GPIOPinSource8            ((uint8_t)0x08)
#define GPIOPinSource9            ((uint8_t)0x09)
#define GPIOPinSource10           ((uint8_t)0x0A)
#define GPIOPinSource11           ((uint8_t)0x0B)
#define GPIOPinSource12           ((uint8_t)0x0C)
#define GPIOPinSource13           ((uint8_t)0x0D)
#define GPIOPinSource14           ((uint8_t)0x0E)
#define GPIOPinSource15           ((uint8_t)0x0F)

// Alternate function selections

//AF 0
#define GPIO_AF_RTC_50Hz      ((uint8_t)0x00)  /* RTC_50Hz Alternate Function mapping */
#define GPIO_AF_MCO           ((uint8_t)0x00)  /* MCO (MCO1 and MCO2) Alternate Function mapping */
#define GPIO_AF_TAMPER        ((uint8_t)0x00)  /* TAMPER (TAMPER_1 and TAMPER_2) Alternate Function mapping */
#define GPIO_AF_SWJ           ((uint8_t)0x00)  /* SWJ (SWD and JTAG) Alternate Function mapping */
#define GPIO_AF_TRACE         ((uint8_t)0x00)  /* TRACE Alternate Function mapping */
#define GPIO_AF0_TIM2         ((uint8_t)0x00)  /* TIM2 Alternate Function mapping */

//AF 1
#define GPIO_AF_TIM1          ((uint8_t)0x01)  /* TIM1 Alternate Function mapping */
#define GPIO_AF_TIM2          ((uint8_t)0x01)  /* TIM2 Alternate Function mapping */

//AF 2
#define GPIO_AF_TIM3          ((uint8_t)0x02)  /* TIM3 Alternate Function mapping */
#define GPIO_AF_TIM4          ((uint8_t)0x02)  /* TIM4 Alternate Function mapping */
#define GPIO_AF_TIM5          ((uint8_t)0x02)  /* TIM5 Alternate Function mapping */

//AF 3
#define GPIO_AF_TIM8          ((uint8_t)0x03)  /* TIM8 Alternate Function mapping */
#define GPIO_AF_TIM9          ((uint8_t)0x03)  /* TIM9 Alternate Function mapping */
#define GPIO_AF_TIM10         ((uint8_t)0x03)  /* TIM10 Alternate Function mapping */
#define GPIO_AF_TIM11         ((uint8_t)0x03)  /* TIM11 Alternate Function mapping */
#define GPIO_AF3_CEC          ((uint8_t)0x03)  /* CEC Alternate Function mapping */

//AF 4
#define GPIO_AF_I2C1          ((uint8_t)0x04)  /* I2C1 Alternate Function mapping */
#define GPIO_AF_I2C2          ((uint8_t)0x04)  /* I2C2 Alternate Function mapping */
#define GPIO_AF_I2C3          ((uint8_t)0x04)  /* I2C3 Alternate Function mapping */
#define GPIO_AF4_CEC          ((uint8_t)0x04)  /* CEC Alternate Function mapping */
#define GPIO_AF_FMPI2C        ((uint8_t)0x04)  /* FMPI2C Alternate Function mapping */

//AF 5
#define GPIO_AF_SPI1          ((uint8_t)0x05)  /* SPI1/I2S1 Alternate Function mapping */
#define GPIO_AF_SPI2          ((uint8_t)0x05)  /* SPI2/I2S2 Alternate Function mapping */
#define GPIO_AF5_SPI3         ((uint8_t)0x05)  /* SPI3/I2S3 Alternate Function mapping (Only for STM32F411xE and STM32F413_423xx Devices) */
#define GPIO_AF_SPI4          ((uint8_t)0x05)  /* SPI4/I2S4 Alternate Function mapping */
#define GPIO_AF_SPI5          ((uint8_t)0x05)  /* SPI5 Alternate Function mapping      */
#define GPIO_AF_SPI6          ((uint8_t)0x05)  /* SPI6 Alternate Function mapping      */

//AF 6
#define GPIO_AF_SPI3          ((uint8_t)0x06)  /* SPI3/I2S3 Alternate Function mapping */
#define GPIO_AF6_SPI1         ((uint8_t)0x06)  /* SPI1 Alternate Function mapping (Only for STM32F410xx Devices) */
#define GPIO_AF6_SPI2         ((uint8_t)0x06)  /* SPI2 Alternate Function mapping (Only for STM32F410xx/STM32F411xE Devices) */
#define GPIO_AF6_SPI4         ((uint8_t)0x06)  /* SPI4 Alternate Function mapping (Only for STM32F411xE Devices) */
#define GPIO_AF6_SPI5         ((uint8_t)0x06)  /* SPI5 Alternate Function mapping (Only for STM32F410xx/STM32F411xE Devices) */
#define GPIO_AF_SAI1          ((uint8_t)0x06)  /* SAI1 Alternate Function mapping      */
#define GPIO_AF_I2S2ext       ((uint8_t)0x06)  /* I2S2ext_SD Alternate Function mapping (only for STM32F412xG and STM32F413_423xx Devices) */

//AF 7
#define GPIO_AF_USART1         ((uint8_t)0x07)  /* USART1 Alternate Function mapping  */
#define GPIO_AF_USART2         ((uint8_t)0x07)  /* USART2 Alternate Function mapping  */
#define GPIO_AF_USART3         ((uint8_t)0x07)  /* USART3 Alternate Function mapping  */
#define GPIO_AF7_SPI3          ((uint8_t)0x07)  /* SPI3/I2S3ext Alternate Function mapping */

//AF 8
#define GPIO_AF_UART4         ((uint8_t)0x08)  /* UART4 Alternate Function mapping  */
#define GPIO_AF_UART5         ((uint8_t)0x08)  /* UART5 Alternate Function mapping  */
#define GPIO_AF_USART6        ((uint8_t)0x08)  /* USART6 Alternate Function mapping */
#define GPIO_AF_UART7         ((uint8_t)0x08)  /* UART7 Alternate Function mapping  */
#define GPIO_AF_UART8         ((uint8_t)0x08)  /* UART8 Alternate Function mapping  */
#define GPIO_AF8_SAI2          ((uint8_t)0x08)  /* SAI2 Alternate Function mapping */
#define GPIO_AF_SPDIF         ((uint8_t)0x08)   /* SPDIF Alternate Function mapping */

//AF 9
#define GPIO_AF_CAN1          ((uint8_t)0x09)  /* CAN1 Alternate Function mapping  */
#define GPIO_AF_CAN2          ((uint8_t)0x09)  /* CAN2 Alternate Function mapping  */
#define GPIO_AF_TIM12         ((uint8_t)0x09)  /* TIM12 Alternate Function mapping */
#define GPIO_AF_TIM13         ((uint8_t)0x09)  /* TIM13 Alternate Function mapping */
#define GPIO_AF_TIM14         ((uint8_t)0x09)  /* TIM14 Alternate Function mapping */
#define GPIO_AF9_I2C2         ((uint8_t)0x09)  /* I2C2 Alternate Function mapping (Only for STM32F401xx/STM32F410xx/STM32F411xE/STM32F412xG/STM32F413_423xx Devices) */
#define GPIO_AF9_I2C3         ((uint8_t)0x09)  /* I2C3 Alternate Function mapping (Only for STM32F401xx/STM32F411xE/STM32F412xG and STM32F413_423xx Devices) */
#define GPIO_AF9_SAI2         ((uint8_t)0x09)  /* SAI2 Alternate Function mapping */
#define GPIO_AF9_LTDC         ((uint8_t)0x09)  /* LTDC Alternate Function mapping */
#define GPIO_AF9_QUADSPI      ((uint8_t)0x09)  /* QuadSPI Alternate Function mapping */

//AF 10
#define GPIO_AF_OTG_FS         ((uint8_t)0xA)  /* OTG_FS Alternate Function mapping */
#define GPIO_AF_OTG_HS         ((uint8_t)0xA)  /* OTG_HS Alternate Function mapping */
#define GPIO_AF10_SAI2         ((uint8_t)0x0A)  /* SAI2 Alternate Function mapping */
#define GPIO_AF10_QUADSPI      ((uint8_t)0x0A)  /* QuadSPI Alternate Function mapping */

//AF 11
#define GPIO_AF_ETH             ((uint8_t)0x0B)  /* ETHERNET Alternate Function mapping */

//AF 12
#define GPIO_AF_FMC              ((uint8_t)0xC)  /* FMC Alternate Function mapping                      */
#define GPIO_AF_OTG_HS_FS        ((uint8_t)0xC)  /* OTG HS configured in FS, Alternate Function mapping */
#define GPIO_AF_SDIO             ((uint8_t)0xC)  /* SDIO Alternate Function mapping   */

//AF 13
#define GPIO_AF_DCMI          ((uint8_t)0x0D)  /* DCMI Alternate Function mapping */

//AF 14
#define GPIO_AF_LTDC          ((uint8_t)0x0E)  /* LCD-TFT Alternate Function mapping */

//AF 15
#define GPIO_AF_EVENTOUT      ((uint8_t)0x0F)  /* EVENTOUT Alternate Function mapping */





/**** Gpio Function Definitions *****/
void GPIOInit(GPIOTypeDef * gpiox, GPIOInitTypeDef * gpioinit);

void GPIOPinAFConfig( GPIOTypeDef* GPIOx, uint16_t GPIO_PinSource, uint8_t GPIO_AF);

void GPIOSetBits(GPIOTypeDef * gpiox, uint16_t gpiopin);

void GPIOClearBits(GPIOTypeDef * gpiox, uint16_t gpiopin);

void GPIOWrite(GPIOTypeDef * gpiox, uint16_t portval);

void GPIOToggleBits(GPIOTypeDef * gpiox, uint16_t gpiopin);

uint8_t GPIOReadInputDataBit( GPIOTypeDef * gpiox, uint16_t gpiopin);

uint16_t GPIOReadInputData( GPIOTypeDef * gpiox);

#ifdef __cplusplus
}
#endif


#endif  //__STM32F446ZE_GPIO_H_