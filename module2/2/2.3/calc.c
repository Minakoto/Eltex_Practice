#include "calc.h"

void add_f(float* res, int cnt, float* op) {
    if(cnt < 2) res = NULL;
    else {
        *res = *op;
        for(int i = 1; i < cnt; i++) {
            *res += *(op + i);
        }
    }
}
void sub_f(float* res, int cnt, float* op) {
    if(cnt < 2) res = NULL;
    else {
        *res = *op;
        for(int i = 1; i < cnt; i++) {
            *res -= *(op + i);
        }
    }   
}
void mul_f(float* res, int cnt, float* op) {
    if(cnt < 2) res = NULL;
    else {
        *res = *op;
        for(int i = 1; i < cnt; i++) {
            *res *= *(op + i);
        }
    }    
}
void div_f(float* res, int cnt, float* op) {
    float arg;
    if(cnt < 2) res = NULL;
    else {
        *res = *op;
        for(int i = 1; i < cnt; i++) {
            arg = *(op + i);
            if(arg == 0) {
                res = NULL;
                break;
            }
            else *res /= arg;
        }
    }
}