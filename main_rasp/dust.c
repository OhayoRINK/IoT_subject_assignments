
#include "dust.h"
#include "adc.h"
#include <stdio.h>

float Vo_Val = 0;
float Voltage = 0;
float dustDensity = 0;

int samplingTime = 280;   // 0.28ms
int delayTime = 40;       // 0.04ms
int offTime = 9680;       // 9.68ms

void initDustSensor(int nLedPin) {
    pinMode(nLedPin, OUTPUT);
}

float readDustSensor(int analogPin, int ledPin) {
    digitalWrite(ledPin, LOW);
    delayMicroseconds(samplingTime);

    Vo_Val = readAdc(analogPin);

    delayMicroseconds(delayTime);
    digitalWrite(ledPin, HIGH);
    delayMicroseconds(offTime);

    Voltage = (Vo_Val * 3.3 / 1024.0) / 3.0;
    dustDensity = (0.172 * Voltage - 0.0999) * 1000;
    if (dustDensity < 0) dustDensity = 0;

    printf("[debug]Vo_Val : %f, Voltage : %f, Value : %f(ug/m3)\n", Vo_Val, Voltage, dustDensity);
    // to check vo_val, voltage to compare value
    return dustDensity;
}
