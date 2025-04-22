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
#define DELTA_BASE_RADIUS 31.2 // base radius - distance from origin to base joint
#define DELTA_END_EFFECTOR_RADIUS 25 // distance from platform's origin to platform joint
// Thetas that motors are positioned at
#define DELTA_THETA_N1 0.0
#define DELTA_THETA_N2 120.0 * PI / 180.0
#define DELTA_THETA_N3 240.0 * PI / 180.0
#define DELTA_LOWER_LINK_LEN 30.0
#define DELTA_UPPER_LINK_LEN 60.0

#define DELTA_THETA_OFFSET  (18.1) * PI / 180.0

// P = platform, B = base
#define DELTA_WP 7.22 // end effector origin to edge perpendicular
#define DELTA_UP 14.43 // end effector origin to corner
#define DELTA_WB 35.0  // base origin to edge perpendicular
#define DELTA_UB 70.0  // base origin to corner
#define DELTA_SP 25.0  // edge length of end effector
#define DELTA_SB 121.24 // edge length of base


// HAPTIC CONSTANTS
#define K_DELTA_THUMB 1.0

/******* Calibration Values ****/
typedef struct {
    double t1;
    double t2;
    double t3;
    double x0;
    double y0;
    double z0;
    double rMax;
    double zMin;
    double zMax;
    double e;     // end effector
    double f;     // base
    double re;
    double rf;
    double sqrt3;
    double pi;    // PI
    double sin120;
    double cos120;
    double tan60;
    double sin30;
    double tan30;
} DeltaThumb;

// External variables
extern double deltaThumbX;
extern double deltaThumbY;
extern double deltaThumbZ;


/******* Function prototypes ****/
void deltaThumbHandler( void );
void setAndMaintainMotorAngle(int motorNumber, double targetAngleDeg);
void initDeltaThumb();
float getThumbX( void ), getThumbY( void ), getThumbZ( void );

// Haptic Mouse functions ////////////////////
void GetElbowPosition (double *x1, double *y1, double *z1,
                       double *x2, double *y2, double *z2, 
                       double *x3, double *y3, double *z3,
                       double *x, double *y, double *z,
                       double *theta_a1, double *theta_a2, double *theta_a3);
void GetThetaii (double *theta1_1, double *theta1_2, double *theta1_3, 
                 double *theta2_1, double *theta2_2, double *theta2_3,
                 double *theta3_1, double *theta3_2, double *theta3_3);

void DeltaThumbGetJacobian (double *J11, double *J12, double *J13, 
                            double *J21, double *J22, double *J23, 
                            double *J31, double *J32, double *J33);
void DeltaThumbGetJacobian_OhioVersion (double *J11, double *J12, double *J13, 
                                        double *J21, double *J22, double *J23, 
                                        double *J31, double *J32, double *J33);

                                        
void ForceApp (void);
// End Haptic Mouse functions ////////////////////

// DeltaZ functions ////////////////////
void goHome();
void goTo(double x, double y, double z);
void goToAngle(int angle1, int angle2, int angle3);
int delta_calcAngleYZ(double x0, double y0, double z0, double *theta);
int delta_calcInverse(double x0, double y0, double z0, double *theta1, double *theta2, double *theta3);
int delta_calcForward(double theta1, double theta2, double theta3, double *x0, double *y0, double *z0);
void reportPosition();
void reportAngles();
int testInWorkspace(double x, double y, double z);
void setupMotors(int pin1,int pin2, int pin3);
// End DeltaZ functions ////////////////////



#ifdef __cplusplus
}
#endif


#endif  //__DELTA_THUMB_H_