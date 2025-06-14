#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>


#define DUST_LED_PIN  17

void initDustSensor(int nLedPin);
float readDustSensor(int analogPin, int ledPin);
