#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

typedef struct operation {
    char name[3];
    void (*op) (float*, int, float*);
} operation;


void add_f(float*, int, float*);
void sub_f(float*, int, float*);
void mul_f(float*, int, float*);
void div_f(float*, int, float*);