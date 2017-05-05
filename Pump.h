#ifndef Pump_h
#define Pump_h

#include "Arduino.h"

class Pump {
  
  public:
    Pump(byte step_mtr_drv,byte step_mtr_dir,byte valve_input_drv,byte valve_output_drv);

    
    void set_valve_dirs(bool input_valve_dir,bool output_valve_dir);
    void pump(int step_size, bool dir);
    
    
  private:
    byte step_mtr_drv;  // Stepper motor driver pin
    byte step_mtr_dir;  // Stepper motor direction pin
    byte valve_input_drv;    // Valve in control pin
    byte valve_output_drv;   // Valve out control pin    

    void initialize();  // Initializes the pinout and initial state for stepper motor and valves
    
    void step_mtr_set_dir(bool dir);
    void step_mtr_actuate(bool dir);
};

#endif
