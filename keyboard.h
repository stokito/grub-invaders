#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include "types.h"

/*

ESC     @
LEFT    <
RIGHT   >
UP      ^
DOWN    v
LSHIFT  l
RSHIFT  r
ENTER   e
F1-F10  0123456789
SPACE   ' '
NOTHING x

only marks will be returned, releases ignored.

*/

void key_decode(uint8 *key, bool *pressed);
void key_polling();
void key_initialize();

#endif
