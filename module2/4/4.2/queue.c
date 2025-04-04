#include "queue.h"


int main() {
    p_queue* pq = NULL;
    pq = Add(pq, "Hello", 24);
    pq = Add(pq, "Goodbye", 23);
    pq = Add(pq, "Greet", 255);
    print(pq);
}

p_queue* Add(p_queue* root, char* msg, short pri) {
    p_queue* rt = root;
    p_queue* tmp = malloc(sizeof(p_queue));
    strncpy(tmp->msg, msg, MSG_SIZE);
    tmp->priority = pri;
    if(root == NULL) {
        tmp->next = NULL;
        return tmp;
    }
    if(rt->priority < tmp->priority) {
        tmp->next = rt;
        return tmp;
    }
    while(rt->priority >= tmp->priority && rt->next != NULL) rt = rt->next;
    if(rt->next == NULL) {
        tmp->next = NULL;
        rt->next = tmp;
        return root;
    }
    tmp->next = rt->next;
    rt->next = tmp;
    return root;
}
p_queue* GetFirst(p_queue* root) {
    p_queue* rt = root;
    if(root == NULL) {
        printf("Queue empty\n");
        return NULL;
    }
    root = root->next;
    return rt;
}
p_queue* GetFromPriority(p_queue* root, short pri) {
    p_queue* rt = root;
    p_queue* prev = NULL;
    if(root == NULL) {
        printf("Queue empty\n");
        return NULL;
    }
    while(rt != NULL && rt->priority != pri) {
        prev = rt;
        rt = rt->next;
    }
    if(rt == NULL) {
        printf("Not found\n");
        return NULL;
    }
    if(prev == NULL) root = rt->next;
    else prev->next = rt->next;
    return rt;
}
p_queue* GetMinPriority(p_queue* root, short pri) {
    p_queue* rt = root;
    p_queue* prev = NULL;
    if(root == NULL) {
        printf("Queue empty\n");
        return NULL;
    }
    while(rt != NULL && rt->priority > pri) {
        prev = rt;
        rt = rt->next;
    }
    if(rt == NULL) {
        printf("Not found\n");
        return NULL;
    }
    if(prev == NULL) root = rt->next;
    else prev->next = rt->next;
    return rt;
}

void print(p_queue* root) {
    p_queue* rt = root;
    while(rt != NULL) {
        printf("%d %s\n",rt->priority, rt->msg);
        rt = rt->next;
    }

}