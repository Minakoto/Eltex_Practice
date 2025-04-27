#include "queue.h"   

p_queue* enqueue(p_queue* q, char* msg, short pri) {
    p_queue* rt = q;
    p_queue* tmp = malloc(sizeof(p_queue));
    strncpy(tmp->msg, msg, MSG_SIZE);
    tmp->priority = pri;
    if(q == NULL) {
        tmp->next = NULL;
        return tmp;
    }
    if(rt->priority > tmp->priority) {
        tmp->next = rt;
        return tmp;
    }
    while(rt->next != NULL && rt->next->priority <= tmp->priority) rt = rt->next;

    if(rt->next == NULL) {
        tmp->next = NULL;
        rt->next = tmp;
        return q;
    }
    tmp->next = rt->next;
    rt->next = tmp;
    return q;
}

p_queue* dequeue(p_queue** q, short pri) {
    if(*q == NULL) return NULL;
    p_queue* new_q = *q;
    if(pri == -1) *q = (*q)->next;
    else {
        p_queue* prev = NULL;
        while(new_q != NULL && new_q->priority != pri) {
            prev = new_q;
            new_q = new_q->next;
        }
        if(prev == NULL) *q = new_q->next;
        else prev->next = new_q->next;
    }
    return new_q;
}
p_queue* dequeue_min(p_queue** q, short pri) {
    if(*q == NULL) return NULL;
    p_queue* new_q = NULL, *tmp = *q, *prev = NULL;
    while(tmp != NULL && tmp->priority < pri) {
        new_q = enqueue(new_q, tmp->msg, tmp->priority);
        *q = (*q)->next;
        tmp = tmp->next;
    }
    return new_q;
}


void print(p_queue* q) {
    if(q == NULL) {
        printf("Empty\n");
        return;
    }
    p_queue* rt = q;
    while(rt != NULL) {
        print_1(rt);
        rt = rt->next;
    }
}
void print_1(p_queue* q) {
    if(q == NULL) {
        printf("Empty\n");
        return;
    }
    printf("%d %s\n",q->priority, q->msg);
}

void clean(p_queue* q) {
     if(q != NULL) free(q);
}