#include "calc.h"

void add_d(int* res, int cnt, int* op) {
    if(cnt < 2) res = NULL;
    else {
        *res = *op;
        for(int i = 1; i < cnt; i++) {
            *res += *(op + i);
        }
    }
}
void sub_d(int * res, int cnt, int* op) {
    if(cnt < 2) res = NULL;
    else {
        *res = *op;
        for(int i = 1; i < cnt; i++) {
            *res -= *(op + i);
        }
    }
}
void mul_d(int* res, int cnt, int* op) {
    if(cnt < 2) res = NULL;
    else {
        *res = *op;
        for(int i = 1; i < cnt; i++) {
            *res *= *(op + i);
        }
    }
}
void div_d(int* res, int cnt, int first, int* op) {
    int arg;
    if(cnt < 2) res = NULL;
    else {
        *res = first;
        for(int i = 0; i < cnt; i++) {
            arg = *(op + i);
            if(arg == 0) {
                res = NULL;
                break;
            }
            else *res /= arg;
        }
    }
}
void mod_d(int* res, int cnt, int first, int* op) {
    int arg;
    if(cnt < 2) res = NULL;
    else {
        *res = first;
        for(int i = 0; i < cnt; i++) {
            arg = *(op + i);
            *res %= arg;
        }
    }  
}

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
void div_f(float* res, int cnt, float first, float* op) {
    float arg;
    if(cnt < 2) res = NULL;
    else {
        *res = first;
        for(int i = 0; i < cnt; i++) {
            arg = *(op + i);
            if(arg == 0) {
                res = NULL;
                break;
            }
            else *res /= arg;
        }
    }
}