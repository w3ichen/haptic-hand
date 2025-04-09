/**
  ******************************************************************************
  * @file    haplink_communication.h 
  * @author  melisao@stanford.edu
  * @version 1.0
  * @date    November-2017
  * @brief   Haplink Communication function prototypes
  ******************************************************************************
  */
#ifndef HAPLINK_COMMUNICATION_H_
#define HAPLINK_COMMUNICATION_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"

void resetCommunicationVariables( void );
int decodeMessage( uint8_t * buf );
double get_tele_position( void);
double get_rx_tele( void );
double get_ry_tele( void );
void get_xH_packed( uint8_t * buffer_to_pack );
void get_rx_ry_packed( uint8_t * buffer_to_pack );

int returnMessageAcknowledged( void );
int returnSeenLifeFromComputer( void );
int returnDataHasBeenRequested( void );
int returnTeleOperationHasBeenRequested( void );

void clearMessageAcknowledged( void );
void clearSeenLifeFromComputer( void );
void clearDataHasBeenRequested( void );
void clearTeleOperationHasBeenRequested( void );

#ifdef __cplusplus
}
#endif

#endif //EOF