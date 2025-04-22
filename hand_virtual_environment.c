/**
  ******************************************************************************
  * @file    hand_virtual_environment.c
  * @author  
  * @version 1.0
  * @date    April-2022
  * @brief   Haptic hand virtual environment
  ******************************************************************************
  */

#include "main.h"
#include <math.h>
#include "stdlib.h"
#include "hand_virtual_environment.h"
#include "delta_thumb.h"
#include "haplink_motors.h"
#include "haplink_position.h"

/* Global Variables ----------------------------------------------------------*/
//variables needed declared in other files:
extern double J00, J01, J10, J11; //jacobian variables
extern double J00_f1, J01_f1, J10_f1, J11_f1; //jacobian variables
extern double J00_f2, J01_f2, J10_f2, J11_f2; //jacobian variables
extern double rx, ry, dx, dy; // 2-DOF position variables
extern double xH, dxH; //1-DOF position variables
double rx_proxy = 0.0;
double ry_proxy = 0.0;
double TorqueX, TorqueY, ForceX, ForceY, ForceH;
double TorqueMotor1, TorqueMotor2, TorqueMotor3, TorqueMotor4, TorqueMotor5, TorqueMotor6, TorqueMotor7;

/*******************************************************************************
  * @name   renderOutsideSphere
  * @brief  Render sphere at a specified location
  * @param  None.
  * @retval None.
  */
void renderOutsideSphere( void ) {
    /********************* THUMB *************************/

    // Check if thumb is inside sphere
    double dist = sphereDistance(deltaThumbX, deltaThumbY, deltaThumbZ);
    double torque1, torque2, torque3, F_coeff;
    double Fx=0, Fy=0, Fz=0;

    if (dist < SPHERE1_RADIUS) {
        // Calculate the forces to apply in order to resist the user
        F_coeff = K_DELTA_THUMB * (SPHERE1_RADIUS - dist) / dist;
        Fx = F_coeff * (deltaThumbX - SPHERE1_X);
        Fy = F_coeff * (deltaThumbY - SPHERE1_Y);
        Fz = F_coeff * (deltaThumbZ - SPHERE1_Z);
    }

    // Use jacobians to transforms forces into motor torques
    // Get the jacobians
    double J11, J12, J13, 
           J21, J22, J23, 
           J31, J32, J33;
    // DeltaThumbGetJacobian (&J11, &J12, &J13, 
    //                        &J21, &J22, &J23, 
    //                        &J31, &J32, &J33);
     DeltaThumbGetJacobian_OhioVersion (&J11, &J12, &J13, 
                                        &J21, &J22, &J23, 
                                        &J31, &J32, &J33);
                                    
    /* Force to Torque*/
    /* transpose */
    // torque1 = J11 * Fx + J21 * Fy + J31 * Fz;
    // torque2 = J12 * Fx + J22 * Fy + J32 * Fz;
    // torque3 = J13 * Fx + J23 * Fy + J33 * Fz;
    /* non - transpose */
    torque1 = J11 * Fx + J12 * Fy + J13 * Fz;
    torque2 = J21 * Fx + J22 * Fy + J23 * Fz;
    torque3 = J31 * Fx + J32 * Fy + J33 * Fz;
    outputTorqueMotor1(torque1);
    outputTorqueMotor2(torque2);
    outputTorqueMotor3(torque3);

    /********************* FINGER 1 *************************/

    // Check if finger 1 is inside sphere
    double xf1_global = getRx1()*-1 + NORMAL_XF; // mm, rotated and translated to be in global frame
    double yf1_global = getRy1() + NORMAL_YF;    // mm, rotated and translated to be in global frame
    double dist_f1 = sphereDistance(xf1_global, yf1_global, NORMAL_ZF1); // mm
    double TorqueX_f1, TorqueY_f1;
    double Fx_f1=0, Fy_f1=0;

    if (dist_f1 < SPHERE1_RADIUS) {
        // Calculate the forces to apply in order to resist the user
        dist_f1 = dist_f1/1000.0; // m
        xf1_global = xf1_global/1000.0; // m
        yf1_global = yf1_global/1000.0; // m
        Fx_f1 = K_FINGERS*(SPHERE1_RADIUS/1000.0 - dist_f1) * ((1.0/dist_f1) * (xf1_global - SPHERE1_X/1000.0)); // N
        Fy_f1 = K_FINGERS*(SPHERE1_RADIUS/1000.0 - dist_f1) * ((1.0/dist_f1) * (yf1_global - SPHERE1_Y/1000.0)); // N
    }

    // Map back to local coordinate axes
    Fx_f1 = Fx_f1*-1; // rotation
    Fy_f1 = Fy_f1;

    // Use jacobians to transforms forces into motor torques
    /* Force to Torque*/
    TorqueX_f1 = J00_f1*Fx_f1 + J10_f1*Fy_f1;
    TorqueX_f1 = TorqueX_f1*0.001;
    TorqueY_f1 = J01_f1*Fx_f1 + J11_f1*Fy_f1;
    TorqueY_f1 = TorqueY_f1*0.001;
            
    TorqueMotor4 = -((TorqueX_f1*R_MA)/R_A);
    TorqueMotor5 = -((TorqueY_f1*R_MB)/R_B); 
            
    outputTorqueMotor4(TorqueMotor4);
    outputTorqueMotor5(-TorqueMotor5);  

    /********************* FINGER 2 *************************/

    // Check if finger 2 is inside sphere
    double xf2_global = getRx1()*-1 + NORMAL_XF; // mm, rotated and translated to be in global frame
    double yf2_global = getRy1() + NORMAL_YF;    // mm, rotated and translated to be in global frame
    double dist_f2 = sphereDistance(xf2_global, yf2_global, NORMAL_ZF2); // mm
    double TorqueX_f2, TorqueY_f2;
    double Fx_f2=0, Fy_f2=0;

    if (dist_f2 < SPHERE1_RADIUS) {
        // Calculate the forces to apply in order to resist the user
        dist_f2 = dist_f2/1000.0; // m
        xf2_global = xf2_global/1000.0; // m
        yf2_global = yf2_global/1000.0; // m
        Fx_f2 = K_FINGERS*(SPHERE1_RADIUS/1000.0 - dist_f2) * ((1.0/dist_f2) * (xf2_global - SPHERE1_X/1000.0)); // N
        Fy_f2 = K_FINGERS*(SPHERE1_RADIUS/1000.0 - dist_f2) * ((1.0/dist_f2) * (yf2_global - SPHERE1_Y/1000.0)); // N
    }

    // Map back to local coordinate axes
    Fx_f2 = Fx_f2; // axes aligned, no rotation needed
    Fy_f2 = Fy_f2;

    // Use jacobians to transforms forces into motor torques
    /* Force to Torque*/
    TorqueX_f2 = J00_f2*Fx_f2 + J10_f2*Fy_f2;
    TorqueX_f2 = TorqueX_f2*0.001;
    TorqueY_f2 = J01_f2*Fx_f2 + J11_f2*Fy_f2;
    TorqueY_f2 = TorqueY_f2*0.001;
            
    TorqueMotor6 = -((TorqueX_f2*R_MA)/R_A);
    TorqueMotor7 = -((TorqueY_f2*R_MB)/R_B); 
            
    outputTorqueMotor6(TorqueMotor6);
    outputTorqueMotor7(-TorqueMotor7);  
}


/*******************************************************************************
  * @name   sphereDistance
  * @brief  Euclidean distance from user location to sphere's center
  * @param  user_x user's x position.
  * @param  user_y user's y position.
  * @param  user_z user's z position.
  * @retval distance in doubles.
  */
double sphereDistance( double user_x, double user_y, double user_z ) {
    double diff_x = user_x - SPHERE1_X;
    double diff_y = user_y - SPHERE1_Y;
    double diff_z = user_z - SPHERE1_Z;

    return sqrt(diff_x*diff_x + diff_y*diff_y + diff_z*diff_z);
}



// /*******************************************************************************
//  * @name   renderOutsideCircle2DOF
//  * @brief  There is a circle of RCircle2 radius centered at CCircleX2,CCircleY2
//  *         that you can explore from the outside.
//  * @param  None.
//  * @retval None.
//  */
// void renderOutsideCircle2DOF(void) {
//   double DCircle = 0.0;
//   double FVector = 0.0;
//   ForceX = 0.0;
//   ForceY = 0.0;
//   double dr = 0.0;
//   double rhat_x = 0.0;
//   double rhat_y = 0.0;
//   // implement the virtual environment!
//   // Remember that ForceX and ForceY should be in Newtons!

//   dr = sqrt(pow((rx - CCircleX2),2) + pow((ry - CCircleY2),2));
//   rhat_x = dr/(rx-CCircleX2);
//   rhat_y = dr/(ry-CCircleY2);

//   if (dr < RCircle){ // ball is inside of circle radius so must be pushed outwards
//       ForceX = ForceX + KCircle2*(RCircle2 - dr)*rhat_x/1000;
//       ForceY = ForceY + KCircle2*(RCircle2 - dr)*rhat_y/1000;
//   }
//  // otherwise ForceX = 0 and ForceY = 0
//   else {
//       ForceX = 0;
//       ForceY = 0;
//   }

//   TorqueX = J00 * ForceX + J10 * ForceY;
//   TorqueX = TorqueX * 0.001;
//   TorqueY = J01 * ForceX + J11 * ForceY;
//   TorqueY = TorqueY * 0.001;

//   TorqueMotor1 = -((TorqueX * R_MA) / R_A);
//   TorqueMotor2 = -((TorqueY * R_MB) / R_B);

//   outputTorqueMotor1(TorqueMotor1);
//   outputTorqueMotor2(TorqueMotor2);
// }