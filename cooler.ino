#include <RCSwitch.h>

#define RCSwitch_PIN 7 
#define HOUSECODE "11001"
#define COOLER_ID "00100"

RCSwitch rcswitch = RCSwitch();
boolean cool = false;

void rcswitch_setup() {
  rcswitch.enableTransmit(RCSwitch_PIN);
}

bool CoolerOnStatus()
{
  return cool;
}

void On() {
  rcswitch.switchOn(HOUSECODE, COOLER_ID);  
}
void Off() {
  rcswitch.switchOff(HOUSECODE, COOLER_ID);    
}

void turnOnCooler() {
  cool = true;
  On();
}

void turnOffCooler() {
  cool = false;
  Off();
}


