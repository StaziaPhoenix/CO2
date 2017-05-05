#include "Pump.h"
#include "K30.h"

// Serial CMD
int input;                 //Initialize serial input


// Button
const int startswitch = 9; //Button pin


// Valve
//const int steppin = 3;     //Stepper motor pin
//const int dirpin = 5;      //Motor direction pin
//const int valve1 = 11;     //Pin for Valve 1 control (input valve)
//const int valve2 = 12;     //Pin for Valve 2 control (output valve)
const int out = 1;         //Set direction out to be 1
const int in = 0;          //Set direction in to be 0
int stepSize = 0;

int rx = 12;
int tx = 13;

Pump pump(3,5,11,12); // Initialize pump object
//Pump(step_mtr_drv,step_mtr_dir,valve_input_pin,valve_output_pin);
K30 k30(rx, tx);

/*
void pump(int steps, boolean dir) {
  if(dir == 1) {
    digitalWrite(dirpin,HIGH); //Set pump moving outwards with dir=1
    Serial.println("This pump is moving out");
  }else if(dir ==0){
    digitalWrite(dirpin,LOW);  //Set pump moving inwards with dir=0
    Serial.println("This pump is moving in");
  }
  
  delay(15);

  Serial.println("This pump is moving!");
  
  for (int i = 1; i <= steps ;i++){
    Serial.println(i);
    digitalWrite(steppin,HIGH);
    delay(9); // on for 9ms
    digitalWrite(steppin,LOW);
    delay(30);  // off for 11ms
    }
}
*/


void setup() {
//  pump.initialize();
//  pinMode(steppin, OUTPUT);
//  pinMode(dirpin, OUTPUT);
  pinMode(startswitch, INPUT);
//  pinMode(valve1, OUTPUT);
//  pinMode(valve2, OUTPUT);
//
//  digitalWrite(steppin, LOW);  //Initialize pump to off
//  digitalWrite(dirpin, LOW);   //Direction low is pump moving inwards
//  
  Serial.begin(9600);

//  digitalWrite(valve1, LOW);  
//  digitalWrite(valve2, LOW);   //OPEN BOTH VALVES
  pump.pump(500, out);              //Drain the pump and plumbing
}


void loop() {
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
//      digitalWrite(valve1, LOW);
//      digitalWrite(valve2, HIGH);  //OPEN VALVE 1, CLOSE VALVE 2
      pump.set_valve_dirs(LOW,HIGH);  // OPEN VALVE 1, CLOSE VALVE 2
      pump.pump(stepSize,in);
      Serial.println("I pumped in");
//      digitalWrite(valve1, HIGH);
//      digitalWrite(valve2, LOW);   //CLOSE VALVE 1, OPEN VALVE 2
      pump.set_valve_dirs(HIGH,LOW);  // OPEN VALVE 1, CLOSE VALVE 2
      pump.pump(stepSize,out);
      Serial.println("I pumped out");
    }
    delay(200);

    // K30 Stuff
    k30.sendRequest();
    unsigned long valCO2 = k30.getValue();
    Serial.print("Co2 ppm = ");
    Serial.println(valCO2);
    delay(2000);
}
