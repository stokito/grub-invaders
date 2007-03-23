#!/bin/bash

set -e
set -v

CFLAGS="-fno-builtin -nostdinc -O2 -I. -Wall -Werror"
LDFLAGS="-nostdlib -Wl,-N -Wl,-Ttext -Wl,100000"
gcc $CFLAGS -c keyboard.c
gcc $CFLAGS -c delay.c
gcc $CFLAGS -c common.c
gcc $CFLAGS -c sound.c
gcc $CFLAGS -c game.c
gcc $CFLAGS -c kernel.c
gcc $CFLAGS -c video.c
gcc $CFLAGS -c memory.c
gcc $CFLAGS -c boot.S
gcc $LDFLAGS -o invaders.exec boot.o kernel.o keyboard.o video.o game.o sound.o delay.o common.o memory.o
objcopy -O binary invaders.exec invaders
