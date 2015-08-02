#include <OneWire.h>

#include <PID_v1.h>
#include <String.h>

double Setpoint, Input, Output;
int sample_interval = 1000;
PID COOLPID(&Input, &Output, &Setpoint, 10,1,50, REVERSE);

int WindowSize = 5000; 
unsigned long windowStartTime;

void serialEvent() {
  Setpoint = Serial.readString().toFloat();
  Serial.print("New Setpoint="); Serial.print(Setpoint);
  Serial.println();


  
}

void setup() {
  windowStartTime = millis();
  Serial.begin(9600);
  rcswitch_setup();
  temperature_setup();
  
  Setpoint = 12;
  Input = 25;
  COOLPID.SetOutputLimits(0, WindowSize);
  COOLPID.SetMode(AUTOMATIC);
  COOLPID.SetSampleTime(sample_interval);
}

void loop() {
  Input = temperature_get();
  COOLPID.Compute();

  if (Input > Setpoint) {
    turnOnCooler();
  }
  else 
  {
    turnOffCooler();
  }

//  unsigned long now = millis();
//  if (now - windowStartTime > WindowSize) {
//    windowStartTime += WindowSize;
//  }
//  if (Output > now - windowStartTime) {
//    turnOnCooler();
//  } 
//  else {
//    turnOffCooler();
//  }
  Serial.print("Current="); Serial.print(Input); Serial.print(" C"); 
  Serial.print(" setp="); Serial.print(Setpoint);
  Serial.print(" outp="); Serial.print(Output);
  Serial.print(" CoolerOn="); Serial.print(CoolerOnStatus());
  Serial.println();
  delay(sample_interval);
}
