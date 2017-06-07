// NOTE:  Need No line ending for prints to line up

#include "Pump.h"
#include "Pinch.h"
#include "K30.h"
#include "Benchtop.h"
#include "Vector.h"
#include <SD.h>

#define out 1         //Set direction out to be 1
#define in 0          //Set direction in to be 0

#define startswitch 9 //Button pin

#define rx 12
#define tx 13

#define MAIN 0
#define PARAMETER 1

#define _sd 53

// Serial CMD
int input;                 //Initialize serial input
int stepSize = 0;
String sample_name = "FAKE";
String file_name = "test.txt";

Benchtop benchtop;
File myFile;

typedef float (Benchtop::*getter)();
getter getters[9] = { &Benchtop::get_syringe_rinse_speed,
                      &Benchtop::get_rinse_volume,
                      &Benchtop::get_rinse_time,
                      &Benchtop::get_acid_volume,
                      &Benchtop::get_acid_wait_time,
                      &Benchtop::get_sample_volume,
                      &Benchtop::get_syringe_sample_speed,
                      &Benchtop::get_sample_wait_time,
                      &Benchtop::get_integration_time
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
                      &Benchtop::set_integration_time
                    };

int menu = MAIN;
#define cs_mtr_drv 3        // control syringe steppin
#define cs_mtr_dir 5        // control syringe dirpin
#define cs_input_pin 6    // control syringe input valve
#define cs_output_pin 7   // control syringe output valve

#define sc_mtr_drv 8        // pump steppin

// Valve & Pump
Pump control_syringe(cs_mtr_drv,cs_mtr_dir,cs_input_pin,cs_output_pin); // Initialize pump object
Pinch strip_chamber(sc_mtr_drv); // Initialize pump object

#define acid_pump_drv 9  // TODO: change this shit
Pinch acid_pump(acid_pump_drv);

//Pump(step motor/valve drive pin,step motor/valve direction pin,valve1/input-valve pin,valve2/output-valve pin);

K30 k30(rx, tx);

// CLI vars
byte ack=0;
#define NONE 130
#define NOT_YET_STR "Not Implemented Yet"



void setup() {
//  pinMode(acid_pump, OUTPUT);

  Serial.begin(9600);
  
  Serial.print("Initializing SD card...");
  if (!SD.begin(_sd)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  benchtop.flush(control_syringe);
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
//  if(Serial.available()) {
//    input = Serial.parseInt();
//    if(input != 0){
//      stepSize = input;
//    }
//    if(stepSize > 500){
//      stepSize = 500;
//      Serial.println("500 is largest allowable step size");
//    }else if(stepSize < 0){
//      stepSize = 0;
//      Serial.println("No negative numbers, dumb dumb");
//    }
//    Serial.print("Step size = ");
//    Serial.println(stepSize);
//  }
  
    stepSize = 500;
//  if(digitalRead(startswitch) == HIGH){
    control_syringe.set_valve_dirs(HIGH,LOW);  // OPEN INPUT VALVE (VALVE 1), CLOSE OUTPUT VALVE (VALVE 2)
    control_syringe.pump(stepSize,in);
    Serial.println("I pumped in");
    
    control_syringe.set_valve_dirs(LOW,HIGH);  // CLOSE INPUT VALVE (VALVE 1), OPEN OUTPUT VALVE (VALVE 2)
    control_syringe.pump(stepSize,out);
    Serial.println("I pumped out");
//  }
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
    Serial.print("\t<1>\tSyringe Rinse Speed (ul/min)\t\t\t"); Serial.println(benchtop.get_syringe_rinse_speed());
    Serial.print("\t<2>\tRinse Volume (uL)\t\t\t"); Serial.println(benchtop.get_rinse_volume());
    Serial.print("\t<3>\tRinse Time (ms)\t\t\t\t"); Serial.println(benchtop.get_rinse_time());
    Serial.print("\t<4>\tAcid Volume (uL)\t\t\t"); Serial.println(benchtop.get_acid_volume());
    Serial.print("\t<5>\tAcid Wait Time (ms)\t\t\t"); Serial.println(benchtop.get_acid_wait_time());
    Serial.print("\t<6>\tSample Volume (uL)\t\t\t"); Serial.println(benchtop.get_sample_volume());
    Serial.print("\t<7>\tSyringe Sample Speed (uL/m)\t\t"); Serial.println(benchtop.get_syringe_sample_speed());
    Serial.print("\t<8>\tSample Wait Time(ms)\t\t\t"); Serial.println(benchtop.get_sample_wait_time());
    Serial.print("\t<9>\tIntegration Time(ms)\t"); Serial.println(benchtop.get_integration_time());
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
          myFile = SD.open(file_name, FILE_WRITE);
          myFile.println(sample_name);
          if (!myFile) {
            Serial.println("Garbage.");
            break;
          }
          Serial.println("BEGIN RINSE\n");
//          benchtop.rinse(strip_chamber,control_syringe);
          Serial.println("\nEND RINSE\n");
          Serial.println("\nBEGIN ANALYSIS\n");
          benchtop.analysis(strip_chamber,control_syringe,k30,acid_pump,myFile);
          Serial.println("\nEND ANALYSIS\n");
          myFile.close();
          print_new_cmd_line();
          break;
        case('c'): // run cleaning cycle
          Serial.println(NOT_YET_STR);
          print_new_cmd_line();
          break;
        case('0'): // test the syringe pump system
          for (int i = 0; i < 3; i++) {
            actuatePump();
          }
          print_new_cmd_line();
          break;
        case('1'): // test the air pump system
          print_new_cmd_line();
          break;
        case('2'): // test the k30
          for (int i = 0; i < 5; i++) {
            detect();
            delay(2000);
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

