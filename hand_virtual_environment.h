/**
  ******************************************************************************
  * @file    hand_virtual_environment.h
  * @author  
  * @version 1.0
  * @date    April-2025
  * @brief   Hand virtual environment
  ******************************************************************************
  */
#ifndef __HAND_VIRTUAL_ENVIRONMENT_H_
#define __HAND_VIRTUAL_ENVIRONMENT_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"


/* Virtual Environments Constants */
// Obstacles
#define SPHERE1_X 0.0
#define SPHERE1_Y 0.0
#define SPHERE1_Z 35.0          // Yuichi recommendation is 110.0, Delta Z currently variable.
#define SPHERE1_RADIUS 50.0     // Delta Z should be XX per CAD, radius should be 

// Can feel on both with Z = 70, radius = 50
// Can feel on just F1 with Z = 35, radius = 50
// Can feel on just F2 with Z = 100, radius = 50

// Original values
//#define SPHERE1_Z 70.0          
//#define SPHERE1_RADIUS 20.0

// Values on 4/22
//#define SPHERE1_Z 10.0          
//#define SPHERE1_RADIUS 20.0

#define NORMAL_XF 122.73
#define NORMAL_YF -12.01
#define NORMAL_ZF1 45.41
#define NORMAL_ZF2 86.59

#define K_FINGERS 200.0

/* Virtual Environments Functions*/
void renderOutsideSphere( void );
double sphereDistance( double user_x, double user_y, double user_z );

double getSphereX( void );
double getSphereY( void );
double getSphereZ( void );
double getSphereRadius( void );

double getXf1_global( void );
double getYf1_global( void );
double getXf2_global( void );
double getYf2_global( void );

#ifdef __cplusplus
}
#endif


#endif  //__HAND_VIRTUAL_ENVIRONMENT_H_