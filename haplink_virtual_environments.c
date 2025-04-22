/**
  ******************************************************************************
  * @file    haplink_virtual_environments.c
  * @author  mortamar@andrew.cmu.edu
  * @version 3.0
  * @date    Jan-2022
  * @brief   Defines the functions to render virtual environments for 1-DOF and
              2-DOF  Haplink. Added Support for Keil Studio
  ******************************************************************************
  */
#include "main.h"
#include "haplink_virtual_environments.h"
#include "haplink_vibration_motors.h"
#include "haplink_fsr.h"
#include "haplink_position.h"
#include "haplink_motors.h"
#include "debug_mort.h"
#include "haplink_communication.h"
#include "haplink_time.h"
#include <math.h>
#include "stdlib.h"

#define PI_MORT         3.14159265
/* Global Variables ----------------------------------------------------------*/
//variables needed declared in other files:
extern double J00, J01, J10, J11; //jacobian variables
extern double J00_f1, J01_f1, J10_f1, J11_f1; //jacobian variables
extern double J00_f2, J01_f2, J10_f2, J11_f2; //jacobian variables
extern double rx, ry, dx, dy; // 2-DOF position variables
extern double xH, dxH; //1-DOF position variables
double rx_proxy = 0.0;
double ry_proxy = 0.0;
double TorqueX, TorqueY, ForceX, ForceY, TorqueMotor1, TorqueMotor2, TorqueMotor4, TorqueMotor5, TorqueMotor6, TorqueMotor7, ForceH;


/* Function Definitions ----------------------------------------------------------*/





/*******************************************************************************
********** 1-DOF Virtual Environments*****************************************
*******************************************************************************/

/*******************************************************************************
  * @name   getForceH
  * @brief  returns the value of the Force at the handle for Haplink 1-DOF
  * @param  None.
  * @retval ForceH.
  */
double getForceH( void )
{
    return ForceH;    
}
/*******************************************************************************
  * @name   getTorqueMotor1
  * @brief  returns the value of the Torque output at motor 1
  * @param  None.
  * @retval TorqueMotor1.
  */
double getTorqueMotor1( void )
{
    return TorqueMotor1;    
} 
/*******************************************************************************
********** 2-DOF Virtual Environments*****************************************
*******************************************************************************/

/*******************************************************************************
  * @name   renderOutsideCircle2DOF_M1M2
  * @brief  There is a circle of RCircle2 radius centered at CCircleX2,CCircleY2
  *         that you can explore from the outside.
  * @param  None.
  * @retval None.
  */
void renderOutsideCircle2DOF_M1M2( void )
{
    static double x_sphere = 40.0/1000.0;
    static double y_sphere = 80.0/1000.0;
    static double R = 30/1000.0;

    double dr;
    double r_x;
    double r_y;
    double r_hat_x;
    double r_hat_y;

    static double k = 100; // N/m

    // Motor 4
    double x_user = rx/1000.0; // Rx1 and Ry1 is for first finger
    double y_user = ry/1000.0; 
    // 
    

    // implement the virtual environment!
    //Remember that ForceX and ForceY should be in Newtons!

    r_x = x_user - x_sphere;
    r_y = y_user - y_sphere;

    dr = sqrt(pow((x_user - x_sphere), 2) + pow((y_user - y_sphere), 2));

    // normalization of a vector
    r_hat_x = (1.0/dr) * r_x;
    r_hat_y = (1.0/dr) * r_y;

    if (dr < R)
    {
        ForceX = k*(R - dr)*r_hat_x;
        ForceY = k*(R - dr)*r_hat_y;
    }
    else
    {
        ForceX = 0.0;
        ForceY = 0.0;
    }

    TorqueX = J00*ForceX + J10*ForceY;
    TorqueX = TorqueX*0.001;
    TorqueY = J01*ForceX + J11*ForceY;
    TorqueY = TorqueY*0.001;
            
    TorqueMotor1 = -((TorqueX*R_MA)/R_A);
    TorqueMotor2 = -((TorqueY*R_MB)/R_B); 
            
    outputTorqueMotor1(TorqueMotor1);
    outputTorqueMotor2(TorqueMotor2);    
}
/*******************************************************************************
  * @name   renderOutsideCircle2DOF_M4M5
  * @brief  There is a circle of RCircle2 radius centered at CCircleX2,CCircleY2
  *         that you can explore from the outside.
  * @param  None.
  * @retval None.
  */
void renderOutsideCircle2DOF_M4M5( void )
{
    static double x_sphere = 40.0/1000.0;
    static double y_sphere = 80.0/1000.0;
    static double R = 30/1000.0;

    double dr;
    double r_x;
    double r_y;
    double r_hat_x;
    double r_hat_y;

    static double k = 100; // N/m

    // Motor 4
    double x_user = getRx1()/1000.0; // Rx1 and Ry1 is for first finger
    double y_user = getRy1()/1000.0; 
    // 
    

    // implement the virtual environment!
    //Remember that ForceX and ForceY should be in Newtons!

    r_x = x_user - x_sphere;
    r_y = y_user - y_sphere;

    dr = sqrt(pow((x_user - x_sphere), 2) + pow((y_user - y_sphere), 2));

    // normalization of a vector
    r_hat_x = (1.0/dr) * r_x;
    r_hat_y = (1.0/dr) * r_y;

    if (dr < R)
    {
        ForceX = k*(R - dr)*r_hat_x;
        ForceY = k*(R - dr)*r_hat_y;
    }
    else
    {
        ForceX = 0.0;
        ForceY = 0.0;
    }

    TorqueX = J00_f1*ForceX + J10_f1*ForceY;
    TorqueX = TorqueX*0.001;
    TorqueY = J01_f1*ForceX + J11_f1*ForceY;
    TorqueY = TorqueY*0.001;
            
    TorqueMotor4 = -((TorqueX*R_MA)/R_A);
    TorqueMotor5 = -((TorqueY*R_MB)/R_B); 
            
    outputTorqueMotor4(TorqueMotor4);
    outputTorqueMotor5(TorqueMotor5);    // flipped the sign to get the circle 
}

/*******************************************************************************
  * @name   renderOutsideCircle2DOF_M6M7
  * @brief  There is a circle of RCircle2 radius centered at CCircleX2,CCircleY2
  *         that you can explore from the outside.
  * @param  None.
  * @retval None.
  */
void renderOutsideCircle2DOF_M6M7( void )
{
    static double x_sphere = -40.0/1000.0;
    static double y_sphere = 80.0/1000.0;
    static double R = 30/1000.0;

    double dr;
    double r_x;
    double r_y;
    double r_hat_x;
    double r_hat_y;

    static double k = 100; // N/m


    double x_user = getRx2()/1000.0; // Rx1 and Ry1 is for first finger
    double y_user = getRy2()/1000.0; 
   
    // implement the virtual environment!
    //Remember that ForceX and ForceY should be in Newtons!

    r_x = x_user - x_sphere;
    r_y = y_user - y_sphere;

    dr = sqrt(pow((x_user - x_sphere), 2) + pow((y_user - y_sphere), 2));

    // normalization of a vector
    r_hat_x = (1.0/dr) * r_x;
    r_hat_y = (1.0/dr) * r_y;

    if (dr < R)
    {
        ForceX = k*(R - dr)*r_hat_x;
        ForceY = k*(R - dr)*r_hat_y;
    }
    else
    {
        ForceX = 0.0;
        ForceY = 0.0;
    }

    TorqueX = J00_f2*ForceX + J10_f2*ForceY;
    TorqueX = TorqueX*0.001;
    TorqueY = J01_f2*ForceX + J11_f2*ForceY;
    TorqueY = TorqueY*0.001;
            
    TorqueMotor6 = -((TorqueX*R_MA)/R_A);
    TorqueMotor7 = -((TorqueY*R_MB)/R_B); 
            
    outputTorqueMotor6(TorqueMotor6);
    outputTorqueMotor7(TorqueMotor7);    // flipped the sign to get the circle 
}

void renderOutsideCircleFinger1( void )
{
  double DCircle = 0.0;
  double FVector = 0.0;  
  ForceX = 0.0;
  ForceY = 0.0;
  
  // implement the virtual environment!
  //Remember that ForceX and ForceY should be in Newtons!
  

  TorqueX = J00_f1*ForceX + J10_f1*ForceY;
  TorqueX = TorqueX*0.001;
  TorqueY = J01_f1*ForceX + J11_f1*ForceY;
  TorqueY = TorqueY*0.001;
        
  TorqueMotor4 = -((TorqueX*R_MA)/R_A);
  TorqueMotor5 = -((TorqueY*R_MB)/R_B); 
        
  outputTorqueMotor4(TorqueMotor4);
  outputTorqueMotor5(TorqueMotor5);    
}

void renderOutsideCircleFinger2( void )
{
  double DCircle = 0.0;
  double FVector = 0.0;  
  ForceX = 0.0;
  ForceY = 0.0;
  
  // implement the virtual environment!
  //Remember that ForceX and ForceY should be in Newtons!
  

  TorqueX = J00_f2*ForceX + J10_f2*ForceY;
  TorqueX = TorqueX*0.001;
  TorqueY = J01_f2*ForceX + J11_f2*ForceY;
  TorqueY = TorqueY*0.001;
        
  TorqueMotor6 = -((TorqueX*R_MA)/R_A);
  TorqueMotor7 = -((TorqueY*R_MB)/R_B); 
        
  outputTorqueMotor6(TorqueMotor6);
  outputTorqueMotor7(TorqueMotor7);    
}

/*******************************************************************************
  * @name   renderOutsideBox2DOF
  * @brief  There is a Box delimited by WALL2_X1, WALL2_X2, WALL2_Y1, WALL2_Y2
  *         that you can explore from the outside.
  * @param  None.
  * @retval None.
  */
int renderOutsideBox2DOF( void )
{
    //Declare parameters (you may need a LOT of parameters) Again here I place the ones I used, you may want different ones.
    double CenterX_Box = 0.0;
    double CenterY_Box = 0.0;
    double Length_Box = 0.0;
    double box_stiffness = 0.0; // need an actual nonzero stiffness
    
    double X_wall_min =  CenterX_Box - Length_Box/2.0;
    double X_wall_max =  CenterX_Box + Length_Box/2.0;
    double Y_wall_min =  CenterY_Box - Length_Box/2.0;
    double Y_wall_max =  CenterY_Box + Length_Box/2.0;
    
    //variables
    double dx1 = 0;
    double dx2 = 0;
    double dy1 = 0;
    double dy2 = 0;
   
    static int contact_made = 0;     //keeping track of contact and returning it for graphics is a suggestion!
    static int contact_condition = 0; //free space
    
    ForceX = 0;
    ForceY = 0;
    
    // implement the virtual environment!
    //Remember that ForceX and ForceY should be in Newtons!


  TorqueX = J00*ForceX + J10*ForceY;
  TorqueX = TorqueX*0.001;
  TorqueY = J01*ForceX + J11*ForceY;
  TorqueY = TorqueY*0.001;
        
  TorqueMotor1 = -((TorqueX*R_MA)/R_A);
  TorqueMotor2 = -((TorqueY*R_MB)/R_B); 
        
  outputTorqueMotor1(TorqueMotor1);
  outputTorqueMotor2(TorqueMotor2);
  
  return contact_made;
}

/*******************************************************************************
  * @name   getProxyX
  * @brief  returns the 2DOF Proxy in the x direction
  * @param  None.
  * @retval double rx_proxy.
  */
double getProxyX( void )
{
    return rx_proxy;    
}
/*******************************************************************************
  * @name   getProxyY
  * @brief  returns the 2DOF Proxy in the y direction
  * @param  None.
  * @retval double ry_proxy.
  */
double getProxyY( void )
{
    return ry_proxy;    
}
/*******************************************************************************
  * @name   getForceX
  * @brief  returns the 2DOF Force in the x direction
  * @param  None.
  * @retval double ForceX.
  */
double getForceX( void )
{
    return ForceX;    
}
/*******************************************************************************
  * @name   getForceY
  * @brief  returns the 2DOF Force in the y direction
  * @param  None.
  * @retval double ForceY.
  */
double getForceY( void )
{
    return ForceY;    
}
/*******************************************************************************
  * @name   getTorqueMotor2
  * @brief  returns torque output from motor 2
  * @param  None.
  * @retval double TorqueMotor2.
  */
double getTorqueMotor2( void )
{
    return TorqueMotor2;    
}

double getTorqueMotor4( void )
{
    return TorqueMotor4;    
}

double getTorqueMotor5( void )
{
    return TorqueMotor5;    
}

double getTorqueMotor6( void )
{
    return TorqueMotor6;    
}

double getTorqueMotor7( void )
{
    return TorqueMotor7;    
}



//EOF