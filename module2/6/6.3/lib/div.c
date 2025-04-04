#include "../calc.h"

void div_f(float* res, int cnt, float* op) {
    float arg;
    if(cnt < 2) res = NULL;
    else {
        *res = *op;
        for(int i = 1; i < cnt; i++) {
            arg = *(op + i);
            if(arg == 0) {
                *res = INFINITY;
            }
            else *res /= arg;
        }
    }
}