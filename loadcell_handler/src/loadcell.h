#ifndef LOADCELL_H
#define LOADCELL_H

#include <Arduino.h>
#include "HX711.h"
 

#define  LOADCELL_DOUT_PIN  3
#define LOADCELL_SCK_PIN  2
#define calibration_factor  -4950


extern float init_end_mass;
extern bool new_data;
extern float data;

void init_loadcell();
void update_loadcell();
void loadcell_tare();
// float end_mass();

#endif

