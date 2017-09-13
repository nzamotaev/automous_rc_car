#include <Servo.h>
#include <Ultrasonic.h>
#include <BasicTerm.h>

Servo sonar_sweeper;
Ultrasonic usonic(6,7);
Ultrasonic usonic_r(5,7);
BasicTerm term(&Serial);

int angle = 0;
int direction = 7;
const int limit = 45;

void setup() {
  pinMode(9,OUTPUT);
  digitalWrite(9,HIGH);
  Serial.begin(115200);
  term.init();
  term.set_attribute(BT_NORMAL);
  term.set_color(BT_WHITE,BT_BLACK);
  term.cls();
  term.show_cursor(true);
  sonar_sweeper.attach(2);
  sonar_sweeper.write(angle);
  term.position(0,0);
  term.println(F("distance"));
  for(int i=1;i<15;i++) {
      term.position(i+1,4);
      term.print('|');
  };
  for(int i=1;i<52;i++) {
      term.position(1,i+4);
      term.print('-');
      term.position(16,i+4);
      term.print('-');
  };
  term.position(1,0);
  term.print(-50);
  term.position(8,0);
  term.print(0);
  term.position(16,0);
  term.print(50);
};

void fillgraph(int ang,long dist) {
    int x = map(ang,-50,50,2,15);
    int y = dist % 54;
    term.position(x,5);
    term.print(F("              "));
    term.print(F("              "));
    term.print(F("              "));
    term.print(F("              "));
    term.position(x,y+5);
    term.print('*');
};

void loop() {
  digitalWrite(9,LOW);
  sonar_sweeper.write(angle+90);
  delay(35);
  digitalWrite(9,HIGH);  
  long distance = usonic.Ranging(CM);
  fillgraph(angle,distance);
  term.position(20,0);
  term.print(F("Millis:       "));
  term.position(20,8);
  term.print(millis());
  term.position(21,0);
  term.print(F("Angle :       "));
  term.position(21,8);
  term.print(angle);
  term.position(22,0);
  term.print(F("Distnc:       "));
  term.position(22,8);
  term.print(distance);
  angle += direction;
  if(abs(angle) > limit ) {
      direction= -direction;
  };
  delay(5);
};
