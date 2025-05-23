/**
  ******************************************************************************
  * @file    main.h 
  * @author  mortamar@andrew.cmu.edu
  * @version 3.0
  * @date    January-2022
  * @brief   This program supports Haplink 1-DOF and 2-DOF. Use main.h to define
            which device you are using. Added support for Keil Studio.
  ******************************************************************************
  */

#include "main.h"
#include "nucleo_led.h"
#include "debug_mort.h"
#include "mbed.h"
#include "haplink_encoders.h"
#include "haplink_motors.h"
#include "haplink_position.h"
#include "haplink_virtual_environments.h"
#include "haplink_time.h"
#include "haplink_fsr.h"
#include "haplink_adc_sensors.h"
#include "delta_thumb.h"
#include "hand_virtual_environment.h"

int main() 
{
    uint32_t print_counter = 0;
    double mass_position;
    double wall_position;
    int contact;

    initCommunication();        // unchanged
    initLED1();                 // unchanged
    initHapticHand();           // calls motor encoder initializations within
    initHaplinkMotors();        // init for all seven motors
    initHaplinkAnalogSensors(); // unchanged
    initHaplinkTime();          // unchanged
    SystemCoreClockUpdate();    // unchanged
  
    //printf("Starting haptic hand...\n");
  while(1) 
  {
    deltaThumbHandler(); // Motors 1, 2, 3
    calculatePositionAndJacobianFinger1();  // Motors 4 and 5
    calculatePositionAndJacobianFinger2();  // Motors 6 and 7



    renderOutsideSphere(); // Single shape felt by thumb and fingers

    /* Finger-specific renders for debugging */
    //renderOutsideCircle2DOF_M1M2(); // Delta disconnected, finger on original motor channels
    //renderOutsideCircle2DOF_M4M5(); // Finger 1
    //renderOutsideCircle2DOF_M6M7(); // Finger 2

    //toggleLED1(); // unused

    /* Message decoding code, do not change*/
    if (checkReceiveMessage() > 0)
    {
        //printComBuffer(); // only if debugging
        clearReceiveMessage();
        //decode Message
        manageIncommingMessage();
    }

//we are using the USB communication to debug:
//This is just an example of a function that would print what I think is all of the parameters you need.
//But you may want to print different things so feel free to write your own in debug_mort.cpp and call it from here.
//Debug prints shouldn't happen very often.
    #ifdef COMM_DEBUGGING
        // printProcessingHapticHand();
        if (print_counter > 10000)
        {
            //printDebug1DOFAllParameters();

            // debugprintHelloWorld();
            printProcessingHapticHand();
          
            //debugprintStarterCode();
            //debugprinttruesusb();

            //debugprintFingerMotorCounts();
            
            printDebugFinger1Parameters();
            printDebugFinger2Parameters();

            print_counter = 0;
        }
        else
        {
            print_counter = print_counter + 1;
        }
    #endif

//we are using the USB communication to talk to processing: 
//change the parameter you are sending depending on the virtual environment you are rendering.
//or maybe you need to write your own function in debug_mort.cpp and call it from here.
    #ifdef COMM_PROCESSING
        // printProcessingHapticHand();
        if (print_counter > 100)
        {
            printProcessingHapticHand();
            print_counter = 0;
        }
        else
        {
            print_counter = print_counter + 1;
        }
        //printProcessingComm1DOF(mass_position*1000.0);
        //printProcessingComm2DOF((double)contact);
        // printProcessingCommFinger1(); // prints out x and y position for finger 1 (z is determined by physical spacing)
        // printProcessingCommFinger2(); // prints out x and y position for finger 2 (z is determined by physical spacing )
    #endif

//we are using the USB communication for teleoperation: 
    #ifdef COMM_TELEOPERATION
        printTeleoperationComm();
    #endif


  }
}
