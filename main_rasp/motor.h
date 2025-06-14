#include <wiringPi.h>
#include <stdio.h>

#define MOTOR_CW_PIN 20
#define MOTOR_CCW_PIN 21

#define CLOCKWISE 1
#define COUNTERCLOCKWISE 0

#define ON 1
#define OFF 0

void initMotor();
void controlMotor(char cMotion, char cDirection);
