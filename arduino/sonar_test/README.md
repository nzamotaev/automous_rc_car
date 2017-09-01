# Sonar test sketch

## Connections

| Arduino | Sonar |
| ------- | ----- |
| +5V     | VCC   |
| GND     | GND   |
| 5       | Trig 1 |
| 6       | Trig 2 |
| 7       | Echo (via diode or)  |

## Requirements

Tested with Arduino diecimila with ethernet shield.

Needs Ultrasonic library

## Expected result

Continuous dump of current distance to the object from the sonar on serial port at 9600 baud.

