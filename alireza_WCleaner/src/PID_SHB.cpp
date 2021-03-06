
#include "PID_SHB.h"

PID::PID(float Kp, float Ki, float Kd, int shift){
  kp = Kp;
  ki = Ki;
  kd = Kd;
  Y_shift = shift;
}




float PID::Compute(float target , float sensor_value ){
  float output;
  float time_changed;
  timer = millis();
  time_changed = (timer - timer_old);
  

  err = sensor_value - target;
  err_D = (float)(err - err_old) /(float) time_changed;
  err_I += (float)err * time_changed /(float) 100;
  output = kp * err + kd * err_D + ki * err_I;

  err_old = err;
  timer_old = timer;
  
  return output;
}


void PID::SetErrorLimit(int Min,int Max){
  error_limit = true;
  error_limit_min = Min;
  error_limit_max = Max;
}

void PID::SetErrorILimit(int Min,int Max){
  error_I_limit = true;
  error_I_limit_min = Min;
  error_I_limit_max = Max;
}

void PID::SetOutputLimit(int Min,int Max){
  output_limit = true;
  output_limit_min = Min;
  output_limit_max = Max;
}

void PID::ReSetITerm(){
  err_I = 0;
}
