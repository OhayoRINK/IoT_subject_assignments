#include <wiringPi.h>
#include <stdio.h>
#include <string.h>
//gpio pin
#define LCD_CD_RS 2
#define LCD_CD_RW 3
#define LCD_CD_EN 4

#define LCD_DB_D0 18
#define LCD_DB_D1 23
#define LCD_DB_D2 24
#define LCD_DB_D3 25
#define LCD_DB_D4 7
#define LCD_DB_D5 12
#define LCD_DB_D6 16
#define LCD_DB_D7 22

#define LCD_DB_PIN_NUM 8
#define LCD_CD_PIN_NUM 3

void write_Data(unsigned char data);
void printString(char *string);
void write_Command(unsigned char command);
void initLcd();
void setDDRAMAddress();
void move2ndLine();
