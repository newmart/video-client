#include <Firmata.h>

#define trigPin 12
#define echoPin 11

// dummy
void analogWriteCallback(byte pin, int value){;}

int cnt = 0;

void setup() {  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Firmata.setFirmwareVersion(0,1);
  Firmata.attach(ANALOG_MESSAGE, analogWriteCallback);
  Firmata.begin(57600);
}

void loop() {
  cnt++;

  Firmata.sendAnalog(0, touchRead(15)>>6); //65536(2^16) --> 1024(2^10)
  Firmata.sendAnalog(1, touchRead(16)>>6);
  Firmata.sendAnalog(2, touchRead(17)>>6);
  Firmata.sendAnalog(3, touchRead(18)>>6);
  Firmata.sendAnalog(4, touchRead(19)>>6);
  Firmata.sendAnalog(5, touchRead(22)>>6);
  Firmata.sendAnalog(6, touchRead(23)>>6);
  Firmata.sendAnalog(7, touchRead(32)>>6);

  if (cnt % 10 == 0) // 500ms...
  {
    Firmata.sendAnalog(9, readRange());
  }
  delay(50);
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
