#include "stm32f446ze_syscfg.h"


void SYSCFGEXTILineConfig(uint8_t EXTI_PortSourceGPIOx, uint8_t EXTI_PinSourcex)
{
  uint32_t tmp = 0x00;


  tmp = ((uint32_t)0x0F) << (0x04 * (EXTI_PinSourcex & (uint8_t)0x03));
  SYSCFG_REGISTER_BLOCK->EXTICR_R[EXTI_PinSourcex >> 0x02] &= ~tmp;
  SYSCFG_REGISTER_BLOCK->EXTICR_R[EXTI_PinSourcex >> 0x02] |= (((uint32_t)EXTI_PortSourceGPIOx) << (0x04 * (EXTI_PinSourcex & (uint8_t)0x03)));
}