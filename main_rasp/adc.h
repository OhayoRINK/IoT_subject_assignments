#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <wiringPi.h>
#include <wiringPiSPI.h>

#define CS_MCP3208	8			//GPIO 8
#define SPI_CHANNEL	0			//SPI Channel
#define SPI_SPEED	1000000		//spi speed 

#define GAS_PIN		2


// MCP3208
int readAdc(unsigned char adcChannel);
int readSensor(int nChannel);

void initAdc();
