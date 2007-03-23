#include "common.h"

void memcpy (void *dst, void *src, uint32 num)
{
  uint32 c;
  for (c=0;c<num;++c) ((uint8*)dst)[c]=((uint8*)src)[c];
};
