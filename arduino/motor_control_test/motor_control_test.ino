#include <Servo.h>
#include <Ultrasonic.h>
#include <BasicTerm.h>

Servo sonar_sweeper;
Servo motor_control;
Servo steering;
BasicTerm term(&Serial);
Ultrasonic usonic1(5,7);
Ultrasonic usonic2(6,7);

int angle = 90;
int motor_speed = 90;
unsigned long timer = 0;


long range0 = 51;
long range1 = 51;
uint8_t state = 0;


void setup() {
  pinMode(9,OUTPUT);
  digitalWrite(9,HIGH);
  Serial.begin(115200);
  term.init();
  term.set_attribute(BT_NORMAL);
  term.set_color(BT_WHITE,BT_BLACK);
  term.cls();
  term.show_cursor(false);

  sonar_sweeper.attach(2);
  motor_control.attach(3);
  steering.attach(4);
  sonar_sweeper.write(90);
  motor_control.write(motor_speed);
  steering.write(angle);
  term.println("position\tpreset");
  timer = millis();
};

void loop() {
    if((millis() - timer) > 16) {
        state+=1;
        state%=6;
        timer = millis();
    };
    switch(state) {
        case 1:
           range0 = usonic1.Ranging(CM);
           state++;
           break;
        case 4: 
           range1 = usonic2.Ranging(CM);
           state++;
           break;
    }
  if((motor_speed < 90) && (range0 <12)) {
       motor_speed = 90;
  }
  if((motor_speed > 90) && (range1 <12)) {
      motor_speed = 90;
  }
  digitalWrite(9,LOW);
  term.print(angle);
  term.print('\t');
  term.print(motor_speed);
  term.print('\t');
  term.print(range0);
  term.print('\t');
  term.print(range1);
  term.print('\t');
  term.println(millis());

  // Here goes reading
  {
     int key;
     key = term.get_key();
     switch(key) {
         case BT_KEY_LEFT:
            angle+=1;
            if(angle > 125) angle = 125;
            break;
         case BT_KEY_RIGHT:
            angle-=1;
            if(angle < 55) angle = 55;
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
            motor_speed = 90;
            angle = 90;
     };
     motor_control.write(motor_speed);
     steering.write(angle);
     sonar_sweeper.write(angle);
  }
};
