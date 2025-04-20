/**
 ******************************************************************************
 * @file    haplink_encoders.h
 * @author  mortamar@andrew.cmu.edu
 * @version 3.0
 * @date    January-2023
 * @brief   Controls Haplink's encoders channels for sensor reading.
 ******************************************************************************
 */
#ifndef __HAPLINK_ENCODERS_H_
#define __HAPLINK_ENCODERS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "main.h"

  void initHapticHandEncodersMotors(void);
  void initHaplinkEncoders2Motors(void);
  void initHaplinkEncoders3Motors(void);
  int32_t getCountsSensor1(void);
  int32_t getCountsSensor2(void);
  int32_t getCountsSensor3(void);
  int32_t getCountsSensor4(void);
  int32_t getCountsSensor5(void);
  int32_t getCountsSensor6(void);
  int32_t getCountsSensor7(void);

#define TOTAL_ENCODER_COUNTS_1 48.0
#define TOTAL_ENCODER_COUNTS_2 48.0
#define TOTAL_ENCODER_COUNTS_3 48.0
#define TOTAL_ENCODER_COUNTS_4 48.0
#define TOTAL_ENCODER_COUNTS_5 48.0
#define TOTAL_ENCODER_COUNTS_6 48.0
#define TOTAL_ENCODER_COUNTS_7 48.0

#ifdef __cplusplus
}
#endif

#endif //__HAPLINK_ENCODERS_H_