#include <Ultrasonic.h>

Ultrasonic usonic(2,3, 40000UL);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Distance=");
  Serial.print(usonic.distanceRead());
  Serial.println();
}
