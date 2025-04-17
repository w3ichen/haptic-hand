/**
  ******************************************************************************
  * @file    delta_thumb.h 
  * @author  
  * @version 
  * @date    April-2025
  * @brief   Delta mechanism thumb
  ******************************************************************************
  */

#ifndef __DELTA_THUMB_H_
#define __DELTA_THUMB_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"

// MATH
#define PI 3.14159265358979323846
#define DEG_TO_RAD(degrees) ((degrees) * (PI / 180.0))
#define RAD_TO_DEG(radians) ((radians) * (180.0 / PI))

// DELTA DEVICE CONSTANTS
#define DELTA_THUMB_THETA_OFFSET (12.5) * PI / 180.0
#define DELTA_dA 17.0 // distance from origin to base joint
#define DELTA_dc 8.0 // distance from platform's origin to platform joint
#define DELTA_THETA_N1 0.0
#define DELTA_THETA_N2 120.0 * PI / 180.0
#define DELTA_THETA_N3 240.0 * PI / 180.0
#define DELTA_LINK_LEN 20.0
#define DELTA_LINK_LEN_2 32.0


// HAPTIC CONSTANTS
#define K_DELTA_THUMB 20.0

/******* Calibration Values ****/
typedef struct {
    float t1;
    float t2;
    float t3;
    float x0;
    float y0;
    float z0;
    float rMax;
    float zMin;
    float zMax;
    float e;     // end effector
    float f;     // base
    float re;
    float rf;
    float sqrt3;
    float pi;    // PI
    float sin120;
    float cos120;
    float tan60;
    float sin30;
    float tan30;
} DeltaThumb;

// External variables
extern float deltaThumbX;
extern float deltaThumbY;
extern float deltaThumbZ;


/******* Function prototypes ****/
void deltaThumbHandler( void );
void setAndMaintainMotorAngle(int motorNumber, float targetAngleDeg);
float getThumbX( void ), getThumbY( void ), getThumbZ( void );

void DeltaThumbGetJacobian (double *J11, double *J12, double *J13, 
                            double *J21, double *J22, double *J23, 
                            double *J31, double *J32, double *J33);
void initDeltaThumb();
void goHome();
void goTo(float x, float y, float z);
void goToAngle(int angle1, int angle2, int angle3);
int delta_calcAngleYZ(float x0, float y0, float z0, float *theta);
int delta_calcInverse(float x0, float y0, float z0, float *theta1, float *theta2, float *theta3);
int delta_calcForward(float theta1, float theta2, float theta3, float *x0, float *y0, float *z0);
void reportPosition();
void reportAngles();

int testInWorkspace(float x, float y, float z);
void setupMotors(int pin1,int pin2, int pin3);



#ifdef __cplusplus
}
#endif


#endif  //__DELTA_THUMB_H_