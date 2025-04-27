#include "queue.h"

int main() {
    p_queue* pq = NULL;
    p_queue* pq2 = NULL;
    srand(time(NULL));
    char* string, *tmp;
    char cmd = 0;
    short prior = 0;
    int t = 0;

    while (cmd != 6){
        printf("1. Generate\n2. Dequeue highest\n3. Dequeue\n4. Dequeue >=\n5. Print\n6. Exit\nEnter option: ");
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
                    prior = rand() % 255;
                    pq = enqueue(pq, tmp, prior);
                    free(tmp);
                }
                break;
            case 2:
                pq2 = dequeue(&pq, -1);
                printf("\nDequeued:\n");
                print_1(pq2);
                if(pq2 != NULL) free(pq2);
                break;
            case 3:
                printf("Input priority: ");
                scanf("%hd", &prior);
                pq2 = dequeue(&pq, prior);
                printf("\nDequeued:\n");
                print_1(pq2);
                if(pq2 != NULL) free(pq2);
                break;
            case 4:
                printf("Input priority: ");
                scanf("%hd", &prior);
                pq2 = dequeue_min(&pq, prior);
                printf("\nDequeued:\n");
                print(pq2);
                if(pq2 != NULL) free(pq2);
                break;
            case 5:
                printf("\nQueue\n");
                print(pq);
                break;
            case 6:
            default:
                cmd = 6;
        }
    }
    if(pq != NULL) free(pq);
}