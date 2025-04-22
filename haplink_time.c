/**
  ******************************************************************************
  * @file    haplink_time.c 
  * @author  melisao@stanford.edu
  * @version 1.0
  * @date    November-2017
  * @brief   Keeps global time.
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/  
#include "haplink_time.h"
#include "haplink_virtual_environments.h"



/* Global variables ----------------------------------------------------------*/
__IO uint16_t CCR1_Val2 = 65535;//65535;//40961;

uint16_t PrescalerValue2 = 0;
uint16_t capture = 0;
uint32_t timeLow = 0;
uint16_t timeHigh = 0;
double timeResolution = 0.47; //in us


/* Function Definitions ------------------------------------------------------*/

/*******************************************************************************
  * @name   initHaplinkTime
  * @brief  Initializes Timer 2 to act as a global time keeper with a resolution
  *         of 0.011 us
  * @param  None.
  * @retval None.
  */
void initHaplinkTime( void )
{
  TIM_TimeBaseInitTypeDef_mort  TIM_TimeBaseStructure2;
  TIM_OCInitTypeDef_mort  TIM_OCInitStructure2;
  NVIC_InitTypeDef_mort NVIC_InitStructure;

  /* TIM2 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

  /* Enable the TIM2 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init_mort(&NVIC_InitStructure);
  
  /* Compute the prescaler value */
  PrescalerValue2 = 20;//(uint16_t) ((SystemCoreClock / 2) / 90000000) - 1;

  /* Time base configuration */
  TIM_TimeBaseStructure2.TIM_Period = 65535;//65535;
  TIM_TimeBaseStructure2.TIM_Prescaler = PrescalerValue2;
  TIM_TimeBaseStructure2.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure2.TIM_CounterMode = TIM_CounterMode_Up_MORT;

  TIM_TimeBaseInit_mort(TIM2_MORT, &TIM_TimeBaseStructure2);

  /* Prescaler configuration */
  TIM_PrescalerConfig_mort(TIM2_MORT, PrescalerValue2, TIM_PSCReloadMode_Immediate_MORT);

  /* Output Compare Timing Mode configuration: Channel1 */
  TIM_OCInitStructure2.TIM_OCMode = TIM_OCMode_Timing_MORT;
  TIM_OCInitStructure2.TIM_OutputState = TIM_OutputState_Enable_MORT;
  TIM_OCInitStructure2.TIM_Pulse = CCR1_Val2;
  TIM_OCInitStructure2.TIM_OCPolarity = TIM_OCPolarity_High_MORT;

  TIM_OC1Init_mort(TIM2_MORT, &TIM_OCInitStructure2);

  TIM_OC1PreloadConfig_mort(TIM2_MORT, TIM_OCPreload_Disable_MORT);
    

   
  /* TIM Interrupts enable */
  TIM_ITConfig_mort(TIM2_MORT, TIM_IT_CC1, ENABLE);

  /* TIM2 enable counter */
  TIM_Cmd_mort(TIM2_MORT, ENABLE);  
}

double getTime_us( void )
{
  double  timeUs = 0;
  timeUs = ((double)TIM_GetCounter_mort(TIM2_MORT))* timeResolution;
  timeUs = timeUs + timeHigh*30801.92;
  return timeUs;
}
double getTime_ms(void)
{
    double timeMs = 0;
    timeMs = getTime_us()/1000.0;
    return timeMs;
}

/* Interrupt callback --------------------------------------------------------*/
void TIM2_IRQHandler(void)
{
  if (TIM_GetITStatus_mort(TIM2_MORT, TIM_IT_CC1) != RESET)
  {
    TIM_ClearITPendingBit_mort(TIM2_MORT, TIM_IT_CC1);

    /* LED1 toggling with frequency = 32.7 Hz */
    //blinkLED();
    timeLow = TIM_GetCapture1_mort(TIM2_MORT);
    TIM_SetCompare1_mort(TIM2_MORT, capture + CCR1_Val2);
    TIM_SetCompare1_mort(TIM2_MORT, CCR1_Val2);
    //timeLow = TIM_GetCounter_mort(TIM2_MORT);
    timeHigh = timeHigh+1;
  }
}
//EOF