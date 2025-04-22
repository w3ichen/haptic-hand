/**
  ******************************************************************************
  * @file    debug_mort.cpp
  * @author  mortamar@andrew.cmu.edu
  * @version 3.0
  * @date    January-2025
  * @brief   Jan 2022:Changed communication structure to be compatible with Keil Studio.
            Debug functions live in this file and also the base communication management functions.
            Jan 2025: had to change com structure again, for some reason now only RawSerial works.
            Probably deprecating libraries... 
            Also had to increase the baud rate to 115200 for the graphics rendering and teleoperation to work
            properly.
  ******************************************************************************
  */


#include "haplink_encoders.h"

#include "delta_thumb.h"

#include "main.h"
#include "mbed.h"
#include "debug_mort.h"
#include "nucleo_led.h"
#include "haplink_communication.h"
#include "haplink_position.h"
#include "haplink_virtual_environments.h"
#include "haplink_motors.h"
#include "haplink_fsr.h"
#include "haplink_time.h"

RawSerial pc(USBTX, USBRX);

//communication variables:
uint8_t receivechar;
int receivedMessage = 0;
uint8_t communicationBuf[20];
uint8_t sendBuffer[10];
uint8_t messagesize = 0;


/*-- Functions to communicate with processing and render graphics, 
change the print to match what you need for your environment.
You can also change the argument so you send processing what you need--*/
/*******************************************************************************
  * @name   printProcessingComm1DOF
  * @brief  this is just an example function to send to show the communication structure to processing.
            this function assumes that what you want to send to processing is one parameter as well
            as the position of the 1DOF Haplink handle.
  * @param  a parameter to send to processing.
  * @retval none.
  */
void printProcessingComm1DOF( double parameter )
{
    //debugprintHelloWorld();
    if ((returnMessageAcknowledged() > 0) && (returnDataHasBeenRequested() > 0))
    {
        clearMessageAcknowledged();
        clearDataHasBeenRequested();
        pc.printf("%f\t%f\t l",(float)getXH(), (float)(parameter));
         //only for debugging:
         //pc.printf("got message \n");
         //if you did not want to send a parameter for example:
        //serial.printf("%f\t l",(float)getXH());
    }
}
/*******************************************************************************
  * @name   printProcessingComm2DOF
  * @brief  this is just an example function to send to show the communication structure to processing.
            this function assumes that what you want to send to processing is one parameter as well
            as the position of the 2DOF Haplink cursor and Proxy for rendering Outside of a Box.
  * @param  a parameter to send to processing.
  * @retval none.
  */
void printProcessingComm2DOF( double parameter )
{
    if ((returnMessageAcknowledged() > 0) && (returnDataHasBeenRequested() > 0))
    {
        clearMessageAcknowledged();
        clearDataHasBeenRequested();
         pc.printf("%f\t%f\t%f\t%f\t%f\t l", (float)getRx(), (float)getRy(), (float)getProxyX(), (float)getProxyY(), (float)parameter);
         ////pc.printf("%f\t%f\t l", (float)getRx(), (float)getRy());
    }
}



/*******************************************************************************
  * @name   printProcessingCommFinger1
  * @brief  this is just an example function to send to show the communication structure to processing.
            this function assumes that what you want to send to processing is the position of the 2DOF Finger1 cursor 
  * @param  a parameter to send to processing.
  * @retval none.
  */
void printProcessingCommFinger1(void)
{
    if ((returnMessageAcknowledged() > 0) && (returnDataHasBeenRequested() > 0))
    {
        clearMessageAcknowledged();
        clearDataHasBeenRequested();
         pc.printf("%f\t%f\t", getRx1(), getRy1());
         ////pc.printf("%f\t%f\t l", (float)getRx(), (float)getRy());
    }
}


/*******************************************************************************
  * @name   printProcessingCommFinger2
  * @brief  this is just an example function to send to show the communication structure to processing.
            this function assumes that what you want to send to processing is the position of the 2DOF Finger2 cursor.
  * @param  a parameter to send to processing.
  * @retval none.
  */
void printProcessingCommFinger2(void)
{
    if ((returnMessageAcknowledged() > 0) && (returnDataHasBeenRequested() > 0))
    {
        clearMessageAcknowledged();
        clearDataHasBeenRequested();
         pc.printf("%f\t%f\t", getRx2(), getRy2());
         ////pc.printf("%f\t%f\t l", (float)getRx(), (float)getRy());
    }
}



/*******************************************************************************
  * @name   printTeleoperationComm
  * @brief  this is just an example function to send to show the communication structure for teleoperation.
            this function assumes that all you want to send is the position of the handle or cursor
  * @param  none.
  * @retval none.
  */
void printTeleoperationComm( void )
{
    if (returnTeleOperationHasBeenRequested() > 0)
    {
                //Communication for teleoperation:
                #ifdef DOF_1 //teleoperation in 1-DOF
                    get_xH_packed( sendBuffer );
                    //writeBlock(sendBuffer,4) ;
                    pc.printf("%c%c%c%c",sendBuffer[0],sendBuffer[1],sendBuffer[2],sendBuffer[3]);
                
                #else //teleoperation in 2-DOF
                    get_rx_ry_packed( sendBuffer );
                    //serial.writeBlock(sendBuffer,6) ;
                    pc.printf("%c%c%c%c%c%c",sendBuffer[0],sendBuffer[1],sendBuffer[2],sendBuffer[3], sendBuffer[4], sendBuffer[5]);
                #endif
                
                clearTeleOperationHasBeenRequested();
    }
}


/*-- Functions to print to help you debug, feel free to add your own
The idea behind this functions is to call them to print useful things to the screen
to help you see that your device is working properly. Just remember that prints will
ALWAYS cause delays and affect the behavior of your device. And if they happen too 
frequently, your device may not work at all.-- */

void debugprintFingerMotorCounts()
{
    pc.printf("Motor 4 Encoder Counts: %i\n", getCountsSensor4());
    pc.printf("Motor 5 Encoder Counts: %i\n", getCountsSensor5());
    pc.printf("Motor 6 Encoder Counts: %i\n", getCountsSensor6());
    pc.printf("Motor 7 Encoder Counts: %i\n", getCountsSensor7());
}

void printDebugDeltaThumb( void )
{
    pc.printf("xH=%lf, dXh=%lf, ForceH=%lf, Torque=%lf\r\n", getXH(), getDxH(), getForceH(), getTorqueMotor1());
}

void printProcessingHapticHand( void )
{
    // pc.printf("%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t l", (float)0.0, (float)0.0, (float)0.0, (float)0.0, (float)0.0, (float)0.0, getThumbX(), getThumbY(), getThumbZ(), (float)0.0, (float)0.0, (float)0.0, (float)0.0);
    if ((returnMessageAcknowledged() > 0) && (returnDataHasBeenRequested() > 0))
    {
        clearMessageAcknowledged();
        clearDataHasBeenRequested();
         pc.printf("%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t l", (float)0.0, (float)0.0, (float)0.0, (float)0.0, (float)0.0, (float)0.0, getThumbX(), getThumbY(), getThumbZ(), (float)0.0, (float)0.0, (float)0.0, (float)0.0);
         ////pc.printf("%f\t%f\t l", (float)getRx(), (float)getRy());
    }
    
}

void printDebug1DOFAllParameters( void )
{
    pc.printf("t=%lf, FSR1=%u, FSR2=%u, xH=%lf, dXh=%lf, ForceH=%lf, Torque=%lf\r\n",getTime_ms(), queryFSR1value(), queryFSR2value(), getXH(), getDxH(), getForceH(), getTorqueMotor1());
}

void printDebug2DOFAllParameters( void )
{
    pc.printf("Rx: %lf, Ry: %lf, ThetaA: %lf, ThetaB: %lf, ProxyX: %lf, ProxyY: %lf \n", getRx(), getRy(), getThetaADeg(), getThetaBDeg(),getProxyX(),getProxyY());
}

void printDebugFinger1Parameters( void )
{
    pc.printf("rx = %lf, ry = %lf, Torque M4 = %lf Nm, Torque M5 = %lf Nm, theta_a_deg = %lf, theta_b_deg = %lf \n", getRx1(), getRy1(), getTorqueMotor4(), getTorqueMotor5(), getThetaA1_deg(), getThetaB1_deg());
}
void printDebugFinger2Parameters( void )
{
    pc.printf("rx = %lf, ry = %lf, Torque M6 = %lf Nm, Torque M7 = %lf Nm, theta_a_deg = %lf, theta_b_deg = %lf \n", getRx2(), getRy2(), getTorqueMotor6(), getTorqueMotor7(), getThetaA2_deg(), getThetaB2_deg());
}

void printComBuffer( void )
{

    pc.printf("message: %u , %u \n", communicationBuf[0], communicationBuf[1]);

}

void debugprint(uint16_t number)
{
    pc.printf("Got to %u\n",number);    
}

void debugprintHelloWorld( void )
{
    pc.printf("Hello! Haptics to see you! \n");
} 

void debugprint2byteValue(uint16_t number)
{
    pc.printf("Value = %u\n",number);    
}

void debugprintRegister( uint32_t registerval)
{
    pc.printf("Register Value %u\n", registerval);
}

void debugprintEncoderCounts( int32_t encodercounts)
{
    pc.printf("Encoder Counts %i\n", encodercounts);
}

void debugprintDouble( double number)
{
    pc.printf("double number %lf\n", number);
}

void debugprintStarterCode( void )
{
    pc.printf("Dear Math, please grow up and solve your own problems.\n");
}

void debugprinttruesusb( void )
{
    pc.printf("l");
}


/*--Functions to manage the two way communication with processing, do not change! --*/
void manageIncommingMessage( void )
{
    int response = 0;
    response = decodeMessage( &communicationBuf[0] );
    //Only if debugging
    //pc.printf("Message received is: %i \n", response);
}


//function that gets called to receive messages from the computer via USB
void receiveMessageCallback( void) 
{
    int i;
    // Note: you need to actually read from the serial to clear the RX interrupt
    //pc.printf("%c\n", pc.getc());
    
    receivechar = pc.getc();
    i = 0;
    if (receivechar == 'p') //receiving position from teleoperation
    {
        communicationBuf[0] = receivechar;
        receivechar = pc.getc(); //get first digit
        communicationBuf[1] = receivechar;
        receivechar = pc.getc(); //get second digit
        communicationBuf[2] = receivechar;
        receivechar = pc.getc(); //get the terminating character
        i = 3;
        #ifdef DOF_2
            communicationBuf[3] = receivechar;
            receivechar = pc.getc(); //get the second digit 
            communicationBuf[4] = receivechar;
            receivechar = pc.getc(); //get the terminating character
        #endif
    }
    else
    {
        while (receivechar != 'l')
        {
            communicationBuf[i] = receivechar;
            receivechar = pc.getc();
            i = i+1;
        }
        //printf("Received Message\n"); //don't print so soon, buffer is not ready.
    }
    //only uncomment when debugging with Arduino, for some reason HAVE to do the newline thing
    //receivechar = pc.getc();
    receivechar = '0';
    receivedMessage = receivedMessage + 1;
    messagesize = i;
}

int checkReceiveMessage( void )
{
    return receivedMessage;
}

void clearReceiveMessage( void )
{
    receivedMessage = 0;
}

void initCommunication( void )
{
    resetCommunicationVariables();
    pc.baud(115200);
    pc.attach(&receiveMessageCallback);
}
//EOF
