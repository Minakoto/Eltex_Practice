#include "queue.h"


int main() {
    p_queue* pq = NULL;
    srand(time(NULL));
    char* tmp;
    // for(int j = 0; j < 50; j++) {
    //     tmp = malloc(25*sizeof(char));
    //     for(int i = 0; i < 25; i++) {
    //         tmp[i] = 32 + (rand() % 128);
    //     }
    //     short pri = rand() % 255;
    //     pq = Add(pq, tmp, pri);
    //     free(tmp);
    // }
    // printf("Initial queue\n");
    // print(pq);
    // printf("\n\n");
    // p_queue* tmp1 = GetFirst(pq);
    // p_queue* tmp2 = GetFromPriority(pq, 54);
    // p_queue* tmp3 = GetMinPriority(pq, 200);
    // printf("Get highest priority\n");
    // print(tmp1);
    // printf("\n\n");
    // printf("Get with priority = 54\n");
    // print(tmp2);
    // printf("\n\n");
    // printf("Get with priority less than 200\n");
    // print(tmp3);
    char cmd = 0;
    char* string;
    short prior = 0;
    int t = 0;

    while (cmd != 6){
        printf("1. Generate\n2. Get with highest priority\n3. Get with priority \n4. Get all higher than given\n5. Print queue\n6. Exit\nEnter option: ");
        scanf("%hhd", &cmd);
        switch(cmd) {
            case 1:
                printf("Enter number: ");
                scanf("%d", &t);
                for(int j = 0; j < t; j++) {
                    tmp = malloc(25*sizeof(char));
                    for(int i = 0; i < 25; i++) {
                        tmp[i] = 32 + (rand() % 128);
                    }
                    short pri = rand() % 255;
                    pq = Add(pq, tmp, pri);
                    free(tmp);
                }
                break;
            case 2:
                p_queue* tmp1 = GetFromPriority(pq, pq->priority);
                //print(pq);
                //pq = Delete(pq, tmp1);
                break;
            case 3:
                printf("Input priority: ");
                scanf("%hd", &prior);
                p_queue* tmp2 = GetFromPriority(pq, prior);
                //pq = Delete(pq, tmp2);
                break;
            case 4:
                printf("Input priority: ");
                scanf("%hd", &prior);
                p_queue* tmp3 = GetMinPriority(pq, prior);
                //print(tmp3);
                break;
            case 5:
                print(pq);
                break;
            case 6:
            default:
                cmd = 6;
        }
    }
    
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
    while(rt->next != NULL && rt->next->priority >= tmp->priority) rt = rt->next;

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
    root = Delete(root, root);
    
    
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
    if(rt == root) {
        root = root->next;
        return root;
    }
    if(rt == NULL) {
        printf("Not found\n");
        return NULL;
    }
    if(prev == NULL) root = root->next;
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

p_queue* Delete(p_queue* pq, p_queue* todel) {
    p_queue* tmp = pq;
    p_queue* prev = NULL;
    while(tmp->priority != todel->priority) {
        prev = tmp;
        tmp = tmp->next;
    }
    if(tmp == NULL) {
        return pq;
    }
    if(tmp == pq) {
        pq = pq->next;
    }
    else {
        prev->next = tmp->next;
    }
    free(tmp);
    pq = Delete(pq, todel->next);
    return pq;
}