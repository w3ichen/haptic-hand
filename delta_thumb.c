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
#include "haplink_encoders.h"
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


float getThumbX( void ) {
    return deltaThumbX;
}
float getThumbY( void ) {
    return deltaThumbY;
}
float getThumbZ( void ) {
    return deltaThumbZ;
}

/*******************************************************************************
  * @name   deltaThumbHandler
  * @brief  runs every time to keep the delta thumb variables up to date!
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

    // // Output forces
    // double ForceMotor1 = 0.0;
    // double TorqueMotor1 = -((R_MA/R_A) * R_HA) * ForceMotor1;
    // TorqueMotor1 = TorqueMotor1*0.001; //convert units
    // outputTorqueMotor1(TorqueMotor1);    

    // double ForceMotor2 = 0.0;
    // double TorqueMotor2 = -((R_MA/R_A) * R_HA) * ForceMotor2;
    // TorqueMotor2 = TorqueMotor2*0.001; //convert units
    // outputTorqueMotor2(TorqueMotor2);    

    // double ForceMotor3 = 0.0;
    // double TorqueMotor3 = -((R_MA/R_A) * R_HA) * ForceMotor3;
    // TorqueMotor3 = TorqueMotor3*0.001; //convert units
    // outputTorqueMotor3(TorqueMotor3);    


    // goHome();
    // goTo(x, y, z); 

    // Update x,y,z positions of end-effector
    delta_calcForward(ThetaMotor1Deg, ThetaMotor2Deg, ThetaMotor3Deg, &deltaThumbX, &deltaThumbY, &deltaThumbZ);

    // goHome();

    // Print values
    // printf("theta1=%f, theta2=%f, theta3=%f, thumbX=%f, thumbY=%f, thumbZ=%f\n", ThetaMotor1Deg, ThetaMotor2Deg, ThetaMotor3Deg, deltaThumbX, deltaThumbY, deltaThumbZ);
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


/*******************************************************************************************************************************************/
// START Haptic mouse code
// Code from Michael Han <woongseh@andrew.cmu.edu>
/*******************************************************************************************************************************************/

void MotorAngle (double *theta_a1, double *theta_a2, double *theta_a3)
{
    int32_t count1 = (double)getCountsSensor1();
    *theta_a1 = -(count1  * (2.0 * PI / 2048.0) - DELTA_THUMB_THETA_OFFSET);
    int32_t count2 = (double)getCountsSensor2();
    *theta_a2 = -(count2  * (2.0 * PI / 2048.0) - DELTA_THUMB_THETA_OFFSET);
    int32_t count3 = (double)getCountsSensor3();
    *theta_a3 = -(count3  * (2.0 * PI / 2048.0) - DELTA_THUMB_THETA_OFFSET);
}

void GetElbowPosition (double *x1, double *y1, double *z1,
                       double *x2, double *y2, double *z2, 
                       double *x3, double *y3, double *z3,
                       double *x, double *y, double *z,
                       double *theta_a1, double *theta_a2, double *theta_a3)
{
    MotorAngle(theta_a1, theta_a2, theta_a3);
    double dAprime = DELTA_dA - DELTA_dc;

    // elbow position for 1
    *x1 = sin(DELTA_THETA_N1) * (dAprime + DELTA_LINK_LEN * cos(*theta_a1));
    *y1 = cos(DELTA_THETA_N1) * (-dAprime - DELTA_LINK_LEN * cos(*theta_a1));
    *z1 = DELTA_LINK_LEN * sin(*theta_a1);

    // elbow position for 2
    *x2 = sin(DELTA_THETA_N2) * (dAprime + DELTA_LINK_LEN * cos(*theta_a2));
    *y2 = cos(DELTA_THETA_N2) * (-dAprime - DELTA_LINK_LEN * cos(*theta_a2));
    *z2 = DELTA_LINK_LEN * sin(*theta_a2);

    // elbow position for 3
    *x3 = sin(DELTA_THETA_N3) * (dAprime + DELTA_LINK_LEN * cos(*theta_a3));
    *y3 = cos(DELTA_THETA_N3) * (-dAprime - DELTA_LINK_LEN * cos(*theta_a3));
    *z3 = DELTA_LINK_LEN * sin(*theta_a3);

    double w1 = pow(*y1, 2) + pow(*z1, 2);
    double w2 = pow(*x2, 2) + pow(*y2, 2) + pow(*z2, 2);
    double w3 = pow(*x3, 2) + pow(*y3, 2) + pow(*z3, 2);

    double d = (*y2 - *y1) * (*x3) - (*y3 - *y1) * (*x2);

    double a1 = ((*y3 - *y1) * (*z2 - *z1) - (*y2 - *y1) * (*z3 - *z1)) / d;
    double b1 = ((*y2 - *y1) * (w3 - w1) - (*y3 - *y1) * (w2 - w1)) / (2 * d);
    double a2 = ((*z3 - *z1) * (*x2) - (*z2 - *z1) * (*x3)) / d;
    double b2 = ((w2 - w1) * (*x3) - (w3 - w1) * (*x2)) / (2 * d);

    //if (r == 0) //on initial run
    //{
    //    r = DELTA_LINK_LEN_2;
    //}
    //else {
    //    r = sqrt(pow((x - x1), 2) + pow((y - y1), 2) + pow((z - z1), 2));
    //}

    double r = DELTA_LINK_LEN_2;

    double A = pow(a1, 2) + pow(a2, 2) + 1;
    double B = 2 * (a1 * b1 + a2 * (b2 - *y1) - *z1);

    double C = pow(b1, 2) + pow((b2 - *y1), 2) + pow(*z1, 2) - pow(r, 2);

    *z = (- B + sqrt(pow(B, 2) - 4.0 * A * C)) / (2.0 * A); // one being used
    if (*z < 0)
    {
        *z = (- B - sqrt(pow(B, 2) - 4.0 * A * C)) / (2.0 * A);
    }
    *x = a1 * (*z) + b1;
    *y = a2 * (*z) + b2;
}

void GetThetaii (double *theta1_1, double *theta1_2, double *theta1_3, 
                 double *theta2_1, double *theta2_2, double *theta2_3,
                 double *theta3_1, double *theta3_2, double *theta3_3)
{
    double x1, y1, z1, x2, y2, z2, x3, y3, z3, x, y, z;
    double theta_a1, theta_a2, theta_a3;
    GetElbowPosition(&x1, &y1, &z1, &x2, &y2, &z2, &x3, &y3, &z3, &x, &y, &z, &theta_a1, &theta_a2, &theta_a3);

    // variable declaration
    double Ax1 = DELTA_dA * cos(270.0 * PI / 180.0);
    double Ay1 = DELTA_dA * sin(270.0 * PI / 180.0);
    double Az1 = 0;
    double Ax2 = DELTA_dA * cos(30.0 * PI / 180.0) * cos(DELTA_THETA_N2) + DELTA_dA * sin(30.0 * PI / 180.0) * sin(DELTA_THETA_N2);
    double Ay2 = - DELTA_dA * cos(30.0 * PI / 180.0) * sin(DELTA_THETA_N2) + DELTA_dA * sin(30.0 * PI / 180.0) * cos(DELTA_THETA_N2);
    double Az2 = 0;
    double Ax3 = DELTA_dA * cos(150.0 * PI / 180.0) * cos(DELTA_THETA_N3) + DELTA_dA * sin(150.0 * PI / 180.0) * sin(DELTA_THETA_N3);
    double Ay3 = - DELTA_dA * cos(150.0 * PI / 180.0) * sin(DELTA_THETA_N3) + DELTA_dA * sin(150.0 * PI / 180.0) * cos(DELTA_THETA_N3);
    double Az3 = 0;
    // Base joint position
    double Bx1 = x1;
    double By1 = y1;
    double Bz1 = z1;
    double Bx2 = x2 * cos(DELTA_THETA_N2) + y2 * sin(DELTA_THETA_N2); 
    double By2 = - x2 * sin(DELTA_THETA_N2) + y2 * cos(DELTA_THETA_N2); 
    double Bz2 = z2; 
    double Bx3 = x3 * cos(DELTA_THETA_N3) + y3 * sin(DELTA_THETA_N3); 
    double By3 = - x3 * sin(DELTA_THETA_N3) + y3 * cos(DELTA_THETA_N3); 
    double Bz3 = z3; 
    // Endeffector position
    double Cx1 = x;
    double Cy1 = y;
    double Cz1 = z;
    double Cx2 = x * cos(DELTA_THETA_N2) + y * sin(DELTA_THETA_N2);
    double Cy2 = - x * sin(DELTA_THETA_N2) + y * cos(DELTA_THETA_N2);
    double Cz2 = z;
    double Cx3 = x * cos(DELTA_THETA_N3) + y * sin(DELTA_THETA_N3);
    double Cy3 = - x * sin(DELTA_THETA_N3) + y * cos(DELTA_THETA_N3);
    double Cz3 = z;
    // Theta3i & theta2i
    double Distance1 = sqrt(pow(Ax1 - Cx1, 2) + pow(Ay1 - Cy1, 2) + pow(Az1 - Cz1, 2));
    double Distance2 = sqrt(pow(Ax2 - Cx2, 2) + pow(Ay2 - Cy2, 2) + pow(Az2 - Cz2, 2));
    double Distance3 = sqrt(pow(Ax3 - Cx3, 2) + pow(Ay3 - Cy3, 2) + pow(Az3 - Cz3, 2));

    *theta1_1 = theta_a1;
    *theta1_2 = theta_a2;
    *theta1_3 = theta_a3;
    *theta3_1 = fmod(PI + atan((Cz1 - Bz1) / (Cx1 - Bx1)), PI);
    *theta3_2 = fmod(PI + atan((Cz2 - Bz2) / (Cx2 - Bx2)), PI);
    *theta3_3 = fmod(PI + atan((Cz3 - Bz3) / (Cx3 - Bx3)), PI);
    *theta2_1 = PI - acos(-(pow(Distance1,2) - pow(DELTA_LINK_LEN, 2) - pow((DELTA_LINK_LEN_2 * sin(*theta3_1)),2)) / (2 * DELTA_LINK_LEN * DELTA_LINK_LEN_2 * sin(*theta3_1)));
    *theta2_2 = PI - acos(-(pow(Distance2,2) - pow(DELTA_LINK_LEN, 2) - pow((DELTA_LINK_LEN_2 * sin(*theta3_2)),2)) / (2 * DELTA_LINK_LEN * DELTA_LINK_LEN_2 * sin(*theta3_2)));
    *theta2_3 = PI - acos(-(pow(Distance3,2) - pow(DELTA_LINK_LEN, 2) - pow((DELTA_LINK_LEN_2 * sin(*theta3_3)),2)) / (2 * DELTA_LINK_LEN * DELTA_LINK_LEN_2 * sin(*theta3_3)));
}

void DeltaThumbGetJacobian (double *J11, double *J12, double *J13, 
                            double *J21, double *J22, double *J23, 
                            double *J31, double *J32, double *J33)
{
    double theta1_1, theta1_2, theta1_3, theta2_1, theta2_2, theta2_3, theta3_1, theta3_2, theta3_3;

    GetThetaii(&theta1_1, &theta1_2, &theta1_3, 
               &theta2_1, &theta2_2, &theta2_3,
               &theta3_1, &theta3_2, &theta3_3);

    // jacobian variables
    double J1x = - sin(theta3_1) * cos(theta2_1 + theta1_1) * sin(DELTA_THETA_N1) + cos(theta3_1) * cos(DELTA_THETA_N1);
    double J1y = - sin(theta3_1) * cos(theta2_1 + theta1_1) * cos(DELTA_THETA_N1) - cos(theta3_1) * sin(DELTA_THETA_N1);
    double J1z = sin(theta3_1) * sin(theta2_1 + theta1_1);

    double J2x = - sin(theta3_2) * cos(theta2_2 + theta1_2) * sin(DELTA_THETA_N3) + cos(theta3_2) * cos(DELTA_THETA_N3);
    double J2y = - sin(theta3_2) * cos(theta2_2 + theta1_2) * cos(DELTA_THETA_N3) - cos(theta3_2) * sin(DELTA_THETA_N3);
    double J2z = sin(theta3_2) * sin(theta2_2 + theta1_2);

    double J3x = - sin(theta3_3) * cos(theta2_3 + theta1_3) * sin(DELTA_THETA_N2) + cos(theta3_3) * cos(DELTA_THETA_N2);
    double J3y = - sin(theta3_3) * cos(theta2_3 + theta1_3) * cos(DELTA_THETA_N2) - cos(theta3_3) * sin(DELTA_THETA_N2);
    double J3z = sin(theta3_3) * sin(theta2_3 + theta1_3);

    double Jqa = (DELTA_LINK_LEN * sin(theta2_1) * sin(theta3_1));
    double Jqb = (DELTA_LINK_LEN * sin(theta2_2) * sin(theta3_2));
    double Jqc = (DELTA_LINK_LEN * sin(theta2_3) * sin(theta3_3));

    *J11 = (Jqa*(J2y*J3z - J3y*J2z))/(J1x*J2y*J3z - J1x*J3y*J2z - J2x*J1y*J3z + J2x*J3y*J1z + J3x*J1y*J2z - J3x*J2y*J1z);
    *J12 = -(Jqa*(J2x*J3z - J3x*J2z))/(J1x*J2y*J3z - J1x*J3y*J2z - J2x*J1y*J3z + J2x*J3y*J1z + J3x*J1y*J2z - J3x*J2y*J1z);
    *J13 = (Jqa*(J2x*J3y - J3x*J2y))/(J1x*J2y*J3z - J1x*J3y*J2z - J2x*J1y*J3z + J2x*J3y*J1z + J3x*J1y*J2z - J3x*J2y*J1z);
    *J21 = -(Jqb*(J1y*J3z - J3y*J1z))/(J1x*J2y*J3z - J1x*J3y*J2z - J2x*J1y*J3z + J2x*J3y*J1z + J3x*J1y*J2z - J3x*J2y*J1z);
    *J22 = (Jqb*(J1x*J3z - J3x*J1z))/(J1x*J2y*J3z - J1x*J3y*J2z - J2x*J1y*J3z + J2x*J3y*J1z + J3x*J1y*J2z - J3x*J2y*J1z);
    *J23 = -(Jqb*(J1x*J3y - J3x*J1y))/(J1x*J2y*J3z - J1x*J3y*J2z - J2x*J1y*J3z + J2x*J3y*J1z + J3x*J1y*J2z - J3x*J2y*J1z);
    *J31 = (Jqc*(J1y*J2z - J2y*J1z))/(J1x*J2y*J3z - J1x*J3y*J2z - J2x*J1y*J3z + J2x*J3y*J1z + J3x*J1y*J2z - J3x*J2y*J1z);
    *J32 = -(Jqc*(J1x*J2z - J2x*J1z))/(J1x*J2y*J3z - J1x*J3y*J2z - J2x*J1y*J3z + J2x*J3y*J1z + J3x*J1y*J2z - J3x*J2y*J1z);
    *J33 = (Jqc*(J1x*J2y - J2x*J1y))/(J1x*J2y*J3z - J1x*J3y*J2z - J2x*J1y*J3z + J2x*J3y*J1z + J3x*J1y*J2z - J3x*J2y*J1z);
}

/*******************************************************************************************************************************************/
// END Haptic mouse Code
/*******************************************************************************************************************************************/