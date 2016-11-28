#include <Firmata.h>

#define trigPin 12
#define echoPin 13
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
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  int range = distance;
  return range;
}
