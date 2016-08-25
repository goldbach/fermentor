#include <RCSwitch.h>

#define RCSwitch_PIN 7 
#define HOUSECODE "11001"
#define COOLER_ID "00100"
#define FRIDGE_MINTIME 120000

RCSwitch rcswitch = RCSwitch();

bool cool = false; 
unsigned long min_cool_stop = 0;
unsigned long min_cool_start = 0;

void rcswitch_setup() {
  rcswitch.enableTransmit(RCSwitch_PIN);
}

bool CoolerOnStatus()
{
  return cool;
}

void turnOnCooler() {
  unsigned long now = millis();
  if ( (!cool) && now > min_cool_start ) {
    Serial.print(now); Serial.println(" Starting cooler");
    cool = true;
    min_cool_stop = now + FRIDGE_MINTIME;
    rcswitch.switchOn(HOUSECODE, COOLER_ID);
  } 
}

void turnOffCooler() {
  unsigned long now = millis();
  if (cool && now > min_cool_stop) {
    Serial.print(now); Serial.println(" Stoping cooler");
    cool = false;
    min_cool_start = now + FRIDGE_MINTIME;
    rcswitch.switchOff(HOUSECODE, COOLER_ID);
  }
}



