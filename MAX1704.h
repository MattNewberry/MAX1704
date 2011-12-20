//
//  MAX1704.h
//  
//
//  Created by Matthew Newberry on 12/18/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

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
  void powerOnReset();
  void quickStart();
  void version();
  void setAlertLevel(uint8_t level);
    
private:
  void performCommand(byte address, int value);
  void readFrom(byte address, int number, int* data);
};

#endif
