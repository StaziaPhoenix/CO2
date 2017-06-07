#ifndef Pinch_h
#define Pinch_h

#include "Arduino.h"

class Pinch {
  
   public:
        /*
         * Constructor for Pinch Valve object
         * 
         * @param step_mtr_drv Pinch valve driver/actuator/control pin         
         */
        Pinch(byte step_mtr_drv);        
    
        /*
         * Opens the Pinch Valve        
         */
        void open();
    
        /*
         * Closes the Pinch Valve      
         */
        void close();        
    
    private:
        byte step_mtr_drv;        // Stepper motor driver pin                   
};

#endif
