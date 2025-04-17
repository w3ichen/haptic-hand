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


  ******************************************************************************
  */

#include "haplink_motors.h"
#include "stm32f4xx_rcc_mort.h"
#include "stm32f446ze_gpio.h"
#include "stm32f4xx_tim_mort.h"


#define PWM11_PIN GPIOPin11
#define PWM12_PIN GPIOPin10
#define PWM21_PIN GPIOPin12
#define PWM22_PIN GPIOPin2
#define PWM31_PIN GPIOPin0
#define PWM32_PIN GPIOPin1

#define PWM11_PORT ((GPIOTypeDef *)GPIOC_BASE_MORT)
#define PWM12_PORT ((GPIOTypeDef *)GPIOC_BASE_MORT)
#define PWM21_PORT ((GPIOTypeDef *)GPIOC_BASE_MORT)
#define PWM22_PORT ((GPIOTypeDef *)GPIOD_BASE_MORT)
#define PWM31_PORT ((GPIOTypeDef *)GPIOD_BASE_MORT)
#define PWM32_PORT ((GPIOTypeDef *)GPIOD_BASE_MORT)

GPIOInitTypeDef gpiomotorsinitstructure;
TIM_TimeBaseInitTypeDef_mort  TIM_TimeBaseStructure;
TIM_OCInitTypeDef_mort  TIM_OCInitStructure;

uint16_t CCR1_Val = 0;
uint16_t CCR2_Val = 0;
uint16_t CCR3_Val = 0;
uint16_t CCR4_Val = 0;

double dutyPrint1 = 0;
double dutyPrint2 = 0;
double dutyPrint3 = 0;

void initMotorsGpio( void )
{
    /* First the pins connected to PWM*/
    // Start clocks for ports in use
    /* GPIOC clock enable */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);


    // Init PWM pins
    gpiomotorsinitstructure.GPIO_Mode = GPIOModeAF;
    gpiomotorsinitstructure.GPIO_OType = GPIOOTypePP;
    gpiomotorsinitstructure.GPIO_Speed = GPIOHighSpeed;
    gpiomotorsinitstructure.GPIO_PuPd = GPIOPuPdUP;
    gpiomotorsinitstructure.GPIO_Pin = GPIOPin6;
    GPIOInit((GPIOTypeDef *)GPIOC_BASE_MORT, &gpiomotorsinitstructure); //PWM1
    gpiomotorsinitstructure.GPIO_Pin = GPIOPin7;
    GPIOInit((GPIOTypeDef *)GPIOC_BASE_MORT, &gpiomotorsinitstructure); //PWM2
    gpiomotorsinitstructure.GPIO_Pin = GPIOPin8;
    GPIOInit((GPIOTypeDef *)GPIOC_BASE_MORT, &gpiomotorsinitstructure); //PWM3
    gpiomotorsinitstructure.GPIO_Pin = GPIOPin9;
    GPIOInit((GPIOTypeDef *)GPIOC_BASE_MORT, &gpiomotorsinitstructure); //PWM4

    /* Connect TIM3 pins to AF2 */  
    GPIOPinAFConfig((GPIOTypeDef *)GPIOC_BASE_MORT, GPIOPinSource6, GPIO_AF_TIM3);
    GPIOPinAFConfig((GPIOTypeDef *)GPIOC_BASE_MORT, GPIOPinSource7, GPIO_AF_TIM3); 
    GPIOPinAFConfig((GPIOTypeDef *)GPIOC_BASE_MORT, GPIOPinSource8, GPIO_AF_TIM3);
    GPIOPinAFConfig((GPIOTypeDef *)GPIOC_BASE_MORT, GPIOPinSource9, GPIO_AF_TIM3); 


    /*Then the pins used for direction*/
    gpiomotorsinitstructure.GPIO_Mode = GPIOModeOUT;
    gpiomotorsinitstructure.GPIO_OType = GPIOOTypePP;
    gpiomotorsinitstructure.GPIO_Speed = GPIOHighSpeed;
    gpiomotorsinitstructure.GPIO_PuPd = GPIOPuPdNOPULL;
    gpiomotorsinitstructure.GPIO_Pin = GPIOPin10;
    GPIOInit((GPIOTypeDef *)GPIOC_BASE_MORT, &gpiomotorsinitstructure); // C10
    gpiomotorsinitstructure.GPIO_Pin = GPIOPin11;
    GPIOInit((GPIOTypeDef *)GPIOC_BASE_MORT, &gpiomotorsinitstructure); // C11
    gpiomotorsinitstructure.GPIO_Pin = GPIOPin12;
    GPIOInit((GPIOTypeDef *)GPIOC_BASE_MORT, &gpiomotorsinitstructure); // C12
    gpiomotorsinitstructure.GPIO_Pin = GPIOPin2;
    GPIOInit((GPIOTypeDef *)GPIOD_BASE_MORT, &gpiomotorsinitstructure); // D2
    gpiomotorsinitstructure.GPIO_Pin = GPIOPin2;
    GPIOInit((GPIOTypeDef *)GPIOG_BASE_MORT, &gpiomotorsinitstructure); // G2
    gpiomotorsinitstructure.GPIO_Pin = GPIOPin3;
    GPIOInit((GPIOTypeDef *)GPIOG_BASE_MORT, &gpiomotorsinitstructure); // G3
    gpiomotorsinitstructure.GPIO_Pin = GPIOPin0;
    GPIOInit((GPIOTypeDef *)GPIOD_BASE_MORT, &gpiomotorsinitstructure); // D0
    gpiomotorsinitstructure.GPIO_Pin = GPIOPin1;
    GPIOInit((GPIOTypeDef *)GPIOD_BASE_MORT, &gpiomotorsinitstructure); // D1
}

void initHaplinkMotors( void )
{
    uint16_t PrescalerValue = 4;
    CCR1_Val = 0;
    CCR2_Val = 0;
    CCR3_Val = 0;
    CCR4_Val = 0;
    /* TIM3 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  
    //setup pwm pins as pwm pins 
    initMotorsGpio();
    //turn off pwm direction pins:
    turnOffMotorsDirPins();

    /* Time base configuration */
    TIM_TimeBaseStructure.TIM_Period = PERIOD_PWM;
    TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up_MORT;
    TIM_TimeBaseInit_mort(TIM3_MORT, &TIM_TimeBaseStructure);

    /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1_MORT;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable_MORT;
  TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High_MORT;

  TIM_OC1Init_mort(TIM3_MORT, &TIM_OCInitStructure);

  TIM_OC1PreloadConfig_mort(TIM3_MORT, TIM_OCPreload_Enable_MORT);

  /* PWM1 Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable_MORT;
  TIM_OCInitStructure.TIM_Pulse = CCR2_Val;

  TIM_OC2Init_mort(TIM3_MORT, &TIM_OCInitStructure);

  TIM_OC2PreloadConfig_mort(TIM3_MORT, TIM_OCPreload_Enable_MORT);

  /* PWM1 Mode configuration: Channel3 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable_MORT;
  TIM_OCInitStructure.TIM_Pulse = CCR3_Val;

  TIM_OC3Init_mort(TIM3_MORT, &TIM_OCInitStructure);

  TIM_OC3PreloadConfig_mort(TIM3_MORT, TIM_OCPreload_Enable_MORT);

  /* PWM1 Mode configuration: Channel4 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable_MORT;
  TIM_OCInitStructure.TIM_Pulse = CCR4_Val;

  TIM_OC4Init_mort(TIM3_MORT, &TIM_OCInitStructure);

  TIM_OC4PreloadConfig_mort(TIM3_MORT, TIM_OCPreload_Enable_MORT);

  TIM_ARRPreloadConfig_mort(TIM3_MORT, ENABLE);

  /* TIM3 enable counter */
  TIM_Cmd_mort(TIM3_MORT, ENABLE);  
}


void turnOffMotorsDirPins( void )
{
    GPIOClearBits(PWM11_PORT, (uint16_t)PWM11_PIN );
    GPIOClearBits(PWM12_PORT, (uint16_t)PWM12_PIN );
    GPIOClearBits(PWM21_PORT, (uint16_t)PWM21_PIN );
    GPIOClearBits(PWM22_PORT, (uint16_t)PWM22_PIN );
    GPIOClearBits(PWM31_PORT, (uint16_t)PWM31_PIN );
    GPIOClearBits(PWM32_PORT, (uint16_t)PWM32_PIN );
}


void motor1Dir1 (void)
{
    GPIOSetBits(PWM11_PORT, (uint16_t)PWM11_PIN );
    GPIOClearBits(PWM12_PORT, (uint16_t)PWM12_PIN );
}

void motor1Dir2 (void)
{
    GPIOClearBits(PWM11_PORT, (uint16_t)PWM11_PIN );
    GPIOSetBits(PWM12_PORT, (uint16_t)PWM12_PIN );
}

void motor2Dir1 (void)
{
    GPIOSetBits(PWM21_PORT, (uint16_t)PWM21_PIN );
    GPIOClearBits(PWM22_PORT, (uint16_t)PWM22_PIN );
}

void motor2Dir2 (void)
{
    GPIOClearBits(PWM21_PORT, (uint16_t)PWM21_PIN );
    GPIOSetBits(PWM22_PORT, (uint16_t)PWM22_PIN );
}

void motor3Dir1 (void)
{
    GPIOSetBits(PWM31_PORT, (uint16_t)PWM31_PIN );
    GPIOClearBits(PWM32_PORT, (uint16_t)PWM32_PIN );
}

void motor3Dir2 (void)
{
    GPIOClearBits(PWM31_PORT, (uint16_t)PWM31_PIN );
    GPIOSetBits(PWM32_PORT, (uint16_t)PWM32_PIN );
}



/*--Functions to directly set the new PWM duty cycle--------------------------*/

/**************************************
 newDuty should be a value betwen 0 and 1
***************************************/
void updateDutyCycle1( double newDuty )
{
    uint32_t newValue;
    if (newDuty > 1)
    {
        newDuty = 1;
    }
    else if (newDuty < 0 )
    {
        newDuty = 0;
    }
    newValue = (uint32_t)(newDuty*PERIOD_PWM);
    TIM_SetCompare1_mort(TIM3_MORT, newValue);  
}
/**************************************
 newDuty should be a value betwen 0 and 1
***************************************/
void updateDutyCycle2( double newDuty )
{
    uint32_t newValue;
    if (newDuty > 1)
    {
        newDuty = 1;
    }
    else if (newDuty < 0 )
    {
        newDuty = 0;
    }
    newValue = (uint32_t)(newDuty*PERIOD_PWM);
    TIM_SetCompare2_mort(TIM3_MORT, newValue);  
}
/**************************************
 newDuty should be a value betwen 0 and 1
***************************************/
void updateDutyCycle3( double newDuty )
{
    uint32_t newValue;
    if (newDuty > 1)
    {
        newDuty = 1;
    }
    else if (newDuty < 0 )
    {
        newDuty = 0;
    }
    newValue = (uint32_t)(newDuty*PERIOD_PWM);
    TIM_SetCompare3_mort(TIM3_MORT, newValue);  
}
/**************************************
 newDuty should be a value betwen 0 and 1
***************************************/
void updateDutyCycle4( double newDuty )
{
    uint32_t newValue;
    if (newDuty > 1)
    {
        newDuty = 1;
    }
    else if (newDuty < 0 )
    {
        newDuty = 0;
    }
    newValue = (uint32_t)(newDuty*PERIOD_PWM);
    TIM_SetCompare4_mort(TIM3_MORT, newValue);  
}

/*--Debugging Functions-------------------------------------------------------*/
void outputDutyCycleMotor1(double duty)
{
    if (duty < 0)
    {
        motor1Dir1();
        duty = duty*(-1.0);
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
        duty = duty*(-1.0);
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
        duty = duty*(-1.0);
    }
    else
    {
        motor3Dir2();
    }
    dutyPrint3 = duty;
    updateDutyCycle3(duty); 
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
        torque = torque*(-1.0);
    }
    else
    {
        motor1Dir2();
    }
    duty = torque*65.13; //replace the 65.13 with value for specific motor.
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
        torque = torque*(-1.0);
    }
    else
    {
        motor2Dir2();
    }

    duty = torque*65.13; //replace 65.13 with value for specific motor.
    dutyPrint2 = duty;
    updateDutyCycle2(duty);
}
/*******************************************************************************
  * @name   outputTorqueMotor3
  * @brief  Converts the desired torque to duty cycle based on calibration and
  *         outputs it on Motor2.
  * @param  double torque: the torque output desired on Motor 2 in Nm.
  * @retval None.
  */
void outputTorqueMotor3(double torque)
{
    double duty;
    if (torque < 0)
    {
        motor3Dir1();
        torque = torque*(-1.0);
    }
    else
    {
        motor3Dir2();
    }

    duty = torque*65.13; //replace the 65.13 with value for specific motor
    dutyPrint3 = duty;
    updateDutyCycle3(duty);
}