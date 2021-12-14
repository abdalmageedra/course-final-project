


#ifndef TIMER_H_
#define TIMER_H_

#include "STD_TYPES.h"

#define NORMAL     0
#define CTC        1

#define _64        0
#define _256       1
#define _1024      2

void TIMER_0_INIT     (void);
void TIMER_0_SET_TIME (u32);
void TIMER_0_START    (void);
void TIMER_0_STOP     (void);

void TIMER_1_INIT     (void);
void TIMER_1_SET_TIME (u32);
void TIMER_1_START    (void);
void TIMER_1_STOP     (void);

void TIMER_2_INIT     (void);
void TIMER_2_SET_TIME (u32);
void TIMER_2_START    (void);
void TIMER_2_STOP     (void);


#endif /* TIMER_H_ */