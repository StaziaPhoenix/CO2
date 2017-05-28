#include "Arduino.h"
#include "Benchtop.h"


/**********     PUBLIC FUNCTIONS     **********/



/*
 * Constructor for pump object.  Then initializes the pins and initial pin states
 * 
 * @param step_mtr_drv stepper motor driver/actuator/control pin
 * @param step_mtr_dir stepper motor direction pin
 * @param valve_input_drv input valve driver/control pin (valve1)
 * @param valve_output_drv output valve driver/control pin (valve2)
 */
Benchtop::Benchtop() {
    syringe_rinse_speed=3.3;
    rinse_volume=0.0;
    rinse_time=0.0;
    acid_volume=0.0;
    acid_wait_time=0.0;
    sample_volume=0.0;
    syringe_sample_speed=0.0;
    sample_wait_time=0.0;
    total_sample_integration_time=0.0;
}


/*
 * Sets the syringe rinse speed
 * 
 * @param syringe_rinse_speed to set
 */
void Benchtop::set_syringe_rinse_speed(float syringe_rinse_speed) {
    this->syringe_rinse_speed=syringe_rinse_speed;
}

/*
 * Gets the syringe rinse speed         
 */
float Benchtop::get_syringe_rinse_speed() {
    return this->syringe_rinse_speed;
}

 /*
 * Sets the rinse volume
 * 
 * @param rinse_volume to set
 */
void Benchtop::set_rinse_volume(float rinse_volume) {
    this->rinse_volume=rinse_volume;
}

/*
 * Gets the rinse volume
 */
float Benchtop::get_rinse_volume() {
    return this->rinse_volume;
}

/*
 * Sets the rinse time
 * 
 * @param rinse_time to set
 */
void Benchtop::set_rinse_time(float rinse_time) {
    this->rinse_time=rinse_time;
}

/*
 * Gets the rinse time
 */
float Benchtop::get_rinse_time() {
    return this->rinse_time;
}

/*
 * Sets the acid volume
 * 
 * @param acid_volume to set
 */
void Benchtop::set_acid_volume(float acid_volume) {
    this->acid_volume=acid_volume;
}

/*
 * Gets the acid volume
 */
float Benchtop::get_acid_volume() {
    return this->acid_volume;
}

/*
 * Sets the acid wait time
 * 
 * @param acid_wait_time to set
 */
void Benchtop::set_acid_wait_time(float acid_wait_time) {
    this->acid_wait_time=acid_wait_time;
}

/*
 * Gets the acid wait time
 */
float Benchtop::get_acid_wait_time() {
    return this->acid_wait_time;
}

/*
 * Sets the sample volume
 * 
 * @param sample_volume to set
 */
void Benchtop::set_sample_volume(float sample_volume) {
    this->sample_volume=sample_volume;
}

/*
 * Gets the sample volume
 */
float Benchtop::get_sample_volume() {
    return this->sample_volume;
}

/*
 * Sets the syringe sample speed
 * 
 * @param syringe_sample_speed to set
 */
void Benchtop::set_syringe_sample_speed(float syringe_sample_speed) {
    this->syringe_sample_speed=syringe_sample_speed;
}

/*
 * Gets the syringe sample speed
 */
float Benchtop::get_syringe_sample_speed() {
    return this->syringe_sample_speed;
}

/*
 * Sets the sample wait time
 * 
 * @param sample_wait_time to set
 */
void Benchtop::set_sample_wait_time(float sample_wait_time) {
    this->sample_wait_time=sample_wait_time;
}

/*
 * Gets the sample wait time
 */
float Benchtop::get_sample_wait_time() {
    return this->sample_wait_time;
}

/*
 * Sets the total sample integration time
 * 
 * @param total_sample_integration_time to set
 */
void Benchtop::set_total_sample_integration_time(float total_sample_integration_time) {
   this->total_sample_integration_time=total_sample_integration_time;
}

/*
 * Gets the total sample integration time
 */
float Benchtop::get_total_sample_integration_time() {
   return this->total_sample_integration_time;
}






/**********     PUBLIC FUNCTIONS     **********/
/*
 * Rinse state
 */
void rinse_state() {
  
}

/*
 * Waste ***** probably wants IO arguments
 */
void waste() {
  
}

/*
 * Fill Rinse w/ Syringe Pump?
 */
void fill_rinse() {
  
}

/*
 * Rinse into Stripping Chamber
 */
void rinse_stripping_chamber() {
  
}

/*
 * Empty Rinse
 */
void empty_rinse() {
  
}

/*
 * Start analysis
 */
void start_analysis() {
  
}

/*
 * Record peak from CO2 Detector (K30)
 */
void detect_co2() {
  
}

/*
 * Add acid to stripping chamber
 */
void add_acid_stripping_chamber() {
  
}

/*
 * Record Sample Temperature
 */
void record_sample_temp() {
  
}

/*
 * Fill Sample w/ Syringe Pump?  Might want to make one function with one above and  and use input argument
 */
void fill_sample() {
  
}

/*
 * Start peak integration for user defined length of time
 */
void start_peak_integration() {
  
}

/*
 * Sample stripping chamber during analysis
 */
void sample_stripping_chamber() {
  
}

/*
 * Empty stripping chamber
 */
void empty_stripping_chamber() {
  
}

