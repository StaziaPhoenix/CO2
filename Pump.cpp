#include "Arduino.h"
#include "Pump.h"


/**********     PUBLIC FUNCTIONS     **********/



/*
 * Constructor for pump object.  Then initializes the pins and initial pin states
 * 
 * @param step_mtr_drv stepper motor driver/actuator/control pin
 * @param step_mtr_dir stepper motor direction pin
 * @param valve_input_drv input valve driver/control pin (valve1)
 * @param valve_output_drv output valve driver/control pin (valve2)
 */
Pump::Pump(byte step_mtr_drv,byte step_mtr_dir,byte val_in_pin,byte val_out_pin) {
  
  this->step_mtr_drv=step_mtr_drv;
  this->step_mtr_dir=step_mtr_dir;
  this->valve_input_drv=val_in_pin;
  this->valve_output_drv=val_out_pin;

  initialize();
}

 /*
 * Sets the input and output valve directions
 * 
 * @param input_valve_dir 1 to close, 0 to open input valve
 * @param output_valve_dir 1 to close, 0 to open output valve
 */
void Pump::set_valve_dirs(bool input_valve_dir,bool output_valve_dir) {
  digitalWrite(this->valve_input_drv,input_valve_dir);
  digitalWrite(this->valve_output_drv,output_valve_dir);   
//  
//  if(input_valve_dir)
//    digitalWrite(this->valve_input_drv,HIGH);
//  else
//    digitalWrite(this->valve_input_drv,LOW);
//
//  if(output_valve_dir)
//    digitalWrite(this->valve_output_drv,HIGH);   
//  else
//    digitalWrite(this->valve_output_drv,LOW);   
}

/*
 * Actuates the valves and pump in a direction for a given step size
 * 
 * @param step_size how many times to perform a "micro" pump
 * @param direction in which to pump, 1 for outward, 0 for inward
 */
void Pump::pump(int step_size, bool dir) {
  if(dir) {
    step_mtr_set_dir(HIGH); // Set stepper motor (pump) to move outwards (i.e. dir=1)
    Serial.println("This pump is moving out");
  } else if(!dir){
    step_mtr_set_dir(LOW);  // Set stepper motor (pump) to move inwards (i.e. dir=0)
    Serial.println("This pump is moving in");
  }  

  Serial.println("This pump is moving!");
  
  for (int i=0;i<step_size;i++){
    Serial.println(i);
    
    step_mtr_actuate(HIGH);
    delay(9); // on for 9ms
    step_mtr_actuate(LOW);
    delay(11);  // off for 11ms or 30ms?
  }
}

void Pump::special_pump(bool dir) {
  if(dir) {
    step_mtr_set_dir(HIGH); // Set stepper motor (pump) to move outwards (i.e. dir=1)
    Serial.println("This pump is moving out");
  } else if(!dir){
    step_mtr_set_dir(LOW);  // Set stepper motor (pump) to move inwards (i.e. dir=0)
    Serial.println("This pump is moving in");
  }

  Serial.println("This pump is moving!");  
    
  step_mtr_actuate(HIGH);
  delay(9); // on for 9ms
  step_mtr_actuate(LOW);
  delay(11);  // off for 11ms or 30ms?
}



/**********     PRIVATE FUNCTIONS     **********/


/*
 * Initializes the pinout and initial state for stepper motor and valves
 */
void Pump::initialize() {
  
  // Set pinout configuration for stepper motor
  pinMode(this->step_mtr_drv,OUTPUT);
  pinMode(this->step_mtr_dir,OUTPUT);

  // Set pinout configuration for valves
  pinMode(this->valve_input_drv,OUTPUT);
  pinMode(this->valve_output_drv,OUTPUT);

  // Set initial state for stepper motor
  digitalWrite(this->step_mtr_drv,LOW); // Set stepper motor to OFF
  digitalWrite(this->step_mtr_dir,LOW); // Set stepper motor to be inward directed

  // Set initial state for valve
  digitalWrite(this->valve_input_drv,LOW);  // OPEN INPUT VALVE (VALVE 2)
  digitalWrite(this->valve_output_drv,LOW); // OPEN OUTPUT VALVE (VALVE 1)
}

/*
 * Sets the stepper motor direction
 * 
 * @param dir direction of stepper motor 1 for outward, 0 for inward
 */
void Pump::step_mtr_set_dir(bool dir) {
  digitalWrite(this->step_mtr_dir,dir);
//  if(dir)
//    digitalWrite(this->step_mtr_dir,HIGH);
//  else
//    digitalWrite(this->step_mtr_dir,LOW);
}

/*
 * Actuates the stepper motor
 * 
 * @param state 1 for motor ON, 0 for motor OFF
 */
void Pump::step_mtr_actuate(bool state) {
  digitalWrite(this->step_mtr_drv,state);
//  if(state)
//    digitalWrite(this->step_mtr_drv,HIGH);
//   else
//    digitalWrite(this->step_mtr_drv,LOW);
}

