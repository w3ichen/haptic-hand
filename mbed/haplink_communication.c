/**
  ******************************************************************************
  * @file    haplink_communication.cpp 
  * @author  mortamar@andrew.cmu.edu
  * @version 2.0
  * @date    March-2021
  * @brief   Contains functions to enable communication between Haplink and 
  *             a computer program.
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/  
#include "haplink_communication.h"
#include "haplink_motors.h"
#include "haplink_position.h"


/* Global Variables ----------------------------------------------------------*/
//variables used for communication protocol with Processing
int messageAcknowledged = 1; //the first time we should just send after a request
int seenLifeFromComputer = 0;
int dataHasBeenRequested = 0; 
int dataTeleOperationHasBeenRequested = 0;
double xH_tele = 0.0;
double xH_tele_new_d = 0.0;
uint16_t xH_tele_new = 0;

double rx_tele = 0.0;
double rx_tele_new_d = 0.0;
uint16_t rx_tele_new = 0;

double ry_tele = 0.0;
double ry_tele_new_d = 0.0;
uint16_t ry_tele_new = 0;

/* Function Definitions ------------------------------------------------------*/



/*******************************************************************************
  * @name   resetCommunicationVariables
  * @brief  Resests the communication variables.
  * @param  None.
  * @retval None
  */
void resetCommunicationVariables( void )
{
    messageAcknowledged = 1; //the first time we should just send after a request
    seenLifeFromComputer = 0;
    dataHasBeenRequested = 0; 
    dataTeleOperationHasBeenRequested = 0;
}


/*******************************************************************************
  * @name   decodeMessage
  * @brief  Decodes message received from Processing program and performs
            instructions.
  * @param  char * buf: message received.
  * @retval None
  */
int decodeMessage( uint8_t * buf )
{
int returnmessage = -1;    //message unknown 
seenLifeFromComputer = 1;
    if (buf[0] == '1')
    {
        returnmessage = 1; //message to acknowledge message received from processing
        messageAcknowledged = 1;
    }
    else if (buf[0] == '2') //random message from processing for debugging //do nothing
    {
        returnmessage = 2;
    }
    else if (buf[0] == '3') //processing requested data to be sent
    {
       returnmessage = 3;
       dataHasBeenRequested = 1;
    }
    else if (buf[0] == 'm')
    {
        returnmessage = 22;
        if (buf[1] == '1')
        {
            if (buf[2]=='0')
            {
                outputDutyCycleMotor1(0.0);
            }
            else if (buf[2] == '1')
            {
                outputDutyCycleMotor1(0.25);
            }
        }
        else if (buf[1] =='2')
        {
            if (buf[2]=='0')
            {
                outputDutyCycleMotor2(0.0);
            }
            else if (buf[2] == '1')
            {
                outputDutyCycleMotor2(0.25);
            }
        }    
    }
    else if (buf[0] == 'p')
    {
        #ifdef DOF_1
            xH_tele_new = buf[1];
            xH_tele_new = xH_tele_new << 8;
            xH_tele_new = xH_tele_new | buf[2];
            xH_tele_new_d = xH_tele_new;
            xH_tele_new_d = (xH_tele_new_d / 100.0) - 90.0;
            xH_tele = xH_tele_new_d; 
        #else
            rx_tele_new = buf[1];
            rx_tele_new = rx_tele_new << 8;
            rx_tele_new = rx_tele_new | buf[2];
            rx_tele_new_d = rx_tele_new;
            rx_tele_new_d = (rx_tele_new_d / 100.0) - 200.0;
            rx_tele = rx_tele_new_d; 
            
            ry_tele_new = buf[3];
            ry_tele_new = ry_tele_new << 8;
            ry_tele_new = ry_tele_new | buf[4];
            ry_tele_new_d = ry_tele_new;
            ry_tele_new_d = (ry_tele_new_d / 100.0) - 200.0;
            ry_tele = ry_tele_new_d; 
        #endif
        //if you receive data from teleoperator, they also want data!
        dataTeleOperationHasBeenRequested = dataTeleOperationHasBeenRequested + 1;  
    }
    else if (buf[0] == 't')
    {
       //another way to request data by the teleoperator
       dataTeleOperationHasBeenRequested = dataTeleOperationHasBeenRequested + 1;     
    }
return returnmessage;     
}

double get_tele_position( void)
{
    return xH_tele;    
}

double get_rx_tele( void )
{
    return rx_tele;
}

double get_ry_tele( void )
{
    return ry_tele;
}

void get_xH_packed( uint8_t * buffer_to_pack )
{
    double position;
    uint16_t position_u;
    
    position = getXH();
    position = position + 90;
    position = position * 100; //give it two digits of precision;
    if (position < 0)
    {
        position = 0;
    }
    position_u =  position;
    buffer_to_pack[0] = 'p';
    buffer_to_pack[1] = position_u >> 8; //store msb first
    buffer_to_pack[2] = position_u & 0xFF; //store lsb second 
    buffer_to_pack[3] = 'l';
}

void get_rx_ry_packed( uint8_t * buffer_to_pack )
{
    double position_x;
    uint16_t position_x_u;
    double position_y;
    uint16_t position_y_u;
    
    position_x = getRx();
    position_x = position_x + 200;
    position_x = position_x * 100; //give it two digits of precision;
    if (position_x < 0)
    {
        position_x = 0;
    }
    position_x_u =  position_x;
    
    position_y = getRy();
    position_y = position_y + 200;
    position_y = position_y * 100; //give it two digits of precision;
    if (position_y < 0)
    {
        position_y = 0;
    }
    position_y_u =  position_y;
    
    buffer_to_pack[0] = 'p';
    buffer_to_pack[1] = position_x_u >> 8; //store msb first
    buffer_to_pack[2] = position_x_u & 0xFF; //store lsb second 
    buffer_to_pack[3] = position_y_u >> 8; //store msb first
    buffer_to_pack[4] = position_y_u & 0xFF; //store lsb second 
    buffer_to_pack[5] = 'l';
}


/*---- Functions to return communication variables ---------- */
int returnMessageAcknowledged( void )
{
    return messageAcknowledged;
}

int returnSeenLifeFromComputer( void )
{
    return seenLifeFromComputer;
}

int returnDataHasBeenRequested( void )
{
    return dataHasBeenRequested;
}

int returnTeleOperationHasBeenRequested( void )
{
    return dataTeleOperationHasBeenRequested;
}
/*---- Functions to clear communication variables ---------- */
void clearMessageAcknowledged( void )
{
    messageAcknowledged = 0;
}

void clearSeenLifeFromComputer( void )
{
     seenLifeFromComputer = 0;
}

void clearDataHasBeenRequested( void )
{
   dataHasBeenRequested = 0;
}

void clearTeleOperationHasBeenRequested( void )
{
    dataTeleOperationHasBeenRequested = 0;
}
//EOF