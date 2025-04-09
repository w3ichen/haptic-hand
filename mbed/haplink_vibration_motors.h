/**
  ******************************************************************************
  * @file    haplink_vibration_motors.h
  * @author  mortamar@andrew.cmu.edu
  * @version 2.0
  * @date    January-2023
  * @brief   vibration motors function prototypes. Haplink's board supports 2 
  *          vibration motors.
  ******************************************************************************
  */
#ifndef __HAPLNK_VIBRATION_MOTORS_H_
#define __HAPLNK_VIBRATION_MOTORS_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/*Function definitions---------------------------------------------------------*/

void turnVibrationMotor1On( double amplitude );
void turnVibrationMotor1Off( void );
void turnVibrationMotor2On( double amplitude );
void turnVibrationMotor2Off( void );
double queryVibrationMotor1status( void );
double queryVibrationMotor2status( void );

#ifdef __cplusplus
}
#endif

#endif /*__HAPLNK_VIBRATION_MOTORS_H_ */