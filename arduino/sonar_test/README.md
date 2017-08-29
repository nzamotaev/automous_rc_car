# Sonar test sketch

## Connections

| Arduino | Sonar |
| ------- | ----- |
| +5V     | VCC   |
| GND     | GND   |
| 2       | Trig  |
| 3       | Echo  |

## Requirements

Tested with Arduino pro mini.

Needs Ultrasonic library

## Expected result

Continuous dump of current distance to the object from the sonar on serial port at 9600 baud.

