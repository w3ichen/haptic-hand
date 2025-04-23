/**
  ******************************************************************************
  * @file    haplink_position.h 
  * @author  mortamar@andrew.cmu.edu
  * @version 3.0
  * @date    January-2022
  * @brief   Function definitions for calculating Haplink position.
             - Added Keil compatibility and Motor 3 functionality.
  ******************************************************************************
  */

#ifndef __HAPLINK_POSITION_H_
#define __HAPLINK_POSITION_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"

/******* Calibration Values ****/
//device values:
#define CX                      0.0       // center point x coordinate
#define CY                      0.0       // center point y coordinate
#define L_A                     65.0      //length of a linkage in mm
#define L_B                     55.0     //length of b linkage in mm
#define R_A                     35.0      // radius of Sector a in mm

#define R_B                     59.0      // radius of Sector b in mm
#define R_HA                    59.0      // radius of Handle A for Hapkit in mm
#define R_MA                    5.5       // radius of Motor a in mm
#define R_MB                    5.5       // radius of Motor b in mm
#define DELTATHETA_A_1            1.5708  //theta a offset in rad (-90deg)
#define DELTATHETA_B_1            -1.10935    //theta b offset in rad (63deg)

#define DELTATHETA_A_2            1.5708  //theta a offset in rad (90deg)
#define DELTATHETA_B_2            -1.10935    //theta b offset in rad (-63deg)

#define THETA_A_OFFSET_RAD      ((THETA_A_OFFSET*3.1416)/180)   //the theta A offset you want to start with in radians
#define THETA_B_OFFSET_RAD      ((THETA_B_OFFSET*3.1416)/180)   //the theta B offset you want to start with in radians

/******* Function prototypes ****/
int initHapticHand( void );

int initHaplinkPosition( void );

double calculatePositionMotor1( void );
double calculatePositionMotor2( void );
double calculatePositionMotor3( void );
double calculatePositionMotor4( void );
double calculatePositionMotor5( void );
double calculatePositionMotor6( void );
double calculatePositionMotor7( void );

void calculatePosition1DOF( void );
void initPositionHandleAndJacobian( void );
void calculatePositionHandleAndJacobian( void );

// finger funcs
void initPositionAndJacobianFinger1( void );
void calculatePositionAndJacobianFinger1( void );
void initPositionAndJacobianFinger2( void );
void calculatePositionAndJacobianFinger2( void );


double getRx( void );
double getRy( void) ;
// added for fingers 1 and 2
double getRx1( void );
double getRy1( void) ;
double getRx2( void );
double getRy2( void) ;
//
double getThetaA( void );
double getThetaB( void );
double getThetaADeg( void );
double getThetaBDeg( void );
double getThetaA1_deg( void );
double getThetaB1_deg( void );
double getThetaA2_deg( void );
double getThetaB2_deg( void );

double getXH( void );
double getDxH( void );
double getXHPrev( void );
double getDx( void );
double getDy( void );
double getTheta_ma( void );
double getTheta_mb( void );
double getTheta_maDeg( void );
double getTheta_mbDeg( void );
double getTimeDif( void );



#ifdef __cplusplus
}
#endif


#endif  //__HAPLINK_POSITION_H_