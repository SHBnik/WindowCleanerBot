#include "motor.h"




uint32_t motor_update_time = 0,rsencoder_time = 0;
enum SATE{idel,home,rsencoder,move,speed}move_state;
enum MOVE{relative,absolute}move_mode;

uint8_t move_dir;
uint32_t move_steps;




void HomeSense(){
  if(!digitalRead(HOME_PIN)){
    MSW_hit = false;
  }
  else{
    MSW_hit = true;
  }
}


void HOME_X(){
  IsHomed = false;
  move_state = home;
}

void MOTOR_move_one_step(bool dir,uint8_t timming){
  bool temp_dir = dir;


  if(millis() - motor_update_time >= timming){
    motor_update_time = millis();

    if(dir){pulses++;}
    else{
      if(pulses <= 0)
        pulses = 0;
      else
        pulses--;
    }

    if(!motor_pin_map){
      #if MOTOR_DIR == 0
        motor_pin_map = 0x01;
        MOTOR_Port = motor_pin_map;
      #elif MOTOR_DIR == 1
        motor_pin_map = 0x08;
        MOTOR_Port = motor_pin_map;
      #endif
    }
    else{
      #if MOTOR_DIR == 0
        if(dir){temp_dir = dir;}
        else{temp_dir = ~dir;}
      #elif MOTOR_DIR == 1
        if(dir){temp_dir = ~dir;}
        else{temp_dir = dir;}
      #endif

      if(temp_dir){
        motor_pin_map = motor_pin_map << 1;
        if(motor_pin_map == 0X10){
          motor_pin_map = 0x01;
        }
        MOTOR_Port = motor_pin_map;
      }
      else{ 
        motor_pin_map = motor_pin_map >> 1;
        if(motor_pin_map == 0X00){
          motor_pin_map = 0x08;
        }
        MOTOR_Port = motor_pin_map;
      }

    }
  }

}




void update_movment(){

  switch (move_state){

  case idel:
    break;

  case home:
    MOTOR_move_one_step(0,1);
    HomeSense();
    if(MSW_hit){
      move_state = rsencoder;
      rsencoder_time = millis();
      IsHomed = true;
      pulses = 0;
      Serial.println("Homed!");
    }

    break;

  case rsencoder:
    if (millis() - rsencoder_time >= 1000){
      encoder_pulse = 0;
      move_state = idel;
    }
    break;


  case move:
    if(move_steps){
      move_steps--;
      MOTOR_move_one_step(move_dir,1);
    }
    else{
      move_state = idel;
    }
    break;
  
  case speed:
    if(!no_move_flag){
      if(GET_X_POS <= 0 && speed_dir == 0){
      }
      else if(GET_X_POS >= 69 && speed_dir == 1){
      }
      else{
        MOTOR_move_one_step(speed_dir,speed_timming);
      }
    }
    break;


  }

    


}





void G1(){
  double newXValue;
  pid_flag = false;
  
  if(Commands.availableValue('X')){
    newXValue = Commands.GetValue('X');
    move_state = move;

    if(move_mode == absolute)
      newXValue = GET_X_POS - newXValue;
    else if (move_mode == relative)
      newXValue = -newXValue;

    if(newXValue < 0){
      move_dir = 1;
      move_steps = (uint32_t) (-newXValue/(float)X_PER_UNIT);
    }
    else if(newXValue > 0){
      move_dir = 0;
      move_steps = (uint32_t) (newXValue/(float)X_PER_UNIT);
    }
    }
  
}

void G91(){
  move_mode = relative;
  Commands.comment("relative");
}

void G90(){
  move_mode = absolute;
  Commands.comment("absolute");
}


void speed_mode(){
  move_state = speed;
}