#include "delta_thumb.h"
#include "haplink_position.h"
#include "haplink_motors.h"

/*******************************************************************************
  * @name   deltaThumbHandler
  * @brief  initialize the delta mechanism thumb
  * @param  None.
  * @retval None.
  */
void deltaThumbHandler( void )
{
    // Read encoders    
    double ThetaMotor1 = calculatePositionMotor1();
    double ThetaMotor2 = calculatePositionMotor2();
    double ThetaMotor3 = calculatePositionMotor3();

    printf("theta1=%f, theta2=%f, theta3=%f\n", ThetaMotor1, ThetaMotor2, ThetaMotor3);
    

    // Output forces
    double ForceMotor1 = 0.0;
    double TorqueMotor1 = -((R_MA/R_A) * R_HA) * ForceMotor1;
    TorqueMotor1 = TorqueMotor1*0.001; //convert units
    outputTorqueMotor1(TorqueMotor1);    

    double ForceMotor2 = 0.0;
    double TorqueMotor2 = -((R_MA/R_A) * R_HA) * ForceMotor2;
    TorqueMotor2 = TorqueMotor2*0.001; //convert units
    outputTorqueMotor2(TorqueMotor2);    

    double ForceMotor3 = 0.0;
    double TorqueMotor3 = -((R_MA/R_A) * R_HA) * ForceMotor3;
    TorqueMotor3 = TorqueMotor3*0.001; //convert units

    outputTorqueMotor3(TorqueMotor3);    
}