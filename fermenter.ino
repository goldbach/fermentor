int sample_interval = 120000;
double Input, Setpoint;

void serialEvent() {
  Setpoint = Serial.readString().toFloat();
  Serial.print("New Setpoint="); Serial.print(Setpoint);
  Serial.println();  
}

void setup() {
  Serial.begin(9600);
  rcswitch_setup();
  temperature_setup();
  
  Setpoint = 20.0;
  Input = 20.0;
}

void loop() {
  unsigned long now = millis();
  Input = temperature_get();
  

  if (Input > Setpoint) {
    turnOnCooler();
  } 
  else {
    turnOffCooler();
  }
  Serial.print("time="); Serial.print(now);
  Serial.print(";current="); Serial.print(Input); Serial.print(" C"); 
  Serial.print(";setpoint="); Serial.print(Setpoint); Serial.print(" C");
  Serial.println();
  delay(sample_interval);
}
