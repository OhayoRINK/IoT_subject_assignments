#include "adc.h"

// MCP3208
int readAdc(unsigned char adcChannel)
{
	unsigned char buff[3];
	int nAdcValue = 0;
	
	buff[0] = 0x06 | ((adcChannel & 0x07) >> 2);
	buff[1] = ((adcChannel & 0x07)<<6);
	buff[2] = 0x00;
	
	digitalWrite(CS_MCP3208,0);		//low cs Active
	
	wiringPiSPIDataRW(SPI_CHANNEL, buff, 3);
	
	buff[1] = 0x0F & buff[1];
	nAdcValue = (buff[1]<<8) | buff[2];
	
	//spi chip Select command 
	digitalWrite(CS_MCP3208, 1);
	
	return nAdcValue;
}

int readSensor(int nChannel)
{
	int nSensorVal = 0;
	nSensorVal = readAdc(nChannel);	//sensorRead
//	printf("Sensor Value = %u\n", nSensorVal);

	return nSensorVal;
}



void initAdc() {
    wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED);
    printf("ADC initialized with SPI channel %d at speed %d\n", SPI_CHANNEL, SPI_SPEED);
}
