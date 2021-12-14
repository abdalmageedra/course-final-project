/*
 * curse_project.c
 *
 * Created: 07-Dec-21 5:39:28 PM
 * Author : ADMIN
 */ 
#include "STD_TYPES.h"
#include "LED.h"
#include "S_SEG.h"
#include "P_B.h"
#include "TEMP_S.h"
#include "TIMER.h"
#include "EEPROM_24C16.h"
#include "HEAT_COOL_RELAY.h"
#include "EX_INT.h"
#include <avr/interrupt.h>
#define  F_CPU 16000000UL
#include "util/delay.h"

extern u32 num_of_ov;
extern u32 initial_value;
static u32 TIMER0_COUNTER;

extern u32 num_of_ov_2;
extern u32 initial_value_2;


u8 MODE= 0;
u8 CURRENT_TEMP;
u8 SET_TEMP =60;


int main(void)

{
	u8 ON_OFF_STATE = OFF; //initial state at start up if OFF
	u8 AVG_TEMP;          //to HOLD the average of temp sensor readings
	
	
	
    S_SEG_INIT();
    P_B_INIT(P_B_ON_OFF);
    P_B_INIT(P_B_UP);
    P_B_INIT(P_B_DOWN);
	LED_INIT(HEATING_LED);
	HEATING_RELAY_INIT();
	COOLING_RELAY_INIT();
	TEMP_S_INIT();
	TIMER_0_INIT();
	TIMER_1_INIT();
	TIMER_2_INIT();
	EEPROM_24C16_INIT();
	EXTERNAL_INT_0_INIT();
	EXTERNAL_INT_1_INIT();
	
	TIMER_0_SET_TIME(5000);
	TIMER_1_SET_TIME(100);
	TIMER_2_SET_TIME(1000);
	
	SET_TEMP = EEPROM_24C16_READ(0x00);
	
	
	
	
    while (1) 
    {
		
		//////toggling between on/off state when button is released////
		if( P_B_READ(P_B_ON_OFF) == pressed )
		{
			_delay_ms(55);
			if(P_B_READ(P_B_ON_OFF) == pressed)
			{
				while(P_B_READ(P_B_ON_OFF) == pressed)
				{}
				ON_OFF_STATE ^= ON; //to toggle ON OFF STATE when on/off button is pressed
			}
		}
		
		
		
/////////////Electric Water Heater is turned ON///////////
		
		if (ON_OFF_STATE==ON) //Electric Water Heater is turned ON
		{
			if(  P_B_READ(P_B_UP)==pressed || P_B_READ(P_B_DOWN)==pressed )
			{
				_delay_ms(50);
				if( P_B_READ(P_B_UP)==pressed || P_B_READ(P_B_DOWN)==pressed )
				{
					while( P_B_READ(P_B_UP)==pressed || P_B_READ(P_B_DOWN)==pressed )
					{}
					MODE = TEMP_SET_MODE; //to enter temp. setting mode when up/down button are pressed
					TIMER_0_START();      //timer 0 to switch back to operating mode after 5 sec of not pressing any button 
				}
			}
			
			
			//////////////temperature setting mode////////////////
			if (MODE == TEMP_SET_MODE) 
			{
				EXTERNAL_INT_0_ENABLE();  //enabling interrupts for button 1&2 to be able to change the temp. once in temp setting mode
				EXTERNAL_INT_1_ENABLE();
				
				while(MODE==TEMP_SET_MODE)
				{
					EEPROM_24C16_WRITE(0x00,SET_TEMP);   // write the set temperature in byte number 0 in external EEPROM IC	
					S_SEG_DISPLAY(SET_TEMP);
				
				}
						
			}
			
			////////////operating mode/////////////////
			else 
			{
				TIMER_1_START();// to update the sensor reading every 100ms
				EXTERNAL_INT_0_DISABLE();  //disabling interrupts to be able to enter temp. setting mode once the up/down buttons are pressed
				EXTERNAL_INT_1_DISABLE();
				AVG_TEMP=TEMP_S_AVG_READ(10);
				S_SEG_DISPLAY (CURRENT_TEMP);
				
					if (SET_TEMP - AVG_TEMP>=5) //once the average temp. in colder than the set temp by 5 degrees heating element is turned on 
					{
						HEATING_RELAY_ON();
						COOLING_RELAY_OFF();
						TIMER_2_START(); //responsible of making the heating element led plink every 1sec				
					}
					
					if (AVG_TEMP - SET_TEMP>=5)//once the average temp. in hotter than the set temp by 5 degrees cooling element is turned on 
					{
						TIMER_2_STOP();
						COOLING_RELAY_ON();
						HEATING_RELAY_OFF();
						LED_ON(HEATING_LED);	
					}
					
					if (AVG_TEMP == SET_TEMP)//once the average temp reaches th set temp heating/cooling elements are turned off
					{
						TIMER_2_STOP();
						COOLING_RELAY_OFF();
						HEATING_RELAY_OFF();
						LED_OFF(HEATING_LED);
					}
				
				
				
			}
			
		}
		
		
		
		
/////////////Electric Water Heater is turned OFF///////////
		else 
		{
			
			HEATING_RELAY_OFF();
			COOLING_RELAY_OFF();
			LED_OFF(HEATING_LED);
			//TIMER_2_STOP();
			EXTERNAL_INT_0_DISABLE();
			EXTERNAL_INT_1_DISABLE();
		}
	}
	
}




/////interrupt function for when the UP button is pressed/////// 
ISR(INT0_vect)
{
	_delay_ms(100);
	SET_TEMP+=5; //single up button press increase temp by 5 degree
	TIMER0_COUNTER = 0;
	
	if (SET_TEMP>75)
	SET_TEMP=75;
	
}


/////interrupt function for when the DOWN button is pressed/////// 
ISR(INT1_vect)
{
	_delay_ms(100);
	SET_TEMP-=5;//single down button press decrease temp by 5 degree
	TIMER0_COUNTER = 0;// TO RESET TIMER EVERY TIME THE BUTTON IS PRESSED
	if (SET_TEMP<35)
	SET_TEMP=35;
	


}


/////timer to turn off temperature setting mode after 5 sec/////
ISR(TIMER0_OVF_vect)
{
	
	TIMER0_COUNTER++;
	if (TIMER0_COUNTER == num_of_ov)
	{
		MODE= OPERATING_MODE;    //toggling mode from temp setting mode to operating mode exit temp. setting mode
		TIMER_0_STOP();
		TIMER0_COUNTER = 0;
		TCNT0 = initial_value;
	}
}


///interrupt timer to update temperature reading every 100ms/////

ISR(TIMER1_COMPA_vect)
{
	CURRENT_TEMP=TEMP_S_READ();// to read the sensor reading every 100ms
	
}





ISR(TIMER2_OVF_vect)
{
	static u32 counter;
	counter++;
	if (counter == num_of_ov_2)
	{
		
		LED_TOGGLE(HEATING_LED);
		counter = 0;
		TCNT2 = initial_value_2;
		
	}
	
}