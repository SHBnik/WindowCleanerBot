#include "encoder.h"
#include <Arduino.h>

void encoder_int1(){
  if(!digitalRead(ENCODER_A_PIN) ) {
      encoder_pulse++;
  } 
  else{
    if(encoder_pulse != 0){
      encoder_pulse--;
    }
  }
}

void encoder_int2(){
  if(!digitalRead(ENCODER_B_PIN)) {
    if(encoder_pulse != 0){
      encoder_pulse--;
    }
  } 
  else{
      encoder_pulse++;
  }
}

float read_angle(){
  return(((360 / (float)ENCODER_PER_REV) * encoder_pulse + HOME_ANGLE) - ANGLE_OFFSET);
}
