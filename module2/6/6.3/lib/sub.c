#include "../calc.h"

void sub_f(float* res, int cnt, float* op) {
    if(cnt < 2) res = NULL;
    else {
        *res = *op;
        for(int i = 1; i < cnt; i++) {
            *res -= *(op + i);
        }
    }   
}