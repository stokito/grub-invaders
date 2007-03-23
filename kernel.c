#include "keyboard.h"
#include "video.h"
#include "game.h"

void cmain (unsigned long magic, unsigned long addr)
{
  key_initialize();
  video_initialize();
  game();
}
