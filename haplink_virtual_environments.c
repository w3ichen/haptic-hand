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
extern double rx, ry, dx, dy; // 2-DOF position variables
extern double xH, dxH; //1-DOF position variables
double rx_proxy = 0.0;
double ry_proxy = 0.0;
double TorqueX, TorqueY, ForceX, ForceY, TorqueMotor1, TorqueMotor2, TorqueMotor4, TorqueMotor5, TorqueMotor6, TorqueMotor7, ForceH;


/* Function Definitions ----------------------------------------------------------*/



/*******************************************************************************
  * @name   renderForceAlert
  * @brief  reads FSR1 and outputs a vibration proportional to the reading
  *         on the vibration motor 1.
  * @param  None.
  * @retval None.
  */
void renderForceAlert( void )
{
  double amplitude = 0.0;
  uint16_t maxFsr = 0.0;                // determined this value by pressing FSR really hard
  uint16_t currFsr = queryFSR1value(); // get the current value of the FSR

    //implement the function!
    // check that the current value does not exceed the max value, 
    // amplitude of vibration should be a function of the current FSR value and the 
    // max FSR value you calculated
    // amplitude HAS to be a value between 0 and 1
 

    turnVibrationMotor1On(amplitude); 
}

/*******************************************************************************
********** 1-DOF Virtual Environments*****************************************
*******************************************************************************/

/*******************************************************************************
  * @name   renderSpring1DOF
  * @brief  renders a 1-DOF spring centered at xH=0
  * @param  None.
  * @retval None.
  */
void renderSpring1DOF( void )
{
    ForceH = 0;
    // Render a Spring:
    //implement the virtual environment!
    // ForceH should be proportional to the displacement!
    //Remember that xH is in mm and Force should be in Newtons and Torque in Newton meters!
    //convert xH to meters!
    ForceH = -K_SPRING*(xH/1000); //convert xH to meters


    TorqueMotor1 = -((R_MA/R_A) * R_HA) * ForceH;
    TorqueMotor1 = TorqueMotor1*0.001; //convert units
    outputTorqueMotor1(TorqueMotor1);    
}
/*******************************************************************************
  * @name   renderVirtualWall1DOF
  * @brief  renders a 1-DOF wall centered at X_WALL
  * @param  None.
  * @retval None.
  */
void renderVirtualWall1DOF( void )
{
    ForceH = 0;
    // Render a Virtual Wall:
    //implement the virtual environment! 
    // ForceH should be zero if you are outside of the wall, it then is proportional to how far you have penetrated into the wall.
    //Remember that xH is in mm and Force should be in Newtons and Torque in Newton meters!
    //convert xH to meters!
    
    TorqueMotor1 = -((R_MA/R_A) * R_HA) * ForceH;
    TorqueMotor1 = TorqueMotor1*0.001; //convert units
    outputTorqueMotor1(TorqueMotor1);     
}
/*******************************************************************************
  * @name   renderLinearDamping1DOF
  * @brief  renders linear damping as a function of dXH
  * @param  None.
  * @retval None.
  */
void renderLinearDamping1DOF( void )
{
    ForceH = 0;
    
    // Render a linear damper:
    //implement the virtual environment!
    //Remember that dxH is in mm/s and Force should be in Newtons and Torque in Newton meters!
    //convert dxH to meters/s!
    
    TorqueMotor1 = -((R_MA/R_A) * R_HA) * ForceH;
    TorqueMotor1 = TorqueMotor1*0.001; //convert units
    outputTorqueMotor1(TorqueMotor1);     
}
/*******************************************************************************
  * @name   renderNonLinearFriction1DOF
  * @brief  Renders a Combination of Coulomb friction with additional damping
  *         during dynamic friction- the Karnopp model
  * @param  None.
  * @retval None.
  */
void renderNonLinearFriction1DOF( void )
{
    //Parameters for nonlinear friction, these are recommendations, you may feel you need different ones.
    //Feel free to declare your own. If you do use these, you need to experiment and assign them nonzero values.   
    double b_nonlinear = 0.0; //Nonlinear damping in N/m (damping for the sharp part of the curve)
    double dxH_threshold = 0.0; //Velocity threshold for nonlinear damping
    double b_scaling = 0.0;    //scaling of the nonlinear damping (in the not so steep part, you can get a shallower slope by dividing b_nonlinear by b_scaling)
    double dxH_m = dxH/1000.0; //get dxH in m/s
    
    ForceH = 0;

    //Implement the virtual environment!
    
    
    TorqueMotor1 = -((R_MA/R_A) * R_HA) * ForceH;
    TorqueMotor1 = TorqueMotor1*0.001; //convert units
    outputTorqueMotor1(TorqueMotor1);    
}
/*******************************************************************************
  * @name   renderHardSurface1DOF
  * @brief  Renders a surface that feels harder than the maximum stiffness
  *         that can be stably displayed by the Haplit using stiffness alone.
  *         This can be done by generating a decaying sinusoid upon impact with
  *         a virtual wall.
  * @param  None.
  * @retval None.
  */
void renderHardSurface1DOF( void )
{
    //Parameters for hard surface: 
    // Again these are parameters that I found useful when generating the virtual environment since 
    // it entails generating a decaying sinusoid. 
    //Feel free to declare your own. If you do use these, you need to experiment and assign them nonzero values. 
    double decay_sine_amplitude_scale = 0.0; //decaying sinusoid velocity to amplitude scale
    double decay_sine_amplitude_max = 0.0; // decaying sinusoid maximum amplitude
    double decay_sine_frequency = 0.0; //decaying sinusoid frequency
    double decay_sine_exponent = 0.0; //decaying sinusoid decay exponent
    double E_Value = 2.71828; // value for constant e
    
    double hardsurfacewall_x = 0.0; //starting point of wall in meters
    double hardsurfacewall_stiffness = 0.0; //stiffness of wall in N/m
    
    static double decay_sine_time = 0.0; //decaying sinusoid time counter
    static double decay_sine_amplitude = 0.0; //decaying sinusoid amplitude
    static int decay_in_wall_flag = 0; //decaying sinusoid flag indicating whether handle is in wall
    
    
    double xH_m = xH/1000.0;
    double dxH_m = dxH/1000.0;
    
    ForceH = 0;
    
    // implement the virtual environment!
    
    TorqueMotor1 = -((R_MA/R_A) * R_HA) * ForceH;
    TorqueMotor1 = TorqueMotor1*0.001; //convert units
    outputTorqueMotor1(TorqueMotor1);    
}
/*******************************************************************************
  * @name   renderBumpAndValley1DOF
  * @brief  A virtual environment in which there is a bump on the left side of 
  *         the Hapkit workspace were xh < 0 and a valley on the right side 
  *         where xh>0. The effects should feel the same whether the user is 
  *         moving right to left or left to right. This effects are created with
  *         a 1-DOF haptic device using lateral forces.
  * @param  None.
  * @retval None.
  */
void renderBumpAndValley1DOF( void )
{
    // Parameter for bumps and valleys these are recommendations, you may feel you need different ones.
    //Feel free to declare your own. If you do use these, you need to experiment and assign them nonzero values.   
    double Bump_Location = 0.0; // Bump location
    double Bump_Length = 0.0; // Length of bump
    double Bump_Height = 0.0; // Height of bump
    double Bump_Stiffness = 0.0; // Stiffness of the bump
    double Valley_Location = 0.0; // Valley location
    double Valley_Length = 0.0; // Length of valley
    double Valley_Height = 0.0; // Amplitude of valley
    double Valley_Stiffness = 0.0; // Stiffness of the valley
    
    ForceH = 0;
    
    // implement the virtual environment!

    TorqueMotor1 = -((R_MA/R_A) * R_HA) * ForceH;
    TorqueMotor1 = TorqueMotor1*0.001; //convert units
    outputTorqueMotor1(TorqueMotor1);    
}
/*******************************************************************************
  * @name   renderTexture1DOF
  * @brief  renders a textured/rough surface
  * @param  None.
  * @retval None.
  */
void renderTexture1DOF( void )
{
    ForceH = 0;
      
    // implement the virtual environment!

    TorqueMotor1 = -((R_MA/R_A) * R_HA) * ForceH;
    TorqueMotor1 = TorqueMotor1*0.001; //convert units
    outputTorqueMotor1(TorqueMotor1);   
}
// also render surface but using a cosine function (sine function works well too :) )
void renderTexture21DOF( void )
{
    ForceH = 0;
    

    // maybe wanna try another algorithm?
    
    TorqueMotor1 = -((R_MA/R_A) * R_HA) * ForceH;
    TorqueMotor1 = TorqueMotor1*0.001; //convert units
    outputTorqueMotor1(TorqueMotor1);   
}
/*******************************************************************************
  * @name   renderWallForGraphics1DOF
  * @brief  renders a wall. Returns the position of the wall.
  * @param  None.
  * @retval graphics_wall.
  */
double renderWallForGraphics1DOF( void )
{
    double graphics_wall = 0.0; //position where the wall will be-> should inform processing
    ForceH = 0;
    
    // implement the virtual environment!
    
    TorqueMotor1 = -((R_MA/R_A) * R_HA) * ForceH;
    TorqueMotor1 = TorqueMotor1*0.001; //convert units
    outputTorqueMotor1(TorqueMotor1);

return graphics_wall;  //return the position of the wall so processing knows where it is
}
/*******************************************************************************
  * @name   renderDynamicMDSimulation1DOF
  * @brief  Implements a dynamic interaction between Haplink and a mass spring
  *         damper system. 
  * @param  None.
  * @retval x_msd.
  */
double renderDynamicMSDSimulation1DOF( void )
{
    //Declare parameters for the simulation: these are recommendations, you may feel you need different ones.
    //Feel free to declare your own. If you do use these, you need to experiment and assign them nonzero values. 
    double m_msd = 0.0;        // mass of the mass spring damper simulation in kg
    double b_msd = 0.0;        // damping coefficient of the mass spring damper simulation in Ns/m
    double k_msd = 0.0;       // spring coefficient of the mass spring damper simulation in N/m
    double k_u = 0.0;        // spring coefficient that represents the stiffness of the interaction between the mass and the user
    
    //variables
    double dt = 0;         //time step for intergration
    double t1 = 0;
    //position variable to keep track of the user in meters
    double xH_m;
    // position variables for keeping track of the position of the mass
    static double x_msd = 0.01;        // position of the mass initialized to its initial position
    static double v_msd = 0;        // velocity of the mass
    static double a_msd = 0;        // acceleration of the mass
    static double xi_msd = 0.01;   // initial position of the mass in meters
    static double t0 = -1.0;  //initial time in seconds //Keil Studio did not allow initializations on functions so had to implement the hack below
    
    
    //if first time running get the actual initial time:
    if (t0 < 0)
    {
        t0 = getTime_ms()/1000.0;
    }

    ForceH = 0; 
    
    xH_m = getXH()/1000.0;
    t1 = getTime_ms()/1000.0;
    dt = t1 - t0;
    t0 = t1;

//implement the virtual environment!
    
    //Calculate the state:


    // If the user has "penetrated" the mass and is interacting with it what is ForceH?:


TorqueMotor1 = -((R_MA/R_A) * R_HA) * ForceH;
TorqueMotor1 = TorqueMotor1*0.001; //convert units
outputTorqueMotor1(TorqueMotor1);   
return x_msd;          
}  
/*******************************************************************************
  * @name   renderBilateralTeleoperator1DOF
  * @brief  returns the value of the Force at the handle for Haplink 1-DOF
  * @param  None.
  * @retval x_msd.
  */
void renderBilateralTeleoperator1DOF(void)
{
    //Declare parameters for bilateral teleoperation
    double ktele = 0;
    double btele = 0;
    double xH2; //position of the other handle
    xH2 = get_tele_position(); //obtain the position of the other handle
    
    ForceH = 0;
    
    //implement bilateral teleoperation
    
    TorqueMotor1 = -((R_MA/R_A) * R_HA) * ForceH;
    TorqueMotor1 = TorqueMotor1*0.001; //convert units
    outputTorqueMotor1(TorqueMotor1);    
}
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
  * @name   renderFloor2DOF
  * @brief  renders a horizontal wall or "floor" at WALL_Y_FLOOR
  * @param  None.
  * @retval None.
  */
void renderFloor2DOF( void )
{
    ForceX = 0;
    ForceY = 0;


     // implement the virtual environment!
    

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
  * @name   renderInsideBox2DOF
  * @brief  The user is "trapped" inside a square box delimited by WALL_X1, 
  *         WALL_X2, WALL_Y1, WALL_Y2.
  * @param  None.
  * @retval None.
  */
void renderInsideBox2DOF( void )
{
   
}
/*******************************************************************************
  * @name   renderInsideCircle2DOF
  * @brief  The user is "trapped" inside a circle of radius RCircle and centered 
  *         at CCircleX,CCircleY.
  * @param  None.
  * @retval None.
  */
void renderInsideCircle2DOF( void )
{
  double DCircle = 0.0;
  double FVector = 0.0;  
  ForceX = 0.0;
  ForceY = 0.0;

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
}
/*******************************************************************************
  * @name   renderOutsideCircle2DOF
  * @brief  There is a circle of RCircle2 radius centered at CCircleX2,CCircleY2
  *         that you can explore from the outside.
  * @param  None.
  * @retval None.
  */
void renderOutsideCircle2DOF( void )
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

    double x_user = getRx1()/1000.0; // Rx1 and Ry1 is for first finger
    double y_user = getRy1()/1000.0; 
    

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
            
    TorqueMotor4 = -((TorqueX*R_MA)/R_A);
    TorqueMotor5 = -((TorqueY*R_MB)/R_B); 
            
    outputTorqueMotor4(TorqueMotor4);
    outputTorqueMotor5(TorqueMotor5);    
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
  * @name   renderBilateralTeleoperator2DOF
  * @brief  renders bilateral teleoperation for the 2-DOF Haplink Cursor
  * @param  None.
  * @retval x_msd.
  */
void renderBilateralTeleoperator2DOF(void)
{
    double ktele = 0.0;
    double btele = 0.0;
    double rx2;
    double ry2;
    
    rx2 = get_rx_tele();
    ry2 = get_ry_tele();
    
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