/**
  ******************************************************************************
  * @file    haplink_encoders.c
  * @author  mortamar@andrew.cmu.edu
  * @version 3.0
  * @date    January-2023
  * @brief   Controls Haplink's encoders channels for sensor reading.
  ******************************************************************************
  */

#include "haplink_encoders.h"
#include "stm32f446ze_syscfg.h"
#include "stm32f4xx_rcc_mort.h"
#include "stm32f446ze_gpio.h"
#include "stm32f446ze_exti.h"
#include "stm32f446ze_misc.h"
#include "nucleo_led.h"
#include "debug_mort.h"

/* Definitions for debugging -------------------------------------------------*/
//For external interrupts:
#define SYSCFG_BASE_ADDRESS                             ((uint32_t)(0x40013800))
#define SYSCFG_EXTERNAL_INTERRUPT_REGISTER_1            (SYSCFG_BASE_ADDRESS + 0x08)
#define SYSCFG_EXTERNAL_INTERRUPT_REGISTER_2            (SYSCFG_BASE_ADDRESS + 0x0C)
#define SYSCFG_EXTERNAL_INTERRUPT_REGISTER_3            (SYSCFG_BASE_ADDRESS + 0x10)
#define SYSCFG_EXTERNAL_INTERRUPT_REGISTER_4            (SYSCFG_BASE_ADDRESS + 0x14)

#define SYSTEM_CONTROL_BASE_ADDRESS                     (0xE000E000)
#define NVIC_BASE_ADDRESS                               (SYSTEM_CONTROL_BASE_ADDRESS + 0x100)
#define NVIC_INTERRUPT_SET_ENABLE_REGISTER_0_31         (NVIC_BASE_ADDRESS)
#define NVIC_INTERRUPT_SET_ENABLE_REGISTER_32_63        (NVIC_BASE_ADDRESS+0x4)
#define NVIC_INTERRUPT_SET_ENABLE_REGISTER_64_95        (NVIC_BASE_ADDRESS+0x8)
#define NVIC_INTERRUPT_CLEAR_ENABLE_REGISTER_0_31       (NVIC_BASE_ADDRESS + 0x80)
#define NVIC_INTERRUPT_CLEAR_ENABLE_REGISTER_32_63      (NVIC_INTERRUPT_CLEAR_ENABLE_REGISTER_0_31 + 0x4)
#define NVIC_INTERRUPT_CLEAR_ENABLE_REGISTER_64_95      (NVIC_INTERRUPT_CLEAR_ENABLE_REGISTER_0_31 + 0x8)
#define NVIC_INTERRUPT_SET_PENDING_REGISTER_0_31        (NVIC_BASE_ADDRESS + 0x100)
#define NVIC_INTERRUPT_SET_PENDING_REGISTER_32_63       (NVIC_INTERRUPT_SET_PENDING_REGISTER_0_31 + 0x4)
#define NVIC_INTERRUPT_SET_PENDING_REGISTER_64_95       (NVIC_INTERRUPT_SET_PENDING_REGISTER_0_31 + 0x8)
#define NVIC_INTERRUPT_CLEAR_PENDING_REGISTER_0_31      (NVIC_BASE_ADDRESS + 0x180)
#define NVIC_INTERRUPT_CLEAR_PENDING_REGISTER_32_63     (NVIC_INTERRUPT_CLEAR_PENDING_REGISTER_0_31 + 0x4)
#define NVIC_INTERRUPT_CLEAR_PENDING_REGISTER_64_95     (NVIC_INTERRUPT_CLEAR_PENDING_REGISTER_0_31 + 0x8)

#define EXTERNAL_INTERRUPT_CONTROLLER_BASE_ADDRESS      ((uint32_t)(0x40013C00))
#define EXTERNAL_INTERRUPT_CONTROLLER_MASK_REGISTER     (EXTERNAL_INTERRUPT_CONTROLLER_BASE_ADDRESS)
//flags for external interrupt controller mask register
#define EXTERNAL_INTERRUPT_CONTROLLER_MASK_REGISTER_EXTI6 ((uint32_t)0x40) 
#define EXTERNAL_INTERRUPT_CONTROLLER_MASK_REGISTER_EXTI14 (((uint32_t)0x01)<<14) 
#define EXTERNAL_INTERRUPT_CONTROLLER_MASK_REGISTER_EXTI15 (((uint32_t)0x01)<<15) 
//Rising trigger selection register
#define EXTERNAL_INTERRUPT_CONTROLLER_RTSR              (EXTERNAL_INTERRUPT_CONTROLLER_BASE_ADDRESS+0x08)
#define EXTERNAL_INTERRUPT_CONTROLLER_RTSR_EXTI6        ((uint32_t)0x40)
#define EXTERNAL_INTERRUPT_CONTROLLER_RTSR_EXTI14        (((uint32_t)0x01)<<14) 
#define EXTERNAL_INTERRUPT_CONTROLLER_RTSR_EXTI15        (((uint32_t)0x01)<<15) 
//Falling trigger selection register
#define EXTERNAL_INTERRUPT_CONTROLLER_FTSR              (EXTERNAL_INTERRUPT_CONTROLLER_BASE_ADDRESS+0x0C)
#define EXTERNAL_INTERRUPT_CONTROLLER_FTSR_EXTI6        ((uint32_t)0x40)
#define EXTERNAL_INTERRUPT_CONTROLLER_FTSR_EXTI14       (((uint32_t)0x01)<<14) 
#define EXTERNAL_INTERRUPT_CONTROLLER_FTSR_EXTI15       (((uint32_t)0x01)<<15) 
//Interrupt pending register
#define EXTERNAL_INTERRUPT_CONTROLLER_PENDING_REGISTER  (EXTERNAL_INTERRUPT_CONTROLLER_BASE_ADDRESS+0x14)
#define EXTERNAL_INTERRUPT_CONTROLLER_PENDING_EXTI6     ((uint32_t)0x40)
#define EXTERNAL_INTERRUPT_CONTROLLER_PENDING_EXTI14     (((uint32_t)0x01)<<14) 
#define EXTERNAL_INTERRUPT_CONTROLLER_PENDING_EXTI15     (((uint32_t)0x01)<<15)

/* Definitions----------------------------------------------------------------*/
#define M2_S1_PIN                 GPIOPin15
#define M2_S2_PIN                 GPIOPin14
#define M1_S1_PIN                 GPIOPin13
#define M1_S2_PIN                 GPIOPin12
#define M3_S1_PIN                 GPIOPin11
#define M3_S2_PIN                 GPIOPin10

/* Global variables -----------------------------------------------------------*/
uint8_t M1p_s1;
uint8_t M2p_s1;
uint8_t M3p_s1;
uint8_t M1_s1;
uint8_t M2_s1;
uint8_t M3_s1;
uint8_t M1p_s2;
uint8_t M2p_s2;
uint8_t M3p_s2;
uint8_t M1_s2;
uint8_t M2_s2;
uint8_t M3_s2;

int32_t CountsSensor1;
int32_t CountsSensor2;
int32_t CountsSensor3;

uint8_t CountsSensor1Changed;
uint8_t CountsSensor2Changed;
uint8_t CountsSensor3Changed;

GPIOInitTypeDef   gpioinitstructure;
EXTIInitTypeDef   extiinitstructure;
NVICInitTypeDef   nvicinitstructure;


/* Function Definitions -----------------------------------------------------------*/

void initHaplinkEncoders2Motors( void )
{
    uint32_t * reg_pointer_32;
   
    
    /* Enable GPIOE clock */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
    
    /* Enable SYSCFG clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

    gpioinitstructure.GPIO_Mode = GPIOModeIN;
    gpioinitstructure.GPIO_OType = GPIOOTypePP;
    gpioinitstructure.GPIO_Speed = GPIOHighSpeed;
    gpioinitstructure.GPIO_PuPd = GPIOPuPdNOPULL;
    gpioinitstructure.GPIO_Pin = GPIOPin12;
    GPIOInit((GPIOTypeDef *)GPIOE_BASE_MORT, &gpioinitstructure);
    gpioinitstructure.GPIO_Pin = GPIOPin13;
    GPIOInit((GPIOTypeDef *)GPIOE_BASE_MORT, &gpioinitstructure);
    gpioinitstructure.GPIO_Pin = GPIOPin14;
    GPIOInit((GPIOTypeDef *)GPIOE_BASE_MORT, &gpioinitstructure);
    gpioinitstructure.GPIO_Pin = GPIOPin15;
    GPIOInit((GPIOTypeDef *)GPIOE_BASE_MORT, &gpioinitstructure);

    M1p_s1 = GPIOReadInputDataBit( (GPIOTypeDef *)GPIOE_BASE_MORT, M1_S1_PIN);
    M1p_s2 = GPIOReadInputDataBit( (GPIOTypeDef *)GPIOE_BASE_MORT, M1_S2_PIN);
    M1_s1 = M1p_s1;
    //check that it is configured as an input correctly
    debugprintRegister(M1_s1);
    M1_s2 = M1p_s2;
    M2p_s1 = GPIOReadInputDataBit( (GPIOTypeDef *)GPIOE_BASE_MORT, M2_S1_PIN);
    M2p_s2 = GPIOReadInputDataBit( (GPIOTypeDef *)GPIOE_BASE_MORT, M2_S2_PIN);
    M2_s1 = M2p_s1;
    M2_s2 = M2p_s2;


    CountsSensor1 = 0;
    CountsSensor2 = 0;
    
    CountsSensor1Changed = 0;
    CountsSensor2Changed = 0;
    

    /* Connect EXTI Line15 to PE15 pin */
    SYSCFGEXTILineConfig(EXTI_PORT_SOURCE_GPIOE , EXTI_PIN_SOURCE_15 );
    /* Connect EXTI Line14 to PE14 pin */
    SYSCFGEXTILineConfig(EXTI_PORT_SOURCE_GPIOE , EXTI_PIN_SOURCE_14 );
    /* Connect EXTI Line13 to PE13 pin */
    SYSCFGEXTILineConfig(EXTI_PORT_SOURCE_GPIOE , EXTI_PIN_SOURCE_13 );
    /* Connect EXTI Line12 to PE12 pin */
    SYSCFGEXTILineConfig(EXTI_PORT_SOURCE_GPIOE , EXTI_PIN_SOURCE_12 );
    
    //check that the register is good:
    reg_pointer_32 = (uint32_t *)SYSCFG_EXTERNAL_INTERRUPT_REGISTER_4;
    debugprintRegister(*reg_pointer_32);

    /* Configure EXTI Line15 */
    extiinitstructure.EXTILine = EXTI_Line15_MORT;
    extiinitstructure.EXTIMode = EXTIModeInterrupt;
    extiinitstructure.EXTITrigger = EXTITriggerRisingFalling;
    extiinitstructure.EXTILineCmd = ENABLE_MORT;
    EXTIInit(&extiinitstructure);
    /* Configure EXTI Line14 */
    extiinitstructure.EXTILine = EXTI_Line14_MORT;
    EXTIInit(&extiinitstructure);
    /* Configure EXTI Line13 */
    extiinitstructure.EXTILine = EXTI_Line13_MORT;
    EXTIInit(&extiinitstructure);
    /* Configure EXTI Line12 */
    extiinitstructure.EXTILine = EXTI_Line12_MORT;
    EXTIInit(&extiinitstructure);
    
    //check that the register is good:
    reg_pointer_32 = (uint32_t *)EXTERNAL_INTERRUPT_CONTROLLER_MASK_REGISTER;
    debugprintRegister(*reg_pointer_32);
    reg_pointer_32 = (uint32_t *)EXTERNAL_INTERRUPT_CONTROLLER_RTSR;
    debugprintRegister(*reg_pointer_32);
    reg_pointer_32 = (uint32_t *)EXTERNAL_INTERRUPT_CONTROLLER_FTSR;
    debugprintRegister(*reg_pointer_32);

    /* Enable and set EXTI15_10 Interrupt to the lowest priority */
    nvicinitstructure.NVICIRQChannel = EXTI15_10_IRQn;
    nvicinitstructure.NVICIRQChannelPreemptionPriority = 0x0F;
    nvicinitstructure.NVICIRQChannelSubPriority = 0x0F;
    nvicinitstructure.NVICIRQChannelCmd = ENABLE_MORT;

    NVICInit(&nvicinitstructure);

    reg_pointer_32 = (uint32_t *)NVIC_INTERRUPT_SET_ENABLE_REGISTER_32_63;
    debugprintRegister(*reg_pointer_32);

}


void initHapticHandEncodersMotors( void )
{
    uint32_t * reg_pointer_32;
   
    
    /* Enable GPIOE clock */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
    
    /* Enable SYSCFG clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

    gpioinitstructure.GPIO_Mode = GPIOModeIN;
    gpioinitstructure.GPIO_OType = GPIOOTypePP;
    gpioinitstructure.GPIO_Speed = GPIOHighSpeed;
    gpioinitstructure.GPIO_PuPd = GPIOPuPdNOPULL;
    gpioinitstructure.GPIO_Pin = GPIOPin12;
    GPIOInit((GPIOTypeDef *)GPIOE_BASE_MORT, &gpioinitstructure);
    gpioinitstructure.GPIO_Pin = GPIOPin13;
    GPIOInit((GPIOTypeDef *)GPIOE_BASE_MORT, &gpioinitstructure);
    gpioinitstructure.GPIO_Pin = GPIOPin14;
    GPIOInit((GPIOTypeDef *)GPIOE_BASE_MORT, &gpioinitstructure);
    gpioinitstructure.GPIO_Pin = GPIOPin15;
    GPIOInit((GPIOTypeDef *)GPIOE_BASE_MORT, &gpioinitstructure);
    gpioinitstructure.GPIO_Pin = GPIOPin11;
    GPIOInit((GPIOTypeDef *)GPIOE_BASE_MORT, &gpioinitstructure);
    gpioinitstructure.GPIO_Pin = GPIOPin10;
    GPIOInit((GPIOTypeDef *)GPIOE_BASE_MORT, &gpioinitstructure);

    M1p_s1 = GPIOReadInputDataBit( (GPIOTypeDef *)GPIOE_BASE_MORT, M1_S1_PIN);
    M1p_s2 = GPIOReadInputDataBit( (GPIOTypeDef *)GPIOE_BASE_MORT, M1_S2_PIN);
    M1_s1 = M1p_s1;
    //check that it is configured as an input correctly
    debugprintRegister(M1_s1);
    M1_s2 = M1p_s2;
    M2p_s1 = GPIOReadInputDataBit( (GPIOTypeDef *)GPIOE_BASE_MORT, M2_S1_PIN);
    M2p_s2 = GPIOReadInputDataBit( (GPIOTypeDef *)GPIOE_BASE_MORT, M2_S2_PIN);
    M2_s1 = M2p_s1;
    M2_s2 = M2p_s2;

    M3p_s1 = GPIOReadInputDataBit( (GPIOTypeDef *)GPIOE_BASE_MORT, M3_S1_PIN);
    M3p_s2 = GPIOReadInputDataBit( (GPIOTypeDef *)GPIOE_BASE_MORT, M3_S2_PIN);
    M3_s1 = M3p_s1;
    M3_s2 = M3p_s2;

    CountsSensor1 = 0;
    CountsSensor2 = 0;
    CountsSensor3 = 0;
    CountsSensor1Changed = 0;
    CountsSensor2Changed = 0;
    CountsSensor3Changed = 0;

    /* Connect EXTI Line15 to PE15 pin */
    SYSCFGEXTILineConfig(EXTI_PORT_SOURCE_GPIOE , EXTI_PIN_SOURCE_15 );
    /* Connect EXTI Line14 to PE14 pin */
    SYSCFGEXTILineConfig(EXTI_PORT_SOURCE_GPIOE , EXTI_PIN_SOURCE_14 );
    /* Connect EXTI Line13 to PE13 pin */
    SYSCFGEXTILineConfig(EXTI_PORT_SOURCE_GPIOE , EXTI_PIN_SOURCE_13 );
    /* Connect EXTI Line12 to PE12 pin */
    SYSCFGEXTILineConfig(EXTI_PORT_SOURCE_GPIOE , EXTI_PIN_SOURCE_12 );
    /* Connect EXTI Line11 to PE11 pin */
    SYSCFGEXTILineConfig(EXTI_PORT_SOURCE_GPIOE , EXTI_PIN_SOURCE_11 );
    /* Connect EXTI Line10 to PE10 pin */
    SYSCFGEXTILineConfig(EXTI_PORT_SOURCE_GPIOE , EXTI_PIN_SOURCE_10 );
    //check that the register is good:
    reg_pointer_32 = (uint32_t *)SYSCFG_EXTERNAL_INTERRUPT_REGISTER_4;
    debugprintRegister(*reg_pointer_32);

    /* Configure EXTI Line15 */
    extiinitstructure.EXTILine = EXTI_Line15_MORT;
    extiinitstructure.EXTIMode = EXTIModeInterrupt;
    extiinitstructure.EXTITrigger = EXTITriggerRisingFalling;
    extiinitstructure.EXTILineCmd = ENABLE_MORT;
    EXTIInit(&extiinitstructure);
    /* Configure EXTI Line14 */
    extiinitstructure.EXTILine = EXTI_Line14_MORT;
    EXTIInit(&extiinitstructure);
    /* Configure EXTI Line13 */
    extiinitstructure.EXTILine = EXTI_Line13_MORT;
    EXTIInit(&extiinitstructure);
    /* Configure EXTI Line12 */
    extiinitstructure.EXTILine = EXTI_Line12_MORT;
    EXTIInit(&extiinitstructure);
    /* Configure EXTI Line11 */
    extiinitstructure.EXTILine = EXTI_Line11_MORT;
    EXTIInit(&extiinitstructure);
    /* Configure EXTI Line10 */
    extiinitstructure.EXTILine = EXTI_Line10_MORT;
    EXTIInit(&extiinitstructure);
    //check that the register is good:
    reg_pointer_32 = (uint32_t *)EXTERNAL_INTERRUPT_CONTROLLER_MASK_REGISTER;
    debugprintRegister(*reg_pointer_32);
    reg_pointer_32 = (uint32_t *)EXTERNAL_INTERRUPT_CONTROLLER_RTSR;
    debugprintRegister(*reg_pointer_32);
    reg_pointer_32 = (uint32_t *)EXTERNAL_INTERRUPT_CONTROLLER_FTSR;
    debugprintRegister(*reg_pointer_32);

    /* Enable and set EXTI15_10 Interrupt to the lowest priority */
    nvicinitstructure.NVICIRQChannel = EXTI15_10_IRQn;
    nvicinitstructure.NVICIRQChannelPreemptionPriority = 0x0F;
    nvicinitstructure.NVICIRQChannelSubPriority = 0x0F;
    nvicinitstructure.NVICIRQChannelCmd = ENABLE_MORT;

    NVICInit(&nvicinitstructure);

    reg_pointer_32 = (uint32_t *)NVIC_INTERRUPT_SET_ENABLE_REGISTER_32_63;
    debugprintRegister(*reg_pointer_32);

}

void initHaplinkEncoders3Motors( void )
{
    uint32_t * reg_pointer_32;
   
    
    /* Enable GPIOE clock */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
    
    /* Enable SYSCFG clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

    gpioinitstructure.GPIO_Mode = GPIOModeIN;
    gpioinitstructure.GPIO_OType = GPIOOTypePP;
    gpioinitstructure.GPIO_Speed = GPIOHighSpeed;
    gpioinitstructure.GPIO_PuPd = GPIOPuPdNOPULL;
    gpioinitstructure.GPIO_Pin = GPIOPin12;
    GPIOInit((GPIOTypeDef *)GPIOE_BASE_MORT, &gpioinitstructure);
    gpioinitstructure.GPIO_Pin = GPIOPin13;
    GPIOInit((GPIOTypeDef *)GPIOE_BASE_MORT, &gpioinitstructure);
    gpioinitstructure.GPIO_Pin = GPIOPin14;
    GPIOInit((GPIOTypeDef *)GPIOE_BASE_MORT, &gpioinitstructure);
    gpioinitstructure.GPIO_Pin = GPIOPin15;
    GPIOInit((GPIOTypeDef *)GPIOE_BASE_MORT, &gpioinitstructure);
    gpioinitstructure.GPIO_Pin = GPIOPin11;
    GPIOInit((GPIOTypeDef *)GPIOE_BASE_MORT, &gpioinitstructure);
    gpioinitstructure.GPIO_Pin = GPIOPin10;
    GPIOInit((GPIOTypeDef *)GPIOE_BASE_MORT, &gpioinitstructure);

    M1p_s1 = GPIOReadInputDataBit( (GPIOTypeDef *)GPIOE_BASE_MORT, M1_S1_PIN);
    M1p_s2 = GPIOReadInputDataBit( (GPIOTypeDef *)GPIOE_BASE_MORT, M1_S2_PIN);
    M1_s1 = M1p_s1;
    //check that it is configured as an input correctly
    debugprintRegister(M1_s1);
    M1_s2 = M1p_s2;
    M2p_s1 = GPIOReadInputDataBit( (GPIOTypeDef *)GPIOE_BASE_MORT, M2_S1_PIN);
    M2p_s2 = GPIOReadInputDataBit( (GPIOTypeDef *)GPIOE_BASE_MORT, M2_S2_PIN);
    M2_s1 = M2p_s1;
    M2_s2 = M2p_s2;

    M3p_s1 = GPIOReadInputDataBit( (GPIOTypeDef *)GPIOE_BASE_MORT, M3_S1_PIN);
    M3p_s2 = GPIOReadInputDataBit( (GPIOTypeDef *)GPIOE_BASE_MORT, M3_S2_PIN);
    M3_s1 = M3p_s1;
    M3_s2 = M3p_s2;

    CountsSensor1 = 0;
    CountsSensor2 = 0;
    CountsSensor3 = 0;
    CountsSensor1Changed = 0;
    CountsSensor2Changed = 0;
    CountsSensor3Changed = 0;

    /* Connect EXTI Line15 to PE15 pin */
    SYSCFGEXTILineConfig(EXTI_PORT_SOURCE_GPIOE , EXTI_PIN_SOURCE_15 );
    /* Connect EXTI Line14 to PE14 pin */
    SYSCFGEXTILineConfig(EXTI_PORT_SOURCE_GPIOE , EXTI_PIN_SOURCE_14 );
    /* Connect EXTI Line13 to PE13 pin */
    SYSCFGEXTILineConfig(EXTI_PORT_SOURCE_GPIOE , EXTI_PIN_SOURCE_13 );
    /* Connect EXTI Line12 to PE12 pin */
    SYSCFGEXTILineConfig(EXTI_PORT_SOURCE_GPIOE , EXTI_PIN_SOURCE_12 );
    /* Connect EXTI Line11 to PE11 pin */
    SYSCFGEXTILineConfig(EXTI_PORT_SOURCE_GPIOE , EXTI_PIN_SOURCE_11 );
    /* Connect EXTI Line10 to PE10 pin */
    SYSCFGEXTILineConfig(EXTI_PORT_SOURCE_GPIOE , EXTI_PIN_SOURCE_10 );
    //check that the register is good:
    reg_pointer_32 = (uint32_t *)SYSCFG_EXTERNAL_INTERRUPT_REGISTER_4;
    debugprintRegister(*reg_pointer_32);

    /* Configure EXTI Line15 */
    extiinitstructure.EXTILine = EXTI_Line15_MORT;
    extiinitstructure.EXTIMode = EXTIModeInterrupt;
    extiinitstructure.EXTITrigger = EXTITriggerRisingFalling;
    extiinitstructure.EXTILineCmd = ENABLE_MORT;
    EXTIInit(&extiinitstructure);
    /* Configure EXTI Line14 */
    extiinitstructure.EXTILine = EXTI_Line14_MORT;
    EXTIInit(&extiinitstructure);
    /* Configure EXTI Line13 */
    extiinitstructure.EXTILine = EXTI_Line13_MORT;
    EXTIInit(&extiinitstructure);
    /* Configure EXTI Line12 */
    extiinitstructure.EXTILine = EXTI_Line12_MORT;
    EXTIInit(&extiinitstructure);
    /* Configure EXTI Line11 */
    extiinitstructure.EXTILine = EXTI_Line11_MORT;
    EXTIInit(&extiinitstructure);
    /* Configure EXTI Line10 */
    extiinitstructure.EXTILine = EXTI_Line10_MORT;
    EXTIInit(&extiinitstructure);
    //check that the register is good:
    reg_pointer_32 = (uint32_t *)EXTERNAL_INTERRUPT_CONTROLLER_MASK_REGISTER;
    debugprintRegister(*reg_pointer_32);
    reg_pointer_32 = (uint32_t *)EXTERNAL_INTERRUPT_CONTROLLER_RTSR;
    debugprintRegister(*reg_pointer_32);
    reg_pointer_32 = (uint32_t *)EXTERNAL_INTERRUPT_CONTROLLER_FTSR;
    debugprintRegister(*reg_pointer_32);

    /* Enable and set EXTI15_10 Interrupt to the lowest priority */
    nvicinitstructure.NVICIRQChannel = EXTI15_10_IRQn;
    nvicinitstructure.NVICIRQChannelPreemptionPriority = 0x0F;
    nvicinitstructure.NVICIRQChannelSubPriority = 0x0F;
    nvicinitstructure.NVICIRQChannelCmd = ENABLE_MORT;

    NVICInit(&nvicinitstructure);

    reg_pointer_32 = (uint32_t *)NVIC_INTERRUPT_SET_ENABLE_REGISTER_32_63;
    debugprintRegister(*reg_pointer_32);

}


/*******************************************************************************
  * @name   getCountsSensor1
  * @brief  Returns the number of counts on Motor1 encoder
  * @param  None.
  * @retval int32_t CountsSensor1: the number of ticks counted on the encoder
  */
int32_t getCountsSensor1( void )
{
    return CountsSensor1;    
}
/*******************************************************************************
  * @name   getCountsSensor2
  * @brief  Returns the number of counts on Motor2 encoder
  * @param  None.
  * @retval int32_t CountsSensor2: the number of ticks counted on the encoder
  */
int32_t getCountsSensor2( void )
{
    return CountsSensor2;    
}
/*******************************************************************************
  * @name   getCountsSensor3
  * @brief  Returns the number of counts on Motor3 encoder
  * @param  None.
  * @retval int32_t CountsSensor2: the number of ticks counted on the encoder
  */
int32_t getCountsSensor3( void )
{
    return CountsSensor3;    
}

/* Interrupt Callbacks ------------------------------------------------------*/

/*#define M2_S1_PIN                 GPIO_Pin_15
#define M2_S2_PIN                 GPIO_Pin_14
#define M1_S1_PIN                 GPIO_Pin_13
#define M1_S2_PIN                 GPIO_Pin_12*/

void EXTI15_10_IRQHandler(void)
{
  toggleLED1();
  //debugprint(0);
  if(EXTI_GetITStatus_mort(EXTI_Line13_MORT) != RESET_MORT) // motor 1  s1
  {
      //debugprint(1);
    M1_s1 = (GPIOReadInputDataBit((GPIOTypeDef *)GPIOE_BASE_MORT, M1_S1_PIN));
    M1_s2 = (GPIOReadInputDataBit((GPIOTypeDef *)GPIOE_BASE_MORT, M1_S2_PIN));
    if (((M1p_s1 == M1p_s2)&&(M1_s1 == (!M1_s2)))||((M1_s1==M1_s2)&&(M1p_s1==(!M1p_s2))))
    {
        CountsSensor1Changed = 1;
        if ((M1_s2 == M1p_s1)&&(M1_s1==(!M1p_s2)))
        {
            CountsSensor1 = CountsSensor1 + 1; //CL rotation
            
        }
        else
        {
            CountsSensor1 = CountsSensor1 - 1; //CCL rotation 
        }
    }
    M1p_s1 = M1_s1;
    M1p_s2 = M1_s2;
    
    /* Clear the EXTI line 13 pending bit */
    EXTI_ClearITPendingBit_mort(EXTI_Line13_MORT);
  }
  else if(EXTI_GetITStatus_mort(EXTI_Line12_MORT) != RESET_MORT) // motor1 s2
  {
    M1_s1 = (GPIOReadInputDataBit((GPIOTypeDef *)GPIOE_BASE_MORT, M1_S1_PIN));
    M1_s2 = (GPIOReadInputDataBit(( GPIOTypeDef *)GPIOE_BASE_MORT, M1_S2_PIN));
    if (((M1p_s1 == M1p_s2)&&(M1_s1 == (!M1_s2)))||((M1_s1==M1_s2)&&(M1p_s1==(!M1p_s2))))
    {
        CountsSensor1Changed = 1;
        if ((M1_s2 == M1p_s1)&&(M1_s1==(!M1p_s2)))
        {
            CountsSensor1 = CountsSensor1 + 1; //CL rotation
        }
        else
        {
            CountsSensor1 = CountsSensor1 - 1; //CCL rotation 
        }
    }
    M1p_s1 = M1_s1;
    M1p_s2 = M1_s2;
    /* Clear the EXTI line 12 pending bit */
    EXTI_ClearITPendingBit_mort(EXTI_Line12_MORT);
  }
  else if(EXTI_GetITStatus_mort(EXTI_Line15_MORT) != RESET) // motor 2 sensor 1
  {
    M2_s1 = (GPIOReadInputDataBit((GPIOTypeDef *)GPIOE_BASE_MORT, M2_S1_PIN));
    M2_s2 = (GPIOReadInputDataBit((GPIOTypeDef *)GPIOE_BASE_MORT, M2_S2_PIN));
    if (((M2p_s1 == M2p_s2)&&(M2_s1 == (!M2_s2)))||((M2_s1==M2_s2)&&(M2p_s1==(!M2p_s2))))
    {
        CountsSensor2Changed = 1;
        if ((M2_s2 == M2p_s1)&&(M2_s1==(!M2p_s2)))
        {
            CountsSensor2 = CountsSensor2 + 1; //CL rotation
        }
        else
        {
            CountsSensor2 = CountsSensor2 - 1; //CCL rotation 
        }
    }
    M2p_s1 = M2_s1;
    M2p_s2 = M2_s2;
    
    /* Clear the EXTI line 15 pending bit */
    EXTI_ClearITPendingBit_mort(EXTI_Line15_MORT);
  }
  else if(EXTI_GetITStatus_mort(EXTI_Line14_MORT) != RESET) // motor2  sensor2
  {
    M2_s1 = (GPIOReadInputDataBit((GPIOTypeDef *)GPIOE_BASE_MORT, M2_S1_PIN));
    M2_s2 = (GPIOReadInputDataBit((GPIOTypeDef *)GPIOE_BASE_MORT, M2_S2_PIN));
    if (((M2p_s1 == M2p_s2)&&(M2_s1 == (!M2_s2)))||((M2_s1==M2_s2)&&(M2p_s1==(!M2p_s2))))
    {
        CountsSensor2Changed = 1;
        if ((M2_s2 == M2p_s1)&&(M2_s1==(!M2p_s2)))
        {
            CountsSensor2 = CountsSensor2 + 1; //CL rotation
        }
        else
        {
            CountsSensor2 = CountsSensor2 - 1; //CCL rotation 
        }
    }
    M2p_s1 = M2_s1;
    M2p_s2 = M2_s2;
    
    /* Clear the EXTI line 14 pending bit */
    EXTI_ClearITPendingBit_mort(EXTI_Line14_MORT);
  }
  else if(EXTI_GetITStatus_mort(EXTI_Line11_MORT) != RESET) // motor 3 sensor 1
  {
    M3_s1 = (GPIOReadInputDataBit((GPIOTypeDef *)GPIOE_BASE_MORT, M3_S1_PIN));
    M3_s2 = (GPIOReadInputDataBit((GPIOTypeDef *)GPIOE_BASE_MORT, M3_S2_PIN));
    if (((M3p_s1 == M3p_s2)&&(M3_s1 == (!M3_s2)))||((M3_s1==M3_s2)&&(M3p_s1==(!M3p_s2))))
    {
        CountsSensor3Changed = 1;
        if ((M3_s2 == M3p_s1)&&(M3_s1==(!M3p_s2)))
        {
            CountsSensor3 = CountsSensor3 + 1; //CL rotation
        }
        else
        {
            CountsSensor3 = CountsSensor3 - 1; //CCL rotation 
        }
    }
    M3p_s1 = M3_s1;
    M3p_s2 = M3_s2;
    
    /* Clear the EXTI line 11 pending bit */
    EXTI_ClearITPendingBit_mort(EXTI_Line11_MORT);
  }
  else if(EXTI_GetITStatus_mort(EXTI_Line10_MORT) != RESET) // motor3  sensor2
  {
    M3_s1 = (GPIOReadInputDataBit((GPIOTypeDef *)GPIOE_BASE_MORT, M3_S1_PIN));
    M3_s2 = (GPIOReadInputDataBit((GPIOTypeDef *)GPIOE_BASE_MORT, M3_S2_PIN));
    if (((M3p_s1 == M3p_s2)&&(M3_s1 == (!M3_s2)))||((M3_s1==M3_s2)&&(M3p_s1==(!M3p_s2))))
    {
        CountsSensor3Changed = 1;
        if ((M3_s2 == M3p_s1)&&(M3_s1==(!M3p_s2)))
        {
            CountsSensor3 = CountsSensor3 + 1; //CL rotation
        }
        else
        {
            CountsSensor3 = CountsSensor3 - 1; //CCL rotation 
        }
    }
    M3p_s1 = M3_s1;
    M3p_s2 = M3_s2;
    
    /* Clear the EXTI line 10 pending bit */
    EXTI_ClearITPendingBit_mort(EXTI_Line10_MORT);
  }
}
//EOF