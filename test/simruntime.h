#pragma once

typedef int i32;
typedef char i8;

extern void __flush();
extern void __bkpt();
extern i32 __rand();

#define screen 0x8000
#define SCREEN_W 256
#define SCREEN_H 128

static inline void put_pixel(i32 x, i32 y, i32 rgb)
{
	*(i32*)((i8*)screen + y * SCREEN_W + x) = rgb;
}
