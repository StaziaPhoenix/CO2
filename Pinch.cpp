#include "Arduino.h"
#include "Pinch.h"


/**********     PUBLIC FUNCTIONS     **********/



/*
 * Constructor for pump object.  Then initializes the pins and initial pin states
 * 
 * @param step_mtr_drv stepper motor driver/actuator/control pin
 * @param step_mtr_dir stepper motor direction pin
 * @param valve_input_drv input valve driver/control pin (valve1)
 * @param valve_output_drv output valve driver/control pin (valve2)
 */
Pinch::Pinch(byte step_mtr_drv) {
  this->step_mtr_drv=step_mtr_drv;
  close(); 
}

/*
 * Opens the Pinch Valve        
 */
void Pinch::open() {
    digitalWrite(this->step_mtr_drv,HIGH);
}

/*
 * Closes the Pinch Valve      
 */
void Pinch::close() {
    digitalWrite(this->step_mtr_drv,LOW);
}
