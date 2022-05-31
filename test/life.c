#include "simruntime.h"

#define BATCH_W (SCREEN_W / 32)
#define BATCH_H (SCREEN_H)

i32 getValue(i32 *field, i32 x, i32 y)
{
    i32 *batch = (i32 *)((i8 *)field + y * 8 + x / 32);
    i32 bit = x % 32;
    i32 mask = 1 << bit;

    i32 value = (*batch & mask) != 0;
    return value;
}

void setValue(i32 *field, i32 x, i32 y, i32 value)
{
    i32 *batch = (i32 *)((i8 *)field + y * 8 + x / 32);
    i32 bit = x % 32;
    i32 mask = 1 << bit;

    if (value) {
        i32 newBatch = *batch | mask;
        *batch = newBatch;
    } else {
        i32 newBatch = *batch & (~mask);
        *batch = newBatch;
    }
}

int main()
{
    i32 *curField = (i32*)(0x8000 - SCREEN_W * SCREEN_H / 32); // 0x7c00
    i32 *prevField = (i32*)(0x8000 - SCREEN_W * SCREEN_H / 32 * 2); // 0x7be8

    for (i32 y = 0; y < SCREEN_H; ++y) {
        for (i32 x = 0; x < SCREEN_W / 32; ++x) {
            *(i32 *)((i8 *)prevField + y * SCREEN_W / 32 + x) = __rand();
        }
    }
    while(1) {
        for (i32 y = 0; y < SCREEN_H; ++y) {
            for (i32 x = 0; x < SCREEN_W; ++x) {
                i32 neighbours = getValue(prevField, (x - 1) % SCREEN_W, (y - 1) % SCREEN_H) +
                    getValue(prevField, (x - 1) % SCREEN_W, (y - 0) % SCREEN_H) +
                    getValue(prevField, (x - 1) % SCREEN_W, (y + 1) % SCREEN_H) +
                    getValue(prevField, (x - 0) % SCREEN_W, (y - 1) % SCREEN_H) +
                    getValue(prevField, (x - 0) % SCREEN_W, (y + 1) % SCREEN_H) +
                    getValue(prevField, (x + 1) % SCREEN_W, (y - 1) % SCREEN_H) +
                    getValue(prevField, (x + 1) % SCREEN_W, (y - 0) % SCREEN_H) +
                    getValue(prevField, (x + 1) % SCREEN_W, (y + 1) % SCREEN_H);
                i32 isAlive = getValue(prevField, x, y);
                if (isAlive) {
                    i32 willLive = (neighbours == 2) || (neighbours == 3); 
                    if (willLive) {
                        setValue(curField, x, y, 1);
                    } else {
                        setValue(curField, x, y, 0);
                    }
                } else {
                    i32 willBorn = neighbours == 3;
                    if (willBorn) {
                        setValue(curField, x, y, 1);
                    } else {
                        setValue(curField, x, y, 0);
                    }
                }
            }
        }
        for (i32 y = 0; y < SCREEN_H; ++y) {
            for (i32 x = 0; x < SCREEN_W; ++x) {
                i32 isAlive = getValue(curField, x, y);
                if (isAlive) {
                    put_pixel(x, y, 0xFFFFFFFF);
                } else {
                    put_pixel(x, y, 0xFF000000);
                }
            }
        }
        for (int i = 0; i < 5; ++i) {
            __flush();
        }

        i32 *tmpField = curField;
        curField = prevField;
        prevField = tmpField;
    }
    return 0;
}
