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
    syringe_rinse_speed=  0.0;
    rinse_volume=         0.0;
    rinse_time=           0.0;
    acid_volume=          0.0;
    acid_wait_time=       0.0;
    sample_volume=        0.0;
    syringe_sample_speed= 0.0;
    sample_wait_time=     0.0;
    integration_time=     0.0;
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
void Benchtop::set_integration_time(float integration_time) {
   this->integration_time=integration_time;
}

/*
 * Gets the total sample integration time
 */
float Benchtop::get_integration_time() {
   return this->integration_time;
}






/**********     PUBLIC FUNCTIONS     **********/
/*
 * Rinse state
 */
void Benchtop::rinse(Pump & strip,Pump & syringe) {
  control_syringe(strip,OPEN,CLOSE);
  strip_chamber(syringe,OPEN,CLOSE);
  fill_rinse(syringe);

  // Rinse into stripping chamber
  control_syringe(strip,CLOSE,OPEN);
  strip_chamber(syringe,CLOSE,OPEN);
  rinse_stripping_chamber(syringe);

  delay(this->rinse_time);

  // TODO: Empty rinse
  strip_chamber(strip,OPEN,CLOSE);
}

/*
 * Waste ***** probably wants IO arguments
 */
void Benchtop::control_syringe(Pump & pump,bool waste,bool sample) {
  pump.set_valve_dirs(waste,sample);
}

/*
 * Sample ***** probably wants IO arguments
 */
void Benchtop::strip_chamber(Pump & pump,bool sample,bool strip) {
  pump.set_valve_dirs(sample,strip);
}

/*
 * Fill Rinse w/ Syringe Pump?
 */
void Benchtop::fill_rinse(Pump & pump) {
  pump.pump(vol_2_steps(rinse_volume),IN);
}

/*
 * Rinse into Stripping Chamber
 */
void Benchtop::rinse_stripping_chamber(Pump & pump) {
  pump.pump(spd_2_steps(syringe_sample_speed),OUT);
}

/*
 * Empty Rinse
 */
void Benchtop::empty_rinse() {
  
}

/*
 * Start analysis
 */
void Benchtop::analysis(Pump & strip,Pump & syringe,K30 & k30,byte acid_pump, File & myFile) {
  unsigned int start_time=millis();
  unsigned int check_time=0;
  unsigned int last_time=0;
  unsigned int _2seconds=2000;
  unsigned int acid_start_time=0;
  unsigned int integration_start_time=0;
  unsigned int sample_wait_start_time=0;
  result_vec.push_back(detect_co2(k30));  // 1
  
  strip_chamber(strip,CLOSE,OPEN);
  // TODO: actuate acid pump; push acid_volume into stripping chamber; has delay
  digitalWrite(acid_pump, HIGH);
  delay(500);
  digitalWrite(acid_pump, LOW);
  // END ACID PUMP - ASK ABOUT THIS
  while(check_time=millis()-start_time < _2seconds)
  ;
  result_vec.push_back(detect_co2(k30));  // 2
  acid_start_time=millis();
  
  fill_sample(syringe);
  
  while(last_time=millis()-check_time < _2seconds)
  ;
  result_vec.push_back(detect_co2(k30));  // 3
  
  check_time=last_time;

  while(millis()-acid_start_time < acid_wait_time) {
    // Making sure we waiting the entired acid wait time
    while(last_time=millis()-check_time < _2seconds)  // Might be too long, might not matter tho
    ;
    result_vec.push_back(detect_co2(k30));
    
    check_time=last_time;
  }
  control_syringe(syringe,CLOSE,OPEN);
//  sample_stripping_chamber(syringe);

  integration_start_time=check_time=millis();

  for(int i=0;i<spd_2_steps(syringe_sample_speed);i++) { //???????????? pump full volume at normal speed
    syringe.special_pump(OUT);
    
    if(last_time=millis()-check_time > _2seconds) {
      result_vec.push_back(detect_co2(k30));
      check_time=last_time;
    } 
  }

  while(millis() - integration_start_time < integration_time)  {// Might be too long, might not matter tho
    if(last_time=millis()-check_time > _2seconds) {
      result_vec.push_back(detect_co2(k30));
      check_time=last_time;
    } 
  }
    result_vec.push_back(detect_co2(k30));
  
  sample_wait_start_time=check_time=millis();
  while(millis() - sample_wait_start_time < sample_wait_time) {
    if(last_time=millis()-check_time > _2seconds) {
      result_vec.push_back(detect_co2(k30));
      check_time=last_time;
    } 
  }

  strip_chamber(strip,OPEN,CLOSE);
  // set valves and shit

  // write results to file
  write_out(myFile);
}

/*
 * Record peak from CO2 Detector (K30)
 */
int Benchtop::detect_co2(K30 & k30) { // TODO: MAKE THIS SMALLER?
  k30.sendRequest();
  return k30.getValue();
}

/*
 * Add acid to stripping chamber
 */
void Benchtop::add_acid_stripping_chamber() {
  
}

/*
 * Record Sample Temperature
 */
void Benchtop::record_sample_temp() {
  
}

/*
 * Fill Sample w/ Syringe Pump?  Might want to make one function with one above and  and use input argument
 */
void Benchtop::fill_sample(Pump & pump) {
  pump.pump(vol_2_steps(sample_volume),IN);
}

/*
 * Start peak integration for user defined length of time
 */
void Benchtop::start_peak_integration() {
  
}

/*
 * Sample stripping chamber during analysis
 */
void Benchtop::sample_stripping_chamber(Pump & pump) {
  pump.pump(spd_2_steps(syringe_sample_speed),OUT);
}

/*
 * Empty stripping chamber
 */
void Benchtop::empty_stripping_chamber() {
  
}

int Benchtop::vol_2_steps(float volume) { // TODO: CALCULATE THIS SHIT
//  return volume;
  return 500; 
}

int Benchtop::spd_2_steps(float spd) { // TODO: CALCULATE THIS SHIT
//  return spd;
  return 500; 
}

void Benchtop::write_out(File & myFile) {
  for (int i = 0; i < result_vec.size(); i++) {
    myFile.println(result_vec[i]);
  }
}

