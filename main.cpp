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

int main() 
{
    uint32_t print_counter = 0;
    double mass_position;
    double wall_position;
    int contact;

    initCommunication();
    initLED1();
    initHaplinkPosition();
    initHaplinkMotors();
    initHaplinkAnalogSensors();
    initHaplinkTime();
    SystemCoreClockUpdate();
    calculatePositionHandleAndJacobian();
  while(1) 
  {
    initDeltaThumb();

    #ifdef DOF_1        
        // calculatePosition1DOF(); 
        /*Insert here the virtual environment from the file haplink_virtual_environments.c that you wish to render*/   
        //renderSpring1DOF( );
        //renderForceAlert( );
        //renderVirtualWall1DOF();
        //renderLinearDamping1DOF();
        //renderNonLinearFriction1DOF();
        //renderHardSurface1DOF();
        //renderBumpAndValley1DOF( );
        //renderTexture21DOF();
        //wall_position =  renderWallForGraphics1DOF();
        //mass_position = renderDynamicMSDSimulation1DOF();
        //renderBilateralTeleoperator1DOF();
    #endif 
    #ifdef DOF_2//then we are in 2DOF
        calculatePositionHandleAndJacobian();
        /*Insert here the virtual environment from the file haplink_virtual_environments.cpp
        that you wish to render*/
         //renderInsideBox2DOF();
         //renderInsideCircle2DOF();
         //renderOutsideCircle2DOF();
        //contact = renderOutsideBox2DOF();
        //renderBilateralTeleoperator2DOF();
    #endif
    toggleLED1();

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
        if (print_counter > 10000)
        {
            //printDebug1DOFAllParameters();
            debugprintHelloWorld();
            //debugprintStarterCode();
            //debugprinttruesusb();
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
        printProcessingComm1DOF(mass_position*1000.0);
        //printProcessingComm2DOF((double)contact);
    #endif

//we are using the USB communication for teleoperation: 
    #ifdef COMM_TELEOPERATION
        printTeleoperationComm();
    #endif


  }
}
