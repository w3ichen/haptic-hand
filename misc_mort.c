/**
  ******************************************************************************
  * @file    misc.c
  * @author  MCD Application Team
  * @version V1.8.0
  * @date    04-November-2016
  * @brief   This file provides all the miscellaneous firmware functions (add-on
  *          to CMSIS functions).
  *          
  *  @verbatim   
  *                               
  *          ===================================================================      
  *                        How to configure Interrupts using driver 
  *          ===================================================================      
  * 
  *            This section provide functions allowing to configure the NVIC interrupts (IRQ).
  *            The Cortex-M4 exceptions are managed by CMSIS functions.
  *
  *            1. Configure the NVIC Priority Grouping using NVIC_PriorityGroupConfig_mort()
  *                function according to the following table.
 
  *  The table below gives the allowed values of the pre-emption priority and subpriority according
  *  to the Priority Grouping configuration performed by NVIC_PriorityGroupConfig_mort function
  *    ==========================================================================================================================
  *      NVIC_PriorityGroup   | NVIC_IRQChannelPreemptionPriority | NVIC_IRQChannelSubPriority  |       Description
  *    ==========================================================================================================================
  *     NVIC_PriorityGroup_0_MORT  |                0                  |            0-15             | 0 bits for pre-emption priority
  *                           |                                   |                             | 4 bits for subpriority
  *    --------------------------------------------------------------------------------------------------------------------------
  *     NVIC_PriorityGroup_1_MORT  |                0-1                |            0-7              | 1 bits for pre-emption priority
  *                           |                                   |                             | 3 bits for subpriority
  *    --------------------------------------------------------------------------------------------------------------------------    
  *     NVIC_PriorityGroup_2_MORT  |                0-3                |            0-3              | 2 bits for pre-emption priority
  *                           |                                   |                             | 2 bits for subpriority
  *    --------------------------------------------------------------------------------------------------------------------------    
  *     NVIC_PriorityGroup_3_MORT  |                0-7                |            0-1              | 3 bits for pre-emption priority
  *                           |                                   |                             | 1 bits for subpriority
  *    --------------------------------------------------------------------------------------------------------------------------    
  *     NVIC_PriorityGroup_4_MORT  |                0-15               |            0                | 4 bits for pre-emption priority
  *                           |                                   |                             | 0 bits for subpriority                       
  *    ==========================================================================================================================     
  *
  *            2. Enable and Configure the priority of the selected IRQ Channels using NVIC_Init_mort()  
  *
  * @note  When the NVIC_PriorityGroup_0_MORT is selected, IRQ pre-emption is no more possible. 
  *        The pending IRQ priority will be managed only by the subpriority.
  *
  * @note  IRQ priority order (sorted by highest to lowest priority):
  *         - Lowest pre-emption priority
  *         - Lowest subpriority
  *         - Lowest hardware priority (IRQ number)
  *
  *  @endverbatim
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

/* Includes ------------------------------------------------------------------*/
#include "misc_mort.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  * @{
  */

/** @defgroup MISC 
  * @brief MISC driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define AIRCR_VECTKEY_MASK    ((uint32_t)0x05FA0000)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup MISC_Private_Functions
  * @{
  */

/**
  * @brief  Configures the priority grouping: pre-emption priority and subpriority.
  * @param  NVIC_PriorityGroup: specifies the priority grouping bits length. 
  *   This parameter can be one of the following values:
  *     @arg NVIC_PriorityGroup_0_MORT: 0 bits for pre-emption priority
  *                                4 bits for subpriority
  *     @arg NVIC_PriorityGroup_1_MORT: 1 bits for pre-emption priority
  *                                3 bits for subpriority
  *     @arg NVIC_PriorityGroup_2_MORT: 2 bits for pre-emption priority
  *                                2 bits for subpriority
  *     @arg NVIC_PriorityGroup_3_MORT: 3 bits for pre-emption priority
  *                                1 bits for subpriority
  *     @arg NVIC_PriorityGroup_4_MORT: 4 bits for pre-emption priority
  *                                0 bits for subpriority
  * @note   When the NVIC_PriorityGroup_0_MORT is selected, IRQ pre-emption is no more possible. 
  *         The pending IRQ priority will be managed only by the subpriority. 
  * @retval None
  */
void NVIC_PriorityGroupConfig_mort(uint32_t NVIC_PriorityGroup)
{
  /* Check the parameters */
  assert_param(IS_NVIC_PRIORITY_GROUP_MORT(NVIC_PriorityGroup));
  
  /* Set the PRIGROUP[10:8] bits according to NVIC_PriorityGroup value */
  SCB->AIRCR = AIRCR_VECTKEY_MASK | NVIC_PriorityGroup;
}

/**
  * @brief  Initializes the NVIC peripheral according to the specified
  *         parameters in the NVIC_InitStruct.
  * @note   To configure interrupts priority correctly, the NVIC_PriorityGroupConfig_mort()
  *         function should be called before. 
  * @param  NVIC_InitStruct: pointer to a NVIC_InitTypeDef_mort structure that contains
  *         the configuration information for the specified NVIC peripheral.
  * @retval None
  */
void NVIC_Init_mort(NVIC_InitTypeDef_mort* NVIC_InitStruct)
{
  uint8_t tmppriority = 0x00, tmppre = 0x00, tmpsub = 0x0F;
  
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NVIC_InitStruct->NVIC_IRQChannelCmd));
  assert_param(IS_NVIC_PREEMPTION_PRIORITY_MORT(NVIC_InitStruct->NVIC_IRQChannelPreemptionPriority));  
  assert_param(IS_NVIC_SUB_PRIORITY(NVIC_InitStruct->NVIC_IRQChannelSubPriority));
    
  if (NVIC_InitStruct->NVIC_IRQChannelCmd != DISABLE)
  {
    /* Compute the Corresponding IRQ Priority --------------------------------*/    
    tmppriority = (0x700 - ((SCB->AIRCR) & (uint32_t)0x700))>> 0x08;
    tmppre = (0x4 - tmppriority);
    tmpsub = tmpsub >> tmppriority;

    tmppriority = NVIC_InitStruct->NVIC_IRQChannelPreemptionPriority << tmppre;
    tmppriority |=  (uint8_t)(NVIC_InitStruct->NVIC_IRQChannelSubPriority & tmpsub);
        
    tmppriority = tmppriority << 0x04;
        
    NVIC->IP[NVIC_InitStruct->NVIC_IRQChannel] = tmppriority;
    
    /* Enable the Selected IRQ Channels --------------------------------------*/
    NVIC->ISER[NVIC_InitStruct->NVIC_IRQChannel >> 0x05] =
      (uint32_t)0x01 << (NVIC_InitStruct->NVIC_IRQChannel & (uint8_t)0x1F);
  }
  else
  {
    /* Disable the Selected IRQ Channels -------------------------------------*/
    NVIC->ICER[NVIC_InitStruct->NVIC_IRQChannel >> 0x05] =
      (uint32_t)0x01 << (NVIC_InitStruct->NVIC_IRQChannel & (uint8_t)0x1F);
  }
}

/**
  * @brief  Sets the vector table location and Offset.
  * @param  NVIC_VectTab: specifies if the vector table is in RAM or FLASH memory.
  *   This parameter can be one of the following values:
  *     @arg NVIC_VectTab_RAM_MORT: Vector Table in internal SRAM.
  *     @arg NVIC_VectTab_FLASH_MORT: Vector Table in internal FLASH.
  * @param  Offset: Vector Table base offset field. This value must be a multiple of 0x200.
  * @retval None
  */
void NVIC_SetVectorTable_mort(uint32_t NVIC_VectTab, uint32_t Offset)
{ 
  /* Check the parameters */
  assert_param(IS_NVIC_VECTTAB_MORT(NVIC_VectTab));
  assert_param(IS_NVIC_OFFSET_MORT(Offset));  
   
  SCB->VTOR = NVIC_VectTab | (Offset & (uint32_t)0x1FFFFF80);
}

/**
  * @brief  Selects the condition for the system to enter low power mode.
  * @param  LowPowerMode: Specifies the new mode for the system to enter low power mode.
  *   This parameter can be one of the following values:
  *     @arg NVIC_LP_SEVONPEND_MORT: Low Power SEV on Pend.
  *     @arg NVIC_LP_SLEEPDEEP_MORT: Low Power DEEPSLEEP request.
  *     @arg NVIC_LP_SLEEPONEXIT_MORT: Low Power Sleep on Exit.
  * @param  NewState: new state of LP condition. This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void NVIC_SystemLPConfig_mort(uint8_t LowPowerMode, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_NVIC_LP_MORT(LowPowerMode));
  assert_param(IS_FUNCTIONAL_STATE(NewState));  
  
  if (NewState != DISABLE)
  {
    SCB->SCR |= LowPowerMode;
  }
  else
  {
    SCB->SCR &= (uint32_t)(~(uint32_t)LowPowerMode);
  }
}

/**
  * @brief  Configures the SysTick clock source.
  * @param  SysTick_CLKSource: specifies the SysTick clock source.
  *   This parameter can be one of the following values:
  *     @arg SysTick_CLKSource_HCLK_Div8_MORT: AHB clock divided by 8 selected as SysTick clock source.
  *     @arg SysTick_CLKSource_HCLK_MORT: AHB clock selected as SysTick clock source.
  * @retval None
  */
void SysTick_CLKSourceConfig_mort(uint32_t SysTick_CLKSource)
{
  /* Check the parameters */
  assert_param(IS_SYSTICK_CLK_SOURCE_MORT(SysTick_CLKSource));
  if (SysTick_CLKSource == SysTick_CLKSource_HCLK_MORT)
  {
    SysTick->CTRL |= SysTick_CLKSource_HCLK_MORT;
  }
  else
  {
    SysTick->CTRL &= SysTick_CLKSource_HCLK_Div8_MORT;
  }
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/


