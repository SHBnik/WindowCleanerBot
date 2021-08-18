#include <Arduino.h>
#include "imu.h"


MPU9250 mpu1;
bool buzzer_for_euler = false;


void update_mpu(){
  if (mpu1.update()) {
    
    if(millis() >= 10000){
      if(abs(abs(mpu1.getPitch()) - pitch_init) >= PITCH_DEV_LIMIT ){

        turn_buuzer_on_off(true);
        buzzer_for_euler = true;
      }
      else if(abs((abs(mpu1.getRoll()) - roll_init)) >= ROLL_DEV_LIMIT ){

        turn_buuzer_on_off(true);
        buzzer_for_euler = true;
      }
      else{
        if(buzzer_for_euler){
          turn_buuzer_on_off(false);
          buzzer_for_euler = false;
        }
      }

    }else{

      pitch_init = abs( mpu1.getPitch());
      roll_init = abs( mpu1.getRoll());


    }

  }
}

void init_mpu(){
  Wire.begin();
  delay(2000);
  mpu1.setup(0x68);

}




void turn_buuzer_on_off(bool state){
  // if(state){digitalWrite(BUZZER_PIN,0);}
  // else     {digitalWrite(BUZZER_PIN,1);}
  digitalWrite(BUZZER_PIN,state);

}


void set_roll_pitch(){
  if(Commands.availableValue('P')){
    PITCH_DEV_LIMIT = Commands.GetValue('P');
  }
  if(Commands.availableValue('R')){
    ROLL_DEV_LIMIT = Commands.GetValue('R');
  }
  
}

void buzzer(){
  if(Commands.availableValue('O')){
    if(Commands.GetValue('O') == 1){
      turn_buuzer_on_off(1);
    }
    else{
      turn_buuzer_on_off(0);
    }
  }
}