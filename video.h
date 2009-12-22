#ifndef __VIDEO_H
#define __VIDEO_H

#include "types.h"

// effect on virtual buffer only
void video_usecolor(uint8 fg, uint8 bg);
void video_putchar(int32 x, int32 y, uint8 code);
void video_fill(int32 x, int32 y, int32 width, int32 height, uint8 code);
void video_puthex8(int32 x, int32 y, uint8 hex);
void video_putstring(int32 x, int32 y, char *str);

// immediate effect
void video_update();
void video_setcolor(uint8 colnum, uint8 red, uint8 green, uint8 blue);
void video_blinkchars(bool onoff);
void video_hidecursor();
void video_poscursor(int32 x, int32 y); // out of screen -> video_hidecursor
void video_initialize();

#endif
