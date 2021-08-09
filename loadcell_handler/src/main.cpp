#include <Arduino.h>
#include "loadcell.h"



bool new_data = false;
float data = 0;


void setup() {
  Serial.begin(9600);
  init_loadcell();
  
  while(Serial.read() != 'q');
}

void loop() {
  update_loadcell();
  if(Serial.available()){
    if(Serial.read() == 't'){
      loadcell_tare();
    }
  }

  if(new_data){
    Serial.println(data);
  }
}