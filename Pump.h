#ifndef Pump_h
#define Pump_h

#include "Arduino.h"

class Pump {
  public:
    Pump(byte step_mtr_pin,byte step_mtr_dir,byte val1_pin,byte val2_pin);
  private:
    byte steppin;     //Stepper motor pin
    byte dirpin;      //Motor direction pin
    byte valve1;     //Pin for Valve 1 control (input valve)
    byte valve2;     //Pin for Valve 2 control (output valve)
//    const int out = 1;         //Set direction out to be 1
//    const int in = 0;          //Set direction in to be 0
//    int stepSize = 0;    
};

#endif
