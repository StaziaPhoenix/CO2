#ifndef Pump_h
#define Pump_h

#include "Arduino.h"

class Pump {
  
   public:
        /*
         * Constructor for pump object
         * 
         * @param step_mtr_drv stepper motor driver/actuator/control pin
         * @param step_mtr_dir stepper motor direction pin
         * @param valve_input_drv input valve driver/control pin (valve1)
         * @param valve_output_drv output valve driver/control pin (valve2)
         */
        Pump(byte step_mtr_drv,byte step_mtr_dir,byte valve_input_drv,byte valve_output_drv);        
    
        /*
         * Sets the input and output valve directions
         * 
         * @param input_valve_dir 1 to close, 0 to open input valve
         * @param output_valve_dir 1 to close, 0 to open output valve
         */
        void set_valve_dirs(bool input_valve_dir,bool output_valve_dir);
    
        /*
         * Actuates the valves and pump in a direction for a given step size
         * 
         * @param step_size how many times to perform a "micro" pump
         * @param delay how long to wait for pump
         * @param direction in which to pump, 1 for outward, 0 for inward
         */
        void pump(int step_size,int _delay,bool dir);

        void special_pump(int _delay,bool dir);
    
    private:
        byte step_mtr_drv;        // Stepper motor driver pin
        byte step_mtr_dir;        // Stepper motor direction pin
        byte valve_input_drv;     // Valve input control pin
        byte valve_output_drv;    // Valve output control pin    
    
        /*
         * Initializes the pinout and initial state for stepper motor and valves
         */
        void initialize();
    
        /*
         * Sets the stepper motor direction
         * 
         * @param dir direction of stepper motor 1 for outward, 0 for inward
         */
        void step_mtr_set_dir(bool dir);
        
        /*
         * Actuates the stepper motor
         * 
         * @param state 1 for motor ON, 0 for motor OFF
         */
        void step_mtr_actuate(bool dir);
};

#endif
