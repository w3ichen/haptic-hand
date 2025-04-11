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
    static int velocitycounter = 0;
    double dxH_new = 0;
    int time_dif_int = 0;
    
    double theta_ma = calculatePositionMotor1();
    
    double theta_a = -theta_ma*R_MA/R_A;
    double xH = -R_HA*theta_a;
    
    printf("Xh=%f\n", xH);
    
    double ForceH = 0.1;

    
    double  TorqueMotor1 = -((R_MA/R_A) * R_HA) * ForceH;
    TorqueMotor1 = TorqueMotor1*0.001; //convert units
    outputTorqueMotor1(TorqueMotor1);    
}