

#include "LED_CFG.h"
#include "DIO.h"
#define  F_CPU 16000000UL
#include "util/delay.h"

void LED_INIT   (u8 led)
{
	switch(led)
	{
		case 0:
		PIN_MODE(HEATING_LED_PIN,OUTPUT);
		break;
		case 1:
		PIN_MODE(M_LED_PIN,OUTPUT);
		break;
		case 2:
		PIN_MODE(L_LED_PIN,OUTPUT);
		break;
		default:;
	}
}
void LED_ON     (u8 led)
{
	switch(led)
	{
		case 0:
		PIN_WRITE(HEATING_LED_PIN,HIGH);
		break;
		case 1:
		PIN_WRITE(M_LED_PIN,HIGH);
		break;
		case 2:
		PIN_WRITE(L_LED_PIN,HIGH);
		break;
		default:;
	}
}
void LED_OFF    (u8 led)
{
	switch(led)
	{
		case 0:
		PIN_WRITE(HEATING_LED_PIN,LOW);
		break;
		case 1:
		PIN_WRITE(M_LED_PIN,LOW);
		break;
		case 2:
		PIN_WRITE(L_LED_PIN,LOW);
		break;
		default:;
	}
}
void LED_TOGGLE (u8 led)
{
		switch(led)
		{
			case 0:
			PIN_TOGGLE(HEATING_LED_PIN);
			break;
			case 1:
			PIN_TOGGLE(M_LED_PIN);
			break;
			case 2:
			PIN_TOGGLE(L_LED_PIN);
			break;
			default:;
		}
}
void LEDS_ON    (void)
{
		PIN_WRITE(HEATING_LED_PIN,HIGH);
		PIN_WRITE(M_LED_PIN,HIGH);
		PIN_WRITE(L_LED_PIN,HIGH);
}
void LEDS_OFF   (void)
{
		PIN_WRITE(HEATING_LED_PIN,LOW);
		PIN_WRITE(M_LED_PIN,LOW);
		PIN_WRITE(L_LED_PIN,LOW);
}

