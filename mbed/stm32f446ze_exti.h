
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F446ZE_EXTI_H
#define __STM32F446ZE_EXTI_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_mort2.h"


/* types ------------------------------------------------------------*/

typedef enum
{
  EXTIModeInterrupt = 0x00,
  EXTIModeEvent = 0x04
}EXTIModeTypeDef;

typedef enum
{
  EXTITriggerRising = 0x08,
  EXTITriggerFalling = 0x0C,  
  EXTITriggerRisingFalling = 0x10
}EXTITriggerTypeDef;


typedef struct
{
  uint32_t EXTILine;               /*!< Specifies the EXTI_MORT lines to be enabled or disabled.
                                         This parameter can be any combination value of @ref EXTI_Lines */
   
  EXTIModeTypeDef EXTIMode;       /*!< Specifies the mode for the EXTI_MORT lines.
                                         This parameter can be a value of @ref EXTIMode_TypeDef_mort */

  EXTITriggerTypeDef EXTITrigger; /*!< Specifies the trigger signal active edge for the EXTI_MORT lines.
                                         This parameter can be a value of @ref EXTITrigger_TypeDef_mort */

  FunctionalState_MORT EXTILineCmd;     /*!< Specifies the new state of the selected EXTI_MORT lines.
                                         This parameter can be set either to ENABLE_MORT or DISABLE_MORT */ 
}EXTIInitTypeDef;

/* Exported constants --------------------------------------------------------*/


#define EXTI_Line0_MORT       ((uint32_t)0x00001)     /*!< External interrupt line 0 */
#define EXTI_Line1_MORT       ((uint32_t)0x00002)     /*!< External interrupt line 1 */
#define EXTI_Line2_MORT       ((uint32_t)0x00004)     /*!< External interrupt line 2 */
#define EXTI_Line3_MORT       ((uint32_t)0x00008)     /*!< External interrupt line 3 */
#define EXTI_Line4_MORT       ((uint32_t)0x00010)     /*!< External interrupt line 4 */
#define EXTI_Line5_MORT       ((uint32_t)0x00020)     /*!< External interrupt line 5 */
#define EXTI_Line6_MORT       ((uint32_t)0x00040)     /*!< External interrupt line 6 */
#define EXTI_Line7_MORT       ((uint32_t)0x00080)     /*!< External interrupt line 7 */
#define EXTI_Line8_MORT       ((uint32_t)0x00100)     /*!< External interrupt line 8 */
#define EXTI_Line9_MORT       ((uint32_t)0x00200)     /*!< External interrupt line 9 */
#define EXTI_Line10_MORT      ((uint32_t)0x00400)     /*!< External interrupt line 10 */
#define EXTI_Line11_MORT      ((uint32_t)0x00800)     /*!< External interrupt line 11 */
#define EXTI_Line12_MORT      ((uint32_t)0x01000)     /*!< External interrupt line 12 */
#define EXTI_Line13_MORT      ((uint32_t)0x02000)     /*!< External interrupt line 13 */
#define EXTI_Line14_MORT      ((uint32_t)0x04000)     /*!< External interrupt line 14 */
#define EXTI_Line15_MORT      ((uint32_t)0x08000)     /*!< External interrupt line 15 */
#define EXTI_Line16_MORT      ((uint32_t)0x10000)     /*!< External interrupt line 16 Connected to the PVD Output */
#define EXTI_Line17_MORT      ((uint32_t)0x20000)     /*!< External interrupt line 17 Connected to the RTC Alarm event */
#define EXTI_Line18_MORT      ((uint32_t)0x40000)     /*!< External interrupt line 18 Connected to the USB OTG FS Wakeup from suspend event */                                    
#define EXTI_Line19_MORT      ((uint32_t)0x80000)     /*!< External interrupt line 19 Connected to the Ethernet Wakeup event */
#define EXTI_Line20_MORT      ((uint32_t)0x00100000)  /*!< External interrupt line 20 Connected to the USB OTG HS (configured in FS) Wakeup event  */
#define EXTI_Line21_MORT      ((uint32_t)0x00200000)  /*!< External interrupt line 21 Connected to the RTC Tamper and Time Stamp events */                                               
#define EXTI_Line22_MORT      ((uint32_t)0x00400000)  /*!< External interrupt line 22 Connected to the RTC Wakeup event */
#define EXTI_Line23_MORT      ((uint32_t)0x00800000)  /*!< External interrupt line 23 Connected to the LPTIM Wakeup event */

/* Function definitions --------------------------------------------------------*/
void EXTIInit(EXTIInitTypeDef* EXTI_InitStruct);
ITStatus_MORT EXTI_GetITStatus_mort(uint32_t EXTI_Line);
void EXTI_ClearITPendingBit_mort(uint32_t EXTI_Line);


#ifdef __cplusplus
}
#endif

#endif /* __STM32F446ze_EXTI_H */