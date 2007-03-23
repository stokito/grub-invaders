#ifndef __DELAY_H
#define __DELAY_H

#include "types.h"

// initialize the keyboard before using delay_wait !!!

// t in seconds.
// x = 1193180 / t
void delay_wait (uint32 x);

#endif
