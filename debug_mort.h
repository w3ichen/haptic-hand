/**
  ******************************************************************************
  * @file    debug_mort.h
  * @author  mortamar@andrew.cmu.edu
  * @version 1.0
  * @date    January-2022
  * @brief   Changed communication structure to be compatible with Keil Studio.
            Debug functions live in this file and also the base communication management functions.
  ******************************************************************************
  */
#ifndef __DEBUG_MORT_H_
#define __DEBUG_MORT_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/*Function definitions---------------------------------------------------------*/
void printDebugDeltaThumb( void );

void printProcessingComm1DOF( double parameter );
void printProcessingComm2DOF( double parameter );
void printTeleoperationComm( void );
void printDebug1DOFAllParameters( void );
void printDebug2DOFAllParameters( void );

void debugprint(uint16_t number);
void debugprintHelloWorld( void );
void debugprint2byteValue(uint16_t number);
void debugprintRegister( uint32_t registerval);
void debugprintEncoderCounts( int32_t encodercounts);
void debugprintDouble( double number);
void debugprintStarterCode( void );
void debugprinttruesusb( void );


void initCommunication( void );
void receiveMessageCallback( void);
void printComBuffer( void );
int checkReceiveMessage( void );
void clearReceiveMessage( void );



void manageIncommingMessage( void );

#ifdef __cplusplus
}
#endif

#endif /*__DEBUG_MORT_H */
