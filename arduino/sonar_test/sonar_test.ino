#include <Ultrasonic.h>

Ultrasonic usonic1(5,7);
Ultrasonic usonic2(6,7);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(usonic1.Ranging(CM));
  Serial.print('\t');
  delay(10);
  Serial.print(usonic2.Ranging(CM));
  Serial.println();
  delay(10);
}
