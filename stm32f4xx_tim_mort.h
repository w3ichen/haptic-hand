/**
  ******************************************************************************
  * @file    stm32f4xx_tim.h
  * @author  MCD Application Team
  * @version V1.8.0
  * @date    04-November-2016
  * @brief   This file contains all the functions prototypes for the TIM firmware 
  *          library.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F4xx_TIM_H_MORT_
#define __STM32F4xx_TIM_H_MORT_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_mort2.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup TIM
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  TIM Time Base Init structure definition  
  * @note   This structure is used with all TIMx except for TIM6_MORT and TIM7_MORT.  
  */

typedef struct
{
  uint16_t TIM_Prescaler;         /*!< Specifies the prescaler value used to divide the TIM clock.
                                       This parameter can be a number between 0x0000 and 0xFFFF */

  uint16_t TIM_CounterMode;       /*!< Specifies the counter mode.
                                       This parameter can be a value of @ref TIM_Counter_Mode */

  uint32_t TIM_Period;            /*!< Specifies the period value to be loaded into the active
                                       Auto-Reload Register at the next update event.
                                       This parameter must be a number between 0x0000 and 0xFFFF.  */ 

  uint16_t TIM_ClockDivision;     /*!< Specifies the clock division.
                                      This parameter can be a value of @ref TIM_Clock_Division_CKD */

  uint8_t TIM_RepetitionCounter;  /*!< Specifies the repetition counter value. Each time the RCR downcounter
                                       reaches zero, an update event is generated and counting restarts
                                       from the RCR value (N).
                                       This means in PWM mode that (N+1) corresponds to:
                                          - the number of PWM periods in edge-aligned mode
                                          - the number of half PWM period in center-aligned mode
                                       This parameter must be a number between 0x00 and 0xFF. 
                                       @note This parameter is valid only for TIM1_MORT and TIM8_MORT. */
} TIM_TimeBaseInitTypeDef_mort; 

/** 
  * @brief  TIM Output Compare Init structure definition  
  */

typedef struct
{
  uint16_t TIM_OCMode;        /*!< Specifies the TIM mode.
                                   This parameter can be a value of @ref TIM_Output_Compare_and_PWM_modes */

  uint16_t TIM_OutputState;   /*!< Specifies the TIM Output Compare state.
                                   This parameter can be a value of @ref TIM_Output_Compare_State */

  uint16_t TIM_OutputNState;  /*!< Specifies the TIM complementary Output Compare state.
                                   This parameter can be a value of @ref TIM_Output_Compare_N_State
                                   @note This parameter is valid only for TIM1_MORT and TIM8_MORT. */

  uint32_t TIM_Pulse;         /*!< Specifies the pulse value to be loaded into the Capture Compare Register. 
                                   This parameter can be a number between 0x0000 and 0xFFFF */

  uint16_t TIM_OCPolarity;    /*!< Specifies the output polarity.
                                   This parameter can be a value of @ref TIM_Output_Compare_Polarity */

  uint16_t TIM_OCNPolarity;   /*!< Specifies the complementary output polarity.
                                   This parameter can be a value of @ref TIM_Output_Compare_N_Polarity
                                   @note This parameter is valid only for TIM1_MORT and TIM8_MORT. */

  uint16_t TIM_OCIdleState;   /*!< Specifies the TIM Output Compare pin state during Idle state.
                                   This parameter can be a value of @ref TIM_Output_Compare_Idle_State
                                   @note This parameter is valid only for TIM1_MORT and TIM8_MORT. */

  uint16_t TIM_OCNIdleState;  /*!< Specifies the TIM Output Compare pin state during Idle state.
                                   This parameter can be a value of @ref TIM_Output_Compare_N_Idle_State
                                   @note This parameter is valid only for TIM1_MORT and TIM8_MORT. */
} TIM_OCInitTypeDef_mort;

/** 
  * @brief  TIM Input Capture Init structure definition  
  */

typedef struct
{

  uint16_t TIM_Channel;      /*!< Specifies the TIM channel.
                                  This parameter can be a value of @ref TIM_Channel */

  uint16_t TIM_ICPolarity;   /*!< Specifies the active edge of the input signal.
                                  This parameter can be a value of @ref TIM_Input_Capture_Polarity */

  uint16_t TIM_ICSelection;  /*!< Specifies the input.
                                  This parameter can be a value of @ref TIM_Input_Capture_Selection */

  uint16_t TIM_ICPrescaler;  /*!< Specifies the Input Capture Prescaler.
                                  This parameter can be a value of @ref TIM_Input_Capture_Prescaler */

  uint16_t TIM_ICFilter;     /*!< Specifies the input capture filter.
                                  This parameter can be a number between 0x0 and 0xF */
} TIM_ICInitTypeDef_mort;

/** 
  * @brief  BDTR structure definition 
  * @note   This structure is used only with TIM1_MORT and TIM8_MORT.    
  */

typedef struct
{

  uint16_t TIM_OSSRState;        /*!< Specifies the Off-State selection used in Run mode.
                                      This parameter can be a value of @ref TIM_OSSR_Off_State_Selection_for_Run_mode_state */

  uint16_t TIM_OSSIState;        /*!< Specifies the Off-State used in Idle state.
                                      This parameter can be a value of @ref TIM_OSSI_Off_State_Selection_for_Idle_mode_state */

  uint16_t TIM_LOCKLevel;        /*!< Specifies the LOCK level parameters.
                                      This parameter can be a value of @ref TIM_Lock_level */ 

  uint16_t TIM_DeadTime;         /*!< Specifies the delay time between the switching-off and the
                                      switching-on of the outputs.
                                      This parameter can be a number between 0x00 and 0xFF  */

  uint16_t TIM_Break;            /*!< Specifies whether the TIM Break input is enabled or not. 
                                      This parameter can be a value of @ref TIM_Break_Input_enable_disable */

  uint16_t TIM_BreakPolarity;    /*!< Specifies the TIM Break Input pin polarity.
                                      This parameter can be a value of @ref TIM_Break_Polarity */

  uint16_t TIM_AutomaticOutput;  /*!< Specifies whether the TIM Automatic Output feature is enabled or not. 
                                      This parameter can be a value of @ref TIM_AOE_Bit_Set_Reset */
} TIM_BDTRInitTypeDef_mort;

/* Exported constants --------------------------------------------------------*/

/** @defgroup TIM_Exported_constants 
  * @{
  */

#define IS_TIM_ALL_PERIPH_MORT(PERIPH) (((PERIPH) == TIM1_MORT) || \
                                   ((PERIPH) == TIM2_MORT) || \
                                   ((PERIPH) == TIM3_MORT) || \
                                   ((PERIPH) == TIM4_MORT) || \
                                   ((PERIPH) == TIM5_MORT) || \
                                   ((PERIPH) == TIM6_MORT) || \
                                   ((PERIPH) == TIM7_MORT) || \
                                   ((PERIPH) == TIM8_MORT) || \
                                   ((PERIPH) == TIM9_MORT) || \
                                   ((PERIPH) == TIM10_MORT) || \
                                   ((PERIPH) == TIM11_MORT) || \
                                   ((PERIPH) == TIM12_MORT) || \
                                   (((PERIPH) == TIM13_MORT) || \
                                   ((PERIPH) == TIM14_MORT)))
/* LIST1: TIM1_MORT, TIM2_MORT, TIM3_MORT, TIM4_MORT, TIM5_MORT, TIM8_MORT, TIM9_MORT, TIM10_MORT, TIM11_MORT, TIM12_MORT, TIM13_MORT and TIM14_MORT */                                         
#define IS_TIM_LIST1_PERIPH_MORT(PERIPH) (((PERIPH) == TIM1_MORT) || \
                                     ((PERIPH) == TIM2_MORT) || \
                                     ((PERIPH) == TIM3_MORT) || \
                                     ((PERIPH) == TIM4_MORT) || \
                                     ((PERIPH) == TIM5_MORT) || \
                                     ((PERIPH) == TIM8_MORT) || \
                                     ((PERIPH) == TIM9_MORT) || \
                                     ((PERIPH) == TIM10_MORT) || \
                                     ((PERIPH) == TIM11_MORT) || \
                                     ((PERIPH) == TIM12_MORT) || \
                                     ((PERIPH) == TIM13_MORT) || \
                                     ((PERIPH) == TIM14_MORT))
                                     
/* LIST2: TIM1_MORT, TIM2_MORT, TIM3_MORT, TIM4_MORT, TIM5_MORT, TIM8_MORT, TIM9_MORT and TIM12_MORT */
#define IS_TIM_LIST2_PERIPH_MORT(PERIPH) (((PERIPH) == TIM1_MORT) || \
                                     ((PERIPH) == TIM2_MORT) || \
                                     ((PERIPH) == TIM3_MORT) || \
                                     ((PERIPH) == TIM4_MORT) || \
                                     ((PERIPH) == TIM5_MORT) || \
                                     ((PERIPH) == TIM8_MORT) || \
                                     ((PERIPH) == TIM9_MORT) || \
                                     ((PERIPH) == TIM12_MORT))
/* LIST3: TIM1_MORT, TIM2_MORT, TIM3_MORT, TIM4_MORT, TIM5_MORT and TIM8_MORT */
#define IS_TIM_LIST3_PERIPH_MORT(PERIPH) (((PERIPH) == TIM1_MORT) || \
                                     ((PERIPH) == TIM2_MORT) || \
                                     ((PERIPH) == TIM3_MORT) || \
                                     ((PERIPH) == TIM4_MORT) || \
                                     ((PERIPH) == TIM5_MORT) || \
                                     ((PERIPH) == TIM8_MORT))
/* LIST4: TIM1_MORT and TIM8_MORT */
#define IS_TIM_LIST4_PERIPH_MORT(PERIPH) (((PERIPH) == TIM1_MORT) || \
                                     ((PERIPH) == TIM8_MORT))
/* LIST5: TIM1_MORT, TIM2_MORT, TIM3_MORT, TIM4_MORT, TIM5_MORT, TIM6_MORT, TIM7_MORT and TIM8_MORT */
#define IS_TIM_LIST5_PERIPH_MORT(PERIPH) (((PERIPH) == TIM1_MORT) || \
                                     ((PERIPH) == TIM2_MORT) || \
                                     ((PERIPH) == TIM3_MORT) || \
                                     ((PERIPH) == TIM4_MORT) || \
                                     ((PERIPH) == TIM5_MORT) || \
                                     ((PERIPH) == TIM6_MORT) || \
                                     ((PERIPH) == TIM7_MORT) || \
                                     ((PERIPH) == TIM8_MORT))
/* LIST6: TIM2_MORT, TIM5_MORT and TIM11_MORT */                               
#define IS_TIM_LIST6_PERIPH_MORT(TIMx)(((TIMx) == TIM2_MORT) || \
                                 ((TIMx) == TIM5_MORT) || \
                                 ((TIMx) == TIM11_MORT))

/** @defgroup TIM_Output_Compare_and_PWM_modes 
  * @{
  */

#define TIM_OCMode_Timing_MORT                  ((uint16_t)0x0000)
#define TIM_OCMode_Active_MORT                  ((uint16_t)0x0010)
#define TIM_OCMode_Inactive_MORT                ((uint16_t)0x0020)
#define TIM_OCMode_Toggle_MORT                  ((uint16_t)0x0030)
#define TIM_OCMode_PWM1_MORT                    ((uint16_t)0x0060)
#define TIM_OCMode_PWM2_MORT                    ((uint16_t)0x0070)
#define IS_TIM_OC_MODE_MORT(MODE) (((MODE) == TIM_OCMode_Timing_MORT) || \
                              ((MODE) == TIM_OCMode_Active_MORT) || \
                              ((MODE) == TIM_OCMode_Inactive_MORT) || \
                              ((MODE) == TIM_OCMode_Toggle_MORT)|| \
                              ((MODE) == TIM_OCMode_PWM1_MORT) || \
                              ((MODE) == TIM_OCMode_PWM2_MORT))
#define IS_TIM_OCM_MORT(MODE) (((MODE) == TIM_OCMode_Timing_MORT) || \
                          ((MODE) == TIM_OCMode_Active_MORT) || \
                          ((MODE) == TIM_OCMode_Inactive_MORT) || \
                          ((MODE) == TIM_OCMode_Toggle_MORT)|| \
                          ((MODE) == TIM_OCMode_PWM1_MORT) || \
                          ((MODE) == TIM_OCMode_PWM2_MORT) ||	\
                          ((MODE) == TIM_ForcedAction_Active_MORT) || \
                          ((MODE) == TIM_ForcedAction_InActive_MORT))
/**
  * @}
  */

/** @defgroup TIM_One_Pulse_Mode 
  * @{
  */

#define TIM_OPMode_Single_MORT                  ((uint16_t)0x0008)
#define TIM_OPMode_Repetitive_MORT              ((uint16_t)0x0000)
#define IS_TIM_OPM_MODE_MORT(MODE) (((MODE) == TIM_OPMode_Single_MORT) || \
                               ((MODE) == TIM_OPMode_Repetitive_MORT))
/**
  * @}
  */ 

/** @defgroup TIM_Channel 
  * @{
  */

#define TIM_Channel_1_MORT                      ((uint16_t)0x0000)
#define TIM_Channel_2_MORT                      ((uint16_t)0x0004)
#define TIM_Channel_3_MORT                      ((uint16_t)0x0008)
#define TIM_Channel_4_MORT                      ((uint16_t)0x000C)
                                 
#define IS_TIM_CHANNEL_MORT(CHANNEL) (((CHANNEL) == TIM_Channel_1_MORT) || \
                                 ((CHANNEL) == TIM_Channel_2_MORT) || \
                                 ((CHANNEL) == TIM_Channel_3_MORT) || \
                                 ((CHANNEL) == TIM_Channel_4_MORT))
                                 
#define IS_TIM_PWMI_CHANNEL_MORT(CHANNEL) (((CHANNEL) == TIM_Channel_1_MORT) || \
                                      ((CHANNEL) == TIM_Channel_2_MORT))
#define IS_TIM_COMPLEMENTARY_CHANNEL_MORT(CHANNEL) (((CHANNEL) == TIM_Channel_1_MORT) || \
                                               ((CHANNEL) == TIM_Channel_2_MORT) || \
                                               ((CHANNEL) == TIM_Channel_3_MORT))
/**
  * @}
  */ 

/** @defgroup TIM_Clock_Division_CKD 
  * @{
  */

#define TIM_CKD_DIV1_MORT                       ((uint16_t)0x0000)
#define TIM_CKD_DIV2_MORT                       ((uint16_t)0x0100)
#define TIM_CKD_DIV4_MORT                       ((uint16_t)0x0200)
#define IS_TIM_CKD_DIV_MORT(DIV) (((DIV) == TIM_CKD_DIV1_MORT) || \
                             ((DIV) == TIM_CKD_DIV2_MORT) || \
                             ((DIV) == TIM_CKD_DIV4_MORT))
/**
  * @}
  */

/** @defgroup TIM_Counter_Mode 
  * @{
  */

#define TIM_CounterMode_Up_MORT                 ((uint16_t)0x0000)
#define TIM_CounterMode_Down_MORT               ((uint16_t)0x0010)
#define TIM_CounterMode_CenterAligned1_MORT     ((uint16_t)0x0020)
#define TIM_CounterMode_CenterAligned2_MORT     ((uint16_t)0x0040)
#define TIM_CounterMode_CenterAligned3_MORT     ((uint16_t)0x0060)
#define IS_TIM_COUNTER_MODE_MORT(MODE) (((MODE) == TIM_CounterMode_Up_MORT) ||  \
                                   ((MODE) == TIM_CounterMode_Down_MORT) || \
                                   ((MODE) == TIM_CounterMode_CenterAligned1_MORT) || \
                                   ((MODE) == TIM_CounterMode_CenterAligned2_MORT) || \
                                   ((MODE) == TIM_CounterMode_CenterAligned3_MORT))
/**
  * @}
  */ 

/** @defgroup TIM_Output_Compare_Polarity 
  * @{
  */

#define TIM_OCPolarity_High_MORT                ((uint16_t)0x0000)
#define TIM_OCPolarity_Low_MORT                 ((uint16_t)0x0002)
#define IS_TIM_OC_POLARITY_MORT(POLARITY) (((POLARITY) == TIM_OCPolarity_High_MORT) || \
                                      ((POLARITY) == TIM_OCPolarity_Low_MORT))
/**
  * @}
  */

/** @defgroup TIM_Output_Compare_N_Polarity 
  * @{
  */
  
#define TIM_OCNPolarity_High_MORT               ((uint16_t)0x0000)
#define TIM_OCNPolarity_Low_MORT                ((uint16_t)0x0008)
#define IS_TIM_OCN_POLARITY_MORT(POLARITY) (((POLARITY) == TIM_OCNPolarity_High_MORT) || \
                                       ((POLARITY) == TIM_OCNPolarity_Low_MORT))
/**
  * @}
  */

/** @defgroup TIM_Output_Compare_State 
  * @{
  */

#define TIM_OutputState_Disable_MORT            ((uint16_t)0x0000)
#define TIM_OutputState_Enable_MORT             ((uint16_t)0x0001)
#define IS_TIM_OUTPUT_STATE_MORT(STATE) (((STATE) == TIM_OutputState_Disable_MORT) || \
                                    ((STATE) == TIM_OutputState_Enable_MORT))
/**
  * @}
  */ 

/** @defgroup TIM_Output_Compare_N_State
  * @{
  */

#define TIM_OutputNState_Disable_MORT           ((uint16_t)0x0000)
#define TIM_OutputNState_Enable_MORT            ((uint16_t)0x0004)
#define IS_TIM_OUTPUTN_STATE_MORT(STATE) (((STATE) == TIM_OutputNState_Disable_MORT) || \
                                     ((STATE) == TIM_OutputNState_Enable_MORT))
/**
  * @}
  */ 

/** @defgroup TIM_Capture_Compare_State
  * @{
  */

#define TIM_CCx_Enable_MORT                      ((uint16_t)0x0001)
#define TIM_CCx_Disable_MORT                     ((uint16_t)0x0000)
#define IS_TIM_CCX_MORT(CCX) (((CCX) == TIM_CCx_Enable_MORT) || \
                         ((CCX) == TIM_CCx_Disable_MORT))
/**
  * @}
  */ 

/** @defgroup TIM_Capture_Compare_N_State
  * @{
  */

#define TIM_CCxN_Enable_MORT                     ((uint16_t)0x0004)
#define TIM_CCxN_Disable_MORT                    ((uint16_t)0x0000)
#define IS_TIM_CCXN_MORT(CCXN) (((CCXN) == TIM_CCxN_Enable_MORT) || \
                           ((CCXN) == TIM_CCxN_Disable_MORT))
/**
  * @}
  */ 

/** @defgroup TIM_Break_Input_enable_disable 
  * @{
  */

#define TIM_Break_Enable_MORT                   ((uint16_t)0x1000)
#define TIM_Break_Disable_MORT                  ((uint16_t)0x0000)
#define IS_TIM_BREAK_STATE_MORT(STATE) (((STATE) == TIM_Break_Enable_MORT) || \
                                   ((STATE) == TIM_Break_Disable_MORT))
/**
  * @}
  */ 

/** @defgroup TIM_Break_Polarity 
  * @{
  */

#define TIM_BreakPolarity_Low_MORT              ((uint16_t)0x0000)
#define TIM_BreakPolarity_High_MORT             ((uint16_t)0x2000)
#define IS_TIM_BREAK_POLARITY_MORT(POLARITY) (((POLARITY) == TIM_BreakPolarity_Low_MORT) || \
                                         ((POLARITY) == TIM_BreakPolarity_High_MORT))
/**
  * @}
  */ 

/** @defgroup TIM_AOE_Bit_Set_Reset 
  * @{
  */

#define TIM_AutomaticOutput_Enable_MORT         ((uint16_t)0x4000)
#define TIM_AutomaticOutput_Disable_MORT        ((uint16_t)0x0000)
#define IS_TIM_AUTOMATIC_OUTPUT_STATE_MORT(STATE) (((STATE) == TIM_AutomaticOutput_Enable_MORT) || \
                                              ((STATE) == TIM_AutomaticOutput_Disable_MORT))
/**
  * @}
  */ 

/** @defgroup TIM_Lock_level
  * @{
  */

#define TIM_LOCKLevel_OFF_MORT                  ((uint16_t)0x0000)
#define TIM_LOCKLevel_1_MORT                    ((uint16_t)0x0100)
#define TIM_LOCKLevel_2_MORT                    ((uint16_t)0x0200)
#define TIM_LOCKLevel_3_MORT                    ((uint16_t)0x0300)
#define IS_TIM_LOCK_LEVEL_MORT(LEVEL) (((LEVEL) == TIM_LOCKLevel_OFF_MORT) || \
                                  ((LEVEL) == TIM_LOCKLevel_1_MORT) || \
                                  ((LEVEL) == TIM_LOCKLevel_2_MORT) || \
                                  ((LEVEL) == TIM_LOCKLevel_3_MORT))
/**
  * @}
  */ 

/** @defgroup TIM_OSSI_Off_State_Selection_for_Idle_mode_state 
  * @{
  */

#define TIM_OSSIState_Enable_MORT               ((uint16_t)0x0400)
#define TIM_OSSIState_Disable_MORT              ((uint16_t)0x0000)
#define IS_TIM_OSSI_STATE_MORT(STATE) (((STATE) == TIM_OSSIState_Enable_MORT) || \
                                  ((STATE) == TIM_OSSIState_Disable_MORT))
/**
  * @}
  */

/** @defgroup TIM_OSSR_Off_State_Selection_for_Run_mode_state
  * @{
  */

#define TIM_OSSRState_Enable_MORT               ((uint16_t)0x0800)
#define TIM_OSSRState_Disable_MORT              ((uint16_t)0x0000)
#define IS_TIM_OSSR_STATE_MORT(STATE) (((STATE) == TIM_OSSRState_Enable_MORT) || \
                                  ((STATE) == TIM_OSSRState_Disable_MORT))
/**
  * @}
  */ 

/** @defgroup TIM_Output_Compare_Idle_State 
  * @{
  */

#define TIM_OCIdleState_Set_MORT                ((uint16_t)0x0100)
#define TIM_OCIdleState_Reset_MORT              ((uint16_t)0x0000)
#define IS_TIM_OCIDLE_STATE_MORT(STATE) (((STATE) == TIM_OCIdleState_Set_MORT) || \
                                    ((STATE) == TIM_OCIdleState_Reset_MORT))
/**
  * @}
  */ 

/** @defgroup TIM_Output_Compare_N_Idle_State 
  * @{
  */

#define TIM_OCNIdleState_Set_MORT               ((uint16_t)0x0200)
#define TIM_OCNIdleState_Reset_MORT             ((uint16_t)0x0000)
#define IS_TIM_OCNIDLE_STATE_MORT(STATE) (((STATE) == TIM_OCNIdleState_Set_MORT) || \
                                     ((STATE) == TIM_OCNIdleState_Reset_MORT))
/**
  * @}
  */ 

/** @defgroup TIM_Input_Capture_Polarity 
  * @{
  */

#define  TIM_ICPolarity_Rising_MORT             ((uint16_t)0x0000)
#define  TIM_ICPolarity_Falling_MORT            ((uint16_t)0x0002)
#define  TIM_ICPolarity_BothEdge_MORT           ((uint16_t)0x000A)
#define IS_TIM_IC_POLARITY_MORT(POLARITY) (((POLARITY) == TIM_ICPolarity_Rising_MORT) || \
                                      ((POLARITY) == TIM_ICPolarity_Falling_MORT)|| \
                                      ((POLARITY) == TIM_ICPolarity_BothEdge_MORT))
/**
  * @}
  */ 

/** @defgroup TIM_Input_Capture_Selection 
  * @{
  */

#define TIM_ICSelection_DirectTI_MORT           ((uint16_t)0x0001) /*!< TIM Input 1, 2, 3 or 4 is selected to be 
                                                                   connected to IC1, IC2, IC3 or IC4, respectively */
#define TIM_ICSelection_IndirectTI_MORT         ((uint16_t)0x0002) /*!< TIM Input 1, 2, 3 or 4 is selected to be
                                                                   connected to IC2, IC1, IC4 or IC3, respectively. */
#define TIM_ICSelection_TRC_MORT                ((uint16_t)0x0003) /*!< TIM Input 1, 2, 3 or 4 is selected to be connected to TRC. */
#define IS_TIM_IC_SELECTION_MORT(SELECTION) (((SELECTION) == TIM_ICSelection_DirectTI_MORT) || \
                                        ((SELECTION) == TIM_ICSelection_IndirectTI_MORT) || \
                                        ((SELECTION) == TIM_ICSelection_TRC_MORT))
/**
  * @}
  */ 

/** @defgroup TIM_Input_Capture_Prescaler 
  * @{
  */

#define TIM_ICPSC_DIV1_MORT                     ((uint16_t)0x0000) /*!< Capture performed each time an edge is detected on the capture input. */
#define TIM_ICPSC_DIV2_MORT                     ((uint16_t)0x0004) /*!< Capture performed once every 2 events. */
#define TIM_ICPSC_DIV4_MORT                     ((uint16_t)0x0008) /*!< Capture performed once every 4 events. */
#define TIM_ICPSC_DIV8_MORT                     ((uint16_t)0x000C) /*!< Capture performed once every 8 events. */
#define IS_TIM_IC_PRESCALER_MORT(PRESCALER) (((PRESCALER) == TIM_ICPSC_DIV1_MORT) || \
                                        ((PRESCALER) == TIM_ICPSC_DIV2_MORT) || \
                                        ((PRESCALER) == TIM_ICPSC_DIV4_MORT) || \
                                        ((PRESCALER) == TIM_ICPSC_DIV8_MORT))
/**
  * @}
  */ 

/** @defgroup TIM_interrupt_sources 
  * @{
  */

#define TIM_IT_Update_MORT                      ((uint16_t)0x0001)
#define TIM_IT_CC1_MORT                         ((uint16_t)0x0002)
#define TIM_IT_CC2_MORT                         ((uint16_t)0x0004)
#define TIM_IT_CC3_MORT                         ((uint16_t)0x0008)
#define TIM_IT_CC4_MORT                         ((uint16_t)0x0010)
#define TIM_IT_COM_MORT                         ((uint16_t)0x0020)
#define TIM_IT_Trigger_MORT                     ((uint16_t)0x0040)
#define TIM_IT_Break_MORT                       ((uint16_t)0x0080)
#define IS_TIM_IT_MORT(IT) ((((IT) & (uint16_t)0xFF00) == 0x0000) && ((IT) != 0x0000))

#define IS_TIM_GET_IT_MORT(IT) (((IT) == TIM_IT_Update_MORT) || \
                           ((IT) == TIM_IT_CC1_MORT) || \
                           ((IT) == TIM_IT_CC2_MORT) || \
                           ((IT) == TIM_IT_CC3_MORT) || \
                           ((IT) == TIM_IT_CC4_MORT) || \
                           ((IT) == TIM_IT_COM_MORT) || \
                           ((IT) == TIM_IT_Trigger_MORT) || \
                           ((IT) == TIM_IT_Break_MORT))
/**
  * @}
  */ 

/** @defgroup TIM_DMA_Base_address 
  * @{
  */

#define TIM_DMABase_CR1_MORT                    ((uint16_t)0x0000)
#define TIM_DMABase_CR2_MORT                    ((uint16_t)0x0001)
#define TIM_DMABase_SMCR_MORT                   ((uint16_t)0x0002)
#define TIM_DMABase_DIER_MORT                   ((uint16_t)0x0003)
#define TIM_DMABase_SR_MORT                     ((uint16_t)0x0004)
#define TIM_DMABase_EGR_MORT                    ((uint16_t)0x0005)
#define TIM_DMABase_CCMR1_MORT                  ((uint16_t)0x0006)
#define TIM_DMABase_CCMR2_MORT                  ((uint16_t)0x0007)
#define TIM_DMABase_CCER_MORT                   ((uint16_t)0x0008)
#define TIM_DMABase_CNT_MORT                    ((uint16_t)0x0009)
#define TIM_DMABase_PSC_MORT                    ((uint16_t)0x000A)
#define TIM_DMABase_ARR_MORT                    ((uint16_t)0x000B)
#define TIM_DMABase_RCR_MORT                    ((uint16_t)0x000C)
#define TIM_DMABase_CCR1_MORT                   ((uint16_t)0x000D)
#define TIM_DMABase_CCR2_MORT                   ((uint16_t)0x000E)
#define TIM_DMABase_CCR3_MORT                   ((uint16_t)0x000F)
#define TIM_DMABase_CCR4_MORT                   ((uint16_t)0x0010)
#define TIM_DMABase_BDTR_MORT                   ((uint16_t)0x0011)
#define TIM_DMABase_DCR_MORT                    ((uint16_t)0x0012)
#define TIM_DMABase_OR_MORT                     ((uint16_t)0x0013)
#define IS_TIM_DMA_BASE_MORT(BASE) (((BASE) == TIM_DMABase_CR1_MORT) || \
                               ((BASE) == TIM_DMABase_CR2_MORT) || \
                               ((BASE) == TIM_DMABase_SMCR_MORT) || \
                               ((BASE) == TIM_DMABase_DIER_MORT) || \
                               ((BASE) == TIM_DMABase_SR_MORT) || \
                               ((BASE) == TIM_DMABase_EGR_MORT) || \
                               ((BASE) == TIM_DMABase_CCMR1_MORT) || \
                               ((BASE) == TIM_DMABase_CCMR2_MORT) || \
                               ((BASE) == TIM_DMABase_CCER_MORT) || \
                               ((BASE) == TIM_DMABase_CNT_MORT) || \
                               ((BASE) == TIM_DMABase_PSC_MORT) || \
                               ((BASE) == TIM_DMABase_ARR_MORT) || \
                               ((BASE) == TIM_DMABase_RCR_MORT) || \
                               ((BASE) == TIM_DMABase_CCR1_MORT) || \
                               ((BASE) == TIM_DMABase_CCR2_MORT) || \
                               ((BASE) == TIM_DMABase_CCR3_MORT) || \
                               ((BASE) == TIM_DMABase_CCR4_MORT) || \
                               ((BASE) == TIM_DMABase_BDTR_MORT) || \
                               ((BASE) == TIM_DMABase_DCR_MORT) || \
                               ((BASE) == TIM_DMABase_OR_MORT))                     
/**
  * @}
  */ 

/** @defgroup TIM_DMA_Burst_Length 
  * @{
  */

#define TIM_DMABurstLength_1Transfer_MORT           ((uint16_t)0x0000)
#define TIM_DMABurstLength_2Transfers_MORT          ((uint16_t)0x0100)
#define TIM_DMABurstLength_3Transfers_MORT          ((uint16_t)0x0200)
#define TIM_DMABurstLength_4Transfers_MORT          ((uint16_t)0x0300)
#define TIM_DMABurstLength_5Transfers_MORT          ((uint16_t)0x0400)
#define TIM_DMABurstLength_6Transfers_MORT          ((uint16_t)0x0500)
#define TIM_DMABurstLength_7Transfers_MORT          ((uint16_t)0x0600)
#define TIM_DMABurstLength_8Transfers_MORT          ((uint16_t)0x0700)
#define TIM_DMABurstLength_9Transfers_MORT          ((uint16_t)0x0800)
#define TIM_DMABurstLength_10Transfers_MORT         ((uint16_t)0x0900)
#define TIM_DMABurstLength_11Transfers_MORT         ((uint16_t)0x0A00)
#define TIM_DMABurstLength_12Transfers_MORT         ((uint16_t)0x0B00)
#define TIM_DMABurstLength_13Transfers_MORT         ((uint16_t)0x0C00)
#define TIM_DMABurstLength_14Transfers_MORT         ((uint16_t)0x0D00)
#define TIM_DMABurstLength_15Transfers_MORT         ((uint16_t)0x0E00)
#define TIM_DMABurstLength_16Transfers_MORT         ((uint16_t)0x0F00)
#define TIM_DMABurstLength_17Transfers_MORT         ((uint16_t)0x1000)
#define TIM_DMABurstLength_18Transfers_MORT         ((uint16_t)0x1100)
#define IS_TIM_DMA_LENGTH_MORT(LENGTH) (((LENGTH) == TIM_DMABurstLength_1Transfer_MORT) || \
                                   ((LENGTH) == TIM_DMABurstLength_2Transfers_MORT) || \
                                   ((LENGTH) == TIM_DMABurstLength_3Transfers_MORT) || \
                                   ((LENGTH) == TIM_DMABurstLength_4Transfers_MORT) || \
                                   ((LENGTH) == TIM_DMABurstLength_5Transfers_MORT) || \
                                   ((LENGTH) == TIM_DMABurstLength_6Transfers_MORT) || \
                                   ((LENGTH) == TIM_DMABurstLength_7Transfers_MORT) || \
                                   ((LENGTH) == TIM_DMABurstLength_8Transfers_MORT) || \
                                   ((LENGTH) == TIM_DMABurstLength_9Transfers_MORT) || \
                                   ((LENGTH) == TIM_DMABurstLength_10Transfers_MORT) || \
                                   ((LENGTH) == TIM_DMABurstLength_11Transfers_MORT) || \
                                   ((LENGTH) == TIM_DMABurstLength_12Transfers_MORT) || \
                                   ((LENGTH) == TIM_DMABurstLength_13Transfers_MORT) || \
                                   ((LENGTH) == TIM_DMABurstLength_14Transfers_MORT) || \
                                   ((LENGTH) == TIM_DMABurstLength_15Transfers_MORT) || \
                                   ((LENGTH) == TIM_DMABurstLength_16Transfers_MORT) || \
                                   ((LENGTH) == TIM_DMABurstLength_17Transfers_MORT) || \
                                   ((LENGTH) == TIM_DMABurstLength_18Transfers_MORT))
/**
  * @}
  */ 

/** @defgroup TIM_DMA_sources 
  * @{
  */

#define TIM_DMA_Update_MORT                     ((uint16_t)0x0100)
#define TIM_DMA_CC1_MORT                        ((uint16_t)0x0200)
#define TIM_DMA_CC2_MORT                        ((uint16_t)0x0400)
#define TIM_DMA_CC3_MORT                        ((uint16_t)0x0800)
#define TIM_DMA_CC4_MORT                        ((uint16_t)0x1000)
#define TIM_DMA_COM_MORT                        ((uint16_t)0x2000)
#define TIM_DMA_Trigger_MORT                    ((uint16_t)0x4000)
#define IS_TIM_DMA_SOURCE_MORT(SOURCE) ((((SOURCE) & (uint16_t)0x80FF) == 0x0000) && ((SOURCE) != 0x0000))

/**
  * @}
  */ 

/** @defgroup TIM_External_Trigger_Prescaler 
  * @{
  */

#define TIM_ExtTRGPSC_OFF_MORT                  ((uint16_t)0x0000)
#define TIM_ExtTRGPSC_DIV2_MORT                 ((uint16_t)0x1000)
#define TIM_ExtTRGPSC_DIV4_MORT                 ((uint16_t)0x2000)
#define TIM_ExtTRGPSC_DIV8_MORT                 ((uint16_t)0x3000)
#define IS_TIM_EXT_PRESCALER_MORT(PRESCALER) (((PRESCALER) == TIM_ExtTRGPSC_OFF_MORT) || \
                                         ((PRESCALER) == TIM_ExtTRGPSC_DIV2_MORT) || \
                                         ((PRESCALER) == TIM_ExtTRGPSC_DIV4_MORT) || \
                                         ((PRESCALER) == TIM_ExtTRGPSC_DIV8_MORT))
/**
  * @}
  */ 

/** @defgroup TIM_Internal_Trigger_Selection 
  * @{
  */

#define TIM_TS_ITR0_MORT                        ((uint16_t)0x0000)
#define TIM_TS_ITR1_MORT                        ((uint16_t)0x0010)
#define TIM_TS_ITR2_MORT                        ((uint16_t)0x0020)
#define TIM_TS_ITR3_MORT                        ((uint16_t)0x0030)
#define TIM_TS_TI1F_ED_MORT                     ((uint16_t)0x0040)
#define TIM_TS_TI1FP1_MORT                      ((uint16_t)0x0050)
#define TIM_TS_TI2FP2_MORT                      ((uint16_t)0x0060)
#define TIM_TS_ETRF_MORT                        ((uint16_t)0x0070)
#define IS_TIM_TRIGGER_SELECTION_MORT(SELECTION) (((SELECTION) == TIM_TS_ITR0_MORT) || \
                                             ((SELECTION) == TIM_TS_ITR1_MORT) || \
                                             ((SELECTION) == TIM_TS_ITR2_MORT) || \
                                             ((SELECTION) == TIM_TS_ITR3_MORT) || \
                                             ((SELECTION) == TIM_TS_TI1F_ED_MORT) || \
                                             ((SELECTION) == TIM_TS_TI1FP1_MORT) || \
                                             ((SELECTION) == TIM_TS_TI2FP2_MORT) || \
                                             ((SELECTION) == TIM_TS_ETRF_MORT))
#define IS_TIM_INTERNAL_TRIGGER_SELECTION_MORT(SELECTION) (((SELECTION) == TIM_TS_ITR0_MORT) || \
                                                      ((SELECTION) == TIM_TS_ITR1_MORT) || \
                                                      ((SELECTION) == TIM_TS_ITR2_MORT) || \
                                                      ((SELECTION) == TIM_TS_ITR3_MORT))
/**
  * @}
  */ 

/** @defgroup TIM_TIx_External_Clock_Source 
  * @{
  */

#define TIM_TIxExternalCLK1Source_TI1_MORT      ((uint16_t)0x0050)
#define TIM_TIxExternalCLK1Source_TI2_MORT      ((uint16_t)0x0060)
#define TIM_TIxExternalCLK1Source_TI1ED_MORT    ((uint16_t)0x0040)

/**
  * @}
  */ 

/** @defgroup TIM_External_Trigger_Polarity 
  * @{
  */ 
#define TIM_ExtTRGPolarity_Inverted_MORT        ((uint16_t)0x8000)
#define TIM_ExtTRGPolarity_NonInverted_MORT     ((uint16_t)0x0000)
#define IS_TIM_EXT_POLARITY_MORT(POLARITY) (((POLARITY) == TIM_ExtTRGPolarity_Inverted_MORT) || \
                                       ((POLARITY) == TIM_ExtTRGPolarity_NonInverted_MORT))
/**
  * @}
  */

/** @defgroup TIM_Prescaler_Reload_Mode 
  * @{
  */

#define TIM_PSCReloadMode_Update_MORT           ((uint16_t)0x0000)
#define TIM_PSCReloadMode_Immediate_MORT        ((uint16_t)0x0001)
#define IS_TIM_PRESCALER_RELOAD_MORT(RELOAD) (((RELOAD) == TIM_PSCReloadMode_Update_MORT) || \
                                         ((RELOAD) == TIM_PSCReloadMode_Immediate_MORT))
/**
  * @}
  */ 

/** @defgroup TIM_Forced_Action 
  * @{
  */

#define TIM_ForcedAction_Active_MORT            ((uint16_t)0x0050)
#define TIM_ForcedAction_InActive_MORT          ((uint16_t)0x0040)
#define IS_TIM_FORCED_ACTION_MORT(ACTION) (((ACTION) == TIM_ForcedAction_Active_MORT) || \
                                      ((ACTION) == TIM_ForcedAction_InActive_MORT))
/**
  * @}
  */ 

/** @defgroup TIM_Encoder_Mode 
  * @{
  */

#define TIM_EncoderMode_TI1_MORT                ((uint16_t)0x0001)
#define TIM_EncoderMode_TI2_MORT                ((uint16_t)0x0002)
#define TIM_EncoderMode_TI12_MORT               ((uint16_t)0x0003)
#define IS_TIM_ENCODER_MODE_MORT(MODE) (((MODE) == TIM_EncoderMode_TI1_MORT) || \
                                   ((MODE) == TIM_EncoderMode_TI2_MORT) || \
                                   ((MODE) == TIM_EncoderMode_TI12_MORT))
/**
  * @}
  */ 


/** @defgroup TIM_Event_Source 
  * @{
  */

#define TIM_EventSource_Update_MORT             ((uint16_t)0x0001)
#define TIM_EventSource_CC1_MORT                ((uint16_t)0x0002)
#define TIM_EventSource_CC2_MORT                ((uint16_t)0x0004)
#define TIM_EventSource_CC3_MORT                ((uint16_t)0x0008)
#define TIM_EventSource_CC4_MORT                ((uint16_t)0x0010)
#define TIM_EventSource_COM_MORT                ((uint16_t)0x0020)
#define TIM_EventSource_Trigger_MORT            ((uint16_t)0x0040)
#define TIM_EventSource_Break_MORT              ((uint16_t)0x0080)
#define IS_TIM_EVENT_SOURCE_MORT(SOURCE) ((((SOURCE) & (uint16_t)0xFF00) == 0x0000) && ((SOURCE) != 0x0000))                                          
  
/**
  * @}
  */ 

/** @defgroup TIM_Update_Source 
  * @{
  */

#define TIM_UpdateSource_Global_MORT            ((uint16_t)0x0000) /*!< Source of update is the counter overflow/underflow
                                                                   or the setting of UG bit, or an update generation
                                                                   through the slave mode controller. */
#define TIM_UpdateSource_Regular_MORT           ((uint16_t)0x0001) /*!< Source of update is counter overflow/underflow. */
#define IS_TIM_UPDATE_SOURCE_MORT(SOURCE) (((SOURCE) == TIM_UpdateSource_Global_MORT) || \
                                      ((SOURCE) == TIM_UpdateSource_Regular_MORT))
/**
  * @}
  */ 

/** @defgroup TIM_Output_Compare_Preload_State 
  * @{
  */

#define TIM_OCPreload_Enable_MORT               ((uint16_t)0x0008)
#define TIM_OCPreload_Disable_MORT              ((uint16_t)0x0000)
#define IS_TIM_OCPRELOAD_STATE_MORT(STATE) (((STATE) == TIM_OCPreload_Enable_MORT) || \
                                       ((STATE) == TIM_OCPreload_Disable_MORT))
/**
  * @}
  */ 

/** @defgroup TIM_Output_Compare_Fast_State 
  * @{
  */

#define TIM_OCFast_Enable_MORT                  ((uint16_t)0x0004)
#define TIM_OCFast_Disable_MORT                 ((uint16_t)0x0000)
#define IS_TIM_OCFAST_STATE_MORT(STATE) (((STATE) == TIM_OCFast_Enable_MORT) || \
                                    ((STATE) == TIM_OCFast_Disable_MORT))
                                     
/**
  * @}
  */ 

/** @defgroup TIM_Output_Compare_Clear_State 
  * @{
  */

#define TIM_OCClear_Enable_MORT                 ((uint16_t)0x0080)
#define TIM_OCClear_Disable_MORT                ((uint16_t)0x0000)
#define IS_TIM_OCCLEAR_STATE_MORT(STATE) (((STATE) == TIM_OCClear_Enable_MORT) || \
                                     ((STATE) == TIM_OCClear_Disable_MORT))
/**
  * @}
  */ 

/** @defgroup TIM_Trigger_Output_Source 
  * @{
  */

#define TIM_TRGOSource_Reset_MORT               ((uint16_t)0x0000)
#define TIM_TRGOSource_Enable_MORT              ((uint16_t)0x0010)
#define TIM_TRGOSource_Update_MORT              ((uint16_t)0x0020)
#define TIM_TRGOSource_OC1_MORT                 ((uint16_t)0x0030)
#define TIM_TRGOSource_OC1Ref_MORT              ((uint16_t)0x0040)
#define TIM_TRGOSource_OC2Ref_MORT              ((uint16_t)0x0050)
#define TIM_TRGOSource_OC3Ref_MORT              ((uint16_t)0x0060)
#define TIM_TRGOSource_OC4Ref_MORT              ((uint16_t)0x0070)
#define IS_TIM_TRGO_SOURCE_MORT(SOURCE) (((SOURCE) == TIM_TRGOSource_Reset_MORT) || \
                                    ((SOURCE) == TIM_TRGOSource_Enable_MORT) || \
                                    ((SOURCE) == TIM_TRGOSource_Update_MORT) || \
                                    ((SOURCE) == TIM_TRGOSource_OC1_MORT) || \
                                    ((SOURCE) == TIM_TRGOSource_OC1Ref_MORT) || \
                                    ((SOURCE) == TIM_TRGOSource_OC2Ref_MORT) || \
                                    ((SOURCE) == TIM_TRGOSource_OC3Ref_MORT) || \
                                    ((SOURCE) == TIM_TRGOSource_OC4Ref_MORT))
/**
  * @}
  */ 

/** @defgroup TIM_Slave_Mode 
  * @{
  */

#define TIM_SlaveMode_Reset_MORT                ((uint16_t)0x0004)
#define TIM_SlaveMode_Gated_MORT                ((uint16_t)0x0005)
#define TIM_SlaveMode_Trigger_MORT              ((uint16_t)0x0006)
#define TIM_SlaveMode_External1_MORT            ((uint16_t)0x0007)
#define IS_TIM_SLAVE_MODE_MORT(MODE) (((MODE) == TIM_SlaveMode_Reset_MORT) || \
                                 ((MODE) == TIM_SlaveMode_Gated_MORT) || \
                                 ((MODE) == TIM_SlaveMode_Trigger_MORT) || \
                                 ((MODE) == TIM_SlaveMode_External1_MORT))
/**
  * @}
  */ 

/** @defgroup TIM_Master_Slave_Mode 
  * @{
  */

#define TIM_MasterSlaveMode_Enable_MORT         ((uint16_t)0x0080)
#define TIM_MasterSlaveMode_Disable_MORT        ((uint16_t)0x0000)
#define IS_TIM_MSM_STATE_MORT(STATE) (((STATE) == TIM_MasterSlaveMode_Enable_MORT) || \
                                 ((STATE) == TIM_MasterSlaveMode_Disable_MORT))
/**
  * @}
  */ 
/** @defgroup TIM_Remap 
  * @{
  */

#define TIM2_TIM8_TRGO_MORT                     ((uint16_t)0x0000)
#define TIM2_ETH_PTP_MORT                       ((uint16_t)0x0400)
#define TIM2_USBFS_SOF_MORT                     ((uint16_t)0x0800)
#define TIM2_USBHS_SOF_MORT                     ((uint16_t)0x0C00)

#define TIM5_GPIO_MORT                          ((uint16_t)0x0000)
#define TIM5_LSI_MORT                           ((uint16_t)0x0040)
#define TIM5_LSE_MORT                           ((uint16_t)0x0080)
#define TIM5_RTC_MORT                           ((uint16_t)0x00C0)

#define TIM11_GPIO_MORT                         ((uint16_t)0x0000)
#define TIM11_HSE_MORT                          ((uint16_t)0x0002)

#define IS_TIM_REMAP_MORT(TIM_REMAP)	 (((TIM_REMAP) == TIM2_TIM8_TRGO_MORT)||\
                                  ((TIM_REMAP) == TIM2_ETH_PTP_MORT)||\
                                  ((TIM_REMAP) == TIM2_USBFS_SOF_MORT)||\
                                  ((TIM_REMAP) == TIM2_USBHS_SOF_MORT)||\
                                  ((TIM_REMAP) == TIM5_GPIO_MORT)||\
                                  ((TIM_REMAP) == TIM5_LSI_MORT)||\
                                  ((TIM_REMAP) == TIM5_LSE_MORT)||\
                                  ((TIM_REMAP) == TIM5_RTC_MORT)||\
                                  ((TIM_REMAP) == TIM11_GPIO_MORT)||\
                                  ((TIM_REMAP) == TIM11_HSE_MORT))

/**
  * @}
  */ 
/** @defgroup TIM_Flags 
  * @{
  */

#define TIM_FLAG_Update_MORT                    ((uint16_t)0x0001)
#define TIM_FLAG_CC1_MORT                       ((uint16_t)0x0002)
#define TIM_FLAG_CC2_MORT                       ((uint16_t)0x0004)
#define TIM_FLAG_CC3_MORT                       ((uint16_t)0x0008)
#define TIM_FLAG_CC4_MORT                       ((uint16_t)0x0010)
#define TIM_FLAG_COM_MORT                       ((uint16_t)0x0020)
#define TIM_FLAG_Trigger_MORT                   ((uint16_t)0x0040)
#define TIM_FLAG_Break_MORT                     ((uint16_t)0x0080)
#define TIM_FLAG_CC1OF_MORT                     ((uint16_t)0x0200)
#define TIM_FLAG_CC2OF_MORT                     ((uint16_t)0x0400)
#define TIM_FLAG_CC3OF_MORT                     ((uint16_t)0x0800)
#define TIM_FLAG_CC4OF_MORT                     ((uint16_t)0x1000)
#define IS_TIM_GET_FLAG_MORT(FLAG) (((FLAG) == TIM_FLAG_Update_MORT) || \
                               ((FLAG) == TIM_FLAG_CC1_MORT) || \
                               ((FLAG) == TIM_FLAG_CC2_MORT) || \
                               ((FLAG) == TIM_FLAG_CC3_MORT) || \
                               ((FLAG) == TIM_FLAG_CC4_MORT) || \
                               ((FLAG) == TIM_FLAG_COM_MORT) || \
                               ((FLAG) == TIM_FLAG_Trigger_MORT) || \
                               ((FLAG) == TIM_FLAG_Break_MORT) || \
                               ((FLAG) == TIM_FLAG_CC1OF_MORT) || \
                               ((FLAG) == TIM_FLAG_CC2OF_MORT) || \
                               ((FLAG) == TIM_FLAG_CC3OF_MORT) || \
                               ((FLAG) == TIM_FLAG_CC4OF_MORT))

/**
  * @}
  */ 

/** @defgroup TIM_Input_Capture_Filer_Value 
  * @{
  */

#define IS_TIM_IC_FILTER_MORT(ICFILTER) ((ICFILTER) <= 0xF) 
/**
  * @}
  */ 

/** @defgroup TIM_External_Trigger_Filter 
  * @{
  */

#define IS_TIM_EXT_FILTER_MORT(EXTFILTER) ((EXTFILTER) <= 0xF)
/**
  * @}
  */ 

/** @defgroup TIM_Legacy 
  * @{
  */

#define TIM_DMABurstLength_1Byte_MORT           TIM_DMABurstLength_1Transfer_MORT
#define TIM_DMABurstLength_2Bytes_MORT          TIM_DMABurstLength_2Transfers_MORT
#define TIM_DMABurstLength_3Bytes_MORT          TIM_DMABurstLength_3Transfers_MORT
#define TIM_DMABurstLength_4Bytes_MORT          TIM_DMABurstLength_4Transfers_MORT
#define TIM_DMABurstLength_5Bytes_MORT          TIM_DMABurstLength_5Transfers_MORT
#define TIM_DMABurstLength_6Bytes_MORT          TIM_DMABurstLength_6Transfers_MORT
#define TIM_DMABurstLength_7Bytes_MORT          TIM_DMABurstLength_7Transfers_MORT
#define TIM_DMABurstLength_8Bytes_MORT          TIM_DMABurstLength_8Transfers_MORT
#define TIM_DMABurstLength_9Bytes_MORT          TIM_DMABurstLength_9Transfers_MORT
#define TIM_DMABurstLength_10Bytes_MORT         TIM_DMABurstLength_10Transfers_MORT
#define TIM_DMABurstLength_11Bytes_MORT         TIM_DMABurstLength_11Transfers_MORT
#define TIM_DMABurstLength_12Bytes_MORT         TIM_DMABurstLength_12Transfers_MORT
#define TIM_DMABurstLength_13Bytes_MORT         TIM_DMABurstLength_13Transfers_MORT
#define TIM_DMABurstLength_14Bytes_MORT         TIM_DMABurstLength_14Transfers_MORT
#define TIM_DMABurstLength_15Bytes_MORT         TIM_DMABurstLength_15Transfers_MORT
#define TIM_DMABurstLength_16Bytes_MORT         TIM_DMABurstLength_16Transfers_MORT
#define TIM_DMABurstLength_17Bytes_MORT         TIM_DMABurstLength_17Transfers_MORT
#define TIM_DMABurstLength_18Bytes_MORT         TIM_DMABurstLength_18Transfers_MORT
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 

/* TimeBase management ********************************************************/
void TIM_DeInit_mort(TIM_TypeDef_mort* TIMx);
void TIM_TimeBaseInit_mort(TIM_TypeDef_mort* TIMx, TIM_TimeBaseInitTypeDef_mort* TIM_TimeBaseInitStruct);
void TIM_TimeBaseStructInit_mort(TIM_TimeBaseInitTypeDef_mort* TIM_TimeBaseInitStruct);
void TIM_PrescalerConfig_mort(TIM_TypeDef_mort* TIMx, uint16_t Prescaler, uint16_t TIM_PSCReloadMode);
void TIM_CounterModeConfig_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_CounterMode);
void TIM_SetCounter_mort(TIM_TypeDef_mort* TIMx, uint32_t Counter);
void TIM_SetAutoreload_mort(TIM_TypeDef_mort* TIMx, uint32_t Autoreload);
uint32_t TIM_GetCounter_mort(TIM_TypeDef_mort* TIMx);
uint16_t TIM_GetPrescaler_mort(TIM_TypeDef_mort* TIMx);
void TIM_UpdateDisableConfig_mort(TIM_TypeDef_mort* TIMx, FunctionalState NewState);
void TIM_UpdateRequestConfig_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_UpdateSource);
void TIM_ARRPreloadConfig_mort(TIM_TypeDef_mort* TIMx, FunctionalState NewState);
void TIM_SelectOnePulseMode_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_OPMode);
void TIM_SetClockDivision_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_CKD);
void TIM_Cmd_mort(TIM_TypeDef_mort* TIMx, FunctionalState NewState);

/* Output Compare management **************************************************/
void TIM_OC1Init_mort(TIM_TypeDef_mort* TIMx, TIM_OCInitTypeDef_mort* TIM_OCInitStruct);
void TIM_OC2Init_mort(TIM_TypeDef_mort* TIMx, TIM_OCInitTypeDef_mort* TIM_OCInitStruct);
void TIM_OC3Init_mort(TIM_TypeDef_mort* TIMx, TIM_OCInitTypeDef_mort* TIM_OCInitStruct);
void TIM_OC4Init_mort(TIM_TypeDef_mort* TIMx, TIM_OCInitTypeDef_mort* TIM_OCInitStruct);
void TIM_OCStructInit_mort(TIM_OCInitTypeDef_mort* TIM_OCInitStruct);
void TIM_SelectOCxM_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_Channel, uint16_t TIM_OCMode);
void TIM_SetCompare1_mort(TIM_TypeDef_mort* TIMx, uint32_t Compare1);
void TIM_SetCompare2_mort(TIM_TypeDef_mort* TIMx, uint32_t Compare2);
void TIM_SetCompare3_mort(TIM_TypeDef_mort* TIMx, uint32_t Compare3);
void TIM_SetCompare4_mort(TIM_TypeDef_mort* TIMx, uint32_t Compare4);
void TIM_ForcedOC1Config_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_ForcedAction);
void TIM_ForcedOC2Config_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_ForcedAction);
void TIM_ForcedOC3Config_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_ForcedAction);
void TIM_ForcedOC4Config_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_ForcedAction);
void TIM_OC1PreloadConfig_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_OCPreload);
void TIM_OC2PreloadConfig_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_OCPreload);
void TIM_OC3PreloadConfig_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_OCPreload);
void TIM_OC4PreloadConfig_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_OCPreload);
void TIM_OC1FastConfig_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_OCFast);
void TIM_OC2FastConfig_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_OCFast);
void TIM_OC3FastConfig_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_OCFast);
void TIM_OC4FastConfig_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_OCFast);
void TIM_ClearOC1Ref_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_OCClear);
void TIM_ClearOC2Ref_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_OCClear);
void TIM_ClearOC3Ref_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_OCClear);
void TIM_ClearOC4Ref_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_OCClear);
void TIM_OC1PolarityConfig_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_OCPolarity);
void TIM_OC1NPolarityConfig_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_OCNPolarity);
void TIM_OC2PolarityConfig_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_OCPolarity);
void TIM_OC2NPolarityConfig_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_OCNPolarity);
void TIM_OC3PolarityConfig_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_OCPolarity);
void TIM_OC3NPolarityConfig_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_OCNPolarity);
void TIM_OC4PolarityConfig_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_OCPolarity);
void TIM_CCxCmd_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_Channel, uint16_t TIM_CCx);
void TIM_CCxNCmd_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_Channel, uint16_t TIM_CCxN);

/* Input Capture management ***************************************************/
void TIM_ICInit_mort(TIM_TypeDef_mort* TIMx, TIM_ICInitTypeDef_mort* TIM_ICInitStruct);
void TIM_ICStructInit_mort(TIM_ICInitTypeDef_mort* TIM_ICInitStruct);
void TIM_PWMIConfig_mort(TIM_TypeDef_mort* TIMx, TIM_ICInitTypeDef_mort* TIM_ICInitStruct);
uint32_t TIM_GetCapture1_mort(TIM_TypeDef_mort* TIMx);
uint32_t TIM_GetCapture2_mort(TIM_TypeDef_mort* TIMx);
uint32_t TIM_GetCapture3_mort(TIM_TypeDef_mort* TIMx);
uint32_t TIM_GetCapture4_mort(TIM_TypeDef_mort* TIMx);
void TIM_SetIC1Prescaler_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_ICPSC);
void TIM_SetIC2Prescaler_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_ICPSC);
void TIM_SetIC3Prescaler_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_ICPSC);
void TIM_SetIC4Prescaler_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_ICPSC);

/* Advanced-control timers (TIM1_MORT and TIM8_MORT) specific features ******************/
void TIM_BDTRConfig_mort(TIM_TypeDef_mort* TIMx, TIM_BDTRInitTypeDef_mort *TIM_BDTRInitStruct);
void TIM_BDTRStructInit_mort(TIM_BDTRInitTypeDef_mort* TIM_BDTRInitStruct);
void TIM_CtrlPWMOutputs_mort(TIM_TypeDef_mort* TIMx, FunctionalState NewState);
void TIM_SelectCOM_mort(TIM_TypeDef_mort* TIMx, FunctionalState NewState);
void TIM_CCPreloadControl_mort(TIM_TypeDef_mort* TIMx, FunctionalState NewState);

/* Interrupts, DMA and flags management ***************************************/
void TIM_ITConfig_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_IT, FunctionalState NewState);
void TIM_GenerateEvent_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_EventSource);
FlagStatus TIM_GetFlagStatus_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_FLAG);
void TIM_ClearFlag_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_FLAG);
ITStatus TIM_GetITStatus_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_IT);
void TIM_ClearITPendingBit_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_IT);
void TIM_DMAConfig_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_DMABase, uint16_t TIM_DMABurstLength);
void TIM_DMACmd_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_DMASource, FunctionalState NewState);
void TIM_SelectCCDMA_mort(TIM_TypeDef_mort* TIMx, FunctionalState NewState);

/* Clocks management **********************************************************/
void TIM_InternalClockConfig_mort(TIM_TypeDef_mort* TIMx);
void TIM_ITRxExternalClockConfig_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_InputTriggerSource);
void TIM_TIxExternalClockConfig_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_TIxExternalCLKSource,
                                uint16_t TIM_ICPolarity, uint16_t ICFilter);
void TIM_ETRClockMode1Config_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_ExtTRGPrescaler, uint16_t TIM_ExtTRGPolarity,
                             uint16_t ExtTRGFilter);
void TIM_ETRClockMode2Config_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_ExtTRGPrescaler, 
                             uint16_t TIM_ExtTRGPolarity, uint16_t ExtTRGFilter);

/* Synchronization management *************************************************/
void TIM_SelectInputTrigger_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_InputTriggerSource);
void TIM_SelectOutputTrigger_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_TRGOSource);
void TIM_SelectSlaveMode_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_SlaveMode);
void TIM_SelectMasterSlaveMode_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_MasterSlaveMode);
void TIM_ETRConfig_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_ExtTRGPrescaler, uint16_t TIM_ExtTRGPolarity,
                   uint16_t ExtTRGFilter);

/* Specific interface management **********************************************/   
void TIM_EncoderInterfaceConfig_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_EncoderMode,
                                uint16_t TIM_IC1Polarity, uint16_t TIM_IC2Polarity);
void TIM_SelectHallSensor_mort(TIM_TypeDef_mort* TIMx, FunctionalState NewState);

/* Specific remapping management **********************************************/
void TIM_RemapConfig_mort(TIM_TypeDef_mort* TIMx, uint16_t TIM_Remap);

#ifdef __cplusplus
}
#endif

#endif /*__STM32F4xx_TIM_H */

/**
  * @}
  */ 

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/



