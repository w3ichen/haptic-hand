#ifndef __HAPLINK_MOTORS_H_
/**
  ******************************************************************************
  * @file    haplink_motors.h
  * @author  mortamar@andrew.cmu.edu
  * @version 1.0
  * @date    January-2023
  * @brief   Control's haplink's motors. By default Haplink has two motors that are connected with directionality
  meant for DC motors (Motors 1 and 2) and two vibration motors (Motors 3 and 4). The code gives you the option 
  of also using Motor 3 as a DC motor. You have to be careful to remove the second motor driver from Haplink's 
  board then and connect it externally. 
  ******************************************************************************
  */
#define __HAPLINK_MOTORS_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"

//PWM timer period
#define PERIOD_PWM                  665
#define MOTOR_1 1
#define MOTOR_2 2
#define MOTOR_3 3
#define MOTOR_4 4
#define MOTOR_5 5
#define MOTOR_6 6
#define MOTOR_7 7


void initHaplinkMotors( void );

void initHaplinkGpio( void );

void turnOffMotorsDirPins( void );

void motor1Dir1 (void);
void motor1Dir2 (void);
void motor2Dir1 (void);
void motor2Dir2 (void);
void motor3Dir1 (void);
void motor3Dir2 (void);

void updateDutyCycle1( double newDuty );
void updateDutyCycle2( double newDuty );
void updateDutyCycle3( double newDuty );
void updateDutyCycle4( double newDuty );
void outputDutyCycleMotor1(double duty);
void outputDutyCycleMotor2(double duty);
void outputDutyCycleMotor3(double duty);
void outputTorqueMotor1(double torque);
void outputTorqueMotor2(double torque);
void outputTorqueMotor3(double torque);
void outputTorqueMotor4(double torque);
void outputTorqueMotor5(double torque);
void outputTorqueMotor6(double torque);
void outputTorqueMotor7(double torque);


#ifdef __cplusplus
}
#endif


#endif  //__HAPLINK_MOTORS_H_