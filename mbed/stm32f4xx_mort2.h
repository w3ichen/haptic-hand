/**
  ******************************************************************************
  * @file    stm32f4xx.h
  * @author  MCD Application Team
  * @version V1.8.0
  * @date    09-November-2016
  * @brief   CMSIS Cortex-M4 Device Peripheral Access Layer Header File. 
  *          This file contains all the peripheral register's definitions, bits 
  *          definitions and memory mapping for STM32F4xx devices.            
  *            
  *          The file is the unique include file that the application programmer
  *          is using in the C source code, usually in main.c. This file contains:
  *           - Configuration section that allows to select:
  *              - The device used in the target application
  *              - To use or not the peripherals drivers in application code(i.e. 
  *                code will be based on direct access to peripherals registers 
  *                rather than drivers API), this option is controlled by 
  *                "#define USE_STDPERIPH_DRIVER"
  *              - To change few application-specific parameters such as the HSE 
  *                crystal frequency
  *           - Data structures and the address mapping for all peripherals
  *           - Peripherals registers declarations and bits definition
  *           - Macros to access peripherals registers hardware
  *  
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************  
  */ 

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup stm32f4xx
  * @{
  */
    
#ifndef __STM32F4xx_H_MORT2_
#define __STM32F4xx_H_MORT2_

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */
  
/** @addtogroup Library_configuration_section
  * @{
  */
  
/* Uncomment the line below according to the target STM32 device used in your
   application 
  */

#if !defined(STM32F40_41xxx) && !defined(STM32F427_437xx) && !defined(STM32F429_439xx) && !defined(STM32F401xx) && !defined(STM32F410xx) && \
    !defined(STM32F411xE) && !defined(STM32F412xG) && !defined(STM32F413_423xx) && !defined(STM32F446xx_MORT) && !defined(STM32F469_479xx)
  /* #define STM32F40_41xxx */   /*!< STM32F405RG, STM32F405VG, STM32F405ZG, STM32F415RG, STM32F415VG, STM32F415ZG,
                                      STM32F407VG, STM32F407VE, STM32F407ZG, STM32F407ZE, STM32F407IG, STM32F407IE, 
                                      STM32F417VG, STM32F417VE, STM32F417ZG, STM32F417ZE, STM32F417IG and STM32F417IE Devices */

  /* #define STM32F427_437xx */  /*!< STM32F427VG, STM32F427VI, STM32F427ZG, STM32F427ZI, STM32F427IG, STM32F427II,
                                      STM32F437VG, STM32F437VI, STM32F437ZG, STM32F437ZI, STM32F437IG, STM32F437II Devices */

  /* #define STM32F429_439xx */  /*!< STM32F429VG, STM32F429VI, STM32F429ZG, STM32F429ZI, STM32F429BG, STM32F429BI,
                                      STM32F429NG, STM32F439NI, STM32F429IG, STM32F429II, STM32F439VG, STM32F439VI,
                                      STM32F439ZG, STM32F439ZI, STM32F439BG, STM32F439BI, STM32F439NG, STM32F439NI,
                                      STM32F439IG and STM32F439II Devices */

  /* #define STM32F401xx */      /*!< STM32F401CB, STM32F401CC,  STM32F401RB, STM32F401RC, STM32F401VB, STM32F401VC,
                                      STM32F401CD, STM32F401RD, STM32F401VD, STM32F401CExx, STM32F401RE and STM32F401VE Devices */

  /* #define STM32F410xx */      /*!< STM32F410Tx, STM32F410Cx and STM32F410Rx */

  /* #define STM32F411xE */      /*!< STM32F411CC, STM32F411RC, STM32F411VC, STM32F411CE, STM32F411RE and STM32F411VE Devices */

  /* #define STM32F412xG */      /*!< STM32F412CEU, STM32F412CGU, STM32F412ZET, STM32F412ZGT, STM32F412ZEJ, STM32F412ZGJ,
                                      STM32F412VET, STM32F412VGT, STM32F412VEH, STM32F412VGH, STM32F412RET, STM32F412RGT,
                                      STM32F412REY and STM32F412RGY Devices */
                                      
  /* #define STM32F413_423xx */  /*!< STM32F413CGU, STM32F413CHU, STM32F413MGY, STM32F413MHY, STM32F413RGT, STM32F413VGT,
                                      STM32F413ZGT, STM32F413RHT, STM32F413VHT, STM32F413ZHT, STM32F413VGH, STM32F413ZGJ,
                                      STM32F413VHH, STM32F413ZHJ, STM32F423CHU, STM32F423RHT, STM32F423VHT, STM32F423ZHT,
                                      STM32F423VHH and STM32F423ZHJ devices */

  #define STM32F446xx_MORT      /*!< STM32F446MC, STM32F446ME, STM32F446RC, STM32F446RE, STM32F446VC, STM32F446VE, STM32F446ZC 
                                      and STM32F446ZE Devices */

  /* #define STM32F469_479xx */  /*!< STM32F479AI, STM32F479II, STM32F479BI, STM32F479NI, STM32F479AG, STM32F479IG, STM32F479BG,
                                      STM32F479NG, STM32F479AE, STM32F479IE, STM32F479BE, STM32F479NE Devices */

#endif /* STM32F40_41xxx && STM32F427_437xx && STM32F429_439xx && STM32F401xx && STM32F410xx && STM32F411xE && STM32F412xG && STM32F413_423xx && STM32F446xx_MORT && STM32F469_479xx */

/* Old STM32F40XX definition, maintained for legacy purpose */
#ifdef STM32F40XX
  #define STM32F40_41xxx
#endif /* STM32F40XX */

/* Old STM32F427X definition, maintained for legacy purpose */
#ifdef STM32F427X
  #define STM32F427_437xx
#endif /* STM32F427X */

/*  Tip: To avoid modifying this file each time you need to switch between these
        devices, you can define the device in your toolchain compiler preprocessor.
  */

#if !defined(STM32F40_41xxx) && !defined(STM32F427_437xx) && !defined(STM32F429_439xx) && !defined(STM32F401xx) && !defined(STM32F410xx) && \
    !defined(STM32F411xE) && !defined(STM32F412xG) && !defined(STM32F413_423xx) && !defined(STM32F446xx_MORT) && !defined(STM32F469_479xx)
 #error "Please select first the target STM32F4xx device used in your application (in stm32f4xx.h file)"
#endif /* STM32F40_41xxx && STM32F427_437xx && STM32F429_439xx && STM32F401xx && STM32F410xx && STM32F411xE && STM32F412xG && STM32F413_23xx && STM32F446xx_MORT && STM32F469_479xx */

#if !defined  (USE_STDPERIPH_DRIVER)
/**
 * @brief Comment the line below if you will not use the peripherals drivers.
   In this case, these drivers will not be included and the application code will 
   be based on direct access to peripherals registers 
   */
  /*#define USE_STDPERIPH_DRIVER */
#endif /* USE_STDPERIPH_DRIVER */

/**
 * @brief In the following line adjust the value of External High Speed oscillator (HSE)
   used in your application 
   
   Tip: To avoid modifying this file each time you need to use different HSE, you
        can define the HSE value in your toolchain compiler preprocessor.
  */           
#if defined(STM32F40_41xxx) || defined(STM32F427_437xx)  || defined(STM32F429_439xx) || defined(STM32F401xx) || \
    defined(STM32F410xx) || defined(STM32F411xE) || defined(STM32F469_479xx)
 #if !defined  (HSE_VALUE) 
  #define HSE_VALUE    ((uint32_t)25000000) /*!< Value of the External oscillator in Hz */
 #endif /* HSE_VALUE */
#elif defined (STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F446xx_MORT)
 #if !defined  (HSE_VALUE) 
  #define HSE_VALUE    ((uint32_t)8000000) /*!< Value of the External oscillator in Hz */
 #endif /* HSE_VALUE */
#endif /* STM32F40_41xxx || STM32F427_437xx || STM32F429_439xx || STM32F401xx || STM32F411xE || STM32F469_479xx */
/**
 * @brief In the following line adjust the External High Speed oscillator (HSE) Startup 
   Timeout value 
   */
#if !defined  (HSE_STARTUP_TIMEOUT) 
  #define HSE_STARTUP_TIMEOUT    ((uint16_t)0x05000)   /*!< Time out for HSE start up */
#endif /* HSE_STARTUP_TIMEOUT */   

#if !defined  (HSI_VALUE)   
  #define HSI_VALUE    ((uint32_t)16000000) /*!< Value of the Internal oscillator in Hz*/
#endif /* HSI_VALUE */   

/**
 * @brief STM32F4XX Standard Peripherals Library version number V1.8.0
   */
#define __STM32F4XX_STDPERIPH_VERSION_MAIN   (0x01) /*!< [31:24] main version */
#define __STM32F4XX_STDPERIPH_VERSION_SUB1   (0x08) /*!< [23:16] sub1 version */
#define __STM32F4XX_STDPERIPH_VERSION_SUB2   (0x00) /*!< [15:8]  sub2 version */
#define __STM32F4XX_STDPERIPH_VERSION_RC     (0x00) /*!< [7:0]  release candidate */ 
#define __STM32F4XX_STDPERIPH_VERSION        ((__STM32F4XX_STDPERIPH_VERSION_MAIN << 24)\
                                             |(__STM32F4XX_STDPERIPH_VERSION_SUB1 << 16)\
                                             |(__STM32F4XX_STDPERIPH_VERSION_SUB2 << 8)\
                                             |(__STM32F4XX_STDPERIPH_VERSION_RC))

/**
  * @}
  */

/** @addtogroup Configuration_section_for_CMSIS
  * @{
  */

/**
 * @brief Configuration of the Cortex-M4 Processor and Core Peripherals 
 */
#define __CM4_REV_MORT                 0x0001  /*!< Core revision r0p1                            */
#define __MPU_PRESENT_MORT             1       /*!< STM32F4XX provides an MPU                     */
#define __NVIC_PRIO_BITS_MORT          4       /*!< STM32F4XX uses 4 Bits for the Priority Levels */
#define __Vendor_SysTickConfig_MORT    0       /*!< Set to 1 if different SysTick Config is used  */
#define __FPU_PRESENT_MORT             1       /*!< FPU present                                   */

/**
 * @brief STM32F4XX Interrupt Number Definition, according to the selected device 
 *        in @ref Library_configuration_section 
 */
typedef enum IRQn_MORT
{
/******  Cortex-M4 Processor Exceptions Numbers ****************************************************************/
  NonMaskableInt_IRQn_MORT         = -14,    /*!< 2 Non Maskable Interrupt                                          */
  MemoryManagement_IRQn_MORT       = -12,    /*!< 4 Cortex-M4 Memory Management Interrupt                           */
  BusFault_IRQn_MORT               = -11,    /*!< 5 Cortex-M4 Bus Fault Interrupt                                   */
  UsageFault_IRQn_MORT             = -10,    /*!< 6 Cortex-M4 Usage Fault Interrupt                                 */
  SVCall_IRQn_MORT                 = -5,     /*!< 11 Cortex-M4 SV Call Interrupt                                    */
  DebugMonitor_IRQn_MORT           = -4,     /*!< 12 Cortex-M4 Debug Monitor Interrupt                              */
  PendSV_IRQn_MORT                 = -2,     /*!< 14 Cortex-M4 Pend SV Interrupt                                    */
  SysTick_IRQn_MORT                = -1,     /*!< 15 Cortex-M4 System Tick Interrupt                                */
/******  STM32 specific Interrupt Numbers **********************************************************************/
  WWDG_IRQn_MORT                   = 0,      /*!< Window WatchDog Interrupt                                         */
  PVD_IRQn_MORT                    = 1,      /*!< PVD through EXTI_MORT Line detection Interrupt                         */
  TAMP_STAMP_IRQn_MORT             = 2,      /*!< Tamper and TimeStamp interrupts through the EXTI_MORT line             */
  RTC_WKUP_IRQn_MORT               = 3,      /*!< RTC_MORT Wakeup interrupt through the EXTI_MORT line                        */
  FLASH_IRQn_MORT                  = 4,      /*!< FLASH_MORT global Interrupt                                            */
  RCC_IRQn_MORT                    = 5,      /*!< RCC_MORT global Interrupt                                              */
  EXTI0_IRQn_MORT                  = 6,      /*!< EXTI_MORT Line0 Interrupt                                              */
  EXTI1_IRQn_MORT                  = 7,      /*!< EXTI_MORT Line1 Interrupt                                              */
  EXTI2_IRQn_MORT                  = 8,      /*!< EXTI_MORT Line2 Interrupt                                              */
  EXTI3_IRQn_MORT                  = 9,      /*!< EXTI_MORT Line3 Interrupt                                              */
  EXTI4_IRQn_MORT                  = 10,     /*!< EXTI_MORT Line4 Interrupt                                              */
  DMA1_Stream0_IRQn_MORT           = 11,     /*!< DMA1_MORT Stream 0 global Interrupt                                    */
  DMA1_Stream1_IRQn_MORT           = 12,     /*!< DMA1_MORT Stream 1 global Interrupt                                    */
  DMA1_Stream2_IRQn_MORT           = 13,     /*!< DMA1_MORT Stream 2 global Interrupt                                    */
  DMA1_Stream3_IRQn_MORT           = 14,     /*!< DMA1_MORT Stream 3 global Interrupt                                    */
  DMA1_Stream4_IRQn_MORT           = 15,     /*!< DMA1_MORT Stream 4 global Interrupt                                    */
  DMA1_Stream5_IRQn_MORT           = 16,     /*!< DMA1_MORT Stream 5 global Interrupt                                    */
  DMA1_Stream6_IRQn_MORT           = 17,     /*!< DMA1_MORT Stream 6 global Interrupt                                    */
  ADC_IRQn_MORT                    = 18,     /*!< ADC1_MORT, ADC2_MORT and ADC3_MORT global Interrupts                             */

#if defined(STM32F40_41xxx)
                                          */
#endif /* STM32F40_41xxx */

#if defined(STM32F427_437xx)
                                            */
#endif /* STM32F427_437xx */
    
#if defined(STM32F429_439xx)
                                         */
#endif /* STM32F429_439xx */

#if defined(STM32F410xx)
                                                  */
#endif /* STM32F410xx */
   
#if defined(STM32F401xx) || defined(STM32F411xE)
                                               */
#if defined(STM32F401xx)
                                             */
#endif /* STM32F411xE */
#if defined(STM32F411xE)
                                              */
#endif /* STM32F411xE */
#endif /* STM32F401xx || STM32F411xE */

#if defined(STM32F469_479xx)
                                               */
#endif /* STM32F469_479xx */

#if defined(STM32F446xx_MORT)
  CAN1_TX_IRQn_MORT                = 19,     /*!< CAN1_MORT TX Interrupt                                                 */
  CAN1_RX0_IRQn_MORT               = 20,     /*!< CAN1_MORT RX0 Interrupt                                                */
  CAN1_RX1_IRQn_MORT               = 21,     /*!< CAN1_MORT RX1 Interrupt                                                */
  CAN1_SCE_IRQn_MORT               = 22,     /*!< CAN1_MORT SCE Interrupt                                                */
  EXTI9_5_IRQn_MORT                = 23,     /*!< External Line[9:5] Interrupts                                     */
  TIM1_BRK_TIM9_IRQn_MORT          = 24,     /*!< TIM1_MORT Break interrupt and TIM9_MORT global interrupt                    */
  TIM1_UP_TIM10_IRQn_MORT          = 25,     /*!< TIM1_MORT Update Interrupt and TIM10_MORT global interrupt                  */
  TIM1_TRG_COM_TIM11_IRQn_MORT     = 26,     /*!< TIM1_MORT Trigger and Commutation Interrupt and TIM11_MORT global interrupt */
  TIM1_CC_IRQn_MORT                = 27,     /*!< TIM1_MORT Capture Compare Interrupt                                    */
  TIM2_IRQn_MORT                   = 28,     /*!< TIM2_MORT global Interrupt                                             */
  TIM3_IRQn_MORT                   = 29,     /*!< TIM3_MORT global Interrupt                                             */
  TIM4_IRQn_MORT                   = 30,     /*!< TIM4_MORT global Interrupt                                             */
  I2C1_EV_IRQn_MORT                = 31,     /*!< I2C1_MORT Event Interrupt                                              */
  I2C1_ER_IRQn_MORT                = 32,     /*!< I2C1_MORT Error Interrupt                                              */
  I2C2_EV_IRQn_MORT                = 33,     /*!< I2C2_MORT Event Interrupt                                              */
  I2C2_ER_IRQn_MORT                = 34,     /*!< I2C2_MORT Error Interrupt                                              */  
  SPI1_IRQn_MORT                   = 35,     /*!< SPI1_MORT global Interrupt                                             */
  SPI2_IRQn_MORT                   = 36,     /*!< SPI2_MORT global Interrupt                                             */
  USART1_IRQn_MORT                 = 37,     /*!< USART1_MORT global Interrupt                                           */
  USART2_IRQn_MORT                 = 38,     /*!< USART2_MORT global Interrupt                                           */
  USART3_IRQn_MORT                 = 39,     /*!< USART3_MORT global Interrupt                                           */
  EXTI15_10_IRQn_MORT              = 40,     /*!< External Line[15:10] Interrupts                                   */
  RTC_Alarm_IRQn_MORT              = 41,     /*!< RTC_MORT Alarm (A and B) through EXTI_MORT Line Interrupt                   */
  OTG_FS_WKUP_IRQn_MORT            = 42,     /*!< USB OTG FS Wakeup through EXTI_MORT line interrupt                     */    
  TIM8_BRK_IRQn_MORT               = 43,     /*!< TIM8_MORT Break Interrupt                                              */
  TIM8_BRK_TIM12_IRQn_MORT         = 43,     /*!< TIM8_MORT Break Interrupt and TIM12_MORT global interrupt                   */
  TIM8_UP_TIM13_IRQn_MORT          = 44,     /*!< TIM8_MORT Update Interrupt and TIM13_MORT global interrupt                  */
  TIM8_TRG_COM_TIM14_IRQn_MORT     = 45,     /*!< TIM8_MORT Trigger and Commutation Interrupt and TIM14_MORT global interrupt */
  DMA1_Stream7_IRQn_MORT           = 47,     /*!< DMA1_MORT Stream7 Interrupt                                            */
  FMC_IRQn_MORT                    = 48,     /*!< FMC global Interrupt                                              */
  SDIO_IRQn_MORT                   = 49,     /*!< SDIO_MORT global Interrupt                                             */
  TIM5_IRQn_MORT                   = 50,     /*!< TIM5_MORT global Interrupt                                             */
  SPI3_IRQn_MORT                   = 51,     /*!< SPI3_MORT global Interrupt                                             */
  UART4_IRQn_MORT                  = 52,     /*!< UART4_MORT global Interrupt                                            */
  UART5_IRQn_MORT                  = 53,     /*!< UART5_MORT global Interrupt                                            */
  TIM6_DAC_IRQn_MORT               = 54,     /*!< TIM6_MORT global and DAC1&2 underrun error  interrupts                 */
  TIM7_IRQn_MORT                   = 55,     /*!< TIM7_MORT global interrupt                                             */
  DMA2_Stream0_IRQn_MORT           = 56,     /*!< DMA2_MORT Stream 0 global Interrupt                                    */
  DMA2_Stream1_IRQn_MORT           = 57,     /*!< DMA2_MORT Stream 1 global Interrupt                                    */
  DMA2_Stream2_IRQn_MORT           = 58,     /*!< DMA2_MORT Stream 2 global Interrupt                                    */
  DMA2_Stream3_IRQn_MORT           = 59,     /*!< DMA2_MORT Stream 3 global Interrupt                                    */
  DMA2_Stream4_IRQn_MORT           = 60,     /*!< DMA2_MORT Stream 4 global Interrupt                                    */
  CAN2_TX_IRQn_MORT                = 63,     /*!< CAN2_MORT TX Interrupt                                                 */
  CAN2_RX0_IRQn_MORT               = 64,     /*!< CAN2_MORT RX0 Interrupt                                                */
  CAN2_RX1_IRQn_MORT               = 65,     /*!< CAN2_MORT RX1 Interrupt                                                */
  CAN2_SCE_IRQn_MORT               = 66,     /*!< CAN2_MORT SCE Interrupt                                                */
  OTG_FS_IRQn_MORT                 = 67,     /*!< USB OTG FS global Interrupt                                       */
  DMA2_Stream5_IRQn_MORT           = 68,     /*!< DMA2_MORT Stream 5 global interrupt                                    */
  DMA2_Stream6_IRQn_MORT           = 69,     /*!< DMA2_MORT Stream 6 global interrupt                                    */
  DMA2_Stream7_IRQn_MORT           = 70,     /*!< DMA2_MORT Stream 7 global interrupt                                    */
  USART6_IRQn_MORT                 = 71,     /*!< USART6_MORT global interrupt                                           */
  I2C3_EV_IRQn_MORT                = 72,     /*!< I2C3_MORT event interrupt                                              */
  I2C3_ER_IRQn_MORT                = 73,     /*!< I2C3_MORT error interrupt                                              */
  OTG_HS_EP1_OUT_IRQn_MORT         = 74,     /*!< USB OTG HS End Point 1 Out global interrupt                       */
  OTG_HS_EP1_IN_IRQn_MORT          = 75,     /*!< USB OTG HS End Point 1 In global interrupt                        */
  OTG_HS_WKUP_IRQn_MORT            = 76,     /*!< USB OTG HS Wakeup through EXTI_MORT interrupt                          */
  OTG_HS_IRQn_MORT                 = 77,     /*!< USB OTG HS global interrupt                                       */
  DCMI_IRQn_MORT                   = 78,     /*!< DCMI_MORT global interrupt                                             */
  FPU_IRQn_MORT                    = 81,     /*!< FPU global interrupt                                              */
  SPI4_IRQn_MORT                   = 84,     /*!< SPI4_MORT global Interrupt                                             */
  SAI1_IRQn_MORT                   = 87,     /*!< SAI1_MORT global Interrupt                                             */
  SAI2_IRQn_MORT                   = 91,     /*!< SAI2_MORT global Interrupt                                             */
  QUADSPI_IRQn_MORT                = 92,     /*!< QUADSPI_MORT global Interrupt                                          */
  CEC_IRQn_MORT                    = 93,     /*!< QUADSPI_MORT global Interrupt                                          */
  SPDIF_RX_IRQn_MORT               = 94,     /*!< QUADSPI_MORT global Interrupt                                          */
  FMPI2C1_EV_IRQn_MORT             = 95,     /*!< FMPI2C Event Interrupt                                            */
  FMPI2C1_ER_IRQn_MORT             = 96      /*!< FMPCI2C Error Interrupt                                           */
#endif /* STM32F446xx_MORT */

#if defined(STM32F412xG)
                                            */
#endif /* STM32F412xG */

#if defined(STM32F413_423xx)
                                            */
                                   */
#endif /* STM32F413_423xx */
} IRQn_Type_MORT;

/**
  * @}
  */
#include "stm32f4xx.h"
#include "core_cm4.h"             /* Cortex-M4 processor and core peripherals */
#include "system_stm32f4xx.h"
#include <stdint.h>

/** @addtogroup Exported_types
  * @{
  */  
/*!< STM32F10x Standard Peripheral Library old types (maintained for legacy purpose) */
//typedef int32_t_mort  s32;
//typedef int16_t_mort s16;
//typedef int8_t_mort  s8;

//typedef const int32_t_mort sc32;  /*!< Read Only */
//typedef const int16_t_mort sc16;  /*!< Read Only */
//typedef const int8_t_mort sc8;   /*!< Read Only */

//typedef __IO int32_t_mort  vs32;
//typedef __IO int16_t_mort  vs16;
//typedef __IO int8_t_mort   vs8;

//typedef __I int32_t_mort vsc32;  /*!< Read Only */
//typedef __I int16_t_mort vsc16;  /*!< Read Only */
//typedef __I int8_t_mort vsc8;   /*!< Read Only */

//typedef uint32_t_mort  u32;
//typedef uint16_t_mort u16;
//typedef uint8_t_mort  u8;

//typedef const uint32_t_mort uc32;  /*!< Read Only */
//typedef const uint16_t_mort uc16;  /*!< Read Only */
//typedef const uint8_t_mort uc8;   /*!< Read Only */

//typedef __IO uint32_t_mort  vu32;
//typedef __IO uint16_t_mort vu16;
//typedef __IO uint8_t_mort  vu8;

//typedef __I uint32_t_mort vuc32;  /*!< Read Only */
//typedef __I uint16_t_mort vuc16;  /*!< Read Only */
//typedef __I uint8_t_mort vuc8;   /*!< Read Only */

typedef enum {RESET_MORT = 0, SET_MORT = !RESET_MORT} FlagStatus_MORT, ITStatus_MORT;

typedef enum {DISABLE_MORT = 0, ENABLE_MORT = !DISABLE_MORT} FunctionalState_MORT;
#define IS_FUNCTIONAL_STATE_MORT(STATE) (((STATE) == DISABLE_MORT) || ((STATE) == ENABLE_MORT))

typedef enum {ERROR_MORT = 0, SUCCESS_MORT = !ERROR} ErrorStatus_MORT;

/**
  * @}
  */

/** @addtogroup Peripheral_registers_structures
  * @{
  */   

/** 
  * @brief Analog to Digital Converter  
  */

typedef struct
{
  __IO uint32_t SR;     /*!< ADC_MORT status register,                         Address offset: 0x00 */
  __IO uint32_t CR1;    /*!< ADC_MORT control register 1,                      Address offset: 0x04 */      
  __IO uint32_t CR2;    /*!< ADC_MORT control register 2,                      Address offset: 0x08 */
  __IO uint32_t SMPR1;  /*!< ADC_MORT sample time register 1,                  Address offset: 0x0C */
  __IO uint32_t SMPR2;  /*!< ADC_MORT sample time register 2,                  Address offset: 0x10 */
  __IO uint32_t JOFR1;  /*!< ADC_MORT injected channel data offset register 1, Address offset: 0x14 */
  __IO uint32_t JOFR2;  /*!< ADC_MORT injected channel data offset register 2, Address offset: 0x18 */
  __IO uint32_t JOFR3;  /*!< ADC_MORT injected channel data offset register 3, Address offset: 0x1C */
  __IO uint32_t JOFR4;  /*!< ADC_MORT injected channel data offset register 4, Address offset: 0x20 */
  __IO uint32_t HTR;    /*!< ADC_MORT watchdog higher threshold register,      Address offset: 0x24 */
  __IO uint32_t LTR;    /*!< ADC_MORT watchdog lower threshold register,       Address offset: 0x28 */
  __IO uint32_t SQR1;   /*!< ADC_MORT regular sequence register 1,             Address offset: 0x2C */
  __IO uint32_t SQR2;   /*!< ADC_MORT regular sequence register 2,             Address offset: 0x30 */
  __IO uint32_t SQR3;   /*!< ADC_MORT regular sequence register 3,             Address offset: 0x34 */
  __IO uint32_t JSQR;   /*!< ADC_MORT injected sequence register,              Address offset: 0x38 */
  __IO uint32_t JDR1;   /*!< ADC_MORT injected data register 1,                Address offset: 0x3C */
  __IO uint32_t JDR2;   /*!< ADC_MORT injected data register 2,                Address offset: 0x40 */
  __IO uint32_t JDR3;   /*!< ADC_MORT injected data register 3,                Address offset: 0x44 */
  __IO uint32_t JDR4;   /*!< ADC_MORT injected data register 4,                Address offset: 0x48 */
  __IO uint32_t DR;     /*!< ADC_MORT regular data register,                   Address offset: 0x4C */
} ADC_TypeDef_mort;

typedef struct
{
  __IO uint32_t CSR;    /*!< ADC_MORT Common status register,                  Address offset: ADC1_MORT base address + 0x300 */
  __IO uint32_t CCR;    /*!< ADC_MORT common control register,                 Address offset: ADC1_MORT base address + 0x304 */
  __IO uint32_t CDR;    /*!< ADC_MORT common regular data register for dual
                             AND triple modes,                            Address offset: ADC1_MORT base address + 0x308 */
} ADC_Common_TypeDef_mort;


/** 
  * @brief Controller Area Network TxMailBox 
  */

typedef struct
{
  __IO uint32_t TIR;  /*!< CAN TX mailbox identifier register */
  __IO uint32_t TDTR; /*!< CAN mailbox data length control and time stamp register */
  __IO uint32_t TDLR; /*!< CAN mailbox data low register */
  __IO uint32_t TDHR; /*!< CAN mailbox data high register */
} CAN_TxMailBox_TypeDef_mort;

/** 
  * @brief Controller Area Network FIFOMailBox 
  */
  
typedef struct
{
  __IO uint32_t RIR;  /*!< CAN receive FIFO mailbox identifier register */
  __IO uint32_t RDTR; /*!< CAN receive FIFO mailbox data length control and time stamp register */
  __IO uint32_t RDLR; /*!< CAN receive FIFO mailbox data low register */
  __IO uint32_t RDHR; /*!< CAN receive FIFO mailbox data high register */
} CAN_FIFOMailBox_TypeDef_mort;

/** 
  * @brief Controller Area Network FilterRegister 
  */
  
typedef struct
{
  __IO uint32_t FR1; /*!< CAN Filter bank register 1 */
  __IO uint32_t FR2; /*!< CAN Filter bank register 1 */
} CAN_FilterRegister_TypeDef_mort;

/** 
  * @brief Controller Area Network 
  */
  
typedef struct
{
  __IO uint32_t              MCR;                 /*!< CAN master control register,         Address offset: 0x00          */
  __IO uint32_t              MSR;                 /*!< CAN master status register,          Address offset: 0x04          */
  __IO uint32_t              TSR;                 /*!< CAN transmit status register,        Address offset: 0x08          */
  __IO uint32_t              RF0R;                /*!< CAN receive FIFO 0 register,         Address offset: 0x0C          */
  __IO uint32_t              RF1R;                /*!< CAN receive FIFO 1 register,         Address offset: 0x10          */
  __IO uint32_t              IER;                 /*!< CAN interrupt enable register,       Address offset: 0x14          */
  __IO uint32_t              ESR;                 /*!< CAN error status register,           Address offset: 0x18          */
  __IO uint32_t              BTR;                 /*!< CAN bit timing register,             Address offset: 0x1C          */
  uint32_t                   RESERVED0[88];       /*!< Reserved, 0x020 - 0x17F                                            */
  CAN_TxMailBox_TypeDef_mort      sTxMailBox[3];       /*!< CAN Tx MailBox,                      Address offset: 0x180 - 0x1AC */
  CAN_FIFOMailBox_TypeDef_mort    sFIFOMailBox[2];     /*!< CAN FIFO MailBox,                    Address offset: 0x1B0 - 0x1CC */
  uint32_t                   RESERVED1[12];       /*!< Reserved, 0x1D0 - 0x1FF                                            */
  __IO uint32_t              FMR;                 /*!< CAN filter master register,          Address offset: 0x200         */
  __IO uint32_t              FM1R;                /*!< CAN filter mode register,            Address offset: 0x204         */
  uint32_t                   RESERVED2;           /*!< Reserved, 0x208                                                    */
  __IO uint32_t              FS1R;                /*!< CAN filter scale register,           Address offset: 0x20C         */
  uint32_t                   RESERVED3;           /*!< Reserved, 0x210                                                    */
  __IO uint32_t              FFA1R;               /*!< CAN filter FIFO assignment register, Address offset: 0x214         */
  uint32_t                   RESERVED4;           /*!< Reserved, 0x218                                                    */
  __IO uint32_t              FA1R;                /*!< CAN filter activation register,      Address offset: 0x21C         */
  uint32_t                   RESERVED5[8];        /*!< Reserved, 0x220-0x23F                                              */ 
  CAN_FilterRegister_TypeDef_mort sFilterRegister[28]; /*!< CAN Filter Register,                 Address offset: 0x240-0x31C   */
} CAN_TypeDef_mort;

#if defined(STM32F446xx_MORT)
/**
  * @brief Consumer Electronics Control
  */
typedef struct
{
  __IO uint32_t CR;           /*!< CEC_MORT control register,              Address offset:0x00 */
  __IO uint32_t CFGR;         /*!< CEC_MORT configuration register,        Address offset:0x04 */
  __IO uint32_t TXDR;         /*!< CEC_MORT Tx data register ,             Address offset:0x08 */
  __IO uint32_t RXDR;         /*!< CEC_MORT Rx Data Register,              Address offset:0x0C */
  __IO uint32_t ISR;          /*!< CEC_MORT Interrupt and Status Register, Address offset:0x10 */
  __IO uint32_t IER;          /*!< CEC_MORT interrupt enable register,     Address offset:0x14 */
}CEC_TypeDef_mort;
#endif /* STM32F446xx_MORT */

/** 
  * @brief CRC_MORT calculation unit 
  */

typedef struct
{
  __IO uint32_t DR;         /*!< CRC_MORT Data register,             Address offset: 0x00 */
  __IO uint8_t  IDR;        /*!< CRC_MORT Independent data register, Address offset: 0x04 */
  uint8_t       RESERVED0;  /*!< Reserved, 0x05                                      */
  uint16_t      RESERVED1;  /*!< Reserved, 0x06                                      */
  __IO uint32_t CR;         /*!< CRC_MORT Control register,          Address offset: 0x08 */
} CRC_TypeDef_mort;

/** 
  * @brief Digital to Analog Converter
  */

typedef struct
{
  __IO uint32_t CR;       /*!< DAC_MORT control register,                                    Address offset: 0x00 */
  __IO uint32_t SWTRIGR;  /*!< DAC_MORT software trigger register,                           Address offset: 0x04 */
  __IO uint32_t DHR12R1;  /*!< DAC_MORT channel1 12-bit right-aligned data holding register, Address offset: 0x08 */
  __IO uint32_t DHR12L1;  /*!< DAC_MORT channel1 12-bit left aligned data holding register,  Address offset: 0x0C */
  __IO uint32_t DHR8R1;   /*!< DAC_MORT channel1 8-bit right aligned data holding register,  Address offset: 0x10 */
  __IO uint32_t DHR12R2;  /*!< DAC_MORT channel2 12-bit right aligned data holding register, Address offset: 0x14 */
  __IO uint32_t DHR12L2;  /*!< DAC_MORT channel2 12-bit left aligned data holding register,  Address offset: 0x18 */
  __IO uint32_t DHR8R2;   /*!< DAC_MORT channel2 8-bit right-aligned data holding register,  Address offset: 0x1C */
  __IO uint32_t DHR12RD;  /*!< Dual DAC_MORT 12-bit right-aligned data holding register,     Address offset: 0x20 */
  __IO uint32_t DHR12LD;  /*!< DUAL DAC_MORT 12-bit left aligned data holding register,      Address offset: 0x24 */
  __IO uint32_t DHR8RD;   /*!< DUAL DAC_MORT 8-bit right aligned data holding register,      Address offset: 0x28 */
  __IO uint32_t DOR1;     /*!< DAC_MORT channel1 data output register,                       Address offset: 0x2C */
  __IO uint32_t DOR2;     /*!< DAC_MORT channel2 data output register,                       Address offset: 0x30 */
  __IO uint32_t SR;       /*!< DAC_MORT status register,                                     Address offset: 0x34 */
} DAC_TypeDef_mort;

#if defined(STM32F412xG) || defined(STM32F413_423xx)
/**
  * @brief DFSDM module registers
  */
typedef struct
{
  __IO uint32_t FLTCR1;         /*!< DFSDM control register1,                          Address offset: 0x100 */
  __IO uint32_t FLTCR2;         /*!< DFSDM control register2,                          Address offset: 0x104 */
  __IO uint32_t FLTISR;         /*!< DFSDM interrupt and status register,              Address offset: 0x108 */
  __IO uint32_t FLTICR;         /*!< DFSDM interrupt flag clear register,              Address offset: 0x10C */
  __IO uint32_t FLTJCHGR;       /*!< DFSDM injected channel group selection register,  Address offset: 0x110 */
  __IO uint32_t FLTFCR;         /*!< DFSDM filter control register,                    Address offset: 0x114 */
  __IO uint32_t FLTJDATAR;      /*!< DFSDM data register for injected group,           Address offset: 0x118 */
  __IO uint32_t FLTRDATAR;      /*!< DFSDM data register for regular group,            Address offset: 0x11C */
  __IO uint32_t FLTAWHTR;       /*!< DFSDM analog watchdog high threshold register,    Address offset: 0x120 */
  __IO uint32_t FLTAWLTR;       /*!< DFSDM analog watchdog low threshold register,     Address offset: 0x124 */
  __IO uint32_t FLTAWSR;        /*!< DFSDM analog watchdog status register             Address offset: 0x128 */
  __IO uint32_t FLTAWCFR;       /*!< DFSDM analog watchdog clear flag register         Address offset: 0x12C */
  __IO uint32_t FLTEXMAX;       /*!< DFSDM extreme detector maximum register,          Address offset: 0x130 */
  __IO uint32_t FLTEXMIN;       /*!< DFSDM extreme detector minimum register           Address offset: 0x134 */
  __IO uint32_t FLTCNVTIMR;     /*!< DFSDM conversion timer,                           Address offset: 0x138 */
} DFSDM_Filter_TypeDef_mort;

/**
  * @brief DFSDM channel configuration registers
  */
typedef struct
{
  __IO uint32_t CHCFGR1;     /*!< DFSDM channel configuration register1,            Address offset: 0x00 */
  __IO uint32_t CHCFGR2;     /*!< DFSDM channel configuration register2,            Address offset: 0x04 */
  __IO uint32_t CHAWSCDR;    /*!< DFSDM channel analog watchdog and
                                  short circuit detector register,                  Address offset: 0x08 */
  __IO uint32_t CHWDATAR;    /*!< DFSDM channel watchdog filter data register,      Address offset: 0x0C */
  __IO uint32_t CHDATINR;    /*!< DFSDM channel data input register,                Address offset: 0x10 */
} DFSDM_Channel_TypeDef_mort;

/* Legacy Defines */
#define DFSDM_TypeDef        DFSDM_Filter_TypeDef_mort
#endif /* STM32F412xG || STM32F413_423xx */
/** 
  * @brief Debug MCU
  */

typedef struct
{
  __IO uint32_t IDCODE;  /*!< MCU device ID code,               Address offset: 0x00 */
  __IO uint32_t CR;      /*!< Debug MCU configuration register, Address offset: 0x04 */
  __IO uint32_t APB1FZ;  /*!< Debug MCU APB1 freeze register,   Address offset: 0x08 */
  __IO uint32_t APB2FZ;  /*!< Debug MCU APB2 freeze register,   Address offset: 0x0C */
}DBGMCU_TypeDef_mort;

/** 
  * @brief DCMI_MORT
  */

typedef struct
{
  __IO uint32_t CR;       /*!< DCMI_MORT control register 1,                       Address offset: 0x00 */
  __IO uint32_t SR;       /*!< DCMI_MORT status register,                          Address offset: 0x04 */
  __IO uint32_t RISR;     /*!< DCMI_MORT raw interrupt status register,            Address offset: 0x08 */
  __IO uint32_t IER;      /*!< DCMI_MORT interrupt enable register,                Address offset: 0x0C */
  __IO uint32_t MISR;     /*!< DCMI_MORT masked interrupt status register,         Address offset: 0x10 */
  __IO uint32_t ICR;      /*!< DCMI_MORT interrupt clear register,                 Address offset: 0x14 */
  __IO uint32_t ESCR;     /*!< DCMI_MORT embedded synchronization code register,   Address offset: 0x18 */
  __IO uint32_t ESUR;     /*!< DCMI_MORT embedded synchronization unmask register, Address offset: 0x1C */
  __IO uint32_t CWSTRTR;  /*!< DCMI_MORT crop window start,                        Address offset: 0x20 */
  __IO uint32_t CWSIZER;  /*!< DCMI_MORT crop window size,                         Address offset: 0x24 */
  __IO uint32_t DR;       /*!< DCMI_MORT data register,                            Address offset: 0x28 */
} DCMI_TypeDef_mort;

/** 
  * @brief DMA Controller
  */

typedef struct
{
  __IO uint32_t CR;     /*!< DMA stream x configuration register      */
  __IO uint32_t NDTR;   /*!< DMA stream x number of data register     */
  __IO uint32_t PAR;    /*!< DMA stream x peripheral address register */
  __IO uint32_t M0AR;   /*!< DMA stream x memory 0 address register   */
  __IO uint32_t M1AR;   /*!< DMA stream x memory 1 address register   */
  __IO uint32_t FCR;    /*!< DMA stream x FIFO control register       */
} DMA_Stream_TypeDef_mort;

typedef struct
{
  __IO uint32_t LISR;   /*!< DMA low interrupt status register,      Address offset: 0x00 */
  __IO uint32_t HISR;   /*!< DMA high interrupt status register,     Address offset: 0x04 */
  __IO uint32_t LIFCR;  /*!< DMA low interrupt flag clear register,  Address offset: 0x08 */
  __IO uint32_t HIFCR;  /*!< DMA high interrupt flag clear register, Address offset: 0x0C */
} DMA_TypeDef_mort;
 
/** 
  * @brief DMA2D_MORT Controller
  */

typedef struct
{
  __IO uint32_t CR;            /*!< DMA2D_MORT Control Register,                         Address offset: 0x00 */
  __IO uint32_t ISR;           /*!< DMA2D_MORT Interrupt Status Register,                Address offset: 0x04 */
  __IO uint32_t IFCR;          /*!< DMA2D_MORT Interrupt Flag Clear Register,            Address offset: 0x08 */
  __IO uint32_t FGMAR;         /*!< DMA2D_MORT Foreground Memory Address Register,       Address offset: 0x0C */
  __IO uint32_t FGOR;          /*!< DMA2D_MORT Foreground Offset Register,               Address offset: 0x10 */
  __IO uint32_t BGMAR;         /*!< DMA2D_MORT Background Memory Address Register,       Address offset: 0x14 */
  __IO uint32_t BGOR;          /*!< DMA2D_MORT Background Offset Register,               Address offset: 0x18 */
  __IO uint32_t FGPFCCR;       /*!< DMA2D_MORT Foreground PFC Control Register,          Address offset: 0x1C */
  __IO uint32_t FGCOLR;        /*!< DMA2D_MORT Foreground Color Register,                Address offset: 0x20 */
  __IO uint32_t BGPFCCR;       /*!< DMA2D_MORT Background PFC Control Register,          Address offset: 0x24 */
  __IO uint32_t BGCOLR;        /*!< DMA2D_MORT Background Color Register,                Address offset: 0x28 */
  __IO uint32_t FGCMAR;        /*!< DMA2D_MORT Foreground CLUT Memory Address Register,  Address offset: 0x2C */
  __IO uint32_t BGCMAR;        /*!< DMA2D_MORT Background CLUT Memory Address Register,  Address offset: 0x30 */
  __IO uint32_t OPFCCR;        /*!< DMA2D_MORT Output PFC Control Register,              Address offset: 0x34 */
  __IO uint32_t OCOLR;         /*!< DMA2D_MORT Output Color Register,                    Address offset: 0x38 */
  __IO uint32_t OMAR;          /*!< DMA2D_MORT Output Memory Address Register,           Address offset: 0x3C */
  __IO uint32_t OOR;           /*!< DMA2D_MORT Output Offset Register,                   Address offset: 0x40 */
  __IO uint32_t NLR;           /*!< DMA2D_MORT Number of Line Register,                  Address offset: 0x44 */
  __IO uint32_t LWR;           /*!< DMA2D_MORT Line Watermark Register,                  Address offset: 0x48 */
  __IO uint32_t AMTCR;         /*!< DMA2D_MORT AHB Master Timer Configuration Register,  Address offset: 0x4C */
  uint32_t      RESERVED[236]; /*!< Reserved, 0x50-0x3FF */
  __IO uint32_t FGCLUT[256];   /*!< DMA2D_MORT Foreground CLUT,                          Address offset:400-7FF */
  __IO uint32_t BGCLUT[256];   /*!< DMA2D_MORT Background CLUT,                          Address offset:800-BFF */
} DMA2D_TypeDef_mort;

#if defined(STM32F469_479xx)
/** 
  * @brief DSI_MORT Controller
  */

typedef struct
{
  __IO uint32_t VR;             /*!< DSI_MORT Host Version Register,                                 Address offset: 0x00       */
  __IO uint32_t CR;             /*!< DSI_MORT Host Control Register,                                 Address offset: 0x04       */
  __IO uint32_t CCR;            /*!< DSI_MORT HOST Clock Control Register,                           Address offset: 0x08       */
  __IO uint32_t LVCIDR;         /*!< DSI_MORT Host LTDC_MORT VCID Register,                               Address offset: 0x0C       */
  __IO uint32_t LCOLCR;         /*!< DSI_MORT Host LTDC_MORT Color Coding Register,                       Address offset: 0x10       */ 
  __IO uint32_t LPCR;           /*!< DSI_MORT Host LTDC_MORT Polarity Configuration Register,             Address offset: 0x14       */
  __IO uint32_t LPMCR;          /*!< DSI_MORT Host Low-Power Mode Configuration Register,            Address offset: 0x18       */
  uint32_t      RESERVED0[4];   /*!< Reserved, 0x1C - 0x2B                                                                 */
  __IO uint32_t PCR;            /*!< DSI_MORT Host Protocol Configuration Register,                  Address offset: 0x2C       */ 
  __IO uint32_t GVCIDR;         /*!< DSI_MORT Host Generic VCID Register,                            Address offset: 0x30       */
  __IO uint32_t MCR;            /*!< DSI_MORT Host Mode Configuration Register,                      Address offset: 0x34       */
  __IO uint32_t VMCR;           /*!< DSI_MORT Host Video Mode Configuration Register,                Address offset: 0x38       */
  __IO uint32_t VPCR;           /*!< DSI_MORT Host Video Packet Configuration Register,              Address offset: 0x3C       */
  __IO uint32_t VCCR;           /*!< DSI_MORT Host Video Chunks Configuration Register,              Address offset: 0x40       */
  __IO uint32_t VNPCR;          /*!< DSI_MORT Host Video Null Packet Configuration Register,         Address offset: 0x44       */
  __IO uint32_t VHSACR;         /*!< DSI_MORT Host Video HSA Configuration Register,                 Address offset: 0x48       */
  __IO uint32_t VHBPCR;         /*!< DSI_MORT Host Video HBP Configuration Register,                 Address offset: 0x4C       */
  __IO uint32_t VLCR;           /*!< DSI_MORT Host Video Line Configuration Register,                Address offset: 0x50       */
  __IO uint32_t VVSACR;         /*!< DSI_MORT Host Video VSA Configuration Register,                 Address offset: 0x54       */
  __IO uint32_t VVBPCR;         /*!< DSI_MORT Host Video VBP Configuration Register,                 Address offset: 0x58       */
  __IO uint32_t VVFPCR;         /*!< DSI_MORT Host Video VFP Configuration Register,                 Address offset: 0x5C       */
  __IO uint32_t VVACR;          /*!< DSI_MORT Host Video VA Configuration Register,                  Address offset: 0x60       */
  __IO uint32_t LCCR;           /*!< DSI_MORT Host LTDC_MORT Command Configuration Register,              Address offset: 0x64       */ 
  __IO uint32_t CMCR;           /*!< DSI_MORT Host Command Mode Configuration Register,              Address offset: 0x68       */
  __IO uint32_t GHCR;           /*!< DSI_MORT Host Generic Header Configuration Register,            Address offset: 0x6C       */
  __IO uint32_t GPDR;           /*!< DSI_MORT Host Generic Payload Data Register,                    Address offset: 0x70       */
  __IO uint32_t GPSR;           /*!< DSI_MORT Host Generic Packet Status Register,                   Address offset: 0x74       */
  __IO uint32_t TCCR[6];        /*!< DSI_MORT Host Timeout Counter Configuration Register,           Address offset: 0x78-0x8F  */
  __IO uint32_t TDCR;           /*!< DSI_MORT Host 3D Configuration Register,                        Address offset: 0x90       */ 
  __IO uint32_t CLCR;           /*!< DSI_MORT Host Clock Lane Configuration Register,                Address offset: 0x94       */
  __IO uint32_t CLTCR;          /*!< DSI_MORT Host Clock Lane Timer Configuration Register,          Address offset: 0x98       */
  __IO uint32_t DLTCR;          /*!< DSI_MORT Host Data Lane Timer Configuration Register,           Address offset: 0x9C       */
  __IO uint32_t PCTLR;          /*!< DSI_MORT Host PHY Control Register,                             Address offset: 0xA0       */ 
  __IO uint32_t PCONFR;         /*!< DSI_MORT Host PHY Configuration Register,                       Address offset: 0xA4       */ 
  __IO uint32_t PUCR;           /*!< DSI_MORT Host PHY ULPS Control Register,                        Address offset: 0xA8       */
  __IO uint32_t PTTCR;          /*!< DSI_MORT Host PHY TX Triggers Configuration Register,           Address offset: 0xAC       */
  __IO uint32_t PSR;            /*!< DSI_MORT Host PHY Status Register,                              Address offset: 0xB0       */
  uint32_t      RESERVED1[2];   /*!< Reserved, 0xB4 - 0xBB                                                                 */
  __IO uint32_t ISR[2];         /*!< DSI_MORT Host Interrupt & Status Register,                      Address offset: 0xBC-0xC3  */
  __IO uint32_t IER[2];         /*!< DSI_MORT Host Interrupt Enable Register,                        Address offset: 0xC4-0xCB  */
  uint32_t      RESERVED2[3];   /*!< Reserved, 0xD0 - 0xD7                                                                 */
  __IO uint32_t FIR[2];         /*!< DSI_MORT Host Force Interrupt Register,                         Address offset: 0xD8-0xDF  */
  uint32_t      RESERVED3[8];   /*!< Reserved, 0xE0 - 0xFF                                                                 */
  __IO uint32_t VSCR;           /*!< DSI_MORT Host Video Shadow Control Register,                    Address offset: 0x100      */
  uint32_t      RESERVED4[2];   /*!< Reserved, 0x104 - 0x10B                                                               */
  __IO uint32_t LCVCIDR;        /*!< DSI_MORT Host LTDC_MORT Current VCID Register,                       Address offset: 0x10C      */
  __IO uint32_t LCCCR;          /*!< DSI_MORT Host LTDC_MORT Current Color Coding Register,               Address offset: 0x110      */
  uint32_t      RESERVED5;      /*!< Reserved, 0x114                                                                       */
  __IO uint32_t LPMCCR;         /*!< DSI_MORT Host Low-power Mode Current Configuration Register,    Address offset: 0x118      */
  uint32_t      RESERVED6[7];   /*!< Reserved, 0x11C - 0x137                                                               */
  __IO uint32_t VMCCR;          /*!< DSI_MORT Host Video Mode Current Configuration Register,        Address offset: 0x138      */
  __IO uint32_t VPCCR;          /*!< DSI_MORT Host Video Packet Current Configuration Register,      Address offset: 0x13C      */
  __IO uint32_t VCCCR;          /*!< DSI_MORT Host Video Chuncks Current Configuration Register,     Address offset: 0x140      */
  __IO uint32_t VNPCCR;         /*!< DSI_MORT Host Video Null Packet Current Configuration Register, Address offset: 0x144      */
  __IO uint32_t VHSACCR;        /*!< DSI_MORT Host Video HSA Current Configuration Register,         Address offset: 0x148      */
  __IO uint32_t VHBPCCR;        /*!< DSI_MORT Host Video HBP Current Configuration Register,         Address offset: 0x14C      */
  __IO uint32_t VLCCR;          /*!< DSI_MORT Host Video Line Current Configuration Register,        Address offset: 0x150      */
  __IO uint32_t VVSACCR;        /*!< DSI_MORT Host Video VSA Current Configuration Register,         Address offset: 0x154      */ 
  __IO uint32_t VVBPCCR;        /*!< DSI_MORT Host Video VBP Current Configuration Register,         Address offset: 0x158      */
  __IO uint32_t VVFPCCR;        /*!< DSI_MORT Host Video VFP Current Configuration Register,         Address offset: 0x15C      */
  __IO uint32_t VVACCR;         /*!< DSI_MORT Host Video VA Current Configuration Register,          Address offset: 0x160      */
  uint32_t      RESERVED7[11];  /*!< Reserved, 0x164 - 0x18F                                                               */
  __IO uint32_t TDCCR;          /*!< DSI_MORT Host 3D Current Configuration Register,                Address offset: 0x190      */
  uint32_t      RESERVED8[155]; /*!< Reserved, 0x194 - 0x3FF                                                               */
  __IO uint32_t WCFGR;          /*!< DSI_MORT Wrapper Configuration Register,                       Address offset: 0x400       */
  __IO uint32_t WCR;            /*!< DSI_MORT Wrapper Control Register,                             Address offset: 0x404       */
  __IO uint32_t WIER;           /*!< DSI_MORT Wrapper Interrupt Enable Register,                    Address offset: 0x408       */
  __IO uint32_t WISR;           /*!< DSI_MORT Wrapper Interrupt and Status Register,                Address offset: 0x40C       */
  __IO uint32_t WIFCR;          /*!< DSI_MORT Wrapper Interrupt Flag Clear Register,                Address offset: 0x410       */
  uint32_t      RESERVED9;      /*!< Reserved, 0x414                                                                       */
  __IO uint32_t WPCR[5];        /*!< DSI_MORT Wrapper PHY Configuration Register,                   Address offset: 0x418-0x42B */
  uint32_t      RESERVED10;     /*!< Reserved, 0x42C                                                                       */
  __IO uint32_t WRPCR;          /*!< DSI_MORT Wrapper Regulator and PLL Control Register, Address offset: 0x430                 */
} DSI_TypeDef_mort;
#endif /* STM32F469_479xx */

/** 
  * @brief Ethernet MAC
  */

typedef struct
{
  __IO uint32_t MACCR;
  __IO uint32_t MACFFR;
  __IO uint32_t MACHTHR;
  __IO uint32_t MACHTLR;
  __IO uint32_t MACMIIAR;
  __IO uint32_t MACMIIDR;
  __IO uint32_t MACFCR;
  __IO uint32_t MACVLANTR;             /*    8 */
  uint32_t      RESERVED0[2];
  __IO uint32_t MACRWUFFR;             /*   11 */
  __IO uint32_t MACPMTCSR;
  uint32_t      RESERVED1[2];
  __IO uint32_t MACSR;                 /*   15 */
  __IO uint32_t MACIMR;
  __IO uint32_t MACA0HR;
  __IO uint32_t MACA0LR;
  __IO uint32_t MACA1HR;
  __IO uint32_t MACA1LR;
  __IO uint32_t MACA2HR;
  __IO uint32_t MACA2LR;
  __IO uint32_t MACA3HR;
  __IO uint32_t MACA3LR;               /*   24 */
  uint32_t      RESERVED2[40];
  __IO uint32_t MMCCR;                 /*   65 */
  __IO uint32_t MMCRIR;
  __IO uint32_t MMCTIR;
  __IO uint32_t MMCRIMR;
  __IO uint32_t MMCTIMR;               /*   69 */
  uint32_t      RESERVED3[14];
  __IO uint32_t MMCTGFSCCR;            /*   84 */
  __IO uint32_t MMCTGFMSCCR;
  uint32_t      RESERVED4[5];
  __IO uint32_t MMCTGFCR;
  uint32_t      RESERVED5[10];
  __IO uint32_t MMCRFCECR;
  __IO uint32_t MMCRFAECR;
  uint32_t      RESERVED6[10];
  __IO uint32_t MMCRGUFCR;
  uint32_t      RESERVED7[334];
  __IO uint32_t PTPTSCR;
  __IO uint32_t PTPSSIR;
  __IO uint32_t PTPTSHR;
  __IO uint32_t PTPTSLR;
  __IO uint32_t PTPTSHUR;
  __IO uint32_t PTPTSLUR;
  __IO uint32_t PTPTSAR;
  __IO uint32_t PTPTTHR;
  __IO uint32_t PTPTTLR;
  __IO uint32_t RESERVED8;
  __IO uint32_t PTPTSSR;
  uint32_t      RESERVED9[565];
  __IO uint32_t DMABMR;
  __IO uint32_t DMATPDR;
  __IO uint32_t DMARPDR;
  __IO uint32_t DMARDLAR;
  __IO uint32_t DMATDLAR;
  __IO uint32_t DMASR;
  __IO uint32_t DMAOMR;
  __IO uint32_t DMAIER;
  __IO uint32_t DMAMFBOCR;
  __IO uint32_t DMARSWTR;
  uint32_t      RESERVED10[8];
  __IO uint32_t DMACHTDR;
  __IO uint32_t DMACHRDR;
  __IO uint32_t DMACHTBAR;
  __IO uint32_t DMACHRBAR;
} ETH_TypeDef_mort;

/** 
  * @brief External Interrupt/Event Controller
  */

typedef struct
{
  __IO uint32_t IMR;    /*!< EXTI_MORT Interrupt mask register,            Address offset: 0x00 */
  __IO uint32_t EMR;    /*!< EXTI_MORT Event mask register,                Address offset: 0x04 */
  __IO uint32_t RTSR;   /*!< EXTI_MORT Rising trigger selection register,  Address offset: 0x08 */
  __IO uint32_t FTSR;   /*!< EXTI_MORT Falling trigger selection register, Address offset: 0x0C */
  __IO uint32_t SWIER;  /*!< EXTI_MORT Software interrupt event register,  Address offset: 0x10 */
  __IO uint32_t PR;     /*!< EXTI_MORT Pending register,                   Address offset: 0x14 */
} EXTI_TypeDef_mort;

/** 
  * @brief FLASH_MORT Registers
  */

typedef struct
{
  __IO uint32_t ACR;      /*!< FLASH_MORT access control register,   Address offset: 0x00 */
  __IO uint32_t KEYR;     /*!< FLASH_MORT key register,              Address offset: 0x04 */
  __IO uint32_t OPTKEYR;  /*!< FLASH_MORT option key register,       Address offset: 0x08 */
  __IO uint32_t SR;       /*!< FLASH_MORT status register,           Address offset: 0x0C */
  __IO uint32_t CR;       /*!< FLASH_MORT control register,          Address offset: 0x10 */
  __IO uint32_t OPTCR;    /*!< FLASH_MORT option control register ,  Address offset: 0x14 */
  __IO uint32_t OPTCR1;   /*!< FLASH_MORT option control register 1, Address offset: 0x18 */
} FLASH_TypeDef_mort;

#if defined(STM32F40_41xxx) || defined(STM32F412xG) || defined(STM32F413_423xx)
/** 
  * @brief Flexible Static Memory Controller
  */

typedef struct
{
  __IO uint32_t BTCR[8];    /*!< NOR/PSRAM chip-select control register(BCR) and chip-select timing register(BTR), Address offset: 0x00-1C */   
} FSMC_Bank1_TypeDef_mort; 

/** 
  * @brief Flexible Static Memory Controller Bank1E
  */
  
typedef struct
{
  __IO uint32_t BWTR[7];    /*!< NOR/PSRAM write timing registers, Address offset: 0x104-0x11C */
} FSMC_Bank1E_TypeDef_mort;

/** 
  * @brief Flexible Static Memory Controller Bank2
  */
  
typedef struct
{
  __IO uint32_t PCR2;       /*!< NAND FLASH_MORT control register 2,                       Address offset: 0x60 */
  __IO uint32_t SR2;        /*!< NAND FLASH_MORT FIFO status and interrupt register 2,     Address offset: 0x64 */
  __IO uint32_t PMEM2;      /*!< NAND FLASH_MORT Common memory space timing register 2,    Address offset: 0x68 */
  __IO uint32_t PATT2;      /*!< NAND FLASH_MORT Attribute memory space timing register 2, Address offset: 0x6C */
  uint32_t      RESERVED0;  /*!< Reserved, 0x70                                                            */
  __IO uint32_t ECCR2;      /*!< NAND FLASH_MORT ECC result registers 2,                   Address offset: 0x74 */
} FSMC_Bank2_TypeDef_mort;

/** 
  * @brief Flexible Static Memory Controller Bank3
  */
  
typedef struct
{
  __IO uint32_t PCR3;       /*!< NAND FLASH_MORT control register 3,                       Address offset: 0x80 */
  __IO uint32_t SR3;        /*!< NAND FLASH_MORT FIFO status and interrupt register 3,     Address offset: 0x84 */
  __IO uint32_t PMEM3;      /*!< NAND FLASH_MORT Common memory space timing register 3,    Address offset: 0x88 */
  __IO uint32_t PATT3;      /*!< NAND FLASH_MORT Attribute memory space timing register 3, Address offset: 0x8C */
  uint32_t      RESERVED0;  /*!< Reserved, 0x90                                                            */
  __IO uint32_t ECCR3;      /*!< NAND FLASH_MORT ECC result registers 3,                   Address offset: 0x94 */
} FSMC_Bank3_TypeDef_mort;

/** 
  * @brief Flexible Static Memory Controller Bank4
  */
  
typedef struct
{
  __IO uint32_t PCR4;       /*!< PC Card  control register 4,                       Address offset: 0xA0 */
  __IO uint32_t SR4;        /*!< PC Card  FIFO status and interrupt register 4,     Address offset: 0xA4 */
  __IO uint32_t PMEM4;      /*!< PC Card  Common memory space timing register 4,    Address offset: 0xA8 */
  __IO uint32_t PATT4;      /*!< PC Card  Attribute memory space timing register 4, Address offset: 0xAC */
  __IO uint32_t PIO4;       /*!< PC Card  I/O space timing register 4,              Address offset: 0xB0 */
} FSMC_Bank4_TypeDef_mort; 
#endif /* STM32F40_41xxx || STM32F412xG || STM32F413_423xx */

#if defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F446xx_MORT) || defined(STM32F469_479xx)
/** 
  * @brief Flexible Memory Controller
  */

typedef struct
{
  __IO uint32_t BTCR[8];    /*!< NOR/PSRAM chip-select control register(BCR) and chip-select timing register(BTR), Address offset: 0x00-1C */   
} FMC_Bank1_TypeDef_mort; 

/** 
  * @brief Flexible Memory Controller Bank1E
  */
  
typedef struct
{
  __IO uint32_t BWTR[7];    /*!< NOR/PSRAM write timing registers, Address offset: 0x104-0x11C */
} FMC_Bank1E_TypeDef_mort;

/** 
  * @brief Flexible Memory Controller Bank2
  */
  
typedef struct
{
  __IO uint32_t PCR2;       /*!< NAND FLASH_MORT control register 2,                       Address offset: 0x60 */
  __IO uint32_t SR2;        /*!< NAND FLASH_MORT FIFO status and interrupt register 2,     Address offset: 0x64 */
  __IO uint32_t PMEM2;      /*!< NAND FLASH_MORT Common memory space timing register 2,    Address offset: 0x68 */
  __IO uint32_t PATT2;      /*!< NAND FLASH_MORT Attribute memory space timing register 2, Address offset: 0x6C */
  uint32_t      RESERVED0;  /*!< Reserved, 0x70                                                            */
  __IO uint32_t ECCR2;      /*!< NAND FLASH_MORT ECC result registers 2,                   Address offset: 0x74 */
} FMC_Bank2_TypeDef_mort;

/** 
  * @brief Flexible Memory Controller Bank3
  */
  
typedef struct
{
  __IO uint32_t PCR3;       /*!< NAND FLASH_MORT control register 3,                       Address offset: 0x80 */
  __IO uint32_t SR3;        /*!< NAND FLASH_MORT FIFO status and interrupt register 3,     Address offset: 0x84 */
  __IO uint32_t PMEM3;      /*!< NAND FLASH_MORT Common memory space timing register 3,    Address offset: 0x88 */
  __IO uint32_t PATT3;      /*!< NAND FLASH_MORT Attribute memory space timing register 3, Address offset: 0x8C */
  uint32_t      RESERVED0;  /*!< Reserved, 0x90                                                            */
  __IO uint32_t ECCR3;      /*!< NAND FLASH_MORT ECC result registers 3,                   Address offset: 0x94 */
} FMC_Bank3_TypeDef_mort;

/** 
  * @brief Flexible Memory Controller Bank4
  */
  
typedef struct
{
  __IO uint32_t PCR4;       /*!< PC Card  control register 4,                       Address offset: 0xA0 */
  __IO uint32_t SR4;        /*!< PC Card  FIFO status and interrupt register 4,     Address offset: 0xA4 */
  __IO uint32_t PMEM4;      /*!< PC Card  Common memory space timing register 4,    Address offset: 0xA8 */
  __IO uint32_t PATT4;      /*!< PC Card  Attribute memory space timing register 4, Address offset: 0xAC */
  __IO uint32_t PIO4;       /*!< PC Card  I/O space timing register 4,              Address offset: 0xB0 */
} FMC_Bank4_TypeDef_mort; 

/** 
  * @brief Flexible Memory Controller Bank5_6
  */
  
typedef struct
{
  __IO uint32_t SDCR[2];        /*!< SDRAM Control registers ,      Address offset: 0x140-0x144  */
  __IO uint32_t SDTR[2];        /*!< SDRAM Timing registers ,       Address offset: 0x148-0x14C  */
  __IO uint32_t SDCMR;       /*!< SDRAM Command Mode register,    Address offset: 0x150  */
  __IO uint32_t SDRTR;       /*!< SDRAM Refresh Timer register,   Address offset: 0x154  */
  __IO uint32_t SDSR;        /*!< SDRAM Status register,          Address offset: 0x158  */
} FMC_Bank5_6_TypeDef_mort; 
#endif /* STM32F427_437xx ||  STM32F429_439xx || STM32F446xx_MORT || STM32F469_479xx */

/** 
  * @brief General Purpose I/O
  */

typedef struct
{
  __IO uint32_t MODER;    /*!< GPIO port mode register,               Address offset: 0x00      */
  __IO uint32_t OTYPER;   /*!< GPIO port output type register,        Address offset: 0x04      */
  __IO uint32_t OSPEEDR;  /*!< GPIO port output speed register,       Address offset: 0x08      */
  __IO uint32_t PUPDR;    /*!< GPIO port pull-up/pull-down register,  Address offset: 0x0C      */
  __IO uint32_t IDR;      /*!< GPIO port input data register,         Address offset: 0x10      */
  __IO uint32_t ODR;      /*!< GPIO port output data register,        Address offset: 0x14      */
  __IO uint16_t BSRRL;    /*!< GPIO port bit set/reset low register,  Address offset: 0x18      */
  __IO uint16_t BSRRH;    /*!< GPIO port bit set/reset high register, Address offset: 0x1A      */
  __IO uint32_t LCKR;     /*!< GPIO port configuration lock register, Address offset: 0x1C      */
  __IO uint32_t AFR[2];   /*!< GPIO alternate function registers,     Address offset: 0x20-0x24 */
} GPIO_TypeDef_mort;

/** 
  * @brief System configuration controller
  */
  
typedef struct
{
  __IO uint32_t MEMRMP;       /*!< SYSCFG_MORT memory remap register,                      Address offset: 0x00      */
  __IO uint32_t PMC;          /*!< SYSCFG_MORT peripheral mode configuration register,     Address offset: 0x04      */
  __IO uint32_t EXTICR[4];    /*!< SYSCFG_MORT external interrupt configuration registers, Address offset: 0x08-0x14 */
#if defined (STM32F410xx) || defined(STM32F412xG) || defined(STM32F413_423xx)
  uint32_t      RESERVED;     /*!< Reserved, 0x18                                                               */
  __IO uint32_t CFGR2;        /*!< Reserved, 0x1C                                                               */
  __IO uint32_t CMPCR;        /*!< SYSCFG_MORT Compensation cell control register,         Address offset: 0x20      */
  uint32_t      RESERVED1[2]; /*!< Reserved, 0x24-0x28                                                          */
  __IO uint32_t CFGR;         /*!< SYSCFG_MORT Configuration register,                     Address offset: 0x2C      */
#else  /* STM32F40_41xxx || STM32F427_437xx || STM32F429_439xx || STM32F401xx || STM32F411xE || STM32F446xx_MORT || STM32F469_479xx */
  uint32_t      RESERVED[2];  /*!< Reserved, 0x18-0x1C                                                          */ 
  __IO uint32_t CMPCR;        /*!< SYSCFG_MORT Compensation cell control register,         Address offset: 0x20      */
#endif /* STM32F410xx || defined(STM32F412xG) || defined(STM32F413_423xx) */
#if defined(STM32F413_423xx)
  __IO uint32_t MCHDLYCR;     /*!< SYSCFG_MORT multi-channel delay register,               Address offset: 0x30      */
#endif /* STM32F413_423xx */
} SYSCFG_TypeDef_mort;

/** 
  * @brief Inter-integrated Circuit Interface
  */

typedef struct
{
  __IO uint16_t CR1;        /*!< I2C Control register 1,     Address offset: 0x00 */
  uint16_t      RESERVED0;  /*!< Reserved, 0x02                                   */
  __IO uint16_t CR2;        /*!< I2C Control register 2,     Address offset: 0x04 */
  uint16_t      RESERVED1;  /*!< Reserved, 0x06                                   */
  __IO uint16_t OAR1;       /*!< I2C Own address register 1, Address offset: 0x08 */
  uint16_t      RESERVED2;  /*!< Reserved, 0x0A                                   */
  __IO uint16_t OAR2;       /*!< I2C Own address register 2, Address offset: 0x0C */
  uint16_t      RESERVED3;  /*!< Reserved, 0x0E                                   */
  __IO uint16_t DR;         /*!< I2C Data register,          Address offset: 0x10 */
  uint16_t      RESERVED4;  /*!< Reserved, 0x12                                   */
  __IO uint16_t SR1;        /*!< I2C Status register 1,      Address offset: 0x14 */
  uint16_t      RESERVED5;  /*!< Reserved, 0x16                                   */
  __IO uint16_t SR2;        /*!< I2C Status register 2,      Address offset: 0x18 */
  uint16_t      RESERVED6;  /*!< Reserved, 0x1A                                   */
  __IO uint16_t CCR;        /*!< I2C Clock control register, Address offset: 0x1C */
  uint16_t      RESERVED7;  /*!< Reserved, 0x1E                                   */
  __IO uint16_t TRISE;      /*!< I2C TRISE register,         Address offset: 0x20 */
  uint16_t      RESERVED8;  /*!< Reserved, 0x22                                   */
  __IO uint16_t FLTR;       /*!< I2C FLTR register,          Address offset: 0x24 */
  uint16_t      RESERVED9;  /*!< Reserved, 0x26                                   */
} I2C_TypeDef_mort;

#if defined(STM32F410xx) || defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F446xx_MORT) 
/**
  * @brief Inter-integrated Circuit Interface
  */

typedef struct
{
  __IO uint32_t CR1;      /*!< FMPI2C Control register 1,            Address offset: 0x00 */
  __IO uint32_t CR2;      /*!< FMPI2C Control register 2,            Address offset: 0x04 */
  __IO uint32_t OAR1;     /*!< FMPI2C Own address 1 register,        Address offset: 0x08 */
  __IO uint32_t OAR2;     /*!< FMPI2C Own address 2 register,        Address offset: 0x0C */
  __IO uint32_t TIMINGR;  /*!< FMPI2C Timing register,               Address offset: 0x10 */
  __IO uint32_t TIMEOUTR; /*!< FMPI2C Timeout register,              Address offset: 0x14 */
  __IO uint32_t ISR;      /*!< FMPI2C Interrupt and status register, Address offset: 0x18 */
  __IO uint32_t ICR;      /*!< FMPI2C Interrupt clear register,      Address offset: 0x1C */
  __IO uint32_t PECR;     /*!< FMPI2C PEC register,                  Address offset: 0x20 */
  __IO uint32_t RXDR;     /*!< FMPI2C Receive data register,         Address offset: 0x24 */
  __IO uint32_t TXDR;     /*!< FMPI2C Transmit data register,        Address offset: 0x28 */
}FMPI2C_TypeDef_mort;
#endif /* STM32F410xx || STM32F412xG || STM32F413_423xx || STM32F446xx_MORT */

/** 
  * @brief Independent WATCHDOG
  */

typedef struct
{
  __IO uint32_t KR;   /*!< IWDG_MORT Key register,       Address offset: 0x00 */
  __IO uint32_t PR;   /*!< IWDG_MORT Prescaler register, Address offset: 0x04 */
  __IO uint32_t RLR;  /*!< IWDG_MORT Reload register,    Address offset: 0x08 */
  __IO uint32_t SR;   /*!< IWDG_MORT Status register,    Address offset: 0x0C */
} IWDG_TypeDef_mort;

/** 
  * @brief LCD-TFT Display Controller
  */
  
typedef struct
{
  uint32_t      RESERVED0[2];  /*!< Reserved, 0x00-0x04 */
  __IO uint32_t SSCR;          /*!< LTDC_MORT Synchronization Size Configuration Register,    Address offset: 0x08 */
  __IO uint32_t BPCR;          /*!< LTDC_MORT Back Porch Configuration Register,              Address offset: 0x0C */
  __IO uint32_t AWCR;          /*!< LTDC_MORT Active Width Configuration Register,            Address offset: 0x10 */
  __IO uint32_t TWCR;          /*!< LTDC_MORT Total Width Configuration Register,             Address offset: 0x14 */
  __IO uint32_t GCR;           /*!< LTDC_MORT Global Control Register,                        Address offset: 0x18 */
  uint32_t      RESERVED1[2];  /*!< Reserved, 0x1C-0x20 */
  __IO uint32_t SRCR;          /*!< LTDC_MORT Shadow Reload Configuration Register,           Address offset: 0x24 */
  uint32_t      RESERVED2[1];  /*!< Reserved, 0x28 */
  __IO uint32_t BCCR;          /*!< LTDC_MORT Background Color Configuration Register,        Address offset: 0x2C */
  uint32_t      RESERVED3[1];  /*!< Reserved, 0x30 */
  __IO uint32_t IER;           /*!< LTDC_MORT Interrupt Enable Register,                      Address offset: 0x34 */
  __IO uint32_t ISR;           /*!< LTDC_MORT Interrupt Status Register,                      Address offset: 0x38 */
  __IO uint32_t ICR;           /*!< LTDC_MORT Interrupt Clear Register,                       Address offset: 0x3C */
  __IO uint32_t LIPCR;         /*!< LTDC_MORT Line Interrupt Position Configuration Register, Address offset: 0x40 */
  __IO uint32_t CPSR;          /*!< LTDC_MORT Current Position Status Register,               Address offset: 0x44 */
  __IO uint32_t CDSR;         /*!< LTDC_MORT Current Display Status Register,                       Address offset: 0x48 */
} LTDC_TypeDef_mort;  

/** 
  * @brief LCD-TFT Display layer x Controller
  */
  
typedef struct
{  
  __IO uint32_t CR;            /*!< LTDC_MORT Layerx Control Register                                  Address offset: 0x84 */
  __IO uint32_t WHPCR;         /*!< LTDC_MORT Layerx Window Horizontal Position Configuration Register Address offset: 0x88 */
  __IO uint32_t WVPCR;         /*!< LTDC_MORT Layerx Window Vertical Position Configuration Register   Address offset: 0x8C */
  __IO uint32_t CKCR;          /*!< LTDC_MORT Layerx Color Keying Configuration Register               Address offset: 0x90 */
  __IO uint32_t PFCR;          /*!< LTDC_MORT Layerx Pixel Format Configuration Register               Address offset: 0x94 */
  __IO uint32_t CACR;          /*!< LTDC_MORT Layerx Constant Alpha Configuration Register             Address offset: 0x98 */
  __IO uint32_t DCCR;          /*!< LTDC_MORT Layerx Default Color Configuration Register              Address offset: 0x9C */
  __IO uint32_t BFCR;          /*!< LTDC_MORT Layerx Blending Factors Configuration Register           Address offset: 0xA0 */
  uint32_t      RESERVED0[2];  /*!< Reserved */
  __IO uint32_t CFBAR;         /*!< LTDC_MORT Layerx Color Frame Buffer Address Register               Address offset: 0xAC */
  __IO uint32_t CFBLR;         /*!< LTDC_MORT Layerx Color Frame Buffer Length Register                Address offset: 0xB0 */
  __IO uint32_t CFBLNR;        /*!< LTDC_MORT Layerx ColorFrame Buffer Line Number Register            Address offset: 0xB4 */
  uint32_t      RESERVED1[3];  /*!< Reserved */
  __IO uint32_t CLUTWR;         /*!< LTDC_MORT Layerx CLUT Write Register                               Address offset: 0x144 */

} LTDC_Layer_TypeDef_mort;

/** 
  * @brief Power Control
  */

typedef struct
{
  __IO uint32_t CR;   /*!< PWR_MORT power control register,        Address offset: 0x00 */
  __IO uint32_t CSR;  /*!< PWR_MORT power control/status register, Address offset: 0x04 */
} PWR_TypeDef_mort;

/** 
  * @brief Reset and Clock Control
  */

typedef struct
{
  __IO uint32_t CR;            /*!< RCC_MORT clock control register,                                  Address offset: 0x00 */
  __IO uint32_t PLLCFGR;       /*!< RCC_MORT PLL configuration register,                              Address offset: 0x04 */
  __IO uint32_t CFGR;          /*!< RCC_MORT clock configuration register,                            Address offset: 0x08 */
  __IO uint32_t CIR;           /*!< RCC_MORT clock interrupt register,                                Address offset: 0x0C */
  __IO uint32_t AHB1RSTR;      /*!< RCC_MORT AHB1 peripheral reset register,                          Address offset: 0x10 */
  __IO uint32_t AHB2RSTR;      /*!< RCC_MORT AHB2 peripheral reset register,                          Address offset: 0x14 */
  __IO uint32_t AHB3RSTR;      /*!< RCC_MORT AHB3 peripheral reset register,                          Address offset: 0x18 */
  uint32_t      RESERVED0;     /*!< Reserved, 0x1C                                                                    */
  __IO uint32_t APB1RSTR;      /*!< RCC_MORT APB1 peripheral reset register,                          Address offset: 0x20 */
  __IO uint32_t APB2RSTR;      /*!< RCC_MORT APB2 peripheral reset register,                          Address offset: 0x24 */
  uint32_t      RESERVED1[2];  /*!< Reserved, 0x28-0x2C                                                               */
  __IO uint32_t AHB1ENR;       /*!< RCC_MORT AHB1 peripheral clock register,                          Address offset: 0x30 */
  __IO uint32_t AHB2ENR;       /*!< RCC_MORT AHB2 peripheral clock register,                          Address offset: 0x34 */
  __IO uint32_t AHB3ENR;       /*!< RCC_MORT AHB3 peripheral clock register,                          Address offset: 0x38 */
  uint32_t      RESERVED2;     /*!< Reserved, 0x3C                                                                    */
  __IO uint32_t APB1ENR;       /*!< RCC_MORT APB1 peripheral clock enable register,                   Address offset: 0x40 */
  __IO uint32_t APB2ENR;       /*!< RCC_MORT APB2 peripheral clock enable register,                   Address offset: 0x44 */
  uint32_t      RESERVED3[2];  /*!< Reserved, 0x48-0x4C                                                               */
  __IO uint32_t AHB1LPENR;     /*!< RCC_MORT AHB1 peripheral clock enable in low power mode register, Address offset: 0x50 */
  __IO uint32_t AHB2LPENR;     /*!< RCC_MORT AHB2 peripheral clock enable in low power mode register, Address offset: 0x54 */
  __IO uint32_t AHB3LPENR;     /*!< RCC_MORT AHB3 peripheral clock enable in low power mode register, Address offset: 0x58 */
  uint32_t      RESERVED4;     /*!< Reserved, 0x5C                                                                    */
  __IO uint32_t APB1LPENR;     /*!< RCC_MORT APB1 peripheral clock enable in low power mode register, Address offset: 0x60 */
  __IO uint32_t APB2LPENR;     /*!< RCC_MORT APB2 peripheral clock enable in low power mode register, Address offset: 0x64 */
  uint32_t      RESERVED5[2];  /*!< Reserved, 0x68-0x6C                                                               */
  __IO uint32_t BDCR;          /*!< RCC_MORT Backup domain control register,                          Address offset: 0x70 */
  __IO uint32_t CSR;           /*!< RCC_MORT clock control & status register,                         Address offset: 0x74 */
  uint32_t      RESERVED6[2];  /*!< Reserved, 0x78-0x7C                                                               */
  __IO uint32_t SSCGR;         /*!< RCC_MORT spread spectrum clock generation register,               Address offset: 0x80 */
  __IO uint32_t PLLI2SCFGR;    /*!< RCC_MORT PLLI2S configuration register,                           Address offset: 0x84 */
  __IO uint32_t PLLSAICFGR;    /*!< RCC_MORT PLLSAI configuration register,                           Address offset: 0x88 */
  __IO uint32_t DCKCFGR;       /*!< RCC_MORT Dedicated Clocks configuration register,                 Address offset: 0x8C */
  __IO uint32_t CKGATENR;      /*!< RCC_MORT Clocks Gated Enable Register,                            Address offset: 0x90 */ /* Only for STM32F412xG, STM32413_423xx and STM32F446xx_MORT devices */
  __IO uint32_t DCKCFGR2;      /*!< RCC_MORT Dedicated Clocks configuration register 2,               Address offset: 0x94 */ /* Only for STM32F410xx, STM32F412xG, STM32413_423xx and STM32F446xx_MORT devices */

} RCC_TypeDef_mort;

/** 
  * @brief Real-Time Clock
  */

typedef struct
{
  __IO uint32_t TR;      /*!< RTC_MORT time register,                                        Address offset: 0x00 */
  __IO uint32_t DR;      /*!< RTC_MORT date register,                                        Address offset: 0x04 */
  __IO uint32_t CR;      /*!< RTC_MORT control register,                                     Address offset: 0x08 */
  __IO uint32_t ISR;     /*!< RTC_MORT initialization and status register,                   Address offset: 0x0C */
  __IO uint32_t PRER;    /*!< RTC_MORT prescaler register,                                   Address offset: 0x10 */
  __IO uint32_t WUTR;    /*!< RTC_MORT wakeup timer register,                                Address offset: 0x14 */
  __IO uint32_t CALIBR;  /*!< RTC_MORT calibration register,                                 Address offset: 0x18 */
  __IO uint32_t ALRMAR;  /*!< RTC_MORT alarm A register,                                     Address offset: 0x1C */
  __IO uint32_t ALRMBR;  /*!< RTC_MORT alarm B register,                                     Address offset: 0x20 */
  __IO uint32_t WPR;     /*!< RTC_MORT write protection register,                            Address offset: 0x24 */
  __IO uint32_t SSR;     /*!< RTC_MORT sub second register,                                  Address offset: 0x28 */
  __IO uint32_t SHIFTR;  /*!< RTC_MORT shift control register,                               Address offset: 0x2C */
  __IO uint32_t TSTR;    /*!< RTC_MORT time stamp time register,                             Address offset: 0x30 */
  __IO uint32_t TSDR;    /*!< RTC_MORT time stamp date register,                             Address offset: 0x34 */
  __IO uint32_t TSSSR;   /*!< RTC_MORT time-stamp sub second register,                       Address offset: 0x38 */
  __IO uint32_t CALR;    /*!< RTC_MORT calibration register,                                 Address offset: 0x3C */
  __IO uint32_t TAFCR;   /*!< RTC_MORT tamper and alternate function configuration register, Address offset: 0x40 */
  __IO uint32_t ALRMASSR;/*!< RTC_MORT alarm A sub second register,                          Address offset: 0x44 */
  __IO uint32_t ALRMBSSR;/*!< RTC_MORT alarm B sub second register,                          Address offset: 0x48 */
  uint32_t RESERVED7;    /*!< Reserved, 0x4C                                                                 */
  __IO uint32_t BKP0R;   /*!< RTC_MORT backup register 1,                                    Address offset: 0x50 */
  __IO uint32_t BKP1R;   /*!< RTC_MORT backup register 1,                                    Address offset: 0x54 */
  __IO uint32_t BKP2R;   /*!< RTC_MORT backup register 2,                                    Address offset: 0x58 */
  __IO uint32_t BKP3R;   /*!< RTC_MORT backup register 3,                                    Address offset: 0x5C */
  __IO uint32_t BKP4R;   /*!< RTC_MORT backup register 4,                                    Address offset: 0x60 */
  __IO uint32_t BKP5R;   /*!< RTC_MORT backup register 5,                                    Address offset: 0x64 */
  __IO uint32_t BKP6R;   /*!< RTC_MORT backup register 6,                                    Address offset: 0x68 */
  __IO uint32_t BKP7R;   /*!< RTC_MORT backup register 7,                                    Address offset: 0x6C */
  __IO uint32_t BKP8R;   /*!< RTC_MORT backup register 8,                                    Address offset: 0x70 */
  __IO uint32_t BKP9R;   /*!< RTC_MORT backup register 9,                                    Address offset: 0x74 */
  __IO uint32_t BKP10R;  /*!< RTC_MORT backup register 10,                                   Address offset: 0x78 */
  __IO uint32_t BKP11R;  /*!< RTC_MORT backup register 11,                                   Address offset: 0x7C */
  __IO uint32_t BKP12R;  /*!< RTC_MORT backup register 12,                                   Address offset: 0x80 */
  __IO uint32_t BKP13R;  /*!< RTC_MORT backup register 13,                                   Address offset: 0x84 */
  __IO uint32_t BKP14R;  /*!< RTC_MORT backup register 14,                                   Address offset: 0x88 */
  __IO uint32_t BKP15R;  /*!< RTC_MORT backup register 15,                                   Address offset: 0x8C */
  __IO uint32_t BKP16R;  /*!< RTC_MORT backup register 16,                                   Address offset: 0x90 */
  __IO uint32_t BKP17R;  /*!< RTC_MORT backup register 17,                                   Address offset: 0x94 */
  __IO uint32_t BKP18R;  /*!< RTC_MORT backup register 18,                                   Address offset: 0x98 */
  __IO uint32_t BKP19R;  /*!< RTC_MORT backup register 19,                                   Address offset: 0x9C */
} RTC_TypeDef_mort;


/** 
  * @brief Serial Audio Interface
  */
  
typedef struct
{
  __IO uint32_t GCR;      /*!< SAI global configuration register,        Address offset: 0x00 */
} SAI_TypeDef_mort;

typedef struct
{
  __IO uint32_t CR1;      /*!< SAI block x configuration register 1,     Address offset: 0x04 */
  __IO uint32_t CR2;      /*!< SAI block x configuration register 2,     Address offset: 0x08 */
  __IO uint32_t FRCR;     /*!< SAI block x frame configuration register, Address offset: 0x0C */
  __IO uint32_t SLOTR;    /*!< SAI block x slot register,                Address offset: 0x10 */
  __IO uint32_t IMR;      /*!< SAI block x interrupt mask register,      Address offset: 0x14 */
  __IO uint32_t SR;       /*!< SAI block x status register,              Address offset: 0x18 */
  __IO uint32_t CLRFR;    /*!< SAI block x clear flag register,          Address offset: 0x1C */
  __IO uint32_t DR;       /*!< SAI block x data register,                Address offset: 0x20 */
} SAI_Block_TypeDef_mort;

/** 
  * @brief SD host Interface
  */

typedef struct
{
  __IO uint32_t POWER;          /*!< SDIO_MORT power control register,    Address offset: 0x00 */
  __IO uint32_t CLKCR;          /*!< SDI clock control register,     Address offset: 0x04 */
  __IO uint32_t ARG;            /*!< SDIO_MORT argument register,         Address offset: 0x08 */
  __IO uint32_t CMD;            /*!< SDIO_MORT command register,          Address offset: 0x0C */
  __I uint32_t  RESPCMD;        /*!< SDIO_MORT command response register, Address offset: 0x10 */
  __I uint32_t  RESP1;          /*!< SDIO_MORT response 1 register,       Address offset: 0x14 */
  __I uint32_t  RESP2;          /*!< SDIO_MORT response 2 register,       Address offset: 0x18 */
  __I uint32_t  RESP3;          /*!< SDIO_MORT response 3 register,       Address offset: 0x1C */
  __I uint32_t  RESP4;          /*!< SDIO_MORT response 4 register,       Address offset: 0x20 */
  __IO uint32_t DTIMER;         /*!< SDIO_MORT data timer register,       Address offset: 0x24 */
  __IO uint32_t DLEN;           /*!< SDIO_MORT data length register,      Address offset: 0x28 */
  __IO uint32_t DCTRL;          /*!< SDIO_MORT data control register,     Address offset: 0x2C */
  __I uint32_t  DCOUNT;         /*!< SDIO_MORT data counter register,     Address offset: 0x30 */
  __I uint32_t  STA;            /*!< SDIO_MORT status register,           Address offset: 0x34 */
  __IO uint32_t ICR;            /*!< SDIO_MORT interrupt clear register,  Address offset: 0x38 */
  __IO uint32_t MASK;           /*!< SDIO_MORT mask register,             Address offset: 0x3C */
  uint32_t      RESERVED0[2];   /*!< Reserved, 0x40-0x44                                  */
  __I uint32_t  FIFOCNT;        /*!< SDIO_MORT FIFO counter register,     Address offset: 0x48 */
  uint32_t      RESERVED1[13];  /*!< Reserved, 0x4C-0x7C                                  */
  __IO uint32_t FIFO;           /*!< SDIO_MORT data FIFO register,        Address offset: 0x80 */
} SDIO_TypeDef_mort;

/** 
  * @brief Serial Peripheral Interface
  */

typedef struct
{
  __IO uint16_t CR1;        /*!< SPI control register 1 (not used in I2S mode),      Address offset: 0x00 */
  uint16_t      RESERVED0;  /*!< Reserved, 0x02                                                           */
  __IO uint16_t CR2;        /*!< SPI control register 2,                             Address offset: 0x04 */
  uint16_t      RESERVED1;  /*!< Reserved, 0x06                                                           */
  __IO uint16_t SR;         /*!< SPI status register,                                Address offset: 0x08 */
  uint16_t      RESERVED2;  /*!< Reserved, 0x0A                                                           */
  __IO uint16_t DR;         /*!< SPI data register,                                  Address offset: 0x0C */
  uint16_t      RESERVED3;  /*!< Reserved, 0x0E                                                           */
  __IO uint16_t CRCPR;      /*!< SPI CRC_MORT polynomial register (not used in I2S mode), Address offset: 0x10 */
  uint16_t      RESERVED4;  /*!< Reserved, 0x12                                                           */
  __IO uint16_t RXCRCR;     /*!< SPI RX CRC_MORT register (not used in I2S mode),         Address offset: 0x14 */
  uint16_t      RESERVED5;  /*!< Reserved, 0x16                                                           */
  __IO uint16_t TXCRCR;     /*!< SPI TX CRC_MORT register (not used in I2S mode),         Address offset: 0x18 */
  uint16_t      RESERVED6;  /*!< Reserved, 0x1A                                                           */
  __IO uint16_t I2SCFGR;    /*!< SPI_I2S configuration register,                     Address offset: 0x1C */
  uint16_t      RESERVED7;  /*!< Reserved, 0x1E                                                           */
  __IO uint16_t I2SPR;      /*!< SPI_I2S prescaler register,                         Address offset: 0x20 */
  uint16_t      RESERVED8;  /*!< Reserved, 0x22                                                           */
} SPI_TypeDef_mort;

#if defined(STM32F446xx_MORT)
/** 
  * @brief SPDIFRX_MORT Interface
  */
typedef struct
{
  __IO uint32_t   CR;           /*!< Control register,                   Address offset: 0x00 */
  __IO uint16_t   IMR;          /*!< Interrupt mask register,            Address offset: 0x04 */
  uint16_t        RESERVED0;    /*!< Reserved,  0x06                                          */  
  __IO uint32_t   SR;           /*!< Status register,                    Address offset: 0x08 */
  __IO uint16_t   IFCR;         /*!< Interrupt Flag Clear register,      Address offset: 0x0C */
  uint16_t        RESERVED1;    /*!< Reserved,  0x0E                                          */   
  __IO uint32_t   DR;           /*!< Data input register,                Address offset: 0x10 */
  __IO uint32_t   CSR;          /*!< Channel Status register,            Address offset: 0x14 */
   __IO uint32_t  DIR;          /*!< Debug Information register,         Address offset: 0x18 */
  uint16_t        RESERVED2;    /*!< Reserved,  0x1A                                          */   
} SPDIFRX_TypeDef_mort;
#endif /* STM32F446xx_MORT */

#if defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F446xx_MORT) || defined(STM32F469_479xx)
/** 
  * @brief QUAD Serial Peripheral Interface
  */
typedef struct
{
  __IO uint32_t CR;       /*!< QUADSPI_MORT Control register,                           Address offset: 0x00 */
  __IO uint32_t DCR;      /*!< QUADSPI_MORT Device Configuration register,              Address offset: 0x04 */
  __IO uint32_t SR;       /*!< QUADSPI_MORT Status register,                            Address offset: 0x08 */
  __IO uint32_t FCR;      /*!< QUADSPI_MORT Flag Clear register,                        Address offset: 0x0C */
  __IO uint32_t DLR;      /*!< QUADSPI_MORT Data Length register,                       Address offset: 0x10 */
  __IO uint32_t CCR;      /*!< QUADSPI_MORT Communication Configuration register,       Address offset: 0x14 */
  __IO uint32_t AR;       /*!< QUADSPI_MORT Address register,                           Address offset: 0x18 */
  __IO uint32_t ABR;      /*!< QUADSPI_MORT Alternate Bytes register,                   Address offset: 0x1C */
  __IO uint32_t DR;       /*!< QUADSPI_MORT Data register,                              Address offset: 0x20 */
  __IO uint32_t PSMKR;    /*!< QUADSPI_MORT Polling Status Mask register,               Address offset: 0x24 */
  __IO uint32_t PSMAR;    /*!< QUADSPI_MORT Polling Status Match register,              Address offset: 0x28 */
  __IO uint32_t PIR;      /*!< QUADSPI_MORT Polling Interval register,                  Address offset: 0x2C */
  __IO uint32_t LPTR;     /*!< QUADSPI_MORT Low Power Timeout register,                 Address offset: 0x30 */
} QUADSPI_TypeDef_mort;
#endif /* STM32F412xG || STM32F413_423xx || STM32F446xx_MORT || STM32F469_479xx */

#if defined(STM32F446xx_MORT)
/** 
  * @brief SPDIF-RX Interface
  */
typedef struct
{
  __IO uint32_t   CR;           /*!< Control register,                   Address offset: 0x00 */
  __IO uint16_t   IMR;          /*!< Interrupt mask register,            Address offset: 0x04 */
  uint16_t        RESERVED0;    /*!< Reserved,  0x06                                          */  
  __IO uint32_t   SR;           /*!< Status register,                    Address offset: 0x08 */
  __IO uint16_t   IFCR;         /*!< Interrupt Flag Clear register,      Address offset: 0x0C */
  uint16_t        RESERVED1;    /*!< Reserved,  0x0E                                          */   
  __IO uint32_t   DR;           /*!< Data input register,                Address offset: 0x10 */
  __IO uint32_t   CSR;          /*!< Channel Status register,            Address offset: 0x14 */
   __IO uint32_t  DIR;          /*!< Debug Information register,         Address offset: 0x18 */
  uint16_t        RESERVED2;    /*!< Reserved,  0x1A                                          */   
} SPDIF_TypeDef_mort;
#endif /* STM32F446xx_MORT */

/** 
  * @brief TIM
  */

typedef struct
{
  __IO uint16_t CR1;         /*!< TIM control register 1,              Address offset: 0x00 */
  uint16_t      RESERVED0;   /*!< Reserved, 0x02                                            */
  __IO uint16_t CR2;         /*!< TIM control register 2,              Address offset: 0x04 */
  uint16_t      RESERVED1;   /*!< Reserved, 0x06                                            */
  __IO uint16_t SMCR;        /*!< TIM slave mode control register,     Address offset: 0x08 */
  uint16_t      RESERVED2;   /*!< Reserved, 0x0A                                            */
  __IO uint16_t DIER;        /*!< TIM DMA/interrupt enable register,   Address offset: 0x0C */
  uint16_t      RESERVED3;   /*!< Reserved, 0x0E                                            */
  __IO uint16_t SR;          /*!< TIM status register,                 Address offset: 0x10 */
  uint16_t      RESERVED4;   /*!< Reserved, 0x12                                            */
  __IO uint16_t EGR;         /*!< TIM event generation register,       Address offset: 0x14 */
  uint16_t      RESERVED5;   /*!< Reserved, 0x16                                            */
  __IO uint16_t CCMR1;       /*!< TIM capture/compare mode register 1, Address offset: 0x18 */
  uint16_t      RESERVED6;   /*!< Reserved, 0x1A                                            */
  __IO uint16_t CCMR2;       /*!< TIM capture/compare mode register 2, Address offset: 0x1C */
  uint16_t      RESERVED7;   /*!< Reserved, 0x1E                                            */
  __IO uint16_t CCER;        /*!< TIM capture/compare enable register, Address offset: 0x20 */
  uint16_t      RESERVED8;   /*!< Reserved, 0x22                                            */
  __IO uint32_t CNT;         /*!< TIM counter register,                Address offset: 0x24 */
  __IO uint16_t PSC;         /*!< TIM prescaler,                       Address offset: 0x28 */
  uint16_t      RESERVED9;   /*!< Reserved, 0x2A                                            */
  __IO uint32_t ARR;         /*!< TIM auto-reload register,            Address offset: 0x2C */
  __IO uint16_t RCR;         /*!< TIM repetition counter register,     Address offset: 0x30 */
  uint16_t      RESERVED10;  /*!< Reserved, 0x32                                            */
  __IO uint32_t CCR1;        /*!< TIM capture/compare register 1,      Address offset: 0x34 */
  __IO uint32_t CCR2;        /*!< TIM capture/compare register 2,      Address offset: 0x38 */
  __IO uint32_t CCR3;        /*!< TIM capture/compare register 3,      Address offset: 0x3C */
  __IO uint32_t CCR4;        /*!< TIM capture/compare register 4,      Address offset: 0x40 */
  __IO uint16_t BDTR;        /*!< TIM break and dead-time register,    Address offset: 0x44 */
  uint16_t      RESERVED11;  /*!< Reserved, 0x46                                            */
  __IO uint16_t DCR;         /*!< TIM DMA control register,            Address offset: 0x48 */
  uint16_t      RESERVED12;  /*!< Reserved, 0x4A                                            */
  __IO uint16_t DMAR;        /*!< TIM DMA address for full transfer,   Address offset: 0x4C */
  uint16_t      RESERVED13;  /*!< Reserved, 0x4E                                            */
  __IO uint16_t OR;          /*!< TIM option register,                 Address offset: 0x50 */
  uint16_t      RESERVED14;  /*!< Reserved, 0x52                                            */
} TIM_TypeDef_mort;

/** 
  * @brief Universal Synchronous Asynchronous Receiver Transmitter
  */
 
typedef struct
{
  __IO uint16_t SR;         /*!< USART Status register,                   Address offset: 0x00 */
  uint16_t      RESERVED0;  /*!< Reserved, 0x02                                                */
  __IO uint16_t DR;         /*!< USART Data register,                     Address offset: 0x04 */
  uint16_t      RESERVED1;  /*!< Reserved, 0x06                                                */
  __IO uint16_t BRR;        /*!< USART Baud rate register,                Address offset: 0x08 */
  uint16_t      RESERVED2;  /*!< Reserved, 0x0A                                                */
  __IO uint16_t CR1;        /*!< USART Control register 1,                Address offset: 0x0C */
  uint16_t      RESERVED3;  /*!< Reserved, 0x0E                                                */
  __IO uint16_t CR2;        /*!< USART Control register 2,                Address offset: 0x10 */
  uint16_t      RESERVED4;  /*!< Reserved, 0x12                                                */
  __IO uint16_t CR3;        /*!< USART Control register 3,                Address offset: 0x14 */
  uint16_t      RESERVED5;  /*!< Reserved, 0x16                                                */
  __IO uint16_t GTPR;       /*!< USART Guard time and prescaler register, Address offset: 0x18 */
  uint16_t      RESERVED6;  /*!< Reserved, 0x1A                                                */
} USART_TypeDef_mort;

/** 
  * @brief Window WATCHDOG
  */

typedef struct
{
  __IO uint32_t CR;   /*!< WWDG_MORT Control register,       Address offset: 0x00 */
  __IO uint32_t CFR;  /*!< WWDG_MORT Configuration register, Address offset: 0x04 */
  __IO uint32_t SR;   /*!< WWDG_MORT Status register,        Address offset: 0x08 */
} WWDG_TypeDef_mort;

/** 
  * @brief Crypto Processor
  */

typedef struct
{
  __IO uint32_t CR;         /*!< CRYP_MORT control register,                                    Address offset: 0x00 */
  __IO uint32_t SR;         /*!< CRYP_MORT status register,                                     Address offset: 0x04 */
  __IO uint32_t DR;         /*!< CRYP_MORT data input register,                                 Address offset: 0x08 */
  __IO uint32_t DOUT;       /*!< CRYP_MORT data output register,                                Address offset: 0x0C */
  __IO uint32_t DMACR;      /*!< CRYP_MORT DMA control register,                                Address offset: 0x10 */
  __IO uint32_t IMSCR;      /*!< CRYP_MORT interrupt mask set/clear register,                   Address offset: 0x14 */
  __IO uint32_t RISR;       /*!< CRYP_MORT raw interrupt status register,                       Address offset: 0x18 */
  __IO uint32_t MISR;       /*!< CRYP_MORT masked interrupt status register,                    Address offset: 0x1C */
  __IO uint32_t K0LR;       /*!< CRYP_MORT key left  register 0,                                Address offset: 0x20 */
  __IO uint32_t K0RR;       /*!< CRYP_MORT key right register 0,                                Address offset: 0x24 */
  __IO uint32_t K1LR;       /*!< CRYP_MORT key left  register 1,                                Address offset: 0x28 */
  __IO uint32_t K1RR;       /*!< CRYP_MORT key right register 1,                                Address offset: 0x2C */
  __IO uint32_t K2LR;       /*!< CRYP_MORT key left  register 2,                                Address offset: 0x30 */
  __IO uint32_t K2RR;       /*!< CRYP_MORT key right register 2,                                Address offset: 0x34 */
  __IO uint32_t K3LR;       /*!< CRYP_MORT key left  register 3,                                Address offset: 0x38 */
  __IO uint32_t K3RR;       /*!< CRYP_MORT key right register 3,                                Address offset: 0x3C */
  __IO uint32_t IV0LR;      /*!< CRYP_MORT initialization vector left-word  register 0,         Address offset: 0x40 */
  __IO uint32_t IV0RR;      /*!< CRYP_MORT initialization vector right-word register 0,         Address offset: 0x44 */
  __IO uint32_t IV1LR;      /*!< CRYP_MORT initialization vector left-word  register 1,         Address offset: 0x48 */
  __IO uint32_t IV1RR;      /*!< CRYP_MORT initialization vector right-word register 1,         Address offset: 0x4C */
  __IO uint32_t CSGCMCCM0R; /*!< CRYP_MORT GCM/GMAC or CCM/CMAC context swap register 0,        Address offset: 0x50 */
  __IO uint32_t CSGCMCCM1R; /*!< CRYP_MORT GCM/GMAC or CCM/CMAC context swap register 1,        Address offset: 0x54 */
  __IO uint32_t CSGCMCCM2R; /*!< CRYP_MORT GCM/GMAC or CCM/CMAC context swap register 2,        Address offset: 0x58 */
  __IO uint32_t CSGCMCCM3R; /*!< CRYP_MORT GCM/GMAC or CCM/CMAC context swap register 3,        Address offset: 0x5C */
  __IO uint32_t CSGCMCCM4R; /*!< CRYP_MORT GCM/GMAC or CCM/CMAC context swap register 4,        Address offset: 0x60 */
  __IO uint32_t CSGCMCCM5R; /*!< CRYP_MORT GCM/GMAC or CCM/CMAC context swap register 5,        Address offset: 0x64 */
  __IO uint32_t CSGCMCCM6R; /*!< CRYP_MORT GCM/GMAC or CCM/CMAC context swap register 6,        Address offset: 0x68 */
  __IO uint32_t CSGCMCCM7R; /*!< CRYP_MORT GCM/GMAC or CCM/CMAC context swap register 7,        Address offset: 0x6C */
  __IO uint32_t CSGCM0R;    /*!< CRYP_MORT GCM/GMAC context swap register 0,                    Address offset: 0x70 */
  __IO uint32_t CSGCM1R;    /*!< CRYP_MORT GCM/GMAC context swap register 1,                    Address offset: 0x74 */
  __IO uint32_t CSGCM2R;    /*!< CRYP_MORT GCM/GMAC context swap register 2,                    Address offset: 0x78 */
  __IO uint32_t CSGCM3R;    /*!< CRYP_MORT GCM/GMAC context swap register 3,                    Address offset: 0x7C */
  __IO uint32_t CSGCM4R;    /*!< CRYP_MORT GCM/GMAC context swap register 4,                    Address offset: 0x80 */
  __IO uint32_t CSGCM5R;    /*!< CRYP_MORT GCM/GMAC context swap register 5,                    Address offset: 0x84 */
  __IO uint32_t CSGCM6R;    /*!< CRYP_MORT GCM/GMAC context swap register 6,                    Address offset: 0x88 */
  __IO uint32_t CSGCM7R;    /*!< CRYP_MORT GCM/GMAC context swap register 7,                    Address offset: 0x8C */
} CRYP_TypeDef_mort;

/** 
  * @brief HASH_MORT
  */
  
typedef struct 
{
  __IO uint32_t CR;               /*!< HASH_MORT control register,          Address offset: 0x00        */
  __IO uint32_t DIN;              /*!< HASH_MORT data input register,       Address offset: 0x04        */
  __IO uint32_t STR;              /*!< HASH_MORT start register,            Address offset: 0x08        */
  __IO uint32_t HR[5];            /*!< HASH_MORT digest registers,          Address offset: 0x0C-0x1C   */
  __IO uint32_t IMR;              /*!< HASH_MORT interrupt enable register, Address offset: 0x20        */
  __IO uint32_t SR;               /*!< HASH_MORT status register,           Address offset: 0x24        */
       uint32_t RESERVED[52];     /*!< Reserved, 0x28-0xF4                                         */
  __IO uint32_t CSR[54];          /*!< HASH_MORT context swap registers,    Address offset: 0x0F8-0x1CC */
} HASH_TypeDef_mort;

/** 
  * @brief HASH_DIGEST_MORT
  */
  
typedef struct 
{
  __IO uint32_t HR[8];     /*!< HASH_MORT digest registers,          Address offset: 0x310-0x32C */ 
} HASH_DIGEST_TypeDef_mort;

/** 
  * @brief RNG_MORT
  */
  
typedef struct 
{
  __IO uint32_t CR;  /*!< RNG_MORT control register, Address offset: 0x00 */
  __IO uint32_t SR;  /*!< RNG_MORT status register,  Address offset: 0x04 */
  __IO uint32_t DR;  /*!< RNG_MORT data register,    Address offset: 0x08 */
} RNG_TypeDef_mort;

#if defined(STM32F410xx) || defined(STM32F413_423xx)
/**
  * @brief LPTIMER
  */
typedef struct
{
  __IO uint32_t ISR;         /*!< LPTIM Interrupt and Status register,                Address offset: 0x00 */
  __IO uint32_t ICR;         /*!< LPTIM Interrupt Clear register,                     Address offset: 0x04 */
  __IO uint32_t IER;         /*!< LPTIM Interrupt Enable register,                    Address offset: 0x08 */
  __IO uint32_t CFGR;        /*!< LPTIM Configuration register,                       Address offset: 0x0C */
  __IO uint32_t CR;          /*!< LPTIM Control register,                             Address offset: 0x10 */
  __IO uint32_t CMP;         /*!< LPTIM Compare register,                             Address offset: 0x14 */
  __IO uint32_t ARR;         /*!< LPTIM Autoreload register,                          Address offset: 0x18 */
  __IO uint32_t CNT;         /*!< LPTIM Counter register,                             Address offset: 0x1C */
  __IO uint32_t OR;          /*!< LPTIM Option register,                              Address offset: 0x20 */
} LPTIM_TypeDef_mort;
#endif /* STM32F410xx || STM32F413_423xx */
/**
  * @}
  */
  
/** @addtogroup Peripheral_memory_map
  * @{
  */

#define FLASH_BASE_MORT            ((uint32_t)0x08000000) /*!< FLASH_MORT(up to 1 MB) base address in the alias region                         */
#define CCMDATARAM_BASE_MORT       ((uint32_t)0x10000000) /*!< CCM(core coupled memory) data RAM(64 KB) base address in the alias region  */
#define SRAM1_BASE_MORT            ((uint32_t)0x20000000) /*!< SRAM1(112 KB) base address in the alias region                             */
#if defined(STM32F40_41xxx) || defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F446xx_MORT) 
#define SRAM2_BASE_MORT            ((uint32_t)0x2001C000) /*!< SRAM2(16 KB) base address in the alias region                              */
#define SRAM3_BASE_MORT            ((uint32_t)0x20020000) /*!< SRAM3(64 KB) base address in the alias region                              */
#elif defined(STM32F469_479xx)
#define SRAM2_BASE_MORT            ((uint32_t)0x20028000) /*!< SRAM2(16 KB) base address in the alias region                              */
#define SRAM3_BASE_MORT            ((uint32_t)0x20030000) /*!< SRAM3(64 KB) base address in the alias region                              */
#elif defined(STM32F413_423xx)
#define SRAM2_BASE_MORT            ((uint32_t)0x20040000) /*!< SRAM2(16 KB) base address in the alias region                              */
#else /* STM32F411xE || STM32F410xx || STM32F412xG */
#endif /* STM32F40_41xxx || STM32F427_437xx || STM32F429_439xx ||  STM32F446xx_MORT */
#define PERIPH_BASE_MORT           ((uint32_t)0x40000000) /*!< Peripheral base address in the alias region                                */
#define BKPSRAM_BASE_MORT          ((uint32_t)0x40024000) /*!< Backup SRAM(4 KB) base address in the alias region                         */
      
#if defined(STM32F40_41xxx) || defined(STM32F412xG) || defined(STM32F413_423xx)
#define FSMC_R_BASE_MORT           ((uint32_t)0xA0000000) /*!< FSMC registers base address                                                */
#endif /* STM32F40_41xxx || STM32F412xG || STM32F413_423xx */

#if defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F446xx_MORT) || defined(STM32F469_479xx)
#define FMC_R_BASE_MORT            ((uint32_t)0xA0000000) /*!< FMC registers base address                                                 */
#endif /* STM32F427_437xx ||  STM32F429_439xx || STM32F446xx_MORT || STM32F469_479xx */

#if defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F446xx_MORT) || defined(STM32F469_479xx)
#define QSPI_R_BASE_MORT           ((uint32_t)0xA0001000) /*!< QUADSPI_MORT registers base address                                            */
#endif /* STM32F412xG || STM32F413_423xx || STM32F446xx_MORT || STM32F469_479xx */

#define CCMDATARAM_BB_BASE    ((uint32_t)0x12000000) /*!< CCM(core coupled memory) data RAM(64 KB) base address in the bit-band region  */
#define SRAM1_BB_BASE_MORT         ((uint32_t)0x22000000) /*!< SRAM1(112 KB) base address in the bit-band region                             */
#if defined(STM32F40_41xxx) || defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F446xx_MORT)
#define SRAM2_BB_BASE_MORT         ((uint32_t)0x22380000) /*!< SRAM2(16 KB) base address in the bit-band region                              */
#define SRAM3_BB_BASE_MORT         ((uint32_t)0x22400000) /*!< SRAM3(64 KB) base address in the bit-band region                              */
#elif defined(STM32F469_479xx)
#define SRAM2_BB_BASE_MORT         ((uint32_t)0x22500000) /*!< SRAM2(16 KB) base address in the bit-band region                              */
#define SRAM3_BB_BASE_MORT         ((uint32_t)0x22600000) /*!< SRAM3(64 KB) base address in the bit-band region                              */
#elif defined(STM32F413_423xx)
#define SRAM2_BB_BASE_MORT         ((uint32_t)0x22800000) /*!< SRAM2(64 KB) base address in the bit-band region                              */   
#else /* STM32F411xE || STM32F410xx || STM32F412xG */
#endif /* STM32F40_41xxx || STM32F427_437xx || STM32F429_439xx ||  STM32F446xx_MORT */
#define PERIPH_BB_BASE_MORT        ((uint32_t)0x42000000) /*!< Peripheral base address in the bit-band region                                */
#define BKPSRAM_BB_BASE_MORT       ((uint32_t)0x42480000) /*!< Backup SRAM(4 KB) base address in the bit-band region                         */

/* Legacy defines */
#define SRAM_BASE_MORT             SRAM1_BASE_MORT
#define SRAM_BB_BASE_MORT          SRAM1_BB_BASE_MORT


/*!< Peripheral memory map */
#define APB1PERIPH_BASE_MORT       PERIPH_BASE_MORT
#define APB2PERIPH_BASE_MORT       (PERIPH_BASE_MORT + 0x00010000)
#define AHB1PERIPH_BASE_MORT       (PERIPH_BASE_MORT + 0x00020000)
#define AHB2PERIPH_BASE_MORT       (PERIPH_BASE_MORT + 0x10000000)

/*!< APB1 peripherals */
#define TIM2_BASE_MORT             (APB1PERIPH_BASE_MORT + 0x0000)
#define TIM3_BASE_MORT             (APB1PERIPH_BASE_MORT + 0x0400)
#define TIM4_BASE_MORT             (APB1PERIPH_BASE_MORT + 0x0800)
#define TIM5_BASE_MORT             (APB1PERIPH_BASE_MORT + 0x0C00)
#define TIM6_BASE_MORT             (APB1PERIPH_BASE_MORT + 0x1000)
#define TIM7_BASE_MORT             (APB1PERIPH_BASE_MORT + 0x1400)
#if defined(STM32F410xx) || defined(STM32F413_423xx)
#define LPTIM1_BASE_MORT           (APB1PERIPH_BASE_MORT + 0x2400)
#endif /* STM32F410xx || STM32F413_423xx */
#define TIM12_BASE_MORT            (APB1PERIPH_BASE_MORT + 0x1800)
#define TIM13_BASE_MORT            (APB1PERIPH_BASE_MORT + 0x1C00)
#define TIM14_BASE_MORT            (APB1PERIPH_BASE_MORT + 0x2000)
#define RTC_BASE_MORT              (APB1PERIPH_BASE_MORT + 0x2800)
#define WWDG_BASE_MORT             (APB1PERIPH_BASE_MORT + 0x2C00)
#define IWDG_BASE_MORT             (APB1PERIPH_BASE_MORT + 0x3000)
#define I2S2ext_BASE_MORT          (APB1PERIPH_BASE_MORT + 0x3400)
#define SPI2_BASE_MORT             (APB1PERIPH_BASE_MORT + 0x3800)
#define SPI3_BASE_MORT             (APB1PERIPH_BASE_MORT + 0x3C00)
#if defined(STM32F446xx_MORT)                              
#define SPDIFRX_BASE_MORT          (APB1PERIPH_BASE_MORT + 0x4000)
#endif /* STM32F446xx_MORT */
#define I2S3ext_BASE_MORT          (APB1PERIPH_BASE_MORT + 0x4000)
#define USART2_BASE_MORT           (APB1PERIPH_BASE_MORT + 0x4400)
#define USART3_BASE_MORT           (APB1PERIPH_BASE_MORT + 0x4800)
#define UART4_BASE_MORT            (APB1PERIPH_BASE_MORT + 0x4C00)
#define UART5_BASE_MORT            (APB1PERIPH_BASE_MORT + 0x5000)
#define I2C1_BASE_MORT             (APB1PERIPH_BASE_MORT + 0x5400)
#define I2C2_BASE_MORT             (APB1PERIPH_BASE_MORT + 0x5800)
#define I2C3_BASE_MORT             (APB1PERIPH_BASE_MORT + 0x5C00)
#if defined(STM32F410xx) || defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F446xx_MORT)
#define FMPI2C1_BASE_MORT          (APB1PERIPH_BASE_MORT + 0x6000)
#endif /* STM32F410xx || STM32F412xG || STM32F413_423xx || STM32F446xx_MORT */
#define CAN1_BASE_MORT             (APB1PERIPH_BASE_MORT + 0x6400)
#define CAN2_BASE_MORT             (APB1PERIPH_BASE_MORT + 0x6800)
#if defined(STM32F413_423xx)
#define CAN3_BASE_MORT             (APB1PERIPH_BASE_MORT + 0x6C00)
#endif /* STM32F413_423xx */
#if defined(STM32F446xx_MORT)
#define CEC_BASE_MORT              (APB1PERIPH_BASE_MORT + 0x6C00)
#endif /* STM32F446xx_MORT */
#define PWR_BASE_MORT              (APB1PERIPH_BASE_MORT + 0x7000)
#define DAC_BASE_MORT              (APB1PERIPH_BASE_MORT + 0x7400)
#define UART7_BASE_MORT            (APB1PERIPH_BASE_MORT + 0x7800)
#define UART8_BASE_MORT            (APB1PERIPH_BASE_MORT + 0x7C00)

/*!< APB2 peripherals */
#define TIM1_BASE_MORT             (APB2PERIPH_BASE_MORT + 0x0000)
#define TIM8_BASE_MORT             (APB2PERIPH_BASE_MORT + 0x0400)
#define USART1_BASE_MORT           (APB2PERIPH_BASE_MORT + 0x1000)
#define USART6_BASE_MORT           (APB2PERIPH_BASE_MORT + 0x1400)
#define UART9_BASE_MORT            (APB2PERIPH_BASE_MORT + 0x1800U)
#define UART10_BASE_MORT           (APB2PERIPH_BASE_MORT + 0x1C00U)
#define ADC1_BASE_MORT             (APB2PERIPH_BASE_MORT + 0x2000)
#define ADC2_BASE_MORT             (APB2PERIPH_BASE_MORT + 0x2100)
#define ADC3_BASE_MORT             (APB2PERIPH_BASE_MORT + 0x2200)
#define ADC_BASE_MORT              (APB2PERIPH_BASE_MORT + 0x2300)
#define SDIO_BASE_MORT             (APB2PERIPH_BASE_MORT + 0x2C00)
#define SPI1_BASE_MORT             (APB2PERIPH_BASE_MORT + 0x3000)
#define SPI4_BASE_MORT             (APB2PERIPH_BASE_MORT + 0x3400)
#define SYSCFG_BASE_MORT           (APB2PERIPH_BASE_MORT + 0x3800)
#define EXTI_BASE_MORT             (APB2PERIPH_BASE_MORT + 0x3C00)
#define TIM9_BASE_MORT             (APB2PERIPH_BASE_MORT + 0x4000)
#define TIM10_BASE_MORT            (APB2PERIPH_BASE_MORT + 0x4400)
#define TIM11_BASE_MORT            (APB2PERIPH_BASE_MORT + 0x4800)
#define SPI5_BASE_MORT             (APB2PERIPH_BASE_MORT + 0x5000)
#define SPI6_BASE_MORT             (APB2PERIPH_BASE_MORT + 0x5400)
#define SAI1_BASE_MORT             (APB2PERIPH_BASE_MORT + 0x5800)
#define SAI1_Block_A_BASE_MORT     (SAI1_BASE_MORT + 0x004)
#define SAI1_Block_B_BASE_MORT     (SAI1_BASE_MORT + 0x024)
#if defined(STM32F446xx_MORT)
#define SAI2_BASE_MORT             (APB2PERIPH_BASE_MORT + 0x5C00)
#define SAI2_Block_A_BASE_MORT     (SAI2_BASE_MORT + 0x004)
#define SAI2_Block_B_BASE_MORT     (SAI2_BASE_MORT + 0x024)
#endif /* STM32F446xx_MORT */
#define LTDC_BASE_MORT             (APB2PERIPH_BASE_MORT + 0x6800)
#define LTDC_Layer1_BASE_MORT      (LTDC_BASE_MORT + 0x84)
#define LTDC_Layer2_BASE_MORT      (LTDC_BASE_MORT + 0x104)
#if defined(STM32F469_479xx)
#define DSI_BASE_MORT              (APB2PERIPH_BASE_MORT + 0x6C00)
#endif /* STM32F469_479xx */
#if defined(STM32F412xG) || defined(STM32F413_423xx)
#define DFSDM1_BASE_MORT           (APB2PERIPH_BASE_MORT + 0x6000)
#define DFSDM1_Channel0_BASE_MORT  (DFSDM1_BASE_MORT + 0x00)
#define DFSDM1_Channel1_BASE_MORT  (DFSDM1_BASE_MORT + 0x20)
#define DFSDM1_Channel2_BASE_MORT  (DFSDM1_BASE_MORT + 0x40)
#define DFSDM1_Channel3_BASE_MORT  (DFSDM1_BASE_MORT + 0x60)
#define DFSDM1_Filter0_BASE_MORT   (DFSDM1_BASE_MORT + 0x100)
#define DFSDM1_Filter1_BASE_MORT   (DFSDM1_BASE_MORT + 0x180)
#define DFSDM1_0_MORT              ((DFSDM_TypeDef *) DFSDM1_Filter0_BASE_MORT)
#define DFSDM1_1_MORT              ((DFSDM_TypeDef *) DFSDM1_Filter1_BASE_MORT)
/* Legacy Defines */
#define DFSDM0                DFSDM1_0_MORT              
#define DFSDM1                DFSDM1_1_MORT              
#if defined(STM32F413_423xx)
#define DFSDM2_BASE_MORT           (APB2PERIPH_BASE_MORT + 0x6400U)
#define DFSDM2_Channel0_BASE_MORT  (DFSDM2_BASE_MORT + 0x00U)
#define DFSDM2_Channel1_BASE_MORT  (DFSDM2_BASE_MORT + 0x20U)
#define DFSDM2_Channel2_BASE_MORT  (DFSDM2_BASE_MORT + 0x40U)
#define DFSDM2_Channel3_BASE_MORT  (DFSDM2_BASE_MORT + 0x60U)
#define DFSDM2_Channel4_BASE_MORT  (DFSDM2_BASE_MORT + 0x80U)
#define DFSDM2_Channel5_BASE_MORT  (DFSDM2_BASE_MORT + 0xA0U)
#define DFSDM2_Channel6_BASE_MORT  (DFSDM2_BASE_MORT + 0xC0U)
#define DFSDM2_Channel7_BASE_MORT  (DFSDM2_BASE_MORT + 0xE0U)
#define DFSDM2_Filter0_BASE_MORT   (DFSDM2_BASE_MORT + 0x100U)
#define DFSDM2_Filter1_BASE_MORT   (DFSDM2_BASE_MORT + 0x180U)
#define DFSDM2_Filter2_BASE_MORT   (DFSDM2_BASE_MORT + 0x200U)
#define DFSDM2_Filter3_BASE_MORT   (DFSDM2_BASE_MORT + 0x280U)
#define DFSDM2_0_MORT              ((DFSDM_TypeDef *) DFSDM2_Filter0_BASE_MORT)
#define DFSDM2_1_MORT              ((DFSDM_TypeDef *) DFSDM2_Filter1_BASE_MORT)
#define DFSDM2_2_MORT              ((DFSDM_TypeDef *) DFSDM2_Filter2_BASE_MORT)
#define DFSDM2_3_MORT              ((DFSDM_TypeDef *) DFSDM2_Filter3_BASE_MORT)
#endif /* STM32F413_423xx */
#endif /* STM32F412xG ||  STM32F413_423xx */

/*!< AHB1 peripherals */
#define GPIOA_BASE_MORT            (AHB1PERIPH_BASE_MORT + 0x0000)
#define GPIOB_BASE_MORT            (AHB1PERIPH_BASE_MORT + 0x0400)
#define GPIOC_BASE_MORT            (AHB1PERIPH_BASE_MORT + 0x0800)
#define GPIOD_BASE_MORT            (AHB1PERIPH_BASE_MORT + 0x0C00)
#define GPIOE_BASE_MORT            (AHB1PERIPH_BASE_MORT + 0x1000)
#define GPIOF_BASE_MORT            (AHB1PERIPH_BASE_MORT + 0x1400)
#define GPIOG_BASE_MORT            (AHB1PERIPH_BASE_MORT + 0x1800)
#define GPIOH_BASE_MORT            (AHB1PERIPH_BASE_MORT + 0x1C00)
#define GPIOI_BASE_MORT            (AHB1PERIPH_BASE_MORT + 0x2000)
#define GPIOJ_BASE_MORT            (AHB1PERIPH_BASE_MORT + 0x2400)
#define GPIOK_BASE_MORT            (AHB1PERIPH_BASE_MORT + 0x2800)
#define CRC_BASE_MORT              (AHB1PERIPH_BASE_MORT + 0x3000)
#define RCC_BASE_MORT              (AHB1PERIPH_BASE_MORT + 0x3800)
#define FLASH_R_BASE_MORT          (AHB1PERIPH_BASE_MORT + 0x3C00)
#define DMA1_BASE_MORT             (AHB1PERIPH_BASE_MORT + 0x6000)
#define DMA1_Stream0_BASE_MORT     (DMA1_BASE_MORT + 0x010)
#define DMA1_Stream1_BASE_MORT     (DMA1_BASE_MORT + 0x028)
#define DMA1_Stream2_BASE_MORT     (DMA1_BASE_MORT + 0x040)
#define DMA1_Stream3_BASE_MORT     (DMA1_BASE_MORT + 0x058)
#define DMA1_Stream4_BASE_MORT     (DMA1_BASE_MORT + 0x070)
#define DMA1_Stream5_BASE_MORT     (DMA1_BASE_MORT + 0x088)
#define DMA1_Stream6_BASE_MORT     (DMA1_BASE_MORT + 0x0A0)
#define DMA1_Stream7_BASE_MORT     (DMA1_BASE_MORT + 0x0B8)
#define DMA2_BASE_MORT             (AHB1PERIPH_BASE_MORT + 0x6400)
#define DMA2_Stream0_BASE_MORT     (DMA2_BASE_MORT + 0x010)
#define DMA2_Stream1_BASE_MORT     (DMA2_BASE_MORT + 0x028)
#define DMA2_Stream2_BASE_MORT     (DMA2_BASE_MORT + 0x040)
#define DMA2_Stream3_BASE_MORT     (DMA2_BASE_MORT + 0x058)
#define DMA2_Stream4_BASE_MORT     (DMA2_BASE_MORT + 0x070)
#define DMA2_Stream5_BASE_MORT     (DMA2_BASE_MORT + 0x088)
#define DMA2_Stream6_BASE_MORT     (DMA2_BASE_MORT + 0x0A0)
#define DMA2_Stream7_BASE_MORT     (DMA2_BASE_MORT + 0x0B8)
#define ETH_BASE_MORT              (AHB1PERIPH_BASE_MORT + 0x8000)
#define ETH_MAC_BASE_MORT          (ETH_BASE_MORT)
#define ETH_MMC_BASE_MORT          (ETH_BASE_MORT + 0x0100)
#define ETH_PTP_BASE_MORT          (ETH_BASE_MORT + 0x0700)
#define ETH_DMA_BASE_MORT          (ETH_BASE_MORT + 0x1000)
#define DMA2D_BASE_MORT            (AHB1PERIPH_BASE_MORT + 0xB000)

/*!< AHB2 peripherals */
#define DCMI_BASE_MORT             (AHB2PERIPH_BASE_MORT + 0x50000)
#define CRYP_BASE_MORT             (AHB2PERIPH_BASE_MORT + 0x60000)
#define HASH_BASE_MORT             (AHB2PERIPH_BASE_MORT + 0x60400)
#define HASH_DIGEST_BASE_MORT      (AHB2PERIPH_BASE_MORT + 0x60710)
#define RNG_BASE_MORT              (AHB2PERIPH_BASE_MORT + 0x60800)

#if defined(STM32F40_41xxx) || defined(STM32F412xG) || defined(STM32F413_423xx)
/*!< FSMC Bankx registers base address */
#define FSMC_Bank1_R_BASE_MORT     (FSMC_R_BASE_MORT + 0x0000)
#define FSMC_Bank1E_R_BASE_MORT    (FSMC_R_BASE_MORT + 0x0104)
#define FSMC_Bank2_R_BASE_MORT     (FSMC_R_BASE_MORT + 0x0060)
#define FSMC_Bank3_R_BASE_MORT     (FSMC_R_BASE_MORT + 0x0080)
#define FSMC_Bank4_R_BASE_MORT     (FSMC_R_BASE_MORT + 0x00A0)
#endif /* STM32F40_41xxx || STM32F412xG || STM32F413_423xx */

#if defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F446xx_MORT) || defined(STM32F469_479xx)
/*!< FMC Bankx registers base address */
#define FMC_Bank1_R_BASE_MORT      (FMC_R_BASE_MORT + 0x0000)
#define FMC_Bank1E_R_BASE_MORT     (FMC_R_BASE_MORT + 0x0104)
#define FMC_Bank2_R_BASE_MORT      (FMC_R_BASE_MORT + 0x0060)
#define FMC_Bank3_R_BASE_MORT      (FMC_R_BASE_MORT + 0x0080)
#define FMC_Bank4_R_BASE_MORT      (FMC_R_BASE_MORT + 0x00A0)
#define FMC_Bank5_6_R_BASE_MORT    (FMC_R_BASE_MORT + 0x0140)
#endif /* STM32F427_437xx ||  STM32F429_439xx || STM32F446xx_MORT || STM32F469_479xx */

/* Debug MCU registers base address */
#define DBGMCU_BASE_MORT           ((uint32_t )0xE0042000)

/**
  * @}
  */
  
/** @addtogroup Peripheral_declaration
  * @{
  */
#if defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F446xx_MORT) || defined(STM32F469_479xx)
#define QUADSPI_MORT             ((QUADSPI_TypeDef_mort *) QSPI_R_BASE_MORT)
#endif /* STM32F412xG || STM32F413_423xx || STM32F446xx_MORT || STM32F469_479xx */
#define TIM2_MORT                ((TIM_TypeDef_mort *) TIM2_BASE_MORT)
#define TIM3_MORT                ((TIM_TypeDef_mort *) TIM3_BASE_MORT)
#define TIM4_MORT                ((TIM_TypeDef_mort *) TIM4_BASE_MORT)
#define TIM5_MORT                ((TIM_TypeDef_mort *) TIM5_BASE_MORT)
#define TIM6_MORT                ((TIM_TypeDef_mort *) TIM6_BASE_MORT)
#define TIM7_MORT                ((TIM_TypeDef_mort *) TIM7_BASE_MORT)
#define TIM12_MORT               ((TIM_TypeDef_mort *) TIM12_BASE_MORT)
#define TIM13_MORT               ((TIM_TypeDef_mort *) TIM13_BASE_MORT)
#define TIM14_MORT               ((TIM_TypeDef_mort *) TIM14_BASE_MORT)
#define RTC_MORT                 ((RTC_TypeDef_mort *) RTC_BASE_MORT)
#define WWDG_MORT                ((WWDG_TypeDef_mort *) WWDG_BASE_MORT)
#define IWDG_MORT                ((IWDG_TypeDef_mort *) IWDG_BASE_MORT)
#define I2S2ext_MORT             ((SPI_TypeDef_mort *) I2S2ext_BASE_MORT)
#define SPI2_MORT                ((SPI_TypeDef_mort *) SPI2_BASE_MORT)
#define SPI3_MORT                ((SPI_TypeDef_mort *) SPI3_BASE_MORT)
#if defined(STM32F446xx_MORT)
#define SPDIFRX_MORT             ((SPDIFRX_TypeDef_mort *) SPDIFRX_BASE_MORT)
#endif /* STM32F446xx_MORT */
#define I2S3ext_MORT             ((SPI_TypeDef_mort *) I2S3ext_BASE_MORT)
#define USART2_MORT              ((USART_TypeDef_mort *) USART2_BASE_MORT)
#define USART3_MORT              ((USART_TypeDef_mort *) USART3_BASE_MORT)
#define UART4_MORT               ((USART_TypeDef_mort *) UART4_BASE_MORT)
#define UART5_MORT               ((USART_TypeDef_mort *) UART5_BASE_MORT)
#define I2C1_MORT                ((I2C_TypeDef_mort *) I2C1_BASE_MORT)
#define I2C2_MORT                ((I2C_TypeDef_mort *) I2C2_BASE_MORT)
#define I2C3_MORT                ((I2C_TypeDef_mort *) I2C3_BASE_MORT)
#if defined(STM32F410xx) || defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F446xx_MORT)
#define FMPI2C1_MORT             ((FMPI2C_TypeDef_mort *) FMPI2C1_BASE_MORT)
#endif /* STM32F410xx || STM32F412xG || STM32F413_423xx || STM32F446xx_MORT */
#if defined(STM32F410xx) || defined(STM32F413_423xx)
#define LPTIM1_MORT              ((LPTIM_TypeDef_mort *) LPTIM1_BASE_MORT)
#endif /* STM32F410xx || STM32F413_423xx */
#define CAN1_MORT                ((CAN_TypeDef_mort *) CAN1_BASE_MORT)
#define CAN2_MORT                ((CAN_TypeDef_mort *) CAN2_BASE_MORT)
#if defined(STM32F413_423xx)
#define CAN3_MORT                ((CAN_TypeDef_mort *) CAN3_BASE_MORT)
#endif /* STM32F413_423xx */
#if defined(STM32F446xx_MORT)
#define CEC_MORT                 ((CEC_TypeDef_mort *) CEC_BASE_MORT)
#endif /* STM32F446xx_MORT */
#define PWR_MORT                 ((PWR_TypeDef_mort *) PWR_BASE_MORT)
#define DAC_MORT                 ((DAC_TypeDef_mort *) DAC_BASE_MORT)
#define UART7_MORT               ((USART_TypeDef_mort *) UART7_BASE_MORT)
#define UART8_MORT               ((USART_TypeDef_mort *) UART8_BASE_MORT)
#define UART9_MORT               ((USART_TypeDef_mort *) UART9_BASE_MORT)
#define UART10_MORT              ((USART_TypeDef_mort *) UART10_BASE_MORT)
#define TIM1_MORT                ((TIM_TypeDef_mort *) TIM1_BASE_MORT)
#define TIM8_MORT                ((TIM_TypeDef_mort *) TIM8_BASE_MORT)
#define USART1_MORT              ((USART_TypeDef_mort *) USART1_BASE_MORT)
#define USART6_MORT              ((USART_TypeDef_mort *) USART6_BASE_MORT)
#define ADC_MORT                 ((ADC_Common_TypeDef_mort *) ADC_BASE_MORT)
#define ADC1_MORT                ((ADC_TypeDef_mort *) ADC1_BASE_MORT)
#define ADC2_MORT                ((ADC_TypeDef_mort *) ADC2_BASE_MORT)
#define ADC3_MORT                ((ADC_TypeDef_mort *) ADC3_BASE_MORT)
#define SDIO_MORT                ((SDIO_TypeDef_mort *) SDIO_BASE_MORT)
#define SPI1_MORT                ((SPI_TypeDef_mort *) SPI1_BASE_MORT) 
#define SPI4_MORT                ((SPI_TypeDef_mort *) SPI4_BASE_MORT)
#define SYSCFG_MORT              ((SYSCFG_TypeDef_mort *) SYSCFG_BASE_MORT)
#define EXTI_MORT                ((EXTI_TypeDef_mort *) EXTI_BASE_MORT)
#define TIM9_MORT                ((TIM_TypeDef_mort *) TIM9_BASE_MORT)
#define TIM10_MORT               ((TIM_TypeDef_mort *) TIM10_BASE_MORT)
#define TIM11_MORT               ((TIM_TypeDef_mort *) TIM11_BASE_MORT)
#define SPI5_MORT                ((SPI_TypeDef_mort *) SPI5_BASE_MORT)
#define SPI6_MORT                ((SPI_TypeDef_mort *) SPI6_BASE_MORT)
#define SAI1_MORT                ((SAI_TypeDef_mort *) SAI1_BASE_MORT)
#define SAI1_Block_A_MORT        ((SAI_Block_TypeDef_mort *)SAI1_Block_A_BASE_MORT)
#define SAI1_Block_B_MORT        ((SAI_Block_TypeDef_mort *)SAI1_Block_B_BASE_MORT)
#if defined(STM32F446xx_MORT)
#define SAI2_MORT                ((SAI_TypeDef_mort *) SAI2_BASE_MORT)
#define SAI2_Block_A_MORT        ((SAI_Block_TypeDef_mort *)SAI2_Block_A_BASE_MORT)
#define SAI2_Block_B_MORT        ((SAI_Block_TypeDef_mort *)SAI2_Block_B_BASE_MORT)
#endif /* STM32F446xx_MORT */
#define LTDC_MORT                ((LTDC_TypeDef_mort *)LTDC_BASE_MORT)
#define LTDC_Layer1_MORT         ((LTDC_Layer_TypeDef_mort *)LTDC_Layer1_BASE_MORT)
#define LTDC_Layer2_MORT         ((LTDC_Layer_TypeDef_mort *)LTDC_Layer2_BASE_MORT)
#if defined(STM32F469_479xx)
#define DSI_MORT                 ((DSI_TypeDef_mort *)DSI_BASE_MORT)
#endif /* STM32F469_479xx */
#if defined(STM32F412xG) || defined(STM32F413_423xx)
#define DFSDM1_Channel0_MORT     ((DFSDM_Channel_TypeDef_mort *) DFSDM1_Channel0_BASE_MORT)
#define DFSDM1_Channel1_MORT     ((DFSDM_Channel_TypeDef_mort *) DFSDM1_Channel1_BASE_MORT)
#define DFSDM1_Channel2_MORT     ((DFSDM_Channel_TypeDef_mort *) DFSDM1_Channel2_BASE_MORT)
#define DFSDM1_Channel3_MORT     ((DFSDM_Channel_TypeDef_mort *) DFSDM1_Channel3_BASE_MORT)
#define DFSDM1_Filter0_MORT      ((DFSDM_TypeDef *) DFSDM_Filter0_BASE)
#define DFSDM1_Filter1_MORT      ((DFSDM_TypeDef *) DFSDM_Filter1_BASE)
#if defined(STM32F413_423xx)
#define DFSDM2_Channel0_MORT     ((DFSDM_Channel_TypeDef_mort *) DFSDM2_Channel0_BASE_MORT)
#define DFSDM2_Channel1_MORT     ((DFSDM_Channel_TypeDef_mort *) DFSDM2_Channel1_BASE_MORT)
#define DFSDM2_Channel2_MORT     ((DFSDM_Channel_TypeDef_mort *) DFSDM2_Channel2_BASE_MORT)
#define DFSDM2_Channel3_MORT     ((DFSDM_Channel_TypeDef_mort *) DFSDM2_Channel3_BASE_MORT)
#define DFSDM2_Channel4_MORT     ((DFSDM_Channel_TypeDef_mort *) DFSDM2_Channel4_BASE_MORT)
#define DFSDM2_Channel5_MORT     ((DFSDM_Channel_TypeDef_mort *) DFSDM2_Channel5_BASE_MORT)
#define DFSDM2_Channel6_MORT     ((DFSDM_Channel_TypeDef_mort *) DFSDM2_Channel6_BASE_MORT)
#define DFSDM2_Channel7_MORT     ((DFSDM_Channel_TypeDef_mort *) DFSDM2_Channel7_BASE_MORT)
#define DFSDM2_Filter0_MORT      ((DFSDM_Filter_TypeDef_mort *) DFSDM2_Filter0_BASE_MORT)
#define DFSDM2_Filter1_MORT      ((DFSDM_Filter_TypeDef_mort *) DFSDM2_Filter1_BASE_MORT)
#define DFSDM2_Filter2_MORT      ((DFSDM_Filter_TypeDef_mort *) DFSDM2_Filter2_BASE_MORT)
#define DFSDM2_Filter3_MORT      ((DFSDM_Filter_TypeDef_mort *) DFSDM2_Filter3_BASE_MORT)
#endif /* STM32F413_423xx */
#endif /* STM32F412xG || STM32F413_423xx */
#define GPIOA_MORT               ((GPIO_TypeDef_mort *) GPIOA_BASE_MORT)
#define GPIOB_MORT               ((GPIO_TypeDef_mort *) GPIOB_BASE_MORT)
#define GPIOC_MORT               ((GPIO_TypeDef_mort *) GPIOC_BASE_MORT)
#define GPIOD_MORT               ((GPIO_TypeDef_mort *) GPIOD_BASE_MORT)
#define GPIOE_MORT               ((GPIO_TypeDef_mort *) GPIOE_BASE_MORT)
#define GPIOF_MORT               ((GPIO_TypeDef_mort *) GPIOF_BASE_MORT)
#define GPIOG_MORT               ((GPIO_TypeDef_mort *) GPIOG_BASE_MORT)
#define GPIOH_MORT               ((GPIO_TypeDef_mort *) GPIOH_BASE_MORT)
#define GPIOI_MORT               ((GPIO_TypeDef_mort *) GPIOI_BASE_MORT)
#define GPIOJ_MORT               ((GPIO_TypeDef_mort *) GPIOJ_BASE_MORT)
#define GPIOK_MORT               ((GPIO_TypeDef_mort *) GPIOK_BASE_MORT)
#define CRC_MORT                 ((CRC_TypeDef_mort *) CRC_BASE_MORT)
#define RCC_MORT                 ((RCC_TypeDef_mort *) RCC_BASE_MORT)
#define FLASH_MORT               ((FLASH_TypeDef_mort *) FLASH_R_BASE_MORT)
#define DMA1_MORT                ((DMA_TypeDef_mort *) DMA1_BASE_MORT)
#define DMA1_Stream0_MORT        ((DMA_Stream_TypeDef_mort *) DMA1_Stream0_BASE_MORT)
#define DMA1_Stream1_MORT        ((DMA_Stream_TypeDef_mort *) DMA1_Stream1_BASE_MORT)
#define DMA1_Stream2_MORT        ((DMA_Stream_TypeDef_mort *) DMA1_Stream2_BASE_MORT)
#define DMA1_Stream3_MORT        ((DMA_Stream_TypeDef_mort *) DMA1_Stream3_BASE_MORT)
#define DMA1_Stream4_MORT        ((DMA_Stream_TypeDef_mort *) DMA1_Stream4_BASE_MORT)
#define DMA1_Stream5_MORT        ((DMA_Stream_TypeDef_mort *) DMA1_Stream5_BASE_MORT)
#define DMA1_Stream6_MORT        ((DMA_Stream_TypeDef_mort *) DMA1_Stream6_BASE_MORT)
#define DMA1_Stream7_MORT        ((DMA_Stream_TypeDef_mort *) DMA1_Stream7_BASE_MORT)
#define DMA2_MORT                ((DMA_TypeDef_mort *) DMA2_BASE_MORT)
#define DMA2_Stream0_MORT        ((DMA_Stream_TypeDef_mort *) DMA2_Stream0_BASE_MORT)
#define DMA2_Stream1_MORT        ((DMA_Stream_TypeDef_mort *) DMA2_Stream1_BASE_MORT)
#define DMA2_Stream2_MORT        ((DMA_Stream_TypeDef_mort *) DMA2_Stream2_BASE_MORT)
#define DMA2_Stream3_MORT        ((DMA_Stream_TypeDef_mort *) DMA2_Stream3_BASE_MORT)
#define DMA2_Stream4_MORT        ((DMA_Stream_TypeDef_mort *) DMA2_Stream4_BASE_MORT)
#define DMA2_Stream5_MORT        ((DMA_Stream_TypeDef_mort *) DMA2_Stream5_BASE_MORT)
#define DMA2_Stream6_MORT        ((DMA_Stream_TypeDef_mort *) DMA2_Stream6_BASE_MORT)
#define DMA2_Stream7_MORT        ((DMA_Stream_TypeDef_mort *) DMA2_Stream7_BASE_MORT)
#define ETH_MORT                 ((ETH_TypeDef_mort *) ETH_BASE_MORT)  
#define DMA2D_MORT               ((DMA2D_TypeDef_mort *)DMA2D_BASE_MORT)
#define DCMI_MORT                ((DCMI_TypeDef_mort *) DCMI_BASE_MORT)
#define CRYP_MORT                ((CRYP_TypeDef_mort *) CRYP_BASE_MORT)
#define HASH_MORT                ((HASH_TypeDef_mort *) HASH_BASE_MORT)
#define HASH_DIGEST_MORT         ((HASH_DIGEST_TypeDef_mort *) HASH_DIGEST_BASE_MORT)
#define RNG_MORT                 ((RNG_TypeDef_mort *) RNG_BASE_MORT)

#if defined(STM32F40_41xxx) || defined(STM32F412xG) || defined(STM32F413_423xx)
#define FSMC_Bank1_MORT          ((FSMC_Bank1_TypeDef_mort *) FSMC_Bank1_R_BASE_MORT)
#define FSMC_Bank1E_MORT         ((FSMC_Bank1E_TypeDef_mort *) FSMC_Bank1E_R_BASE_MORT)
#define FSMC_Bank2_MORT          ((FSMC_Bank2_TypeDef_mort *) FSMC_Bank2_R_BASE_MORT)
#define FSMC_Bank3_MORT          ((FSMC_Bank3_TypeDef_mort *) FSMC_Bank3_R_BASE_MORT)
#define FSMC_Bank4_MORT          ((FSMC_Bank4_TypeDef_mort *) FSMC_Bank4_R_BASE_MORT)
#endif /* STM32F40_41xxx || STM32F412xG || STM32F413_423xx */

#if defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F446xx_MORT) || defined(STM32F469_479xx)
#define FMC_Bank1_MORT           ((FMC_Bank1_TypeDef_mort *) FMC_Bank1_R_BASE_MORT)
#define FMC_Bank1E_MORT          ((FMC_Bank1E_TypeDef_mort *) FMC_Bank1E_R_BASE_MORT)
#define FMC_Bank2_MORT           ((FMC_Bank2_TypeDef_mort *) FMC_Bank2_R_BASE_MORT)
#define FMC_Bank3_MORT           ((FMC_Bank3_TypeDef_mort *) FMC_Bank3_R_BASE_MORT)
#define FMC_Bank4_MORT           ((FMC_Bank4_TypeDef_mort *) FMC_Bank4_R_BASE_MORT)
#define FMC_Bank5_6_MORT         ((FMC_Bank5_6_TypeDef_mort *) FMC_Bank5_6_R_BASE_MORT)
#endif /* STM32F427_437xx ||  STM32F429_439xx || STM32F446xx_MORT || STM32F469_479xx */

#define DBGMCU_MORT              ((DBGMCU_TypeDef_mort *) DBGMCU_BASE_MORT)

/**
  * @}
  */

/** @addtogroup Exported_constants
  * @{
  */
  
  /** @addtogroup Peripheral_Registers_Bits_Definition
  * @{
  */
    
/******************************************************************************/
/*                         Peripheral Registers_Bits_Definition               */
/******************************************************************************/

/******************************************************************************/
/*                                                                            */
/*                        Analog to Digital Converter                         */
/*                                                                            */
/******************************************************************************/
/********************  Bit definition for ADC_SR register  ********************/
#define  ADC_SR_AWD_MORT                          ((uint8_t)0x01)               /*!<Analog watchdog flag               */
#define  ADC_SR_EOC_MORT                          ((uint8_t)0x02)               /*!<End of conversion                  */
#define  ADC_SR_JEOC_MORT                         ((uint8_t)0x04)               /*!<Injected channel end of conversion */
#define  ADC_SR_JSTRT_MORT                        ((uint8_t)0x08)               /*!<Injected channel Start flag        */
#define  ADC_SR_STRT_MORT                         ((uint8_t)0x10)               /*!<Regular channel Start flag         */
#define  ADC_SR_OVR_MORT                          ((uint8_t)0x20)               /*!<Overrun flag                       */

/*******************  Bit definition for ADC_CR1 register  ********************/
#define  ADC_CR1_AWDCH_MORT                       ((uint32_t)0x0000001F)        /*!<AWDCH[4:0] bits (Analog watchdog channel select bits) */
#define  ADC_CR1_AWDCH_0_MORT                     ((uint32_t)0x00000001)        /*!<Bit 0 */
#define  ADC_CR1_AWDCH_1_MORT                     ((uint32_t)0x00000002)        /*!<Bit 1 */
#define  ADC_CR1_AWDCH_2_MORT                     ((uint32_t)0x00000004)        /*!<Bit 2 */
#define  ADC_CR1_AWDCH_3_MORT                     ((uint32_t)0x00000008)        /*!<Bit 3 */
#define  ADC_CR1_AWDCH_4_MORT                     ((uint32_t)0x00000010)        /*!<Bit 4 */
#define  ADC_CR1_EOCIE_MORT                       ((uint32_t)0x00000020)        /*!<Interrupt enable for EOC                              */
#define  ADC_CR1_AWDIE_MORT                       ((uint32_t)0x00000040)        /*!<AAnalog Watchdog interrupt enable                     */
#define  ADC_CR1_JEOCIE_MORT                      ((uint32_t)0x00000080)        /*!<Interrupt enable for injected channels                */
#define  ADC_CR1_SCAN_MORT                        ((uint32_t)0x00000100)        /*!<Scan mode                                             */
#define  ADC_CR1_AWDSGL_MORT                      ((uint32_t)0x00000200)        /*!<Enable the watchdog on a single channel in scan mode  */
#define  ADC_CR1_JAUTO_MORT                       ((uint32_t)0x00000400)        /*!<Automatic injected group conversion                   */
#define  ADC_CR1_DISCEN_MORT                      ((uint32_t)0x00000800)        /*!<Discontinuous mode on regular channels                */
#define  ADC_CR1_JDISCEN_MORT                     ((uint32_t)0x00001000)        /*!<Discontinuous mode on injected channels               */
#define  ADC_CR1_DISCNUM_MORT                     ((uint32_t)0x0000E000)        /*!<DISCNUM[2:0] bits (Discontinuous mode channel count)  */
#define  ADC_CR1_DISCNUM_0_MORT                   ((uint32_t)0x00002000)        /*!<Bit 0 */
#define  ADC_CR1_DISCNUM_1_MORT                   ((uint32_t)0x00004000)        /*!<Bit 1 */
#define  ADC_CR1_DISCNUM_2_MORT                   ((uint32_t)0x00008000)        /*!<Bit 2 */
#define  ADC_CR1_JAWDEN_MORT                      ((uint32_t)0x00400000)        /*!<Analog watchdog enable on injected channels           */
#define  ADC_CR1_AWDEN_MORT                       ((uint32_t)0x00800000)        /*!<Analog watchdog enable on regular channels            */
#define  ADC_CR1_RES_MORT                         ((uint32_t)0x03000000)        /*!<RES[2:0] bits (Resolution)                            */
#define  ADC_CR1_RES_0_MORT                       ((uint32_t)0x01000000)        /*!<Bit 0 */
#define  ADC_CR1_RES_1_MORT                       ((uint32_t)0x02000000)        /*!<Bit 1 */
#define  ADC_CR1_OVRIE_MORT                       ((uint32_t)0x04000000)         /*!<overrun interrupt enable                              */
  
/*******************  Bit definition for ADC_CR2 register  ********************/
#define  ADC_CR2_ADON_MORT                        ((uint32_t)0x00000001)        /*!<A/D Converter ON / OFF             */
#define  ADC_CR2_CONT_MORT                        ((uint32_t)0x00000002)        /*!<Continuous Conversion              */
#define  ADC_CR2_DMA_MORT                         ((uint32_t)0x00000100)        /*!<Direct Memory access mode          */
#define  ADC_CR2_DDS_MORT                         ((uint32_t)0x00000200)        /*!<DMA disable selection (Single ADC_MORT) */
#define  ADC_CR2_EOCS_MORT                        ((uint32_t)0x00000400)        /*!<End of conversion selection        */
#define  ADC_CR2_ALIGN_MORT                       ((uint32_t)0x00000800)        /*!<Data Alignment                     */
#define  ADC_CR2_JEXTSEL_MORT                     ((uint32_t)0x000F0000)        /*!<JEXTSEL[3:0] bits (External event select for injected group) */
#define  ADC_CR2_JEXTSEL_0_MORT                   ((uint32_t)0x00010000)        /*!<Bit 0 */
#define  ADC_CR2_JEXTSEL_1_MORT                   ((uint32_t)0x00020000)        /*!<Bit 1 */
#define  ADC_CR2_JEXTSEL_2_MORT                   ((uint32_t)0x00040000)        /*!<Bit 2 */
#define  ADC_CR2_JEXTSEL_3_MORT                   ((uint32_t)0x00080000)        /*!<Bit 3 */
#define  ADC_CR2_JEXTEN_MORT                      ((uint32_t)0x00300000)        /*!<JEXTEN[1:0] bits (External Trigger Conversion mode for injected channelsp) */
#define  ADC_CR2_JEXTEN_0_MORT                    ((uint32_t)0x00100000)        /*!<Bit 0 */
#define  ADC_CR2_JEXTEN_1_MORT                    ((uint32_t)0x00200000)        /*!<Bit 1 */
#define  ADC_CR2_JSWSTART_MORT                    ((uint32_t)0x00400000)        /*!<Start Conversion of injected channels */
#define  ADC_CR2_EXTSEL_MORT                      ((uint32_t)0x0F000000)        /*!<EXTSEL[3:0] bits (External Event Select for regular group) */
#define  ADC_CR2_EXTSEL_0_MORT                    ((uint32_t)0x01000000)        /*!<Bit 0 */
#define  ADC_CR2_EXTSEL_1_MORT                    ((uint32_t)0x02000000)        /*!<Bit 1 */
#define  ADC_CR2_EXTSEL_2_MORT                    ((uint32_t)0x04000000)        /*!<Bit 2 */
#define  ADC_CR2_EXTSEL_3_MORT                    ((uint32_t)0x08000000)        /*!<Bit 3 */
#define  ADC_CR2_EXTEN_MORT                       ((uint32_t)0x30000000)        /*!<EXTEN[1:0] bits (External Trigger Conversion mode for regular channelsp) */
#define  ADC_CR2_EXTEN_0_MORT                     ((uint32_t)0x10000000)        /*!<Bit 0 */
#define  ADC_CR2_EXTEN_1_MORT                     ((uint32_t)0x20000000)        /*!<Bit 1 */
#define  ADC_CR2_SWSTART_MORT                     ((uint32_t)0x40000000)        /*!<Start Conversion of regular channels */

/******************  Bit definition for ADC_SMPR1 register  *******************/
#define  ADC_SMPR1_SMP10_MORT                     ((uint32_t)0x00000007)        /*!<SMP10[2:0] bits (Channel 10 Sample time selection) */
#define  ADC_SMPR1_SMP10_0_MORT                   ((uint32_t)0x00000001)        /*!<Bit 0 */
#define  ADC_SMPR1_SMP10_1_MORT                   ((uint32_t)0x00000002)        /*!<Bit 1 */
#define  ADC_SMPR1_SMP10_2_MORT                   ((uint32_t)0x00000004)        /*!<Bit 2 */
#define  ADC_SMPR1_SMP11_MORT                     ((uint32_t)0x00000038)        /*!<SMP11[2:0] bits (Channel 11 Sample time selection) */
#define  ADC_SMPR1_SMP11_0_MORT                   ((uint32_t)0x00000008)        /*!<Bit 0 */
#define  ADC_SMPR1_SMP11_1_MORT                   ((uint32_t)0x00000010)        /*!<Bit 1 */
#define  ADC_SMPR1_SMP11_2_MORT                   ((uint32_t)0x00000020)        /*!<Bit 2 */
#define  ADC_SMPR1_SMP12_MORT                     ((uint32_t)0x000001C0)        /*!<SMP12[2:0] bits (Channel 12 Sample time selection) */
#define  ADC_SMPR1_SMP12_0_MORT                   ((uint32_t)0x00000040)        /*!<Bit 0 */
#define  ADC_SMPR1_SMP12_1_MORT                   ((uint32_t)0x00000080)        /*!<Bit 1 */
#define  ADC_SMPR1_SMP12_2_MORT                   ((uint32_t)0x00000100)        /*!<Bit 2 */
#define  ADC_SMPR1_SMP13_MORT                     ((uint32_t)0x00000E00)        /*!<SMP13[2:0] bits (Channel 13 Sample time selection) */
#define  ADC_SMPR1_SMP13_0_MORT                   ((uint32_t)0x00000200)        /*!<Bit 0 */
#define  ADC_SMPR1_SMP13_1_MORT                   ((uint32_t)0x00000400)        /*!<Bit 1 */
#define  ADC_SMPR1_SMP13_2_MORT                   ((uint32_t)0x00000800)        /*!<Bit 2 */
#define  ADC_SMPR1_SMP14_MORT                     ((uint32_t)0x00007000)        /*!<SMP14[2:0] bits (Channel 14 Sample time selection) */
#define  ADC_SMPR1_SMP14_0_MORT                   ((uint32_t)0x00001000)        /*!<Bit 0 */
#define  ADC_SMPR1_SMP14_1_MORT                   ((uint32_t)0x00002000)        /*!<Bit 1 */
#define  ADC_SMPR1_SMP14_2_MORT                   ((uint32_t)0x00004000)        /*!<Bit 2 */
#define  ADC_SMPR1_SMP15_MORT                     ((uint32_t)0x00038000)        /*!<SMP15[2:0] bits (Channel 15 Sample time selection) */
#define  ADC_SMPR1_SMP15_0_MORT                   ((uint32_t)0x00008000)        /*!<Bit 0 */
#define  ADC_SMPR1_SMP15_1_MORT                   ((uint32_t)0x00010000)        /*!<Bit 1 */
#define  ADC_SMPR1_SMP15_2_MORT                   ((uint32_t)0x00020000)        /*!<Bit 2 */
#define  ADC_SMPR1_SMP16_MORT                     ((uint32_t)0x001C0000)        /*!<SMP16[2:0] bits (Channel 16 Sample time selection) */
#define  ADC_SMPR1_SMP16_0_MORT                   ((uint32_t)0x00040000)        /*!<Bit 0 */
#define  ADC_SMPR1_SMP16_1_MORT                   ((uint32_t)0x00080000)        /*!<Bit 1 */
#define  ADC_SMPR1_SMP16_2_MORT                   ((uint32_t)0x00100000)        /*!<Bit 2 */
#define  ADC_SMPR1_SMP17_MORT                     ((uint32_t)0x00E00000)        /*!<SMP17[2:0] bits (Channel 17 Sample time selection) */
#define  ADC_SMPR1_SMP17_0_MORT                   ((uint32_t)0x00200000)        /*!<Bit 0 */
#define  ADC_SMPR1_SMP17_1_MORT                   ((uint32_t)0x00400000)        /*!<Bit 1 */
#define  ADC_SMPR1_SMP17_2_MORT                   ((uint32_t)0x00800000)        /*!<Bit 2 */
#define  ADC_SMPR1_SMP18_MORT                     ((uint32_t)0x07000000)        /*!<SMP18[2:0] bits (Channel 18 Sample time selection) */
#define  ADC_SMPR1_SMP18_0_MORT                   ((uint32_t)0x01000000)        /*!<Bit 0 */
#define  ADC_SMPR1_SMP18_1_MORT                   ((uint32_t)0x02000000)        /*!<Bit 1 */
#define  ADC_SMPR1_SMP18_2_MORT                   ((uint32_t)0x04000000)        /*!<Bit 2 */

/******************  Bit definition for ADC_SMPR2 register  *******************/
#define  ADC_SMPR2_SMP0_MORT                      ((uint32_t)0x00000007)        /*!<SMP0[2:0] bits (Channel 0 Sample time selection) */
#define  ADC_SMPR2_SMP0_0_MORT                    ((uint32_t)0x00000001)        /*!<Bit 0 */
#define  ADC_SMPR2_SMP0_1_MORT                    ((uint32_t)0x00000002)        /*!<Bit 1 */
#define  ADC_SMPR2_SMP0_2_MORT                    ((uint32_t)0x00000004)        /*!<Bit 2 */
#define  ADC_SMPR2_SMP1_MORT                      ((uint32_t)0x00000038)        /*!<SMP1[2:0] bits (Channel 1 Sample time selection) */
#define  ADC_SMPR2_SMP1_0_MORT                    ((uint32_t)0x00000008)        /*!<Bit 0 */
#define  ADC_SMPR2_SMP1_1_MORT                    ((uint32_t)0x00000010)        /*!<Bit 1 */
#define  ADC_SMPR2_SMP1_2_MORT                    ((uint32_t)0x00000020)        /*!<Bit 2 */
#define  ADC_SMPR2_SMP2_MORT                      ((uint32_t)0x000001C0)        /*!<SMP2[2:0] bits (Channel 2 Sample time selection) */
#define  ADC_SMPR2_SMP2_0_MORT                    ((uint32_t)0x00000040)        /*!<Bit 0 */
#define  ADC_SMPR2_SMP2_1_MORT                    ((uint32_t)0x00000080)        /*!<Bit 1 */
#define  ADC_SMPR2_SMP2_2_MORT                    ((uint32_t)0x00000100)        /*!<Bit 2 */
#define  ADC_SMPR2_SMP3_MORT                      ((uint32_t)0x00000E00)        /*!<SMP3[2:0] bits (Channel 3 Sample time selection) */
#define  ADC_SMPR2_SMP3_0_MORT                    ((uint32_t)0x00000200)        /*!<Bit 0 */
#define  ADC_SMPR2_SMP3_1_MORT                    ((uint32_t)0x00000400)        /*!<Bit 1 */
#define  ADC_SMPR2_SMP3_2_MORT                    ((uint32_t)0x00000800)        /*!<Bit 2 */
#define  ADC_SMPR2_SMP4_MORT                      ((uint32_t)0x00007000)        /*!<SMP4[2:0] bits (Channel 4 Sample time selection) */
#define  ADC_SMPR2_SMP4_0_MORT                    ((uint32_t)0x00001000)        /*!<Bit 0 */
#define  ADC_SMPR2_SMP4_1_MORT                    ((uint32_t)0x00002000)        /*!<Bit 1 */
#define  ADC_SMPR2_SMP4_2_MORT                    ((uint32_t)0x00004000)        /*!<Bit 2 */
#define  ADC_SMPR2_SMP5_MORT                      ((uint32_t)0x00038000)        /*!<SMP5[2:0] bits (Channel 5 Sample time selection) */
#define  ADC_SMPR2_SMP5_0_MORT                    ((uint32_t)0x00008000)        /*!<Bit 0 */
#define  ADC_SMPR2_SMP5_1_MORT                    ((uint32_t)0x00010000)        /*!<Bit 1 */
#define  ADC_SMPR2_SMP5_2_MORT                    ((uint32_t)0x00020000)        /*!<Bit 2 */
#define  ADC_SMPR2_SMP6_MORT                      ((uint32_t)0x001C0000)        /*!<SMP6[2:0] bits (Channel 6 Sample time selection) */
#define  ADC_SMPR2_SMP6_0_MORT                    ((uint32_t)0x00040000)        /*!<Bit 0 */
#define  ADC_SMPR2_SMP6_1_MORT                    ((uint32_t)0x00080000)        /*!<Bit 1 */
#define  ADC_SMPR2_SMP6_2_MORT                    ((uint32_t)0x00100000)        /*!<Bit 2 */
#define  ADC_SMPR2_SMP7_MORT                      ((uint32_t)0x00E00000)        /*!<SMP7[2:0] bits (Channel 7 Sample time selection) */
#define  ADC_SMPR2_SMP7_0_MORT                    ((uint32_t)0x00200000)        /*!<Bit 0 */
#define  ADC_SMPR2_SMP7_1_MORT                    ((uint32_t)0x00400000)        /*!<Bit 1 */
#define  ADC_SMPR2_SMP7_2_MORT                    ((uint32_t)0x00800000)        /*!<Bit 2 */
#define  ADC_SMPR2_SMP8_MORT                      ((uint32_t)0x07000000)        /*!<SMP8[2:0] bits (Channel 8 Sample time selection) */
#define  ADC_SMPR2_SMP8_0_MORT                    ((uint32_t)0x01000000)        /*!<Bit 0 */
#define  ADC_SMPR2_SMP8_1_MORT                    ((uint32_t)0x02000000)        /*!<Bit 1 */
#define  ADC_SMPR2_SMP8_2_MORT                    ((uint32_t)0x04000000)        /*!<Bit 2 */
#define  ADC_SMPR2_SMP9_MORT                      ((uint32_t)0x38000000)        /*!<SMP9[2:0] bits (Channel 9 Sample time selection) */
#define  ADC_SMPR2_SMP9_0_MORT                    ((uint32_t)0x08000000)        /*!<Bit 0 */
#define  ADC_SMPR2_SMP9_1_MORT                    ((uint32_t)0x10000000)        /*!<Bit 1 */
#define  ADC_SMPR2_SMP9_2_MORT                    ((uint32_t)0x20000000)        /*!<Bit 2 */

/******************  Bit definition for ADC_JOFR1 register  *******************/
#define  ADC_JOFR1_JOFFSET1_MORT                  ((uint16_t)0x0FFF)            /*!<Data offset for injected channel 1 */

/******************  Bit definition for ADC_JOFR2 register  *******************/
#define  ADC_JOFR2_JOFFSET2_MORT                  ((uint16_t)0x0FFF)            /*!<Data offset for injected channel 2 */

/******************  Bit definition for ADC_JOFR3 register  *******************/
#define  ADC_JOFR3_JOFFSET3_MORT                  ((uint16_t)0x0FFF)            /*!<Data offset for injected channel 3 */

/******************  Bit definition for ADC_JOFR4 register  *******************/
#define  ADC_JOFR4_JOFFSET4_MORT                  ((uint16_t)0x0FFF)            /*!<Data offset for injected channel 4 */

/*******************  Bit definition for ADC_HTR register  ********************/
#define  ADC_HTR_HT_MORT                          ((uint16_t)0x0FFF)            /*!<Analog watchdog high threshold */

/*******************  Bit definition for ADC_LTR register  ********************/
#define  ADC_LTR_LT_MORT                          ((uint16_t)0x0FFF)            /*!<Analog watchdog low threshold */

/*******************  Bit definition for ADC_SQR1 register  *******************/
#define  ADC_SQR1_SQ13_MORT                       ((uint32_t)0x0000001F)        /*!<SQ13[4:0] bits (13th conversion in regular sequence) */
#define  ADC_SQR1_SQ13_0_MORT                     ((uint32_t)0x00000001)        /*!<Bit 0 */
#define  ADC_SQR1_SQ13_1_MORT                     ((uint32_t)0x00000002)        /*!<Bit 1 */
#define  ADC_SQR1_SQ13_2_MORT                     ((uint32_t)0x00000004)        /*!<Bit 2 */
#define  ADC_SQR1_SQ13_3_MORT                     ((uint32_t)0x00000008)        /*!<Bit 3 */
#define  ADC_SQR1_SQ13_4_MORT                     ((uint32_t)0x00000010)        /*!<Bit 4 */
#define  ADC_SQR1_SQ14_MORT                       ((uint32_t)0x000003E0)        /*!<SQ14[4:0] bits (14th conversion in regular sequence) */
#define  ADC_SQR1_SQ14_0_MORT                     ((uint32_t)0x00000020)        /*!<Bit 0 */
#define  ADC_SQR1_SQ14_1_MORT                     ((uint32_t)0x00000040)        /*!<Bit 1 */
#define  ADC_SQR1_SQ14_2_MORT                     ((uint32_t)0x00000080)        /*!<Bit 2 */
#define  ADC_SQR1_SQ14_3_MORT                     ((uint32_t)0x00000100)        /*!<Bit 3 */
#define  ADC_SQR1_SQ14_4_MORT                     ((uint32_t)0x00000200)        /*!<Bit 4 */
#define  ADC_SQR1_SQ15_MORT                       ((uint32_t)0x00007C00)        /*!<SQ15[4:0] bits (15th conversion in regular sequence) */
#define  ADC_SQR1_SQ15_0_MORT                     ((uint32_t)0x00000400)        /*!<Bit 0 */
#define  ADC_SQR1_SQ15_1_MORT                     ((uint32_t)0x00000800)        /*!<Bit 1 */
#define  ADC_SQR1_SQ15_2_MORT                     ((uint32_t)0x00001000)        /*!<Bit 2 */
#define  ADC_SQR1_SQ15_3_MORT                     ((uint32_t)0x00002000)        /*!<Bit 3 */
#define  ADC_SQR1_SQ15_4_MORT                     ((uint32_t)0x00004000)        /*!<Bit 4 */
#define  ADC_SQR1_SQ16_MORT                       ((uint32_t)0x000F8000)        /*!<SQ16[4:0] bits (16th conversion in regular sequence) */
#define  ADC_SQR1_SQ16_0_MORT                     ((uint32_t)0x00008000)        /*!<Bit 0 */
#define  ADC_SQR1_SQ16_1_MORT                     ((uint32_t)0x00010000)        /*!<Bit 1 */
#define  ADC_SQR1_SQ16_2_MORT                     ((uint32_t)0x00020000)        /*!<Bit 2 */
#define  ADC_SQR1_SQ16_3_MORT                     ((uint32_t)0x00040000)        /*!<Bit 3 */
#define  ADC_SQR1_SQ16_4_MORT                     ((uint32_t)0x00080000)        /*!<Bit 4 */
#define  ADC_SQR1_L_MORT                          ((uint32_t)0x00F00000)        /*!<L[3:0] bits (Regular channel sequence length) */
#define  ADC_SQR1_L__0_MORT                        ((uint32_t)0x00100000)        /*!<Bit 0 */
#define  ADC_SQR1_L__1_MORT                        ((uint32_t)0x00200000)        /*!<Bit 1 */
#define  ADC_SQR1_L__2_MORT                        ((uint32_t)0x00400000)        /*!<Bit 2 */
#define  ADC_SQR1_L__3_MORT                        ((uint32_t)0x00800000)        /*!<Bit 3 */

/*******************  Bit definition for ADC_SQR2 register  *******************/
#define  ADC_SQR2_SQ7_MORT                        ((uint32_t)0x0000001F)        /*!<SQ7[4:0] bits (7th conversion in regular sequence) */
#define  ADC_SQR2_SQ7_0_MORT                      ((uint32_t)0x00000001)        /*!<Bit 0 */
#define  ADC_SQR2_SQ7_1_MORT                      ((uint32_t)0x00000002)        /*!<Bit 1 */
#define  ADC_SQR2_SQ7_2_MORT                      ((uint32_t)0x00000004)        /*!<Bit 2 */
#define  ADC_SQR2_SQ7_3_MORT                      ((uint32_t)0x00000008)        /*!<Bit 3 */
#define  ADC_SQR2_SQ7_4_MORT                      ((uint32_t)0x00000010)        /*!<Bit 4 */
#define  ADC_SQR2_SQ8_MORT                        ((uint32_t)0x000003E0)        /*!<SQ8[4:0] bits (8th conversion in regular sequence) */
#define  ADC_SQR2_SQ8_0_MORT                      ((uint32_t)0x00000020)        /*!<Bit 0 */
#define  ADC_SQR2_SQ8_1_MORT                      ((uint32_t)0x00000040)        /*!<Bit 1 */
#define  ADC_SQR2_SQ8_2_MORT                      ((uint32_t)0x00000080)        /*!<Bit 2 */
#define  ADC_SQR2_SQ8_3_MORT                      ((uint32_t)0x00000100)        /*!<Bit 3 */
#define  ADC_SQR2_SQ8_4_MORT                      ((uint32_t)0x00000200)        /*!<Bit 4 */
#define  ADC_SQR2_SQ9_MORT                        ((uint32_t)0x00007C00)        /*!<SQ9[4:0] bits (9th conversion in regular sequence) */
#define  ADC_SQR2_SQ9_0_MORT                      ((uint32_t)0x00000400)        /*!<Bit 0 */
#define  ADC_SQR2_SQ9_1_MORT                      ((uint32_t)0x00000800)        /*!<Bit 1 */
#define  ADC_SQR2_SQ9_2_MORT                      ((uint32_t)0x00001000)        /*!<Bit 2 */
#define  ADC_SQR2_SQ9_3_MORT                      ((uint32_t)0x00002000)        /*!<Bit 3 */
#define  ADC_SQR2_SQ9_4_MORT                      ((uint32_t)0x00004000)        /*!<Bit 4 */
#define  ADC_SQR2_SQ10_MORT                       ((uint32_t)0x000F8000)        /*!<SQ10[4:0] bits (10th conversion in regular sequence) */
#define  ADC_SQR2_SQ10_0_MORT                     ((uint32_t)0x00008000)        /*!<Bit 0 */
#define  ADC_SQR2_SQ10_1_MORT                     ((uint32_t)0x00010000)        /*!<Bit 1 */
#define  ADC_SQR2_SQ10_2_MORT                     ((uint32_t)0x00020000)        /*!<Bit 2 */
#define  ADC_SQR2_SQ10_3_MORT                     ((uint32_t)0x00040000)        /*!<Bit 3 */
#define  ADC_SQR2_SQ10_4_MORT                     ((uint32_t)0x00080000)        /*!<Bit 4 */
#define  ADC_SQR2_SQ11_MORT                       ((uint32_t)0x01F00000)        /*!<SQ11[4:0] bits (11th conversion in regular sequence) */
#define  ADC_SQR2_SQ11_0_MORT                     ((uint32_t)0x00100000)        /*!<Bit 0 */
#define  ADC_SQR2_SQ11_1_MORT                     ((uint32_t)0x00200000)        /*!<Bit 1 */
#define  ADC_SQR2_SQ11_2_MORT                     ((uint32_t)0x00400000)        /*!<Bit 2 */
#define  ADC_SQR2_SQ11_3_MORT                     ((uint32_t)0x00800000)        /*!<Bit 3 */
#define  ADC_SQR2_SQ11_4_MORT                     ((uint32_t)0x01000000)        /*!<Bit 4 */
#define  ADC_SQR2_SQ12_MORT                       ((uint32_t)0x3E000000)        /*!<SQ12[4:0] bits (12th conversion in regular sequence) */
#define  ADC_SQR2_SQ12_0_MORT                     ((uint32_t)0x02000000)        /*!<Bit 0 */
#define  ADC_SQR2_SQ12_1_MORT                     ((uint32_t)0x04000000)        /*!<Bit 1 */
#define  ADC_SQR2_SQ12_2_MORT                     ((uint32_t)0x08000000)        /*!<Bit 2 */
#define  ADC_SQR2_SQ12_3_MORT                     ((uint32_t)0x10000000)        /*!<Bit 3 */
#define  ADC_SQR2_SQ12_4_MORT                     ((uint32_t)0x20000000)        /*!<Bit 4 */

/*******************  Bit definition for ADC_SQR3 register  *******************/
#define  ADC_SQR3_SQ1_MORT                        ((uint32_t)0x0000001F)        /*!<SQ1[4:0] bits (1st conversion in regular sequence) */
#define  ADC_SQR3_SQ1_0_MORT                      ((uint32_t)0x00000001)        /*!<Bit 0 */
#define  ADC_SQR3_SQ1_1_MORT                      ((uint32_t)0x00000002)        /*!<Bit 1 */
#define  ADC_SQR3_SQ1_2_MORT                      ((uint32_t)0x00000004)        /*!<Bit 2 */
#define  ADC_SQR3_SQ1_3_MORT                      ((uint32_t)0x00000008)        /*!<Bit 3 */
#define  ADC_SQR3_SQ1_4_MORT                      ((uint32_t)0x00000010)        /*!<Bit 4 */
#define  ADC_SQR3_SQ2_MORT                        ((uint32_t)0x000003E0)        /*!<SQ2[4:0] bits (2nd conversion in regular sequence) */
#define  ADC_SQR3_SQ2_0_MORT                      ((uint32_t)0x00000020)        /*!<Bit 0 */
#define  ADC_SQR3_SQ2_1_MORT                      ((uint32_t)0x00000040)        /*!<Bit 1 */
#define  ADC_SQR3_SQ2_2_MORT                      ((uint32_t)0x00000080)        /*!<Bit 2 */
#define  ADC_SQR3_SQ2_3_MORT                      ((uint32_t)0x00000100)        /*!<Bit 3 */
#define  ADC_SQR3_SQ2_4_MORT                      ((uint32_t)0x00000200)        /*!<Bit 4 */
#define  ADC_SQR3_SQ3_MORT                        ((uint32_t)0x00007C00)        /*!<SQ3[4:0] bits (3rd conversion in regular sequence) */
#define  ADC_SQR3_SQ3_0_MORT                      ((uint32_t)0x00000400)        /*!<Bit 0 */
#define  ADC_SQR3_SQ3_1_MORT                      ((uint32_t)0x00000800)        /*!<Bit 1 */
#define  ADC_SQR3_SQ3_2_MORT                      ((uint32_t)0x00001000)        /*!<Bit 2 */
#define  ADC_SQR3_SQ3_3_MORT                      ((uint32_t)0x00002000)        /*!<Bit 3 */
#define  ADC_SQR3_SQ3_4_MORT                      ((uint32_t)0x00004000)        /*!<Bit 4 */
#define  ADC_SQR3_SQ4_MORT                        ((uint32_t)0x000F8000)        /*!<SQ4[4:0] bits (4th conversion in regular sequence) */
#define  ADC_SQR3_SQ4_0_MORT                      ((uint32_t)0x00008000)        /*!<Bit 0 */
#define  ADC_SQR3_SQ4_1_MORT                      ((uint32_t)0x00010000)        /*!<Bit 1 */
#define  ADC_SQR3_SQ4_2_MORT                      ((uint32_t)0x00020000)        /*!<Bit 2 */
#define  ADC_SQR3_SQ4_3_MORT                      ((uint32_t)0x00040000)        /*!<Bit 3 */
#define  ADC_SQR3_SQ4_4_MORT                      ((uint32_t)0x00080000)        /*!<Bit 4 */
#define  ADC_SQR3_SQ5_MORT                        ((uint32_t)0x01F00000)        /*!<SQ5[4:0] bits (5th conversion in regular sequence) */
#define  ADC_SQR3_SQ5_0_MORT                      ((uint32_t)0x00100000)        /*!<Bit 0 */
#define  ADC_SQR3_SQ5_1_MORT                      ((uint32_t)0x00200000)        /*!<Bit 1 */
#define  ADC_SQR3_SQ5_2_MORT                      ((uint32_t)0x00400000)        /*!<Bit 2 */
#define  ADC_SQR3_SQ5_3_MORT                      ((uint32_t)0x00800000)        /*!<Bit 3 */
#define  ADC_SQR3_SQ5_4_MORT                      ((uint32_t)0x01000000)        /*!<Bit 4 */
#define  ADC_SQR3_SQ6_MORT                        ((uint32_t)0x3E000000)        /*!<SQ6[4:0] bits (6th conversion in regular sequence) */
#define  ADC_SQR3_SQ6_0_MORT                      ((uint32_t)0x02000000)        /*!<Bit 0 */
#define  ADC_SQR3_SQ6_1_MORT                      ((uint32_t)0x04000000)        /*!<Bit 1 */
#define  ADC_SQR3_SQ6_2_MORT                      ((uint32_t)0x08000000)        /*!<Bit 2 */
#define  ADC_SQR3_SQ6_3_MORT                      ((uint32_t)0x10000000)        /*!<Bit 3 */
#define  ADC_SQR3_SQ6_4_MORT                      ((uint32_t)0x20000000)        /*!<Bit 4 */

/*******************  Bit definition for ADC_JSQR register  *******************/
#define  ADC_JSQR_JSQ1_MORT                       ((uint32_t)0x0000001F)        /*!<JSQ1[4:0] bits (1st conversion in injected sequence) */  
#define  ADC_JSQR_JSQ1_0_MORT                     ((uint32_t)0x00000001)        /*!<Bit 0 */
#define  ADC_JSQR_JSQ1_1_MORT                     ((uint32_t)0x00000002)        /*!<Bit 1 */
#define  ADC_JSQR_JSQ1_2_MORT                     ((uint32_t)0x00000004)        /*!<Bit 2 */
#define  ADC_JSQR_JSQ1_3_MORT                     ((uint32_t)0x00000008)        /*!<Bit 3 */
#define  ADC_JSQR_JSQ1_4_MORT                     ((uint32_t)0x00000010)        /*!<Bit 4 */
#define  ADC_JSQR_JSQ2_MORT                       ((uint32_t)0x000003E0)        /*!<JSQ2[4:0] bits (2nd conversion in injected sequence) */
#define  ADC_JSQR_JSQ2_0_MORT                     ((uint32_t)0x00000020)        /*!<Bit 0 */
#define  ADC_JSQR_JSQ2_1_MORT                     ((uint32_t)0x00000040)        /*!<Bit 1 */
#define  ADC_JSQR_JSQ2_2_MORT                     ((uint32_t)0x00000080)        /*!<Bit 2 */
#define  ADC_JSQR_JSQ2_3_MORT                     ((uint32_t)0x00000100)        /*!<Bit 3 */
#define  ADC_JSQR_JSQ2_4_MORT                     ((uint32_t)0x00000200)        /*!<Bit 4 */
#define  ADC_JSQR_JSQ3_MORT                       ((uint32_t)0x00007C00)        /*!<JSQ3[4:0] bits (3rd conversion in injected sequence) */
#define  ADC_JSQR_JSQ3_0_MORT                     ((uint32_t)0x00000400)        /*!<Bit 0 */
#define  ADC_JSQR_JSQ3_1_MORT                     ((uint32_t)0x00000800)        /*!<Bit 1 */
#define  ADC_JSQR_JSQ3_2_MORT                     ((uint32_t)0x00001000)        /*!<Bit 2 */
#define  ADC_JSQR_JSQ3_3_MORT                     ((uint32_t)0x00002000)        /*!<Bit 3 */
#define  ADC_JSQR_JSQ3_4_MORT                     ((uint32_t)0x00004000)        /*!<Bit 4 */
#define  ADC_JSQR_JSQ4_MORT                       ((uint32_t)0x000F8000)        /*!<JSQ4[4:0] bits (4th conversion in injected sequence) */
#define  ADC_JSQR_JSQ4_0_MORT                     ((uint32_t)0x00008000)        /*!<Bit 0 */
#define  ADC_JSQR_JSQ4_1_MORT                     ((uint32_t)0x00010000)        /*!<Bit 1 */
#define  ADC_JSQR_JSQ4_2_MORT                     ((uint32_t)0x00020000)        /*!<Bit 2 */
#define  ADC_JSQR_JSQ4_3_MORT                     ((uint32_t)0x00040000)        /*!<Bit 3 */
#define  ADC_JSQR_JSQ4_4_MORT                     ((uint32_t)0x00080000)        /*!<Bit 4 */
#define  ADC_JSQR_JL_MORT                         ((uint32_t)0x00300000)        /*!<JL[1:0] bits (Injected Sequence length) */
#define  ADC_JSQR_JL_0_MORT                       ((uint32_t)0x00100000)        /*!<Bit 0 */
#define  ADC_JSQR_JL_1_MORT                       ((uint32_t)0x00200000)        /*!<Bit 1 */

/*******************  Bit definition for ADC_JDR1 register  *******************/
#define  ADC_JDR1_JDATA_MORT                      ((uint16_t)0xFFFF)            /*!<Injected data */

/*******************  Bit definition for ADC_JDR2 register  *******************/
#define  ADC_JDR2_JDATA_MORT                      ((uint16_t)0xFFFF)            /*!<Injected data */

/*******************  Bit definition for ADC_JDR3 register  *******************/
#define  ADC_JDR3_JDATA_MORT                      ((uint16_t)0xFFFF)            /*!<Injected data */

/*******************  Bit definition for ADC_JDR4 register  *******************/
#define  ADC_JDR4_JDATA_MORT                      ((uint16_t)0xFFFF)            /*!<Injected data */

/********************  Bit definition for ADC_DR register  ********************/
#define  ADC_DR_DATA_MORT                         ((uint32_t)0x0000FFFF)        /*!<Regular data */
#define  ADC_DR_ADC2DATA_MORT                     ((uint32_t)0xFFFF0000)        /*!<ADC2_MORT data */

/*******************  Bit definition for ADC_CSR register  ********************/
#define  ADC_CSR_AWD1_MORT                        ((uint32_t)0x00000001)        /*!<ADC1_MORT Analog watchdog flag */
#define  ADC_CSR_EOC1_MORT                        ((uint32_t)0x00000002)        /*!<ADC1_MORT End of conversion */
#define  ADC_CSR_JEOC1_MORT                       ((uint32_t)0x00000004)        /*!<ADC1_MORT Injected channel end of conversion */
#define  ADC_CSR_JSTRT1_MORT                      ((uint32_t)0x00000008)        /*!<ADC1_MORT Injected channel Start flag */
#define  ADC_CSR_STRT1_MORT                       ((uint32_t)0x00000010)        /*!<ADC1_MORT Regular channel Start flag */
#define  ADC_CSR_OVR1_MORT                        ((uint32_t)0x00000020)        /*!<ADC1_MORT DMA overrun  flag */
#define  ADC_CSR_AWD2_MORT                        ((uint32_t)0x00000100)        /*!<ADC2_MORT Analog watchdog flag */
#define  ADC_CSR_EOC2_MORT                        ((uint32_t)0x00000200)        /*!<ADC2_MORT End of conversion */
#define  ADC_CSR_JEOC2_MORT                       ((uint32_t)0x00000400)        /*!<ADC2_MORT Injected channel end of conversion */
#define  ADC_CSR_JSTRT2_MORT                      ((uint32_t)0x00000800)        /*!<ADC2_MORT Injected channel Start flag */
#define  ADC_CSR_STRT2_MORT                       ((uint32_t)0x00001000)        /*!<ADC2_MORT Regular channel Start flag */
#define  ADC_CSR_OVR2_MORT                        ((uint32_t)0x00002000)        /*!<ADC2_MORT DMA overrun  flag */
#define  ADC_CSR_AWD3_MORT                        ((uint32_t)0x00010000)        /*!<ADC3_MORT Analog watchdog flag */
#define  ADC_CSR_EOC3_MORT                        ((uint32_t)0x00020000)        /*!<ADC3_MORT End of conversion */
#define  ADC_CSR_JEOC3_MORT                       ((uint32_t)0x00040000)        /*!<ADC3_MORT Injected channel end of conversion */
#define  ADC_CSR_JSTRT3_MORT                      ((uint32_t)0x00080000)        /*!<ADC3_MORT Injected channel Start flag */
#define  ADC_CSR_STRT3_MORT                       ((uint32_t)0x00100000)        /*!<ADC3_MORT Regular channel Start flag */
#define  ADC_CSR_OVR3_MORT                        ((uint32_t)0x00200000)        /*!<ADC3_MORT DMA overrun  flag */

/* Legacy defines */
#define  ADC_CSR_DOVR1_MORT                        ADC_CSR_OVR1_MORT
#define  ADC_CSR_DOVR2_MORT                        ADC_CSR_OVR2_MORT
#define  ADC_CSR_DOVR3_MORT                        ADC_CSR_OVR3_MORT

/*******************  Bit definition for ADC_CCR register  ********************/
#define  ADC_CCR_MULTI_MORT                       ((uint32_t)0x0000001F)        /*!<MULTI[4:0] bits (Multi-ADC_MORT mode selection) */  
#define  ADC_CCR_MULTI_0_MORT                     ((uint32_t)0x00000001)        /*!<Bit 0 */
#define  ADC_CCR_MULTI_1_MORT                     ((uint32_t)0x00000002)        /*!<Bit 1 */
#define  ADC_CCR_MULTI_2_MORT                     ((uint32_t)0x00000004)        /*!<Bit 2 */
#define  ADC_CCR_MULTI_3_MORT                     ((uint32_t)0x00000008)        /*!<Bit 3 */
#define  ADC_CCR_MULTI_4_MORT                     ((uint32_t)0x00000010)        /*!<Bit 4 */
#define  ADC_CCR_DELAY_MORT                       ((uint32_t)0x00000F00)        /*!<DELAY[3:0] bits (Delay between 2 sampling phases) */  
#define  ADC_CCR_DELAY_0_MORT                     ((uint32_t)0x00000100)        /*!<Bit 0 */
#define  ADC_CCR_DELAY_1_MORT                     ((uint32_t)0x00000200)        /*!<Bit 1 */
#define  ADC_CCR_DELAY_2_MORT                     ((uint32_t)0x00000400)        /*!<Bit 2 */
#define  ADC_CCR_DELAY_3_MORT                     ((uint32_t)0x00000800)        /*!<Bit 3 */
#define  ADC_CCR_DDS_MORT                         ((uint32_t)0x00002000)        /*!<DMA disable selection (Multi-ADC_MORT mode) */
#define  ADC_CCR_DMA_MORT                         ((uint32_t)0x0000C000)        /*!<DMA[1:0] bits (Direct Memory Access mode for multimode) */  
#define  ADC_CCR_DMA_0_MORT                       ((uint32_t)0x00004000)        /*!<Bit 0 */
#define  ADC_CCR_DMA_1_MORT                       ((uint32_t)0x00008000)        /*!<Bit 1 */
#define  ADC_CCR_ADCPRE_MORT                      ((uint32_t)0x00030000)        /*!<ADCPRE[1:0] bits (ADC_MORT prescaler) */  
#define  ADC_CCR_ADCPRE_0_MORT                    ((uint32_t)0x00010000)        /*!<Bit 0 */
#define  ADC_CCR_ADCPRE_1_MORT                    ((uint32_t)0x00020000)        /*!<Bit 1 */
#define  ADC_CCR_VBATE_MORT                       ((uint32_t)0x00400000)        /*!<VBAT Enable */
#define  ADC_CCR_TSVREFE_MORT                     ((uint32_t)0x00800000)        /*!<Temperature Sensor and VREFINT Enable */

/*******************  Bit definition for ADC_CDR register  ********************/
#define  ADC_CDR_DATA1_MORT                      ((uint32_t)0x0000FFFF)         /*!<1st data of a pair of regular conversions */
#define  ADC_CDR_DATA2_MORT                      ((uint32_t)0xFFFF0000)         /*!<2nd data of a pair of regular conversions */

/******************************************************************************/
/*                                                                            */
/*                         Controller Area Network                            */
/*                                                                            */
/******************************************************************************/
/*!<CAN control and status registers */
/*******************  Bit definition for CAN_MCR register  ********************/


/*******************  Bit definition for CAN_MSR register  ********************/


/*******************  Bit definition for CAN_TSR register  ********************/


/*******************  Bit definition for CAN_RF0R register  *******************/


/*******************  Bit definition for CAN_RF1R register  *******************/


/********************  Bit definition for CAN_IER register  *******************/


/********************  Bit definition for CAN_ESR register  *******************/

/*******************  Bit definition for CAN_BTR register  ********************/


/*!<Mailbox registers */
/******************  Bit definition for CAN_TI0R register  ********************/


/******************  Bit definition for CAN_TDT0R register  *******************/

/******************  Bit definition for CAN_TDL0R register  *******************/


/******************  Bit definition for CAN_TDH0R register  *******************/

/*******************  Bit definition for CAN_TI1R register  *******************/


/*******************  Bit definition for CAN_TDT1R register  ******************/


/*******************  Bit definition for CAN_TDL1R register  ******************/


/*******************  Bit definition for CAN_TDH1R register  ******************/


/*******************  Bit definition for CAN_TI2R register  *******************/

/*******************  Bit definition for CAN_TDT2R register  ******************/  


/*******************  Bit definition for CAN_TDL2R register  ******************/


/*******************  Bit definition for CAN_TDH2R register  ******************/


/*******************  Bit definition for CAN_RI0R register  *******************/


/*******************  Bit definition for CAN_RDT0R register  ******************/


/*******************  Bit definition for CAN_RDL0R register  ******************/


/*******************  Bit definition for CAN_RDH0R register  ******************/


/*******************  Bit definition for CAN_RI1R register  *******************/


/*******************  Bit definition for CAN_RDT1R register  ******************/


/*******************  Bit definition for CAN_RDL1R register  ******************/


/*******************  Bit definition for CAN_RDH1R register  ******************/


/*!<CAN filter registers */
/*******************  Bit definition for CAN_FMR register  ********************/


/*******************  Bit definition for CAN_FM1R register  *******************/


/*******************  Bit definition for CAN_FS1R register  *******************/


/******************  Bit definition for CAN_FFA1R register  *******************/


/*******************  Bit definition for CAN_FA1R register  *******************/


/*******************  Bit definition for CAN_F0R1 register  *******************/


/*******************  Bit definition for CAN_F1R1 register  *******************/


/*******************  Bit definition for CAN_F2R1 register  *******************/


/*******************  Bit definition for CAN_F3R1 register  *******************/


/*******************  Bit definition for CAN_F4R1 register  *******************/


/*******************  Bit definition for CAN_F5R1 register  *******************/


/*******************  Bit definition for CAN_F6R1 register  *******************/


/*******************  Bit definition for CAN_F7R1 register  *******************/


/*******************  Bit definition for CAN_F8R1 register  *******************/


/*******************  Bit definition for CAN_F9R1 register  *******************/


/*******************  Bit definition for CAN_F10R1 register  ******************/

/*******************  Bit definition for CAN_F11R1 register  ******************/


/*******************  Bit definition for CAN_F12R1 register  ******************/


/*******************  Bit definition for CAN_F13R1 register  ******************/


/*******************  Bit definition for CAN_F0R2 register  *******************/


/*******************  Bit definition for CAN_F1R2 register  *******************/


/*******************  Bit definition for CAN_F2R2 register  *******************/


/*******************  Bit definition for CAN_F3R2 register  *******************/

/*******************  Bit definition for CAN_F4R2 register  *******************/


/*******************  Bit definition for CAN_F5R2 register  *******************/

/*******************  Bit definition for CAN_F6R2 register  *******************/


/*******************  Bit definition for CAN_F7R2 register  *******************/


/*******************  Bit definition for CAN_F8R2 register  *******************/


/*******************  Bit definition for CAN_F9R2 register  *******************/

/*******************  Bit definition for CAN_F10R2 register  ******************/

/*******************  Bit definition for CAN_F11R2 register  ******************/


/*******************  Bit definition for CAN_F12R2 register  ******************/


/*******************  Bit definition for CAN_F13R2 register  ******************/



#if defined(STM32F446xx_MORT)
/******************************************************************************/
/*                                                                            */
/*                          HDMI-CEC_MORT (CEC_MORT)                                    */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for CEC_CR register  *********************/
#define  CEC_CR_CECEN_MORT                        ((uint32_t)0x00000001)       /*!< CEC_MORT Enable                              */
#define  CEC_CR_TXSOM_MORT                        ((uint32_t)0x00000002)       /*!< CEC_MORT Tx Start Of Message                 */
#define  CEC_CR_TXEOM_MORT                        ((uint32_t)0x00000004)       /*!< CEC_MORT Tx End Of Message                   */

/*******************  Bit definition for CEC_CFGR register  *******************/
#define  CEC_CFGR_SFT_MORT                        ((uint32_t)0x00000007)       /*!< CEC_MORT Signal Free Time                    */
#define  CEC_CFGR_RXTOL_MORT                      ((uint32_t)0x00000008)       /*!< CEC_MORT Tolerance                           */
#define  CEC_CFGR_BRESTP_MORT                     ((uint32_t)0x00000010)       /*!< CEC_MORT Rx Stop                             */
#define  CEC_CFGR_BREGEN_MORT                     ((uint32_t)0x00000020)       /*!< CEC_MORT Bit Rising Error generation         */
#define  CEC_CFGR_LREGEN_MORT                     ((uint32_t)0x00000040)       /*!< CEC_MORT Long Period Error generation        */
#define  CEC_CFGR_SFTOPT_MORT                     ((uint32_t)0x00000100)       /*!< CEC_MORT Signal Free Time optional           */
#define  CEC_CFGR_BRDNOGEN_MORT                   ((uint32_t)0x00000080)       /*!< CEC_MORT Broadcast No error generation       */
#define  CEC_CFGR_OAR_MORT                        ((uint32_t)0x7FFF0000)       /*!< CEC_MORT Own Address                         */
#define  CEC_CFGR_LSTN_MORT                       ((uint32_t)0x80000000)       /*!< CEC_MORT Listen mode                         */

/*******************  Bit definition for CEC_TXDR register  *******************/
#define  CEC_TXDR_TXD_MORT                        ((uint32_t)0x000000FF)       /*!< CEC_MORT Tx Data                              */

/*******************  Bit definition for CEC_RXDR register  *******************/
#define  CEC_TXDR_RXD_MORT                        ((uint32_t)0x000000FF)       /*!< CEC_MORT Rx Data                              */

/*******************  Bit definition for CEC_ISR register  ********************/
#define  CEC_ISR_RXBR_MORT                        ((uint32_t)0x00000001)       /*!< CEC_MORT Rx-Byte Received                      */
#define  CEC_ISR_RXEND_MORT                       ((uint32_t)0x00000002)       /*!< CEC_MORT End Of Reception                      */
#define  CEC_ISR_RXOVR_MORT                       ((uint32_t)0x00000004)       /*!< CEC_MORT Rx-Overrun                            */
#define  CEC_ISR_BRE_MORT                         ((uint32_t)0x00000008)       /*!< CEC_MORT Rx Bit Rising Error                   */
#define  CEC_ISR_SBPE_MORT                        ((uint32_t)0x00000010)       /*!< CEC_MORT Rx Short Bit period Error             */
#define  CEC_ISR_LBPE_MORT                        ((uint32_t)0x00000020)       /*!< CEC_MORT Rx Long Bit period Error              */
#define  CEC_ISR_RXACKE_MORT                      ((uint32_t)0x00000040)       /*!< CEC_MORT Rx Missing Acknowledge                */
#define  CEC_ISR_ARBLST_MORT                      ((uint32_t)0x00000080)       /*!< CEC_MORT Arbitration Lost                      */
#define  CEC_ISR_TXBR_MORT                        ((uint32_t)0x00000100)       /*!< CEC_MORT Tx Byte Request                       */
#define  CEC_ISR_TXEND_MORT                       ((uint32_t)0x00000200)       /*!< CEC_MORT End of Transmission                   */
#define  CEC_ISR_TXUDR_MORT                       ((uint32_t)0x00000400)       /*!< CEC_MORT Tx-Buffer Underrun                    */
#define  CEC_ISR_TXERR_MORT                       ((uint32_t)0x00000800)       /*!< CEC_MORT Tx-Error                              */
#define  CEC_ISR_TXACKE_MORT                      ((uint32_t)0x00001000)       /*!< CEC_MORT Tx Missing Acknowledge                */

/*******************  Bit definition for CEC_IER register  ********************/
#define  CEC_IER_RXBRIE_MORT                      ((uint32_t)0x00000001)       /*!< CEC_MORT Rx-Byte Received IT Enable            */
#define  CEC_IER_RXENDIE_MORT                     ((uint32_t)0x00000002)       /*!< CEC_MORT End Of Reception IT Enable            */
#define  CEC_IER_RXOVRIE_MORT                     ((uint32_t)0x00000004)       /*!< CEC_MORT Rx-Overrun IT Enable                  */
#define  CEC_IER_BREIEIE_MORT                     ((uint32_t)0x00000008)       /*!< CEC_MORT Rx Bit Rising Error IT Enable         */
#define  CEC_IER_SBPEIE_MORT                      ((uint32_t)0x00000010)       /*!< CEC_MORT Rx Short Bit period Error IT Enable   */
#define  CEC_IER_LBPEIE_MORT                      ((uint32_t)0x00000020)       /*!< CEC_MORT Rx Long Bit period Error IT Enable    */
#define  CEC_IER_RXACKEIE_MORT                    ((uint32_t)0x00000040)       /*!< CEC_MORT Rx Missing Acknowledge IT Enable      */
#define  CEC_IER_ARBLSTIE_MORT                    ((uint32_t)0x00000080)       /*!< CEC_MORT Arbitration Lost IT Enable            */
#define  CEC_IER_TXBRIE_MORT                      ((uint32_t)0x00000100)       /*!< CEC_MORT Tx Byte Request  IT Enable            */
#define  CEC_IER_TXENDIE_MORT                     ((uint32_t)0x00000200)       /*!< CEC_MORT End of Transmission IT Enable         */
#define  CEC_IER_TXUDRIE_MORT                     ((uint32_t)0x00000400)       /*!< CEC_MORT Tx-Buffer Underrun IT Enable          */
#define  CEC_IER_TXERRIE_MORT                     ((uint32_t)0x00000800)       /*!< CEC_MORT Tx-Error IT Enable                    */
#define  CEC_IER_TXACKEIE_MORT                    ((uint32_t)0x00001000)       /*!< CEC_MORT Tx Missing Acknowledge IT Enable      */
#endif /* STM32F446xx_MORT */

/******************************************************************************/
/*                                                                            */
/*                          CRC_MORT calculation unit                              */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for CRC_DR register  *********************/
#define  CRC_DR_DR_MORT                           ((uint32_t)0xFFFFFFFF) /*!< Data register bits */


/*******************  Bit definition for CRC_IDR register  ********************/
#define  CRC_IDR_IDR_MORT                         ((uint8_t)0xFF)        /*!< General-purpose 8-bit data register bits */


/********************  Bit definition for CRC_CR register  ********************/
#define  CRC_CR_RESET_MORT                        ((uint8_t)0x01)        /*!< RESET bit */

/******************************************************************************/
/*                                                                            */
/*                            Crypto Processor                                */
/*                                                                            */
/******************************************************************************/
/******************* Bits definition for CRYP_CR register  ********************/


/****************** Bits definition for CRYP_SR register  *********************/

/****************** Bits definition for CRYP_DMACR register  ******************/

/*****************  Bits definition for CRYP_IMSCR register  ******************/

/****************** Bits definition for CRYP_RISR register  *******************/

/****************** Bits definition for CRYP_MISR register  *******************/

/******************************************************************************/
/*                                                                            */
/*                      Digital to Analog Converter                           */
/*                                                                            */
/******************************************************************************/
/********************  Bit definition for DAC_CR register  ********************/
#define  DAC_CR_EN1_MORT                          ((uint32_t)0x00000001)        /*!<DAC_MORT channel1 enable */
#define  DAC_CR_BOFF1_MORT                        ((uint32_t)0x00000002)        /*!<DAC_MORT channel1 output buffer disable */
#define  DAC_CR_TEN1_MORT                         ((uint32_t)0x00000004)        /*!<DAC_MORT channel1 Trigger enable */

#define  DAC_CR_TSEL1_MORT                        ((uint32_t)0x00000038)        /*!<TSEL1[2:0] (DAC_MORT channel1 Trigger selection) */
#define  DAC_CR_TSEL1_0_MORT                      ((uint32_t)0x00000008)        /*!<Bit 0 */
#define  DAC_CR_TSEL1_1_MORT                      ((uint32_t)0x00000010)        /*!<Bit 1 */
#define  DAC_CR_TSEL1_2_MORT                      ((uint32_t)0x00000020)        /*!<Bit 2 */

#define  DAC_CR_WAVE1_MORT                        ((uint32_t)0x000000C0)        /*!<WAVE1[1:0] (DAC_MORT channel1 noise/triangle wave generation enable) */
#define  DAC_CR_WAVE1_0_MORT                      ((uint32_t)0x00000040)        /*!<Bit 0 */
#define  DAC_CR_WAVE1_1_MORT                      ((uint32_t)0x00000080)        /*!<Bit 1 */

#define  DAC_CR_MAMP1_MORT                        ((uint32_t)0x00000F00)        /*!<MAMP1[3:0] (DAC_MORT channel1 Mask/Amplitude selector) */
#define  DAC_CR_MAMP1_0_MORT                      ((uint32_t)0x00000100)        /*!<Bit 0 */
#define  DAC_CR_MAMP1_1_MORT                      ((uint32_t)0x00000200)        /*!<Bit 1 */
#define  DAC_CR_MAMP1_2_MORT                      ((uint32_t)0x00000400)        /*!<Bit 2 */
#define  DAC_CR_MAMP1_3_MORT                      ((uint32_t)0x00000800)        /*!<Bit 3 */

#define  DAC_CR_DMAEN1_MORT                       ((uint32_t)0x00001000)        /*!<DAC_MORT channel1 DMA enable */
#define  DAC_CR_DMAUDRIE1_MORT                    ((uint32_t)0x00002000)        /*!<DAC_MORT channel1 DMA underrun interrupt enable*/
#define  DAC_CR_EN2_MORT                          ((uint32_t)0x00010000)        /*!<DAC_MORT channel2 enable */
#define  DAC_CR_BOFF2_MORT                        ((uint32_t)0x00020000)        /*!<DAC_MORT channel2 output buffer disable */
#define  DAC_CR_TEN2_MORT                         ((uint32_t)0x00040000)        /*!<DAC_MORT channel2 Trigger enable */

#define  DAC_CR_TSEL2_MORT                        ((uint32_t)0x00380000)        /*!<TSEL2[2:0] (DAC_MORT channel2 Trigger selection) */
#define  DAC_CR_TSEL2_0_MORT                      ((uint32_t)0x00080000)        /*!<Bit 0 */
#define  DAC_CR_TSEL2_1_MORT                      ((uint32_t)0x00100000)        /*!<Bit 1 */
#define  DAC_CR_TSEL2_2_MORT                      ((uint32_t)0x00200000)        /*!<Bit 2 */

#define  DAC_CR_WAVE2_MORT                        ((uint32_t)0x00C00000)        /*!<WAVE2[1:0] (DAC_MORT channel2 noise/triangle wave generation enable) */
#define  DAC_CR_WAVE2_0_MORT                      ((uint32_t)0x00400000)        /*!<Bit 0 */
#define  DAC_CR_WAVE2_1_MORT                      ((uint32_t)0x00800000)        /*!<Bit 1 */

#define  DAC_CR_MAMP2_MORT                        ((uint32_t)0x0F000000)        /*!<MAMP2[3:0] (DAC_MORT channel2 Mask/Amplitude selector) */
#define  DAC_CR_MAMP2_0_MORT                      ((uint32_t)0x01000000)        /*!<Bit 0 */
#define  DAC_CR_MAMP2_1_MORT                      ((uint32_t)0x02000000)        /*!<Bit 1 */
#define  DAC_CR_MAMP2_2_MORT                      ((uint32_t)0x04000000)        /*!<Bit 2 */
#define  DAC_CR_MAMP2_3_MORT                      ((uint32_t)0x08000000)        /*!<Bit 3 */

#define  DAC_CR_DMAEN2_MORT                       ((uint32_t)0x10000000)        /*!<DAC_MORT channel2 DMA enabled */
#define  DAC_CR_DMAUDRIE2_MORT                    ((uint32_t)0x20000000U)        /*!<DAC_MORT channel2 DMA underrun interrupt enable*/

/*****************  Bit definition for DAC_SWTRIGR register  ******************/
#define  DAC_SWTRIGR_SWTRIG1_MORT                 ((uint8_t)0x01)               /*!<DAC_MORT channel1 software trigger */
#define  DAC_SWTRIGR_SWTRIG2_MORT                 ((uint8_t)0x02)               /*!<DAC_MORT channel2 software trigger */

/*****************  Bit definition for DAC_DHR12R1 register  ******************/
#define  DAC_DHR12R1_DACC1DHR_MORT                ((uint16_t)0x0FFF)            /*!<DAC_MORT channel1 12-bit Right aligned data */

/*****************  Bit definition for DAC_DHR12L1 register  ******************/
#define  DAC_DHR12L1_DACC1DHR_MORT                ((uint16_t)0xFFF0)            /*!<DAC_MORT channel1 12-bit Left aligned data */

/******************  Bit definition for DAC_DHR8R1 register  ******************/
#define  DAC_DHR8R1_DACC1DHR_MORT                 ((uint8_t)0xFF)               /*!<DAC_MORT channel1 8-bit Right aligned data */

/*****************  Bit definition for DAC_DHR12R2 register  ******************/
#define  DAC_DHR12R2_DACC2DHR_MORT                ((uint16_t)0x0FFF)            /*!<DAC_MORT channel2 12-bit Right aligned data */

/*****************  Bit definition for DAC_DHR12L2 register  ******************/
#define  DAC_DHR12L2_DACC2DHR_MORT                ((uint16_t)0xFFF0)            /*!<DAC_MORT channel2 12-bit Left aligned data */

/******************  Bit definition for DAC_DHR8R2 register  ******************/
#define  DAC_DHR8R2_DACC2DHR_MORT                 ((uint8_t)0xFF)               /*!<DAC_MORT channel2 8-bit Right aligned data */

/*****************  Bit definition for DAC_DHR12RD register  ******************/
#define  DAC_DHR12RD_DACC1DHR_MORT                ((uint32_t)0x00000FFF)        /*!<DAC_MORT channel1 12-bit Right aligned data */
#define  DAC_DHR12RD_DACC2DHR_MORT                ((uint32_t)0x0FFF0000)        /*!<DAC_MORT channel2 12-bit Right aligned data */

/*****************  Bit definition for DAC_DHR12LD register  ******************/
#define  DAC_DHR12LD_DACC1DHR_MORT                ((uint32_t)0x0000FFF0)        /*!<DAC_MORT channel1 12-bit Left aligned data */
#define  DAC_DHR12LD_DACC2DHR_MORT                ((uint32_t)0xFFF00000)        /*!<DAC_MORT channel2 12-bit Left aligned data */

/******************  Bit definition for DAC_DHR8RD register  ******************/
#define  DAC_DHR8RD_DACC1DHR_MORT                 ((uint16_t)0x00FF)            /*!<DAC_MORT channel1 8-bit Right aligned data */
#define  DAC_DHR8RD_DACC2DHR_MORT                 ((uint16_t)0xFF00)            /*!<DAC_MORT channel2 8-bit Right aligned data */

/*******************  Bit definition for DAC_DOR1 register  *******************/
#define  DAC_DOR1_DACC1DOR_MORT                   ((uint16_t)0x0FFF)            /*!<DAC_MORT channel1 data output */

/*******************  Bit definition for DAC_DOR2 register  *******************/
#define  DAC_DOR2_DACC2DOR_MORT                   ((uint16_t)0x0FFF)            /*!<DAC_MORT channel2 data output */

/********************  Bit definition for DAC_SR register  ********************/
#define  DAC_SR_DMAUDR1_MORT                      ((uint32_t)0x00002000)        /*!<DAC_MORT channel1 DMA underrun flag */
#define  DAC_SR_DMAUDR2_MORT                      ((uint32_t)0x20000000)        /*!<DAC_MORT channel2 DMA underrun flag */

/******************************************************************************/
/*                                                                            */
/*                                 Debug MCU                                  */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/*                                                                            */
/*                                    DCMI_MORT                                    */
/*                                                                            */
/******************************************************************************/
/********************  Bits definition for DCMI_CR register  ******************/


/********************  Bits definition for DCMI_SR register  ******************/


/********************  Bits definition for DCMI_RIS register  *****************/

/* Legacy defines */


/********************  Bits definition for DCMI_IER register  *****************/


/* Legacy defines */


/********************  Bits definition for DCMI_MIS register  ****************/


/* Legacy defines */


/********************  Bits definition for DCMI_ICR register  *****************/


/* Legacy defines */

/********************  Bits definition for DCMI_ESCR register  ******************/


/********************  Bits definition for DCMI_ESUR register  ******************/


/********************  Bits definition for DCMI_CWSTRT register  ******************/


/********************  Bits definition for DCMI_CWSIZE register  ******************/


/********************  Bits definition for DCMI_DR register  ******************/


/******************************************************************************/
/*                                                                            */
/*                 Digital Filter for Sigma Delta Modulators                  */
/*                                                                            */
/******************************************************************************/

/****************   DFSDM channel configuration registers  ********************/

/***************  Bit definition for DFSDM_CHCFGR1 register  ******************/

/***************  Bit definition for DFSDM_CHCFGR2 register  ******************/

/******************  Bit definition for DFSDM_CHAWSCDR register ***************/

/****************  Bit definition for DFSDM_CHWDATR register *******************/

/****************  Bit definition for DFSDM_CHDATINR register *****************/

/************************   DFSDM module registers  ****************************/

/*****************  Bit definition for DFSDM_FLTCR1 register *******************/

/********************  Bit definition for DFSDM_FLTCR2 register ***************/

/*****************  Bit definition for DFSDM_FLTISR register *******************/

/*****************  Bit definition for DFSDM_FLTICR register *******************/

/****************  Bit definition for DFSDM_FLTJCHGR register ******************/

/*****************  Bit definition for DFSDM_FLTFCR register *******************/

/***************  Bit definition for DFSDM_FLTJDATAR register *****************/

/***************  Bit definition for DFSDM_FLTRDATAR register *****************/

/***************  Bit definition for DFSDM_FLTAWHTR register ******************/

/***************  Bit definition for DFSDM_FLTAWLTR register ******************/

/***************  Bit definition for DFSDM_FLTAWSR register *******************/

/***************  Bit definition for DFSDM_FLTAWCFR register ******************/

/***************  Bit definition for DFSDM_FLTEXMAX register ******************/

/***************  Bit definition for DFSDM_FLTEXMIN register ******************/

/***************  Bit definition for DFSDM_FLTCNVTIMR register ****************/

/******************************************************************************/
/*                                                                            */
/*                             DMA Controller                                 */
/*                                                                            */
/******************************************************************************/
/********************  Bits definition for DMA_SxCR register  *****************/ 
#define DMA_SxCR_CHSEL_MORT                       ((uint32_t)0x0E000000)
#define DMA_SxCR_CHSEL_0_MORT                     ((uint32_t)0x02000000)
#define DMA_SxCR_CHSEL_1_MORT                     ((uint32_t)0x04000000)
#define DMA_SxCR_CHSEL_2_MORT                     ((uint32_t)0x08000000) 
#define DMA_SxCR_MBURST_MORT                      ((uint32_t)0x01800000)
#define DMA_SxCR_MBURST_0_MORT                    ((uint32_t)0x00800000)
#define DMA_SxCR_MBURST_1_MORT                    ((uint32_t)0x01000000)
#define DMA_SxCR_PBURST_MORT                      ((uint32_t)0x00600000)
#define DMA_SxCR_PBURST_0_MORT                    ((uint32_t)0x00200000)
#define DMA_SxCR_PBURST_1_MORT                    ((uint32_t)0x00400000)
#define DMA_SxCR_ACK_MORT                         ((uint32_t)0x00100000)
#define DMA_SxCR_CT_MORT                          ((uint32_t)0x00080000)  
#define DMA_SxCR_DBM_MORT                         ((uint32_t)0x00040000)
#define DMA_SxCR_PL_MORT                          ((uint32_t)0x00030000)
#define DMA_SxCR_PL_0_MORT                        ((uint32_t)0x00010000)
#define DMA_SxCR_PL_1_MORT                        ((uint32_t)0x00020000)
#define DMA_SxCR_PINCOS_MORT                      ((uint32_t)0x00008000)
#define DMA_SxCR_MSIZE_MORT                       ((uint32_t)0x00006000)
#define DMA_SxCR_MSIZE_0_MORT                     ((uint32_t)0x00002000)
#define DMA_SxCR_MSIZE_1_MORT                     ((uint32_t)0x00004000)
#define DMA_SxCR_PSIZE_MORT                       ((uint32_t)0x00001800)
#define DMA_SxCR_PSIZE_0_MORT                     ((uint32_t)0x00000800)
#define DMA_SxCR_PSIZE_1_MORT                     ((uint32_t)0x00001000)
#define DMA_SxCR_MINC_MORT                        ((uint32_t)0x00000400)
#define DMA_SxCR_PINC_MORT                        ((uint32_t)0x00000200)
#define DMA_SxCR_CIRC_MORT                        ((uint32_t)0x00000100)
#define DMA_SxCR_DIR_MORT                         ((uint32_t)0x000000C0)
#define DMA_SxCR_DIR_0_MORT                       ((uint32_t)0x00000040)
#define DMA_SxCR_DIR_1_MORT                       ((uint32_t)0x00000080)
#define DMA_SxCR_PFCTRL_MORT                      ((uint32_t)0x00000020)
#define DMA_SxCR_TCIE_MORT                        ((uint32_t)0x00000010)
#define DMA_SxCR_HTIE_MORT                        ((uint32_t)0x00000008)
#define DMA_SxCR_TEIE_MORT                        ((uint32_t)0x00000004)
#define DMA_SxCR_DMEIE_MORT                       ((uint32_t)0x00000002)
#define DMA_SxCR_EN_MORT                          ((uint32_t)0x00000001)

/********************  Bits definition for DMA_SxCNDTR register  **************/
#define DMA_SxNDT_MORT                            ((uint32_t)0x0000FFFF)
#define DMA_SxNDT_0_MORT                          ((uint32_t)0x00000001)
#define DMA_SxNDT_1_MORT                          ((uint32_t)0x00000002)
#define DMA_SxNDT_2_MORT                          ((uint32_t)0x00000004)
#define DMA_SxNDT_3_MORT                          ((uint32_t)0x00000008)
#define DMA_SxNDT_4_MORT                          ((uint32_t)0x00000010)
#define DMA_SxNDT_5_MORT                          ((uint32_t)0x00000020)
#define DMA_SxNDT_6_MORT                          ((uint32_t)0x00000040)
#define DMA_SxNDT_7_MORT                          ((uint32_t)0x00000080)
#define DMA_SxNDT_8_MORT                          ((uint32_t)0x00000100)
#define DMA_SxNDT_9_MORT                          ((uint32_t)0x00000200)
#define DMA_SxNDT_10_MORT                         ((uint32_t)0x00000400)
#define DMA_SxNDT_11_MORT                         ((uint32_t)0x00000800)
#define DMA_SxNDT_12_MORT                         ((uint32_t)0x00001000)
#define DMA_SxNDT_13_MORT                         ((uint32_t)0x00002000)
#define DMA_SxNDT_14_MORT                         ((uint32_t)0x00004000)
#define DMA_SxNDT_15_MORT                         ((uint32_t)0x00008000)

/********************  Bits definition for DMA_SxFCR register  ****************/ 
#define DMA_SxFCR_FEIE_MORT                       ((uint32_t)0x00000080)
#define DMA_SxFCR_FS_MORT                         ((uint32_t)0x00000038)
#define DMA_SxFCR_FS_0_MORT                       ((uint32_t)0x00000008)
#define DMA_SxFCR_FS_1_MORT                       ((uint32_t)0x00000010)
#define DMA_SxFCR_FS_2_MORT                       ((uint32_t)0x00000020)
#define DMA_SxFCR_DMDIS_MORT                      ((uint32_t)0x00000004)
#define DMA_SxFCR_FTH_MORT                        ((uint32_t)0x00000003)
#define DMA_SxFCR_FTH_0_MORT                      ((uint32_t)0x00000001)
#define DMA_SxFCR_FTH_1_MORT                      ((uint32_t)0x00000002)

/********************  Bits definition for DMA_LISR register  *****************/ 
#define DMA_LISR_TCIF3_MORT                       ((uint32_t)0x08000000)
#define DMA_LISR_HTIF3_MORT                       ((uint32_t)0x04000000)
#define DMA_LISR_TEIF3_MORT                       ((uint32_t)0x02000000)
#define DMA_LISR_DMEIF3_MORT                      ((uint32_t)0x01000000)
#define DMA_LISR_FEIF3_MORT                       ((uint32_t)0x00400000)
#define DMA_LISR_TCIF2_MORT                       ((uint32_t)0x00200000)
#define DMA_LISR_HTIF2_MORT                       ((uint32_t)0x00100000)
#define DMA_LISR_TEIF2_MORT                       ((uint32_t)0x00080000)
#define DMA_LISR_DMEIF2_MORT                      ((uint32_t)0x00040000)
#define DMA_LISR_FEIF2_MORT                       ((uint32_t)0x00010000)
#define DMA_LISR_TCIF1_MORT                       ((uint32_t)0x00000800)
#define DMA_LISR_HTIF1_MORT                       ((uint32_t)0x00000400)
#define DMA_LISR_TEIF1_MORT                       ((uint32_t)0x00000200)
#define DMA_LISR_DMEIF1_MORT                      ((uint32_t)0x00000100)
#define DMA_LISR_FEIF1_MORT                       ((uint32_t)0x00000040)
#define DMA_LISR_TCIF0_MORT                       ((uint32_t)0x00000020)
#define DMA_LISR_HTIF0_MORT                       ((uint32_t)0x00000010)
#define DMA_LISR_TEIF0_MORT                       ((uint32_t)0x00000008)
#define DMA_LISR_DMEIF0_MORT                      ((uint32_t)0x00000004)
#define DMA_LISR_FEIF0_MORT                       ((uint32_t)0x00000001)

/********************  Bits definition for DMA_HISR register  *****************/ 
#define DMA_HISR_TCIF7_MORT                       ((uint32_t)0x08000000)
#define DMA_HISR_HTIF7_MORT                       ((uint32_t)0x04000000)
#define DMA_HISR_TEIF7_MORT                       ((uint32_t)0x02000000)
#define DMA_HISR_DMEIF7_MORT                      ((uint32_t)0x01000000)
#define DMA_HISR_FEIF7_MORT                       ((uint32_t)0x00400000)
#define DMA_HISR_TCIF6_MORT                       ((uint32_t)0x00200000)
#define DMA_HISR_HTIF6_MORT                       ((uint32_t)0x00100000)
#define DMA_HISR_TEIF6_MORT                       ((uint32_t)0x00080000)
#define DMA_HISR_DMEIF6_MORT                      ((uint32_t)0x00040000)
#define DMA_HISR_FEIF6_MORT                       ((uint32_t)0x00010000)
#define DMA_HISR_TCIF5_MORT                       ((uint32_t)0x00000800)
#define DMA_HISR_HTIF5_MORT                       ((uint32_t)0x00000400)
#define DMA_HISR_TEIF5_MORT                       ((uint32_t)0x00000200)
#define DMA_HISR_DMEIF5_MORT                      ((uint32_t)0x00000100)
#define DMA_HISR_FEIF5_MORT                       ((uint32_t)0x00000040)
#define DMA_HISR_TCIF4_MORT                       ((uint32_t)0x00000020)
#define DMA_HISR_HTIF4_MORT                       ((uint32_t)0x00000010)
#define DMA_HISR_TEIF4_MORT                       ((uint32_t)0x00000008)
#define DMA_HISR_DMEIF4_MORT                      ((uint32_t)0x00000004)
#define DMA_HISR_FEIF4_MORT                       ((uint32_t)0x00000001)

/********************  Bits definition for DMA_LIFCR register  ****************/ 
#define DMA_LIFCR_CTCIF3_MORT                     ((uint32_t)0x08000000)
#define DMA_LIFCR_CHTIF3_MORT                     ((uint32_t)0x04000000)
#define DMA_LIFCR_CTEIF3_MORT                     ((uint32_t)0x02000000)
#define DMA_LIFCR_CDMEIF3_MORT                    ((uint32_t)0x01000000)
#define DMA_LIFCR_CFEIF3_MORT                     ((uint32_t)0x00400000)
#define DMA_LIFCR_CTCIF2_MORT                     ((uint32_t)0x00200000)
#define DMA_LIFCR_CHTIF2_MORT                     ((uint32_t)0x00100000)
#define DMA_LIFCR_CTEIF2_MORT                     ((uint32_t)0x00080000)
#define DMA_LIFCR_CDMEIF2_MORT                    ((uint32_t)0x00040000)
#define DMA_LIFCR_CFEIF2_MORT                     ((uint32_t)0x00010000)
#define DMA_LIFCR_CTCIF1_MORT                     ((uint32_t)0x00000800)
#define DMA_LIFCR_CHTIF1_MORT                     ((uint32_t)0x00000400)
#define DMA_LIFCR_CTEIF1_MORT                     ((uint32_t)0x00000200)
#define DMA_LIFCR_CDMEIF1_MORT                    ((uint32_t)0x00000100)
#define DMA_LIFCR_CFEIF1_MORT                     ((uint32_t)0x00000040)
#define DMA_LIFCR_CTCIF0_MORT                     ((uint32_t)0x00000020)
#define DMA_LIFCR_CHTIF0_MORT                     ((uint32_t)0x00000010)
#define DMA_LIFCR_CTEIF0_MORT                     ((uint32_t)0x00000008)
#define DMA_LIFCR_CDMEIF0_MORT                    ((uint32_t)0x00000004)
#define DMA_LIFCR_CFEIF0_MORT                     ((uint32_t)0x00000001)

/********************  Bits definition for DMA_HIFCR  register  ****************/ 
#define DMA_HIFCR_CTCIF7_MORT                     ((uint32_t)0x08000000)
#define DMA_HIFCR_CHTIF7_MORT                     ((uint32_t)0x04000000)
#define DMA_HIFCR_CTEIF7_MORT                     ((uint32_t)0x02000000)
#define DMA_HIFCR_CDMEIF7_MORT                    ((uint32_t)0x01000000)
#define DMA_HIFCR_CFEIF7_MORT                     ((uint32_t)0x00400000)
#define DMA_HIFCR_CTCIF6_MORT                     ((uint32_t)0x00200000)
#define DMA_HIFCR_CHTIF6_MORT                     ((uint32_t)0x00100000)
#define DMA_HIFCR_CTEIF6_MORT                     ((uint32_t)0x00080000)
#define DMA_HIFCR_CDMEIF6_MORT                    ((uint32_t)0x00040000)
#define DMA_HIFCR_CFEIF6_MORT                     ((uint32_t)0x00010000)
#define DMA_HIFCR_CTCIF5_MORT                     ((uint32_t)0x00000800)
#define DMA_HIFCR_CHTIF5_MORT                     ((uint32_t)0x00000400)
#define DMA_HIFCR_CTEIF5_MORT                     ((uint32_t)0x00000200)
#define DMA_HIFCR_CDMEIF5_MORT                    ((uint32_t)0x00000100)
#define DMA_HIFCR_CFEIF5_MORT                     ((uint32_t)0x00000040)
#define DMA_HIFCR_CTCIF4_MORT                     ((uint32_t)0x00000020)
#define DMA_HIFCR_CHTIF4_MORT                     ((uint32_t)0x00000010)
#define DMA_HIFCR_CTEIF4_MORT                     ((uint32_t)0x00000008)
#define DMA_HIFCR_CDMEIF4_MORT                    ((uint32_t)0x00000004)
#define DMA_HIFCR_CFEIF4_MORT                     ((uint32_t)0x00000001)

/******************************************************************************/
/*                                                                            */
/*                         AHB Master DMA2D_MORT Controller (DMA2D_MORT)                */
/*                                                                            */
/******************************************************************************/

/********************  Bit definition for DMA2D_CR register  ******************/

#define DMA2D_CR_START_MORT                     ((uint32_t)0x00000001)               /*!< Start transfer */
#define DMA2D_CR_SUSP_MORT                      ((uint32_t)0x00000002)               /*!< Suspend transfer */
#define DMA2D_CR_ABORT_MORT                     ((uint32_t)0x00000004)               /*!< Abort transfer */
#define DMA2D_CR_TEIE_MORT                      ((uint32_t)0x00000100)               /*!< Transfer Error Interrupt Enable */
#define DMA2D_CR_TCIE_MORT                      ((uint32_t)0x00000200)               /*!< Transfer Complete Interrupt Enable */
#define DMA2D_CR_TWIE_MORT                      ((uint32_t)0x00000400)               /*!< Transfer Watermark Interrupt Enable */
#define DMA2D_CR_CAEIE_MORT                     ((uint32_t)0x00000800)               /*!< CLUT Access Error Interrupt Enable */
#define DMA2D_CR_CTCIE_MORT                     ((uint32_t)0x00001000)               /*!< CLUT Transfer Complete Interrupt Enable */
#define DMA2D_CR_CEIE_MORT                      ((uint32_t)0x00002000)               /*!< Configuration Error Interrupt Enable */
#define DMA2D_CR_MODE_MORT                      ((uint32_t)0x00030000)               /*!< DMA2D_MORT Mode */

/********************  Bit definition for DMA2D_ISR register  *****************/

#define DMA2D_ISR_TEIF_MORT                     ((uint32_t)0x00000001)               /*!< Transfer Error Interrupt Flag */
#define DMA2D_ISR_TCIF_MORT                     ((uint32_t)0x00000002)               /*!< Transfer Complete Interrupt Flag */
#define DMA2D_ISR_TWIF_MORT                     ((uint32_t)0x00000004)               /*!< Transfer Watermark Interrupt Flag */
#define DMA2D_ISR_CAEIF_MORT                    ((uint32_t)0x00000008)               /*!< CLUT Access Error Interrupt Flag */
#define DMA2D_ISR_CTCIF_MORT                    ((uint32_t)0x00000010)               /*!< CLUT Transfer Complete Interrupt Flag */
#define DMA2D_ISR_CEIF_MORT                     ((uint32_t)0x00000020)               /*!< Configuration Error Interrupt Flag */

/********************  Bit definition for DMA2D_IFCR register  ****************/

#define DMA2D_IFCR_CTEIF_MORT                   ((uint32_t)0x00000001)               /*!< Clears Transfer Error Interrupt Flag         */
#define DMA2D_IFCR_CTCIF_MORT                   ((uint32_t)0x00000002)               /*!< Clears Transfer Complete Interrupt Flag      */
#define DMA2D_IFCR_CTWIF_MORT                   ((uint32_t)0x00000004)               /*!< Clears Transfer Watermark Interrupt Flag     */
#define DMA2D_IFCR_CAECIF_MORT                  ((uint32_t)0x00000008)               /*!< Clears CLUT Access Error Interrupt Flag      */
#define DMA2D_IFCR_CCTCIF_MORT                  ((uint32_t)0x00000010)               /*!< Clears CLUT Transfer Complete Interrupt Flag */
#define DMA2D_IFCR_CCEIF_MORT                   ((uint32_t)0x00000020)               /*!< Clears Configuration Error Interrupt Flag    */

/* Legacy defines */
#define DMA2D_IFSR_CTEIF                   DMA2D_IFCR_CTEIF_MORT                     /*!< Clears Transfer Error Interrupt Flag         */
#define DMA2D_IFSR_CTCIF                   DMA2D_IFCR_CTCIF_MORT                     /*!< Clears Transfer Complete Interrupt Flag      */
#define DMA2D_IFSR_CTWIF                   DMA2D_IFCR_CTWIF_MORT                     /*!< Clears Transfer Watermark Interrupt Flag     */
#define DMA2D_IFSR_CCAEIF                  DMA2D_IFCR_CAECIF_MORT                    /*!< Clears CLUT Access Error Interrupt Flag      */
#define DMA2D_IFSR_CCTCIF                  DMA2D_IFCR_CCTCIF_MORT                    /*!< Clears CLUT Transfer Complete Interrupt Flag */
#define DMA2D_IFSR_CCEIF                   DMA2D_IFCR_CCEIF_MORT                     /*!< Clears Configuration Error Interrupt Flag    */

/********************  Bit definition for DMA2D_FGMAR register  ***************/

#define DMA2D_FGMAR_MA_MORT                     ((uint32_t)0xFFFFFFFF)               /*!< Memory Address */

/********************  Bit definition for DMA2D_FGOR register  ****************/

#define DMA2D_FGOR_LO_MORT                      ((uint32_t)0x00003FFF)               /*!< Line Offset */

/********************  Bit definition for DMA2D_BGMAR register  ***************/

#define DMA2D_BGMAR_MA_MORT                     ((uint32_t)0xFFFFFFFF)               /*!< Memory Address */

/********************  Bit definition for DMA2D_BGOR register  ****************/

#define DMA2D_BGOR_LO_MORT                      ((uint32_t)0x00003FFF)               /*!< Line Offset */

/********************  Bit definition for DMA2D_FGPFCCR register  *************/

#define DMA2D_FGPFCCR_CM_MORT                   ((uint32_t)0x0000000F)               /*!< Input color mode CM[3:0] */
#define DMA2D_FGPFCCR_CM_0_MORT                 ((uint32_t)0x00000001)               /*!< Input color mode CM bit 0 */
#define DMA2D_FGPFCCR_CM_1_MORT                 ((uint32_t)0x00000002)               /*!< Input color mode CM bit 1 */
#define DMA2D_FGPFCCR_CM_2_MORT                 ((uint32_t)0x00000004)               /*!< Input color mode CM bit 2 */
#define DMA2D_FGPFCCR_CM_3_MORT                 ((uint32_t)0x00000008)               /*!< Input color mode CM bit 3 */
#define DMA2D_FGPFCCR_CCM_MORT                  ((uint32_t)0x00000010)               /*!< CLUT Color mode */
#define DMA2D_FGPFCCR_START_MORT                ((uint32_t)0x00000020)               /*!< Start */
#define DMA2D_FGPFCCR_CS_MORT                   ((uint32_t)0x0000FF00)               /*!< CLUT size */
#define DMA2D_FGPFCCR_AM_MORT                   ((uint32_t)0x00030000)               /*!< Alpha mode AM[1:0] */
#define DMA2D_FGPFCCR_AM_0_MORT                 ((uint32_t)0x00010000)               /*!< Alpha mode AM bit 0 */
#define DMA2D_FGPFCCR_AM_1_MORT                 ((uint32_t)0x00020000)               /*!< Alpha mode AM bit 1 */
#define DMA2D_FGPFCCR_ALPHA_MORT                ((uint32_t)0xFF000000)               /*!< Alpha value */

/********************  Bit definition for DMA2D_FGCOLR register  **************/

#define DMA2D_FGCOLR_BLUE_MORT                  ((uint32_t)0x000000FF)               /*!< Blue Value */
#define DMA2D_FGCOLR_GREEN_MORT                 ((uint32_t)0x0000FF00)               /*!< Green Value */
#define DMA2D_FGCOLR_RED_MORT                   ((uint32_t)0x00FF0000)               /*!< Red Value */   

/********************  Bit definition for DMA2D_BGPFCCR register  *************/

#define DMA2D_BGPFCCR_CM_MORT                   ((uint32_t)0x0000000F)               /*!< Input color mode CM[3:0] */
#define DMA2D_BGPFCCR_CM_0_MORT                 ((uint32_t)0x00000001)               /*!< Input color mode CM bit 0 */
#define DMA2D_BGPFCCR_CM_1_MORT                 ((uint32_t)0x00000002)               /*!< Input color mode CM bit 1 */
#define DMA2D_BGPFCCR_CM_2_MORT                 ((uint32_t)0x00000004)               /*!< Input color mode CM bit 2 */
#define DMA2D_FGPFCCR_CM_3_MORT                 ((uint32_t)0x00000008)               /*!< Input color mode CM bit 3 */
#define DMA2D_BGPFCCR_CCM_MORT                  ((uint32_t)0x00000010)               /*!< CLUT Color mode */
#define DMA2D_BGPFCCR_START_MORT                ((uint32_t)0x00000020)               /*!< Start */
#define DMA2D_BGPFCCR_CS_MORT                   ((uint32_t)0x0000FF00)               /*!< CLUT size */
#define DMA2D_BGPFCCR_AM_MORT                   ((uint32_t)0x00030000)               /*!< Alpha mode AM[1:0] */
#define DMA2D_BGPFCCR_AM_0_MORT                 ((uint32_t)0x00010000)               /*!< Alpha mode AM bit 0 */
#define DMA2D_BGPFCCR_AM_1_MORT                 ((uint32_t)0x00020000)               /*!< Alpha mode AM bit 1 */
#define DMA2D_BGPFCCR_ALPHA_MORT                ((uint32_t)0xFF000000)               /*!< Alpha value */

/********************  Bit definition for DMA2D_BGCOLR register  **************/

#define DMA2D_BGCOLR_BLUE_MORT                  ((uint32_t)0x000000FF)               /*!< Blue Value */
#define DMA2D_BGCOLR_GREEN_MORT                 ((uint32_t)0x0000FF00)               /*!< Green Value */
#define DMA2D_BGCOLR_RED_MORT                   ((uint32_t)0x00FF0000)               /*!< Red Value */

/********************  Bit definition for DMA2D_FGCMAR register  **************/

#define DMA2D_FGCMAR_MA_MORT                    ((uint32_t)0xFFFFFFFF)               /*!< Memory Address */

/********************  Bit definition for DMA2D_BGCMAR register  **************/

#define DMA2D_BGCMAR_MA_MORT                    ((uint32_t)0xFFFFFFFF)               /*!< Memory Address */

/********************  Bit definition for DMA2D_OPFCCR register  **************/

#define DMA2D_OPFCCR_CM_MORT                    ((uint32_t)0x00000007)               /*!< Color mode CM[2:0] */
#define DMA2D_OPFCCR_CM_0_MORT                  ((uint32_t)0x00000001)               /*!< Color mode CM bit 0 */
#define DMA2D_OPFCCR_CM_1_MORT                  ((uint32_t)0x00000002)               /*!< Color mode CM bit 1 */
#define DMA2D_OPFCCR_CM_2_MORT                  ((uint32_t)0x00000004)               /*!< Color mode CM bit 2 */

/********************  Bit definition for DMA2D_OCOLR register  ***************/

/*!<Mode_ARGB8888/RGB888 */

#define DMA2D_OCOLR_BLUE_1_MORT                 ((uint32_t)0x000000FF)               /*!< BLUE Value */
#define DMA2D_OCOLR_GREEN_1_MORT                ((uint32_t)0x0000FF00)               /*!< GREEN Value  */
#define DMA2D_OCOLR_RED_1_MORT                  ((uint32_t)0x00FF0000)               /*!< Red Value */
#define DMA2D_OCOLR_ALPHA_1                ((uint32_t)0xFF000000)               /*!< Alpha Channel Value */

/*!<Mode_RGB565 */
#define DMA2D_OCOLR_BLUE_2_MORT                 ((uint32_t)0x0000001F)               /*!< BLUE Value */
#define DMA2D_OCOLR_GREEN_2_MORT                ((uint32_t)0x000007E0)               /*!< GREEN Value  */
#define DMA2D_OCOLR_RED_2_MORT                  ((uint32_t)0x0000F800)               /*!< Red Value */

/*!<Mode_ARGB1555 */
#define DMA2D_OCOLR_BLUE_3_MORT                 ((uint32_t)0x0000001F)               /*!< BLUE Value */
#define DMA2D_OCOLR_GREEN_3_MORT                ((uint32_t)0x000003E0)               /*!< GREEN Value  */
#define DMA2D_OCOLR_RED_3_MORT                  ((uint32_t)0x00007C00)               /*!< Red Value */
#define DMA2D_OCOLR_ALPHA_3_MORT                ((uint32_t)0x00008000)               /*!< Alpha Channel Value */

/*!<Mode_ARGB4444 */
#define DMA2D_OCOLR_BLUE_4_MORT                 ((uint32_t)0x0000000F)               /*!< BLUE Value */
#define DMA2D_OCOLR_GREEN_4_MORT                ((uint32_t)0x000000F0)               /*!< GREEN Value  */
#define DMA2D_OCOLR_RED_4_MORT                  ((uint32_t)0x00000F00)               /*!< Red Value */
#define DMA2D_OCOLR_ALPHA_4_MORT                ((uint32_t)0x0000F000)               /*!< Alpha Channel Value */

/********************  Bit definition for DMA2D_OMAR register  ****************/

#define DMA2D_OMAR_MA_MORT                      ((uint32_t)0xFFFFFFFF)               /*!< Memory Address */

/********************  Bit definition for DMA2D_OOR register  *****************/

#define DMA2D_OOR_LO_MORT                       ((uint32_t)0x00003FFF)               /*!< Line Offset */

/********************  Bit definition for DMA2D_NLR register  *****************/

#define DMA2D_NLR_NL_MORT                       ((uint32_t)0x0000FFFF)               /*!< Number of Lines */
#define DMA2D_NLR_PL_MORT                       ((uint32_t)0x3FFF0000)               /*!< Pixel per Lines */

/********************  Bit definition for DMA2D_LWR register  *****************/

#define DMA2D_LWR_LW_MORT                       ((uint32_t)0x0000FFFF)               /*!< Line Watermark */

/********************  Bit definition for DMA2D_AMTCR register  ***************/

#define DMA2D_AMTCR_EN_MORT                     ((uint32_t)0x00000001)               /*!< Enable */
#define DMA2D_AMTCR_DT_MORT                     ((uint32_t)0x0000FF00)               /*!< Dead Time */



/********************  Bit definition for DMA2D_FGCLUT register  **************/
                                                                     
/********************  Bit definition for DMA2D_BGCLUT register  **************/


/******************************************************************************/
/*                                                                            */
/*                    External Interrupt/Event Controller                     */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for EXTI_IMR register  *******************/
#define  EXTI_IMR_MR0_MORT                        ((uint32_t)0x00000001)        /*!< Interrupt Mask on line 0 */
#define  EXTI_IMR_MR1_MORT                        ((uint32_t)0x00000002)        /*!< Interrupt Mask on line 1 */
#define  EXTI_IMR_MR2_MORT                        ((uint32_t)0x00000004)        /*!< Interrupt Mask on line 2 */
#define  EXTI_IMR_MR3_MORT                        ((uint32_t)0x00000008)        /*!< Interrupt Mask on line 3 */
#define  EXTI_IMR_MR4_MORT                        ((uint32_t)0x00000010)        /*!< Interrupt Mask on line 4 */
#define  EXTI_IMR_MR5_MORT                        ((uint32_t)0x00000020)        /*!< Interrupt Mask on line 5 */
#define  EXTI_IMR_MR6_MORT                        ((uint32_t)0x00000040)        /*!< Interrupt Mask on line 6 */
#define  EXTI_IMR_MR7_MORT                        ((uint32_t)0x00000080)        /*!< Interrupt Mask on line 7 */
#define  EXTI_IMR_MR8_MORT                        ((uint32_t)0x00000100)        /*!< Interrupt Mask on line 8 */
#define  EXTI_IMR_MR9_MORT                        ((uint32_t)0x00000200)        /*!< Interrupt Mask on line 9 */
#define  EXTI_IMR_MR10_MORT                       ((uint32_t)0x00000400)        /*!< Interrupt Mask on line 10 */
#define  EXTI_IMR_MR11_MORT                       ((uint32_t)0x00000800)        /*!< Interrupt Mask on line 11 */
#define  EXTI_IMR_MR12_MORT                       ((uint32_t)0x00001000)        /*!< Interrupt Mask on line 12 */
#define  EXTI_IMR_MR13_MORT                       ((uint32_t)0x00002000)        /*!< Interrupt Mask on line 13 */
#define  EXTI_IMR_MR14_MORT                       ((uint32_t)0x00004000)        /*!< Interrupt Mask on line 14 */
#define  EXTI_IMR_MR15_MORT                       ((uint32_t)0x00008000)        /*!< Interrupt Mask on line 15 */
#define  EXTI_IMR_MR16_MORT                       ((uint32_t)0x00010000)        /*!< Interrupt Mask on line 16 */
#define  EXTI_IMR_MR17_MORT                       ((uint32_t)0x00020000)        /*!< Interrupt Mask on line 17 */
#define  EXTI_IMR_MR18_MORT                       ((uint32_t)0x00040000)        /*!< Interrupt Mask on line 18 */
#define  EXTI_IMR_MR19_MORT                       ((uint32_t)0x00080000)        /*!< Interrupt Mask on line 19 */
#define  EXTI_IMR_MR23_MORT                       ((uint32_t)0x00800000)        /*!< Interrupt Mask on line 23 */

/*******************  Bit definition for EXTI_EMR register  *******************/
#define  EXTI_EMR_MR0_MORT                        ((uint32_t)0x00000001)        /*!< Event Mask on line 0 */
#define  EXTI_EMR_MR1_MORT                        ((uint32_t)0x00000002)        /*!< Event Mask on line 1 */
#define  EXTI_EMR_MR2_MORT                        ((uint32_t)0x00000004)        /*!< Event Mask on line 2 */
#define  EXTI_EMR_MR3_MORT                        ((uint32_t)0x00000008)        /*!< Event Mask on line 3 */
#define  EXTI_EMR_MR4_MORT                        ((uint32_t)0x00000010)        /*!< Event Mask on line 4 */
#define  EXTI_EMR_MR5_MORT                        ((uint32_t)0x00000020)        /*!< Event Mask on line 5 */
#define  EXTI_EMR_MR6_MORT                        ((uint32_t)0x00000040)        /*!< Event Mask on line 6 */
#define  EXTI_EMR_MR7_MORT                        ((uint32_t)0x00000080)        /*!< Event Mask on line 7 */
#define  EXTI_EMR_MR8_MORT                        ((uint32_t)0x00000100)        /*!< Event Mask on line 8 */
#define  EXTI_EMR_MR9_MORT                        ((uint32_t)0x00000200)        /*!< Event Mask on line 9 */
#define  EXTI_EMR_MR10_MORT                       ((uint32_t)0x00000400)        /*!< Event Mask on line 10 */
#define  EXTI_EMR_MR11_MORT                       ((uint32_t)0x00000800)        /*!< Event Mask on line 11 */
#define  EXTI_EMR_MR12_MORT                       ((uint32_t)0x00001000)        /*!< Event Mask on line 12 */
#define  EXTI_EMR_MR13_MORT                       ((uint32_t)0x00002000)        /*!< Event Mask on line 13 */
#define  EXTI_EMR_MR14_MORT                       ((uint32_t)0x00004000)        /*!< Event Mask on line 14 */
#define  EXTI_EMR_MR15_MORT                       ((uint32_t)0x00008000)        /*!< Event Mask on line 15 */
#define  EXTI_EMR_MR16_MORT                       ((uint32_t)0x00010000)        /*!< Event Mask on line 16 */
#define  EXTI_EMR_MR17_MORT                       ((uint32_t)0x00020000)        /*!< Event Mask on line 17 */
#define  EXTI_EMR_MR18_MORT                       ((uint32_t)0x00040000)        /*!< Event Mask on line 18 */
#define  EXTI_EMR_MR19_MORT                       ((uint32_t)0x00080000)        /*!< Event Mask on line 19 */
#define  EXTI_EMR_MR23_MORT                       ((uint32_t)0x00800000)        /*!< Event Mask on line 19 */

/******************  Bit definition for EXTI_RTSR register  *******************/
#define  EXTI_RTSR_TR0_MORT                       ((uint32_t)0x00000001)        /*!< Rising trigger event configuration bit of line 0 */
#define  EXTI_RTSR_TR1_MORT                       ((uint32_t)0x00000002)        /*!< Rising trigger event configuration bit of line 1 */
#define  EXTI_RTSR_TR2_MORT                       ((uint32_t)0x00000004)        /*!< Rising trigger event configuration bit of line 2 */
#define  EXTI_RTSR_TR3_MORT                       ((uint32_t)0x00000008)        /*!< Rising trigger event configuration bit of line 3 */
#define  EXTI_RTSR_TR4_MORT                       ((uint32_t)0x00000010)        /*!< Rising trigger event configuration bit of line 4 */
#define  EXTI_RTSR_TR5_MORT                       ((uint32_t)0x00000020)        /*!< Rising trigger event configuration bit of line 5 */
#define  EXTI_RTSR_TR6_MORT                       ((uint32_t)0x00000040)        /*!< Rising trigger event configuration bit of line 6 */
#define  EXTI_RTSR_TR7_MORT                       ((uint32_t)0x00000080)        /*!< Rising trigger event configuration bit of line 7 */
#define  EXTI_RTSR_TR8_MORT                       ((uint32_t)0x00000100)        /*!< Rising trigger event configuration bit of line 8 */
#define  EXTI_RTSR_TR9_MORT                       ((uint32_t)0x00000200)        /*!< Rising trigger event configuration bit of line 9 */
#define  EXTI_RTSR_TR10_MORT                      ((uint32_t)0x00000400)        /*!< Rising trigger event configuration bit of line 10 */
#define  EXTI_RTSR_TR11_MORT                      ((uint32_t)0x00000800)        /*!< Rising trigger event configuration bit of line 11 */
#define  EXTI_RTSR_TR12_MORT                      ((uint32_t)0x00001000)        /*!< Rising trigger event configuration bit of line 12 */
#define  EXTI_RTSR_TR13_MORT                      ((uint32_t)0x00002000)        /*!< Rising trigger event configuration bit of line 13 */
#define  EXTI_RTSR_TR14_MORT                      ((uint32_t)0x00004000)        /*!< Rising trigger event configuration bit of line 14 */
#define  EXTI_RTSR_TR15_MORT                      ((uint32_t)0x00008000)        /*!< Rising trigger event configuration bit of line 15 */
#define  EXTI_RTSR_TR16_MORT                      ((uint32_t)0x00010000)        /*!< Rising trigger event configuration bit of line 16 */
#define  EXTI_RTSR_TR17_MORT                      ((uint32_t)0x00020000)        /*!< Rising trigger event configuration bit of line 17 */
#define  EXTI_RTSR_TR18_MORT                      ((uint32_t)0x00040000)        /*!< Rising trigger event configuration bit of line 18 */
#define  EXTI_RTSR_TR19_MORT                      ((uint32_t)0x00080000)        /*!< Rising trigger event configuration bit of line 19 */
#define  EXTI_RTSR_TR23_MORT                      ((uint32_t)0x00800000)        /*!< Rising trigger event configuration bit of line 23 */

/******************  Bit definition for EXTI_FTSR register  *******************/
#define  EXTI_FTSR_TR0_MORT                       ((uint32_t)0x00000001)        /*!< Falling trigger event configuration bit of line 0 */
#define  EXTI_FTSR_TR1_MORT                       ((uint32_t)0x00000002)        /*!< Falling trigger event configuration bit of line 1 */
#define  EXTI_FTSR_TR2_MORT                       ((uint32_t)0x00000004)        /*!< Falling trigger event configuration bit of line 2 */
#define  EXTI_FTSR_TR3_MORT                       ((uint32_t)0x00000008)        /*!< Falling trigger event configuration bit of line 3 */
#define  EXTI_FTSR_TR4_MORT                       ((uint32_t)0x00000010)        /*!< Falling trigger event configuration bit of line 4 */
#define  EXTI_FTSR_TR5_MORT                       ((uint32_t)0x00000020)        /*!< Falling trigger event configuration bit of line 5 */
#define  EXTI_FTSR_TR6_MORT                       ((uint32_t)0x00000040)        /*!< Falling trigger event configuration bit of line 6 */
#define  EXTI_FTSR_TR7_MORT                       ((uint32_t)0x00000080)        /*!< Falling trigger event configuration bit of line 7 */
#define  EXTI_FTSR_TR8_MORT                       ((uint32_t)0x00000100)        /*!< Falling trigger event configuration bit of line 8 */
#define  EXTI_FTSR_TR9_MORT                       ((uint32_t)0x00000200)        /*!< Falling trigger event configuration bit of line 9 */
#define  EXTI_FTSR_TR10_MORT                      ((uint32_t)0x00000400)        /*!< Falling trigger event configuration bit of line 10 */
#define  EXTI_FTSR_TR11_MORT                      ((uint32_t)0x00000800)        /*!< Falling trigger event configuration bit of line 11 */
#define  EXTI_FTSR_TR12_MORT                      ((uint32_t)0x00001000)        /*!< Falling trigger event configuration bit of line 12 */
#define  EXTI_FTSR_TR13_MORT                      ((uint32_t)0x00002000)        /*!< Falling trigger event configuration bit of line 13 */
#define  EXTI_FTSR_TR14_MORT                      ((uint32_t)0x00004000)        /*!< Falling trigger event configuration bit of line 14 */
#define  EXTI_FTSR_TR15_MORT                      ((uint32_t)0x00008000)        /*!< Falling trigger event configuration bit of line 15 */
#define  EXTI_FTSR_TR16_MORT                      ((uint32_t)0x00010000)        /*!< Falling trigger event configuration bit of line 16 */
#define  EXTI_FTSR_TR17_MORT                      ((uint32_t)0x00020000)        /*!< Falling trigger event configuration bit of line 17 */
#define  EXTI_FTSR_TR18_MORT                      ((uint32_t)0x00040000)        /*!< Falling trigger event configuration bit of line 18 */
#define  EXTI_FTSR_TR19_MORT                      ((uint32_t)0x00080000)        /*!< Falling trigger event configuration bit of line 19 */
#define  EXTI_FTSR_TR23_MORT                      ((uint32_t)0x00800000)        /*!< Falling trigger event configuration bit of line 23 */

/******************  Bit definition for EXTI_SWIER register  ******************/
#define  EXTI_SWIER_SWIER0_MORT                   ((uint32_t)0x00000001)        /*!< Software Interrupt on line 0 */
#define  EXTI_SWIER_SWIER1_MORT                   ((uint32_t)0x00000002)        /*!< Software Interrupt on line 1 */
#define  EXTI_SWIER_SWIER2_MORT                   ((uint32_t)0x00000004)        /*!< Software Interrupt on line 2 */
#define  EXTI_SWIER_SWIER3_MORT                   ((uint32_t)0x00000008)        /*!< Software Interrupt on line 3 */
#define  EXTI_SWIER_SWIER4_MORT                   ((uint32_t)0x00000010)        /*!< Software Interrupt on line 4 */
#define  EXTI_SWIER_SWIER5_MORT                   ((uint32_t)0x00000020)        /*!< Software Interrupt on line 5 */
#define  EXTI_SWIER_SWIER6_MORT                   ((uint32_t)0x00000040)        /*!< Software Interrupt on line 6 */
#define  EXTI_SWIER_SWIER7_MORT                   ((uint32_t)0x00000080)        /*!< Software Interrupt on line 7 */
#define  EXTI_SWIER_SWIER8_MORT                   ((uint32_t)0x00000100)        /*!< Software Interrupt on line 8 */
#define  EXTI_SWIER_SWIER9_MORT                   ((uint32_t)0x00000200)        /*!< Software Interrupt on line 9 */
#define  EXTI_SWIER_SWIER10_MORT                  ((uint32_t)0x00000400)        /*!< Software Interrupt on line 10 */
#define  EXTI_SWIER_SWIER11_MORT                  ((uint32_t)0x00000800)        /*!< Software Interrupt on line 11 */
#define  EXTI_SWIER_SWIER12_MORT                  ((uint32_t)0x00001000)        /*!< Software Interrupt on line 12 */
#define  EXTI_SWIER_SWIER13_MORT                  ((uint32_t)0x00002000)        /*!< Software Interrupt on line 13 */
#define  EXTI_SWIER_SWIER14_MORT                  ((uint32_t)0x00004000)        /*!< Software Interrupt on line 14 */
#define  EXTI_SWIER_SWIER15_MORT                  ((uint32_t)0x00008000)        /*!< Software Interrupt on line 15 */
#define  EXTI_SWIER_SWIER16_MORT                  ((uint32_t)0x00010000)        /*!< Software Interrupt on line 16 */
#define  EXTI_SWIER_SWIER17_MORT                  ((uint32_t)0x00020000)        /*!< Software Interrupt on line 17 */
#define  EXTI_SWIER_SWIER18_MORT                  ((uint32_t)0x00040000)        /*!< Software Interrupt on line 18 */
#define  EXTI_SWIER_SWIER19_MORT                  ((uint32_t)0x00080000)        /*!< Software Interrupt on line 19 */
#define  EXTI_SWIER_SWIER23_MORT                  ((uint32_t)0x00800000)        /*!< Software Interrupt on line 23 */

/*******************  Bit definition for EXTI_PR register  ********************/
#define  EXTI_PR_PR0_MORT                         ((uint32_t)0x00000001)        /*!< Pending bit for line 0 */
#define  EXTI_PR_PR1_MORT                         ((uint32_t)0x00000002)        /*!< Pending bit for line 1 */
#define  EXTI_PR_PR2_MORT                         ((uint32_t)0x00000004)        /*!< Pending bit for line 2 */
#define  EXTI_PR_PR3_MORT                         ((uint32_t)0x00000008)        /*!< Pending bit for line 3 */
#define  EXTI_PR_PR4_MORT                         ((uint32_t)0x00000010)        /*!< Pending bit for line 4 */
#define  EXTI_PR_PR5_MORT                         ((uint32_t)0x00000020)        /*!< Pending bit for line 5 */
#define  EXTI_PR_PR6_MORT                         ((uint32_t)0x00000040)        /*!< Pending bit for line 6 */
#define  EXTI_PR_PR7_MORT                         ((uint32_t)0x00000080)        /*!< Pending bit for line 7 */
#define  EXTI_PR_PR8_MORT                         ((uint32_t)0x00000100)        /*!< Pending bit for line 8 */
#define  EXTI_PR_PR9_MORT                         ((uint32_t)0x00000200)        /*!< Pending bit for line 9 */
#define  EXTI_PR_PR10_MORT                        ((uint32_t)0x00000400)        /*!< Pending bit for line 10 */
#define  EXTI_PR_PR11_MORT                        ((uint32_t)0x00000800)        /*!< Pending bit for line 11 */
#define  EXTI_PR_PR12_MORT                        ((uint32_t)0x00001000)        /*!< Pending bit for line 12 */
#define  EXTI_PR_PR13_MORT                        ((uint32_t)0x00002000)        /*!< Pending bit for line 13 */
#define  EXTI_PR_PR14_MORT                        ((uint32_t)0x00004000)        /*!< Pending bit for line 14 */
#define  EXTI_PR_PR15_MORT                        ((uint32_t)0x00008000)        /*!< Pending bit for line 15 */
#define  EXTI_PR_PR16_MORT                        ((uint32_t)0x00010000)        /*!< Pending bit for line 16 */
#define  EXTI_PR_PR17_MORT                        ((uint32_t)0x00020000)        /*!< Pending bit for line 17 */
#define  EXTI_PR_PR18_MORT                        ((uint32_t)0x00040000)        /*!< Pending bit for line 18 */
#define  EXTI_PR_PR19_MORT                        ((uint32_t)0x00080000)        /*!< Pending bit for line 19 */
#define  EXTI_PR_PR23_MORT                        ((uint32_t)0x00800000)        /*!< Pending bit for line 23 */

/******************************************************************************/
/*                                                                            */
/*                                    FLASH_MORT                                   */
/*                                                                            */
/******************************************************************************/
/*******************  Bits definition for FLASH_ACR register  *****************/

/*******************  Bits definition for FLASH_SR register  ******************/

/*******************  Bits definition for FLASH_CR register  ******************/

/*******************  Bits definition for FLASH_OPTCR register  ***************/

/******************  Bits definition for FLASH_OPTCR1 register  ***************/

#if defined(STM32F40_41xxx) || defined(STM32F412xG) || defined(STM32F413_423xx)
/******************************************************************************/
/*                                                                            */
/*                       Flexible Static Memory Controller                    */
/*                                                                            */
/******************************************************************************/
/******************  Bit definition for FSMC_BCR1 register  *******************/


/******************  Bit definition for FSMC_BCR2 register  *******************/


/******************  Bit definition for FSMC_BCR3 register  *******************/


/******************  Bit definition for FSMC_BCR4 register  *******************/


/******************  Bit definition for FSMC_BTR1 register  ******************/


/******************  Bit definition for FSMC_BTR2 register  *******************/


/*******************  Bit definition for FSMC_BTR3 register  *******************/



/******************  Bit definition for FSMC_BTR4 register  *******************/


/******************  Bit definition for FSMC_BWTR1 register  ******************/


/******************  Bit definition for FSMC_BWTR2 register  ******************/


/******************  Bit definition for FSMC_BWTR3 register  ******************/


/******************  Bit definition for FSMC_BWTR4 register  ******************/


/******************  Bit definition for FSMC_PCR2 register  *******************/


/******************  Bit definition for FSMC_PCR3 register  *******************/


/******************  Bit definition for FSMC_PCR4 register  *******************/


/*******************  Bit definition for FSMC_SR2 register  *******************/


/*******************  Bit definition for FSMC_SR3 register  *******************/


/*******************  Bit definition for FSMC_SR4 register  *******************/

/******************  Bit definition for FSMC_PMEM2 register  ******************/


/******************  Bit definition for FSMC_PMEM3 register  ******************/


/******************  Bit definition for FSMC_PMEM4 register  ******************/


/******************  Bit definition for FSMC_PATT2 register  ******************/


/******************  Bit definition for FSMC_PATT3 register  ******************/


/******************  Bit definition for FSMC_PATT4 register  ******************/

/******************  Bit definition for FSMC_PIO4 register  *******************/


/******************  Bit definition for FSMC_ECCR2 register  ******************/


/******************  Bit definition for FSMC_ECCR3 register  ******************/

#endif /* STM32F40_41xxx || STM32F412xG || STM32F413_423xx */

#if defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F446xx_MORT) || defined(STM32F469_479xx)
/******************************************************************************/
/*                                                                            */
/*                          Flexible Memory Controller                        */
/*                                                                            */
/******************************************************************************/
/******************  Bit definition for FMC_BCR1 register  *******************/

/******************  Bit definition for FMC_BCR2 register  *******************/

/******************  Bit definition for FMC_BCR3 register  *******************/

/******************  Bit definition for FMC_BCR4 register  *******************/

/******************  Bit definition for FMC_BTR1 register  ******************/


/******************  Bit definition for FMC_BTR2 register  *******************/


/*******************  Bit definition for FMC_BTR3 register  *******************/

/******************  Bit definition for FMC_BTR4 register  *******************/


/******************  Bit definition for FMC_BWTR1 register  ******************/

/******************  Bit definition for FMC_BWTR2 register  ******************/

/******************  Bit definition for FMC_BWTR3 register  ******************/

/******************  Bit definition for FMC_BWTR4 register  ******************/

/******************  Bit definition for FMC_PCR2 register  *******************/

/******************  Bit definition for FMC_PCR3 register  *******************/

/******************  Bit definition for FMC_PCR4 register  *******************/

/*******************  Bit definition for FMC_SR2 register  *******************/

/*******************  Bit definition for FMC_SR3 register  *******************/

/*******************  Bit definition for FMC_SR4 register  *******************/

/******************  Bit definition for FMC_PMEM2 register  ******************/


/******************  Bit definition for FMC_PMEM3 register  ******************/

/******************  Bit definition for FMC_PMEM4 register  ******************/

/******************  Bit definition for FMC_PATT2 register  ******************/

/******************  Bit definition for FMC_PATT3 register  ******************/

/******************  Bit definition for FMC_PATT4 register  ******************/

/******************  Bit definition for FMC_PIO4 register  *******************/

/******************  Bit definition for FMC_ECCR2 register  ******************/

/******************  Bit definition for FMC_ECCR3 register  ******************/

/******************  Bit definition for FMC_SDCR1 register  ******************/

/******************  Bit definition for FMC_SDCR2 register  ******************/

/******************  Bit definition for FMC_SDTR1 register  ******************/

/******************  Bit definition for FMC_SDTR2 register  ******************/

/******************  Bit definition for FMC_SDCMR register  ******************/

/******************  Bit definition for FMC_SDRTR register  ******************/

/******************  Bit definition for FMC_SDSR register  ******************/

#endif /* STM32F427_437xx ||  STM32F429_439xx || STM32F446xx_MORT || STM32F469_479xx */

/******************************************************************************/
/*                                                                            */
/*                            General Purpose I/O                             */
/*                                                                            */
/******************************************************************************/
/******************  Bits definition for GPIO_MODER register  *****************/
#define GPIO_MODER_MODER0_MORT                    ((uint32_t)0x00000003)
#define GPIO_MODER_MODER0_0_MORT                  ((uint32_t)0x00000001)
#define GPIO_MODER_MODER0_1_MORT                  ((uint32_t)0x00000002)

#define GPIO_MODER_MODER1_MORT                    ((uint32_t)0x0000000C)
#define GPIO_MODER_MODER1_0_MORT                  ((uint32_t)0x00000004)
#define GPIO_MODER_MODER1_1_MORT                  ((uint32_t)0x00000008)

#define GPIO_MODER_MODER2_MORT                    ((uint32_t)0x00000030)
#define GPIO_MODER_MODER2_0_MORT                  ((uint32_t)0x00000010)
#define GPIO_MODER_MODER2_1_MORT                  ((uint32_t)0x00000020)

#define GPIO_MODER_MODER3_MORT                    ((uint32_t)0x000000C0)
#define GPIO_MODER_MODER3_0_MORT                  ((uint32_t)0x00000040)
#define GPIO_MODER_MODER3_1_MORT                  ((uint32_t)0x00000080)

#define GPIO_MODER_MODER4_MORT                    ((uint32_t)0x00000300)
#define GPIO_MODER_MODER4_0_MORT                  ((uint32_t)0x00000100)
#define GPIO_MODER_MODER4_1_MORT                  ((uint32_t)0x00000200)

#define GPIO_MODER_MODER5_MORT                    ((uint32_t)0x00000C00)
#define GPIO_MODER_MODER5_0_MORT                  ((uint32_t)0x00000400)
#define GPIO_MODER_MODER5_1_MORT                  ((uint32_t)0x00000800)

#define GPIO_MODER_MODER6_MORT                    ((uint32_t)0x00003000)
#define GPIO_MODER_MODER6_0_MORT                  ((uint32_t)0x00001000)
#define GPIO_MODER_MODER6_1_MORT                  ((uint32_t)0x00002000)

#define GPIO_MODER_MODER7_MORT                    ((uint32_t)0x0000C000)
#define GPIO_MODER_MODER7_0_MORT                  ((uint32_t)0x00004000)
#define GPIO_MODER_MODER7_1_MORT                  ((uint32_t)0x00008000)

#define GPIO_MODER_MODER8_MORT                    ((uint32_t)0x00030000)
#define GPIO_MODER_MODER8_0_MORT                  ((uint32_t)0x00010000)
#define GPIO_MODER_MODER8_1_MORT                  ((uint32_t)0x00020000)

#define GPIO_MODER_MODER9_MORT                    ((uint32_t)0x000C0000)
#define GPIO_MODER_MODER9_0_MORT                  ((uint32_t)0x00040000)
#define GPIO_MODER_MODER9_1_MORT                  ((uint32_t)0x00080000)

#define GPIO_MODER_MODER10_MORT                   ((uint32_t)0x00300000)
#define GPIO_MODER_MODER10_0_MORT                 ((uint32_t)0x00100000)
#define GPIO_MODER_MODER10_1_MORT                 ((uint32_t)0x00200000)

#define GPIO_MODER_MODER11_MORT                   ((uint32_t)0x00C00000)
#define GPIO_MODER_MODER11_0_MORT                 ((uint32_t)0x00400000)
#define GPIO_MODER_MODER11_1_MORT                 ((uint32_t)0x00800000)

#define GPIO_MODER_MODER12_MORT                   ((uint32_t)0x03000000)
#define GPIO_MODER_MODER12_0_MORT                 ((uint32_t)0x01000000)
#define GPIO_MODER_MODER12_1_MORT                 ((uint32_t)0x02000000)

#define GPIO_MODER_MODER13_MORT                   ((uint32_t)0x0C000000)
#define GPIO_MODER_MODER13_0_MORT                 ((uint32_t)0x04000000)
#define GPIO_MODER_MODER13_1_MORT                 ((uint32_t)0x08000000)

#define GPIO_MODER_MODER14_MORT                   ((uint32_t)0x30000000)
#define GPIO_MODER_MODER14_0_MORT                 ((uint32_t)0x10000000)
#define GPIO_MODER_MODER14_1_MORT                 ((uint32_t)0x20000000)

#define GPIO_MODER_MODER15_MORT                   ((uint32_t)0xC0000000)
#define GPIO_MODER_MODER15_0_MORT                 ((uint32_t)0x40000000)
#define GPIO_MODER_MODER15_1_MORT                 ((uint32_t)0x80000000)

/******************  Bits definition for GPIO_OTYPER register  ****************/
#define GPIO_OTYPER_OT_0_MORT                     ((uint32_t)0x00000001)
#define GPIO_OTYPER_OT_1_MORT                     ((uint32_t)0x00000002)
#define GPIO_OTYPER_OT_2_MORT                     ((uint32_t)0x00000004)
#define GPIO_OTYPER_OT_3_MORT                     ((uint32_t)0x00000008)
#define GPIO_OTYPER_OT_4_MORT                     ((uint32_t)0x00000010)
#define GPIO_OTYPER_OT_5_MORT                     ((uint32_t)0x00000020)
#define GPIO_OTYPER_OT_6_MORT                     ((uint32_t)0x00000040)
#define GPIO_OTYPER_OT_7_MORT                     ((uint32_t)0x00000080)
#define GPIO_OTYPER_OT_8_MORT                     ((uint32_t)0x00000100)
#define GPIO_OTYPER_OT_9_MORT                     ((uint32_t)0x00000200)
#define GPIO_OTYPER_OT_10_MORT                    ((uint32_t)0x00000400)
#define GPIO_OTYPER_OT_11_MORT                    ((uint32_t)0x00000800)
#define GPIO_OTYPER_OT_12_MORT                    ((uint32_t)0x00001000)
#define GPIO_OTYPER_OT_13_MORT                    ((uint32_t)0x00002000)
#define GPIO_OTYPER_OT_14_MORT                    ((uint32_t)0x00004000)
#define GPIO_OTYPER_OT_15_MORT                    ((uint32_t)0x00008000)

/******************  Bits definition for GPIO_OSPEEDR register  ***************/
#define GPIO_OSPEEDER_OSPEEDR0_MORT               ((uint32_t)0x00000003)
#define GPIO_OSPEEDER_OSPEEDR0_0_MORT             ((uint32_t)0x00000001)
#define GPIO_OSPEEDER_OSPEEDR0_1_MORT             ((uint32_t)0x00000002)

#define GPIO_OSPEEDER_OSPEEDR1_MORT               ((uint32_t)0x0000000C)
#define GPIO_OSPEEDER_OSPEEDR1_0_MORT             ((uint32_t)0x00000004)
#define GPIO_OSPEEDER_OSPEEDR1_1_MORT             ((uint32_t)0x00000008)

#define GPIO_OSPEEDER_OSPEEDR2_MORT               ((uint32_t)0x00000030)
#define GPIO_OSPEEDER_OSPEEDR2_0_MORT             ((uint32_t)0x00000010)
#define GPIO_OSPEEDER_OSPEEDR2_1_MORT             ((uint32_t)0x00000020)

#define GPIO_OSPEEDER_OSPEEDR3_MORT               ((uint32_t)0x000000C0)
#define GPIO_OSPEEDER_OSPEEDR3_0_MORT             ((uint32_t)0x00000040)
#define GPIO_OSPEEDER_OSPEEDR3_1_MORT             ((uint32_t)0x00000080)

#define GPIO_OSPEEDER_OSPEEDR4_MORT               ((uint32_t)0x00000300)
#define GPIO_OSPEEDER_OSPEEDR4_0_MORT             ((uint32_t)0x00000100)
#define GPIO_OSPEEDER_OSPEEDR4_1_MORT             ((uint32_t)0x00000200)

#define GPIO_OSPEEDER_OSPEEDR5_MORT               ((uint32_t)0x00000C00)
#define GPIO_OSPEEDER_OSPEEDR5_0_MORT             ((uint32_t)0x00000400)
#define GPIO_OSPEEDER_OSPEEDR5_1_MORT             ((uint32_t)0x00000800)

#define GPIO_OSPEEDER_OSPEEDR6_MORT               ((uint32_t)0x00003000)
#define GPIO_OSPEEDER_OSPEEDR6_0_MORT             ((uint32_t)0x00001000)
#define GPIO_OSPEEDER_OSPEEDR6_1_MORT             ((uint32_t)0x00002000)

#define GPIO_OSPEEDER_OSPEEDR7_MORT               ((uint32_t)0x0000C000)
#define GPIO_OSPEEDER_OSPEEDR7_0_MORT             ((uint32_t)0x00004000)
#define GPIO_OSPEEDER_OSPEEDR7_1_MORT             ((uint32_t)0x00008000)

#define GPIO_OSPEEDER_OSPEEDR8_MORT               ((uint32_t)0x00030000)
#define GPIO_OSPEEDER_OSPEEDR8_0_MORT             ((uint32_t)0x00010000)
#define GPIO_OSPEEDER_OSPEEDR8_1_MORT             ((uint32_t)0x00020000)

#define GPIO_OSPEEDER_OSPEEDR9_MORT               ((uint32_t)0x000C0000)
#define GPIO_OSPEEDER_OSPEEDR9_0_MORT             ((uint32_t)0x00040000)
#define GPIO_OSPEEDER_OSPEEDR9_1_MORT             ((uint32_t)0x00080000)

#define GPIO_OSPEEDER_OSPEEDR10_MORT              ((uint32_t)0x00300000)
#define GPIO_OSPEEDER_OSPEEDR10_0_MORT            ((uint32_t)0x00100000)
#define GPIO_OSPEEDER_OSPEEDR10_1_MORT            ((uint32_t)0x00200000)

#define GPIO_OSPEEDER_OSPEEDR11_MORT              ((uint32_t)0x00C00000)
#define GPIO_OSPEEDER_OSPEEDR11_0_MORT            ((uint32_t)0x00400000)
#define GPIO_OSPEEDER_OSPEEDR11_1_MORT            ((uint32_t)0x00800000)

#define GPIO_OSPEEDER_OSPEEDR12_MORT              ((uint32_t)0x03000000)
#define GPIO_OSPEEDER_OSPEEDR12_0_MORT            ((uint32_t)0x01000000)
#define GPIO_OSPEEDER_OSPEEDR12_1_MORT            ((uint32_t)0x02000000)

#define GPIO_OSPEEDER_OSPEEDR13_MORT              ((uint32_t)0x0C000000)
#define GPIO_OSPEEDER_OSPEEDR13_0_MORT            ((uint32_t)0x04000000)
#define GPIO_OSPEEDER_OSPEEDR13_1_MORT            ((uint32_t)0x08000000)

#define GPIO_OSPEEDER_OSPEEDR14_MORT              ((uint32_t)0x30000000)
#define GPIO_OSPEEDER_OSPEEDR14_0_MORT            ((uint32_t)0x10000000)
#define GPIO_OSPEEDER_OSPEEDR14_1_MORT            ((uint32_t)0x20000000)

#define GPIO_OSPEEDER_OSPEEDR15_MORT              ((uint32_t)0xC0000000)
#define GPIO_OSPEEDER_OSPEEDR15_0_MORT            ((uint32_t)0x40000000)
#define GPIO_OSPEEDER_OSPEEDR15_1_MORT            ((uint32_t)0x80000000)

/******************  Bits definition for GPIO_PUPDR register  *****************/
#define GPIO_PUPDR_PUPDR0_MORT                    ((uint32_t)0x00000003)
#define GPIO_PUPDR_PUPDR0_0_MORT                  ((uint32_t)0x00000001)
#define GPIO_PUPDR_PUPDR0_1_MORT                  ((uint32_t)0x00000002)

#define GPIO_PUPDR_PUPDR1_MORT                    ((uint32_t)0x0000000C)
#define GPIO_PUPDR_PUPDR1_0_MORT                  ((uint32_t)0x00000004)
#define GPIO_PUPDR_PUPDR1_1_MORT                  ((uint32_t)0x00000008)

#define GPIO_PUPDR_PUPDR2_MORT                    ((uint32_t)0x00000030)
#define GPIO_PUPDR_PUPDR2_0_MORT                  ((uint32_t)0x00000010)
#define GPIO_PUPDR_PUPDR2_1_MORT                  ((uint32_t)0x00000020)

#define GPIO_PUPDR_PUPDR3_MORT                    ((uint32_t)0x000000C0)
#define GPIO_PUPDR_PUPDR3_0_MORT                  ((uint32_t)0x00000040)
#define GPIO_PUPDR_PUPDR3_1_MORT                  ((uint32_t)0x00000080)

#define GPIO_PUPDR_PUPDR4_MORT                    ((uint32_t)0x00000300)
#define GPIO_PUPDR_PUPDR4_0_MORT                  ((uint32_t)0x00000100)
#define GPIO_PUPDR_PUPDR4_1_MORT                  ((uint32_t)0x00000200)

#define GPIO_PUPDR_PUPDR5_MORT                    ((uint32_t)0x00000C00)
#define GPIO_PUPDR_PUPDR5_0_MORT                  ((uint32_t)0x00000400)
#define GPIO_PUPDR_PUPDR5_1_MORT                  ((uint32_t)0x00000800)

#define GPIO_PUPDR_PUPDR6_MORT                    ((uint32_t)0x00003000)
#define GPIO_PUPDR_PUPDR6_0_MORT                  ((uint32_t)0x00001000)
#define GPIO_PUPDR_PUPDR6_1_MORT                  ((uint32_t)0x00002000)

#define GPIO_PUPDR_PUPDR7_MORT                    ((uint32_t)0x0000C000)
#define GPIO_PUPDR_PUPDR7_0_MORT                  ((uint32_t)0x00004000)
#define GPIO_PUPDR_PUPDR7_1_MORT                  ((uint32_t)0x00008000)

#define GPIO_PUPDR_PUPDR8_MORT                    ((uint32_t)0x00030000)
#define GPIO_PUPDR_PUPDR8_0_MORT                  ((uint32_t)0x00010000)
#define GPIO_PUPDR_PUPDR8_1_MORT                  ((uint32_t)0x00020000)

#define GPIO_PUPDR_PUPDR9_MORT                    ((uint32_t)0x000C0000)
#define GPIO_PUPDR_PUPDR9_0_MORT                  ((uint32_t)0x00040000)
#define GPIO_PUPDR_PUPDR9_1_MORT                  ((uint32_t)0x00080000)

#define GPIO_PUPDR_PUPDR10_MORT                   ((uint32_t)0x00300000)
#define GPIO_PUPDR_PUPDR10_0_MORT                 ((uint32_t)0x00100000)
#define GPIO_PUPDR_PUPDR10_1_MORT                 ((uint32_t)0x00200000)

#define GPIO_PUPDR_PUPDR11_MORT                   ((uint32_t)0x00C00000)
#define GPIO_PUPDR_PUPDR11_0_MORT                 ((uint32_t)0x00400000)
#define GPIO_PUPDR_PUPDR11_1_MORT                 ((uint32_t)0x00800000)

#define GPIO_PUPDR_PUPDR12_MORT                   ((uint32_t)0x03000000)
#define GPIO_PUPDR_PUPDR12_0_MORT                 ((uint32_t)0x01000000)
#define GPIO_PUPDR_PUPDR12_1_MORT                 ((uint32_t)0x02000000)

#define GPIO_PUPDR_PUPDR13_MORT                   ((uint32_t)0x0C000000)
#define GPIO_PUPDR_PUPDR13_0_MORT                 ((uint32_t)0x04000000)
#define GPIO_PUPDR_PUPDR13_1_MORT                 ((uint32_t)0x08000000)

#define GPIO_PUPDR_PUPDR14_MORT                   ((uint32_t)0x30000000)
#define GPIO_PUPDR_PUPDR14_0_MORT                 ((uint32_t)0x10000000)
#define GPIO_PUPDR_PUPDR14_1_MORT                 ((uint32_t)0x20000000)

#define GPIO_PUPDR_PUPDR15_MORT                   ((uint32_t)0xC0000000)
#define GPIO_PUPDR_PUPDR15_0_MORT                 ((uint32_t)0x40000000)
#define GPIO_PUPDR_PUPDR15_1_MORT                 ((uint32_t)0x80000000)

/******************  Bits definition for GPIO_IDR register  *******************/
#define GPIO_IDR_IDR_0_MORT                       ((uint32_t)0x00000001)
#define GPIO_IDR_IDR_1_MORT                       ((uint32_t)0x00000002)
#define GPIO_IDR_IDR_2_MORT                       ((uint32_t)0x00000004)
#define GPIO_IDR_IDR_3_MORT                       ((uint32_t)0x00000008)
#define GPIO_IDR_IDR_4_MORT                       ((uint32_t)0x00000010)
#define GPIO_IDR_IDR_5_MORT                       ((uint32_t)0x00000020)
#define GPIO_IDR_IDR_6_MORT                       ((uint32_t)0x00000040)
#define GPIO_IDR_IDR_7_MORT                       ((uint32_t)0x00000080)
#define GPIO_IDR_IDR_8_MORT                       ((uint32_t)0x00000100)
#define GPIO_IDR_IDR_9_MORT                       ((uint32_t)0x00000200)
#define GPIO_IDR_IDR_10_MORT                      ((uint32_t)0x00000400)
#define GPIO_IDR_IDR_11_MORT                      ((uint32_t)0x00000800)
#define GPIO_IDR_IDR_12_MORT                      ((uint32_t)0x00001000)
#define GPIO_IDR_IDR_13_MORT                      ((uint32_t)0x00002000)
#define GPIO_IDR_IDR_14_MORT                      ((uint32_t)0x00004000)
#define GPIO_IDR_IDR_15_MORT                      ((uint32_t)0x00008000)
/* Old GPIO_IDR register bits definition, maintained for legacy purpose */
#define GPIO_OTYPER_IDR_0_MORT                    GPIO_IDR_IDR_0_MORT
#define GPIO_OTYPER_IDR_1_MORT                    GPIO_IDR_IDR_1_MORT
#define GPIO_OTYPER_IDR_2_MORT                    GPIO_IDR_IDR_2_MORT
#define GPIO_OTYPER_IDR_3_MORT                    GPIO_IDR_IDR_3_MORT
#define GPIO_OTYPER_IDR_4_MORT                    GPIO_IDR_IDR_4_MORT
#define GPIO_OTYPER_IDR_5_MORT                    GPIO_IDR_IDR_5_MORT
#define GPIO_OTYPER_IDR_6_MORT                    GPIO_IDR_IDR_6_MORT
#define GPIO_OTYPER_IDR_7_MORT                    GPIO_IDR_IDR_7_MORT
#define GPIO_OTYPER_IDR_8_MORT                    GPIO_IDR_IDR_8_MORT
#define GPIO_OTYPER_IDR_9_MORT                    GPIO_IDR_IDR_9_MORT
#define GPIO_OTYPER_IDR_10_MORT                   GPIO_IDR_IDR_10_MORT
#define GPIO_OTYPER_IDR_11_MORT                   GPIO_IDR_IDR_11_MORT
#define GPIO_OTYPER_IDR_12_MORT                   GPIO_IDR_IDR_12_MORT
#define GPIO_OTYPER_IDR_13_MORT                   GPIO_IDR_IDR_13_MORT
#define GPIO_OTYPER_IDR_14_MORT                   GPIO_IDR_IDR_14_MORT
#define GPIO_OTYPER_IDR_15_MORT                   GPIO_IDR_IDR_15_MORT

/******************  Bits definition for GPIO_ODR register  *******************/
#define GPIO_ODR_ODR_0_MORT                       ((uint32_t)0x00000001)
#define GPIO_ODR_ODR_1_MORT                       ((uint32_t)0x00000002)
#define GPIO_ODR_ODR_2_MORT                       ((uint32_t)0x00000004)
#define GPIO_ODR_ODR_3_MORT                       ((uint32_t)0x00000008)
#define GPIO_ODR_ODR_4_MORT                       ((uint32_t)0x00000010)
#define GPIO_ODR_ODR_5_MORT                       ((uint32_t)0x00000020)
#define GPIO_ODR_ODR_6_MORT                       ((uint32_t)0x00000040)
#define GPIO_ODR_ODR_7_MORT                       ((uint32_t)0x00000080)
#define GPIO_ODR_ODR_8_MORT                       ((uint32_t)0x00000100)
#define GPIO_ODR_ODR_9_MORT                       ((uint32_t)0x00000200)
#define GPIO_ODR_ODR_10_MORT                      ((uint32_t)0x00000400)
#define GPIO_ODR_ODR_11_MORT                      ((uint32_t)0x00000800)
#define GPIO_ODR_ODR_12_MORT                      ((uint32_t)0x00001000)
#define GPIO_ODR_ODR_13_MORT                      ((uint32_t)0x00002000)
#define GPIO_ODR_ODR_14_MORT                      ((uint32_t)0x00004000)
#define GPIO_ODR_ODR_15_MORT                      ((uint32_t)0x00008000)
/* Old GPIO_ODR register bits definition, maintained for legacy purpose */
/*#define GPIO_OTYPER_ODR_0                    GPIO_ODR_ODR_0_MORT
#define GPIO_OTYPER_ODR_1                    GPIO_ODR_ODR_1_MORT
#define GPIO_OTYPER_ODR_2                    GPIO_ODR_ODR_2_MORT
#define GPIO_OTYPER_ODR_3                    GPIO_ODR_ODR_3_MORT
#define GPIO_OTYPER_ODR_4                    GPIO_ODR_ODR_4_MORT
#define GPIO_OTYPER_ODR_5                    GPIO_ODR_ODR_5_MORT
#define GPIO_OTYPER_ODR_6                    GPIO_ODR_ODR_6_MORT
#define GPIO_OTYPER_ODR_7                    GPIO_ODR_ODR_7_MORT
#define GPIO_OTYPER_ODR_8                    GPIO_ODR_ODR_8_MORT
#define GPIO_OTYPER_ODR_9                    GPIO_ODR_ODR_9_MORT
#define GPIO_OTYPER_ODR_10                   GPIO_ODR_ODR_10_MORT
#define GPIO_OTYPER_ODR_11                   GPIO_ODR_ODR_11_MORT
#define GPIO_OTYPER_ODR_12                   GPIO_ODR_ODR_12_MORT
#define GPIO_OTYPER_ODR_13                   GPIO_ODR_ODR_13_MORT
#define GPIO_OTYPER_ODR_14                   GPIO_ODR_ODR_14_MORT
#define GPIO_OTYPER_ODR_15                   GPIO_ODR_ODR_15_MORT*/

/******************  Bits definition for GPIO_BSRR register  ******************/
#define GPIO_BSRR_BS_0_MORT                       ((uint32_t)0x00000001)
#define GPIO_BSRR_BS_1_MORT                       ((uint32_t)0x00000002)
#define GPIO_BSRR_BS_2_MORT                       ((uint32_t)0x00000004)
#define GPIO_BSRR_BS_3_MORT                       ((uint32_t)0x00000008)
#define GPIO_BSRR_BS_4_MORT                       ((uint32_t)0x00000010)
#define GPIO_BSRR_BS_5_MORT                       ((uint32_t)0x00000020)
#define GPIO_BSRR_BS_6_MORT                       ((uint32_t)0x00000040)
#define GPIO_BSRR_BS_7_MORT                       ((uint32_t)0x00000080)
#define GPIO_BSRR_BS_8_MORT                       ((uint32_t)0x00000100)
#define GPIO_BSRR_BS_9_MORT                       ((uint32_t)0x00000200)
#define GPIO_BSRR_BS_10_MORT                      ((uint32_t)0x00000400)
#define GPIO_BSRR_BS_11_MORT                      ((uint32_t)0x00000800)
#define GPIO_BSRR_BS_12_MORT                      ((uint32_t)0x00001000)
#define GPIO_BSRR_BS_13_MORT                      ((uint32_t)0x00002000)
#define GPIO_BSRR_BS_14_MORT                      ((uint32_t)0x00004000)
#define GPIO_BSRR_BS_15_MORT                      ((uint32_t)0x00008000)
#define GPIO_BSRR_BR_0_MORT                       ((uint32_t)0x00010000)
#define GPIO_BSRR_BR_1_MORT                       ((uint32_t)0x00020000)
#define GPIO_BSRR_BR_2_MORT                       ((uint32_t)0x00040000)
#define GPIO_BSRR_BR_3_MORT                       ((uint32_t)0x00080000)
#define GPIO_BSRR_BR_4_MORT                       ((uint32_t)0x00100000)
#define GPIO_BSRR_BR_5_MORT                       ((uint32_t)0x00200000)
#define GPIO_BSRR_BR_6_MORT                       ((uint32_t)0x00400000)
#define GPIO_BSRR_BR_7_MORT                       ((uint32_t)0x00800000)
#define GPIO_BSRR_BR_8_MORT                       ((uint32_t)0x01000000)
#define GPIO_BSRR_BR_9_MORT                       ((uint32_t)0x02000000)
#define GPIO_BSRR_BR_10_MORT                      ((uint32_t)0x04000000)
#define GPIO_BSRR_BR_11_MORT                      ((uint32_t)0x08000000)
#define GPIO_BSRR_BR_12_MORT                      ((uint32_t)0x10000000)
#define GPIO_BSRR_BR_13_MORT                      ((uint32_t)0x20000000)
#define GPIO_BSRR_BR_14_MORT                      ((uint32_t)0x40000000)
#define GPIO_BSRR_BR_15_MORT                      ((uint32_t)0x80000000)

/******************************************************************************/
/*                                                                            */
/*                                    HASH_MORT                                    */
/*                                                                            */
/******************************************************************************/
/******************  Bits definition for HASH_CR register  ********************/


/******************  Bits definition for HASH_STR register  *******************/


/******************  Bits definition for HASH_IMR register  *******************/


/******************  Bits definition for HASH_SR register  ********************/

/******************************************************************************/
/*                                                                            */
/*                      Inter-integrated Circuit Interface                    */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for I2C_CR1 register  ********************/

/*******************  Bit definition for I2C_CR2 register  ********************/

/*******************  Bit definition for I2C_OAR1 register  *******************/

/*******************  Bit definition for I2C_OAR2 register  *******************/

/********************  Bit definition for I2C_DR register  ********************/

/*******************  Bit definition for I2C_SR1 register  ********************/

/*******************  Bit definition for I2C_SR2 register  ********************/
 
/*******************  Bit definition for I2C_CCR register  ********************/

/******************  Bit definition for I2C_TRISE register  *******************/

/******************  Bit definition for I2C_FLTR register  *******************/

#if defined(STM32F410xx) || defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F446xx_MORT)
/******************************************************************************/
/*                                                                            */
/*              Fast-mode Plus Inter-integrated circuit (FMPI2C)              */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for I2C_CR1 register  *******************/

/******************  Bit definition for I2C_CR2 register  ********************/

/*******************  Bit definition for I2C_OAR1 register  ******************/

/*******************  Bit definition for I2C_OAR2 register  *******************/

/*******************  Bit definition for I2C_TIMINGR register *****************/

/******************* Bit definition for I2C_TIMEOUTR register *****************/

/******************  Bit definition for I2C_ISR register  *********************/

/******************  Bit definition for I2C_ICR register  *********************/

/******************  Bit definition for I2C_PECR register  ********************/

/******************  Bit definition for I2C_RXDR register  *********************/

/******************  Bit definition for I2C_TXDR register  *********************/

#endif /* STM32F410xx || STM32F412xG || STM32F413_423xx || STM32F446xx_MORT */
/******************************************************************************/
/*                                                                            */
/*                           Independent WATCHDOG                             */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for IWDG_KR register  ********************/

/*******************  Bit definition for IWDG_PR register  ********************/

/*******************  Bit definition for IWDG_RLR register  *******************/

/*******************  Bit definition for IWDG_SR register  ********************/

/******************************************************************************/
/*                                                                            */
/*                      LCD-TFT Display Controller (LTDC_MORT)                     */
/*                                                                            */
/******************************************************************************/

/********************  Bit definition for LTDC_SSCR register  *****************/


/********************  Bit definition for LTDC_BPCR register  *****************/


/********************  Bit definition for LTDC_AWCR register  *****************/


/********************  Bit definition for LTDC_TWCR register  *****************/


/********************  Bit definition for LTDC_GCR register  ******************/


/* Legacy defines */

/********************  Bit definition for LTDC_SRCR register  *****************/


/********************  Bit definition for LTDC_BCCR register  *****************/


/********************  Bit definition for LTDC_IER register  ******************/


/********************  Bit definition for LTDC_ISR register  ******************/


/********************  Bit definition for LTDC_ICR register  ******************/


/********************  Bit definition for LTDC_LIPCR register  ****************/


/********************  Bit definition for LTDC_CPSR register  *****************/


/********************  Bit definition for LTDC_CDSR register  *****************/


/********************  Bit definition for LTDC_LxCR register  *****************/


/********************  Bit definition for LTDC_LxWHPCR register  **************/


/********************  Bit definition for LTDC_LxWVPCR register  **************/


/********************  Bit definition for LTDC_LxCKCR register  ***************/


/********************  Bit definition for LTDC_LxPFCR register  ***************/


/********************  Bit definition for LTDC_LxCACR register  ***************/


/********************  Bit definition for LTDC_LxDCCR register  ***************/

    
/********************  Bit definition for LTDC_LxBFCR register  ***************/


/********************  Bit definition for LTDC_LxCFBAR register  **************/


/********************  Bit definition for LTDC_LxCFBLR register  **************/


/********************  Bit definition for LTDC_LxCFBLNR register  *************/


/********************  Bit definition for LTDC_LxCLUTWR register  *************/


#if defined(STM32F469_479xx)
/******************************************************************************/
/*                                                                            */
/*                                    DSI_MORT                                     */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for DSI_VR register  *****************/


/*******************  Bit definition for DSI_CR register  *****************/


/*******************  Bit definition for DSI_CCR register  ****************/


/*******************  Bit definition for DSI_LVCIDR register  *************/


/*******************  Bit definition for DSI_LCOLCR register  *************/



/*******************  Bit definition for DSI_LPCR register  ***************/


/*******************  Bit definition for DSI_LPMCR register  **************/


/*******************  Bit definition for DSI_PCR register  ****************/


/*******************  Bit definition for DSI_GVCIDR register  *************/


/*******************  Bit definition for DSI_MCR register  ****************/


/*******************  Bit definition for DSI_VMCR register  ***************/


/*******************  Bit definition for DSI_VPCR register  ***************/


/*******************  Bit definition for DSI_VCCR register  ***************/


/*******************  Bit definition for DSI_VNPCR register  **************/


/*******************  Bit definition for DSI_VHSACR register  *************/


/*******************  Bit definition for DSI_VHBPCR register  *************/


/*******************  Bit definition for DSI_VLCR register  ***************/

/*******************  Bit definition for DSI_VVSACR register  *************/


/*******************  Bit definition for DSI_VVBPCR register  *************/


/*******************  Bit definition for DSI_VVFPCR register  *************/


/*******************  Bit definition for DSI_VVACR register  **************/


/*******************  Bit definition for DSI_LCCR register  ***************/


/*******************  Bit definition for DSI_CMCR register  ***************/


/*******************  Bit definition for DSI_GHCR register  ***************/


/*******************  Bit definition for DSI_GPDR register  ***************/


/*******************  Bit definition for DSI_GPSR register  ***************/

/*******************  Bit definition for DSI_TCCR0 register  **************/


/*******************  Bit definition for DSI_TCCR1 register  **************/


/*******************  Bit definition for DSI_TCCR2 register  **************/


/*******************  Bit definition for DSI_TCCR3 register  **************/


/*******************  Bit definition for DSI_TCCR4 register  **************/


/*******************  Bit definition for DSI_TCCR5 register  **************/


/*******************  Bit definition for DSI_TDCR register  ***************/


/*******************  Bit definition for DSI_CLCR register  ***************/


/*******************  Bit definition for DSI_CLTCR register  **************/


/*******************  Bit definition for DSI_DLTCR register  **************/


/*******************  Bit definition for DSI_PCTLR register  **************/


/*******************  Bit definition for DSI_PCONFR register  *************/


/*******************  Bit definition for DSI_PUCR register  ***************/


/*******************  Bit definition for DSI_PTTCR register  **************/


/*******************  Bit definition for DSI_PSR register  ****************/


/*******************  Bit definition for DSI_ISR0 register  ***************/

/*******************  Bit definition for DSI_ISR1 register  ***************/


/*******************  Bit definition for DSI_IER0 register  ***************/


/*******************  Bit definition for DSI_IER1 register  ***************/


/*******************  Bit definition for DSI_FIR0 register  ***************/


/*******************  Bit definition for DSI_FIR1 register  ***************/


/*******************  Bit definition for DSI_VSCR register  ***************/


/*******************  Bit definition for DSI_LCVCIDR register  ************/


/*******************  Bit definition for DSI_LCCCR register  **************/


/*******************  Bit definition for DSI_LPMCCR register  *************/

/*******************  Bit definition for DSI_VMCCR register  **************/


/*******************  Bit definition for DSI_VPCCR register  **************/


/*******************  Bit definition for DSI_VCCCR register  **************/


/*******************  Bit definition for DSI_VNPCCR register  *************/


/*******************  Bit definition for DSI_VHSACCR register  ************/


/*******************  Bit definition for DSI_VHBPCCR register  ************/


/*******************  Bit definition for DSI_VLCCR register  **************/


/*******************  Bit definition for DSI_VVSACCR register  ***************/


/*******************  Bit definition for DSI_VVBPCCR register  ************/


/*******************  Bit definition for DSI_VVFPCCR register  ************/


/*******************  Bit definition for DSI_VVACCR register  *************/


/*******************  Bit definition for DSI_TDCCR register  **************/


/*******************  Bit definition for DSI_WCFGR register  ***************/

/*******************  Bit definition for DSI_WCR register  *****************/


/*******************  Bit definition for DSI_WIER register  ****************/


/*******************  Bit definition for DSI_WISR register  ****************/

/*******************  Bit definition for DSI_WIFCR register  ***************/

/*******************  Bit definition for DSI_WPCR0 register  ***************/

/*******************  Bit definition for DSI_WPCR1 register  ***************/


/*******************  Bit definition for DSI_WPCR2 register  ***************/


/*******************  Bit definition for DSI_WPCR3 register  ***************/


/*******************  Bit definition for DSI_WPCR4 register  ***************/


/*******************  Bit definition for DSI_WRPCR register  ***************/

#endif /* STM32F469_479xx */

/******************************************************************************/
/*                                                                            */
/*                             Power Control                                  */
/*                                                                            */
/******************************************************************************/
/********************  Bit definition for PWR_CR register  ********************/

/*!< PVD level configuration */

/* Legacy define */

/*******************  Bit definition for PWR_CSR register  ********************/

/* Legacy define */


#if defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F446xx_MORT) || defined(STM32F469_479xx)
/******************************************************************************/
/*                                                                            */
/*                                    QUADSPI_MORT                                 */
/*                                                                            */
/******************************************************************************/
/*****************  Bit definition for QUADSPI_CR register  *******************/

/*****************  Bit definition for QUADSPI_DCR register  ******************/

/******************  Bit definition for QUADSPI_SR register  *******************/

/******************  Bit definition for QUADSPI_FCR register  ******************/

/******************  Bit definition for QUADSPI_DLR register  ******************/

/******************  Bit definition for QUADSPI_CCR register  ******************/

/******************  Bit definition for QUADSPI_AR register  *******************/

/******************  Bit definition for QUADSPI_ABR register  ******************/

/******************  Bit definition for QUADSPI_DR register  *******************/

/******************  Bit definition for QUADSPI_PSMKR register  ****************/

/******************  Bit definition for QUADSPI_PSMAR register  ****************/

/******************  Bit definition for QUADSPI_PIR register  *****************/

/******************  Bit definition for QUADSPI_LPTR register  *****************/
         
#endif /* STM32F412xG || STM32F413_423xx || STM32F446xx_MORT || STM32F469_479xx */

/******************************************************************************/
/*                                                                            */
/*                         Reset and Clock Control                            */
/*                                                                            */
/******************************************************************************/
/********************  Bit definition for RCC_CR register  ********************/
#define  RCC_CR_HSION_MORT                        ((uint32_t)0x00000001)
#define  RCC_CR_HSIRDY_MORT                       ((uint32_t)0x00000002)

#define  RCC_CR_HSITRIM_MORT                      ((uint32_t)0x000000F8)
#define  RCC_CR_HSITRIM_0_MORT                    ((uint32_t)0x00000008)/*!<Bit 0 */
#define  RCC_CR_HSITRIM_1_MORT                    ((uint32_t)0x00000010)/*!<Bit 1 */
#define  RCC_CR_HSITRIM_2_MORT                    ((uint32_t)0x00000020)/*!<Bit 2 */
#define  RCC_CR_HSITRIM_3_MORT                    ((uint32_t)0x00000040)/*!<Bit 3 */
#define  RCC_CR_HSITRIM_4_MORT                    ((uint32_t)0x00000080)/*!<Bit 4 */

#define  RCC_CR_HSICAL_MORT                       ((uint32_t)0x0000FF00)
#define  RCC_CR_HSICAL_0_MORT                     ((uint32_t)0x00000100)/*!<Bit 0 */
#define  RCC_CR_HSICAL_1_MORT                     ((uint32_t)0x00000200)/*!<Bit 1 */
#define  RCC_CR_HSICAL_2_MORT                     ((uint32_t)0x00000400)/*!<Bit 2 */
#define  RCC_CR_HSICAL_3_MORT                     ((uint32_t)0x00000800)/*!<Bit 3 */
#define  RCC_CR_HSICAL_4_MORT                     ((uint32_t)0x00001000)/*!<Bit 4 */
#define  RCC_CR_HSICAL_5_MORT                     ((uint32_t)0x00002000)/*!<Bit 5 */
#define  RCC_CR_HSICAL_6_MORT                     ((uint32_t)0x00004000)/*!<Bit 6 */
#define  RCC_CR_HSICAL_7_MORT                     ((uint32_t)0x00008000)/*!<Bit 7 */

#define  RCC_CR_HSEON_MORT                        ((uint32_t)0x00010000)
#define  RCC_CR_HSERDY_MORT                       ((uint32_t)0x00020000)
#define  RCC_CR_HSEBYP_MORT                       ((uint32_t)0x00040000)
#define  RCC_CR_CSSON_MORT                        ((uint32_t)0x00080000)
#define  RCC_CR_PLLON_MORT                        ((uint32_t)0x01000000)
#define  RCC_CR_PLLRDY_MORT                       ((uint32_t)0x02000000)
#define  RCC_CR_PLLI2SON_MORT                     ((uint32_t)0x04000000)
#define  RCC_CR_PLLI2SRDY_MORT                    ((uint32_t)0x08000000)
#define  RCC_CR_PLLSAION_MORT                     ((uint32_t)0x10000000)
#define  RCC_CR_PLLSAIRDY_MORT                    ((uint32_t)0x20000000)

/********************  Bit definition for RCC_PLLCFGR register  ***************/
#define  RCC_PLLCFGR_PLLM_MORT                    ((uint32_t)0x0000003F)
#define  RCC_PLLCFGR_PLLM_0_MORT                  ((uint32_t)0x00000001)
#define  RCC_PLLCFGR_PLLM_1_MORT                  ((uint32_t)0x00000002)
#define  RCC_PLLCFGR_PLLM_2_MORT                  ((uint32_t)0x00000004)
#define  RCC_PLLCFGR_PLLM_3_MORT                  ((uint32_t)0x00000008)
#define  RCC_PLLCFGR_PLLM_4_MORT                  ((uint32_t)0x00000010)
#define  RCC_PLLCFGR_PLLM_5_MORT                  ((uint32_t)0x00000020)

#define  RCC_PLLCFGR_PLLN_MORT                     ((uint32_t)0x00007FC0)
#define  RCC_PLLCFGR_PLLN_0_MORT                   ((uint32_t)0x00000040)
#define  RCC_PLLCFGR_PLLN_1_MORT                   ((uint32_t)0x00000080)
#define  RCC_PLLCFGR_PLLN_2_MORT                   ((uint32_t)0x00000100)
#define  RCC_PLLCFGR_PLLN_3_MORT                   ((uint32_t)0x00000200)
#define  RCC_PLLCFGR_PLLN_4_MORT                   ((uint32_t)0x00000400)
#define  RCC_PLLCFGR_PLLN_5_MORT                   ((uint32_t)0x00000800)
#define  RCC_PLLCFGR_PLLN_6_MORT                   ((uint32_t)0x00001000)
#define  RCC_PLLCFGR_PLLN_7_MORT                   ((uint32_t)0x00002000)
#define  RCC_PLLCFGR_PLLN_8_MORT                   ((uint32_t)0x00004000)

#define  RCC_PLLCFGR_PLLP_MORT                    ((uint32_t)0x00030000)
#define  RCC_PLLCFGR_PLLP_0_MORT                  ((uint32_t)0x00010000)
#define  RCC_PLLCFGR_PLLP_1_MORT                  ((uint32_t)0x00020000)

#define  RCC_PLLCFGR_PLLSRC_MORT                  ((uint32_t)0x00400000)
#define  RCC_PLLCFGR_PLLSRC_HSE_MORT              ((uint32_t)0x00400000)
#define  RCC_PLLCFGR_PLLSRC_HSI_MORT              ((uint32_t)0x00000000)

#define  RCC_PLLCFGR_PLLQ_MORT                    ((uint32_t)0x0F000000)
#define  RCC_PLLCFGR_PLLQ_0_MORT                  ((uint32_t)0x01000000)
#define  RCC_PLLCFGR_PLLQ_1_MORT                  ((uint32_t)0x02000000)
#define  RCC_PLLCFGR_PLLQ_2_MORT                  ((uint32_t)0x04000000)
#define  RCC_PLLCFGR_PLLQ_3_MORT                  ((uint32_t)0x08000000)

#if defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F446xx_MORT) || defined(STM32F469_479xx)
#define  RCC_PLLCFGR_PLLR_MORT                    ((uint32_t)0x70000000)
#define  RCC_PLLCFGR_PLLR_0_MORT                  ((uint32_t)0x10000000)
#define  RCC_PLLCFGR_PLLR_1_MORT                  ((uint32_t)0x20000000)
#define  RCC_PLLCFGR_PLLR_2_MORT                  ((uint32_t)0x40000000)
#endif /* STM32F412xG || STM32F413_423xx || STM32F446xx_MORT || STM32F469_479xx */

/********************  Bit definition for RCC_CFGR register  ******************/
/*!< SW configuration */
#define  RCC_CFGR_SW_MORT                         ((uint32_t)0x00000003)        /*!< SW[1:0] bits (System clock Switch) */
#define  RCC_CFGR_SW_0_MORT                       ((uint32_t)0x00000001)        /*!< Bit 0 */
#define  RCC_CFGR_SW_1_MORT                       ((uint32_t)0x00000002)        /*!< Bit 1 */

#define  RCC_CFGR_SW_HSI_MORT                     ((uint32_t)0x00000000)        /*!< HSI selected as system clock */
#define  RCC_CFGR_SW_HSE_MORT                     ((uint32_t)0x00000001)        /*!< HSE selected as system clock */
#define  RCC_CFGR_SW_PLL_MORT                     ((uint32_t)0x00000002)        /*!< PLL/PLLP selected as system clock */
#if defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F446xx_MORT) || defined(STM32F469_479xx)
#define  RCC_CFGR_SW_PLLR_MORT                    ((uint32_t)0x00000003)        /*!< PLL/PLLR selected as system clock */
#endif /* STM32F412xG || STM32F413_423xx || STM32F446xx_MORT || STM32F469_479xx */

/*!< SWS configuration */
#define  RCC_CFGR_SWS_MORT                        ((uint32_t)0x0000000C)        /*!< SWS[1:0] bits (System Clock Switch Status) */
#define  RCC_CFGR_SWS_0_MORT                      ((uint32_t)0x00000004)        /*!< Bit 0 */
#define  RCC_CFGR_SWS_1_MORT                      ((uint32_t)0x00000008)        /*!< Bit 1 */

#define  RCC_CFGR_SWS_HSI_MORT                    ((uint32_t)0x00000000)        /*!< HSI oscillator used as system clock */
#define  RCC_CFGR_SWS_HSE_MORT                    ((uint32_t)0x00000004)        /*!< HSE oscillator used as system clock */
#define  RCC_CFGR_SWS_PLL_MORT                    ((uint32_t)0x00000008)        /*!< PLL/PLLP used as system clock       */
#if defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F469_479xx) || defined(STM32F446xx_MORT)
#define  RCC_CFGR_SWS_PLLR_MORT                   ((uint32_t)0x0000000C)        /*!< PLL/PLLR used as system clock       */
#endif /* STM32F412xG || STM32F413_423xx || STM32F446xx_MORT || STM32F469_479xx */

/*!< HPRE configuration */
#define  RCC_CFGR_HPRE_MORT                       ((uint32_t)0x000000F0)        /*!< HPRE[3:0] bits (AHB prescaler) */
#define  RCC_CFGR_HPRE_0_MORT                     ((uint32_t)0x00000010)        /*!< Bit 0 */
#define  RCC_CFGR_HPRE_1_MORT                     ((uint32_t)0x00000020)        /*!< Bit 1 */
#define  RCC_CFGR_HPRE_2_MORT                     ((uint32_t)0x00000040)        /*!< Bit 2 */
#define  RCC_CFGR_HPRE_3_MORT                     ((uint32_t)0x00000080)        /*!< Bit 3 */

#define  RCC_CFGR_HPRE_DIV1_MORT                  ((uint32_t)0x00000000)        /*!< SYSCLK not divided */
#define  RCC_CFGR_HPRE_DIV2_MORT                  ((uint32_t)0x00000080)        /*!< SYSCLK divided by 2 */
#define  RCC_CFGR_HPRE_DIV4_MORT                  ((uint32_t)0x00000090)        /*!< SYSCLK divided by 4 */
#define  RCC_CFGR_HPRE_DIV8_MORT                  ((uint32_t)0x000000A0)        /*!< SYSCLK divided by 8 */
#define  RCC_CFGR_HPRE_DIV16_MORT                 ((uint32_t)0x000000B0)        /*!< SYSCLK divided by 16 */
#define  RCC_CFGR_HPRE_DIV64_MORT                 ((uint32_t)0x000000C0)        /*!< SYSCLK divided by 64 */
#define  RCC_CFGR_HPRE_DIV128_MORT                ((uint32_t)0x000000D0)        /*!< SYSCLK divided by 128 */
#define  RCC_CFGR_HPRE_DIV256_MORT                ((uint32_t)0x000000E0)        /*!< SYSCLK divided by 256 */
#define  RCC_CFGR_HPRE_DIV512_MORT                ((uint32_t)0x000000F0)        /*!< SYSCLK divided by 512 */

#if defined(STM32F410xx)
/*!< MCO1EN configuration */

#endif /* STM32F410xx */
/*!< PPRE1 configuration */
#define  RCC_CFGR_PPRE1_MORT                      ((uint32_t)0x00001C00)        /*!< PRE1[2:0] bits (APB1 prescaler) */
#define  RCC_CFGR_PPRE1_0_MORT                    ((uint32_t)0x00000400)        /*!< Bit 0 */
#define  RCC_CFGR_PPRE1_1_MORT                    ((uint32_t)0x00000800)        /*!< Bit 1 */
#define  RCC_CFGR_PPRE1_2_MORT                    ((uint32_t)0x00001000)        /*!< Bit 2 */

#define  RCC_CFGR_PPRE1_DIV1_MORT                 ((uint32_t)0x00000000)        /*!< HCLK not divided */
#define  RCC_CFGR_PPRE1_DIV2_MORT                 ((uint32_t)0x00001000)        /*!< HCLK divided by 2 */
#define  RCC_CFGR_PPRE1_DIV4_MORT                 ((uint32_t)0x00001400)        /*!< HCLK divided by 4 */
#define  RCC_CFGR_PPRE1_DIV8_MORT                 ((uint32_t)0x00001800)        /*!< HCLK divided by 8 */
#define  RCC_CFGR_PPRE1_DIV16_MORT                ((uint32_t)0x00001C00)        /*!< HCLK divided by 16 */

/*!< PPRE2 configuration */
#define  RCC_CFGR_PPRE2_MORT                      ((uint32_t)0x0000E000)        /*!< PRE2[2:0] bits (APB2 prescaler) */
#define  RCC_CFGR_PPRE2_0_MORT                    ((uint32_t)0x00002000)        /*!< Bit 0 */
#define  RCC_CFGR_PPRE2_1_MORT                    ((uint32_t)0x00004000)        /*!< Bit 1 */
#define  RCC_CFGR_PPRE2_2_MORT                    ((uint32_t)0x00008000)        /*!< Bit 2 */

#define  RCC_CFGR_PPRE2_DIV1_MORT                 ((uint32_t)0x00000000)        /*!< HCLK not divided */
#define  RCC_CFGR_PPRE2_DIV2_MORT                 ((uint32_t)0x00008000)        /*!< HCLK divided by 2 */
#define  RCC_CFGR_PPRE2_DIV4_MORT                 ((uint32_t)0x0000A000)        /*!< HCLK divided by 4 */
#define  RCC_CFGR_PPRE2_DIV8_MORT                 ((uint32_t)0x0000C000)        /*!< HCLK divided by 8 */
#define  RCC_CFGR_PPRE2_DIV16_MORT                ((uint32_t)0x0000E000)        /*!< HCLK divided by 16 */

/*!< RTCPRE configuration */
#define  RCC_CFGR_RTCPRE_MORT                     ((uint32_t)0x001F0000)
#define  RCC_CFGR_RTCPRE_0_MORT                   ((uint32_t)0x00010000)
#define  RCC_CFGR_RTCPRE_1_MORT                   ((uint32_t)0x00020000)
#define  RCC_CFGR_RTCPRE_2_MORT                   ((uint32_t)0x00040000)
#define  RCC_CFGR_RTCPRE_3_MORT                   ((uint32_t)0x00080000)
#define  RCC_CFGR_RTCPRE_4_MORT                   ((uint32_t)0x00100000)

/*!< MCO1 configuration */
#define  RCC_CFGR_MCO1_MORT                       ((uint32_t)0x00600000)
#define  RCC_CFGR_MCO1_0_MORT                     ((uint32_t)0x00200000)
#define  RCC_CFGR_MCO1_1_MORT                     ((uint32_t)0x00400000)

#define  RCC_CFGR_I2SSRC_MORT                     ((uint32_t)0x00800000)

#define  RCC_CFGR_MCO1PRE_MORT                    ((uint32_t)0x07000000)
#define  RCC_CFGR_MCO1PRE_0_MORT                  ((uint32_t)0x01000000)
#define  RCC_CFGR_MCO1PRE_1_MORT                  ((uint32_t)0x02000000)
#define  RCC_CFGR_MCO1PRE_2_MORT                  ((uint32_t)0x04000000)

#define  RCC_CFGR_MCO2PRE_MORT                    ((uint32_t)0x38000000)
#define  RCC_CFGR_MCO2PRE_0_MORT                  ((uint32_t)0x08000000)
#define  RCC_CFGR_MCO2PRE_1_MORT                  ((uint32_t)0x10000000)
#define  RCC_CFGR_MCO2PRE_2_MORT                  ((uint32_t)0x20000000)

#define  RCC_CFGR_MCO2_MORT                       ((uint32_t)0xC0000000)
#define  RCC_CFGR_MCO2_0_MORT                     ((uint32_t)0x40000000)
#define  RCC_CFGR_MCO2_1_MORT                     ((uint32_t)0x80000000)

/********************  Bit definition for RCC_CIR register  *******************/
#define  RCC_CIR_LSIRDYF_MORT                     ((uint32_t)0x00000001)
#define  RCC_CIR_LSERDYF_MORT                     ((uint32_t)0x00000002)
#define  RCC_CIR_HSIRDYF_MORT                     ((uint32_t)0x00000004)
#define  RCC_CIR_HSERDYF_MORT                     ((uint32_t)0x00000008)
#define  RCC_CIR_PLLRDYF_MORT                     ((uint32_t)0x00000010)
#define  RCC_CIR_PLLI2SRDYF_MORT                  ((uint32_t)0x00000020)
#define  RCC_CIR_PLLSAIRDYF_MORT                  ((uint32_t)0x00000040)
#define  RCC_CIR_CSSF_MORT                        ((uint32_t)0x00000080)
#define  RCC_CIR_LSIRDYIE_MORT                    ((uint32_t)0x00000100)
#define  RCC_CIR_LSERDYIE_MORT                    ((uint32_t)0x00000200)
#define  RCC_CIR_HSIRDYIE_MORT                    ((uint32_t)0x00000400)
#define  RCC_CIR_HSERDYIE_MORT                    ((uint32_t)0x00000800)
#define  RCC_CIR_PLLRDYIE_MORT                    ((uint32_t)0x00001000)
#define  RCC_CIR_PLLI2SRDYIE_MORT                 ((uint32_t)0x00002000)
#define  RCC_CIR_PLLSAIRDYIE_MORT                 ((uint32_t)0x00004000)
#define  RCC_CIR_LSIRDYC_MORT                     ((uint32_t)0x00010000)
#define  RCC_CIR_LSERDYC_MORT                     ((uint32_t)0x00020000)
#define  RCC_CIR_HSIRDYC_MORT                     ((uint32_t)0x00040000)
#define  RCC_CIR_HSERDYC_MORT                     ((uint32_t)0x00080000)
#define  RCC_CIR_PLLRDYC_MORT                     ((uint32_t)0x00100000)
#define  RCC_CIR_PLLI2SRDYC_MORT                  ((uint32_t)0x00200000)
#define  RCC_CIR_PLLSAIRDYC_MORT                  ((uint32_t)0x00400000)
#define  RCC_CIR_CSSC_MORT                        ((uint32_t)0x00800000)

/********************  Bit definition for RCC_AHB1RSTR register  **************/
#define  RCC_AHB1RSTR_GPIOARST_MORT               ((uint32_t)0x00000001)
#define  RCC_AHB1RSTR_GPIOBRST_MORT               ((uint32_t)0x00000002)
#define  RCC_AHB1RSTR_GPIOCRST_MORT               ((uint32_t)0x00000004)
#define  RCC_AHB1RSTR_GPIODRST_MORT               ((uint32_t)0x00000008)
#define  RCC_AHB1RSTR_GPIOERST_MORT               ((uint32_t)0x00000010)
#define  RCC_AHB1RSTR_GPIOFRST_MORT               ((uint32_t)0x00000020)
#define  RCC_AHB1RSTR_GPIOGRST_MORT               ((uint32_t)0x00000040)
#define  RCC_AHB1RSTR_GPIOHRST_MORT               ((uint32_t)0x00000080)
#define  RCC_AHB1RSTR_GPIOIRST_MORT               ((uint32_t)0x00000100)
#define  RCC_AHB1RSTR_GPIOJRST_MORT               ((uint32_t)0x00000200)
#define  RCC_AHB1RSTR_GPIOKRST_MORT               ((uint32_t)0x00000400)
#define  RCC_AHB1RSTR_CRCRST_MORT                 ((uint32_t)0x00001000)
#define  RCC_AHB1RSTR_DMA1RST_MORT                ((uint32_t)0x00200000)
#define  RCC_AHB1RSTR_DMA2RST_MORT                ((uint32_t)0x00400000)
#define  RCC_AHB1RSTR_DMA2DRST_MORT               ((uint32_t)0x00800000)
#define  RCC_AHB1RSTR_ETHMACRST_MORT              ((uint32_t)0x02000000)
#define  RCC_AHB1RSTR_OTGHRST_MORT                ((uint32_t)0x10000000)

/********************  Bit definition for RCC_AHB2RSTR register  **************/
#define  RCC_AHB2RSTR_DCMIRST_MORT                ((uint32_t)0x00000001)
#define  RCC_AHB2RSTR_CRYPRST_MORT                ((uint32_t)0x00000010)
#define  RCC_AHB2RSTR_HASHRST_MORT                ((uint32_t)0x00000020)
 /* maintained for legacy purpose */
#define  RCC_AHB2RSTR_HSAHRST_MORT                RCC_AHB2RSTR_HASHRST_MORT
#define  RCC_AHB2RSTR_RNGRST_MORT                 ((uint32_t)0x00000040)
#define  RCC_AHB2RSTR_OTGFSRST_MORT               ((uint32_t)0x00000080)

/********************  Bit definition for RCC_AHB3RSTR register  **************/
#if defined(STM32F40_41xxx) || defined(STM32F412xG) || defined(STM32F413_423xx)

#endif /* STM32F40_41xxx || STM32F412xG || STM32F413_423xx */

#if defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F446xx_MORT) || defined(STM32F469_479xx)
#define  RCC_AHB3RSTR_FMCRST_MORT                ((uint32_t)0x00000001)
#endif /* STM32F427_437xx ||  STM32F429_439xx || STM32F446xx_MORT || STM32F469_479xx */
#if defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F446xx_MORT) || defined(STM32F469_479xx)
#define  RCC_AHB3RSTR_QSPIRST_MORT               ((uint32_t)0x00000002)
#endif /* STM32F412xG || STM32F413_423xx || STM32F446xx_MORT || STM32F469_479xx */

/********************  Bit definition for RCC_APB1RSTR register  **************/
#define  RCC_APB1RSTR_TIM2RST_MORT                ((uint32_t)0x00000001)
#define  RCC_APB1RSTR_TIM3RST_MORT                ((uint32_t)0x00000002)
#define  RCC_APB1RSTR_TIM4RST_MORT                ((uint32_t)0x00000004)
#define  RCC_APB1RSTR_TIM5RST_MORT                ((uint32_t)0x00000008)
#define  RCC_APB1RSTR_TIM6RST_MORT                ((uint32_t)0x00000010)
#define  RCC_APB1RSTR_TIM7RST_MORT                ((uint32_t)0x00000020)
#define  RCC_APB1RSTR_TIM12RST_MORT               ((uint32_t)0x00000040)
#define  RCC_APB1RSTR_TIM13RST_MORT               ((uint32_t)0x00000080)
#define  RCC_APB1RSTR_TIM14RST_MORT               ((uint32_t)0x00000100)
#if defined(STM32F410xx) || defined(STM32F413_423xx)
#define  RCC_APB1RSTR_LPTIM1RST_MORT              ((uint32_t)0x00000200)
#endif /* STM32F410xx || STM32F413_423xx */
#define  RCC_APB1RSTR_WWDGRST_MORT                ((uint32_t)0x00000800)
#define  RCC_APB1RSTR_SPI2RST_MORT                ((uint32_t)0x00004000)
#define  RCC_APB1RSTR_SPI3RST_MORT                ((uint32_t)0x00008000)
#if defined(STM32F446xx_MORT)
#define  RCC_APB1RSTR_SPDIFRXRST_MORT             ((uint32_t)0x00010000)
#endif /* STM32F446xx_MORT */
#define  RCC_APB1RSTR_USART2RST_MORT              ((uint32_t)0x00020000)
#define  RCC_APB1RSTR_USART3RST_MORT              ((uint32_t)0x00040000)
#define  RCC_APB1RSTR_UART4RST_MORT               ((uint32_t)0x00080000)
#define  RCC_APB1RSTR_UART5RST_MORT               ((uint32_t)0x00100000)
#define  RCC_APB1RSTR_I2C1RST_MORT                ((uint32_t)0x00200000)
#define  RCC_APB1RSTR_I2C2RST_MORT                ((uint32_t)0x00400000)
#define  RCC_APB1RSTR_I2C3RST_MORT                ((uint32_t)0x00800000)
#if defined(STM32F410xx) || defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F446xx_MORT)
#define  RCC_APB1RSTR_FMPI2C1RST_MORT             ((uint32_t)0x01000000)
#endif /* STM32F410xx || STM32F412xG || STM32F413_423xx || STM32F446xx_MORT */
#define  RCC_APB1RSTR_CAN1RST_MORT                ((uint32_t)0x02000000)
#define  RCC_APB1RSTR_CAN2RST_MORT                ((uint32_t)0x04000000)
#if defined(STM32F446xx_MORT)
#define  RCC_APB1RSTR_CECRST_MORT                 ((uint32_t)0x08000000)
#endif /* STM32F446xx_MORT */
#define  RCC_APB1RSTR_PWRRST_MORT                 ((uint32_t)0x10000000)
#define  RCC_APB1RSTR_DACRST_MORT                 ((uint32_t)0x20000000)
#define  RCC_APB1RSTR_UART7RST_MORT               ((uint32_t)0x40000000)
#define  RCC_APB1RSTR_UART8RST_MORT               ((uint32_t)0x80000000)

/********************  Bit definition for RCC_APB2RSTR register  **************/
#define  RCC_APB2RSTR_TIM1RST_MORT                ((uint32_t)0x00000001)
#define  RCC_APB2RSTR_TIM8RST_MORT                ((uint32_t)0x00000002)
#define  RCC_APB2RSTR_USART1RST_MORT              ((uint32_t)0x00000010)
#define  RCC_APB2RSTR_USART6RST_MORT              ((uint32_t)0x00000020)
#define  RCC_APB2RSTR_UART9RST_MORT               ((uint32_t)0x00000040)
#define  RCC_APB2RSTR_UART10RST_MORT              ((uint32_t)0x00000080)
#define  RCC_APB2RSTR_ADCRST_MORT                 ((uint32_t)0x00000100)
#define  RCC_APB2RSTR_SDIORST_MORT                ((uint32_t)0x00000800)
#define  RCC_APB2RSTR_SPI1RST_MORT                ((uint32_t)0x00001000)
#define  RCC_APB2RSTR_SPI4RST_MORT                ((uint32_t)0x00002000)
#define  RCC_APB2RSTR_SYSCFGRST_MORT              ((uint32_t)0x00004000)
#define  RCC_APB2RSTR_TIM9RST_MORT                ((uint32_t)0x00010000)
#define  RCC_APB2RSTR_TIM10RST_MORT               ((uint32_t)0x00020000)
#define  RCC_APB2RSTR_TIM11RST_MORT               ((uint32_t)0x00040000)
#define  RCC_APB2RSTR_SPI5RST_MORT                ((uint32_t)0x00100000)
#define  RCC_APB2RSTR_SPI6RST_MORT                ((uint32_t)0x00200000)
#define  RCC_APB2RSTR_SAI1RST_MORT                ((uint32_t)0x00400000)
#if defined(STM32F446xx_MORT)
#define  RCC_APB2RSTR_SAI2RST_MORT                ((uint32_t)0x00800000)
#endif /* STM32F446xx_MORT */
#define  RCC_APB2RSTR_LTDCRST_MORT                ((uint32_t)0x04000000)
#if defined(STM32F469_479xx)
#define  RCC_APB2RSTR_DSIRST_MORT                 ((uint32_t)0x08000000)
#endif /* STM32F469_479xx */
#if defined(STM32F412xG) || defined(STM32F413_423xx)
#define  RCC_APB2RSTR_DFSDM1RST_MORT              ((uint32_t)0x01000000)
#endif /* STM32F412xG || STM32F413_423xx */

#if defined(STM32F413_423xx)
#define  RCC_APB2RSTR_DFSDM2RST_MORT              ((uint32_t)0x02000000)
#endif /* STM32F413_423xx */
/* Old definitions, maintained for legacy purpose */
#define  RCC_APB2RSTR_SPI1_MORT                   RCC_APB2RSTR_SPI1RST_MORT
#define  RCC_APB2RSTR_DFSDMRST               RCC_APB2RSTR_DFSDM1RST_MORT

/********************  Bit definition for RCC_AHB1ENR register  ***************/
#define  RCC_AHB1ENR_GPIOAEN_MORT                 ((uint32_t)0x00000001)
#define  RCC_AHB1ENR_GPIOBEN_MORT                 ((uint32_t)0x00000002)
#define  RCC_AHB1ENR_GPIOCEN_MORT                 ((uint32_t)0x00000004)
#define  RCC_AHB1ENR_GPIODEN_MORT                 ((uint32_t)0x00000008)
#define  RCC_AHB1ENR_GPIOEEN_MORT                 ((uint32_t)0x00000010)
#define  RCC_AHB1ENR_GPIOFEN_MORT                 ((uint32_t)0x00000020)
#define  RCC_AHB1ENR_GPIOGEN_MORT                 ((uint32_t)0x00000040)
#define  RCC_AHB1ENR_GPIOHEN_MORT                 ((uint32_t)0x00000080)
#define  RCC_AHB1ENR_GPIOIEN_MORT                 ((uint32_t)0x00000100)
#define  RCC_AHB1ENR_GPIOJEN_MORT                 ((uint32_t)0x00000200)
#define  RCC_AHB1ENR_GPIOKEN_MORT                 ((uint32_t)0x00000400)
#define  RCC_AHB1ENR_CRCEN_MORT                   ((uint32_t)0x00001000)
#define  RCC_AHB1ENR_BKPSRAMEN_MORT               ((uint32_t)0x00040000)
#define  RCC_AHB1ENR_CCMDATARAMEN_MORT            ((uint32_t)0x00100000)
#define  RCC_AHB1ENR_DMA1EN_MORT                  ((uint32_t)0x00200000)
#define  RCC_AHB1ENR_DMA2EN_MORT                  ((uint32_t)0x00400000)
#define  RCC_AHB1ENR_DMA2DEN_MORT                 ((uint32_t)0x00800000)
#define  RCC_AHB1ENR_ETHMACEN_MORT                ((uint32_t)0x02000000)
#define  RCC_AHB1ENR_ETHMACTXEN_MORT              ((uint32_t)0x04000000)
#define  RCC_AHB1ENR_ETHMACRXEN_MORT              ((uint32_t)0x08000000)
#define  RCC_AHB1ENR_ETHMACPTPEN_MORT             ((uint32_t)0x10000000)
#define  RCC_AHB1ENR_OTGHSEN_MORT                 ((uint32_t)0x20000000)
#define  RCC_AHB1ENR_OTGHSULPIEN_MORT             ((uint32_t)0x40000000)

/********************  Bit definition for RCC_AHB2ENR register  ***************/
#define  RCC_AHB2ENR_DCMIEN_MORT                  ((uint32_t)0x00000001)
#define  RCC_AHB2ENR_CRYPEN_MORT                  ((uint32_t)0x00000010)
#define  RCC_AHB2ENR_HASHEN_MORT                  ((uint32_t)0x00000020)
#define  RCC_AHB2ENR_RNGEN_MORT                   ((uint32_t)0x00000040)
#define  RCC_AHB2ENR_OTGFSEN_MORT                 ((uint32_t)0x00000080)

/********************  Bit definition for RCC_AHB3ENR register  ***************/

#if defined(STM32F40_41xxx) || defined(STM32F412xG) || defined(STM32F413_423xx)

#endif /* STM32F40_41xxx || STM32F412xG || STM32F413_423xx */

#if defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F446xx_MORT) || defined(STM32F469_479xx)
#define  RCC_AHB3ENR_FMCEN_MORT                  ((uint32_t)0x00000001)
#endif /* STM32F427_437xx ||  STM32F429_439xx || STM32F446xx_MORT || STM32F469_479xx */

#if defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F446xx_MORT) || defined(STM32F469_479xx)
#define  RCC_AHB3ENR_QSPIEN_MORT                 ((uint32_t)0x00000002)
#endif /* STM32F412xG || STM32F413_423xx || STM32F446xx_MORT || STM32F469_479xx */

/********************  Bit definition for RCC_APB1ENR register  ***************/
#define  RCC_APB1ENR_TIM2EN_MORT                  ((uint32_t)0x00000001)
#define  RCC_APB1ENR_TIM3EN_MORT                  ((uint32_t)0x00000002)
#define  RCC_APB1ENR_TIM4EN_MORT                  ((uint32_t)0x00000004)
#define  RCC_APB1ENR_TIM5EN_MORT                  ((uint32_t)0x00000008)
#define  RCC_APB1ENR_TIM6EN_MORT                  ((uint32_t)0x00000010)
#define  RCC_APB1ENR_TIM7EN_MORT                  ((uint32_t)0x00000020)
#define  RCC_APB1ENR_TIM12EN_MORT                 ((uint32_t)0x00000040)
#define  RCC_APB1ENR_TIM13EN_MORT                 ((uint32_t)0x00000080)
#define  RCC_APB1ENR_TIM14EN_MORT                 ((uint32_t)0x00000100)
#if defined(STM32F410xx) || defined(STM32F413_423xx)

#endif /* STM32F410xx || STM32F413_423xx */
#define  RCC_APB1ENR_WWDGEN_MORT                  ((uint32_t)0x00000800)
#define  RCC_APB1ENR_SPI2EN_MORT                  ((uint32_t)0x00004000)
#define  RCC_APB1ENR_SPI3EN_MORT                  ((uint32_t)0x00008000)
#if defined(STM32F446xx_MORT)
#define  RCC_APB1ENR_SPDIFRXEN_MORT               ((uint32_t)0x00010000)
#endif /* STM32F446xx_MORT */
#define  RCC_APB1ENR_USART2EN_MORT                ((uint32_t)0x00020000)
#define  RCC_APB1ENR_USART3EN_MORT                ((uint32_t)0x00040000)
#define  RCC_APB1ENR_UART4EN_MORT                 ((uint32_t)0x00080000)
#define  RCC_APB1ENR_UART5EN_MORT                 ((uint32_t)0x00100000)
#define  RCC_APB1ENR_I2C1EN_MORT                  ((uint32_t)0x00200000)
#define  RCC_APB1ENR_I2C2EN_MORT                  ((uint32_t)0x00400000)
#define  RCC_APB1ENR_I2C3EN_MORT                  ((uint32_t)0x00800000)
#if defined(STM32F410xx) || defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F446xx_MORT)
#define  RCC_APB1ENR_FMPI2C1EN_MORT               ((uint32_t)0x01000000)
#endif /* STM32F410xx || STM32F412xG || STM32F413_423xx || STM32F446xx_MORT */
#define  RCC_APB1ENR_CAN1EN_MORT                  ((uint32_t)0x02000000)
#define  RCC_APB1ENR_CAN2EN_MORT                  ((uint32_t)0x04000000)
#if defined(STM32F446xx_MORT)
#define  RCC_APB1ENR_CECEN_MORT                   ((uint32_t)0x08000000)
#endif /* STM32F446xx_MORT */
#define  RCC_APB1ENR_PWREN_MORT                   ((uint32_t)0x10000000)
#define  RCC_APB1ENR_DACEN_MORT                   ((uint32_t)0x20000000)
#define  RCC_APB1ENR_UART7EN_MORT                 ((uint32_t)0x40000000)
#define  RCC_APB1ENR_UART8EN_MORT                 ((uint32_t)0x80000000)

/********************  Bit definition for RCC_APB2ENR register  ***************/
#define  RCC_APB2ENR_TIM1EN_MORT                  ((uint32_t)0x00000001)
#define  RCC_APB2ENR_TIM8EN_MORT                  ((uint32_t)0x00000002)
#define  RCC_APB2ENR_USART1EN_MORT                ((uint32_t)0x00000010)
#define  RCC_APB2ENR_USART6EN_MORT                ((uint32_t)0x00000020)
#define  RCC_APB2ENR_UART9EN_MORT                 ((uint32_t)0x00000040)
#define  RCC_APB2ENR_UART10EN_MORT                ((uint32_t)0x00000080)
#define  RCC_APB2ENR_ADC1EN_MORT                  ((uint32_t)0x00000100)
#define  RCC_APB2ENR_ADC2EN_MORT                  ((uint32_t)0x00000200)
#define  RCC_APB2ENR_ADC3EN_MORT                  ((uint32_t)0x00000400)
#define  RCC_APB2ENR_SDIOEN_MORT                  ((uint32_t)0x00000800)
#define  RCC_APB2ENR_SPI1EN_MORT                  ((uint32_t)0x00001000)
#define  RCC_APB2ENR_SPI4EN_MORT                  ((uint32_t)0x00002000)
#define  RCC_APB2ENR_SYSCFGEN_MORT                ((uint32_t)0x00004000)
#define  RCC_APB2ENR_EXTIEN_MORT                  ((uint32_t)0x00008000)
#define  RCC_APB2ENR_TIM9EN_MORT                  ((uint32_t)0x00010000)
#define  RCC_APB2ENR_TIM10EN_MORT                 ((uint32_t)0x00020000)
#define  RCC_APB2ENR_TIM11EN_MORT                 ((uint32_t)0x00040000)
#define  RCC_APB2ENR_SPI5EN_MORT                  ((uint32_t)0x00100000)
#define  RCC_APB2ENR_SPI6EN_MORT                  ((uint32_t)0x00200000)
#define  RCC_APB2ENR_SAI1EN_MORT                  ((uint32_t)0x00400000)
#if defined(STM32F446xx_MORT)
#define  RCC_APB2ENR_SAI2EN_MORT                  ((uint32_t)0x00800000)
#endif /* STM32F446xx_MORT */
#define  RCC_APB2ENR_LTDCEN_MORT                  ((uint32_t)0x04000000)
#if defined(STM32F469_479xx)
#define  RCC_APB2ENR_DSIEN_MORT                   ((uint32_t)0x08000000)
#endif /* STM32F469_479xx */
#if defined(STM32F412xG) || defined(STM32F413_423xx)
#define  RCC_APB2ENR_DFSDM1EN_MORT                ((uint32_t)0x01000000)
#endif /* STM32F412xG || STM32F413_423xx */
#if defined(STM32F413_423xx)
#define  RCC_APB2ENR_DFSDM2EN_MORT                ((uint32_t)0x02000000)
#endif /* STM32F413_423xx */
/********************  Bit definition for RCC_AHB1LPENR register  *************/
#define  RCC_AHB1LPENR_GPIOALPEN_MORT             ((uint32_t)0x00000001)
#define  RCC_AHB1LPENR_GPIOBLPEN_MORT             ((uint32_t)0x00000002)
#define  RCC_AHB1LPENR_GPIOCLPEN_MORT             ((uint32_t)0x00000004)
#define  RCC_AHB1LPENR_GPIODLPEN_MORT             ((uint32_t)0x00000008)
#define  RCC_AHB1LPENR_GPIOELPEN_MORT             ((uint32_t)0x00000010)
#define  RCC_AHB1LPENR_GPIOFLPEN_MORT             ((uint32_t)0x00000020)
#define  RCC_AHB1LPENR_GPIOGLPEN_MORT             ((uint32_t)0x00000040)
#define  RCC_AHB1LPENR_GPIOHLPEN_MORT             ((uint32_t)0x00000080)
#define  RCC_AHB1LPENR_GPIOILPEN_MORT             ((uint32_t)0x00000100)
#define  RCC_AHB1LPENR_GPIOJLPEN_MORT             ((uint32_t)0x00000200)
#define  RCC_AHB1LPENR_GPIOKLPEN_MORT             ((uint32_t)0x00000400)
#define  RCC_AHB1LPENR_CRCLPEN_MORT               ((uint32_t)0x00001000)
#define  RCC_AHB1LPENR_FLITFLPEN_MORT             ((uint32_t)0x00008000)
#define  RCC_AHB1LPENR_SRAM1LPEN_MORT             ((uint32_t)0x00010000)
#define  RCC_AHB1LPENR_SRAM2LPEN_MORT             ((uint32_t)0x00020000)
#define  RCC_AHB1LPENR_BKPSRAMLPEN_MORT           ((uint32_t)0x00040000)
#define  RCC_AHB1LPENR_SRAM3LPEN_MORT             ((uint32_t)0x00080000)
#define  RCC_AHB1LPENR_DMA1LPEN_MORT              ((uint32_t)0x00200000)
#define  RCC_AHB1LPENR_DMA2LPEN_MORT              ((uint32_t)0x00400000)
#define  RCC_AHB1LPENR_DMA2DLPEN_MORT             ((uint32_t)0x00800000)
#define  RCC_AHB1LPENR_ETHMACLPEN_MORT            ((uint32_t)0x02000000)
#define  RCC_AHB1LPENR_ETHMACTXLPEN_MORT          ((uint32_t)0x04000000)
#define  RCC_AHB1LPENR_ETHMACRXLPEN_MORT          ((uint32_t)0x08000000)
#define  RCC_AHB1LPENR_ETHMACPTPLPEN_MORT         ((uint32_t)0x10000000)
#define  RCC_AHB1LPENR_OTGHSLPEN_MORT             ((uint32_t)0x20000000)
#define  RCC_AHB1LPENR_OTGHSULPILPEN_MORT         ((uint32_t)0x40000000)

/********************  Bit definition for RCC_AHB2LPENR register  *************/
#define  RCC_AHB2LPENR_DCMILPEN_MORT              ((uint32_t)0x00000001)
#define  RCC_AHB2LPENR_CRYPLPEN_MORT              ((uint32_t)0x00000010)
#define  RCC_AHB2LPENR_HASHLPEN_MORT              ((uint32_t)0x00000020)
#define  RCC_AHB2LPENR_RNGLPEN_MORT               ((uint32_t)0x00000040)
#define  RCC_AHB2LPENR_OTGFSLPEN_MORT             ((uint32_t)0x00000080)

/********************  Bit definition for RCC_AHB3LPENR register  *************/
#if defined(STM32F40_41xxx) || defined(STM32F412xG) || defined(STM32F413_423xx)
#define  RCC_AHB3LPENR_FSMCLPEN_MORT              ((uint32_t)0x00000001)
#endif /* STM32F40_41xxx || STM32F412xG || STM32F413_423xx */

#if defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F446xx_MORT) || defined(STM32F469_479xx)
#define  RCC_AHB3LPENR_FMCLPEN_MORT              ((uint32_t)0x00000001)
#endif /* STM32F427_437xx ||  STM32F429_439xx  || STM32F446xx_MORT || STM32F469_479xx */
#if defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F446xx_MORT) || defined(STM32F469_479xx)
#define  RCC_AHB3LPENR_QSPILPEN_MORT             ((uint32_t)0x00000002)
#endif /* STM32F412xG || STM32F413_423xx || STM32F469_479xx || STM32F446xx_MORT */

/********************  Bit definition for RCC_APB1LPENR register  *************/
#define  RCC_APB1LPENR_TIM2LPEN_MORT              ((uint32_t)0x00000001)
#define  RCC_APB1LPENR_TIM3LPEN_MORT              ((uint32_t)0x00000002)
#define  RCC_APB1LPENR_TIM4LPEN_MORT              ((uint32_t)0x00000004)
#define  RCC_APB1LPENR_TIM5LPEN_MORT              ((uint32_t)0x00000008)
#define  RCC_APB1LPENR_TIM6LPEN_MORT              ((uint32_t)0x00000010)
#define  RCC_APB1LPENR_TIM7LPEN_MORT              ((uint32_t)0x00000020)
#define  RCC_APB1LPENR_TIM12LPEN_MORT             ((uint32_t)0x00000040)
#define  RCC_APB1LPENR_TIM13LPEN_MORT             ((uint32_t)0x00000080)
#define  RCC_APB1LPENR_TIM14LPEN_MORT             ((uint32_t)0x00000100)
#if defined(STM32F410xx) || defined(STM32F413_423xx)
#define  RCC_APB1LPENR_LPTIM1LPEN_MORT            ((uint32_t)0x00000200)
#endif /* STM32F410xx || STM32F413_423xx */
#define  RCC_APB1LPENR_WWDGLPEN_MORT              ((uint32_t)0x00000800)
#define  RCC_APB1LPENR_SPI2LPEN_MORT              ((uint32_t)0x00004000)
#define  RCC_APB1LPENR_SPI3LPEN_MORT              ((uint32_t)0x00008000)
#if defined(STM32F446xx_MORT)
#define  RCC_APB1LPENR_SPDIFRXLPEN_MORT           ((uint32_t)0x00010000)
#endif /* STM32F446xx_MORT */
#define  RCC_APB1LPENR_USART2LPEN_MORT            ((uint32_t)0x00020000)
#define  RCC_APB1LPENR_USART3LPEN_MORT            ((uint32_t)0x00040000)
#define  RCC_APB1LPENR_UART4LPEN_MORT             ((uint32_t)0x00080000)
#define  RCC_APB1LPENR_UART5LPEN_MORT             ((uint32_t)0x00100000)
#define  RCC_APB1LPENR_I2C1LPEN_MORT              ((uint32_t)0x00200000)
#define  RCC_APB1LPENR_I2C2LPEN_MORT              ((uint32_t)0x00400000)
#define  RCC_APB1LPENR_I2C3LPEN_MORT              ((uint32_t)0x00800000)
#if defined(STM32F410xx) || defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F446xx_MORT)
#define  RCC_APB1LPENR_FMPI2C1LPEN_MORT           ((uint32_t)0x01000000)
#endif /* STM32F410xx || STM32F412xG || STM32F413_423xx || STM32F446xx_MORT */
#define  RCC_APB1LPENR_CAN1LPEN_MORT              ((uint32_t)0x02000000)
#define  RCC_APB1LPENR_CAN2LPEN_MORT              ((uint32_t)0x04000000)
#if defined(STM32F446xx_MORT)
#define  RCC_APB1LPENR_CECLPEN_MORT               ((uint32_t)0x08000000)
#endif /* STM32F446xx_MORT */
#define  RCC_APB1LPENR_PWRLPEN_MORT               ((uint32_t)0x10000000)
#define  RCC_APB1LPENR_DACLPEN_MORT               ((uint32_t)0x20000000)
#define  RCC_APB1LPENR_UART7LPEN_MORT             ((uint32_t)0x40000000)
#define  RCC_APB1LPENR_UART8LPEN_MORT             ((uint32_t)0x80000000)

/********************  Bit definition for RCC_APB2LPENR register  *************/
#define  RCC_APB2LPENR_TIM1LPEN_MORT              ((uint32_t)0x00000001)
#define  RCC_APB2LPENR_TIM8LPEN_MORT              ((uint32_t)0x00000002)
#define  RCC_APB2LPENR_USART1LPEN_MORT            ((uint32_t)0x00000010)
#define  RCC_APB2LPENR_USART6LPEN_MORT            ((uint32_t)0x00000020)
#define  RCC_APB2LPENR_UART9LPEN_MORT             ((uint32_t)0x00000040)
#define  RCC_APB2LPENR_UART10LPEN_MORT            ((uint32_t)0x00000080)
#define  RCC_APB2LPENR_ADC1LPEN_MORT              ((uint32_t)0x00000100)
#define  RCC_APB2LPENR_ADC2PEN_MORT               ((uint32_t)0x00000200)
#define  RCC_APB2LPENR_ADC3LPEN_MORT              ((uint32_t)0x00000400)
#define  RCC_APB2LPENR_SDIOLPEN_MORT              ((uint32_t)0x00000800)
#define  RCC_APB2LPENR_SPI1LPEN_MORT              ((uint32_t)0x00001000)
#define  RCC_APB2LPENR_SPI4LPEN_MORT              ((uint32_t)0x00002000)
#define  RCC_APB2LPENR_SYSCFGLPEN_MORT            ((uint32_t)0x00004000)
#define  RCC_APB2LPENR_TIM9LPEN_MORT              ((uint32_t)0x00010000)
#define  RCC_APB2LPENR_TIM10LPEN_MORT             ((uint32_t)0x00020000)
#define  RCC_APB2LPENR_TIM11LPEN_MORT             ((uint32_t)0x00040000)
#define  RCC_APB2LPENR_SPI5LPEN_MORT              ((uint32_t)0x00100000)
#define  RCC_APB2LPENR_SPI6LPEN_MORT              ((uint32_t)0x00200000)
#define  RCC_APB2LPENR_SAI1LPEN_MORT              ((uint32_t)0x00400000)
#if defined(STM32F446xx_MORT)
#define  RCC_APB2LPENR_SAI2LPEN_MORT              ((uint32_t)0x00800000)
#endif /* STM32F446xx_MORT */
#define  RCC_APB2LPENR_LTDCLPEN_MORT              ((uint32_t)0x04000000)
#if defined(STM32F469_479xx)

#endif /* STM32F469_479xx */
#if defined(STM32F412xG) || defined(STM32F413_423xx)

#endif /* STM32F412xG || STM32F413_423xx */
#if defined(STM32F413_423xx)

#endif /* STM32F413_423xx */

/********************  Bit definition for RCC_BDCR register  ******************/
#define  RCC_BDCR_LSEON_MORT                      ((uint32_t)0x00000001)
#define  RCC_BDCR_LSERDY_MORT                     ((uint32_t)0x00000002)
#define  RCC_BDCR_LSEBYP_MORT                     ((uint32_t)0x00000004)
#define  RCC_BDCR_LSEMOD_MORT                     ((uint32_t)0x00000008)

#define  RCC_BDCR_RTCSEL_MORT                    ((uint32_t)0x00000300)
#define  RCC_BDCR_RTCSEL_0_MORT                  ((uint32_t)0x00000100)
#define  RCC_BDCR_RTCSEL_1_MORT                  ((uint32_t)0x00000200)

#define  RCC_BDCR_RTCEN_MORT                      ((uint32_t)0x00008000)
#define  RCC_BDCR_BDRST_MORT                      ((uint32_t)0x00010000)

/********************  Bit definition for RCC_CSR register  *******************/
#define  RCC_CSR_LSION_MORT                       ((uint32_t)0x00000001)
#define  RCC_CSR_LSIRDY_MORT                      ((uint32_t)0x00000002)
#define  RCC_CSR_RMVF_MORT                        ((uint32_t)0x01000000)
#define  RCC_CSR_BORRSTF_MORT                     ((uint32_t)0x02000000)
#define  RCC_CSR_PADRSTF_MORT                     ((uint32_t)0x04000000)
#define  RCC_CSR_PORRSTF_MORT                     ((uint32_t)0x08000000)
#define  RCC_CSR_SFTRSTF_MORT                     ((uint32_t)0x10000000)
#define  RCC_CSR_WDGRSTF_MORT                     ((uint32_t)0x20000000)
#define  RCC_CSR_WWDGRSTF_MORT                    ((uint32_t)0x40000000)
#define  RCC_CSR_LPWRRSTF_MORT                    ((uint32_t)0x80000000)

/********************  Bit definition for RCC_SSCGR register  *****************/
#define  RCC_SSCGR_MODPER_MORT                    ((uint32_t)0x00001FFF)
#define  RCC_SSCGR_INCSTEP_MORT                   ((uint32_t)0x0FFFE000)
#define  RCC_SSCGR_SPREADSEL_MORT                 ((uint32_t)0x40000000)
#define  RCC_SSCGR_SSCGEN_MORT                    ((uint32_t)0x80000000)

/********************  Bit definition for RCC_PLLI2SCFGR register  ************/
#define  RCC_PLLI2SCFGR_PLLI2SM_MORT              ((uint32_t)0x0000003F)
#define  RCC_PLLI2SCFGR_PLLI2SM_0_MORT            ((uint32_t)0x00000001)
#define  RCC_PLLI2SCFGR_PLLI2SM_1_MORT            ((uint32_t)0x00000002)
#define  RCC_PLLI2SCFGR_PLLI2SM_2_MORT            ((uint32_t)0x00000004)
#define  RCC_PLLI2SCFGR_PLLI2SM_3_MORT            ((uint32_t)0x00000008)
#define  RCC_PLLI2SCFGR_PLLI2SM_4_MORT            ((uint32_t)0x00000010)
#define  RCC_PLLI2SCFGR_PLLI2SM_5_MORT            ((uint32_t)0x00000020)

#define  RCC_PLLI2SCFGR_PLLI2SN_MORT              ((uint32_t)0x00007FC0)
#define  RCC_PLLI2SCFGR_PLLI2SN_0_MORT            ((uint32_t)0x00000040)
#define  RCC_PLLI2SCFGR_PLLI2SN_1_MORT            ((uint32_t)0x00000080)
#define  RCC_PLLI2SCFGR_PLLI2SN_2_MORT            ((uint32_t)0x00000100)
#define  RCC_PLLI2SCFGR_PLLI2SN_3_MORT            ((uint32_t)0x00000200)
#define  RCC_PLLI2SCFGR_PLLI2SN_4_MORT            ((uint32_t)0x00000400)
#define  RCC_PLLI2SCFGR_PLLI2SN_5_MORT            ((uint32_t)0x00000800)
#define  RCC_PLLI2SCFGR_PLLI2SN_6_MORT            ((uint32_t)0x00001000)
#define  RCC_PLLI2SCFGR_PLLI2SN_7_MORT            ((uint32_t)0x00002000)
#define  RCC_PLLI2SCFGR_PLLI2SN_8_MORT            ((uint32_t)0x00004000)

#if defined(STM32F412xG) || defined(STM32F413_423xx)

#endif /* STM32F412xG || STM32F413_423xx */

#if defined(STM32F446xx_MORT)
#define  RCC_PLLI2SCFGR_PLLI2SP_MORT              ((uint32_t)0x00030000)
#define  RCC_PLLI2SCFGR_PLLI2SP_0_MORT            ((uint32_t)0x00010000)
#define  RCC_PLLI2SCFGR_PLLI2SP_1_MORT            ((uint32_t)0x00020000)
#endif /* STM32F446xx_MORT */

#define  RCC_PLLI2SCFGR_PLLI2SQ_MORT              ((uint32_t)0x0F000000)
#define  RCC_PLLI2SCFGR_PLLI2SQ_0_MORT            ((uint32_t)0x01000000)
#define  RCC_PLLI2SCFGR_PLLI2SQ_1_MORT            ((uint32_t)0x02000000)
#define  RCC_PLLI2SCFGR_PLLI2SQ_2_MORT            ((uint32_t)0x04000000)
#define  RCC_PLLI2SCFGR_PLLI2SQ_3_MORT            ((uint32_t)0x08000000)

#define  RCC_PLLI2SCFGR_PLLI2SR_MORT              ((uint32_t)0x70000000)
#define  RCC_PLLI2SCFGR_PLLI2SR_0_MORT            ((uint32_t)0x10000000)
#define  RCC_PLLI2SCFGR_PLLI2SR_1_MORT            ((uint32_t)0x20000000)
#define  RCC_PLLI2SCFGR_PLLI2SR_2_MORT            ((uint32_t)0x40000000)

/********************  Bit definition for RCC_PLLSAICFGR register  ************/
#if defined(STM32F446xx_MORT)
#define  RCC_PLLSAICFGR_PLLSAIM_MORT              ((uint32_t)0x0000003F)
#define  RCC_PLLSAICFGR_PLLSAIM_0_MORT            ((uint32_t)0x00000001)
#define  RCC_PLLSAICFGR_PLLSAIM_1_MORT            ((uint32_t)0x00000002)
#define  RCC_PLLSAICFGR_PLLSAIM_2_MORT            ((uint32_t)0x00000004)
#define  RCC_PLLSAICFGR_PLLSAIM_3_MORT            ((uint32_t)0x00000008)
#define  RCC_PLLSAICFGR_PLLSAIM_4_MORT            ((uint32_t)0x00000010)
#define  RCC_PLLSAICFGR_PLLSAIM_5_MORT            ((uint32_t)0x00000020)
#endif /* STM32F446xx_MORT */

#define  RCC_PLLSAICFGR_PLLSAIN_MORT              ((uint32_t)0x00007FC0)
#define  RCC_PLLSAICFGR_PLLSAIN_0_MORT            ((uint32_t)0x00000040)
#define  RCC_PLLSAICFGR_PLLSAIN_1_MORT            ((uint32_t)0x00000080)
#define  RCC_PLLSAICFGR_PLLSAIN_2_MORT            ((uint32_t)0x00000100)
#define  RCC_PLLSAICFGR_PLLSAIN_3_MORT            ((uint32_t)0x00000200)
#define  RCC_PLLSAICFGR_PLLSAIN_4_MORT            ((uint32_t)0x00000400)
#define  RCC_PLLSAICFGR_PLLSAIN_5_MORT            ((uint32_t)0x00000800)
#define  RCC_PLLSAICFGR_PLLSAIN_6_MORT            ((uint32_t)0x00001000)
#define  RCC_PLLSAICFGR_PLLSAIN_7_MORT            ((uint32_t)0x00002000)
#define  RCC_PLLSAICFGR_PLLSAIN_8_MORT            ((uint32_t)0x00004000)

#if defined(STM32F446xx_MORT) || defined(STM32F469_479xx)  
#define  RCC_PLLSAICFGR_PLLSAIP_MORT              ((uint32_t)0x00030000)
#define  RCC_PLLSAICFGR_PLLSAIP_0_MORT            ((uint32_t)0x00010000)
#define  RCC_PLLSAICFGR_PLLSAIP_1_MORT            ((uint32_t)0x00020000)
#endif /* STM32F446xx_MORT || STM32F469_479xx */

#define  RCC_PLLSAICFGR_PLLSAIQ_MORT              ((uint32_t)0x0F000000)
#define  RCC_PLLSAICFGR_PLLSAIQ_0_MORT            ((uint32_t)0x01000000)
#define  RCC_PLLSAICFGR_PLLSAIQ_1_MORT            ((uint32_t)0x02000000)
#define  RCC_PLLSAICFGR_PLLSAIQ_2_MORT            ((uint32_t)0x04000000)
#define  RCC_PLLSAICFGR_PLLSAIQ_3_MORT            ((uint32_t)0x08000000)

#define  RCC_PLLSAICFGR_PLLSAIR_MORT              ((uint32_t)0x70000000)
#define  RCC_PLLSAICFGR_PLLSAIR_0_MORT            ((uint32_t)0x10000000)
#define  RCC_PLLSAICFGR_PLLSAIR_1_MORT            ((uint32_t)0x20000000)
#define  RCC_PLLSAICFGR_PLLSAIR_2_MORT            ((uint32_t)0x40000000)

/********************  Bit definition for RCC_DCKCFGR register  ***************/
#define  RCC_DCKCFGR_PLLI2SDIVQ_MORT              ((uint32_t)0x0000001F)
#define  RCC_DCKCFGR_PLLSAIDIVQ_MORT              ((uint32_t)0x00001F00)
#define  RCC_DCKCFGR_PLLSAIDIVR_MORT              ((uint32_t)0x00030000)

#if defined(STM32F412xG) || defined(STM32F413_423xx)

#endif /* STM32F412xG || STM32F413_423xx */

#if defined(STM32F413_423xx)

#endif /* STM32F413_423xx */

#define  RCC_DCKCFGR_SAI1ASRC_MORT                ((uint32_t)0x00300000)
#define  RCC_DCKCFGR_SAI1ASRC_0_MORT              ((uint32_t)0x00100000)
#define  RCC_DCKCFGR_SAI1ASRC_1_MORT              ((uint32_t)0x00200000)
#if defined(STM32F446xx_MORT)
#define  RCC_DCKCFGR_SAI1SRC_MORT                 ((uint32_t)0x00300000)
#define  RCC_DCKCFGR_SAI1SRC_0_MORT               ((uint32_t)0x00100000)
#define  RCC_DCKCFGR_SAI1SRC_1_MORT               ((uint32_t)0x00200000)
#endif /* STM32F446xx_MORT */

#define  RCC_DCKCFGR_SAI1BSRC_MORT                ((uint32_t)0x00C00000)
#define  RCC_DCKCFGR_SAI1BSRC_0_MORT              ((uint32_t)0x00400000)
#define  RCC_DCKCFGR_SAI1BSRC_1_MORT              ((uint32_t)0x00800000)
#if defined(STM32F446xx_MORT)
#define  RCC_DCKCFGR_SAI2SRC_MORT                 ((uint32_t)0x00C00000)
#define  RCC_DCKCFGR_SAI2SRC_0_MORT               ((uint32_t)0x00400000)
#define  RCC_DCKCFGR_SAI2SRC_1_MORT               ((uint32_t)0x00800000)
#endif /* STM32F446xx_MORT */

#define  RCC_DCKCFGR_TIMPRE_MORT                  ((uint32_t)0x01000000)
#if defined(STM32F469_479xx)

#endif /* STM32F469_479xx */

#if defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F446xx_MORT)
#define  RCC_DCKCFGR_I2S1SRC_MORT                 ((uint32_t)0x06000000)
#define  RCC_DCKCFGR_I2S1SRC_0_MORT               ((uint32_t)0x02000000)
#define  RCC_DCKCFGR_I2S1SRC_1_MORT               ((uint32_t)0x04000000)
#define  RCC_DCKCFGR_I2S2SRC_MORT                 ((uint32_t)0x18000000)
#define  RCC_DCKCFGR_I2S2SRC_0_MORT               ((uint32_t)0x08000000)
#define  RCC_DCKCFGR_I2S2SRC_1_MORT               ((uint32_t)0x10000000)

/********************  Bit definition for RCC_CKGATENR register  ***************/
#define  RCC_CKGATENR_AHB2APB1_CKEN_MORT          ((uint32_t)0x00000001)
#define  RCC_CKGATENR_AHB2APB2_CKEN_MORT          ((uint32_t)0x00000002)
#define  RCC_CKGATENR_CM4DBG_CKEN_MORT            ((uint32_t)0x00000004)
#define  RCC_CKGATENR_SPARE_CKEN_MORT             ((uint32_t)0x00000008)
#define  RCC_CKGATENR_SRAM_CKEN_MORT              ((uint32_t)0x00000010)
#define  RCC_CKGATENR_FLITF_CKEN_MORT             ((uint32_t)0x00000020)
#define  RCC_CKGATENR_RCC_CKEN_MORT               ((uint32_t)0x00000040)
#if defined(STM32F412xG) || defined(STM32F413_423xx)

#endif /* STM32F412xG || STM32F413_423xx */

/********************  Bit definition for RCC_DCKCFGR2 register  ***************/
#define  RCC_DCKCFGR2_FMPI2C1SEL_MORT             ((uint32_t)0x00C00000)
#define  RCC_DCKCFGR2_FMPI2C1SEL_0_MORT           ((uint32_t)0x00400000)
#define  RCC_DCKCFGR2_FMPI2C1SEL_1_MORT           ((uint32_t)0x00800000)
#define  RCC_DCKCFGR2_CECSEL_MORT                 ((uint32_t)0x04000000)
#define  RCC_DCKCFGR2_CK48MSEL_MORT               ((uint32_t)0x08000000)
#define  RCC_DCKCFGR2_SDIOSEL_MORT                ((uint32_t)0x10000000)
#if defined(STM32F446xx_MORT)
#define  RCC_DCKCFGR2_SPDIFRXSEL_MORT             ((uint32_t)0x20000000)
#endif /* STM32F446xx_MORT */
#if defined(STM32F413_423xx)

#endif /* STM32F413_423xx */
#endif /* STM32F412xG || STM32F413_423xx || STM32F446xx_MORT */

#if defined(STM32F410xx)

#endif /* STM32F410xx */

#if defined(STM32F410xx)
/********************  Bit definition for RCC_DCKCFGR2 register  **************/

#endif /* STM32F410xx */
/******************************************************************************/
/*                                                                            */
/*                                    RNG_MORT                                     */
/*                                                                            */
/******************************************************************************/
/********************  Bits definition for RNG_CR register  *******************/
#define RNG_CR_RNGEN_MORT                         ((uint32_t)0x00000004)
#define RNG_CR_IE_MORT                            ((uint32_t)0x00000008)

/********************  Bits definition for RNG_SR register  *******************/
#define RNG_SR_DRDY_MORT                          ((uint32_t)0x00000001)
#define RNG_SR_CECS_MORT                          ((uint32_t)0x00000002)
#define RNG_SR_SECS_MORT                          ((uint32_t)0x00000004)
#define RNG_SR_CEIS_MORT                          ((uint32_t)0x00000020)
#define RNG_SR_SEIS_MORT                          ((uint32_t)0x00000040)

/******************************************************************************/
/*                                                                            */
/*                           Real-Time Clock (RTC_MORT)                            */
/*                                                                            */
/******************************************************************************/
/********************  Bits definition for RTC_TR register  *******************/


/********************  Bits definition for RTC_DR register  *******************/


/********************  Bits definition for RTC_CR register  *******************/


/********************  Bits definition for RTC_ISR register  ******************/


/********************  Bits definition for RTC_PRER register  *****************/


/********************  Bits definition for RTC_WUTR register  *****************/

/********************  Bits definition for RTC_CALIBR register  ***************/


/********************  Bits definition for RTC_ALRMAR register  ***************/

/********************  Bits definition for RTC_ALRMBR register  ***************/

/********************  Bits definition for RTC_WPR register  ******************/


/********************  Bits definition for RTC_SSR register  ******************/


/********************  Bits definition for RTC_SHIFTR register  ***************/


/********************  Bits definition for RTC_TSTR register  *****************/


/********************  Bits definition for RTC_TSDR register  *****************/

/********************  Bits definition for RTC_TSSSR register  ****************/


/********************  Bits definition for RTC_CAL register  *****************/

/********************  Bits definition for RTC_TAFCR register  ****************/

/********************  Bits definition for RTC_ALRMASSR register  *************/

/********************  Bits definition for RTC_ALRMBSSR register  *************/

/********************  Bits definition for RTC_BKP0R register  ****************/

/********************  Bits definition for RTC_BKP1R register  ****************/

/********************  Bits definition for RTC_BKP2R register  ****************/

/********************  Bits definition for RTC_BKP3R register  ****************/

/********************  Bits definition for RTC_BKP4R register  ****************/

/********************  Bits definition for RTC_BKP5R register  ****************/

/********************  Bits definition for RTC_BKP6R register  ****************/

/********************  Bits definition for RTC_BKP7R register  ****************/

/********************  Bits definition for RTC_BKP8R register  ****************/


/********************  Bits definition for RTC_BKP9R register  ****************/


/********************  Bits definition for RTC_BKP10R register  ***************/

/********************  Bits definition for RTC_BKP11R register  ***************/

/********************  Bits definition for RTC_BKP12R register  ***************/

/********************  Bits definition for RTC_BKP13R register  ***************/

/********************  Bits definition for RTC_BKP14R register  ***************/

/********************  Bits definition for RTC_BKP15R register  ***************/

/********************  Bits definition for RTC_BKP16R register  ***************/


/********************  Bits definition for RTC_BKP17R register  ***************/

/********************  Bits definition for RTC_BKP18R register  ***************/

/********************  Bits definition for RTC_BKP19R register  ***************/

/******************************************************************************/
/*                                                                            */
/*                          Serial Audio Interface                            */
/*                                                                            */
/******************************************************************************/
/********************  Bit definition for SAI_GCR register  *******************/

/*******************  Bit definition for SAI_xCR1 register  *******************/

/*******************  Bit definition for SAI_xCR2 register  *******************/

/******************  Bit definition for SAI_xFRCR register  *******************/


/******************  Bit definition for SAI_xSLOTR register  *******************/

/*******************  Bit definition for SAI_xIMR register  *******************/

/********************  Bit definition for SAI_xSR register  *******************/

/******************  Bit definition for SAI_xCLRFR register  ******************/

/******************  Bit definition for SAI_xDR register  ******************/
     

#if defined(STM32F446xx_MORT)
/******************************************************************************/
/*                                                                            */
/*                              SPDIF-RX Interface                            */
/*                                                                            */
/******************************************************************************/
/********************  Bit definition for SPDIFRX_CR register  *******************/

/*******************  Bit definition for SPDIFRX_IMR register  *******************/

/*******************  Bit definition for SPDIFRX_SR register  *******************/

/*******************  Bit definition for SPDIFRX_IFCR register  *******************/

/*******************  Bit definition for SPDIFRX_DR register  (DRFMT = 0b00 case) *******************/

/*******************  Bit definition for SPDIFRX_DR register  (DRFMT = 0b01 case) *******************/

/*******************  Bit definition for SPDIFRX_DR register  (DRFMT = 0b10 case) *******************/

/*******************  Bit definition for SPDIFRX_CSR register   *******************/

/*******************  Bit definition for SPDIFRX_DIR register    *******************/

#endif /* STM32F446xx_MORT */

/******************************************************************************/
/*                                                                            */
/*                          SD host Interface                                 */
/*                                                                            */
/******************************************************************************/
/******************  Bit definition for SDIO_POWER register  ******************/

/******************  Bit definition for SDIO_CLKCR register  ******************/

/*******************  Bit definition for SDIO_ARG register  *******************/

/*******************  Bit definition for SDIO_CMD register  *******************/

/*****************  Bit definition for SDIO_RESPCMD register  *****************/

/******************  Bit definition for SDIO_RESP0 register  ******************/

/******************  Bit definition for SDIO_RESP1 register  ******************/

/******************  Bit definition for SDIO_RESP2 register  ******************/

/******************  Bit definition for SDIO_RESP3 register  ******************/

/******************  Bit definition for SDIO_RESP4 register  ******************/

/******************  Bit definition for SDIO_DTIMER register  *****************/

/******************  Bit definition for SDIO_DLEN register  *******************/

/******************  Bit definition for SDIO_DCTRL register  ******************/

/******************  Bit definition for SDIO_DCOUNT register  *****************/

/******************  Bit definition for SDIO_STA register  ********************/

/*******************  Bit definition for SDIO_ICR register  *******************/
 

/******************  Bit definition for SDIO_MASK register  *******************/

/*****************  Bit definition for SDIO_FIFOCNT register  *****************/

/******************  Bit definition for SDIO_FIFO register  *******************/

/******************************************************************************/
/*                                                                            */
/*                        Serial Peripheral Interface                         */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for SPI_CR1 register  ********************/
#define  SPI_CR1_CPHA_MORT                        ((uint16_t)0x0001)            /*!<Clock Phase      */
#define  SPI_CR1_CPOL_MORT                        ((uint16_t)0x0002)            /*!<Clock Polarity   */
#define  SPI_CR1_MSTR_MORT                        ((uint16_t)0x0004)            /*!<Master Selection */

#define  SPI_CR1_BR_MORT                          ((uint16_t)0x0038)            /*!<BR[2:0] bits (Baud Rate Control) */
#define  SPI_CR1_BR_0_MORT                        ((uint16_t)0x0008)            /*!<Bit 0 */
#define  SPI_CR1_BR_1_MORT                        ((uint16_t)0x0010)            /*!<Bit 1 */
#define  SPI_CR1_BR_2_MORT                        ((uint16_t)0x0020)            /*!<Bit 2 */

#define  SPI_CR1_SPE_MORT                         ((uint16_t)0x0040)            /*!<SPI Enable                          */
#define  SPI_CR1_LSBFIRST_MORT                    ((uint16_t)0x0080)            /*!<Frame Format                        */
#define  SPI_CR1_SSI_MORT                         ((uint16_t)0x0100)            /*!<Internal slave select               */
#define  SPI_CR1_SSM_MORT                         ((uint16_t)0x0200)            /*!<Software slave management           */
#define  SPI_CR1_RXONLY_MORT                      ((uint16_t)0x0400)            /*!<Receive only                        */
#define  SPI_CR1_DFF_MORT                         ((uint16_t)0x0800)            /*!<Data Frame Format                   */
#define  SPI_CR1_CRCNEXT_MORT                     ((uint16_t)0x1000)            /*!<Transmit CRC_MORT next                   */
#define  SPI_CR1_CRCEN_MORT                       ((uint16_t)0x2000)            /*!<Hardware CRC_MORT calculation enable     */
#define  SPI_CR1_BIDIOE_MORT                      ((uint16_t)0x4000)            /*!<Output enable in bidirectional mode */
#define  SPI_CR1_BIDIMODE_MORT                    ((uint16_t)0x8000)            /*!<Bidirectional data mode enable      */

/*******************  Bit definition for SPI_CR2 register  ********************/
#define  SPI_CR2_RXDMAEN_MORT                     ((uint8_t)0x01)               /*!<Rx Buffer DMA Enable                 */
#define  SPI_CR2_TXDMAEN_MORT                     ((uint8_t)0x02)               /*!<Tx Buffer DMA Enable                 */
#define  SPI_CR2_SSOE_MORT                        ((uint8_t)0x04)               /*!<SS Output Enable                     */
#define  SPI_CR2_ERRIE_MORT                       ((uint8_t)0x20)               /*!<Error Interrupt Enable               */
#define  SPI_CR2_RXNEIE_MORT                      ((uint8_t)0x40)               /*!<RX buffer Not Empty Interrupt Enable */
#define  SPI_CR2_TXEIE_MORT                       ((uint8_t)0x80)               /*!<Tx buffer Empty Interrupt Enable     */

/********************  Bit definition for SPI_SR register  ********************/
#define  SPI_SR_RXNE_MORT                         ((uint8_t)0x01)               /*!<Receive buffer Not Empty */
#define  SPI_SR_TXE_MORT                          ((uint8_t)0x02)               /*!<Transmit buffer Empty    */
#define  SPI_SR_CHSIDE_MORT                       ((uint8_t)0x04)               /*!<Channel side             */
#define  SPI_SR_UDR_MORT                          ((uint8_t)0x08)               /*!<Underrun flag            */
#define  SPI_SR_CRCERR_MORT                       ((uint8_t)0x10)               /*!<CRC_MORT Error flag           */
#define  SPI_SR_MODF_MORT                         ((uint8_t)0x20)               /*!<Mode fault               */
#define  SPI_SR_OVR_MORT                          ((uint8_t)0x40)               /*!<Overrun flag             */
#define  SPI_SR_BSY_MORT                          ((uint8_t)0x80)               /*!<Busy flag                */

/********************  Bit definition for SPI_DR register  ********************/
#define  SPI_DR_DR_MORT                           ((uint16_t)0xFFFF)            /*!<Data Register           */

/*******************  Bit definition for SPI_CRCPR register  ******************/
#define  SPI_CRCPR_CRCPOLY_MORT                   ((uint16_t)0xFFFF)            /*!<CRC_MORT polynomial register */

/******************  Bit definition for SPI_RXCRCR register  ******************/
#define  SPI_RXCRCR_RXCRC_MORT                    ((uint16_t)0xFFFF)            /*!<Rx CRC_MORT Register         */

/******************  Bit definition for SPI_TXCRCR register  ******************/
#define  SPI_TXCRCR_TXCRC_MORT                    ((uint16_t)0xFFFF)            /*!<Tx CRC_MORT Register         */

/******************  Bit definition for SPI_I2SCFGR register  *****************/
#define  SPI_I2SCFGR_CHLEN_MORT                   ((uint16_t)0x0001)            /*!<Channel length (number of bits per audio channel) */

#define  SPI_I2SCFGR_DATLEN_MORT                  ((uint16_t)0x0006)            /*!<DATLEN[1:0] bits (Data length to be transferred)  */
#define  SPI_I2SCFGR_DATLEN_0_MORT                ((uint16_t)0x0002)            /*!<Bit 0 */
#define  SPI_I2SCFGR_DATLEN_1_MORT                ((uint16_t)0x0004)            /*!<Bit 1 */

#define  SPI_I2SCFGR_CKPOL_MORT                   ((uint16_t)0x0008)            /*!<steady state clock polarity               */

#define  SPI_I2SCFGR_I2SSTD_MORT                  ((uint16_t)0x0030)            /*!<I2SSTD[1:0] bits (I2S standard selection) */
#define  SPI_I2SCFGR_I2SSTD_0_MORT                ((uint16_t)0x0010)            /*!<Bit 0 */
#define  SPI_I2SCFGR_I2SSTD_1_MORT                ((uint16_t)0x0020)            /*!<Bit 1 */

#define  SPI_I2SCFGR_PCMSYNC_MORT                 ((uint16_t)0x0080)            /*!<PCM frame synchronization                 */

#define  SPI_I2SCFGR_I2SCFG_MORT                  ((uint16_t)0x0300)            /*!<I2SCFG[1:0] bits (I2S configuration mode) */
#define  SPI_I2SCFGR_I2SCFG_0_MORT                ((uint16_t)0x0100)            /*!<Bit 0 */
#define  SPI_I2SCFGR_I2SCFG_1_MORT                ((uint16_t)0x0200)            /*!<Bit 1 */

#define  SPI_I2SCFGR_I2SE_MORT                    ((uint16_t)0x0400)            /*!<I2S Enable         */
#define  SPI_I2SCFGR_I2SMOD_MORT                  ((uint16_t)0x0800)            /*!<I2S mode selection */
#if defined(STM32F413_423xx) || defined(STM32F446xx_MORT)
#define  SPI_I2SCFGR_ASTRTEN_MORT                 ((uint16_t)0x1000)            /*!<Asynchronous start enable */
#endif /* STM32F413_423xx */

/******************  Bit definition for SPI_I2SPR register  *******************/
#define  SPI_I2SPR_I2SDIV_MORT                    ((uint16_t)0x00FF)            /*!<I2S Linear prescaler         */
#define  SPI_I2SPR_ODD_MORT                       ((uint16_t)0x0100)            /*!<Odd factor for the prescaler */
#define  SPI_I2SPR_MCKOE_MORT                     ((uint16_t)0x0200)            /*!<Master Clock Output Enable   */

/******************************************************************************/
/*                                                                            */
/*                                 SYSCFG_MORT                                     */
/*                                                                            */
/******************************************************************************/
/******************  Bit definition for SYSCFG_MEMRMP register  ***************/  

/******************  Bit definition for SYSCFG_PMC register  ******************/


/*****************  Bit definition for SYSCFG_EXTICR1 register  ***************/

/** 
  * @brief   EXTI0 configuration  
  */ 


/** 
  * @brief   EXTI1 configuration  
  */ 


/** 
  * @brief   EXTI2 configuration  
  */ 



/** 
  * @brief   EXTI3 configuration  
  */ 


/*****************  Bit definition for SYSCFG_EXTICR2 register  ***************/
        
/** 
  * @brief   EXTI4 configuration  
  */ 


/** 
  * @brief   EXTI5 configuration  
  */ 


/** 
  * @brief   EXTI6 configuration  
  */ 


/** 
  * @brief   EXTI7 configuration  
  */ 


/*****************  Bit definition for SYSCFG_EXTICR3 register  ***************/

/** 
  * @brief   EXTI8 configuration  
  */ 


/** 
  * @brief   EXTI9 configuration  
  */ 


/** 
  * @brief   EXTI10 configuration  
  */ 


/** 
  * @brief   EXTI11 configuration  
  */ 


/*****************  Bit definition for SYSCFG_EXTICR4 register  ***************/

/** 
  * @brief   EXTI12 configuration  
  */ 


/** 
  * @brief   EXTI13 configuration  
  */ 


/** 
  * @brief   EXTI14 configuration  
  */ 

/** 
  * @brief   EXTI15 configuration  
  */ 


#if defined(STM32F412xG) || defined(STM32F413_423xx)
/******************  Bit definition for SYSCFG_CFGR register  *****************/

#endif /* STM32F412xG || STM32413_423xx */

#if defined (STM32F410xx) || defined(STM32F412xG) || defined(STM32F413_423xx)
/******************  Bit definition for SYSCFG_CFGR2 register  ****************/
               
#endif /* STM32F410xx || STM32F412xG || STM32F413_423xx */
/******************  Bit definition for SYSCFG_CMPCR register  ****************/  

#if defined(STM32F413_423xx)
/******************  Bit definition for SYSCFG_MCHDLYCR register  *****************/

#endif /* STM32F413_423xx */

/******************************************************************************/
/*                                                                            */
/*                                    TIM                                     */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for TIM_CR1 register  ********************/
#define  TIM_CR1_CEN_MORT                         ((uint16_t)0x0001)            /*!<Counter enable        */
#define  TIM_CR1_UDIS_MORT                        ((uint16_t)0x0002)            /*!<Update disable        */
#define  TIM_CR1_URS_MORT                         ((uint16_t)0x0004)            /*!<Update request source */
#define  TIM_CR1_OPM_MORT                         ((uint16_t)0x0008)            /*!<One pulse mode        */
#define  TIM_CR1_DIR_MORT                         ((uint16_t)0x0010)            /*!<Direction             */

#define  TIM_CR1_CMS_MORT                         ((uint16_t)0x0060)            /*!<CMS[1:0] bits (Center-aligned mode selection) */
#define  TIM_CR1_CMS_0_MORT                       ((uint16_t)0x0020)            /*!<Bit 0 */
#define  TIM_CR1_CMS_1_MORT                       ((uint16_t)0x0040)            /*!<Bit 1 */

#define  TIM_CR1_ARPE_MORT                        ((uint16_t)0x0080)            /*!<Auto-reload preload enable     */

#define  TIM_CR1_CKD_MORT                         ((uint16_t)0x0300)            /*!<CKD[1:0] bits (clock division) */
#define  TIM_CR1_CKD_0_MORT                       ((uint16_t)0x0100)            /*!<Bit 0 */
#define  TIM_CR1_CKD_1_MORT                       ((uint16_t)0x0200)            /*!<Bit 1 */

/*******************  Bit definition for TIM_CR2 register  ********************/
#define  TIM_CR2_CCPC_MORT                        ((uint16_t)0x0001)            /*!<Capture/Compare Preloaded Control        */
#define  TIM_CR2_CCUS_MORT                        ((uint16_t)0x0004)            /*!<Capture/Compare Control Update Selection */
#define  TIM_CR2_CCDS_MORT                        ((uint16_t)0x0008)            /*!<Capture/Compare DMA Selection            */

#define  TIM_CR2_MMS_MORT                         ((uint16_t)0x0070)            /*!<MMS[2:0] bits (Master Mode Selection) */
#define  TIM_CR2_MMS_0_MORT                       ((uint16_t)0x0010)            /*!<Bit 0 */
#define  TIM_CR2_MMS_1_MORT                       ((uint16_t)0x0020)            /*!<Bit 1 */
#define  TIM_CR2_MMS_2_MORT                       ((uint16_t)0x0040)            /*!<Bit 2 */

#define  TIM_CR2_TI1S_MORT                        ((uint16_t)0x0080)            /*!<TI1 Selection */
#define  TIM_CR2_OIS1_MORT                        ((uint16_t)0x0100)            /*!<Output Idle state 1 (OC1 output)  */
#define  TIM_CR2_OIS1N_MORT                       ((uint16_t)0x0200)            /*!<Output Idle state 1 (OC1N output) */
#define  TIM_CR2_OIS2_MORT                        ((uint16_t)0x0400)            /*!<Output Idle state 2 (OC2 output)  */
#define  TIM_CR2_OIS2N_MORT                       ((uint16_t)0x0800)            /*!<Output Idle state 2 (OC2N output) */
#define  TIM_CR2_OIS3_MORT                        ((uint16_t)0x1000)            /*!<Output Idle state 3 (OC3 output)  */
#define  TIM_CR2_OIS3N_MORT                       ((uint16_t)0x2000)            /*!<Output Idle state 3 (OC3N output) */
#define  TIM_CR2_OIS4_MORT                        ((uint16_t)0x4000)            /*!<Output Idle state 4 (OC4 output)  */

/*******************  Bit definition for TIM_SMCR register  *******************/
#define  TIM_SMCR_SMS_MORT                        ((uint16_t)0x0007)            /*!<SMS[2:0] bits (Slave mode selection)    */
#define  TIM_SMCR_SMS_0_MORT                      ((uint16_t)0x0001)            /*!<Bit 0 */
#define  TIM_SMCR_SMS_1_MORT                      ((uint16_t)0x0002)            /*!<Bit 1 */
#define  TIM_SMCR_SMS_2_MORT                      ((uint16_t)0x0004)            /*!<Bit 2 */

#define  TIM_SMCR_TS_MORT                         ((uint16_t)0x0070)            /*!<TS[2:0] bits (Trigger selection)        */
#define  TIM_SMCR_TS_0_MORT                       ((uint16_t)0x0010)            /*!<Bit 0 */
#define  TIM_SMCR_TS_1_MORT                       ((uint16_t)0x0020)            /*!<Bit 1 */
#define  TIM_SMCR_TS_2_MORT                       ((uint16_t)0x0040)            /*!<Bit 2 */

#define  TIM_SMCR_MSM_MORT                        ((uint16_t)0x0080)            /*!<Master/slave mode                       */

#define  TIM_SMCR_ETF_MORT                        ((uint16_t)0x0F00)            /*!<ETF[3:0] bits (External trigger filter) */
#define  TIM_SMCR_ETF_0_MORT                      ((uint16_t)0x0100)            /*!<Bit 0 */
#define  TIM_SMCR_ETF_1_MORT                      ((uint16_t)0x0200)            /*!<Bit 1 */
#define  TIM_SMCR_ETF_2_MORT                      ((uint16_t)0x0400)            /*!<Bit 2 */
#define  TIM_SMCR_ETF_3_MORT                      ((uint16_t)0x0800)            /*!<Bit 3 */

#define  TIM_SMCR_ETPS_MORT                       ((uint16_t)0x3000)            /*!<ETPS[1:0] bits (External trigger prescaler) */
#define  TIM_SMCR_ETPS_0_MORT                     ((uint16_t)0x1000)            /*!<Bit 0 */
#define  TIM_SMCR_ETPS_1_MORT                     ((uint16_t)0x2000)            /*!<Bit 1 */

#define  TIM_SMCR_ECE_MORT                        ((uint16_t)0x4000)            /*!<External clock enable     */
#define  TIM_SMCR_ETP_MORT                        ((uint16_t)0x8000)            /*!<External trigger polarity */

/*******************  Bit definition for TIM_DIER register  *******************/
#define  TIM_DIER_UIE_MORT                        ((uint16_t)0x0001)            /*!<Update interrupt enable */
#define  TIM_DIER_CC1IE_MORT                      ((uint16_t)0x0002)            /*!<Capture/Compare 1 interrupt enable   */
#define  TIM_DIER_CC2IE_MORT                      ((uint16_t)0x0004)            /*!<Capture/Compare 2 interrupt enable   */
#define  TIM_DIER_CC3IE_MORT                      ((uint16_t)0x0008)            /*!<Capture/Compare 3 interrupt enable   */
#define  TIM_DIER_CC4IE_MORT                      ((uint16_t)0x0010)            /*!<Capture/Compare 4 interrupt enable   */
#define  TIM_DIER_COMIE_MORT                      ((uint16_t)0x0020)            /*!<COM interrupt enable                 */
#define  TIM_DIER_TIE_MORT                        ((uint16_t)0x0040)            /*!<Trigger interrupt enable             */
#define  TIM_DIER_BIE_MORT                        ((uint16_t)0x0080)            /*!<Break interrupt enable               */
#define  TIM_DIER_UDE_MORT                        ((uint16_t)0x0100)            /*!<Update DMA request enable            */
#define  TIM_DIER_CC1DE_MORT                      ((uint16_t)0x0200)            /*!<Capture/Compare 1 DMA request enable */
#define  TIM_DIER_CC2DE_MORT                      ((uint16_t)0x0400)            /*!<Capture/Compare 2 DMA request enable */
#define  TIM_DIER_CC3DE_MORT                      ((uint16_t)0x0800)            /*!<Capture/Compare 3 DMA request enable */
#define  TIM_DIER_CC4DE_MORT                      ((uint16_t)0x1000)            /*!<Capture/Compare 4 DMA request enable */
#define  TIM_DIER_COMDE_MORT                      ((uint16_t)0x2000)            /*!<COM DMA request enable               */
#define  TIM_DIER_TDE_MORT                        ((uint16_t)0x4000)            /*!<Trigger DMA request enable           */

/********************  Bit definition for TIM_SR register  ********************/
#define  TIM_SR_UIF_MORT                          ((uint16_t)0x0001)            /*!<Update interrupt Flag              */
#define  TIM_SR_CC1IF_MORT                        ((uint16_t)0x0002)            /*!<Capture/Compare 1 interrupt Flag   */
#define  TIM_SR_CC2IF_MORT                        ((uint16_t)0x0004)            /*!<Capture/Compare 2 interrupt Flag   */
#define  TIM_SR_CC3IF_MORT                        ((uint16_t)0x0008)            /*!<Capture/Compare 3 interrupt Flag   */
#define  TIM_SR_CC4IF_MORT                        ((uint16_t)0x0010)            /*!<Capture/Compare 4 interrupt Flag   */
#define  TIM_SR_COMIF_MORT                        ((uint16_t)0x0020)            /*!<COM interrupt Flag                 */
#define  TIM_SR_TIF_MORT                          ((uint16_t)0x0040)            /*!<Trigger interrupt Flag             */
#define  TIM_SR_BIF_MORT                          ((uint16_t)0x0080)            /*!<Break interrupt Flag               */
#define  TIM_SR_CC1OF_MORT                        ((uint16_t)0x0200)            /*!<Capture/Compare 1 Overcapture Flag */
#define  TIM_SR_CC2OF_MORT                        ((uint16_t)0x0400)            /*!<Capture/Compare 2 Overcapture Flag */
#define  TIM_SR_CC3OF_MORT                        ((uint16_t)0x0800)            /*!<Capture/Compare 3 Overcapture Flag */
#define  TIM_SR_CC4OF_MORT                        ((uint16_t)0x1000)            /*!<Capture/Compare 4 Overcapture Flag */

/*******************  Bit definition for TIM_EGR register  ********************/
#define  TIM_EGR_UG_MORT                          ((uint8_t)0x01)               /*!<Update Generation                         */
#define  TIM_EGR_CC1G_MORT                        ((uint8_t)0x02)               /*!<Capture/Compare 1 Generation              */
#define  TIM_EGR_CC2G_MORT                        ((uint8_t)0x04)               /*!<Capture/Compare 2 Generation              */
#define  TIM_EGR_CC3G_MORT                        ((uint8_t)0x08)               /*!<Capture/Compare 3 Generation              */
#define  TIM_EGR_CC4G_MORT                        ((uint8_t)0x10)               /*!<Capture/Compare 4 Generation              */
#define  TIM_EGR_COMG_MORT                        ((uint8_t)0x20)               /*!<Capture/Compare Control Update Generation */
#define  TIM_EGR_TG_MORT                          ((uint8_t)0x40)               /*!<Trigger Generation                        */
#define  TIM_EGR_BG_MORT                          ((uint8_t)0x80)               /*!<Break Generation                          */

/******************  Bit definition for TIM_CCMR1 register  *******************/
#define  TIM_CCMR1_CC1S_MORT                      ((uint16_t)0x0003)            /*!<CC1S[1:0] bits (Capture/Compare 1 Selection) */
#define  TIM_CCMR1_CC1S_0_MORT                    ((uint16_t)0x0001)            /*!<Bit 0 */
#define  TIM_CCMR1_CC1S_1_MORT                    ((uint16_t)0x0002)            /*!<Bit 1 */

#define  TIM_CCMR1_OC1FE_MORT                     ((uint16_t)0x0004)            /*!<Output Compare 1 Fast enable                 */
#define  TIM_CCMR1_OC1PE_MORT                     ((uint16_t)0x0008)            /*!<Output Compare 1 Preload enable              */

#define  TIM_CCMR1_OC1M_MORT                      ((uint16_t)0x0070)            /*!<OC1M[2:0] bits (Output Compare 1 Mode)       */
#define  TIM_CCMR1_OC1M_0_MORT                    ((uint16_t)0x0010)            /*!<Bit 0 */
#define  TIM_CCMR1_OC1M_1_MORT                    ((uint16_t)0x0020)            /*!<Bit 1 */
#define  TIM_CCMR1_OC1M_2_MORT                    ((uint16_t)0x0040)            /*!<Bit 2 */

#define  TIM_CCMR1_OC1CE_MORT                     ((uint16_t)0x0080)            /*!<Output Compare 1Clear Enable                 */

#define  TIM_CCMR1_CC2S_MORT                      ((uint16_t)0x0300)            /*!<CC2S[1:0] bits (Capture/Compare 2 Selection) */
#define  TIM_CCMR1_CC2S_0_MORT                    ((uint16_t)0x0100)            /*!<Bit 0 */
#define  TIM_CCMR1_CC2S_1_MORT                    ((uint16_t)0x0200)            /*!<Bit 1 */

#define  TIM_CCMR1_OC2FE_MORT                     ((uint16_t)0x0400)            /*!<Output Compare 2 Fast enable                 */
#define  TIM_CCMR1_OC2PE_MORT                     ((uint16_t)0x0800)            /*!<Output Compare 2 Preload enable              */

#define  TIM_CCMR1_OC2M_MORT                      ((uint16_t)0x7000)            /*!<OC2M[2:0] bits (Output Compare 2 Mode)       */
#define  TIM_CCMR1_OC2M_0_MORT                    ((uint16_t)0x1000)            /*!<Bit 0 */
#define  TIM_CCMR1_OC2M_1_MORT                    ((uint16_t)0x2000)            /*!<Bit 1 */
#define  TIM_CCMR1_OC2M_2_MORT                    ((uint16_t)0x4000)            /*!<Bit 2 */

#define  TIM_CCMR1_OC2CE_MORT                     ((uint16_t)0x8000)            /*!<Output Compare 2 Clear Enable */

/*----------------------------------------------------------------------------*/

#define  TIM_CCMR1_IC1PSC_MORT                    ((uint16_t)0x000C)            /*!<IC1PSC[1:0] bits (Input Capture 1 Prescaler) */
#define  TIM_CCMR1_IC1PSC_0_MORT                  ((uint16_t)0x0004)            /*!<Bit 0 */
#define  TIM_CCMR1_IC1PSC_1_MORT                  ((uint16_t)0x0008)            /*!<Bit 1 */

#define  TIM_CCMR1_IC1F_MORT                      ((uint16_t)0x00F0)            /*!<IC1F[3:0] bits (Input Capture 1 Filter)      */
#define  TIM_CCMR1_IC1F_0_MORT                    ((uint16_t)0x0010)            /*!<Bit 0 */
#define  TIM_CCMR1_IC1F_1_MORT                    ((uint16_t)0x0020)            /*!<Bit 1 */
#define  TIM_CCMR1_IC1F_2_MORT                    ((uint16_t)0x0040)            /*!<Bit 2 */
#define  TIM_CCMR1_IC1F_3_MORT                    ((uint16_t)0x0080)            /*!<Bit 3 */

#define  TIM_CCMR1_IC2PSC_MORT                    ((uint16_t)0x0C00)            /*!<IC2PSC[1:0] bits (Input Capture 2 Prescaler)  */
#define  TIM_CCMR1_IC2PSC_0_MORT                  ((uint16_t)0x0400)            /*!<Bit 0 */
#define  TIM_CCMR1_IC2PSC_1_MORT                  ((uint16_t)0x0800)            /*!<Bit 1 */

#define  TIM_CCMR1_IC2F_MORT                      ((uint16_t)0xF000)            /*!<IC2F[3:0] bits (Input Capture 2 Filter)       */
#define  TIM_CCMR1_IC2F_0_MORT                    ((uint16_t)0x1000)            /*!<Bit 0 */
#define  TIM_CCMR1_IC2F_1_MORT                    ((uint16_t)0x2000)            /*!<Bit 1 */
#define  TIM_CCMR1_IC2F_2_MORT                    ((uint16_t)0x4000)            /*!<Bit 2 */
#define  TIM_CCMR1_IC2F_3_MORT                    ((uint16_t)0x8000)            /*!<Bit 3 */

/******************  Bit definition for TIM_CCMR2 register  *******************/
#define  TIM_CCMR2_CC3S_MORT                      ((uint16_t)0x0003)            /*!<CC3S[1:0] bits (Capture/Compare 3 Selection)  */
#define  TIM_CCMR2_CC3S_0_MORT                    ((uint16_t)0x0001)            /*!<Bit 0 */
#define  TIM_CCMR2_CC3S_1_MORT                    ((uint16_t)0x0002)            /*!<Bit 1 */

#define  TIM_CCMR2_OC3FE_MORT                     ((uint16_t)0x0004)            /*!<Output Compare 3 Fast enable           */
#define  TIM_CCMR2_OC3PE_MORT                     ((uint16_t)0x0008)            /*!<Output Compare 3 Preload enable        */

#define  TIM_CCMR2_OC3M_MORT                      ((uint16_t)0x0070)            /*!<OC3M[2:0] bits (Output Compare 3 Mode) */
#define  TIM_CCMR2_OC3M_0_MORT                    ((uint16_t)0x0010)            /*!<Bit 0 */
#define  TIM_CCMR2_OC3M_1_MORT                    ((uint16_t)0x0020)            /*!<Bit 1 */
#define  TIM_CCMR2_OC3M_2_MORT                    ((uint16_t)0x0040)            /*!<Bit 2 */

#define  TIM_CCMR2_OC3CE_MORT                     ((uint16_t)0x0080)            /*!<Output Compare 3 Clear Enable */

#define  TIM_CCMR2_CC4S_MORT                      ((uint16_t)0x0300)            /*!<CC4S[1:0] bits (Capture/Compare 4 Selection) */
#define  TIM_CCMR2_CC4S_0_MORT                    ((uint16_t)0x0100)            /*!<Bit 0 */
#define  TIM_CCMR2_CC4S_1_MORT                    ((uint16_t)0x0200)            /*!<Bit 1 */

#define  TIM_CCMR2_OC4FE_MORT                     ((uint16_t)0x0400)            /*!<Output Compare 4 Fast enable    */
#define  TIM_CCMR2_OC4PE_MORT                     ((uint16_t)0x0800)            /*!<Output Compare 4 Preload enable */

#define  TIM_CCMR2_OC4M_MORT                      ((uint16_t)0x7000)            /*!<OC4M[2:0] bits (Output Compare 4 Mode) */
#define  TIM_CCMR2_OC4M_0_MORT                    ((uint16_t)0x1000)            /*!<Bit 0 */
#define  TIM_CCMR2_OC4M_1_MORT                    ((uint16_t)0x2000)            /*!<Bit 1 */
#define  TIM_CCMR2_OC4M_2_MORT                    ((uint16_t)0x4000)            /*!<Bit 2 */

#define  TIM_CCMR2_OC4CE_MORT                     ((uint16_t)0x8000)            /*!<Output Compare 4 Clear Enable */

/*----------------------------------------------------------------------------*/

#define  TIM_CCMR2_IC3PSC_MORT                    ((uint16_t)0x000C)            /*!<IC3PSC[1:0] bits (Input Capture 3 Prescaler) */
#define  TIM_CCMR2_IC3PSC_0_MORT                  ((uint16_t)0x0004)            /*!<Bit 0 */
#define  TIM_CCMR2_IC3PSC_1_MORT                  ((uint16_t)0x0008)            /*!<Bit 1 */

#define  TIM_CCMR2_IC3F_MORT                      ((uint16_t)0x00F0)            /*!<IC3F[3:0] bits (Input Capture 3 Filter) */
#define  TIM_CCMR2_IC3F_0_MORT                    ((uint16_t)0x0010)            /*!<Bit 0 */
#define  TIM_CCMR2_IC3F_1_MORT                    ((uint16_t)0x0020)            /*!<Bit 1 */
#define  TIM_CCMR2_IC3F_2_MORT                    ((uint16_t)0x0040)            /*!<Bit 2 */
#define  TIM_CCMR2_IC3F_3_MORT                    ((uint16_t)0x0080)            /*!<Bit 3 */

#define  TIM_CCMR2_IC4PSC_MORT                    ((uint16_t)0x0C00)            /*!<IC4PSC[1:0] bits (Input Capture 4 Prescaler) */
#define  TIM_CCMR2_IC4PSC_0_MORT                  ((uint16_t)0x0400)            /*!<Bit 0 */
#define  TIM_CCMR2_IC4PSC_1_MORT                  ((uint16_t)0x0800)            /*!<Bit 1 */

#define  TIM_CCMR2_IC4F_MORT                      ((uint16_t)0xF000)            /*!<IC4F[3:0] bits (Input Capture 4 Filter) */
#define  TIM_CCMR2_IC4F_0_MORT                    ((uint16_t)0x1000)            /*!<Bit 0 */
#define  TIM_CCMR2_IC4F_1_MORT                    ((uint16_t)0x2000)            /*!<Bit 1 */
#define  TIM_CCMR2_IC4F_2_MORT                    ((uint16_t)0x4000)            /*!<Bit 2 */
#define  TIM_CCMR2_IC4F_3_MORT                    ((uint16_t)0x8000)            /*!<Bit 3 */

/*******************  Bit definition for TIM_CCER register  *******************/
#define  TIM_CCER_CC1E_MORT                       ((uint16_t)0x0001)            /*!<Capture/Compare 1 output enable                 */
#define  TIM_CCER_CC1P_MORT                       ((uint16_t)0x0002)            /*!<Capture/Compare 1 output Polarity               */
#define  TIM_CCER_CC1NE_MORT                      ((uint16_t)0x0004)            /*!<Capture/Compare 1 Complementary output enable   */
#define  TIM_CCER_CC1NP_MORT                      ((uint16_t)0x0008)            /*!<Capture/Compare 1 Complementary output Polarity */
#define  TIM_CCER_CC2E_MORT                       ((uint16_t)0x0010)            /*!<Capture/Compare 2 output enable                 */
#define  TIM_CCER_CC2P_MORT                       ((uint16_t)0x0020)            /*!<Capture/Compare 2 output Polarity               */
#define  TIM_CCER_CC2NE_MORT                      ((uint16_t)0x0040)            /*!<Capture/Compare 2 Complementary output enable   */
#define  TIM_CCER_CC2NP_MORT                      ((uint16_t)0x0080)            /*!<Capture/Compare 2 Complementary output Polarity */
#define  TIM_CCER_CC3E_MORT                       ((uint16_t)0x0100)            /*!<Capture/Compare 3 output enable                 */
#define  TIM_CCER_CC3P_MORT                       ((uint16_t)0x0200)            /*!<Capture/Compare 3 output Polarity               */
#define  TIM_CCER_CC3NE_MORT                      ((uint16_t)0x0400)            /*!<Capture/Compare 3 Complementary output enable   */
#define  TIM_CCER_CC3NP_MORT                      ((uint16_t)0x0800)            /*!<Capture/Compare 3 Complementary output Polarity */
#define  TIM_CCER_CC4E_MORT                       ((uint16_t)0x1000)            /*!<Capture/Compare 4 output enable                 */
#define  TIM_CCER_CC4P_MORT                       ((uint16_t)0x2000)            /*!<Capture/Compare 4 output Polarity               */
#define  TIM_CCER_CC4NP_MORT                      ((uint16_t)0x8000)            /*!<Capture/Compare 4 Complementary output Polarity */

/*******************  Bit definition for TIM_CNT register  ********************/
#define  TIM_CNT_CNT_MORT                         ((uint16_t)0xFFFF)            /*!<Counter Value            */

/*******************  Bit definition for TIM_PSC register  ********************/
#define  TIM_PSC_PSC_MORT                         ((uint16_t)0xFFFF)            /*!<Prescaler Value          */

/*******************  Bit definition for TIM_ARR register  ********************/
#define  TIM_ARR_ARR_MORT                         ((uint16_t)0xFFFF)            /*!<actual auto-reload Value */

/*******************  Bit definition for TIM_RCR register  ********************/
#define  TIM_RCR_REP_MORT                         ((uint8_t)0xFF)               /*!<Repetition Counter Value */

/*******************  Bit definition for TIM_CCR1 register  *******************/
#define  TIM_CCR1_CCR1_MORT                       ((uint16_t)0xFFFF)            /*!<Capture/Compare 1 Value  */

/*******************  Bit definition for TIM_CCR2 register  *******************/
#define  TIM_CCR2_CCR2_MORT                       ((uint16_t)0xFFFF)            /*!<Capture/Compare 2 Value  */

/*******************  Bit definition for TIM_CCR3 register  *******************/
#define  TIM_CCR3_CCR3_MORT                       ((uint16_t)0xFFFF)            /*!<Capture/Compare 3 Value  */

/*******************  Bit definition for TIM_CCR4 register  *******************/
#define  TIM_CCR4_CCR4_MORT                       ((uint16_t)0xFFFF)            /*!<Capture/Compare 4 Value  */

/*******************  Bit definition for TIM_BDTR register  *******************/
#define  TIM_BDTR_DTG_MORT                        ((uint16_t)0x00FF)            /*!<DTG[0:7] bits (Dead-Time Generator set-up) */
#define  TIM_BDTR_DTG_0_MORT                      ((uint16_t)0x0001)            /*!<Bit 0 */
#define  TIM_BDTR_DTG_1_MORT                      ((uint16_t)0x0002)            /*!<Bit 1 */
#define  TIM_BDTR_DTG_2_MORT                      ((uint16_t)0x0004)            /*!<Bit 2 */
#define  TIM_BDTR_DTG_3_MORT                      ((uint16_t)0x0008)            /*!<Bit 3 */
#define  TIM_BDTR_DTG_4_MORT                      ((uint16_t)0x0010)            /*!<Bit 4 */
#define  TIM_BDTR_DTG_5_MORT                      ((uint16_t)0x0020)            /*!<Bit 5 */
#define  TIM_BDTR_DTG_6_MORT                      ((uint16_t)0x0040)            /*!<Bit 6 */
#define  TIM_BDTR_DTG_7_MORT                      ((uint16_t)0x0080)            /*!<Bit 7 */

#define  TIM_BDTR_LOCK_MORT                       ((uint16_t)0x0300)            /*!<LOCK[1:0] bits (Lock Configuration) */
#define  TIM_BDTR_LOCK_0_MORT                     ((uint16_t)0x0100)            /*!<Bit 0 */
#define  TIM_BDTR_LOCK_1_MORT                     ((uint16_t)0x0200)            /*!<Bit 1 */

#define  TIM_BDTR_OSSI_MORT                       ((uint16_t)0x0400)            /*!<Off-State Selection for Idle mode */
#define  TIM_BDTR_OSSR_MORT                       ((uint16_t)0x0800)            /*!<Off-State Selection for Run mode  */
#define  TIM_BDTR_BKE_MORT                        ((uint16_t)0x1000)            /*!<Break enable                      */
#define  TIM_BDTR_BKP_MORT                        ((uint16_t)0x2000)            /*!<Break Polarity                    */
#define  TIM_BDTR_AOE_MORT                        ((uint16_t)0x4000)            /*!<Automatic Output enable           */
#define  TIM_BDTR_MOE_MORT                        ((uint16_t)0x8000)            /*!<Main Output enable                */

/*******************  Bit definition for TIM_DCR register  ********************/
#define  TIM_DCR_DBA_MORT                         ((uint16_t)0x001F)            /*!<DBA[4:0] bits (DMA Base Address) */
#define  TIM_DCR_DBA_0_MORT                       ((uint16_t)0x0001)            /*!<Bit 0 */
#define  TIM_DCR_DBA_1_MORT                       ((uint16_t)0x0002)            /*!<Bit 1 */
#define  TIM_DCR_DBA_2_MORT                       ((uint16_t)0x0004)            /*!<Bit 2 */
#define  TIM_DCR_DBA_3_MORT                       ((uint16_t)0x0008)            /*!<Bit 3 */
#define  TIM_DCR_DBA_4_MORT                       ((uint16_t)0x0010)            /*!<Bit 4 */

#define  TIM_DCR_DBL_MORT                         ((uint16_t)0x1F00)            /*!<DBL[4:0] bits (DMA Burst Length) */
#define  TIM_DCR_DBL_0_MORT                       ((uint16_t)0x0100)            /*!<Bit 0 */
#define  TIM_DCR_DBL_1_MORT                       ((uint16_t)0x0200)            /*!<Bit 1 */
#define  TIM_DCR_DBL_2_MORT                       ((uint16_t)0x0400)            /*!<Bit 2 */
#define  TIM_DCR_DBL_3_MORT                       ((uint16_t)0x0800)            /*!<Bit 3 */
#define  TIM_DCR_DBL_4_MORT                       ((uint16_t)0x1000)            /*!<Bit 4 */

/*******************  Bit definition for TIM_DMAR register  *******************/
#define  TIM_DMAR_DMAB_MORT                       ((uint16_t)0xFFFF)            /*!<DMA register for burst accesses                    */

/*******************  Bit definition for TIM_OR register  *********************/
#define TIM_OR_TI4_RMP_MORT                       ((uint16_t)0x00C0)            /*!<TI4_RMP[1:0] bits (TIM5_MORT Input 4 remap)             */
#define TIM_OR_TI4_RMP_0_MORT                     ((uint16_t)0x0040)            /*!<Bit 0 */
#define TIM_OR_TI4_RMP_1_MORT                     ((uint16_t)0x0080)            /*!<Bit 1 */
#define TIM_OR_ITR1_RMP_MORT                      ((uint16_t)0x0C00)            /*!<ITR1_RMP[1:0] bits (TIM2_MORT Internal trigger 1 remap) */
#define TIM_OR_ITR1_RMP_0_MORT                    ((uint16_t)0x0400)            /*!<Bit 0 */
#define TIM_OR_ITR1_RMP_1_MORT                    ((uint16_t)0x0800)            /*!<Bit 1 */

#if defined(STM32F410xx) || defined(STM32F413_423xx)
/******************************************************************************/
/*                                                                            */
/*                         Low Power Timer (LPTIM)                            */
/*                                                                            */
/******************************************************************************/
/******************  Bit definition for LPTIM_ISR register  *******************/

/******************  Bit definition for LPTIM_ICR register  *******************/

/******************  Bit definition for LPTIM_IER register ********************/

/******************  Bit definition for LPTIM_CFGR register *******************/


/******************  Bit definition for LPTIM_CR register  ********************/

/******************  Bit definition for LPTIM_CMP register  *******************/

/******************  Bit definition for LPTIM_ARR register  *******************/

/******************  Bit definition for LPTIM_CNT register  *******************/

/******************  Bit definition for LPTIM_OR register  *******************/

#endif /* STM32F410xx || STM32F413_423xx */

/******************************************************************************/
/*                                                                            */
/*         Universal Synchronous Asynchronous Receiver Transmitter            */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for USART_SR register  *******************/

/*******************  Bit definition for USART_DR register  *******************/

/******************  Bit definition for USART_BRR register  *******************/

/******************  Bit definition for USART_CR1 register  *******************/

/******************  Bit definition for USART_CR2 register  *******************/

/******************  Bit definition for USART_CR3 register  *******************/

/******************  Bit definition for USART_GTPR register  ******************/

/******************************************************************************/
/*                                                                            */
/*                            Window WATCHDOG                                 */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for WWDG_CR register  ********************/

/*******************  Bit definition for WWDG_CFR register  *******************/

/*******************  Bit definition for WWDG_SR register  ********************/

/******************************************************************************/
/*                                                                            */
/*                                DBG                                         */
/*                                                                            */
/******************************************************************************/
/********************  Bit definition for DBGMCU_IDCODE register  *************/

/********************  Bit definition for DBGMCU_CR register  *****************/


/********************  Bit definition for DBGMCU_APB1_FZ register  ************/


/********************  Bit definition for DBGMCU_APB1_FZ register  ************/


/******************************************************************************/
/*                                                                            */
/*                Ethernet MAC Registers bits definitions                     */
/*                                                                            */
/******************************************************************************/
/* Bit definition for Ethernet MAC Control Register register */


/* Bit definition for Ethernet MAC Frame Filter Register */

/* Bit definition for Ethernet MAC Flow Control Register */


/* Bit definition for Ethernet MAC Status Register */


/* Bit definition for Ethernet MAC Interrupt Mask Register */


/* Bit definition for Ethernet MAC Address0 High Register */


/* Bit definition for Ethernet MAC Address0 Low Register */


/* Bit definition for Ethernet MAC Address1 High Register */

/* Bit definition for Ethernet MAC Address1 Low Register */


/* Bit definition for Ethernet MAC Address2 High Register */


/* Bit definition for Ethernet MAC Address2 Low Register */


/* Bit definition for Ethernet MAC Address3 High Register */


/* Bit definition for Ethernet MAC Address3 Low Register */


/******************************************************************************/
/*                Ethernet MMC Registers bits definition                      */
/******************************************************************************/

/* Bit definition for Ethernet MMC Contol Register */


/* Bit definition for Ethernet MMC Receive Interrupt Register */

/* Bit definition for Ethernet MMC Transmit Interrupt Register */

/* Bit definition for Ethernet MMC Receive Interrupt Mask Register */

/* Bit definition for Ethernet MMC Transmit Interrupt Mask Register */

/******************************************************************************/
/*               Ethernet PTP Registers bits definition                       */
/******************************************************************************/

/* Bit definition for Ethernet PTP Time Stamp Contol Register */



/******************************************************************************/
/*                 Ethernet DMA Registers bits definition                     */
/******************************************************************************/

/* Bit definition for Ethernet DMA Bus Mode Register */


/**
  *
  */

 /**
  * @}
  */ 

#ifdef USE_STDPERIPH_DRIVER
  #include "stm32f4xx_conf.h"
#endif /* USE_STDPERIPH_DRIVER */

/** @addtogroup Exported_macro
  * @{
  */

#define SET_BIT_MORT(REG, BIT)     ((REG) |= (BIT))

#define CLEAR_BIT_MORT(REG, BIT)   ((REG) &= ~(BIT))

#define READ_BIT_MORT(REG, BIT)    ((REG) & (BIT))

#define CLEAR_REG_MORT(REG)        ((REG) = (0x0))

#define WRITE_REG_MORT(REG, VAL)   ((REG) = (VAL))

#define READ_REG_MORT(REG)         ((REG))

#define MODIFY_REG_MORT(REG, CLEARMASK, SETMASK)  WRITE_REG_MORT((REG), (((READ_REG_MORT(REG)) & (~(CLEARMASK))) | (SETMASK)))

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __STM32F4xx_H */

/**
  * @}
  */

  /**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/