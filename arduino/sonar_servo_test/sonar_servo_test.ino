#include <Servo.h>
#include <Ultrasonic.h>

Servo sonar_sweeper;
Ultrasonic usonic(5,7);
Ultrasonic usonic_r(6,7);

int angle = 0;
int direction = 7;
const int limit = 45;

void setup() {
  pinMode(9,OUTPUT);
  digitalWrite(9,HIGH);
  Serial.begin(9600);
  sonar_sweeper.attach(2);
  sonar_sweeper.write(angle);
  Serial.println("angle\tdistance");
};

void loop() {
  digitalWrite(9,LOW);
  sonar_sweeper.write(angle+90);
  delay(35);
  digitalWrite(9,HIGH);  
  Serial.print(angle);
  Serial.print('\t');
  Serial.println(usonic.Ranging(CM));
  angle += direction;
  if(abs(angle) > limit ) {
      direction= -direction;
  };
  delay(5);
};
