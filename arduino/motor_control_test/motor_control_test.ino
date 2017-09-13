#include <Servo.h>
#include <Ultrasonic.h>
#include <BasicTerm.h>

Servo sonar_sweeper;
Servo motor_control;
BasicTerm term(&Serial);

int angle = 90;
int motor_speed = 90;
unsigned long timer = 0;
bool drive = false;

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
  Serial.begin(115200);
  term.init();
  term.set_attribute(BT_NORMAL);
  term.set_color(BT_WHITE,BT_BLACK);
  term.cls();
  term.show_cursor(false);

  steering_servo_setup();
  sonar_sweeper.attach(2);
  motor_control.attach(3);
  sonar_sweeper.write(90);
  motor_control.write(motor_speed);
  term.println("position\tpreset");
  timer = millis();
};

void loop() {
  digitalWrite(9,LOW);
  int value = analogRead(3);//700-885
  value = map(value,790,835,0,180);//100,675,0,1023);//675 - 1023 = 5v, 675 = 3.3v
//  int preset = map(angle,0,180,0,1023);
//  int preset = map(angle,0,180,0,675);
  int preset = angle;
  int dir = 0;
    if(abs(value-preset) < 10) {
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
  term.print(value);
  term.print('\t');
  term.print(angle);
  term.print('\t');
  term.print(preset);
  term.print('\t');
  term.print(drive);
  term.print('\t');
  term.print(motor_speed);
  term.print('\t');
  term.println(millis());
  // Here goes reading
  {
     int key;
     key = term.get_key();
     switch(key) {
         case BT_KEY_LEFT:
            angle+=1;
            if(angle > 180) angle = 180;
            break;
         case BT_KEY_RIGHT:
            angle-=1;
            if(angle < 0) angle = 0;
            break;
         case BT_KEY_UP:
            motor_speed+=1;
            if(motor_speed > 180) motor_speed = 180;
            break;
         case BT_KEY_DOWN:
            motor_speed-=1;
            if(motor_speed < 0) motor_speed = 0;
            break;
         case 'c':
         case 'C':
            angle=90;
            break;
         case 'D':
         case 'd':
            drive = !drive;
            motor_speed = 90;
     };
     motor_control.write(motor_speed);
  }
};
