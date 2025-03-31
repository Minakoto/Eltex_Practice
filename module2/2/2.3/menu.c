#include "calc.h"

void add_f(float* res, int cnt, float* op) {
    if(cnt < 2) res = NULL;
    else {
        *res = *op;
        for(int i = 1; i < cnt; i++) {
            *res += *(op + i);
        }
    }
}
void sub_f(float* res, int cnt, float* op) {
    if(cnt < 2) res = NULL;
    else {
        *res = *op;
        for(int i = 1; i < cnt; i++) {
            *res -= *(op + i);
        }
    }   
}
void mul_f(float* res, int cnt, float* op) {
    if(cnt < 2) res = NULL;
    else {
        *res = *op;
        for(int i = 1; i < cnt; i++) {
            *res *= *(op + i);
        }
    }    
}
void div_f(float* res, int cnt, float* op) {
    float arg;
    if(cnt < 2) res = NULL;
    else {
        *res = *op;
        for(int i = 1; i < cnt; i++) {
            arg = *(op + i);
            if(arg == 0) {
                res = NULL;
                break;
            }
            else *res /= arg;
        }
    }
}

char menu_f();

void print_cmd(char);

void list_operations(operation* op) {
    for(int i = 0; i < 4; i++) {
        printf("%d Operation %s\n", i+1, op[i].name);
    }
    printf("-1. Exit\n");
    printf("Enter option: ");
}

void menu(operation* ops) {
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
            i = find(ops, "add");
            if(i != -1) ops[i].op(&res, num, operands);
            break;
        case 2:
            i = find(ops, "sub");
            if(i != -1) ops[i].op(&res, num, operands);
            break;
        case 3:
            i = find(ops, "mul");
            if(i != -1) ops[i].op(&res, num, operands);
            break;
        case 4:
            i = find(ops, "div");
            if(i != -1) ops[i].op(&res, num, operands);
            break;
        default:
            cmd = -1;
            break;
        }
        if(cmd != -1) printf("%f\n", res);
        free(operands);

    }
}

int find(operation* ops, const char* oper) {
    for(int i = 0; i < 4; i++) {
        if(strcmp(ops[i].name, oper) == 0) return i;
    }
    return -1;
}

int main() {
    operation ops[4] = {
        {"add", add_f},
        {"sub", sub_f},
        {"mul", mul_f},
        {"div", div_f}
    };
    menu(ops);
}
