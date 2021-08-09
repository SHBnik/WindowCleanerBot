#ifndef MOTOR_H
#define MOTOR_H

#include "config.h"
#include <Arduino.h>
#include "gcode.h"


#define GET_X_POS (pulses * X_PER_UNIT)


extern bool MSW_hit;
extern bool IsHomed;
extern uint8_t motor_pin_map;
extern uint16_t encoder_pulse;
extern uint32_t pulses; 
extern float speed_timming;
extern float motor_speed;
extern uint8_t speed_dir;
extern bool pid_flag;
extern bool no_move_flag;


extern gcode Commands;


void HOME_X();
void MOTOR_move_one_step(bool dir);
void HomeSense();
void update_movment();
void G1();
void G90();
void G91();
void speed_mode();



#endif

