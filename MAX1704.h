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

#ifndef _MAX1704_h
#define _MAX1704_h

#define MAX1704_ADDR            0x36
#define MAX1704_SOC             0x04
#define MAX1704_VERSION         0x08
#define MAX1704_POWER_ON_RESET  0x54
#define MAX1704_QUICK_START     0x40
#define MAX1704_CONFIG          0x0C
#define MAX1704_COMMAND         0xFE
#define MAX1704_ALERT_LEVEL     0x97

class MAX1704{
    
public:
  float stateOfCharge();
  void showConfig();
  void reset();
  void quickStart();
  char version();
  void setAlertThreshold(uint8_t level);
  int alertThreshold();
  boolean isSleeping();
  boolean isAlerting();
  void sleep();
  void awake();
  
    
private:
  void performCommand(byte address, int value);
  void readFrom(byte address, byte &msb, byte &lsb);
};

#endif
