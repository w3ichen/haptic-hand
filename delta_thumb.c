/**
  ******************************************************************************
  * @file    delta_thumb.cpp
  * @date    April-2025
  * @brief   Delta thumb mechanism based on code from https://github.com/alvaresc/DeltaZ/blob/main/Arduino/DeltaZ_communication/DeltaRobot.cpp
  * NOTE: DeltaZ code operates in degrees!
  ******************************************************************************
  */

#include "delta_thumb.h"
#include "haplink_position.h"
#include "haplink_motors.h"
#include <math.h> // For sqrt
#include "delta_thumb.h"

// Global vars
DeltaThumb deltaThumb;


float deltaThumbX;
float deltaThumbY;
float deltaThumbZ;
double ThetaMotor1Rad;
double ThetaMotor2Rad;
double ThetaMotor3Rad;
double ThetaMotor1Deg;
double ThetaMotor2Deg;
double ThetaMotor3Deg;


/*******************************************************************************
  * @name   deltaThumbHandler
  * @brief  initialize the delta mechanism thumb
  * @param  None.
  * @retval None.
  ******************************************************************************
  */
void deltaThumbHandler( void )
{
    // Read encoders    
    ThetaMotor1Rad = calculatePositionMotor1();
    ThetaMotor2Rad = calculatePositionMotor2();
    ThetaMotor3Rad = calculatePositionMotor3();
    // Convert radians to degrees
    ThetaMotor1Deg = RAD_TO_DEG(ThetaMotor1Rad);
    ThetaMotor2Deg = RAD_TO_DEG(ThetaMotor2Rad);
    ThetaMotor3Deg = RAD_TO_DEG(ThetaMotor3Rad);

    // Output forces
    double ForceMotor1 = 0.0;
    double TorqueMotor1 = -((R_MA/R_A) * R_HA) * ForceMotor1;
    TorqueMotor1 = TorqueMotor1*0.001; //convert units
    outputTorqueMotor1(TorqueMotor1);    

    double ForceMotor2 = 0.0;
    double TorqueMotor2 = -((R_MA/R_A) * R_HA) * ForceMotor2;
    TorqueMotor2 = TorqueMotor2*0.001; //convert units
    outputTorqueMotor2(TorqueMotor2);    

    double ForceMotor3 = 0.0;
    double TorqueMotor3 = -((R_MA/R_A) * R_HA) * ForceMotor3;
    TorqueMotor3 = TorqueMotor3*0.001; //convert units

    outputTorqueMotor3(TorqueMotor3);    

    // Update x,y,z positions of end-effector
    delta_calcForward(ThetaMotor1Deg, ThetaMotor2Deg, ThetaMotor3Deg, &deltaThumbX, &deltaThumbY, &deltaThumbZ);


    goHome();


    // Print values
    printf("theta1=%f, theta2=%f, theta3=%f, thumbX=%f, thumbY=%f, thumbZ=%f\n", ThetaMotor1Deg, ThetaMotor2Deg, ThetaMotor3Deg, deltaThumbX, deltaThumbY, deltaThumbZ);
}



/**
 * @name   setAndMaintainMotorAngle
 * @brief  Sets a motor to a specific angle and maintains it using PID control
 * @param  motorNumber: Which motor to control (1, 2, or 3)
 * @param  targetAngleDeg: The target angle in degrees
 * @retval None.
 */
void setAndMaintainMotorAngle(int motorNumber, float targetAngleDeg) {
    static float errorIntegral1 = 0.0;
    static float errorIntegral2 = 0.0;
    static float errorIntegral3 = 0.0;
    static float prevError1 = 0.0;
    static float prevError2 = 0.0;
    static float prevError3 = 0.0;
    
    // PID coefficients - adjust these values based on system response
    const float kp = 0.05;  // Proportional gain
    const float ki = 0.001; // Integral gain
    const float kd = 0.01;  // Derivative gain
    
    // Maximum integral value to prevent windup
    const float maxIntegral = 50.0;
    
    float currentAngleDeg = 0.0;
    float error = 0.0;
    float errorDerivative = 0.0;
    float *errorIntegralPtr = NULL;
    float *prevErrorPtr = NULL;
    float torque = 0.0;
    
    // Use the global angle variables based on motor number
    switch(motorNumber) {
        case 1:
            currentAngleDeg = ThetaMotor1Deg;
            errorIntegralPtr = &errorIntegral1;
            prevErrorPtr = &prevError1;
            break;
        case 2:
            currentAngleDeg = ThetaMotor2Deg;
            errorIntegralPtr = &errorIntegral2;
            prevErrorPtr = &prevError2;
            break;
        case 3:
            currentAngleDeg = ThetaMotor3Deg;
            errorIntegralPtr = &errorIntegral3;
            prevErrorPtr = &prevError3;
            break;
        default:
            printf("Invalid motor number!\n");
            return; // Invalid motor number
    }
    
    // Calculate error
    error = targetAngleDeg - currentAngleDeg;
    
    // Calculate error integral with anti-windup
    *errorIntegralPtr += error;
    if (*errorIntegralPtr > maxIntegral) {
        *errorIntegralPtr = maxIntegral; // Cap + value
    } else if (*errorIntegralPtr < -maxIntegral) {
        *errorIntegralPtr = -maxIntegral; // Cap - value
    }
    
    // Calculate error derivative
    errorDerivative = error - *prevErrorPtr;
    *prevErrorPtr = error;
    
    // Calculate torque using PID formula
    torque = kp * error + ki * (*errorIntegralPtr) + kd * errorDerivative;
    
    // Apply torque to motor
    switch(motorNumber) {
        case 1:
            outputTorqueMotor1(torque);
            break;
        case 2:
            outputTorqueMotor2(torque);
            break;
        case 3:
            outputTorqueMotor3(torque);
            break;
    }
}


/*******************************************************************************************************************************************/
// START DeltaZ code
// Modified version of https://github.com/alvaresc/DeltaZ/blob/main/Arduino/DeltaZ_communication/DeltaRobot.cpp
// NOTE: DeltaZ code operates in degrees!
/*******************************************************************************************************************************************/


void initDeltaThumb() {
  // Inits delta vars
  deltaThumb.e = 25;     // end effector
  deltaThumb.f = 50;     // base
  deltaThumb.re = 60.0;
  deltaThumb.rf = 30.0;
  deltaThumb.sqrt3 = sqrt(3.0);
  deltaThumb.pi = 3.141592653;    // PI
  deltaThumb.sin120 = deltaThumb.sqrt3 / 2.0;
  deltaThumb.cos120 = -0.5;
  deltaThumb.tan60 = deltaThumb.sqrt3;
  deltaThumb.sin30 = 0.5;
  deltaThumb.tan30 = 1.0 / deltaThumb.sqrt3;
  deltaThumb.rMax = 30;
  deltaThumb.zMin = -75;
  deltaThumb.zMax = -35;

  deltaThumbX = 0;
  deltaThumbY = 0;
  deltaThumbZ = 0;
}

void goHome() {
  /* Delta will go to its home position (x,y,z) = (0,0,-47.06) where all joint angles are zero. The robot will report its joint angles to the serial monitor*/
  goToAngle(0,0,0);
  reportAngles();
}

void goTo(float x, float y, float z) {
  /* Inputs the target position, (x,y,z). First, this function tests if the target position is in the workspace. 
   If so, it calculates the inverse kineamtics, moves the robot to that position. It not, the robot reports that it isnt in the workspace.
   Finally, the robot reports its current joint angles.*/
  int inWorkspace = testInWorkspace(x, y, z);

  if (inWorkspace){
    deltaThumb.x0 = x;
    deltaThumb.y0 = y;
    deltaThumb.z0 = z;
    delta_calcInverse(deltaThumb.x0, deltaThumb.y0, deltaThumb.z0, &deltaThumb.t1, &deltaThumb.t2, &deltaThumb.t3);

    // Set the angles
    setAndMaintainMotorAngle(MOTOR_1, -deltaThumb.t1 + 90);
    setAndMaintainMotorAngle(MOTOR_2, -deltaThumb.t2 + 90);
    setAndMaintainMotorAngle(MOTOR_3, -deltaThumb.t3 + 90);  
  } else {
    printf("NOT IN WORKSPACE");
  }
  reportAngles();
}

int testInWorkspace(float x, float y, float z) {
  /* inputs target x,y, and z position. Tests if the position if the position is in the current worksapce of the robot (set by rMax, zMin, and zMax.
  If the point is in the workspace, return 1, else return 0*/
  float r = sqrt(x * x + y * y);
  if ((r <= deltaThumb.rMax) && (z <= deltaThumb.zMax) && (z >= deltaThumb.zMin)) {
    return 1;
  } else {
    return 0;
  }
}

void reportPosition(){
  /* Report the curent position of the robot*/
//    printf("ATPOS %.2f %.2f %.2f\n", deltaThumb.x0, deltaThumb.y0, deltaThumb.z0);
}

void reportAngles(){
  /* Report the current position of the robot*/
    // printf("ATANG %f %f %f\n", deltaThumb.t1, deltaThumb.t2, deltaThumb.t3);
}

void goToAngle(int angle1, int angle2, int angle3) {
  /* inputs angles angle1-3. Claculates forward kineamtics and tests if position is in the workspace. If so, the robot goes to those angles. 
   *  If not, the root reports that it is not in the workspace. Then, report the position of the robot. */
  float x0Old = deltaThumb.x0;
  float y0Old = deltaThumb.y0;
  float z0Old = deltaThumb.z0;

  delta_calcForward(angle1, angle2, angle3, &deltaThumb.x0, &deltaThumb.y0, &deltaThumb.z0);
  /* Visit https://hypertriangle.com/~alex/delta-robot-tutorial/ for more information*/
  int inWorkspace = testInWorkspace(deltaThumb.x0, deltaThumb.y0, deltaThumb.z0);
  if (inWorkspace){
    deltaThumb.t1 = angle1;
    deltaThumb.t2 = angle2;
    deltaThumb.t3 = angle3;

    // Set the angles
    setAndMaintainMotorAngle(MOTOR_1, -deltaThumb.t1 + 90);
    setAndMaintainMotorAngle(MOTOR_2, -deltaThumb.t2 + 90);
    setAndMaintainMotorAngle(MOTOR_3, -deltaThumb.t3 + 90);  
  } else {
    printf("NOT IN WORKSPACE");
    deltaThumb.x0 = x0Old;
    deltaThumb.y0 = y0Old;
    deltaThumb.z0 = z0Old;
  }
  reportPosition();
}

int delta_calcAngleYZ(float x0, float y0, float z0, float *theta) {
  /* Visit https://hypertriangle.com/~alex/delta-robot-tutorial/ for more information*/
  float y1 = -0.5 * 0.57735 * deltaThumb.f; // f/2 * tg 30
  //float y1 = yy1;
  y0 -= 0.5 * 0.57735 * deltaThumb.e;    // shift center to edge
  // z = a + b*y
  float a = (x0 * x0 + y0 * y0 + z0 * z0 + deltaThumb.rf * deltaThumb.rf - deltaThumb.re * deltaThumb.re - y1 * y1) / (2 * z0);
  float b = (y1 - y0) / z0;
  // discriminant
  float d = -(a + b * y1) * (a + b * y1) + deltaThumb.rf * (b * b * deltaThumb.rf + deltaThumb.rf);
  if (d < 0) return -1; // non-existing point
  float yj = (y1 - a * b - sqrt(d)) / (b * b + 1); // choosing outer point
  float zj = a + b * yj;
  *theta = 180.0 * atan(-zj / (y1 - yj)) / deltaThumb.pi + ((yj > y1) ? 180.0 : 0.0);
  if ((*theta < -180) || (*theta > 180))
    return -1;
  return 0;
}


/**
 * Given xyz coordinates, calculates angles
 * @param x0
 * @param y0
 * @param z0
 * @return theta1, theta2, theta3
 */
int delta_calcInverse(float x0, float y0, float z0, float *theta1, float *theta2, float *theta3) {
  /* Visit https://hypertriangle.com/~alex/delta-robot-tutorial/ for more information*/
  *theta1 = 0;
  *theta2 = 0;
  *theta3 = 0;
  int stat1 = delta_calcAngleYZ(x0, y0, z0, theta1);
  int stat2 = delta_calcAngleYZ(x0 * deltaThumb.cos120 + y0 * deltaThumb.sin120, y0 * deltaThumb.cos120 - x0 * deltaThumb.sin120, z0, theta2); // rotate coords to +120 deg
  int stat3 = delta_calcAngleYZ(x0 * deltaThumb.cos120 - y0 * deltaThumb.sin120, y0 * deltaThumb.cos120 + x0 * deltaThumb.sin120, z0, theta3); // rotate coords to -120 deg
  return stat1 + stat2 + stat3;
}

/**
 * Given angles, calculates x,y,z position of end effector
 * @param theta1
 * @param theta2
 * @param theta3
 * @return x0, y0, z0
 */
int delta_calcForward(float theta1, float theta2, float theta3, float *x0, float *y0, float *z0) {
  /* Visit https://hypertriangle.com/~alex/delta-robot-tutorial/ for more information*/
  float t = (deltaThumb.f - deltaThumb.e) * deltaThumb.tan30 / 2;
  float dtr = deltaThumb.pi / (float)180.0;

  theta1 *= dtr;
  theta2 *= dtr;
  theta3 *= dtr;

  float y1 = -(t + deltaThumb.rf * cos(theta1));
  float z1 = -deltaThumb.rf * sin(theta1);

  float y2 = (t + deltaThumb.rf * cos(theta2)) * deltaThumb.sin30;
  float x2 = y2 * deltaThumb.tan60;
  float z2 = -deltaThumb.rf * sin(theta2);

  float y3 = (t + deltaThumb.rf * cos(theta3)) * deltaThumb.sin30;
  float x3 = -y3 * deltaThumb.tan60;
  float z3 = -deltaThumb.rf * sin(theta3);

  float dnm = (y2 - y1) * x3 - (y3 - y1) * x2;

  float w1 = y1 * y1 + z1 * z1;
  float w2 = x2 * x2 + y2 * y2 + z2 * z2;
  float w3 = x3 * x3 + y3 * y3 + z3 * z3;

  // x = (a1*z + b1)/dnm
  float a1 = (z2 - z1) * (y3 - y1) - (z3 - z1) * (y2 - y1);
  float b1 = -((w2 - w1) * (y3 - y1) - (w3 - w1) * (y2 - y1)) / 2.0;

  // y = (a2*z + b2)/dnm;
  float a2 = -(z2 - z1) * x3 + (z3 - z1) * x2;
  float b2 = ((w2 - w1) * x3 - (w3 - w1) * x2) / 2.0;

  // a*z^2 + b*z + c = 0
  float a = a1 * a1 + a2 * a2 + dnm * dnm;
  float b = 2 * (a1 * b1 + a2 * (b2 - y1 * dnm) - z1 * dnm * dnm);
  float c = (b2 - y1 * dnm) * (b2 - y1 * dnm) + b1 * b1 + dnm * dnm * (z1 * z1 - deltaThumb.re * deltaThumb.re);

  // discriminant
  float d = b * b - (float)4.0 * a * c;
  if (d < 0) return -1; // non-existing point
  
  *z0 = -(float)0.5 * (b + sqrt(d)) / a;
  *x0 = (a1 * *z0 + b1) / dnm;
  *y0 = (a2 * *z0 + b2) / dnm;
  return 0;
}

/*******************************************************************************************************************************************/
// END DeltaZ Code
/*******************************************************************************************************************************************/
