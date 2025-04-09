/**
  ******************************************************************************
  * @file    haplink_vibration_motors.cpp 
  * @author  mortamar@andrew.cmu.edu
  * @version 1.0
  * @date    Jan-2020
  * @brief   Functions to control the two vibration motors connected to Haplink.
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "haplink_motors.h"
#include "haplink_vibration_motors.h"

/* Global Variables-----------------------------------------------------------*/
double vibrationMotor1status = 0.0;
double vibrationMotor2status = 0.0;


/*******************************************************************************
  * @name   turnVibrationMotor1On
  * @brief  Turns the Vibration Motor 1 on with amplitude defined by amplitude
  * @param  double amplitude: should be a number between 0 and 1 that defines 
  *          the amplitude of the vibration waveform between 0 and 100%.
  * @retval None.
  */
void turnVibrationMotor1On( double amplitude )
{
    if (amplitude > 1.0)
    {
        amplitude = 1.0;
    }
    else if (amplitude < 0.0)
    {
        amplitude = 0.0;    
    }
    updateDutyCycle3( amplitude );
    vibrationMotor1status = amplitude;            
}
/*******************************************************************************
  * @name   turnVibrationMotor1Off
  * @brief  Turns the Vibration Motor 1 off 
  * @param  None.
  * @retval None.
  */
void turnVibrationMotor1Off( void )
{
    updateDutyCycle3(0);            
}
/*******************************************************************************
  * @name   turnVibrationMotor2On
  * @brief  Turns the Vibration Motor 2 on with amplitude defined by amplitude
  * @param  double amplitude: should be a number between 0 and 1 that defines 
  *          the amplitude of the vibration waveform between 0 and 100%.
  * @retval None.
  */
void turnVibrationMotor2On( double amplitude )
{
    if (amplitude > 1.0)
    {
        amplitude = 1.0;
    }
    else if (amplitude < 0.0)
    {
        amplitude = 0.0;    
    }
    updateDutyCycle4( amplitude );
    vibrationMotor2status = amplitude;          
}
/*******************************************************************************
  * @name   turnVibrationMotor2Off
  * @brief  Turns the Vibration Motor 2 off 
  * @param  None.
  * @retval None.
  */
void turnVibrationMotor2Off( void )
{
    updateDutyCycle4(0);            
}
/*******************************************************************************
  * @name   queryVibrationMotor1status
  * @brief  returns the current amplitude that the vibrationmotor is being 
  *         actuated at.
  * @param  None.
  * @retval double vibrationMotor1status: a number between 0 and 1 that 
  *          retpresents the amplitdue that the vibration motor 1 is vibrating at
  *          from 0 to 100%.
  */
double queryVibrationMotor1status( void )
{
    return vibrationMotor1status; 
}
/*******************************************************************************
  * @name   queryVibrationMotor2status
  * @brief  returns the current amplitude that the vibrationmotor is being 
  *         actuated at.
  * @param  None.
  * @retval double vibrationMotor2status: a number between 0 and 1 that 
  *          retpresents the amplitdue that the vibration motor 2 is vibrating at
  *          from 0 to 100%.
  */
double queryVibrationMotor2status( void )
{
    return vibrationMotor2status; 
}

//EOF