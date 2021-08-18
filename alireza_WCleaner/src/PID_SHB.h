#ifndef PID_SHB_h
#define PID_SHB_h

#include <Arduino.h>


class PID{


  public:


    PID::PID(float, float, float, int);
    float PID::Compute(float , float);               
    void PID::SetErrorLimit(int ,int);
    void PID::SetErrorILimit(int ,int);
    void PID::SetOutputLimit(int ,int);
    void PID::ReSetITerm();

  private:

    
	  float kp;                  
    float ki;                  
    float kd;                  
    int Y_shift;

    float err = 0;
    float err_old = 0;
    float err_I;
    float err_D;

    bool error_limit = false;
    bool error_I_limit = false;
    bool output_limit = false;
    
    int error_limit_min;
    int error_limit_max;
    
    int error_I_limit_min;
    int error_I_limit_max;
    
    int output_limit_min;
    int output_limit_max;
    
    long timer;
    long timer_old;

};
#endif

