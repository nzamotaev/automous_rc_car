#include "steering.h"
#include <Arduino.h>

uint8_t angle; 
bool drive;

void steering_servo_setup() {
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  digitalWrite(A0,LOW);
  digitalWrite(A1,LOW);
  angle = 90;
  drive = false;
}

void steering_servo_direction(int8_t i) {
    digitalWrite(A0,LOW);
    digitalWrite(A1,LOW);
    if(i>0) {
        digitalWrite(A0,HIGH);
    }else if(i<0) {
        digitalWrite(A1,HIGH);
    };
}

void steering_servo_process() {
  uint16_t value = analogRead(3);
//  value = map(value,100,675,0,1023);//675 - 1023 = 5v, 675 = 3.3v
//  int preset = map(angle,0,180,0,1023);
  uint16_t preset = map(angle,0,180,0,675);
  int8_t dir = 0;
    if(abs(value-preset) < 5) {
        dir=0;
    }else {
      if(value < preset) {
        dir=1;
      }else if (value > preset) {
        dir=-1;
      }
  }
  if(!drive) dir = 0; 
  steering_servo_direction(dir);
};

void steering_servo_enable(bool ena) {
    drive = ena;
}

void steering_servo_set_angle(uint8_t ang) {
    angle = ang;
}
