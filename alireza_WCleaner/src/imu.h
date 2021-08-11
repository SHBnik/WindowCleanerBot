#ifndef IMU_H
#define IMU_H

#include "MPU9250.h"
#include "config.h"
#include "gcode.h"


extern float pitch_init, roll_init;


extern gcode Commands;
extern uint8_t PITCH_DEV_LIMIT,ROLL_DEV_LIMIT;

void init_mpu();
void update_mpu();
void turn_buuzer_on_off(bool state);
void set_roll_pitch();
void buzzer();


#endif