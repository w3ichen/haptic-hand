#include "stm32f446ze_misc.h"

#define AIRCR_VECTKEY_MASK    ((uint32_t)0x05FA0000)

void NVICInit( NVICInitTypeDef* NVIC_InitStruct)
{
  uint8_t tmppriority = 0x00, tmppre = 0x00, tmpsub = 0x0F;
  

    
  if (NVIC_InitStruct->NVICIRQChannelCmd != DISABLE_MORT)
  {
    /* Compute the Corresponding IRQ Priority --------------------------------*/    
    tmppriority = (0x700 - ((SCB->AIRCR) & (uint32_t)0x700))>> 0x08;
    tmppre = (0x4 - tmppriority);
    tmpsub = tmpsub >> tmppriority;

    tmppriority = NVIC_InitStruct->NVICIRQChannelPreemptionPriority << tmppre;
    tmppriority |=  (uint8_t)(NVIC_InitStruct->NVICIRQChannelSubPriority & tmpsub);
        
    tmppriority = tmppriority << 0x04;
        
    NVIC->IP[NVIC_InitStruct->NVICIRQChannel] = tmppriority;
    
    /* Enable the Selected IRQ Channels --------------------------------------*/
    NVIC->ISER[NVIC_InitStruct->NVICIRQChannel >> 0x05] =
      (uint32_t)0x01 << (NVIC_InitStruct->NVICIRQChannel & (uint8_t)0x1F);
  }
  else
  {
    /* Disable the Selected IRQ Channels -------------------------------------*/
    NVIC->ICER[NVIC_InitStruct->NVICIRQChannel >> 0x05] = (uint32_t)0x01 << (NVIC_InitStruct->NVICIRQChannel & (uint8_t)0x1F);
  }
}