#include <TroykaIMU.h>
#include <Ultrasonic.h>
#include <Wire.h>
#include <Servo.h>
#include <SPI.h>
#include <Ethernet.h>
#include <BasicTerm.h>

BasicTerm term(&Serial);
Gyroscope gyro;
Accelerometer accel;
Compass compass;
Barometer barometer;

EthernetServer statusserver(80);
EthernetServer commandserver(23);

Servo sonar_sweeper;
Servo motor_control;
Servo steering;
Ultrasonic usonic(5,7);
Ultrasonic usonic_r(6,7);

byte mac[] = {
      0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};


// калибровочные значения компаса
// полученные в калибровочной матрице из примера «compassCalibrateMatrix»
const double compassCalibrationBias[3] = {524.21, 3352.214, -1402.236};

const double compassCalibrationMatrix[3][3] = {
    {1.757, 0.04, -0.028}, {0.008, 1.767, -0.016}, {-0.018, 0.077, 1.782}};

void setup() {
  Serial.begin(115200);
  term.init();
  term.set_attribute(BT_NORMAL);
  term.set_color(BT_WHITE, BT_BLACK);
  term.cls();
  term.show_cursor(false);
  if(Ethernet.begin(mac)==0) {
      term.println(F("Failed to configure Ethernet with DHCP"));
      for(;;) ;
  }
  sonar_sweeper.attach(2);
  motor_control.attach(3);
  steering.attach(4);
  sonar_sweeper.write(90);
  motor_control.write(90);
  steering.write(90);
  statusserver.begin();
  commandserver.begin();
  gyro.begin();
  accel.begin();
  compass.begin();
  barometer.begin();
  compass.calibrateMatrix(compassCalibrationMatrix, compassCalibrationBias);
  term.println(F("Initialisation completed"));
  term.println(F("Gyroscope\t\t\tAccelerometer\t\t\tCompass\t\tBarometer"));
}

void loop() {
  unsigned long time = millis();
  // вывод угловой скорости в градусах в секунду относительно оси X
  term.print(gyro.readDegPerSecX());
  term.print('\t');
  // вывод угловой скорости в градусах в секунду относительно оси Y
  term.print(gyro.readDegPerSecY());
  term.print('\t');
  // вывод угловой скорости в градусах в секунду относительно оси Z
  term.print(gyro.readDegPerSecZ());
  term.print(F("\t\t"));
  // вывод направления и величины ускорения в м/с² по оси X
  term.print(accel.readAX());
  term.print('\t');
  // вывод направления и величины ускорения в м/с² по оси Y
  term.print(accel.readAY());
  term.print('\t');
  // вывод направления и величины ускорения в м/с² по оси Z
  term.print(accel.readAZ());
  term.print(F("\t\t"));
  // выводим азимут относительно оси Z
  term.print(compass.readAzimut());
  term.print(F(" Degrees\t"));
  // вывод значения абсолютного давления
  term.print(barometer.readPressureMillibars());
  term.print('\t');
  // вывод значения температуры окружающей среды
  term.print(barometer.readTemperatureC());
  term.print('\t');
  term.println(millis() - time);
}
