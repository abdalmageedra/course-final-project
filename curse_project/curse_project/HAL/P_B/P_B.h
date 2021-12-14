


#ifndef P_B_H_
#define P_B_H_

#include "STD_TYPES.h"

void  P_B_INIT (u8);
u8    P_B_READ (u8);

#define P_B_ON_OFF   0
#define P_B_DOWN     1
#define P_B_UP       2

#define pressed      1
#define released     0

#define ON     1 
#define OFF    0

#define TEMP_SET_MODE   1
#define OPERATING_MODE  0
#endif /* P_B_H_ */