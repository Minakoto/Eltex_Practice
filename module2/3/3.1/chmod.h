#ifndef CHMOD
#define CHMOD

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <math.h>

typedef struct perm {
    uint8_t permissions[9];
    char* file;
} perm;

void use_perm(perm*, int, char*);
void convert_perm(perm*, mode_t);
void print_perm(perm*);
mode_t mod_perm(char, char);
mode_t parse_perms(char*, mode_t);

#endif