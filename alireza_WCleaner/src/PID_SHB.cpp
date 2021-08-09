
#include "PID_SHB.h"

PID::PID(float Kp, float Ki, float Kd, int shift){
  kp = Kp;
  ki = Ki;
  kd = Kd;
  Y_shift = shift;
}




float PID::Compute(int target , int sensor_value ){
  float output;
  float time_changed;
  timer = millis();
  time_changed = (timer - timer_old);
  

  err = sensor_value - target;
  if(error_limit){
    err = constrain(err,error_limit_min,error_limit_max);
  }  
  err_D = (float)(err - err_old) /(float) time_changed;
  err_I += (float)err * time_changed;
  if(error_I_limit){
    err_I = constrain(err_I,error_I_limit_min,error_I_limit_max);
  }
  output = Y_shift + kp * err + kd * err_D + ki * err_I;
  if(output_limit){
    output = constrain(output,output_limit_min,output_limit_max);
  }

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
