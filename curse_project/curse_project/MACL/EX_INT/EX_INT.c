

#include "REG.h"
#include "BIT_MATH.h"

void EXTERNAL_INT_0_INIT(void)
{
	SET_BIT(SREG,7);         /*_TO_ENABLE_EXTERNAL_INT_*****************/
	SET_BIT(GICR,6);         /*_TO_ENABLE_INTERRUPT_0_******************/
	
	SET_BIT(MCUCR,0);        /*_DETERMINE_ACTION_TRIGGER_THE_INTERRUPT_*/
	SET_BIT(MCUCR,1);        /*_DETERMINE_ACTION_TRIGGER_THE_INTERRUPT_*/
}

void EXTERNAL_INT_1_INIT(void)
{
	SET_BIT(SREG,7);         /*_TO_ENABLE_EXTERNAL_INT_*****************/
	SET_BIT(GICR,7);         /*_TO_ENABLE_INTERRUPT_1_******************/
	
	SET_BIT(MCUCR,2);        /*_DFvaMSTYR2HupL1SyUXqGcpzeDy9N11HMAHex5eH*/
	SET_BIT(MCUCR,3);        /*_DFvaMSTYR2HupL1SyUXqGcpzeDy9N11HMAHex5eH*/
}

void EXTERNAL_INT_0_ENABLE(void)
{
	SET_BIT(GICR,6);
}

void EXTERNAL_INT_1_ENABLE(void)
{
	SET_BIT(GICR,7);
}

void EXTERNAL_INT_0_DISABLE(void)
{
	CLR_BIT(GICR,6); 
}

void EXTERNAL_INT_1_DISABLE(void)
{
	CLR_BIT(GICR,7);
}