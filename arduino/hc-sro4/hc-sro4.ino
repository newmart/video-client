#include <Firmata.h>

#define trigPin 12
#define echoPin 11
byte analogPin;

// dummy
void analogWriteCallback(byte pin, int value){;}

void setup() {
  analogPin = 0;
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Firmata.setFirmwareVersion(0,1);
  Firmata.attach(ANALOG_MESSAGE, analogWriteCallback);
  Firmata.begin(57600);
}

void loop() {
  Firmata.sendAnalog(analogPin, readRange());
  delay(500);
}

int readRange() {
  long duration, distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  distance = (duration/2) / 29.1;
  int range = distance;
  return range;
}
