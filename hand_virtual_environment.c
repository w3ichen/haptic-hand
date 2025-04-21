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



/*******************************************************************************
  * @name   renderOutsideSphere
  * @brief  Render sphere at a specified location
  * @param  None.
  * @retval None.
  */
void renderOutsideSphere( void ) {
    // THUMB
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