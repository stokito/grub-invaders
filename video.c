#include "video.h"

#include "io.h"
#include "common.h"
#include "memory.h"

static uint8 video_attr=7;
static uint8 *videohidden = 0;
static const uint8 hextab[16] = {'0','1','2','3','4','5','6','7',
				 '8','9','A','B','C','D','E','F'};

void video_usecolor(uint8 fg, uint8 bg)
{
  video_attr = (fg & 15) | (bg << 4);
};

void video_putchar(int32 x, int32 y, uint8 code)
{
  if ((x<0) || (y<0) || (x>=80) || (y>=25)) return;
  videohidden [ (y*80+x)*2 ] = code;
  videohidden [ (y*80+x)*2 +1 ] = video_attr;
};

void video_fill(int32 x, int32 y, int32 width, int32 height, uint8 code)
{
  int32 a, b;

  for (a = x; a < x+width; ++a)
    for (b = y; b < y+height; ++b)
      video_putchar (a, b, code);
};

void video_puthex8(int32 x, int32 y, uint8 hex)
{
  video_putchar(x,y,hextab[hex>>4]);
  video_putchar(x+1,y,hextab[hex&15]);
};

void video_putstring(int32 x, int32 y, char *str)
{
  while (*str) video_putchar(x++,y,*(str++));
};

void video_update()
{
  memcpy ((uint8*)0xb8000, videohidden, 80*25*2);
};

void video_setcolor(uint8 colnum, uint8 red, uint8 green, uint8 blue)
{
  const uint8 tab[16]={0,1,2,3,4,5,0x14,7,0x38,0x39,0x3a,
		       0x3b,0x3c,0x3d,0x3e,0x3f};
  if (colnum>=16) return;
  outb(tab[colnum],0x3c8);
  outb(red,0x3c9);
  outb(green,0x3c9);
  outb(blue,0x3c9);
};

void video_blinkchars(bool onoff)
{
  // FIXME I BUGGY ON SOME VIDEO CARDS
  uint8 a;
  inb(0x3da);
  outb(0x10,0x3c0);
  a=inb(0x3c1);
  if (onoff) a |= 8; else a &= ~8;
  outb(a,0x3c1);
  outb(32,0x3c0);
};

static void video_visiblecursor (bool onoff)
{
  uint8 a;
  outb(0xa, 0x3d4);
  a = inb(0x3d5);
  if (onoff) a &= ~32; else a |= 32;
  outb(0xa, 0x3d4);
  outb(a, 0x3d5);
};

void video_hidecursor()
{
  video_visiblecursor (false);
};

void video_poscursor(int32 x, int32 y)
{
  if ((x<0) || (y<0) || (x>=80) || (y>=25)) {
    video_hidecursor ();
  }else{
    uint16 c;
    c = y*80+x;
    outb(0xe,0x3d4);
    outb(c>>8,0x3d5);
    outb(0xf,0x3d4);
    outb(c&255,0x3d5);
    video_visiblecursor(true);
  };
};

void video_initialize()
{
  videohidden = malloc (80*25*2);
};
