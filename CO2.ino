#include "Pump.h"

#define out 1         //Set direction out to be 1
#define in 0          //Set direction in to be 0

// Serial CMD
int input;                 //Initialize serial input

// Button
const int startswitch = 9; //Button pin



// Valve & Pump
Pump pump(3,5,11 ,12); // Initialize pump object
//Pump(step motor/valve drive pin,step motor/valve direction pin,valve1/input-valve pin,valve2/output-valve pin);

int stepSize = 0;     

void setup() {
  pinMode(startswitch, INPUT);

  Serial.begin(9600);

  pump.set_valve_dirs(LOW,LOW);  // Open both input valve and output valve
  pump.pump(500,out);            //Drain the pump and plumbing
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
      pump.set_valve_dirs(LOW,HIGH);  // OPEN INPUT VALVE (VALVE 1), CLOSE OUTPUT VALVE (VALVE 2)
      pump.pump(stepSize,in);
      Serial.println("I pumped in");
      
      pump.set_valve_dirs(HIGH,LOW);  // CLOSE INPUT VALVE (VALVE 1), OPEN OUTPUT VALVE (VALVE 2)
      pump.pump(stepSize,out);
      Serial.println("I pumped out");
    }
    delay(200);
}
