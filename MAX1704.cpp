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

float MAX1704::stateOfCharge(){

  int data[] = {};
  readFrom(MAX1704_SOC,2,data);

  float fraction = data[1] / 256.0;
  float percentage = data[0] + fraction;

  return percentage;
}

void MAX1704::showConfig(){

  int threshold = alertThreshold();
  boolean sleep = isSleeping();
  boolean alert = isAlerting();

  Serial.print("Sleep = ");
  Serial.println(sleep, HEX);
  Serial.print("Alert = ");
  Serial.println(alert, HEX);
  Serial.print("Alert Threshold = ");
  Serial.print(threshold, DEC);
  Serial.println("%");
}

void MAX1704::powerOnReset(){

  performCommand(MAX1704_POWER_ON_RESET, 0x00);
}

void MAX1704::quickStart(){

  performCommand(MAX1704_QUICK_START, 0x00);
}

void MAX1704::version(){

}

void MAX1704::setAlertThreshold(uint8_t level){

  Wire.beginTransmission(MAX1704_ADDR);
  Wire.write(MAX1704_CONFIG);
  Wire.write(MAX1704_ALERT_LEVEL);
  Wire.write(32 - level);
  Wire.endTransmission();
}

int MAX1704::alertThreshold(){
 
 int data[] = {};
  readFrom(MAX1704_CONFIG,2,data);

  byte alertThreshold = data[1] & 0x1f; 
  
  return int(32 - alertThreshold);
}

boolean MAX1704::isAlerting(){
  
  int data[] = {};
  readFrom(MAX1704_CONFIG,2,data);

  byte alert = (data[1] >>5) & 0x01;
  
  return int(alert) == 1;
}

boolean MAX1704::isSleeping(){
 
 int data[] = {};
  readFrom(MAX1704_CONFIG,2,data);

 byte sleep = (data[1] >>7) & 0x01; 
  
  return int(sleep) == 1;
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



