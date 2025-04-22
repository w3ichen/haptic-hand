#include "stm32f446ze_exti.h"

void EXTIInit(EXTIInitTypeDef* EXTI_InitStruct)
{
  uint32_t tmp = 0;

  tmp = (uint32_t)EXTI_BASE_MORT;
     
  if (EXTI_InitStruct->EXTILineCmd != DISABLE_MORT)
  {
    /* Clear EXTI_MORT line configuration */
    EXTI_MORT->IMR &= ~EXTI_InitStruct->EXTILine;
    EXTI_MORT->EMR &= ~EXTI_InitStruct->EXTILine;
    
    tmp += EXTI_InitStruct->EXTIMode;

    *(volatile uint32_t *) tmp |= EXTI_InitStruct->EXTILine;

    /* Clear Rising Falling edge configuration */
    EXTI_MORT->RTSR &= ~EXTI_InitStruct->EXTILine;
    EXTI_MORT->FTSR &= ~EXTI_InitStruct->EXTILine;

    /* Select the trigger for the selected external interrupts */
    if (EXTI_InitStruct->EXTITrigger == EXTITriggerRisingFalling)
    {
      /* Rising Falling edge */
      EXTI_MORT->RTSR |= EXTI_InitStruct->EXTILine;
      EXTI_MORT->FTSR |= EXTI_InitStruct->EXTILine;
    }
    else
    {
      tmp = (uint32_t)EXTI_BASE_MORT;
      tmp += EXTI_InitStruct->EXTITrigger;

      *(volatile uint32_t *) tmp |= EXTI_InitStruct->EXTILine;
    }
  }
  else
  {
    tmp += EXTI_InitStruct->EXTIMode;

    /* Disable the selected external lines */
    *(volatile uint32_t *) tmp &= ~EXTI_InitStruct->EXTILine;
  }
}

ITStatus_MORT EXTI_GetITStatus_mort(uint32_t EXTI_Line)
{
  FlagStatus_MORT bitstatus = RESET_MORT;
  
  if ((EXTI_MORT->PR & EXTI_Line) != (uint32_t)RESET_MORT)
  {
    bitstatus = SET_MORT;
  }
  else
  {
    bitstatus = RESET_MORT;
  }
  return bitstatus;
  
}

void EXTI_ClearITPendingBit_mort(uint32_t EXTI_Line)
{
  
  EXTI_MORT->PR = EXTI_Line;
}