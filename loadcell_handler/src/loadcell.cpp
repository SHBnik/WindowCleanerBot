#include "loadcell.h"


HX711 scale;



void init_loadcell(){
    scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);    
    scale.set_scale(calibration_factor);
    // scale.tare();
}



void update_loadcell(){
    new_data = false;
    if(scale.wait_ready_timeout(100,0)) {
        new_data = true;
        data = scale.get_units(); 
    }
}

void loadcell_tare(){
    scale.tare();
    // init_end_mass = MAX_HEAD_WEIGHT * sin(read_angle() * DEG_TO_RAD);
}

// float end_mass(){
//     return(MAX_HEAD_WEIGHT * sin(read_angle() * DEG_TO_RAD) - init_end_mass);
// }