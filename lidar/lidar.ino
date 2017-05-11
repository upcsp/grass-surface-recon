#include <Wire.h>
#include <LIDARLite.h>

LIDARLite lidar;
double d;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  lidar.begin(0, true); // default, I2c @ 400 kHz
  lidar.configure(0); // default
}

void loop() {
  // put your main code here, to run repeatedly:
  d = lidar.distance();
  Serial.println(d);
}

