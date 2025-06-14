#include "lcd.h"

const int LcdDataPinTable[8] = {
	LCD_DB_D0, LCD_DB_D1, LCD_DB_D2, LCD_DB_D3,
	LCD_DB_D4, LCD_DB_D5, LCD_DB_D6, LCD_DB_D7
};

const int LcdControlPinTable[3] = {
	LCD_CD_RS, LCD_CD_RW, LCD_CD_EN
};

void write_Data(unsigned char data)
{
	digitalWrite(LCD_CD_RS, LOW);
	digitalWrite(LCD_CD_RW, LOW);
	digitalWrite(LCD_CD_EN, LOW);

	digitalWrite(LCD_CD_RS, HIGH);

	int i;
	for(i=0; i<8; i++){
		if(data & (1 << i)){
			digitalWrite(LcdDataPinTable[i], HIGH);
		}
		else{
			digitalWrite(LcdDataPinTable[i], LOW);
		}
	}
	digitalWrite(LCD_CD_EN, HIGH);
	delayMicroseconds(110);
	digitalWrite(LCD_CD_EN, LOW);
	delayMicroseconds(50);
}

void printString(char *string)
{
	while(*string != '\0'){
		write_Data(*string);
		string++;
	}
}

void write_Command(unsigned char command)
{
	digitalWrite(LCD_CD_RS, LOW);
	digitalWrite(LCD_CD_RW, LOW);
	digitalWrite(LCD_CD_EN, LOW);

	int i;
	for(i=0; i<8; i++){
		if(command & (1 << i)){
			digitalWrite(LcdDataPinTable[i], HIGH);
		}
		else{
			digitalWrite(LcdDataPinTable[i], LOW);
		}
	}

	delayMicroseconds(20);
	digitalWrite(LCD_CD_EN, HIGH);
	delayMicroseconds(300);
	digitalWrite(LCD_CD_EN, LOW);
	delayMicroseconds(20);
}

void initLcd(void)
{
	int i;
	for(i=0; i<LCD_CD_PIN_NUM; i++){
		pinMode(LcdControlPinTable[i], OUTPUT);
		digitalWrite(LcdControlPinTable[i], LOW);
	}
	for(i=0; i<LCD_DB_PIN_NUM; i++){
		pinMode(LcdDataPinTable[i], OUTPUT);
		digitalWrite(LcdDataPinTable[i], LOW);
	}

	delayMicroseconds(20);
	digitalWrite(LCD_CD_EN, LOW);
	delayMicroseconds(20);

	write_Command(0x38);           // function set
	delayMicroseconds(45);

	write_Command(0x0C);          // display on
	delayMicroseconds(45);

	write_Command(0x01);         // clear display
	delay(2);

	write_Command(0x1C);          // entry mode set(shift right)
	delayMicroseconds(45);

	write_Command(0x1C);            // entry mode shift right
	delayMicroseconds(45);

	write_Command(0x1C);
	delayMicroseconds(45);
}

void setDDRAMAddress()
{
	write_Command(0x80);            // set ddram address
	delayMicroseconds(110);
}

void move2ndLine()
{
	write_Command(0xC0);          // move to 2nd Line
	delayMicroseconds(110);
}
