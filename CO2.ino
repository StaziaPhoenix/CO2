#include "Pump.h"
#include "K30.h"

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

// Serial CMD
int input;                 //Initialize serial input
int stepSize = 0;

// Valve & Pump
//Pump pump(3,5,11 ,12); // Initialize pump object
Pump pump(3,5,11,10); // Initialize pump object
//Pump(step motor/valve drive pin,step motor/valve direction pin,valve1/input-valve pin,valve2/output-valve pin);

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
  pinMode(startswitch, INPUT);

  Serial.begin(9600);

  pump.set_valve_dirs(LOW,LOW);  // Open both input valve and output valve
  pump.pump(500,out);            //Drain the pump and plumbing
}


void loop() {
  actuatePump();
  detect();
}

void detect() {
  k30.sendRequest();
  unsigned long valCO2 = k30.getValue();
  Serial.print("Co2 ppm = ");
  Serial.println(valCO2);
  delay(2000);
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

