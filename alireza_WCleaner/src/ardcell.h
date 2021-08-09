#ifndef ARDCELL_H
#define ARDCELL_H
#include "config.h"
#include "encoder.h"
#include "Filters.h"

#define ardcell_serial Serial2




extern float init_end_mass;
extern float mass;
extern bool new_mass_data_flag;


void ardcell_init();
void update_ardcell();
void ardcell_tare();
float end_mass();

#endif
