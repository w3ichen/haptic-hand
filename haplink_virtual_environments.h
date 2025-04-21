/**
  ******************************************************************************
  * @file    haplink_virtual_environments.h
  * @author  mortamar@andrew.cmu.edu
  * @version 3.0
  * @date    January-2022
  * @brief   virtual environments function prototypes for 1 and 2-DOF
  ******************************************************************************
  */
#ifndef __HAPLINK_VIRTUAL_ENVIRONMENTS_H_
#define __HAPLINK_VIRTUAL_ENVIRONMENTS_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"


/* Virtual Environments Constants */

/* For 1DOF */
//Constant for rendering a Spring  
    #define K_SPRING       500.0            //Spring constant in N/m
//Constant for rendering linear damping
    #define B_LINEAR       0.0              //Linear damping in N*s/m
//Constants for virtual wall
    #define X_WALL          0.0             //Position of the virtual wall in mm
    #define K_WALL          0.0             //Maximum stiffness of the virtual Wall in N/m
    #define B_WALL_1        0.0             // will you use damping in your wall?
//Constants for nonlinear damping
    #define B_NONLINEAR     0.0             //Nonlinear damping in N*s/m
    #define DXH_THRESHOLD   0.0             //Velocity threshold in mm/s
    #define B_SCALING       0.0             //Scaling of the nonlinear damping
//Constants for Texture
    #define TEXTURE_SPATIAL_FREQUENCY 0.0   //Spatial Frequency of texture rendering: 1/16 
    #define TEXTURE_DAMPING           0.0   //Damping for texture rendering
//Constants for Texture 2
    #define TEXTURE_SPATIAL_FREQUENCY_2 (0.0) //Spatial Frequency of texture rendering: number of bumps divided by range
    #define TEXTURE_K_2           0.0         //Stiffness for texture rendering

#define M_PI  3.1416

/* For 2-DOF */
//Constants for rendering being inside of a box
    #define KCircle         0.0 //stiffness of walls of circle
    #define BCircle         0.0 //damping of walls of circle (if necessary)
    #define RCircle         0.0 //Radius of the circle in mm
    #define CCircleX        0.0 //x coordinate of the center point of the circle in mm
    #define CCircleY        0.0 // y coordinate of the center point of the circle in mm
//Constants for rendering being outside of a circle
    #define KCircle2         0.0 
    #define BCircle2         0.0
    #define RCircle2         0.0 //Radius of the circle in mm
    #define CCircleX2        0.0 //x coordinate of the center point of the circle in mm
    #define CCircleY2        0.0 // y coordinate of the center point of the circle in mm  
//Constants for rendering a floor
    #define K_WALL_FLOOR      0.0
    #define WALL_Y_FLOOR      0.0   


/* Virtual Environments Functions*/


double getForceH( void );
double getTorqueMotor1( void );
//2DOF


void renderOutsideCircle2DOF_M1M2( void );
void renderOutsideCircle2DOF_M4M5( void );
void renderOutsideCircle2DOF_M6M7( void );

int renderOutsideBox2DOF( void );

double getProxyX( void );
double getProxyY( void );
double getForceX( void );
double getForceY( void );

double getTorqueMotor2( void );
double getTorqueMotor3( void );
double getTorqueMotor4( void );
double getTorqueMotor5( void );
double getTorqueMotor6( void );
double getTorqueMotor7( void );
#ifdef __cplusplus
}
#endif


#endif  //__HAPLINK_VIRTUAL_ENVIRONMENTS_H_