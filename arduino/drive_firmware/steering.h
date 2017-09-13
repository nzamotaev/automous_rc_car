#ifndef __STEERING_H__
#define __STEERING_H__
#include <stdint.h>

void steering_servo_setup();
void steering_servo_process();
void steering_servo_set_angle(uint8_t ang);
void steering_servo_enable(bool ena);
#endif
