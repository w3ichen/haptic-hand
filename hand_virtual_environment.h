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
#define SPHERE1_Z 70.0
#define SPHERE1_RADIUS 20.0

/* Virtual Environments Functions*/
void renderOutsideSphere( void );
double sphereDistance( double user_x, double user_y, double user_z );

double getSphereX( void );
double getSphereY( void );
double getSphereZ( void );
double getSphereRadius( void );



#ifdef __cplusplus
}
#endif


#endif  //__HAND_VIRTUAL_ENVIRONMENT_H_