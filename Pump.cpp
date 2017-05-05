#include "Arduino.h"
#include "Pump.h"


/**********     PUBLIC FUNCTIONS     **********/



Pump::Pump(byte step_mtr_drv,byte step_mtr_dir,byte val_in_pin,byte val_out_pin) {
  
  this->step_mtr_drv=step_mtr_drv;
  this->step_mtr_dir=step_mtr_dir;
  this->valve_input_drv=val_in_pin;
  this->valve_output_drv=val_out_pin;

  initialize();
}

void Pump::set_valve_dirs(bool input_valve_dir,bool output_valve_dir) {
  digitalWrite(this->valve_input_drv,input_valve_dir);
  digitalWrite(this->valve_output_drv,output_valve_dir);   
}

void Pump::pump(int step_size, bool dir) {
  if(dir) {
    step_mtr_set_dir(HIGH); // Set stepper motor (pump) to move outwards (i.e. dir=1)
//    digitalWrite(dirpin,HIGH); //Set pump moving outwards with dir=1
    Serial.println("This pump is moving out");
  } else if(!dir){
    step_mtr_set_dir(LOW);
//    digitalWrite(dirpin,LOW);  // Set stepper motor (pump) to move inwards (i.e. dir=0)
    Serial.println("This pump is moving in");
  }
  
  delay(15);  // Delete?  Do we need this?

  Serial.println("This pump is moving!");
  
  for (int i=0;i<step_size;i++){
    Serial.println(i);
    
//    digitalWrite(steppin,HIGH);
    step_mtr_actuate(HIGH);
    delay(9); // on for 9ms
//    digitalWrite(steppin,LOW);
    step_mtr_actuate(LOW);
    delay(11);  // off for 11ms or 30ms?
  }
}



/**********     PRIVATE FUNCTIONS     **********/



void Pump::initialize() {
  
  // Set pinout configuration for stepper motor
  pinMode(this->step_mtr_drv,OUTPUT);
  pinMode(this->step_mtr_dir,OUTPUT);

  // Set pinout configuration for valves
  pinMode(this->valve_input_drv,OUTPUT);
  pinMode(this->valve_output_drv,OUTPUT);

  // Set initial state for stepper motor
  digitalWrite(this->step_mtr_drv,LOW);  //Initialize pump to off
  digitalWrite(this->step_mtr_dir,LOW);   //Direction low is pump moving inwards

  // Set initial state for valve
  digitalWrite(this->valve_input_drv,LOW);  
  digitalWrite(this->valve_output_drv,LOW);   //OPEN BOTH VALVES  
}

void Pump::step_mtr_set_dir(bool dir) {
  if(dir)
    digitalWrite(this->step_mtr_dir,HIGH);
  else
    digitalWrite(this->step_mtr_dir,LOW);
}

void Pump::step_mtr_actuate(bool state) {
  if(state)
    digitalWrite(this->step_mtr_drv,HIGH);
   else
    digitalWrite(this->step_mtr_drv,LOW);
}

