

#include "ADC.h"
#include "TEMP_S_CFG.h"

void TEMP_S_INIT(void)
{
	ADC_INIT();
}
u16  TEMP_S_READ(void)
{
	u16 value;	
	value = ADC_READ(TEMP_S_PIN);
	u16 temp;
	temp = ((u32)value * 500 ) / 1023;
	return temp;
}

u16  TEMP_S_AVG_READ(u8 sample_num)
{
	u16 AVG_READING=0;
	u8 i;
	for(i=0;i<sample_num;i++)
	{
		AVG_READING += TEMP_S_READ();
	}
	AVG_READING=AVG_READING/sample_num;
	return AVG_READING;
}