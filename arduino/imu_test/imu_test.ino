#include <BasicTerm.h>
#include <TroykaIMU.h>
#include <Wire.h>

BasicTerm term(&Serial);
// создаём объект для работы с гироскопом
Gyroscope gyro;
// создаём объект для работы с акселерометром
Accelerometer accel;
// создаём объект для работы с компасом
Compass compass;
// создаём объект для работы с барометром
Barometer barometer;

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
  gyro.begin();
  accel.begin();
  compass.begin();
  barometer.begin();
  compass.calibrateMatrix(compassCalibrationMatrix, compassCalibrationBias);
  term.println("Initialisation completed");
  term.println("Gyroscope\t\t\tAccelerometer\t\t\tCompass\t\tBarometer");
}

void loop() {
  unsigned long time = millis();
  // вывод угловой скорости в градусах в секунду относительно оси X
  term.print(gyro.readDegPerSecX());
  term.print("\t");
  // вывод угловой скорости в градусах в секунду относительно оси Y
  term.print(gyro.readDegPerSecY());
  term.print("\t");
  // вывод угловой скорости в градусах в секунду относительно оси Z
  term.print(gyro.readDegPerSecZ());
  term.print("\t\t");
  // вывод направления и величины ускорения в м/с² по оси X
  term.print(accel.readAX());
  term.print("\t");
  // вывод направления и величины ускорения в м/с² по оси Y
  term.print(accel.readAY());
  term.print("\t");
  // вывод направления и величины ускорения в м/с² по оси Z
  term.print(accel.readAZ());
  term.print("\t\t");
  // выводим азимут относительно оси Z
  term.print(compass.readAzimut());
  term.print(" Degrees\t");
  // вывод значения абсолютного давления
  term.print(barometer.readPressureMillibars());
  term.print("\t");
  // вывод значения температуры окружающей среды
  term.print(barometer.readTemperatureC());
  term.print("\t");
  term.println(millis() - time);
  delay(100);
}
