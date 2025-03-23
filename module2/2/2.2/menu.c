#include "calc.h"

char menu_d();
char menu_f();

void print_cmd(char);

int main() {
    char big_cmd = -1, mode = 0;
    while(mode <= 0) {
        printf("Pick a mode\n1. Integer\n2. Float\nInput: ");
        scanf("%hhd", &mode);
        if(mode > 2 || mode < 0) printf("Wrong mode!\n");
    }
    while(big_cmd != 0) {
        print_cmd(mode);
        if(mode == 1) {
            big_cmd = menu_d();
        }
        else if(mode == 2) {
            big_cmd = menu_f();
        }
    }
    return 0;
}

char menu_d() {
    getchar();
    char res = 1;
    char cmd;
    int *operand, result;
    unsigned int cnt;
    scanf("%c", &cmd);
    operand = malloc(cnt * sizeof(int));
    switch (cmd) {
    case '+':
        printf("Number of Operands:");
        scanf("%u", &cnt);
        printf("Enter operands: ");
        for(int i = 0; i < cnt; i++) scanf("%d", operand + i);
        add_d(&result, cnt, operand);
        printf("\nRESULT: %d\n\n", result);
        break;
    case '-':
        printf("Number of Operands:");
        scanf("%u", &cnt);
        printf("Enter operands: ");
        for(int i = 0; i < cnt; i++) scanf("%d", operand + i);
        sub_d(&result, cnt, operand);
        printf("\nRESULT: %d\n\n\n", result);
        break;
    case '*':
        printf("Number of Operands:");
        scanf("%u", &cnt);
        printf("Enter operands: ");
        for(int i = 0; i < cnt; i++) scanf("%d", operand + i);
        mul_d(&result, cnt, operand);
        printf("\nRESULT: %d\n\n", result);
        break;
    case '/':
        printf("Number of Operands:");
        scanf("%u", &cnt);
        printf("Enter operands: ");
        for(int i = 0; i < cnt; i++) scanf("%d", operand + i);
        div_d(&result, cnt, operand[0], operand + 1);
        printf("\nRESULT: %d\n\n", result);
        break;
    case '%':
        printf("Number of Operands:");
        scanf("%u", &cnt);
        printf("Enter operands: ");
        for(int i = 0; i < cnt; i++) scanf("%d", operand + i);
        mod_d(&result, cnt, operand[0], operand + 1);
        printf("\nRESULT: %d\n\n", result);
        break;
    case '0':
        res = 0;
        break;
    default:
        printf("Unknown operation!\n");
    }
    free(operand);
    result = 0;
    return res;
}

char menu_f() {
    getchar();
    char res = 1;
    char cmd;
    float *operand, result;
    unsigned int cnt;
    scanf("%c", &cmd);
    operand = malloc(cnt * sizeof(int));
    switch (cmd) {
    case '+':
        printf("Number of Operands:");
        scanf("%u", &cnt);
        printf("Enter operands: ");
        for(int i = 0; i < cnt; i++) scanf("%f", operand + i);
        add_f(&result, cnt, operand);
        printf("\nRESULT: %f\n\n", result);
        break;
    case '-':
        printf("Number of Operands:");
        scanf("%u", &cnt);
        printf("Enter operands: ");
        for(int i = 0; i < cnt; i++) scanf("%f", operand + i);
        sub_f(&result, cnt, operand);
        printf("\nRESULT: %f\n\n", result);
        break;
    case '*':
        printf("Number of Operands:");
        scanf("%u", &cnt);
        printf("Enter operands: ");
        for(int i = 0; i < cnt; i++) scanf("%f", operand + i);
        mul_f(&result, cnt, operand);
        printf("\nRESULT: %f\n\n", result);
        break;
    case '/':
        printf("Number of Operands:");
        scanf("%u", &cnt);
        printf("Enter operands: ");
        for(int i = 0; i < cnt; i++) scanf("%f", operand + i);
        div_f(&result, cnt, operand[0], operand + 1);
        if(&result == NULL) printf("\nRESULT: NULL\n\n");
        else printf("\nRESULT: %f\n\n", result);
        break;
    case '0':
        res = 0;
        break;
    default:
        printf("Unknown operation!\n");
    }
    free(operand);
    result = 0;
    return res;
}

void print_cmd(char mode) {

    const char opt[] = {'+', '-', '*', '/', '%'};
    printf("MENU\n");
    for(int i = 0; i < 4; i++) {
        printf("Operation \"%c\"\n",*(opt + i));
    }
    if(mode == 1) printf("Operation \"%c\"\n", *(opt + 4));
    printf("0 - Exit\n");
}
