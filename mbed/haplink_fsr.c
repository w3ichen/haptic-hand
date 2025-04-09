/**
  ******************************************************************************
  * @file    haplink_fsr.c 
  * @author  mortamar@andrew.cmu.edu
  * @version 1.0
  * @date    Jan-2020
  * @brief   Functions to read the two force-sensitive resistors connected 
  *          to Haplink.
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "haplink_adc_sensors.h"
#include "haplink_fsr.h"

/*******************************************************************************
  * @name   queryFSR1value
  * @brief  Returns the value of the readings from force-sensitive resistor 1
  * @param  None.
  * @retval uint16_t value of 12 bit FSR 1.
  */
uint16_t queryFSR1value( void )
{
    return getHaplinkAnalogSensor1Value( );
}
/*******************************************************************************
  * @name   queryFSR2value
  * @brief  Returns the value of the readings from force-sensitive resistor 2
  * @param  None.
  * @retval uint16_t value of 12 bit FSR 2.
  */
uint16_t queryFSR2value( void )
{
    return getHaplinkAnalogSensor2Value( );
}
//EOF