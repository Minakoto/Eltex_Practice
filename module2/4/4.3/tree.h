#ifndef TREE
#define TREE
#include "phonebook.h"

typedef struct btree {
    Entry val;
    struct btree* left, *right;
    int height;
} btree;

void Add(Entry, btree**);
char Del(short, btree**);
void Print(btree*, int);
btree* Search(btree*, int);
// btree* Find(int, btree*);
// int height(btree*);
// int balfactor(btree*);

// void fixheight(btree*);
// btree* rotater(btree*);
// btree* rotatel(btree*);
// btree* balance(btree*);
#endif