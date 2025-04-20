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
// For external interrupts:
#define SYSCFG_BASE_ADDRESS ((uint32_t)(0x40013800))
#define SYSCFG_EXTERNAL_INTERRUPT_REGISTER_1 (SYSCFG_BASE_ADDRESS + 0x08)
#define SYSCFG_EXTERNAL_INTERRUPT_REGISTER_2 (SYSCFG_BASE_ADDRESS + 0x0C)
#define SYSCFG_EXTERNAL_INTERRUPT_REGISTER_3 (SYSCFG_BASE_ADDRESS + 0x10)
#define SYSCFG_EXTERNAL_INTERRUPT_REGISTER_4 (SYSCFG_BASE_ADDRESS + 0x14)

#define SYSTEM_CONTROL_BASE_ADDRESS (0xE000E000)
#define NVIC_BASE_ADDRESS (SYSTEM_CONTROL_BASE_ADDRESS + 0x100)
#define NVIC_INTERRUPT_SET_ENABLE_REGISTER_0_31 (NVIC_BASE_ADDRESS)
#define NVIC_INTERRUPT_SET_ENABLE_REGISTER_32_63 (NVIC_BASE_ADDRESS + 0x4)
#define NVIC_INTERRUPT_SET_ENABLE_REGISTER_64_95 (NVIC_BASE_ADDRESS + 0x8)
#define NVIC_INTERRUPT_CLEAR_ENABLE_REGISTER_0_31 (NVIC_BASE_ADDRESS + 0x80)
#define NVIC_INTERRUPT_CLEAR_ENABLE_REGISTER_32_63 (NVIC_INTERRUPT_CLEAR_ENABLE_REGISTER_0_31 + 0x4)
#define NVIC_INTERRUPT_CLEAR_ENABLE_REGISTER_64_95 (NVIC_INTERRUPT_CLEAR_ENABLE_REGISTER_0_31 + 0x8)
#define NVIC_INTERRUPT_SET_PENDING_REGISTER_0_31 (NVIC_BASE_ADDRESS + 0x100)
#define NVIC_INTERRUPT_SET_PENDING_REGISTER_32_63 (NVIC_INTERRUPT_SET_PENDING_REGISTER_0_31 + 0x4)
#define NVIC_INTERRUPT_SET_PENDING_REGISTER_64_95 (NVIC_INTERRUPT_SET_PENDING_REGISTER_0_31 + 0x8)
#define NVIC_INTERRUPT_CLEAR_PENDING_REGISTER_0_31 (NVIC_BASE_ADDRESS + 0x180)
#define NVIC_INTERRUPT_CLEAR_PENDING_REGISTER_32_63 (NVIC_INTERRUPT_CLEAR_PENDING_REGISTER_0_31 + 0x4)
#define NVIC_INTERRUPT_CLEAR_PENDING_REGISTER_64_95 (NVIC_INTERRUPT_CLEAR_PENDING_REGISTER_0_31 + 0x8)

#define EXTERNAL_INTERRUPT_CONTROLLER_BASE_ADDRESS ((uint32_t)(0x40013C00))
#define EXTERNAL_INTERRUPT_CONTROLLER_MASK_REGISTER (EXTERNAL_INTERRUPT_CONTROLLER_BASE_ADDRESS)
// flags for external interrupt controller mask register
#define EXTERNAL_INTERRUPT_CONTROLLER_MASK_REGISTER_EXTI6 ((uint32_t)0x40)
#define EXTERNAL_INTERRUPT_CONTROLLER_MASK_REGISTER_EXTI14 (((uint32_t)0x01) << 14)
#define EXTERNAL_INTERRUPT_CONTROLLER_MASK_REGISTER_EXTI15 (((uint32_t)0x01) << 15)
// Rising trigger selection register
#define EXTERNAL_INTERRUPT_CONTROLLER_RTSR (EXTERNAL_INTERRUPT_CONTROLLER_BASE_ADDRESS + 0x08)
#define EXTERNAL_INTERRUPT_CONTROLLER_RTSR_EXTI6 ((uint32_t)0x40)
#define EXTERNAL_INTERRUPT_CONTROLLER_RTSR_EXTI14 (((uint32_t)0x01) << 14)
#define EXTERNAL_INTERRUPT_CONTROLLER_RTSR_EXTI15 (((uint32_t)0x01) << 15)
// Falling trigger selection register
#define EXTERNAL_INTERRUPT_CONTROLLER_FTSR (EXTERNAL_INTERRUPT_CONTROLLER_BASE_ADDRESS + 0x0C)
#define EXTERNAL_INTERRUPT_CONTROLLER_FTSR_EXTI6 ((uint32_t)0x40)
#define EXTERNAL_INTERRUPT_CONTROLLER_FTSR_EXTI14 (((uint32_t)0x01) << 14)
#define EXTERNAL_INTERRUPT_CONTROLLER_FTSR_EXTI15 (((uint32_t)0x01) << 15)
// Interrupt pending register
#define EXTERNAL_INTERRUPT_CONTROLLER_PENDING_REGISTER (EXTERNAL_INTERRUPT_CONTROLLER_BASE_ADDRESS + 0x14)
#define EXTERNAL_INTERRUPT_CONTROLLER_PENDING_EXTI6 ((uint32_t)0x40)
#define EXTERNAL_INTERRUPT_CONTROLLER_PENDING_EXTI14 (((uint32_t)0x01) << 14)
#define EXTERNAL_INTERRUPT_CONTROLLER_PENDING_EXTI15 (((uint32_t)0x01) << 15)

/* Definitions----------------------------------------------------------------*/
#define M2_S1_PIN GPIOPin15 // PE15
#define M2_S2_PIN GPIOPin14 // PE14
#define M1_S1_PIN GPIOPin13 // PE13
#define M1_S2_PIN GPIOPin12 // PE12
#define M3_S1_PIN GPIOPin11 // PE11
#define M3_S2_PIN GPIOPin10 // PE10
#define M4_S1_PIN GPIOPin9  // PE9
#define M4_S2_PIN GPIOPin8  // PE8
#define M5_S1_PIN GPIOPin7  // PE7
#define M5_S2_PIN GPIOPin6  // PE6
#define M6_S1_PIN GPIOPin4  // PE4
#define M6_S2_PIN GPIOPin3  // PE3
#define M7_S1_PIN GPIOPin2  // PE2
#define M7_S2_PIN GPIOPin1  // PE1

#define M2_S1_PORT (GPIOTypeDef *)GPIOE_BASE_MORT // PE15
#define M2_S2_PORT (GPIOTypeDef *)GPIOE_BASE_MORT // PE14
#define M1_S1_PORT (GPIOTypeDef *)GPIOE_BASE_MORT // PE13
#define M1_S2_PORT (GPIOTypeDef *)GPIOE_BASE_MORT // PE12
#define M3_S1_PORT (GPIOTypeDef *)GPIOE_BASE_MORT // PE11
#define M3_S2_PORT (GPIOTypeDef *)GPIOE_BASE_MORT // PE10
#define M4_S1_PORT (GPIOTypeDef *)GPIOE_BASE_MORT // PE9
#define M4_S2_PORT (GPIOTypeDef *)GPIOE_BASE_MORT // PE8
#define M5_S1_PORT (GPIOTypeDef *)GPIOE_BASE_MORT // PE7
#define M5_S2_PORT (GPIOTypeDef *)GPIOE_BASE_MORT // PE6
#define M6_S1_PORT (GPIOTypeDef *)GPIOE_BASE_MORT // PE4
#define M6_S2_PORT (GPIOTypeDef *)GPIOE_BASE_MORT // PE3
#define M7_S1_PORT (GPIOTypeDef *)GPIOE_BASE_MORT // PE2
#define M7_S2_PORT (GPIOTypeDef *)GPIOE_BASE_MORT // PE1

/* Global variables -----------------------------------------------------------*/
uint8_t M1p_s1;
uint8_t M2p_s1;
uint8_t M3p_s1;
uint8_t M4p_s1;
uint8_t M5p_s1;
uint8_t M6p_s1;
uint8_t M7p_s1;

uint8_t M1_s1;
uint8_t M2_s1;
uint8_t M3_s1;
uint8_t M4_s1;
uint8_t M5_s1;
uint8_t M6_s1;
uint8_t M7_s1;

uint8_t M1p_s2;
uint8_t M2p_s2;
uint8_t M3p_s2;
uint8_t M4p_s2;
uint8_t M5p_s2;
uint8_t M6p_s2;
uint8_t M7p_s2;

uint8_t M1_s2;
uint8_t M2_s2;
uint8_t M3_s2;
uint8_t M4_s2;
uint8_t M5_s2;
uint8_t M6_s2;
uint8_t M7_s2;

int32_t CountsSensor1;
int32_t CountsSensor2;
int32_t CountsSensor3;
int32_t CountsSensor4;
int32_t CountsSensor5;
int32_t CountsSensor6;
int32_t CountsSensor7;

uint8_t CountsSensor1Changed;
uint8_t CountsSensor2Changed;
uint8_t CountsSensor3Changed;
uint8_t CountsSensor4Changed;
uint8_t CountsSensor5Changed;
uint8_t CountsSensor6Changed;
uint8_t CountsSensor7Changed;

GPIOInitTypeDef gpioinitstructure;
EXTIInitTypeDef extiinitstructure;
NVICInitTypeDef nvicinitstructure;

/* Function Definitions -----------------------------------------------------------*/

// All initializations for motor encoders
void initHapticHandEncodersMotors(void)
{
    uint32_t *reg_pointer_32;

    /* Enable GPIOE clock */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

    /* Enable SYSCFG clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

    gpioinitstructure.GPIO_Mode = GPIOModeIN;
    gpioinitstructure.GPIO_OType = GPIOOTypePP;
    gpioinitstructure.GPIO_Speed = GPIOHighSpeed;
    gpioinitstructure.GPIO_PuPd = GPIOPuPdNOPULL;

    gpioinitstructure.GPIO_Pin = M2_S1_PIN;
    GPIOInit(M2_S1_PORT, &gpioinitstructure);
    gpioinitstructure.GPIO_Pin = M2_S2_PIN;
    GPIOInit(M2_S2_PORT, &gpioinitstructure);
    gpioinitstructure.GPIO_Pin = M1_S1_PIN;
    GPIOInit(M1_S1_PORT, &gpioinitstructure);
    gpioinitstructure.GPIO_Pin = M1_S2_PIN;
    GPIOInit(M1_S2_PORT, &gpioinitstructure);
    gpioinitstructure.GPIO_Pin = M3_S1_PIN;
    GPIOInit(M3_S1_PORT, &gpioinitstructure);
    gpioinitstructure.GPIO_Pin = M3_S2_PIN;
    GPIOInit(M3_S2_PORT, &gpioinitstructure);
    gpioinitstructure.GPIO_Pin = M4_S1_PIN;
    GPIOInit(M4_S1_PORT, &gpioinitstructure);
    gpioinitstructure.GPIO_Pin = M4_S2_PIN;
    GPIOInit(M4_S2_PORT, &gpioinitstructure);
    gpioinitstructure.GPIO_Pin = M5_S1_PIN;
    GPIOInit(M5_S1_PORT, &gpioinitstructure);
    gpioinitstructure.GPIO_Pin = M5_S2_PIN;
    GPIOInit(M5_S2_PORT, &gpioinitstructure);
    gpioinitstructure.GPIO_Pin = M6_S1_PIN;
    GPIOInit(M6_S1_PORT, &gpioinitstructure);
    gpioinitstructure.GPIO_Pin = M6_S2_PIN;
    GPIOInit(M6_S2_PORT, &gpioinitstructure);
    gpioinitstructure.GPIO_Pin = M7_S1_PIN;
    GPIOInit(M7_S1_PORT, &gpioinitstructure);
    gpioinitstructure.GPIO_Pin = M7_S2_PIN;
    GPIOInit(M7_S2_PORT, &gpioinitstructure);

    M1p_s1 = GPIOReadInputDataBit(M1_S1_PORT, M1_S1_PIN);
    M1p_s2 = GPIOReadInputDataBit(M1_S2_PORT, M1_S2_PIN);
    M1_s1 = M1p_s1;
    M1_s2 = M1p_s2;

    M2p_s1 = GPIOReadInputDataBit(M2_S1_PORT, M2_S1_PIN);
    M2p_s2 = GPIOReadInputDataBit(M2_S2_PORT, M2_S2_PIN);
    M2_s1 = M2p_s1;
    M2_s2 = M2p_s2;

    M3p_s1 = GPIOReadInputDataBit(M3_S1_PORT, M3_S1_PIN);
    M3p_s2 = GPIOReadInputDataBit(M3_S2_PORT, M3_S2_PIN);
    M3_s1 = M3p_s1;
    M3_s2 = M3p_s2;

    M4p_s1 = GPIOReadInputDataBit(M4_S1_PORT, M4_S1_PIN);
    M4p_s2 = GPIOReadInputDataBit(M4_S2_PORT, M4_S2_PIN);
    M4_s1 = M4p_s1;
    M4_s2 = M4p_s2;

    M5p_s1 = GPIOReadInputDataBit(M5_S1_PORT, M5_S1_PIN);
    M5p_s2 = GPIOReadInputDataBit(M5_S2_PORT, M5_S2_PIN);
    M5_s1 = M5p_s1;
    M5_s2 = M5p_s2;

    M6p_s1 = GPIOReadInputDataBit(M6_S1_PORT, M6_S1_PIN);
    M6p_s2 = GPIOReadInputDataBit(M6_S2_PORT, M6_S2_PIN);
    M6_s1 = M6p_s1;
    M6_s2 = M6p_s2;

    M7p_s1 = GPIOReadInputDataBit(M7_S1_PORT, M7_S1_PIN);
    M7p_s2 = GPIOReadInputDataBit(M7_S2_PORT, M7_S2_PIN);
    M7_s1 = M7p_s1;
    M7_s2 = M7p_s2;

    CountsSensor1 = 0;
    CountsSensor2 = 0;
    CountsSensor3 = 0;
    CountsSensor4 = 0;
    CountsSensor5 = 0;
    CountsSensor6 = 0;
    CountsSensor7 = 0;

    CountsSensor1Changed = 0;
    CountsSensor2Changed = 0;
    CountsSensor3Changed = 0;
    CountsSensor4Changed = 0;
    CountsSensor5Changed = 0;
    CountsSensor6Changed = 0;
    CountsSensor7Changed = 0;

    /* Connect EXTI Line15 to PE15 pin */
    SYSCFGEXTILineConfig(EXTI_PORT_SOURCE_GPIOE, EXTI_PIN_SOURCE_15);
    /* Connect EXTI Line14 to PE14 pin */
    SYSCFGEXTILineConfig(EXTI_PORT_SOURCE_GPIOE, EXTI_PIN_SOURCE_14);
    /* Connect EXTI Line13 to PE13 pin */
    SYSCFGEXTILineConfig(EXTI_PORT_SOURCE_GPIOE, EXTI_PIN_SOURCE_13);
    /* Connect EXTI Line12 to PE12 pin */
    SYSCFGEXTILineConfig(EXTI_PORT_SOURCE_GPIOE, EXTI_PIN_SOURCE_12);
    /* Connect EXTI Line11 to PE11 pin */
    SYSCFGEXTILineConfig(EXTI_PORT_SOURCE_GPIOE, EXTI_PIN_SOURCE_11);
    /* Connect EXTI Line10 to PE10 pin */
    SYSCFGEXTILineConfig(EXTI_PORT_SOURCE_GPIOE, EXTI_PIN_SOURCE_10);
    /* Connect EXTI Line9 to PE9 pin */
    SYSCFGEXTILineConfig(EXTI_PORT_SOURCE_GPIOE, EXTI_PIN_SOURCE_9);
    /* Connect EXTI Line8 to PE8 pin */
    SYSCFGEXTILineConfig(EXTI_PORT_SOURCE_GPIOE, EXTI_PIN_SOURCE_8);
    /* Connect EXTI Line9 to PE7 pin */
    SYSCFGEXTILineConfig(EXTI_PORT_SOURCE_GPIOE, EXTI_PIN_SOURCE_7);
    /* Connect EXTI Line8 to PE6 pin */
    SYSCFGEXTILineConfig(EXTI_PORT_SOURCE_GPIOE, EXTI_PIN_SOURCE_6);
    /* Connect EXTI Line9 to PE4 pin */
    SYSCFGEXTILineConfig(EXTI_PORT_SOURCE_GPIOE, EXTI_PIN_SOURCE_4);
    /* Connect EXTI Line8 to PE3 pin */
    SYSCFGEXTILineConfig(EXTI_PORT_SOURCE_GPIOE, EXTI_PIN_SOURCE_3);
    /* Connect EXTI Line9 to PE2 pin */
    SYSCFGEXTILineConfig(EXTI_PORT_SOURCE_GPIOE, EXTI_PIN_SOURCE_2);
    /* Connect EXTI Line8 to PE1 pin */
    SYSCFGEXTILineConfig(EXTI_PORT_SOURCE_GPIOE, EXTI_PIN_SOURCE_1);

    // check that the register is good:
    // reg_pointer_32 = (uint32_t *)SYSCFG_EXTERNAL_INTERRUPT_REGISTER_4;
    // debugprintRegister(*reg_pointer_32);

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
    /* Configure EXTI Line9 */
    extiinitstructure.EXTILine = EXTI_Line9_MORT;
    EXTIInit(&extiinitstructure);
    /* Configure EXTI Line8 */
    extiinitstructure.EXTILine = EXTI_Line8_MORT;
    EXTIInit(&extiinitstructure);
    /* Configure EXTI Line7 */
    extiinitstructure.EXTILine = EXTI_Line7_MORT;
    EXTIInit(&extiinitstructure);
    /* Configure EXTI Line6 */
    extiinitstructure.EXTILine = EXTI_Line6_MORT;
    EXTIInit(&extiinitstructure);
    /* Configure EXTI Line4 */
    extiinitstructure.EXTILine = EXTI_Line4_MORT;
    EXTIInit(&extiinitstructure);
    /* Configure EXTI Line3 */
    extiinitstructure.EXTILine = EXTI_Line3_MORT;
    EXTIInit(&extiinitstructure);
    /* Configure EXTI Line2 */
    extiinitstructure.EXTILine = EXTI_Line2_MORT;
    EXTIInit(&extiinitstructure);
    /* Configure EXTI Line1 */
    extiinitstructure.EXTILine = EXTI_Line1_MORT;
    EXTIInit(&extiinitstructure);

    // check that the register is good:
    // reg_pointer_32 = (uint32_t *)EXTERNAL_INTERRUPT_CONTROLLER_MASK_REGISTER;
    // debugprintRegister(*reg_pointer_32);
    // reg_pointer_32 = (uint32_t *)EXTERNAL_INTERRUPT_CONTROLLER_RTSR;
    // debugprintRegister(*reg_pointer_32);
    // reg_pointer_32 = (uint32_t *)EXTERNAL_INTERRUPT_CONTROLLER_FTSR;
    // debugprintRegister(*reg_pointer_32);

    /* Enable and set EXTI15_10 Interrupt to the lowest priority */
    nvicinitstructure.NVICIRQChannel = EXTI15_10_IRQn;
    // nvicinitstructure.NVICIRQChannelPreemptionPriority = 0x0F;
    // nvicinitstructure.NVICIRQChannelSubPriority = 0x0F;
    nvicinitstructure.NVICIRQChannelCmd = ENABLE_MORT;
    NVICInit(&nvicinitstructure);

    /* Enable and set EXTI9_5 Interrupt to the lowest priority */
    nvicinitstructure.NVICIRQChannel = EXTI9_5_IRQn;
    // nvicinitstructure.NVICIRQChannelPreemptionPriority = 0x0F;
    // nvicinitstructure.NVICIRQChannelSubPriority = 0x0F;
    nvicinitstructure.NVICIRQChannelCmd = ENABLE_MORT;
    NVICInit(&nvicinitstructure);

    /* Enable and set EXTI4 Interrupt to the lowest priority */
    nvicinitstructure.NVICIRQChannel = EXTI4_IRQn;
    // nvicinitstructure.NVICIRQChannelPreemptionPriority = 0x0F;
    // nvicinitstructure.NVICIRQChannelSubPriority = 0x0F;
    nvicinitstructure.NVICIRQChannelCmd = ENABLE_MORT;
    NVICInit(&nvicinitstructure);

    /* Enable and set EXTI3 Interrupt to the lowest priority */
    nvicinitstructure.NVICIRQChannel = EXTI3_IRQn;
    // nvicinitstructure.NVICIRQChannelPreemptionPriority = 0x0F;
    // nvicinitstructure.NVICIRQChannelSubPriority = 0x0F;
    nvicinitstructure.NVICIRQChannelCmd = ENABLE_MORT;
    NVICInit(&nvicinitstructure);

    /* Enable and set EXTI2 Interrupt to the lowest priority */
    nvicinitstructure.NVICIRQChannel = EXTI2_IRQn;
    // nvicinitstructure.NVICIRQChannelPreemptionPriority = 0x0F;
    // nvicinitstructure.NVICIRQChannelSubPriority = 0x0F;
    nvicinitstructure.NVICIRQChannelCmd = ENABLE_MORT;
    NVICInit(&nvicinitstructure);

    /* Enable and set EXTI4 Interrupt to the lowest priority */
    nvicinitstructure.NVICIRQChannel = EXTI1_IRQn;
    // nvicinitstructure.NVICIRQChannelPreemptionPriority = 0x0F;
    // nvicinitstructure.NVICIRQChannelSubPriority = 0x0F;
    nvicinitstructure.NVICIRQChannelCmd = ENABLE_MORT;
    NVICInit(&nvicinitstructure);

    // reg_pointer_32 = (uint32_t *)NVIC_INTERRUPT_SET_ENABLE_REGISTER_32_63;
    // debugprintRegister(*reg_pointer_32);
}

/*******************************************************************************
 * @name   getCountsSensor1
 * @brief  Returns the number of counts on Motor1 encoder
 * @param  None.
 * @retval int32_t CountsSensor1: the number of ticks counted on the encoder
 */
int32_t getCountsSensor1(void)
{
    return CountsSensor1;
}
/*******************************************************************************
 * @name   getCountsSensor2
 * @brief  Returns the number of counts on Motor2 encoder
 * @param  None.
 * @retval int32_t CountsSensor2: the number of ticks counted on the encoder
 */
int32_t getCountsSensor2(void)
{
    return CountsSensor2;
}
/*******************************************************************************
 * @name   getCountsSensor3
 * @brief  Returns the number of counts on Motor3 encoder
 * @param  None.
 * @retval int32_t CountsSensor2: the number of ticks counted on the encoder
 */
int32_t getCountsSensor3(void)
{
    return CountsSensor3;
}

/*******************************************************************************
 * @name   getCountsSensor4
 * @brief  Returns the number of counts on Motor4 encoder
 * @param  None.
 * @retval int32_t CountsSensor4: the number of ticks counted on the encoder
 */
int32_t getCountsSensor4(void)
{
    return CountsSensor4;
}

/*******************************************************************************
 * @name   getCountsSensor5
 * @brief  Returns the number of counts on Motor5 encoder
 * @param  None.
 * @retval int32_t CountsSensor5: the number of ticks counted on the encoder
 */
int32_t getCountsSensor5(void)
{
    return CountsSensor5;
}

/*******************************************************************************
 * @name   getCountsSensor6
 * @brief  Returns the number of counts on Motor6 encoder
 * @param  None.
 * @retval int32_t CountsSensor6: the number of ticks counted on the encoder
 */
int32_t getCountsSensor6(void)
{
    return CountsSensor6;
}

/*******************************************************************************
 * @name   getCountsSensor7
 * @brief  Returns the number of counts on Motor7 encoder
 * @param  None.
 * @retval int32_t CountsSensor7: the number of ticks counted on the encoder
 */
int32_t getCountsSensor7(void)
{
    return CountsSensor7;
}

/* Interrupt Callbacks ------------------------------------------------------*/

/*#define M2_S1_PIN                 GPIO_Pin_15
#define M2_S2_PIN                 GPIO_Pin_14
#define M1_S1_PIN                 GPIO_Pin_13
#define M1_S2_PIN                 GPIO_Pin_12*/

void EXTI9_5_IRQHandler(void)
{
    // debugprint(9);
    if (EXTI_GetITStatus_mort(EXTI_Line9_MORT) != RESET) // motor 4 sensor 1
    {
        M4_s1 = (GPIOReadInputDataBit((GPIOTypeDef *)GPIOE_BASE_MORT, M4_S1_PIN));
        M4_s2 = (GPIOReadInputDataBit((GPIOTypeDef *)GPIOE_BASE_MORT, M4_S2_PIN));
        if (((M4p_s1 == M4p_s2) && (M4_s1 == (!M4_s2))) || ((M4_s1 == M4_s2) && (M4p_s1 == (!M4p_s2))))
        {
            CountsSensor4Changed = 1;
            if ((M4_s2 == M4p_s1) && (M4_s1 == (!M4p_s2)))
            {
                CountsSensor4 = CountsSensor4 + 1; // CL rotation
            }
            else
            {
                CountsSensor4 = CountsSensor4 - 1; // CCL rotation
            }
        }
        M4p_s1 = M4_s1;
        M4p_s2 = M4_s2;

        /* Clear the EXTI line 9 pending bit */
        EXTI_ClearITPendingBit_mort(EXTI_Line9_MORT);
    }
    else if (EXTI_GetITStatus_mort(EXTI_Line8_MORT) != RESET) // motor4 sensor 2
    {
        // debugprint(8);
        M4_s1 = (GPIOReadInputDataBit((GPIOTypeDef *)GPIOE_BASE_MORT, M4_S1_PIN));
        M4_s2 = (GPIOReadInputDataBit((GPIOTypeDef *)GPIOE_BASE_MORT, M4_S2_PIN));
        if (((M4p_s1 == M4p_s2) && (M4_s1 == (!M4_s2))) || ((M4_s1 == M4_s2) && (M4p_s1 == (!M4p_s2))))
        {
            CountsSensor4Changed = 1;
            if ((M4_s2 == M4p_s1) && (M4_s1 == (!M4p_s2)))
            {
                CountsSensor4 = CountsSensor4 + 1; // CL rotation
            }
            else
            {
                CountsSensor4 = CountsSensor4 - 1; // CCL rotation
            }
        }
        M4p_s1 = M4_s1;
        M4p_s2 = M4_s2;
        /* Clear the EXTI line 8 pending bit */
        EXTI_ClearITPendingBit_mort(EXTI_Line8_MORT);
    }
    else if (EXTI_GetITStatus_mort(EXTI_Line7_MORT) != RESET) // motor 5 sensor 1
    {
        // debugprint(7);
        M5_s1 = (GPIOReadInputDataBit((GPIOTypeDef *)GPIOE_BASE_MORT, M5_S1_PIN));
        M5_s2 = (GPIOReadInputDataBit((GPIOTypeDef *)GPIOE_BASE_MORT, M5_S2_PIN));
        if (((M5p_s1 == M5p_s2) && (M5_s1 == (!M5_s2))) || ((M5_s1 == M5_s2) && (M5p_s1 == (!M5p_s2))))
        {
            CountsSensor5Changed = 1;
            if ((M5_s2 == M5p_s1) && (M5_s1 == (!M5p_s2)))
            {
                CountsSensor5 = CountsSensor5 + 1; // CL rotation
            }
            else
            {
                CountsSensor5 = CountsSensor5 - 1; // CCL rotation
            }
        }
        M5p_s1 = M5_s1;
        M5p_s2 = M5_s2;

        /* Clear the EXTI line 7 pending bit */
        EXTI_ClearITPendingBit_mort(EXTI_Line7_MORT);
    }
    else if (EXTI_GetITStatus_mort(EXTI_Line6_MORT) != RESET) // motor5 sensor2
    {
        // debugprint(6);
        M5_s1 = (GPIOReadInputDataBit((GPIOTypeDef *)GPIOE_BASE_MORT, M5_S1_PIN));
        M5_s2 = (GPIOReadInputDataBit((GPIOTypeDef *)GPIOE_BASE_MORT, M5_S2_PIN));
        if (((M5p_s1 == M5p_s2) && (M5_s1 == (!M5_s2))) || ((M5_s1 == M5_s2) && (M5p_s1 == (!M5p_s2))))
        {
            CountsSensor5Changed = 1;
            if ((M5_s2 == M5p_s1) && (M5_s1 == (!M5p_s2)))
            {
                CountsSensor5 = CountsSensor5 + 1; // CL rotation
            }
            else
            {
                CountsSensor5 = CountsSensor5 - 1; // CCL rotation
            }
        }
        M5p_s1 = M5_s1;
        M5p_s2 = M5_s2;

        /* Clear the EXTI line 6 pending bit */
        EXTI_ClearITPendingBit_mort(EXTI_Line6_MORT);
    }
}

void EXTI4_IRQHandler(void)
{
    if (EXTI_GetITStatus_mort(EXTI_Line4_MORT) != RESET) // motor 6 sensor 1
    {
        // debugprint(4);
        M6_s1 = (GPIOReadInputDataBit((GPIOTypeDef *)GPIOE_BASE_MORT, M6_S1_PIN));
        M6_s2 = (GPIOReadInputDataBit((GPIOTypeDef *)GPIOE_BASE_MORT, M6_S2_PIN));
        if (((M6p_s1 == M6p_s2) && (M6_s1 == (!M6_s2))) || ((M6_s1 == M6_s2) && (M6p_s1 == (!M6p_s2))))
        {
            CountsSensor6Changed = 1;
            if ((M6_s2 == M6p_s1) && (M6_s1 == (!M6p_s2)))
            {
                CountsSensor6 = CountsSensor6 + 1; // CL rotation
            }
            else
            {
                CountsSensor6 = CountsSensor6 - 1; // CCL rotation
            }
        }
        M6p_s1 = M6_s1;
        M6p_s2 = M6_s2;

        EXTI_ClearITPendingBit_mort(EXTI_Line4_MORT);
    }
}
void EXTI3_IRQHandler(void) // motor 6 s2
{
    if (EXTI_GetITStatus_mort(EXTI_Line3_MORT) != RESET)
    {
        // debugprint(3);
        M6_s1 = (GPIOReadInputDataBit((GPIOTypeDef *)GPIOE_BASE_MORT, M6_S1_PIN));
        M6_s2 = (GPIOReadInputDataBit((GPIOTypeDef *)GPIOE_BASE_MORT, M6_S2_PIN));
        if (((M6p_s1 == M6p_s2) && (M6_s1 == (!M6_s2))) || ((M6_s1 == M6_s2) && (M6p_s1 == (!M6p_s2))))
        {
            CountsSensor6Changed = 1;
            if ((M6_s2 == M6p_s1) && (M6_s1 == (!M6p_s2)))
            {
                CountsSensor6 = CountsSensor6 + 1; // CL rotation
            }
            else
            {
                CountsSensor6 = CountsSensor6 - 1; // CCL rotation
            }
        }
        M6p_s1 = M6_s1;
        M6p_s2 = M6_s2;

        EXTI_ClearITPendingBit_mort(EXTI_Line3_MORT);
    }
}
void EXTI2_IRQHandler(void) // motor 7 s1
{
    if (EXTI_GetITStatus_mort(EXTI_Line2_MORT) != RESET)
    {
        // debugprint(2);
        M7_s1 = (GPIOReadInputDataBit((GPIOTypeDef *)GPIOE_BASE_MORT, M7_S1_PIN));
        M7_s2 = (GPIOReadInputDataBit((GPIOTypeDef *)GPIOE_BASE_MORT, M7_S2_PIN));
        if (((M7p_s1 == M7p_s2) && (M7_s1 == (!M7_s2))) || ((M7_s1 == M7_s2) && (M7p_s1 == (!M7p_s2))))
        {
            CountsSensor7Changed = 1;
            if ((M7_s2 == M7p_s1) && (M7_s1 == (!M7p_s2)))
            {
                CountsSensor7 = CountsSensor7 + 1; // CL rotation
            }
            else
            {
                CountsSensor7 = CountsSensor7 - 1; // CCL rotation
            }
        }
        M7p_s1 = M7_s1;
        M7p_s2 = M7_s2;

        EXTI_ClearITPendingBit_mort(EXTI_Line2_MORT);
    }
}
void EXTI1_IRQHandler(void) // motor 7 s2
{
    if (EXTI_GetITStatus_mort(EXTI_Line1_MORT) != RESET)
    {
        // debugprint(1);
        M7_s1 = (GPIOReadInputDataBit((GPIOTypeDef *)GPIOE_BASE_MORT, M7_S1_PIN));
        M7_s2 = (GPIOReadInputDataBit((GPIOTypeDef *)GPIOE_BASE_MORT, M7_S2_PIN));
        if (((M7p_s1 == M7p_s2) && (M7_s1 == (!M7_s2))) || ((M7_s1 == M7_s2) && (M7p_s1 == (!M7p_s2))))
        {
            CountsSensor7Changed = 1;
            if ((M7_s2 == M7p_s1) && (M7_s1 == (!M7p_s2)))
            {
                CountsSensor7 = CountsSensor7 + 1; // CL rotation
            }
            else
            {
                CountsSensor7 = CountsSensor7 - 1; // CCL rotation
            }
        }
        M7p_s1 = M7_s1;
        M7p_s2 = M7_s2;

        EXTI_ClearITPendingBit_mort(EXTI_Line1_MORT);
    }
}

void EXTI15_10_IRQHandler(void)
{
    // toggleLED1();
    // debugprint(0);
    if (EXTI_GetITStatus_mort(EXTI_Line13_MORT) != RESET) // motor 1  s1
    {
        M1_s1 = (GPIOReadInputDataBit((GPIOTypeDef *)GPIOE_BASE_MORT, M1_S1_PIN));
        M1_s2 = (GPIOReadInputDataBit((GPIOTypeDef *)GPIOE_BASE_MORT, M1_S2_PIN));
        if (((M1p_s1 == M1p_s2) && (M1_s1 == (!M1_s2))) || ((M1_s1 == M1_s2) && (M1p_s1 == (!M1p_s2))))
        {
            CountsSensor1Changed = 1;
            if ((M1_s2 == M1p_s1) && (M1_s1 == (!M1p_s2)))
            {
                CountsSensor1 = CountsSensor1 + 1; // CL rotation
            }
            else
            {
                CountsSensor1 = CountsSensor1 - 1; // CCL rotation
            }
        }
        M1p_s1 = M1_s1;
        M1p_s2 = M1_s2;

        /* Clear the EXTI line 13 pending bit */
        EXTI_ClearITPendingBit_mort(EXTI_Line13_MORT);
    }
    else if (EXTI_GetITStatus_mort(EXTI_Line12_MORT) != RESET) // motor1 s2
    {
        // debugprint(12);
        M1_s1 = (GPIOReadInputDataBit((GPIOTypeDef *)GPIOE_BASE_MORT, M1_S1_PIN));
        M1_s2 = (GPIOReadInputDataBit((GPIOTypeDef *)GPIOE_BASE_MORT, M1_S2_PIN));
        if (((M1p_s1 == M1p_s2) && (M1_s1 == (!M1_s2))) || ((M1_s1 == M1_s2) && (M1p_s1 == (!M1p_s2))))
        {
            CountsSensor1Changed = 1;
            if ((M1_s2 == M1p_s1) && (M1_s1 == (!M1p_s2)))
            {
                CountsSensor1 = CountsSensor1 + 1; // CL rotation
            }
            else
            {
                CountsSensor1 = CountsSensor1 - 1; // CCL rotation
            }
        }
        M1p_s1 = M1_s1;
        M1p_s2 = M1_s2;
        /* Clear the EXTI line 12 pending bit */
        EXTI_ClearITPendingBit_mort(EXTI_Line12_MORT);
    }
    else if (EXTI_GetITStatus_mort(EXTI_Line15_MORT) != RESET) // motor 2 sensor 1
    {
        // debugprint(15);
        M2_s1 = (GPIOReadInputDataBit((GPIOTypeDef *)GPIOE_BASE_MORT, M2_S1_PIN));
        M2_s2 = (GPIOReadInputDataBit((GPIOTypeDef *)GPIOE_BASE_MORT, M2_S2_PIN));
        if (((M2p_s1 == M2p_s2) && (M2_s1 == (!M2_s2))) || ((M2_s1 == M2_s2) && (M2p_s1 == (!M2p_s2))))
        {
            CountsSensor2Changed = 1;
            if ((M2_s2 == M2p_s1) && (M2_s1 == (!M2p_s2)))
            {
                CountsSensor2 = CountsSensor2 + 1; // CL rotation
            }
            else
            {
                CountsSensor2 = CountsSensor2 - 1; // CCL rotation
            }
        }
        M2p_s1 = M2_s1;
        M2p_s2 = M2_s2;

        /* Clear the EXTI line 15 pending bit */
        EXTI_ClearITPendingBit_mort(EXTI_Line15_MORT);
    }
    else if (EXTI_GetITStatus_mort(EXTI_Line14_MORT) != RESET) // motor2  sensor2
    {
        // debugprint(14);
        M2_s1 = (GPIOReadInputDataBit((GPIOTypeDef *)GPIOE_BASE_MORT, M2_S1_PIN));
        M2_s2 = (GPIOReadInputDataBit((GPIOTypeDef *)GPIOE_BASE_MORT, M2_S2_PIN));
        if (((M2p_s1 == M2p_s2) && (M2_s1 == (!M2_s2))) || ((M2_s1 == M2_s2) && (M2p_s1 == (!M2p_s2))))
        {
            CountsSensor2Changed = 1;
            if ((M2_s2 == M2p_s1) && (M2_s1 == (!M2p_s2)))
            {
                CountsSensor2 = CountsSensor2 + 1; // CL rotation
            }
            else
            {
                CountsSensor2 = CountsSensor2 - 1; // CCL rotation
            }
        }
        M2p_s1 = M2_s1;
        M2p_s2 = M2_s2;

        /* Clear the EXTI line 14 pending bit */
        EXTI_ClearITPendingBit_mort(EXTI_Line14_MORT);
    }
    else if (EXTI_GetITStatus_mort(EXTI_Line11_MORT) != RESET) // motor 3 sensor 1
    {
        // debugprint(11);
        M3_s1 = (GPIOReadInputDataBit((GPIOTypeDef *)GPIOE_BASE_MORT, M3_S1_PIN));
        M3_s2 = (GPIOReadInputDataBit((GPIOTypeDef *)GPIOE_BASE_MORT, M3_S2_PIN));
        if (((M3p_s1 == M3p_s2) && (M3_s1 == (!M3_s2))) || ((M3_s1 == M3_s2) && (M3p_s1 == (!M3p_s2))))
        {
            CountsSensor3Changed = 1;
            if ((M3_s2 == M3p_s1) && (M3_s1 == (!M3p_s2)))
            {
                CountsSensor3 = CountsSensor3 + 1; // CL rotation
            }
            else
            {
                CountsSensor3 = CountsSensor3 - 1; // CCL rotation
            }
        }
        M3p_s1 = M3_s1;
        M3p_s2 = M3_s2;

        /* Clear the EXTI line 11 pending bit */
        EXTI_ClearITPendingBit_mort(EXTI_Line11_MORT);
    }
    else if (EXTI_GetITStatus_mort(EXTI_Line10_MORT) != RESET) // motor3  sensor2
    {
        // debugprint(10);
        M3_s1 = (GPIOReadInputDataBit((GPIOTypeDef *)GPIOE_BASE_MORT, M3_S1_PIN));
        M3_s2 = (GPIOReadInputDataBit((GPIOTypeDef *)GPIOE_BASE_MORT, M3_S2_PIN));
        if (((M3p_s1 == M3p_s2) && (M3_s1 == (!M3_s2))) || ((M3_s1 == M3_s2) && (M3p_s1 == (!M3p_s2))))
        {
            CountsSensor3Changed = 1;
            if ((M3_s2 == M3p_s1) && (M3_s1 == (!M3p_s2)))
            {
                CountsSensor3 = CountsSensor3 + 1; // CL rotation
            }
            else
            {
                CountsSensor3 = CountsSensor3 - 1; // CCL rotation
            }
        }
        M3p_s1 = M3_s1;
        M3p_s2 = M3_s2;

        /* Clear the EXTI line 10 pending bit */
        EXTI_ClearITPendingBit_mort(EXTI_Line10_MORT);
    }
}
// EOF