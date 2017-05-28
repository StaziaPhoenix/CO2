#ifndef Benchtop_h
#define Benchtop_h

#include "Arduino.h"
#include "Pump.h"
#include "K30.h"
#include "Vector.h"

#define CLOSE 1         //Set direction out to be 1
#define OPEN 0          //Set direction in to be 0

#define OUT 1         //Set direction out to be 1
#define IN 0          //Set direction in to be 0

class Benchtop {
  
   public:
        /*
         * Constructor for Benchtop object
         *          
         */
        Benchtop();        
    
       
        /*
         * Sets the syringe rinse speed
         * 
         * @param syringe_rinse_speed to set
         */
        void set_syringe_rinse_speed(float syringe_rinse_speed);

        /*
         * Gets the syringe rinse speed         
         */
        float get_syringe_rinse_speed();

         /*
         * Sets the rinse volume
         * 
         * @param rinse_volume to set
         */
        void set_rinse_volume(float rinse_volume);

        /*
         * Gets the rinse volume
         */
        float get_rinse_volume();

        /*
         * Sets the rinse time
         * 
         * @param rinse_time to set
         */
        void set_rinse_time(float rinse_time);

        /*
         * Gets the rinse time
         */
        float get_rinse_time();

        /*
         * Sets the acid volume
         * 
         * @param acid_volume to set
         */
        void set_acid_volume(float acid_volume);

        /*
         * Gets the acid volume
         */
        float get_acid_volume();

        /*
         * Sets the acid wait time
         * 
         * @param acid_wait_time to set
         */
        void set_acid_wait_time(float acid_wait_time);

        /*
         * Gets the acid wait time
         */
        float get_acid_wait_time();
        
        /*
         * Sets the sample volume
         * 
         * @param sample_volume to set
         */
        void set_sample_volume(float sample_volume);

        /*
         * Gets the sample volume
         */
        float get_sample_volume();

        /*
         * Sets the syringe sample speed
         * 
         * @param syringe_sample_speed to set
         */
        void set_syringe_sample_speed(float syringe_sample_speed);

        /*
         * Gets the syringe sample speed
         */
        float get_syringe_sample_speed();

        /*
         * Sets the sample wait time
         * 
         * @param sample_wait_time to set
         */
        void set_sample_wait_time(float sample_wait_time);

        /*
         * Gets the sample wait time
         */
        float get_sample_wait_time();

        /*
         * Sets the total sample integration time
         * 
         * @param total_sample_integration_time to set
         */
        void set_total_sample_integration_time(float total_sample_integration_time);

        /*
         * Gets the total sample integration time
         */
        float get_total_sample_integration_time();   

        /*
         * Rinse state
         */
        void rinse(Pump & strip,Pump & syringe);

        /*
         * Start analysis
         */
        void analysis(Pump & strip,Pump & syringe,K30 & k30,byte acid_pump);
    
    private:
        float syringe_rinse_speed;
        float rinse_volume;
        float rinse_time;
        float acid_volume;
        float acid_wait_time;
        float sample_volume;
        float syringe_sample_speed;
        float sample_wait_time;
        float total_sample_integration_time;
        
        Vector<unsigned long> result_vec;   // TODO: MAKE THIS SMALLER?

        

        /*
         * Waste ***** probably wants IO arguments
         */
        void control_syringe(Pump & pump,bool waste,bool sample);

        /*
         * Sampple ***** probably wants IO arguments
         */
        void strip_chamber(Pump & pump,bool sample,bool strip);

        /*
         * Fill Rinse w/ Syringe Pump?
         */
        void fill_rinse(Pump & syringe);

        /*
         * Rinse into Stripping Chamber
         */
        void rinse_stripping_chamber(Pump & pump);

        /*
         * Empty Rinse
         */
        void empty_rinse();

        

        /*
         * Record peak from CO2 Detector (K30)
         */
        unsigned long detect_co2(K30 & k30);

        /*
         * Add acid to stripping chamber
         */
        void add_acid_stripping_chamber();

        /*
         * Record Sample Temperature
         */
        void record_sample_temp();

        /*
         * Fill Sample w/ Syringe Pump?  Might want to make one function with one above and  and use input argument
         */
        void fill_sample(Pump & syringe);

        /*
         * Start peak integration for user defined length of time
         */
        void start_peak_integration();

        /*
         * Sample stripping chamber during analysis
         */
        void sample_stripping_chamber(Pump & pump);

        /*
         * Empty stripping chamber
         */
        void empty_stripping_chamber();

        float vol_2_steps(float volume);
        float spd_2_steps(float spd);
};

#endif
