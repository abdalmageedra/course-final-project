
#include "TIMER_CFG.h"
#include "TIMER.h"
#include "BIT_MATH.h"
#include "REG.h"

u32 num_of_ov; 
u8 initial_value;

u32 num_of_ov_2;
u8 initial_value_2;

void TIMER_0_INIT(void)
{
	#if TIMER_0_MODE   ==  NORMAL
	CLR_BIT(TCCR0,3);
	CLR_BIT(TCCR0,6);
	#elif TIMER_0_MODE  == CTC
	SET_BIT(TCCR0,3);
	CLR_BIT(TCCR0,6);
	#endif
	SET_BIT(SREG,7);    // to enable global int
	SET_BIT(TIMSK,0);   // to enable timer0 int
}

void TIMER_0_SET_TIME(u32 desired_time)
{
	u8 tick_time   = 1024 / 16;   // result in micro second
	u32 total_ticks = ( desired_time * 1000 ) / tick_time;
	num_of_ov       = total_ticks / 256;
	initial_value   = 255 - ( total_ticks % 256 );
	if( (total_ticks % 256) != 0 )
	{
		TCNT0       = initial_value;
		num_of_ov++;
	}
}

void TIMER_0_START(void)
{
	#if TIMER_0_PRESCALER     ==   _64
	SET_BIT(TCCR0,0);
	SET_BIT(TCCR0,1);
	CLR_BIT(TCCR0,2);
	#elif TIMER_0_PRESCALER   ==   _256
	CLR_BIT(TCCR0,0);
	CLR_BIT(TCCR0,1);
    SET_BIT(TCCR0,2);
	#elif TIMER_0_PRESCALER   ==   _1024
	SET_BIT(TCCR0,0);
	CLR_BIT(TCCR0,1);
	SET_BIT(TCCR0,2);
	#endif
}

void TIMER_0_STOP(void)
{
	CLR_BIT(TCCR0,0);
	CLR_BIT(TCCR0,1);
	CLR_BIT(TCCR0,2);
}

void TIMER_1_INIT(void)
{
	/*to select CTC mode in timer 1*/
	CLR_BIT(TCCR1A,0);
	CLR_BIT(TCCR1A,1);
	SET_BIT(TCCR1B,3);
	CLR_BIT(TCCR1B,4);

	/*_to enable global int and timer 1 int*/
	SET_BIT(SREG,7);
	SET_BIT(TIMSK,4);
}

void TIMER_1_SET_TIME(u32 desired_time)
{
	if (desired_time <= 8000)
	{
		u8  tick_time  = 1024 / 16;      // result will be in micro second
		u32 total_ticks = desired_time*1000 / tick_time;
		OCR1A = total_ticks - 1;

	}
}

void TIMER_1_START(void)
{
	SET_BIT(TCCR1B,0);
	CLR_BIT(TCCR1B,1);
	SET_BIT(TCCR1B,2);
	
}

void TIMER_1_STOP(void)
{
	CLR_BIT(TCCR1B,0);
	CLR_BIT(TCCR1B,1);
	CLR_BIT(TCCR1B,2);
}

void TIMER_2_INIT     (void)
{
	CLR_BIT(TCCR2,3);
	CLR_BIT(TCCR2,6);
	
	
	SET_BIT(SREG,7);    // to enable global int
	SET_BIT(TIMSK,6);
}

void TIMER_2_SET_TIME (u32 desired_time )
{
	u8 tick_time   = 1024 / 16;   // result in micro second
	u32 total_ticks = ( desired_time * 1000 ) / tick_time;
	num_of_ov_2       = total_ticks / 256;
	initial_value_2   = 255 - ( total_ticks % 256 );
	if( (total_ticks % 256) != 0 )
	{
		TCNT2       = initial_value_2;
		num_of_ov_2++;
	}
}

void TIMER_2_START    (void)
{
	SET_BIT(TCCR2,0);
	SET_BIT(TCCR2,1);
	SET_BIT(TCCR2,2);
}

void TIMER_2_STOP     (void)
{
	CLR_BIT(TCCR2,0);
	CLR_BIT(TCCR2,1);
	CLR_BIT(TCCR2,2);
}


