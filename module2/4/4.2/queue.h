#ifndef QUEUE
#define QUEUE
#define MSG_SIZE 25
#define QUEUE_SIZE 50
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct p_queue {
    short priority;
    char msg[MSG_SIZE];
    struct p_queue* next;
} p_queue;

p_queue* Add(p_queue*, char*, short);
p_queue* GetFirst(p_queue*);
p_queue* GetFromPriority(p_queue*, short);
p_queue* GetMinPriority(p_queue*, short);
void print(p_queue*);
#endif