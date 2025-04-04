#include "calc.h"
#include <dlfcn.h>

void print_cmd(char);
void list_operations(operation*);
void menu(operation*);
int find(operation*, const char*);

int main() {
    operation ops[4];
    strcpy(ops[0].name, "add");
    strcpy(ops[1].name, "sub");
    strcpy(ops[2].name, "mul");
    strcpy(ops[3].name, "div");
    
    menu(ops);
}

void list_operations(operation* op) {
    for(int i = 0; i < 4; i++) {
        printf("%d Operation %s\n", i+1, op[i].name);
    }
    printf("-1. Exit\n");
    printf("Enter option: ");
}
void menu(operation* ops) {
    void* handle;
    float res = 0;
    char cmd = 0;
    int i = 0;
    int num = 0;
    float * operands;
    while(cmd != -1) {
        res = 0;
        list_operations(ops);
        scanf("%hhd", &cmd);
        if(cmd == -1) continue;
        printf("Number of operands: ");
        scanf("%d", &num);
        printf("Enter %d operands: ", num);
    
        operands = malloc(num * sizeof(float));
        for(int j = 0; j < num; j++) scanf("%f", operands + j);
        switch (cmd)  {
        case 1:
            handle = dlopen("lib/libadd.so", RTLD_LAZY);
            ops[0].op = dlsym(handle, "add_f");
            if(i != -1) ops[0].op(&res, num, operands);
            dlclose(handle);
            break;
        case 2:
            handle = dlopen("lib/libsub.so", RTLD_LAZY);
            ops[1].op = dlsym(handle, "sub_f");
            ops[1].op(&res, num, operands);
            dlclose(handle);
            break;
        case 3:
            handle = dlopen("lib/libmul.so", RTLD_LAZY);
            ops[2].op = dlsym(handle, "mul_f");
            ops[2].op(&res, num, operands);
            dlclose(handle);
            break;
        case 4:
            handle = dlopen("lib/libdiv.so", RTLD_LAZY);
            ops[3].op = dlsym(handle, "div_f");
            ops[3].op(&res, num, operands);
            dlclose(handle);
            break;
        default:
            cmd = -1;
            break;
        }
        if(res == INFINITY) printf("Division by zero, stop it\n");
        else if(cmd != -1) printf("%f\n", res);
        free(operands);

    }
}
int find(operation* ops, const char* oper) {
    for(int i = 0; i < 4; i++) {
        if(strcmp(ops[i].name, oper) == 0) return i;
    }
    return -1;
}
