/**
  ******************************************************************************
  * @file    main.h 
  * @author  mortamar@andrew.cmu.edu
  * @version 3.0
  * @date    January-2022
  * @brief   This program supports Haplink 1-DOF and 2-DOF. Comment and uncomment
             the lines that are indicated depending on which device you will use. 
             This file also defines your initial position for Paddle 2.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H_
#define __MAIN_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_mort2.h"

/* MACROS for everyone--------------------------------------------------------*/

//comment out which device you are not using:
   #define DOF_1          1
    //#define DOF_2         2

//choose which communication you are using, comment out the other two!
    #define COMM_DEBUGGING          1
    //#define COMM_PROCESSING         2
    //#define COMM_TELEOPERATION      3

// Haplink 2-DOF initial Offset in degrees:
// These have to match the offset on your actual physical Haplink
// Change these if you want to start from another position. 
// Remember to change your startign position depending on your virtual environment
// so you start from a 0 force condition!
#define THETA_A_OFFSET      0.0
#define THETA_B_OFFSET      0.0
    
 //Suggested Box location for Haplink 2-DOF when starting from
 // Theta_A_OFFSET = 0, Theta_B_Offset = 0 in degrees   
#define X_WALL_CORNER      -16.327652
#define Y_WALL_CORNER       142.337051


#ifdef __cplusplus
}
#endif

#endif /*__MAIN_H */