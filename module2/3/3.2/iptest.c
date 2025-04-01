#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


uint32_t convert(char* str) {
    uint32_t res = 0;
    uint8_t quad;
    char* tmp = malloc((strlen(str) + 1)* sizeof(char));
    strcpy(tmp, str);
    char* part = strtok(tmp, ".");
    for(int i = 0; i < 4; i++) {
        quad = (uint8_t)atoi(part);
        res = (res << 8) | quad;
        part = strtok(NULL, ".");
    }
    free(tmp);
    return res;
}
uint32_t genip(char* mask) {
    uint32_t tmp = 0;
    uint8_t quad, rnd = 0;
    char* tmpstr = malloc((strlen(mask) + 1)*sizeof(char));
    strcpy(tmpstr, mask);
    char* part = strtok(tmpstr, ".");
    for(int i = 4; i > 0; --i) {
        quad = atoi(part);
        rnd = (uint8_t)((rand() % (quad + 1)));
        tmp = (tmp << 8) | (rnd);
        part = strtok(NULL, ".");
    }
    free(tmpstr);
    return tmp;
}
int is_connected(uint32_t subnet,uint32_t mask,uint32_t ip) {
    return ((subnet & mask) == (subnet & ip)) ? 1 : 0;
}
int main(int argc, char* argv[]) {
    char* str_mask = argv[2];
    char * str_subnet = argv[1];
    int N = atoi(argv[3]);
    int cnt = 0;
    srand(time(NULL));
    uint32_t ip, subnet, mask;
    subnet = convert(str_subnet);
    mask = convert(str_mask);
    for(int i = 0; i < N; i++) {
        ip = genip(argv[2]);
        cnt += is_connected(subnet, mask, ip);
    }
    printf("Ammount connected: %d, %.3f%%\n", cnt, ((float)cnt/N) * 100);
    printf("Ammount not connected: %d, %.3f%%\n", N - cnt, ((float)(N - cnt)/N) * 100);
}