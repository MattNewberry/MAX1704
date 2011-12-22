/**************************************************************************
 *                                                                         *
 * MAX1704* Driver for Arduino                                             *
 *                                                                         *
 * Matthew Newberry                                                        *
 * mattnewberry@me.com                                                     *
 *                                                                         *
 ***************************************************************************
 *                                                                         * 
 * This program is free software; you can redistribute it and/or modify    *
 * it under the terms of the GNU License.                                  *
 * This program is distributed in the hope that it will be useful,         *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 * GNU License V2 for more details.                                        *
 *                                                                         *
 ***************************************************************************/

#include "Arduino.h"
#include "MAX1704.h"
#include "Wire.h"

float MAX1704::stateOfCharge(){

  byte msb = 0;
  byte lsb = 0;

  readFrom(MAX1704_SOC,msb,lsb);

  float fraction = lsb / 256.0;
  float percentage = msb + fraction;

  return percentage;
}

void MAX1704::showConfig(){

  int threshold = alertThreshold();
  boolean sleep = isSleeping();
  boolean alert = isAlerting();
  byte v = version();
  
  Serial.print("Version = ");
  Serial.println(v, HEX);
  Serial.print("Sleep = ");
  Serial.println(sleep, HEX);
  Serial.print("Alert = ");
  Serial.println(alert, HEX);
  Serial.print("Alert Threshold = ");
  Serial.print(threshold, DEC);
  Serial.println("%");
}

void MAX1704::reset(){

  performCommand(MAX1704_POWER_ON_RESET, 0x00);
}

void MAX1704::quickStart(){

  performCommand(MAX1704_QUICK_START, 0x00);
}

char MAX1704::version(){

  int value = 0;
  byte msb = 0;
  byte lsb = 0;
  readFrom(MAX1704_VERSION, msb, lsb);
  
    value  = 0xFF00 & (msb<<8);
    value |=   0xFF & lsb;

  return value;
}

void MAX1704::setAlertThreshold(uint8_t level){

  Wire.beginTransmission(MAX1704_ADDR);
  Wire.write(MAX1704_CONFIG);
  Wire.write(MAX1704_ALERT_LEVEL);
  Wire.write(32 - level);
  Wire.endTransmission();
}

int MAX1704::alertThreshold(){

  byte msb = 0;
  byte lsb = 0;

  readFrom(MAX1704_CONFIG,msb,lsb);
  byte threshold = lsb & 0x1f;

  return 32 - threshold;
}

boolean MAX1704::isAlerting(){

  byte msb = 0;
  byte lsb = 0;

  readFrom(MAX1704_CONFIG,msb,lsb);
  byte alert = (lsb >>5) & 0x01;

  return int(alert) == 1;
}

boolean MAX1704::isSleeping(){

  byte msb = 0;
  byte lsb = 0;

  readFrom(MAX1704_CONFIG,msb,lsb);
  byte sleep = (lsb >>7) & 0x01; 

  return int(sleep) == 1;
}

void MAX1704::sleep(){
  
}

void MAX1704::awake(){
 
  
}

void MAX1704::performCommand(byte address, int value){

  Wire.beginTransmission(MAX1704_ADDR);
  Wire.write(MAX1704_COMMAND);
  Wire.write(address);
  Wire.write(value);
  Wire.endTransmission();
}

void MAX1704::readFrom(byte address, byte &msb, byte &lsb){

  Wire.beginTransmission(MAX1704_ADDR);
  Wire.write(address);
  Wire.endTransmission();

  Wire.requestFrom(MAX1704_ADDR, 2);

  int numread = Wire.available();
  //if (numread == 2) {
  msb = Wire.read();
  lsb = Wire.read();
  //}
  Wire.endTransmission();
}





