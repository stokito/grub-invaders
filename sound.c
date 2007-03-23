#include "sound.h"

#include "io.h"

void sound_freq (uint32 freq)
{
  uint16 z = (uint16) ( ((uint32)(1193180)) / freq );

  outb(182,0x43);
  outb(z&255, 0x42);
  outb(z>>8, 0x42);
  outb(inb(0x61) | 3, 0x61);
};

void sound_nosound ()
{
  outb(inb(0x61) & ~3, 0x61);
};
