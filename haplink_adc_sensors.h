/**
  ******************************************************************************
  * @file    haplink_adc_sensors.h
  * @author  mortamar@andrew.cmu.edu
  * @version 3.0
  * @date    November-2017
  * @brief   ADC function prototypes, adapted for Keil studio
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAPLINK_ADC_SENSORS_H_
#define __HAPLINK_ADC_SENSORS_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_mort2.h"
#include "stm32f4xx_adc_mort.h"
#include "stm32f4xx_gpio_mort.h"
#include "stm32f4xx_dma_mort.h"
#include "stm32f4xx_rcc_mort.h"

//change if want more FSR's connected: (can handle up to 8)
#define NUMBER_ADC_CHANNELS  2

void initHaplinkAnalogSensors( void );
uint16_t getHaplinkAnalogSensor1Value( void );
uint16_t getHaplinkAnalogSensor2Value( void );
uint16_t getHaplinkAnalogSensor3Value( void );
uint16_t getHaplinkAnalogSensor4Value( void );
uint16_t getHaplinkAnalogSensor5Value( void );
uint16_t getHaplinkAnalogSensor6Value( void );
uint16_t getHaplinkAnalogSensor7Value( void );
uint16_t getHaplinkAnalogSensor8Value( void );

#ifdef __cplusplus
}
#endif

#endif /* __HAPLINK_ADC_SENSORS_H_ */
//EOF