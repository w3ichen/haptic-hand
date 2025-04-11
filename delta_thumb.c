#include "delta_thumb.h"
#include "haplink_position.h"
#include "haplink_motors.h"

/*******************************************************************************
  * @name   initDeltaThumb
  * @brief  initialize the delta mechanism thumb
  * @param  None.
  * @retval None.
  */
void initDeltaThumb( void )
{
    // Read encoders    
    double ThetaMotor1 = calculatePositionMotor1();
    double ThetaMotor2 = calculatePositionMotor2();

    printf("theta1=%f, theta2=%f\n", ThetaMotor1, ThetaMotor2);
    

    // Output forces
    double ForceMotor1 = 0.0;
    double TorqueMotor1 = -((R_MA/R_A) * R_HA) * ForceMotor1;
    TorqueMotor1 = TorqueMotor1*0.001; //convert units
    outputTorqueMotor1(TorqueMotor1);    

    double ForceMotor2 = 0.0;
    double TorqueMotor2 = -((R_MA/R_A) * R_HA) * ForceMotor2;
    TorqueMotor2 = TorqueMotor2*0.001; //convert units
    outputTorqueMotor2(TorqueMotor2);    
}