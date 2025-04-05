/**
  ******************************************************************************
  * @file    haplink_fsr.h
  * @author  mortamar@andrew.cmu.edu
  * @version 1.0
  * @date    January-2020
  * @brief   force-sensitive resistors function prototypes. Haplink's board  
  *          supports 2 fsrs.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAPLINK_FSR_H_
#define __HAPLINK_FSR_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_mort2.h"


uint16_t queryFSR1value( void );
uint16_t queryFSR2value( void );

#ifdef __cplusplus
}
#endif

#endif //__HAPLINK_FSR_H_