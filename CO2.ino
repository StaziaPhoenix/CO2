// NOTE:  Need No line ending for prints to line up

#include "Pump.h"
#include "K30.h"
#include "Benchtop.h"

#define out 1         //Set direction out to be 1
#define in 0          //Set direction in to be 0

#define startswitch 9 //Button pin

#define rx 12
#define tx 13

/* Pump 8 */
#define step_mtr_drv 3        // pump steppin
#define step_mtr_dir 5        // pump dirpin
#define valve_input_pin 11    // pump input valve
#define valve_output_pin 10   // pump output valve

#define MAIN 0
#define PARAMETER 1

// Serial CMD
int input;                 //Initialize serial input
int stepSize = 0;

float syringe_rinse_speed     = 0; // speed that control syringe pushes to strip chamber during rinse (s2)
float rinse_volume            = 0; // volume of sample during rinse (s1)
float rinse_time              = 0; // how long we let the rinse sit in the stripping chamber
float acid_volume             = 0; // how much acid to push over acid_wait_time
float acid_wait_time          = 0; // how long to let acid sit in the chamber before starting integration
float sample_volume           = 0; // volume of sample during analysis (s1)
float syringe_sample_speed    = 0; // speed that control syringe pushes to strip chamber during analysis (s2)
float sample_wait_time        = 0; // how long to continue reading after sample integration time
float total_sample_integration_time = 0;

Benchtop benchtop;

//float * parameters[] = {&syringe_rinse_speed, &rinse_volume, &rinse_time, &acid_volume,
//                    &acid_wait_time, &sample_volume, &syringe_sample_speed,
//                    &sample_wait_time, &total_sample_integration_time};

typedef float (Benchtop::*getter)();
getter getters[9] = { &Benchtop::get_syringe_rinse_speed,
                      &Benchtop::get_rinse_volume,
                      &Benchtop::get_rinse_time,
                      &Benchtop::get_acid_volume,
                      &Benchtop::get_acid_wait_time,
                      &Benchtop::get_sample_volume,
                      &Benchtop::get_syringe_sample_speed,
                      &Benchtop::get_sample_wait_time,
                      &Benchtop::get_total_sample_integration_time
                    };

typedef void (Benchtop::*setter)(float);
setter setters[9] = { &Benchtop::set_syringe_rinse_speed,
                      &Benchtop::set_rinse_volume,
                      &Benchtop::set_rinse_time,
                      &Benchtop::set_acid_volume,
                      &Benchtop::set_acid_wait_time,
                      &Benchtop::set_sample_volume,
                      &Benchtop::set_syringe_sample_speed,
                      &Benchtop::set_sample_wait_time,
                      &Benchtop::set_total_sample_integration_time
                    };

int menu = MAIN;

// Valve & Pump
//Pump pump(3,5,11 ,12); // Initialize pump object
Pump pump(3,5,11,10); // Initialize pump object
//Pump(step motor/valve drive pin,step motor/valve direction pin,valve1/input-valve pin,valve2/output-valve pin);

K30 k30(rx, tx);

// CLI vars
//byte in_byte=0;
byte ack=0;
#define NONE 130
#define NOT_YET_STR "Not Implemented Yet"

void setup() {
  pinMode(startswitch, INPUT);

  Serial.begin(9600);

  pump.set_valve_dirs(LOW,LOW);  // Open both input valve and output valve
//  pump.pump(500,out);            //Drain the pump and plumbing
}


void loop() {
  while(!ack) {
    ack=get_ack();
    delay(3000);
  }

  if (menu == MAIN) {
    do_serial_cmd(get_serial_cmd());
  } else {
    do_parameter_cmd(get_serial_cmd());
  }
//  actuatePump();
//  detect();
}

void detect() {
  k30.sendRequest();
  unsigned long valCO2 = k30.getValue();
  Serial.print("Co2 ppm = ");
  Serial.println(valCO2);
}

void actuatePump() {
  if(Serial.available()) {
    input = Serial.parseInt();
    if(input != 0){
      stepSize = input;
    }
    if(stepSize > 500){
      stepSize = 500;
      Serial.println("500 is largest allowable step size");
    }else if(stepSize < 0){
      stepSize = 0;
      Serial.println("No negative numbers, dumb dumb");
    }
    Serial.print("Step size = ");
    Serial.println(stepSize);
  }
  
  
  if(digitalRead(startswitch) == HIGH){
    pump.set_valve_dirs(LOW,HIGH);  // OPEN INPUT VALVE (VALVE 1), CLOSE OUTPUT VALVE (VALVE 2)
    pump.pump(stepSize,in);
    Serial.println("I pumped in");
    
    pump.set_valve_dirs(HIGH,LOW);  // CLOSE INPUT VALVE (VALVE 1), OPEN OUTPUT VALVE (VALVE 2)
    pump.pump(stepSize,out);
    Serial.println("I pumped out");
  }
  delay(200);

}






/* -------- COMMAND LINE FUNCTIONS -------- */

void print_cmd_list() {
    Serial.print("\nCommands:\r\n");
    // new commands here
    Serial.print("\t<p>\tParameters Menu\n");
    Serial.print("\t<r>\tRun\n");
    Serial.print("\t<c>\tClean\n");
    Serial.print("\t<0>\tTest Syringe Pump\n");
    Serial.print("\t<1>\tTest Air Pump\n");
    Serial.print("\t<2>\tTest K30\n");
    Serial.print("\t<h>\tPrint Command List\n");
    Serial.println();
}

void print_parameter_menu() {
    Serial.print("\nParameters:\r\n");
    // new commands here
    Serial.print("\t<1>\tSyringe Rinse Speed (s)\t\t\t"); Serial.println(benchtop.get_syringe_rinse_speed());
    Serial.print("\t<2>\tRinse Volume (mL)\t\t\t"); Serial.println(benchtop.get_rinse_volume());
    Serial.print("\t<3>\tRinse Time (s)\t\t\t\t"); Serial.println(benchtop.get_rinse_time());
    Serial.print("\t<4>\tAcid Volume (mL)\t\t\t"); Serial.println(benchtop.get_acid_volume());
    Serial.print("\t<5>\tAcid Wait Time (s)\t\t\t"); Serial.println(benchtop.get_acid_wait_time());
    Serial.print("\t<6>\tSample Volume (mL)\t\t\t"); Serial.println(benchtop.get_sample_volume());
    Serial.print("\t<7>\tSyringe Sample Speed (m/s)\t\t"); Serial.println(benchtop.get_syringe_sample_speed());
    Serial.print("\t<8>\tSample Wait Time(s)\t\t\t"); Serial.println(benchtop.get_sample_wait_time());
    Serial.print("\t<9>\tTotal Sample Integration Time(s)\t"); Serial.println(benchtop.get_total_sample_integration_time());
    Serial.print("\t<h>\tReturn to main menu\n");
    Serial.println();
}

void do_serial_cmd(byte cmd) {
    switch(cmd) {
        // Add more commands
        case('p'): // Set parameters menu
          menu = PARAMETER;
          print_parameter_menu();
          print_new_cmd_line();
          break;
        case('r'): // run analysis
          Serial.println(NOT_YET_STR);
          print_new_cmd_line();
          break;
        case('c'): // run cleaning cycle
          Serial.println(NOT_YET_STR);
          print_new_cmd_line();
          break;
        case('0'): // test the syringe pump system
          for (int i = 0; i < 10; i++) {
            actuatePump();
          }
          print_new_cmd_line();
          break;
        case('1'): // test the air pump system
          Serial.println(NOT_YET_STR);
          print_new_cmd_line();
          break;
        case('2'): // test the k30
          for (int i = 0; i < 10; i++) {
            detect();
          }
          print_new_cmd_line();
          break;
        case('h'):
          print_cmd_list();
          print_new_cmd_line();
          break;
        case(NONE):
          break;
    }
}

void updateVariable(byte idx) {
  Serial.print("\tEnter the value you want to set.\n");
  while (!Serial.available()) {
    delay(5);
  }
  Serial.print("\tUpdating... ");
  (benchtop.*(setters[idx]))(Serial.readString().toFloat());
  Serial.println((benchtop.*(getters[idx]))());
  print_parameter_menu();
  print_new_cmd_line();
}

void do_parameter_cmd(byte cmd) {
    switch(cmd) {
      case('h'):
        menu = MAIN;
        print_cmd_list();
        print_new_cmd_line();
        break;
      case(NONE):
        break;
      default:
        byte idx = cmd-'1';
        if (idx > -1 && idx < 9) {
          updateVariable(idx);
          break;
        }
        Serial.println("That isn't a command");
        print_parameter_menu();
        print_new_cmd_line();
        break;
    }
}

bool get_ack() {
    Serial.println("\nPress <h> for command list");
    Serial.print(">");
    byte in_byte=Serial.read();

    if(in_byte == 'h') {
      Serial.print((char)in_byte);
      print_cmd_list();
      print_new_cmd_line();
      return true;
    }
    return false;
}

byte get_serial_cmd() {
  byte in_byte;

  if(Serial.available()) {
    in_byte=Serial.read();
    Serial.println((char)in_byte); 
    return in_byte;
  } else {
    return NONE;
  }
}


void print_new_cmd_line() {
  Serial.print(">");
}

