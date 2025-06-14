
#include <wiringPi.h>
#include <stdio.h>

int gnPirState = LOW;

void initPir(int nPin) {
    pinMode(nPin, INPUT);
}

int readPir(int nPin) {
    int nPirVal = digitalRead(nPin);
    if (nPirVal == HIGH && gnPirState == LOW) {
        printf("[debug]pir enabled\n");
        gnPirState = HIGH;
    } else if (nPirVal == LOW && gnPirState == HIGH) {
        printf("[debug]pir disabled\n");
        gnPirState = LOW;
    }
    return nPirVal;
}
