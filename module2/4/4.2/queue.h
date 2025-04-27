#ifndef QUEUE
#define QUEUE
#define MSG_SIZE 25
#define QUEUE_SIZE 50
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct p_queue {
    short priority;
    char msg[MSG_SIZE];
    struct p_queue* next;
} p_queue;

p_queue* enqueue(p_queue*, char*, short);
p_queue* dequeue(p_queue**, short); // s - -1 - max
p_queue* dequeue_min(p_queue**, short);
void print(p_queue*);
void print_1(p_queue*);
#endif