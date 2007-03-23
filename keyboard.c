#include "keyboard.h"

#include "io.h"
#include "memory.h"

static uint8 *ringbuf=0;
static uint32 ringstart=0, ringend=0, ringsize=1024;

void key_decode(uint8 *key, bool *pressed)
{
  uint8 c;
  uint32 ringoldstart = ringstart;

  *key='x';
  *pressed=false;
    
  if (ringstart == ringend) return;
  c=ringbuf[ringstart++];
  if (ringstart==ringsize) ringstart=0;

  if (c == 0xe0) {
    if (ringstart == ringend) {
      ringstart = ringoldstart;
      return;
    };
    c = ringbuf[ringstart++];
    if (ringstart == ringsize) ringstart=0;
    *pressed = ((c&0x80) == 0) ? true : false;
    c &= ~0x80;
    if (c==0x4d) *key='>';
    if (c==0x4b) *key='<';
    if (c==0x48) *key='^';
    if (c==0x50) *key='v';
  }else{
    *pressed = ((c&0x80) == 0) ? true : false;
    c &= ~0x80;
    if ((c>=0x3b) && (c<=0x44)) *key=c-0x3b+'0';
    if (c==0x2a) *key='l';
    if (c==0x36) *key='r';
    if (c==1) *key='@';
    if (c==0x1c) *key='e';
    if (c==0x39) *key=' ';
  };
};

void key_polling()
{
  if (inb(0x64)&1) {
    ringbuf[ringend++] = inb(0x60);
    if (ringend==ringsize) ringend=0;
  };
};

void key_initialize()
{
  ringbuf = malloc (ringsize);
};
