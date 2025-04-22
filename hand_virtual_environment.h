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
#define SPHERE1_Z 60.0          // Yuichi recommendation is 110.0, Delta Z currently variable.
#define SPHERE1_RADIUS 10.0     // Delta Z should be XX per CAD, radius should be 

// Original values
//#define SPHERE1_Z 60.0          
//#define SPHERE1_RADIUS 10.0

#define NORMAL_XF 122.73
#define NORMAL_YF -12.01
#define NORMAL_ZF1 45.41
#define NORMAL_ZF2 86.59

#define K_FINGERS 100.0

/* Virtual Environments Functions*/
void renderOutsideSphere( void );
double sphereDistance( double user_x, double user_y, double user_z );




#ifdef __cplusplus
}
#endif


#endif  //__HAND_VIRTUAL_ENVIRONMENT_H_