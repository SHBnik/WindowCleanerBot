#ifndef ENCODER_H
#define ENCODER_H
#include "config.h"

extern uint16_t encoder_pulse;


void encoder_int1();
void encoder_int2();
float read_angle();




#endif
