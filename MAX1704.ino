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
#include "Wire.h"
#include "MAX1704.h"

MAX1704 fuelGauge;

void setup(){
  
 Wire.begin(); 
 Serial.begin(9600);
 
 Serial.println("Starting up...");
 delay(1000);
 fuelGauge.reset();
 fuelGauge.quickStart();
 fuelGauge.showConfig();
 delay(1000);
}

void loop(){

 delay(1000);
  float charge = fuelGauge.stateOfCharge();
  Serial.println(charge);
  delay(1000);
}
