
#include <wiringPi.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "lcd.h"
#include "pir.h"
#include "dust.h"
#include "adc.h"
#include "motor.h"

#define LCD_TIMEOUT_SEC 10
#define DUST_LED_PIN 17
#define DUST_ADC_CHANNEL 3
#define ADC_CHANNEL 0
#define GAS_CHANNEL GAS_PIN

int main() {
    wiringPiSetupGpio();
    initLcd();
    initPir(PIR_PIN);
    initAdc();
    initDustSensor(DUST_LED_PIN);
    initMotor();

    int lcdOn = 0;
    time_t lastMotionTime = 0;

    while (1) {
        int pirVal = readPir(PIR_PIN);

        if (pirVal == HIGH) {
            time(&lastMotionTime);

            if (!lcdOn) {
                write_Command(0x0C);  // LCD ON
                lcdOn = 1;
            }

            float dust = readDustSensor(DUST_ADC_CHANNEL, DUST_LED_PIN);
            int gas = readSensor(GAS_CHANNEL);
    
            // motor onoff return
            static int motorOn = 0;

            // motor action option (basic gas result 600, 500)
            if (!motorOn && (dust >= 150 || gas >= 500)) {
                controlMotor(ON, CLOCKWISE);
                motorOn = 1;
            }
            else if (motorOn && (dust <= 130 && gas <= 480)) {
                controlMotor(OFF, 0);
                motorOn = 0;
            }

// CSV logging
    FILE* logFile = fopen("/home/sdhbbb/workspace/FinalT/csv_database/log_air.csv", "a");
    if (logFile != NULL) {
        time_t now = time(NULL);
        struct tm* t = localtime(&now);
        fprintf(logFile, "%04d-%02d-%02d %02d:%02d:%02d, Dust: %.1f, GAS: %d\n",
            t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
            t->tm_hour, t->tm_min, t->tm_sec,
            dust, gas);
        fclose(logFile);
    }


            write_Command(0x80);
            char buf[32];
            snprintf(buf, sizeof(buf), "D:%.1fug/m3", dust);
            printString(buf);

            write_Command(0xC0);
            snprintf(buf, sizeof(buf), "G:%d", gas);
            printString(buf);
            if (dust > 150 || gas > 600) {
                controlMotor(ON, CLOCKWISE);
            }


            delay(5000);  // 5 second interval
        }

        if (lcdOn) {
            time_t now;
            time(&now);
            if (difftime(now, lastMotionTime) >= LCD_TIMEOUT_SEC) {
                write_Command(0x08);  // LCD OFF
                lcdOn = 0;
            }
        }

        delay(500);
    }

    return 0;
}
