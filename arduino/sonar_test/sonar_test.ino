#include <Ultrasonic.h>
#include <BasicTerm.h>


Ultrasonic usonic1(5,7);
Ultrasonic usonic2(6,7);

BasicTerm term(&Serial);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  term.init();
  term.set_attribute(BT_NORMAL);
  term.set_color(BT_WHITE,BT_BLACK);
  term.cls();
  term.show_cursor(false);
}

void loop() {
  long range1 = usonic1.Ranging(CM);
  long range2 = usonic2.Ranging(CM);
  // put your main code here, to run repeatedly:
  term.set_color(BT_RED,BT_BLACK);
  term.position(0,0);
  term.print(F("Front : "));
  term.print(F("      "));
  term.position(0,8);
  term.print(range1);
  delay(30);
  term.set_color(BT_BLUE,BT_BLACK);
  term.position(1,0);
  term.print(F("Back  : "));
  term.print(F("      "));
  term.position(1,8);
  term.print(range2);
  delay(30);
  term.set_color(BT_YELLOW,BT_BLACK);
  term.position(2,0);
  term.print(F("Millis: "));
  term.print(F("      "));
  term.position(2,8);
  term.print(millis());
  delay(30);
}
