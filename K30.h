#ifndef K30_h
#define K30_h

#include "Arduino.h"
#include "SoftwareSerial.h"

class K30 {
  
  public:
    K30(byte rx, byte tx) : K_30_Serial(rx, tx) {
      initialize();
    }

    void sendRequest();
    unsigned long getValue();
    
  private:
    SoftwareSerial K_30_Serial;
    int responseSize = 7;
    
    byte commandPacket[7] = {0xFE, 0X44, 0X00, 0X08, 0X02, 0X9F, 0X25};  //Command packet to read Co2 (see app note)
    byte response[7] = {0,};  //create an array to store the response

    //multiplier for value. default is 1. set to 3 for K-30 3% and 10 for K-33 ICB
    int valMultiplier = 1;

    void initialize();

};

#endif
