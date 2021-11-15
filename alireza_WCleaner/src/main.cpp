#include <Arduino.h>
#include "motor.h"
#include "imu.h"
#include "encoder.h"
#include "config.h"
#include "gcode.h"
#include "ardcell.h"
#include "PID_SHB.h"
#include "Filters.h"
#include "MassFormula.h"

void PinInit();
void Report();
void repeat_report();
void pid_active();

bool MSW_hit = false;
bool IsHomed = false;
uint8_t motor_pin_map = 0X00;
uint16_t encoder_pulse = 0;
float pitch_init, roll_init;
uint32_t pulses = 0;

float init_end_mass = 0;
float mass = 0;
bool new_mass_data_flag = false;

uint16_t repeat_time = 0;
bool is_repeat_time = false;
uint32_t last_report_time = 0;

float motor_speed = 0;
uint8_t speed_dir = 0;
float speed_timming = 0;
bool no_move_flag = false;


uint8_t weight_setpoint = 0;
bool pid_flag = false;

uint8_t PITCH_DEV_LIMIT = 20,ROLL_DEV_LIMIT = 20;

// G1 move
//G91 relative
//G90 absolute
commandscallback commands[NO_GCODE_COMMANDS] = {{"G28",HOME_X},{"M100",Report},{"M105",repeat_report},
  {"G1",G1},{"G90",G90},{"G91",G91},{"M50",ardcell_tare},{"G10",pid_active},{"M51",set_roll_pitch},{"M1",buzzer}};
gcode Commands(NO_GCODE_COMMANDS,commands);

PID weight_pid(KP, KI, KD, 0);

FilterOnePole lowpassFilter( LOWPASS, 1 ); 
RunningStatistics lowpassFilterStats;    


void setup() {
  Commands.begin(9600);
  init_mpu();
  PinInit();
  ardcell_init();
  weight_pid.SetOutputLimit(-1000, 1000);
  weight_pid.SetErrorILimit(-10,10);
  lowpassFilterStats.setWindowSecs( 0.1);
}

void loop() {
  Commands.available();
  update_mpu();
  update_movment();
  update_ardcell();

  if(is_repeat_time){
    if(millis()-last_report_time >= repeat_time){
      last_report_time = millis();
      Report();
    }
  }



  if(pid_flag){
    if(new_mass_data_flag){
      new_mass_data_flag = false;

      // if(abs(weight_setpoint - mass) > 0.5){
      //   weight_pid.ReSetITerm();
      // }
      float calc_mass = force_gram(GET_X_POS,read_angle());
      motor_speed = weight_pid.Compute(weight_setpoint,calc_mass);
      // motor_speed = weight_pid.Compute(weight_setpoint,mass);
      if(motor_speed >= 0)  speed_dir = 0;
      else                  speed_dir = 1;

      if(motor_speed == 0){
        no_move_flag = true;
      }
      else{
        no_move_flag = false;
        speed_timming = 1/(float)abs(motor_speed);
      }
    }
  }

}






void Report(){
  Serial.print("angle:");
  Serial.print(read_angle());
  Serial.print(" ");
  Serial.print("roll:");
  Serial.print(roll_init);
  Serial.print(" ");
  Serial.print("pitch:");
  Serial.print(pitch_init);
  Serial.print(" ");
  Serial.print("x_distance:");
  Serial.print(GET_X_POS);
  Serial.print(" ");
  Serial.print("weight:");
  // lowpassFilter.input(mass);
  // lowpassFilterStats.input( lowpassFilter.output() );
  Serial.print(mass);
  Serial.print("\n");
}


void repeat_report(){
  if(is_repeat_time)  is_repeat_time = false;

  if(Commands.availableValue('T')){
    repeat_time = Commands.GetValue('T');
    is_repeat_time = true;  
  }
}




void pid_active(){
  if(Commands.availableValue('P')){
    weight_setpoint = Commands.GetValue('P');  
    pid_flag = true;
    speed_mode();
  }
}



void PinInit(){
  pinMode(HOME_PIN,INPUT_PULLUP);
  pinMode(ENCODER_A_PIN,INPUT_PULLUP);
  pinMode(ENCODER_B_PIN,INPUT_PULLUP);
  pinMode(BUZZER_PIN,OUTPUT);
  DDRF = DDRF | 0B00001111;
  motor_pin_map = 0X00; 
  MOTOR_Port = motor_pin_map;

  attachInterrupt(digitalPinToInterrupt(ENCODER_A_PIN),encoder_int1,RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER_B_PIN),encoder_int2,RISING);
}












