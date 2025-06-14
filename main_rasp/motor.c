#include "motor.h"

void initMotor()
{
	pinMode(MOTOR_CW_PIN, OUTPUT);
	pinMode(MOTOR_CCW_PIN, OUTPUT);
	controlMotor(OFF, 0);
}

void controlMotor(char cMotion, char cDirection)
{
	if(cMotion == ON)
	{
		if(cDirection == CLOCKWISE)
		{
			digitalWrite(MOTOR_CW_PIN, HIGH);
			digitalWrite(MOTOR_CCW_PIN, LOW);
			printf("[debug] motor on clockwise\n");
		}
		else if(cDirection == COUNTERCLOCKWISE)
		{
			digitalWrite(MOTOR_CW_PIN, LOW);
			digitalWrite(MOTOR_CCW_PIN, HIGH);
			printf("[debug]motor on counterclockwise\n");
		}
	}
	else if(cMotion == OFF)
	{
		digitalWrite(MOTOR_CW_PIN, LOW);
		digitalWrite(MOTOR_CCW_PIN, LOW);
		printf("[debug]motor off\n");
	}
}
