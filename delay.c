#include "delay.h"

#include "io.h"

#include "video.h"
#include "keyboard.h"

static void delay_wait_short (uint32 x)
{
  uint16 val;
  uint8 lo, hi;

  val=x+20000;

  outb(32+16,0x43);
  outb(val&255,0x40);
  outb(val>>8,0x40);
  
  do outb(0xe2,0x43); while (inb(0x40)&64);

  for (;;) {
    outb(0,0x43);
    lo=inb(0x40);
    hi=inb(0x40);
    val=((uint16)lo) | (((uint16)hi) << 8);
    if (val<20000) break;
    key_polling();
  };
};

void delay_wait (uint32 x)
{
  while (x>30000) {
    x-=30000;
    delay_wait_short(30000);
  };
  delay_wait_short(x);
};

