/**
  ******************************************************************************
  * @file    haplink_motors.c
  * @author  mortamar@andrew.cmu.edu
  * @version 1.0
  * @date    January-2023
  * @brief   Control's haplink's motors. By default Haplink has two motors that are connected with directionality
  meant for DC motors (Motors 1 and 2) and two vibration motors (Motors 3 and 4). The code gives you the option
  of also using Motor 3 as a DC motor. You have to be careful to remove the second motor driver from Haplink's
  board then and connect it externally.
  ******************************************************************************
  */
/* Pin Connections:***********************************************************
    | HARDWARE       | PIN # | RESOURCE   |
    |----------------|-------|------------|
    | Motor 1 PWM    | PC6   | TIM3_CH1   |
    | Motor 1 Dir 1  | PC11  | Output     |
    | Motor 1 Dir 2  | PC10  | Output     |
    | Motor 1 Enc 1  | PE13  | EXTI_15    |
    | Motor 1 Enc 2  | PE12  | EXTI_14    |
    | Motor 2 PWM    | PC7   | TIM3_CH2   |
    | Motor 2 Dir 1  | PC12  | Output     |
    | Motor 2 Dir 2  | PD2   | Output     |
    | Motor 2 Enc 1  | PE15  | EXTI_13    |
    | Motor 2 Enc 2  | PE14  | EXTI_12    |
    | Motor 3 PWM    | PC8   | TIM3_CH3   |
    | Motor 3 Dir1   | PD0   | Output     |
    | Motor 3 Dir 2  | PD1   | Output     |
    | Motor 3 Enc1   | PE11  | EXTI_11.   |
    | Motor 3 Enc 2  | PE10  | EXTI_10.   |
    | Motor 4 PWM    | PC9   | TIM3_CH4   |
    | Motor 4 Dir 1  | PD3   | Output     |
    | Motor 4 Dir 2  | PD4   | Output     |
    | Motor 4 Enc 1  | PE9   | EXTI_9     |
    | Motor 4 Enc 2  | PE8   | EXTI_8     |
    | Motor 5 PWM    | PD12  | TIM4_CH1   |
    | Motor 5 Dir 1  | PG2   | Output     |
    | Motor 5 Dir 2  | PG3   | Output     |
    | Motor 5 Enc 1  | PE7   | EXTI_7     |
    | Motor 5 Enc 2  | PE6   | EXTI_6     |
    | Motor 6 PWM    | PD13  | TIM4_CH2   |
    | Motor 6 Dir 1  | PG4   | Output     |
    | Motor 6 Dir 2  | PG5   | Output     |
    | Motor 6 Enc 1  | PE4   | EXTI_4     |
    | Motor 6 Enc 2  | PE3   | EXTI_3     |
    | Motor 7 PWM    | PD14  | TIM4_CH3   |
    | Motor 7 Dir 1  | PG8   | Output     |
    | Motor 7 Dir 2  | PG9   | Output     |
    | Motor 7 Enc 1  | PE2   | EXTI_2     |
    | Motor 7 Enc 2  | PE1   | EXTI_1     |
    |----------------|-------|------------|
  ******************************************************************************
  */

#include "haplink_motors.h"
#include "stm32f4xx_rcc_mort.h"
#include "stm32f446ze_gpio.h"
#include "stm32f4xx_tim_mort.h"

// PWM Pins
#define PWM1_PIN GPIOPin6  // PC6
#define PWM2_PIN GPIOPin7  // PC7
#define PWM3_PIN GPIOPin8  // PC8
#define PWM4_PIN GPIOPin9  // PC9
#define PWM5_PIN GPIOPin12 // PD12
#define PWM6_PIN GPIOPin13 // PD13
#define PWM7_PIN GPIOPin14 // PD14

#define PWM1_PINSOURCE GPIOPinSource6  // PC6
#define PWM2_PINSOURCE GPIOPinSource7  // PC7
#define PWM3_PINSOURCE GPIOPinSource8  // PC8
#define PWM4_PINSOURCE GPIOPinSource9  // PC9
#define PWM5_PINSOURCE GPIOPinSource12 // PD12
#define PWM6_PINSOURCE GPIOPinSource13 // PD13
#define PWM7_PINSOURCE GPIOPinSource14 // PD14

// PWM Ports
#define PWM1_PORT ((GPIOTypeDef *)GPIOC_BASE_MORT)
#define PWM2_PORT ((GPIOTypeDef *)GPIOC_BASE_MORT)
#define PWM3_PORT ((GPIOTypeDef *)GPIOC_BASE_MORT)
#define PWM4_PORT ((GPIOTypeDef *)GPIOC_BASE_MORT)
#define PWM5_PORT ((GPIOTypeDef *)GPIOD_BASE_MORT)
#define PWM6_PORT ((GPIOTypeDef *)GPIOD_BASE_MORT)
#define PWM7_PORT ((GPIOTypeDef *)GPIOD_BASE_MORT)

// Direction Pins
#define PWM11_PIN GPIOPin11 // PC11
#define PWM12_PIN GPIOPin10 // PC10
#define PWM21_PIN GPIOPin12 // PC12
#define PWM22_PIN GPIOPin2  // PD2
#define PWM31_PIN GPIOPin0  // PD0
#define PWM32_PIN GPIOPin1  // PD1
#define PWM41_PIN GPIOPin3  // PD3
#define PWM42_PIN GPIOPin4  // PD4
#define PWM51_PIN GPIOPin2  // PG2
#define PWM52_PIN GPIOPin3  // PG3
#define PWM61_PIN GPIOPin4  // PG4
#define PWM62_PIN GPIOPin5  // PG5
#define PWM71_PIN GPIOPin8  // PG8
#define PWM72_PIN GPIOPin9  // PG9

// Direction Ports
#define PWM11_PORT ((GPIOTypeDef *)GPIOC_BASE_MORT)
#define PWM12_PORT ((GPIOTypeDef *)GPIOC_BASE_MORT)
#define PWM21_PORT ((GPIOTypeDef *)GPIOC_BASE_MORT)
#define PWM22_PORT ((GPIOTypeDef *)GPIOD_BASE_MORT)
#define PWM31_PORT ((GPIOTypeDef *)GPIOD_BASE_MORT)
#define PWM32_PORT ((GPIOTypeDef *)GPIOD_BASE_MORT)
#define PWM41_PORT ((GPIOTypeDef *)GPIOD_BASE_MORT)
#define PWM42_PORT ((GPIOTypeDef *)GPIOD_BASE_MORT)
#define PWM51_PORT ((GPIOTypeDef *)GPIOG_BASE_MORT)
#define PWM52_PORT ((GPIOTypeDef *)GPIOG_BASE_MORT)
#define PWM61_PORT ((GPIOTypeDef *)GPIOG_BASE_MORT)
#define PWM62_PORT ((GPIOTypeDef *)GPIOG_BASE_MORT)
#define PWM71_PORT ((GPIOTypeDef *)GPIOG_BASE_MORT)
#define PWM72_PORT ((GPIOTypeDef *)GPIOG_BASE_MORT)

GPIOInitTypeDef gpiomotorsinitstructure;
TIM_TimeBaseInitTypeDef_mort TIM_TimeBaseStructure;
TIM_OCInitTypeDef_mort TIM_OCInitStructure;

// 1 Capture-Compare Register per timer channel - renamed to be timer-specific
uint16_t TIM3_CCR1_Val = 0;
uint16_t TIM3_CCR2_Val = 0;
uint16_t TIM3_CCR3_Val = 0;
uint16_t TIM3_CCR4_Val = 0;
uint16_t TIM4_CCR1_Val = 0;
uint16_t TIM4_CCR2_Val = 0;
uint16_t TIM4_CCR3_Val = 0;

double dutyPrint1 = 0;
double dutyPrint2 = 0;
double dutyPrint3 = 0;
double dutyPrint4 = 0;
double dutyPrint5 = 0;
double dutyPrint6 = 0;
double dutyPrint7 = 0;

void initMotorsGpio(void)
{
    /* First the pins connected to PWM*/
    // Start clocks for ports in use
    /* GPIOC clock enable */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);

    // Pins for timer 3, motors 1-4
    gpiomotorsinitstructure.GPIO_Mode = GPIOModeAF;
    gpiomotorsinitstructure.GPIO_OType = GPIOOTypePP;
    gpiomotorsinitstructure.GPIO_Speed = GPIOHighSpeed;
    gpiomotorsinitstructure.GPIO_PuPd = GPIOPuPdUP;
    gpiomotorsinitstructure.GPIO_Pin = PWM1_PIN;
    GPIOInit(PWM1_PORT, &gpiomotorsinitstructure); // PWM1
    gpiomotorsinitstructure.GPIO_Pin = PWM2_PIN;
    GPIOInit(PWM2_PORT, &gpiomotorsinitstructure); // PWM2
    gpiomotorsinitstructure.GPIO_Pin = PWM3_PIN;
    GPIOInit(PWM3_PORT, &gpiomotorsinitstructure); // PWM3
    gpiomotorsinitstructure.GPIO_Pin = PWM4_PIN;
    GPIOInit(PWM4_PORT, &gpiomotorsinitstructure); // PWM4

    /* Connect TIM3 pins to AF2 */
    GPIOPinAFConfig(PWM1_PORT, PWM1_PINSOURCE, GPIO_AF_TIM3);
    GPIOPinAFConfig(PWM2_PORT, PWM2_PINSOURCE, GPIO_AF_TIM3);
    GPIOPinAFConfig(PWM3_PORT, PWM3_PINSOURCE, GPIO_AF_TIM3);
    GPIOPinAFConfig(PWM4_PORT, PWM4_PINSOURCE, GPIO_AF_TIM3);

    // Pins for Timer 4 Motors 5-7
    gpiomotorsinitstructure.GPIO_Pin = PWM5_PIN;
    GPIOInit(PWM5_PORT, &gpiomotorsinitstructure); // PWM1
    gpiomotorsinitstructure.GPIO_Pin = PWM6_PIN;
    GPIOInit(PWM6_PORT, &gpiomotorsinitstructure); // PWM2
    gpiomotorsinitstructure.GPIO_Pin = PWM7_PIN;
    GPIOInit(PWM7_PORT, &gpiomotorsinitstructure); // PWM3

    /* Connect TIM4 pins to AF2 */
    GPIOPinAFConfig(PWM5_PORT, PWM5_PINSOURCE, GPIO_AF_TIM4);
    GPIOPinAFConfig(PWM6_PORT, PWM6_PINSOURCE, GPIO_AF_TIM4);
    GPIOPinAFConfig(PWM7_PORT, PWM7_PINSOURCE, GPIO_AF_TIM4);

    /*Then the pins used for direction*/

    gpiomotorsinitstructure.GPIO_Mode = GPIOModeOUT;
    gpiomotorsinitstructure.GPIO_OType = GPIOOTypePP;
    gpiomotorsinitstructure.GPIO_Speed = GPIOHighSpeed;
    gpiomotorsinitstructure.GPIO_PuPd = GPIOPuPdNOPULL;

    gpiomotorsinitstructure.GPIO_Pin = PWM11_PIN;
    GPIOInit(PWM11_PORT, &gpiomotorsinitstructure);
    gpiomotorsinitstructure.GPIO_Pin = PWM12_PIN;
    GPIOInit(PWM12_PORT, &gpiomotorsinitstructure);
    gpiomotorsinitstructure.GPIO_Pin = PWM21_PIN;
    GPIOInit(PWM21_PORT, &gpiomotorsinitstructure);
    gpiomotorsinitstructure.GPIO_Pin = PWM22_PIN;
    GPIOInit(PWM22_PORT, &gpiomotorsinitstructure);
    gpiomotorsinitstructure.GPIO_Pin = PWM31_PIN;
    GPIOInit(PWM31_PORT, &gpiomotorsinitstructure);
    gpiomotorsinitstructure.GPIO_Pin = PWM32_PIN;
    GPIOInit(PWM32_PORT, &gpiomotorsinitstructure);
    gpiomotorsinitstructure.GPIO_Pin = PWM41_PIN;
    GPIOInit(PWM41_PORT, &gpiomotorsinitstructure);
    gpiomotorsinitstructure.GPIO_Pin = PWM42_PIN;
    GPIOInit(PWM42_PORT, &gpiomotorsinitstructure);
    gpiomotorsinitstructure.GPIO_Pin = PWM51_PIN;
    GPIOInit(PWM51_PORT, &gpiomotorsinitstructure);
    gpiomotorsinitstructure.GPIO_Pin = PWM52_PIN;
    GPIOInit(PWM52_PORT, &gpiomotorsinitstructure);
    gpiomotorsinitstructure.GPIO_Pin = PWM61_PIN;
    GPIOInit(PWM61_PORT, &gpiomotorsinitstructure);
    gpiomotorsinitstructure.GPIO_Pin = PWM62_PIN;
    GPIOInit(PWM62_PORT, &gpiomotorsinitstructure);
    gpiomotorsinitstructure.GPIO_Pin = PWM71_PIN;
    GPIOInit(PWM71_PORT, &gpiomotorsinitstructure);
    gpiomotorsinitstructure.GPIO_Pin = PWM72_PIN;
    GPIOInit(PWM72_PORT, &gpiomotorsinitstructure);
}

void initHaplinkMotors(void)
{
    uint16_t PrescalerValue = 4;
    TIM3_CCR1_Val = 0;
    TIM3_CCR2_Val = 0;
    TIM3_CCR3_Val = 0;
    TIM3_CCR4_Val = 0;
    TIM4_CCR1_Val = 0;
    TIM4_CCR2_Val = 0;
    TIM4_CCR3_Val = 0;
    /* TIM3 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    /* TIM4 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

    // setup pwm pins as pwm pins
    initMotorsGpio();
    // turn off pwm direction pins:
    turnOffMotorsDirPins();

    /* Time base configuration */
    TIM_TimeBaseStructure.TIM_Period = PERIOD_PWM;
    TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up_MORT;
    TIM_TimeBaseInit_mort(TIM3_MORT, &TIM_TimeBaseStructure);
    TIM_TimeBaseInit_mort(TIM4_MORT, &TIM_TimeBaseStructure);

    /* PWM1 Mode configuration: TIM3 Channel1 */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1_MORT;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable_MORT;
    TIM_OCInitStructure.TIM_Pulse = TIM3_CCR1_Val;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High_MORT;

    TIM_OC1Init_mort(TIM3_MORT, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig_mort(TIM3_MORT, TIM_OCPreload_Enable_MORT);

    TIM_OC1Init_mort(TIM4_MORT, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig_mort(TIM4_MORT, TIM_OCPreload_Enable_MORT);

    /* PWM1 Mode configuration: TIM3 Channel2 */
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable_MORT;
    TIM_OCInitStructure.TIM_Pulse = TIM3_CCR2_Val;

    TIM_OC2Init_mort(TIM3_MORT, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig_mort(TIM3_MORT, TIM_OCPreload_Enable_MORT);

    /* PWM1 Mode configuration: TIM3 Channel3 */
    TIM_OCInitStructure.TIM_Pulse = TIM3_CCR3_Val;
    TIM_OC3Init_mort(TIM3_MORT, &TIM_OCInitStructure);
    TIM_OC3PreloadConfig_mort(TIM3_MORT, TIM_OCPreload_Enable_MORT);

    // Fingers
    /* PWM1 Mode configuration: TIM3 Channel4 */
    TIM_OCInitStructure.TIM_Pulse = TIM3_CCR4_Val;
    TIM_OC4Init_mort(TIM3_MORT, &TIM_OCInitStructure);
    TIM_OC4PreloadConfig_mort(TIM3_MORT, TIM_OCPreload_Enable_MORT);

    // TIM4
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable_MORT;
    /* PWM1 Mode configuration: TIM4 Channel1 */
    TIM_OCInitStructure.TIM_Pulse = TIM4_CCR1_Val;
    TIM_OC1Init_mort(TIM4_MORT, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig_mort(TIM4_MORT, TIM_OCPreload_Enable_MORT);

    /* PWM1 Mode configuration: TIM4 Channel2 */
    TIM_OCInitStructure.TIM_Pulse = TIM4_CCR2_Val;
    TIM_OC2Init_mort(TIM4_MORT, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig_mort(TIM4_MORT, TIM_OCPreload_Enable_MORT);

    /* PWM1 Mode configuration: TIM4 Channel3 */
    TIM_OCInitStructure.TIM_Pulse = TIM4_CCR3_Val;
    TIM_OC3Init_mort(TIM4_MORT, &TIM_OCInitStructure);
    TIM_OC3PreloadConfig_mort(TIM4_MORT, TIM_OCPreload_Enable_MORT);

    /* TIM3 enable counter */
    TIM_ARRPreloadConfig_mort(TIM3_MORT, ENABLE);
    TIM_Cmd_mort(TIM3_MORT, ENABLE);

    /* TIM4 enable counter */
    TIM_ARRPreloadConfig_mort(TIM4_MORT, ENABLE);
    TIM_Cmd_mort(TIM4_MORT, ENABLE);
}

void turnOffMotorsDirPins(void)
{
    GPIOClearBits(PWM11_PORT, (uint16_t)PWM11_PIN);
    GPIOClearBits(PWM12_PORT, (uint16_t)PWM12_PIN);
    GPIOClearBits(PWM21_PORT, (uint16_t)PWM21_PIN);
    GPIOClearBits(PWM22_PORT, (uint16_t)PWM22_PIN);
    GPIOClearBits(PWM31_PORT, (uint16_t)PWM31_PIN);
    GPIOClearBits(PWM32_PORT, (uint16_t)PWM32_PIN);
    GPIOClearBits(PWM41_PORT, (uint16_t)PWM41_PIN);
    GPIOClearBits(PWM42_PORT, (uint16_t)PWM42_PIN);
    GPIOClearBits(PWM51_PORT, (uint16_t)PWM51_PIN);
    GPIOClearBits(PWM52_PORT, (uint16_t)PWM52_PIN);
    GPIOClearBits(PWM61_PORT, (uint16_t)PWM61_PIN);
    GPIOClearBits(PWM62_PORT, (uint16_t)PWM62_PIN);
    GPIOClearBits(PWM71_PORT, (uint16_t)PWM71_PIN);
    GPIOClearBits(PWM72_PORT, (uint16_t)PWM72_PIN);
}

void motor1Dir1(void)
{
    GPIOSetBits(PWM11_PORT, (uint16_t)PWM11_PIN);
    GPIOClearBits(PWM12_PORT, (uint16_t)PWM12_PIN);
}

void motor1Dir2(void)
{
    GPIOClearBits(PWM11_PORT, (uint16_t)PWM11_PIN);
    GPIOSetBits(PWM12_PORT, (uint16_t)PWM12_PIN);
}

void motor2Dir1(void)
{
    GPIOSetBits(PWM21_PORT, (uint16_t)PWM21_PIN);
    GPIOClearBits(PWM22_PORT, (uint16_t)PWM22_PIN);
}

void motor2Dir2(void)
{
    GPIOClearBits(PWM21_PORT, (uint16_t)PWM21_PIN);
    GPIOSetBits(PWM22_PORT, (uint16_t)PWM22_PIN);
}

void motor3Dir1(void)
{
    GPIOSetBits(PWM31_PORT, (uint16_t)PWM31_PIN);
    GPIOClearBits(PWM32_PORT, (uint16_t)PWM32_PIN);
}

void motor3Dir2(void)
{
    GPIOClearBits(PWM31_PORT, (uint16_t)PWM31_PIN);
    GPIOSetBits(PWM32_PORT, (uint16_t)PWM32_PIN);
}

void motor4Dir1(void)
{
    GPIOSetBits(PWM41_PORT, (uint16_t)PWM41_PIN);
    GPIOClearBits(PWM42_PORT, (uint16_t)PWM42_PIN);
}

void motor4Dir2(void)
{
    GPIOClearBits(PWM41_PORT, (uint16_t)PWM41_PIN);
    GPIOSetBits(PWM42_PORT, (uint16_t)PWM42_PIN);
}

void motor5Dir1(void)
{
    GPIOSetBits(PWM51_PORT, (uint16_t)PWM51_PIN);
    GPIOClearBits(PWM52_PORT, (uint16_t)PWM52_PIN);
}

void motor5Dir2(void)
{
    GPIOClearBits(PWM51_PORT, (uint16_t)PWM51_PIN);
    GPIOSetBits(PWM52_PORT, (uint16_t)PWM52_PIN);
}

void motor6Dir1(void)
{
    GPIOSetBits(PWM61_PORT, (uint16_t)PWM61_PIN);
    GPIOClearBits(PWM62_PORT, (uint16_t)PWM62_PIN);
}

void motor6Dir2(void)
{
    GPIOClearBits(PWM61_PORT, (uint16_t)PWM61_PIN);
    GPIOSetBits(PWM62_PORT, (uint16_t)PWM62_PIN);
}

void motor7Dir1(void)
{
    GPIOSetBits(PWM71_PORT, (uint16_t)PWM71_PIN);
    GPIOClearBits(PWM72_PORT, (uint16_t)PWM72_PIN);
}

void motor7Dir2(void)
{
    GPIOClearBits(PWM71_PORT, (uint16_t)PWM71_PIN);
    GPIOSetBits(PWM72_PORT, (uint16_t)PWM72_PIN);
}

/*--Functions to directly set the new PWM duty cycle--------------------------*/

/**************************************
 newDuty should be a value betwen 0 and 1
***************************************/
void updateDutyCycle1(double newDuty)
{
    uint32_t newValue;
    if (newDuty > 1)
    {
        newDuty = 1;
    }
    else if (newDuty < 0)
    {
        newDuty = 0;
    }
    newValue = (uint32_t)(newDuty * PERIOD_PWM);
    TIM_SetCompare1_mort(TIM3_MORT, newValue);
}
/**************************************
 newDuty should be a value betwen 0 and 1
***************************************/
void updateDutyCycle2(double newDuty)
{
    uint32_t newValue;
    if (newDuty > 1)
    {
        newDuty = 1;
    }
    else if (newDuty < 0)
    {
        newDuty = 0;
    }
    newValue = (uint32_t)(newDuty * PERIOD_PWM);
    TIM_SetCompare2_mort(TIM3_MORT, newValue);
}
/**************************************
 newDuty should be a value betwen 0 and 1
***************************************/
void updateDutyCycle3(double newDuty)
{
    uint32_t newValue;
    if (newDuty > 1)
    {
        newDuty = 1;
    }
    else if (newDuty < 0)
    {
        newDuty = 0;
    }
    newValue = (uint32_t)(newDuty * PERIOD_PWM);
    TIM_SetCompare3_mort(TIM3_MORT, newValue);
}
/**************************************
 newDuty should be a value betwen 0 and 1
***************************************/
void updateDutyCycle4(double newDuty)
{
    uint32_t newValue;
    if (newDuty > 1)
    {
        newDuty = 1;
    }
    else if (newDuty < 0)
    {
        newDuty = 0;
    }
    newValue = (uint32_t)(newDuty * PERIOD_PWM);
    TIM_SetCompare4_mort(TIM3_MORT, newValue);
}
/**************************************
 newDuty should be a value betwen 0 and 1
***************************************/
void updateDutyCycle5(double newDuty)
{
    uint32_t newValue;
    if (newDuty > 1)
    {
        newDuty = 1;
    }
    else if (newDuty < 0)
    {
        newDuty = 0;
    }
    newValue = (uint32_t)(newDuty * PERIOD_PWM);
    TIM_SetCompare1_mort(TIM4_MORT, newValue);
}
/**************************************
 newDuty should be a value betwen 0 and 1
***************************************/
void updateDutyCycle6(double newDuty)
{
    uint32_t newValue;
    if (newDuty > 1)
    {
        newDuty = 1;
    }
    else if (newDuty < 0)
    {
        newDuty = 0;
    }
    newValue = (uint32_t)(newDuty * PERIOD_PWM);
    TIM_SetCompare2_mort(TIM4_MORT, newValue);
}
/**************************************
 newDuty should be a value betwen 0 and 1
***************************************/
void updateDutyCycle7(double newDuty)
{
    uint32_t newValue;
    if (newDuty > 1)
    {
        newDuty = 1;
    }
    else if (newDuty < 0)
    {
        newDuty = 0;
    }
    newValue = (uint32_t)(newDuty * PERIOD_PWM);
    TIM_SetCompare3_mort(TIM4_MORT, newValue);
}

/*--Debugging Functions-------------------------------------------------------*/
void outputDutyCycleMotor1(double duty)
{
    if (duty < 0)
    {
        motor1Dir1();
        duty = duty * (-1.0);
    }
    else
    {
        motor1Dir2();
    }
    dutyPrint1 = duty;
    updateDutyCycle1(duty);
}
void outputDutyCycleMotor2(double duty)
{
    if (duty < 0)
    {
        motor2Dir1();
        duty = duty * (-1.0);
    }
    else
    {
        motor2Dir2();
    }
    dutyPrint2 = duty;
    updateDutyCycle2(duty);
}
void outputDutyCycleMotor3(double duty)
{
    if (duty < 0)
    {
        motor3Dir1();
        duty = duty * (-1.0);
    }
    else
    {
        motor3Dir2();
    }
    dutyPrint3 = duty;
    updateDutyCycle3(duty);
}

void outputDutyCycleMotor4(double duty)
{
    if (duty < 0)
    {
        motor4Dir1();
        duty = duty * (-1.0);
    }
    else
    {
        motor4Dir2();
    }
    dutyPrint4 = duty;
    updateDutyCycle4(duty);
}

void outputDutyCycleMotor5(double duty)
{
    if (duty < 0)
    {
        motor5Dir1();
        duty = duty * (-1.0);
    }
    else
    {
        motor5Dir2();
    }
    dutyPrint5 = duty;
    updateDutyCycle5(duty);
}

void outputDutyCycleMotor6(double duty)
{
    if (duty < 0)
    {
        motor6Dir1();
        duty = duty * (-1.0);
    }
    else
    {
        motor6Dir2();
    }
    dutyPrint6 = duty;
    updateDutyCycle6(duty);
}

void outputDutyCycleMotor7(double duty)
{
    if (duty < 0)
    {
        motor7Dir1();
        duty = duty * (-1.0);
    }
    else
    {
        motor7Dir2();
    }
    dutyPrint7 = duty;
    updateDutyCycle7(duty);
}

/**/
/*******************************************************************************
 * @name   outputTorqueMotor1
 * @brief  Converts the desired torque to duty cycle based on calibration and
 *         outputs it on Motor1.
 * @param  double torque: the torque output desired on Motor 1 in Nm.
 * @retval None.
 */
void outputTorqueMotor1(double torque)
{
    double duty;
    if (torque < 0)
    {
        motor1Dir1();
        torque = torque * (-1.0);
    }
    else
    {
        motor1Dir2();
    }
    duty = torque * 65.13; // replace the 65.13 with value for specific motor.
    dutyPrint1 = duty;
    updateDutyCycle1(duty);
}

/*******************************************************************************
 * @name   outputTorqueMotor2
 * @brief  Converts the desired torque to duty cycle based on calibration and
 *         outputs it on Motor2.
 * @param  double torque: the torque output desired on Motor 2 in Nm.
 * @retval None.
 */
void outputTorqueMotor2(double torque)
{
    double duty;
    if (torque < 0)
    {
        motor2Dir1();
        torque = torque * (-1.0);
    }
    else
    {
        motor2Dir2();
    }

    duty = torque * 65.13; // replace 65.13 with value for specific motor.
    dutyPrint2 = duty;
    updateDutyCycle2(duty);
}
/*******************************************************************************
 * @name   outputTorqueMotor3
 * @brief  Converts the desired torque to duty cycle based on calibration and
 *         outputs it on Motor3.
 * @param  double torque: the torque output desired on Motor 3 in Nm.
 * @retval None.
 */
void outputTorqueMotor3(double torque)
{
    double duty;
    if (torque < 0)
    {
        motor3Dir1();
        torque = torque * (-1.0);
    }
    else
    {
        motor3Dir2();
    }

    duty = torque * 65.13; // replace the 65.13 with value for specific motor
    dutyPrint3 = duty;
    updateDutyCycle3(duty);
}
/*******************************************************************************
 * @name   outputTorqueMotor4
 * @brief  Converts the desired torque to duty cycle based on calibration and
 *         outputs it on Motor4.
 * @param  double torque: the torque output desired on Motor 4 in Nm.
 * @retval None.
 */
void outputTorqueMotor4(double torque)
{
    double duty;
    if (torque < 0)
    {
        motor4Dir1();
        torque = torque * (-1.0);
    }
    else
    {
        motor4Dir2();
    }

    duty = torque * 65.13; // replace the 65.13 with value for specific motor
    dutyPrint4 = duty;
    updateDutyCycle4(duty);
}
/*******************************************************************************
 * @name   outputTorqueMotor5
 * @brief  Converts the desired torque to duty cycle based on calibration and
 *         outputs it on Motor5.
 * @param  double torque: the torque output desired on Motor 5 in Nm.
 * @retval None.
 */
void outputTorqueMotor5(double torque)
{
    double duty;
    if (torque < 0)
    {
        motor5Dir1();
        torque = torque * (-1.0);
    }
    else
    {
        motor5Dir2();
    }

    duty = torque * 65.13; // replace the 65.13 with value for specific motor
    dutyPrint5 = duty;
    updateDutyCycle5(duty);
}
/*******************************************************************************
 * @name   outputTorqueMotor6
 * @brief  Converts the desired torque to duty cycle based on calibration and
 *         outputs it on Motor6.
 * @param  double torque: the torque output desired on Motor 6 in Nm.
 * @retval None.
 */
void outputTorqueMotor6(double torque)
{
    double duty;
    if (torque < 0)
    {
        motor6Dir1();
        torque = torque * (-1.0);
    }
    else
    {
        motor6Dir2();
    }

    duty = torque * 65.13; // replace the 65.13 with value for specific motor
    dutyPrint6 = duty;
    updateDutyCycle6(duty);
}
/*******************************************************************************
 * @name   outputTorqueMotor7
 * @brief  Converts the desired torque to duty cycle based on calibration and
 *         outputs it on Motor2.
 * @param  double torque: the torque output desired on Motor 2 in Nm.
 * @retval None.
 */
void outputTorqueMotor7(double torque)
{
    double duty;
    if (torque < 0)
    {
        motor7Dir1();
        torque = torque * (-1.0);
    }
    else
    {
        motor7Dir2();
    }

    duty = torque * 65.13; // replace the 65.13 with value for specific motor
    dutyPrint7 = duty;
    updateDutyCycle7(duty);
}