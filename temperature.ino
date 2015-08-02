#include <DallasTemperature.h>
#include <OneWire.h>

const int ONE_WIRE_BUS = 3;

OneWire onewire(ONE_WIRE_BUS);  
DallasTemperature sensors(&onewire);

void temperature_setup() {
  sensors.begin();
}

double temperature_get() {
  sensors.requestTemperatures();
  return sensors.getTempCByIndex(0);
}

