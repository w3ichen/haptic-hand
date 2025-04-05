#ifndef __STM32F446ZE_SYSCFG_H
#define __STM32F446ZE_SYSCFG_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_mort2.h"


/*SYSCFG_EXTI_PORT_SOURCES*/
#define EXTI_PORT_SOURCE_GPIOA          ((uint8_t)0x00)
#define EXTI_PORT_SOURCE_GPIOB          ((uint8_t)0x01)
#define EXTI_PORT_SOURCE_GPIOC          ((uint8_t)0x02)
#define EXTI_PORT_SOURCE_GPIOD          ((uint8_t)0x03)
#define EXTI_PORT_SOURCE_GPIOE          ((uint8_t)0x04)
#define EXTI_PORT_SOURCE_GPIOF          ((uint8_t)0x05)
#define EXTI_PORT_SOURCE_GPIOG          ((uint8_t)0x06)
#define EXTI_PORT_SOURCE_GPIOH          ((uint8_t)0x07)
#define EXTI_PORT_SOURCE_GPIOI          ((uint8_t)0x08)
#define EXTI_PORT_SOURCE_GPIOJ          ((uint8_t)0x09)
#define EXTI_PORT_SOURCE_GPIOK          ((uint8_t)0x0A)

/*SYSCFG_EXTI_PIN_SOURCES*/
#define EXTI_PIN_SOURCE_0               ((uint8_t)0x00)
#define EXTI_PIN_SOURCE_1               ((uint8_t)0x01)
#define EXTI_PIN_SOURCE_2               ((uint8_t)0x02)
#define EXTI_PIN_SOURCE_3               ((uint8_t)0x03)
#define EXTI_PIN_SOURCE_4               ((uint8_t)0x04)
#define EXTI_PIN_SOURCE_5               ((uint8_t)0x05)
#define EXTI_PIN_SOURCE_6               ((uint8_t)0x06)
#define EXTI_PIN_SOURCE_7               ((uint8_t)0x07)
#define EXTI_PIN_SOURCE_8               ((uint8_t)0x08)
#define EXTI_PIN_SOURCE_9               ((uint8_t)0x09)
#define EXTI_PIN_SOURCE_10              ((uint8_t)0x0A)
#define EXTI_PIN_SOURCE_11              ((uint8_t)0x0B)
#define EXTI_PIN_SOURCE_12              ((uint8_t)0x0C)
#define EXTI_PIN_SOURCE_13              ((uint8_t)0x0D)
#define EXTI_PIN_SOURCE_14              ((uint8_t)0x0E)
#define EXTI_PIN_SOURCE_15              ((uint8_t)0x0F)


/*System configuration controller*/
typedef struct
{
  volatile uint32_t MEMRMP_R;       /*!< SYSCFG_MORT memory remap register,                      Address offset: 0x00      */
  volatile uint32_t PMC_R;          /*!< SYSCFG_MORT peripheral mode configuration register,     Address offset: 0x04      */
  volatile uint32_t EXTICR_R[4];    /*!< SYSCFG_MORT external interrupt configuration registers, Address offset: 0x08-0x14 */
  uint32_t      RESERVED[2];  /*!< Reserved, 0x18-0x1C                                                          */ 
  volatile uint32_t CMPCR_R;        /*!< SYSCFG_MORT Compensation cell control register,         Address offset: 0x20      */
} SYSCFGTypeDef;

#define SYSCFG_REGISTER_BLOCK             ((SYSCFGTypeDef *) SYSCFG_BASE_MORT)

/*Function definitions*/
void SYSCFGEXTILineConfig(uint8_t EXTI_PortSourceGPIOx, uint8_t EXTI_PinSourcex);


#ifdef __cplusplus
}
#endif


#endif  //__STM32F446ZE_SYSCFG_H_