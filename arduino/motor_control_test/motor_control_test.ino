#include <Servo.h>
#include <Ultrasonic.h>

Servo sonar_sweeper;
Servo motor_control;

int angle = 0;
const int limit = 45;
int timer = 0;

void steering_servo_setup() {
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  digitalWrite(A0,LOW);
  digitalWrite(A1,LOW);
}

void steering_servo_direction(int i) {
    digitalWrite(A0,LOW);
    digitalWrite(A1,LOW);
    if(i>0) {
        digitalWrite(A0,HIGH);
    }else if(i<0) {
        digitalWrite(A1,HIGH);
    };
}

void setup() {
  pinMode(9,OUTPUT);
  digitalWrite(9,HIGH);
  Serial.begin(9600);
  steering_servo_setup();
  sonar_sweeper.attach(2);
  motor_control.attach(3);
  sonar_sweeper.write(90);
  motor_control.write(90);
  Serial.println("position\tpreset");
  timer = millis();
};

void loop() {
  digitalWrite(9,LOW);
  int value = analogRead(3);
//  value = map(value,100,675,0,1023);//675 - 1023 = 5v, 675 = 3.3v
  int preset = map(angle,0,180,0,1023);
  int dir = 0;
    if(abs(value-preset) < 20) {
        dir=0;
    }else {
      if(value < preset) {
        dir=1;
      }else if (value > preset) {
        dir=-1;
      }
  }
  steering_servo_direction(dir);
  Serial.print(value);
  Serial.print('\t');
  Serial.print(angle);
  Serial.print('\t');
  Serial.println(preset);
  if(timer<millis()) {
      digitalWrite(9,HIGH);
      timer=millis() + 5000;
      angle = angle + 5;
      if(angle > 180) {
          angle = 0;
      }
  }
};
