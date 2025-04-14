/**
  ******************************************************************************
  * @file    haplink_position.cpp 
  * @author  mortamar@andrew.cmu.edu
  * @version 3.0
  * @date    January-2022
  * @brief   Calculates the position of the Hapkit Handle and the Haplink Cursor.
  ******************************************************************************
  */

#include "haplink_position.h"
#include "haplink_time.h"
#include "haplink_encoders.h"
#include "stdlib.h"
#include <math.h>
#include <debug_mort.h>
#include "delta_thumb.h"

/* Global Variables ----------------------------------------------------------*/

//Motor Variables
double theta_m1;
double theta_m2;
double theta_m3;
double theta_m4;
double theta_m5;
double theta_m6;
double theta_m7;

//Haplink Variables
double theta_a;
double theta_b;
double theta_ma;
double theta_mb;

double b1, b2;

double time0_counter;
double deltatime_counter;
double time_counter;

extern uint8_t CountsSensor1Changed;
extern uint8_t CountsSensor2Changed;

uint8_t Velocity1Changed;


//position of handle variables:
double rx, dx, rx_prev, dx_prev;
double ry, dy, ry_prev, dy_prev;
double t0_pos, t1_pos,time_dif;
double xH, dxH, xH_prev, dxH_prev; //position of the hapkit handle
// Jacobian variables:
double J00, J01, J10, J11;

//debug variables:
int debugcounter = 0;


/*******************************************************************************
  * @name   initHapticHand
  * @brief  initializes the Haptic hand position variables and position hardware
  * @param  None.
  * @retval int 1 to indicate initialization has been completed.
  */
int initHapticHand( void )
{
    //initialize variables
    rx = 0;
    ry = 0;
    rx_prev = 0;
    ry_prev = 0;
    dx = 0;
    dy = 0;
    dx_prev = 0;
    dy_prev = 0;
    theta_a = 0;
    theta_b = 0;
    xH = 0;
    xH_prev = 0;
    dxH = 0;
    dxH_prev = 0;
    
    J00 = 0;
    J01 = 0;
    J10 = 0;
    J11 = 0;
    //initialize encoders
    initHapticHandEncodersMotors();
    
    initPositionHandleAndJacobian( );   

    initDeltaThumb();
    return 1;
}

/*******************************************************************************
  * @name   initHaplinkPosition
  * @brief  initializes the Haplink position variables and position hardware
  * @param  None.
  * @retval int 1 to indicate initialization has been completed.
  */
int initHaplinkPosition( void )
{
    //initialize variables
    rx = 0;
    ry = 0;
    rx_prev = 0;
    ry_prev = 0;
    dx = 0;
    dy = 0;
    dx_prev = 0;
    dy_prev = 0;
    theta_a = 0;
    theta_b = 0;
    xH = 0;
    xH_prev = 0;
    dxH = 0;
    dxH_prev = 0;
    
    J00 = 0;
    J01 = 0;
    J10 = 0;
    J11 = 0;
    //initialize encoders
    initHaplinkEncoders2Motors();
    //wait_ms(200); //wait to settle timers
    
    initPositionHandleAndJacobian( );   
    return 1;
}


/*******************************************************************************
  * @name   calculatePositionMotor1
  * @brief  Calculates the rotation of Motor 1 in radians
  * @param  None.
  * @retval theta_m1: the current rotation of Motor 1 in radians
  */
double calculatePositionMotor1( void )
{
     theta_m1 = (double)getCountsSensor1();
    theta_m1 = theta_m1*2.0*3.1416;
    theta_m1 = theta_m1/TOTAL_ENCODER_COUNTS_1;
    return theta_m1;
}

/*******************************************************************************
  * @name   calculatePositionMotor2
  * @brief  Calculates the rotation of Motor 2 in radians
  * @param  None.
  * @retval theta_m2: the current rotation of Motor 2 in radians
  */
double calculatePositionMotor2( void )
{
    theta_m2 = (double)getCountsSensor2();
    theta_m2 = theta_m2*2.0*3.1416;
    theta_m2 = theta_m2/TOTAL_ENCODER_COUNTS_2;
    return theta_m2;
}

/*******************************************************************************
  * @name   calculatePositionMotor3
  * @brief  Calculates the rotation of Motor 3 in radians
  * @param  None.
  * @retval theta_m3: the current rotation of Motor 3 in radians
  */
double calculatePositionMotor3( void )
{
    theta_m3 = (double)getCountsSensor3();
    theta_m3 = theta_m3*2.0*3.1416;
    theta_m3 = theta_m3/TOTAL_ENCODER_COUNTS_3;
    return theta_m3;
}

/*******************************************************************************
  * @name   calculatePositionMotor4
  * @brief  Calculates the rotation of Motor 4 in radians
  * @param  None.
  * @retval theta_m4: the current rotation of Motor 4 in radians
  */
double calculatePositionMotor4( void )
{
    theta_m4 = (double)getCountsSensor4();
    theta_m4 = theta_m4*2.0*3.1416;
    theta_m4 = theta_m4/TOTAL_ENCODER_COUNTS_4;
    return theta_m4;
}

/*******************************************************************************
  * @name   calculatePositionMotor5
  * @brief  Calculates the rotation of Motor 5 in radians
  * @param  None.
  * @retval theta_m5: the current rotation of Motor 5 in radians
  */
double calculatePositionMotor5( void )
{
    theta_m5 = (double)getCountsSensor5();
    theta_m5 = theta_m5*2.0*3.1416;
    theta_m5 = theta_m5/TOTAL_ENCODER_COUNTS_5;
    return theta_m5;
}

/*******************************************************************************
  * @name   calculatePositionMotor6
  * @brief  Calculates the rotation of Motor 6 in radians
  * @param  None.
  * @retval theta_m6: the current rotation of Motor 6 in radians
  */
double calculatePositionMotor6( void )
{
    theta_m6 = (double)getCountsSensor6();
    theta_m6 = theta_m6*2.0*3.1416;
    theta_m6 = theta_m6/TOTAL_ENCODER_COUNTS_6;
    return theta_m6;
}

/*******************************************************************************
  * @name   calculatePositionMotor7
  * @brief  Calculates the rotation of Motor 7 in radians
  * @param  None.
  * @retval theta_m7: the current rotation of Motor 7 in radians
  */
double calculatePositionMotor7( void )
{
    theta_m7 = (double)getCountsSensor7();
    theta_m7 = theta_m7*2.0*3.1416;
    theta_m7 = theta_m7/TOTAL_ENCODER_COUNTS_7;
    return theta_m7;
}



/*******************************************************************************
  * @name   calculatePosition1DOF
  * @brief  calculates the position of the 1DOF handle of Haplink in mm and  
  *         stores it in xH. It also caluclates the velocity of the 1DOF handle 
  *         in mm/s and stores it in dxH.
  * @param  None.
  * @retval None.
  */
void calculatePosition1DOF( void )
{
    static int velocitycounter = 0;
    double dxH_new = 0;
    int time_dif_int = 0;
    
    //theta_ma is the rotation angle of the motor in radians.
    theta_ma = calculatePositionMotor1();
    
     /*Calculate the positon of the handle xH as a function of the rotation
    of the handle theta_a*/
    
    /*Add code here:***********************************************************/
    /* Uncomment and fill the variables theta_a (the rotation of the paddle in radians)
    and xH (the arc length displacement of the padddle in mm)*/
    theta_a = -theta_ma*R_MA/R_A;
    xH = -R_HA*theta_a;
    /**************************************************************************/
    
    t1_pos = getTime_ms(); //t1_pos: time in ms since last call
    time_dif = t1_pos-t0_pos; //t0_pos: time in ms measured on previous call
    
    /*Add code here:***********************************************************/
    /*Calculate the velocity of the handle dxH you know of two different algorithms.
    Try them both, see which one generates a smoother response, and keep that one,
    This will require several lines of code which you should write below. 
    Remember to update the value of t0_pos, and the necessary variable if you
    decide to use a filter: xH_prev, dxH_prev. You can also try to use velocitycounter
    to not calculate a velocity sample at every loop. CountsSensor1Changed is
    a  variable which determines when the counts in the encoder have been updated.
    If you use it, remember to set it to 0 again when you are done.*/
    
    //dxH = ;//Some complicated function you will decide on
    /**************************************************************************/

    printDebug1DOFAllParameters();
}

/*******************************************************************************
  * @name   initPositionHandleAndJacobian
  * @brief  initializes the 2DOF position variables of Haplink
  * @param  None.
  * @retval None.
  */
void initPositionHandleAndJacobian( void )
{
    double tildetheta_a = 0;
    double tildetheta_b = 0;
    double px = 0;
    double py = 0;
    
    // Compute the angle of the paddles in radians
    theta_ma = -calculatePositionMotor1();
    theta_mb = -calculatePositionMotor2();
    
     /*Add code here:***********************************************************/
    
    
    /* Uncomment and fill the variables theta_a, tehta_b (the rotation of paddle's a and b in radians)
    and rx and ry */
    /*Add code here:***********************************************************/
    
    // Compute the angle of the paddles in radians
    //theta_a = +THETA_A_OFFSET_RAD; //some ratio of radiuses and theta_ma + the initial offset.
    //theta_b = +THETA_B_OFFSET_RAD;
    
  
    // Compute px and py 
    tildetheta_a = theta_a + DELTATHETA_A; 
    //px = ;
    //py = ;

    //Compute rx and ry in frame n
    tildetheta_b = theta_b + DELTATHETA_B; 
    //rx =  ;
    //ry =  ;
    
    /**************************************************************************/
    
    rx_prev =  rx;
    ry_prev =  ry;
    t0_pos = getTime_ms();
    
}

/*******************************************************************************
  * @name   calculatePositionHandleAndJacobian
  * @brief  calculates the 2DOF position variables of Haplink in mm.
  * @param  None.
  * @retval None.
  */
void calculatePositionHandleAndJacobian( void )
{
    static int velocityCounter = 0;
    double tildetheta_a = 0;
    double tildetheta_b = 0;
    double px = 0;
    double py = 0;
    
    
    // Compute the angle of the paddles in radians
    //motor angles:
    theta_ma = -calculatePositionMotor1();
    theta_mb = -calculatePositionMotor2();
    /* Uncomment and fill the variables theta_a, tehta_b (the rotation of paddle's a and b in radians)
    and rx and ry, as well as the velocity variables dx and dy */
    /*Add code here:***********************************************************/
    
    // Compute the angle of the paddles in radians
    //theta_a = +THETA_A_OFFSET_RAD; //some ratio of radiuses and theta_ma + the initial offset.
    //theta_b = +THETA_B_OFFSET_RAD;
    
  
    // Compute px and py 
    tildetheta_a = theta_a + DELTATHETA_A; 
    //px = ;
    //py = ;

    //Compute rx and ry in n
    tildetheta_b = theta_b + DELTATHETA_B; 
    //rx =  ;
    //ry =  ;
    
    //build the Jacobian
    //J00 = ;
    //J01 = ;
    //J10 = ;   
    //J11 = ;  
    
    //for dx and dy decide on your method and implement it, don't forget to reset
    //the velocity counter if that is what you are using and update t0_pos.
    t1_pos = getTime_ms();
}



/*--Functions to Access the various position variables------------------------*/

double getRx( void )
{
    return rx;
}

double getRy( void )
{ 
    return ry;
}

double getThetaA( void )
{
    return theta_a;
}
double getThetaB( void )
{
    return theta_b;
}
double getThetaADeg( void )
{
    return theta_a*180/3.1416;
}
double getThetaBDeg( void )
{
    return theta_b*180/3.1416;
}
double getXH( void )
{
    return xH;
}
double getXHPrev( void )
{
    return xH_prev;
}
double getDxH( void )
{
    return dxH;
}
double getDx( void )
{
    return dx;
}
double getDy( void )
{
    return dy;
}
double getTheta_ma( void )
{
    return theta_ma;    
}
double getTheta_mb( void )
{
    return theta_mb;
}
double getTheta_maDeg( void )
{
    return theta_ma*180/3.1416;    
}
double getTheta_mbDeg( void )
{
    return theta_mb*180/3.1416;
}
double getTimeDif( void )
{
    return time_dif;    
}
//EOF




