#include "ardcell.h"



void ardcell_init(){
    ardcell_serial.begin(9600);
    ardcell_serial.println('q');
}

float end_mass(){
    return(MAX_HEAD_WEIGHT * sin(read_angle() * DEG_TO_RAD) - init_end_mass);
}

void update_ardcell(){
    if(ardcell_serial.available()){
        mass = ardcell_serial.readStringUntil('\n').toFloat() * abs(cos(read_angle()*DEG_TO_RAD));//- end_mass();
        new_mass_data_flag = true;

    }
}


void ardcell_tare(){
    ardcell_serial.print('t');
    init_end_mass = MAX_HEAD_WEIGHT * sin(read_angle() * DEG_TO_RAD);
}

