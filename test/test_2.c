#include "simruntime.h"

int main()
{
    for (int y = 0; y < SCREEN_H; ++y) {
        for (int x = 0; x < SCREEN_W; ++x) {
            put_pixel(x, y, __rand());
        }
    }
    __flush();
    return 0;
}
