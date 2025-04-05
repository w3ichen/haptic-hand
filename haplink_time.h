/**
  ******************************************************************************
  * @file    haplink_time.h 
  * @author  mortamar@andrew.cmu.edu
  * @version 2.0
  * @date    Jan-2021
  * @brief   Contains function definitions to control timers that keep time since
  *          code started running.
  ******************************************************************************
  */
#ifndef _HAPLINK_TIME_H_
#define _HAPLINK_TIME_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"
#include "stm32f4xx_tim_mort.h"
#include "stm32f4xx_rcc_mort.h"
#include "misc_mort.h"

void initHaplinkTime( void );
double getTime_us( void );
double getTime_ms(void);


#ifdef __cplusplus
}
#endif

#endif 
//EOF