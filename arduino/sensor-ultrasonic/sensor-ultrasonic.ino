#include "Ultrasonic.h"
#include <Firmata.h>

byte analogPin;
Ultrasonic ultrasonic(7);

// dummy
void analogWriteCallback(byte pin, int value){;}

void setup() {
  analogPin = 0;
  
  Firmata.setFirmwareVersion(0,1);
  Firmata.attach(ANALOG_MESSAGE, analogWriteCallback);
  Firmata.begin(57600);
}

void loop() {
  Firmata.sendAnalog(analogPin, readRange());  
}

int readRange() {
  long RangeInCentimeters;
  RangeInCentimeters = ultrasonic.MeasureInCentimeters();
  /*
  Serial.print("distance : ");
  Serial.print(RangeInCentimeters,DEC);
  Serial.println("cm");
  */
  int range = RangeInCentimeters;
  return range;
}

