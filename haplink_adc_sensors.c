/**
  ******************************************************************************
  * @file    haplink_adc_sensors.c
  * @author  melisao@stanford.edu
  * @version 2.0
  * @date    November-2017
  * @brief   Controls Haplink's ADC channels for sensor reading. Changed support
  *          from the magnetoresistive sensors which require separate channels
  *          to 8 channels of the same ADC intended for force sensor reading.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "haplink_adc_sensors.h"


/* Definitions----------------------------------------------------------------*/
#define ADCx                       ADC3_MORT
  #define ADC_CHANNEL5              ADC_Channel_9
  #define ADC_CHANNEL6              ADC_Channel_14
  #define ADC_CHANNEL3              ADC_Channel_15
  #define ADC_CHANNEL4              ADC_Channel_4
  #define ADC_CHANNEL2              ADC_Channel_5
  #define ADC_CHANNEL1              ADC_Channel_6
  #define ADC_CHANNEL7              ADC_Channel_7
  #define ADC_CHANNEL8              ADC_Channel_8
  
  #define ADCx_CLK                 RCC_APB2Periph_ADC3
  #define ADCx_CHANNEL_GPIO_CLK    RCC_AHB1Periph_GPIOF
  #define GPIO_PIN5                 GPIO_Pin_3
  #define GPIO_PIN6                 GPIO_Pin_4
  #define GPIO_PIN3                 GPIO_Pin_5
  #define GPIO_PIN4                 GPIO_Pin_6
  #define GPIO_PIN2                 GPIO_Pin_7
  #define GPIO_PIN1                 GPIO_Pin_8
  #define GPIO_PIN7                 GPIO_Pin_9
  #define GPIO_PIN8                 GPIO_Pin_10
  #define GPIO_PORT                GPIOF_MORT
  #define DMA_CHANNELx             DMA_Channel_2
  #define DMA_STREAMx              DMA2_Stream0_MORT
  #define ADCx_DR_ADDRESS          ((uint32_t)0x4001224C)
  
/* Global variables -----------------------------------------------------------*/
__IO uint16_t haplinkSensorValues[8] ;
__IO uint16_t uhADCxConvertedValue = 0;
__IO uint32_t uwADCxConvertedVoltage = 0;

/* Function Definitions ------------------------------------------------------*/

/*******************************************************************************
  * @name   initHaplinkAnalogSensors
  * @brief  Initializes 8 ADC channels to read analog input and store in the
            haplinkSensorValues buffer using DMA.
  * @param  None
  * @retval None
  */
void initHaplinkAnalogSensors( void )
{
   ADC_InitTypeDef_mort       ADC_InitStructure;
  ADC_CommonInitTypeDef_mort ADC_CommonInitStructure;
  DMA_InitTypeDef_mort       DMA_InitStructure;
  GPIO_InitTypeDef_mort      GPIO_InitStructure;

  /* Enable ADCx, DMA and GPIO clocks ****************************************/ 
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
  RCC_AHB1PeriphClockCmd(ADCx_CHANNEL_GPIO_CLK, ENABLE);  
  RCC_APB2PeriphClockCmd(ADCx_CLK, ENABLE);
  

  /* DMA2 Stream0 channel2 configuration **************************************/
  DMA_InitStructure.DMA_Channel = DMA_CHANNELx;  
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADCx_DR_ADDRESS;
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&haplinkSensorValues[0];//(uint32_t)&uhADCxConvertedValue;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  DMA_InitStructure.DMA_BufferSize = NUMBER_ADC_CHANNELS;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//DMA_MemoryInc_Disable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_Init_mort(DMA_STREAMx, &DMA_InitStructure);
  DMA_Cmd_mort(DMA_STREAMx, ENABLE);

  /* Configure ADC3 Channel pins as analog input ******************************/
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN1 | GPIO_PIN2 ;//| GPIO_PIN3 | GPIO_PIN4 | GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7 | GPIO_PIN8; //uncomment more if you need more ADC's
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init_mort(GPIO_PORT, &GPIO_InitStructure);

  /* ADC Common Init **********************************************************/
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
  ADC_CommonInit_mort(&ADC_CommonInitStructure);

  /* ADC3 Init ****************************************************************/
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;//DISABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfConversion = NUMBER_ADC_CHANNELS;
  ADC_Init_mort(ADCx, &ADC_InitStructure);

  /* ADC3 regular channel7 configuration **************************************/
  ADC_RegularChannelConfig_mort(ADCx, ADC_CHANNEL1, 1, ADC_SampleTime_3Cycles);
  ADC_RegularChannelConfig_mort(ADCx, ADC_CHANNEL2, 2, ADC_SampleTime_3Cycles);
  //ADC_RegularChannelConfig_mort(ADCx, ADC_CHANNEL3, 3, ADC_SampleTime_3Cycles);
  //ADC_RegularChannelConfig_mort(ADCx, ADC_CHANNEL4, 4, ADC_SampleTime_3Cycles);
  //ADC_RegularChannelConfig_mort(ADCx, ADC_CHANNEL5, 5, ADC_SampleTime_3Cycles);
  //ADC_RegularChannelConfig_mort(ADCx, ADC_CHANNEL6, 6, ADC_SampleTime_3Cycles);
  //ADC_RegularChannelConfig_mort(ADCx, ADC_CHANNEL7, 7, ADC_SampleTime_3Cycles);
  //ADC_RegularChannelConfig_mort(ADCx, ADC_CHANNEL8, 8, ADC_SampleTime_3Cycles);
  
 /* Enable DMA request after last transfer (Single-ADC mode) */
  ADC_DMARequestAfterLastTransferCmd_mort(ADCx, ENABLE);

  /* Enable ADC3 DMA */
  ADC_DMACmd_mort(ADCx, ENABLE);

  /* Enable ADC3 */
  ADC_Cmd_mort(ADCx, ENABLE); 
  
  ADC_SoftwareStartConv_mort(ADCx);
}

/*******************************************************************************
  * @name   getHaplinkAnalogSensor1Value
  * @brief  returns the first element of the haplinkSensorValues buffer
  * @param  None
  * @retval uint16_t haplinkSensorValues[0]
  */
uint16_t getHaplinkAnalogSensor1Value( void )
{
    return (haplinkSensorValues[0] & 0xFFF);    
}
/*******************************************************************************
  * @name   getHaplinkAnalogSensor2Value
  * @brief  returns the first element of the haplinkSensorValues buffer
  * @param  None
  * @retval uint16_t haplinkSensorValues[1]
  */
uint16_t getHaplinkAnalogSensor2Value( void )
{
    return (haplinkSensorValues[1] & 0xFFF);    
}
/*******************************************************************************
  * @name   getHaplinkAnalogSensor3Value
  * @brief  returns the first element of the haplinkSensorValues buffer
  * @param  None
  * @retval uint16_t haplinkSensorValues[2]
  */
uint16_t getHaplinkAnalogSensor3Value( void )
{
    return (haplinkSensorValues[2] & 0xFFF);    
}
/*******************************************************************************
  * @name   getHaplinkAnalogSensor4Value
  * @brief  returns the first element of the haplinkSensorValues buffer
  * @param  None
  * @retval uint16_t haplinkSensorValues[3]
  */
uint16_t getHaplinkAnalogSensor4Value( void )
{
    return (haplinkSensorValues[3] & 0xFFF);    
}
/*******************************************************************************
  * @name   getHaplinkAnalogSensor5Value
  * @brief  returns the first element of the haplinkSensorValues buffer
  * @param  None
  * @retval uint16_t haplinkSensorValues[4]
  */
uint16_t getHaplinkAnalogSensor5Value( void )
{
    return (haplinkSensorValues[4] & 0xFFF);    
}
/*******************************************************************************
  * @name   getHaplinkAnalogSensor6Value
  * @brief  returns the first element of the haplinkSensorValues buffer
  * @param  None
  * @retval uint16_t haplinkSensorValues[5]
  */
uint16_t getHaplinkAnalogSensor6Value( void )
{
    return (haplinkSensorValues[5] & 0xFFF);    
}
/*******************************************************************************
  * @name   getHaplinkAnalogSensor7Value
  * @brief  returns the first element of the haplinkSensorValues buffer
  * @param  None
  * @retval uint16_t haplinkSensorValues[6]
  */
uint16_t getHaplinkAnalogSensor7Value( void )
{
    return (haplinkSensorValues[6] & 0xFFF);    
}
/*******************************************************************************
  * @name   getHaplinkAnalogSensor8Value
  * @brief  returns the first element of the haplinkSensorValues buffer
  * @param  None
  * @retval uint16_t haplinkSensorValues[7]
  */
uint16_t getHaplinkAnalogSensor8Value( void )
{
    return (haplinkSensorValues[7] & 0xFFF);    
}
//EOF