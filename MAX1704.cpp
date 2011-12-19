//
//  MAX1704.cpp
//  
//
//  Created by Matthew Newberry on 12/18/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "Arduino.h"
#include "MAX1704.h"
#include "Wire.h"

float MAX1704::stateOfCharge(void){

  int data[] = {};
  readFrom(MAX1704_SOC,2,data);
  
  float fraction = data[1] / 256.0;
  float percentage = data[0] + fraction;

  return percentage;
}

void MAX1704::powerOnReset(){

  performCommand(MAX1704_POWER_ON_RESET, 0x00);
}

void MAX1704::quickStart(){

  performCommand(MAX1704_QUICK_START, 0x00);
}

void MAX1704::version(){

}

void MAX1704::performCommand(byte address, int value){

  Wire.beginTransmission(MAX1704_ADDR);
  Wire.write(MAX1704_COMMAND);
  Wire.write(address);
  Wire.write(value);
  
  Wire.endTransmission();
}

void MAX1704::readFrom(byte address, int number, int* data){

  Wire.beginTransmission(MAX1704_ADDR);
  Wire.write(address);
  Wire.endTransmission();

  Wire.requestFrom(MAX1704_ADDR, number);

  int i = 0;
  while(Wire.available()){

    data[i] = Wire.read();
    i++;
  }

  Wire.endTransmission();
}

