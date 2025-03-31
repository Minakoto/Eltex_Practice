#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

void use_perm(perm* p, int args, char*);
void convert_perm(perm* p, unsigned short mode);
perm parse_perms(char* perms);

typedef struct perm {
    uint8_t user[3];
    uint8_t group[3];
    uint8_t other[3];
    char* file;
} perm;

int main(int argc, char* argv[]) {
    perm p;
    if(argc == 2) {
        p.file = malloc(strlen(argv[1])*sizeof(char));
        strcpy(p.file, argv[1]);
        use_perm(p, argc, NULL);
    }
    else if(argc == 3) {
        p.file = malloc(strlen(argv[2])*sizeof(char));
        strcpy(p.file, argv[2]);
        use_perm(p, argc, argv[1]);
    }
    else p.file = malloc(sizeof(char));
    free(p.file);
}

void use_perm(perm* p, int args, char* perms) {
    struct stat cur_perms;
    stat(p->file, &cur_perms);
    printf("Current permissions:\n");
    convert_perm(p, cur_perms.st_mode);
    print_perm(p);
    if(args == 2) {
        *p = parse_perms(perms);
        printf("Modified permissions:\n");
        print_perm(p);
    }
}
perm parse_perms(char* perms) {
    perm tmp;
    if(perms[0] < 58 && perms[0] > 47) {
        
    }

}

void convert_perm(perm* p, unsigned short mode) {
    p->user[0] = mode & S_IRUSR;
    p->user[1] = mode & S_IWUSR;
    p->user[2] = mode & S_IXUSR;

    p->group[0] = mode & S_IRGRP;
    p->group[1] = mode & S_IWGRP;
    p->group[2] = mode & S_IXGRP;

    p->other[0] = mode & S_IROTH;
    p->other[1] = mode & S_IWOTH;
    p->other[2] = mode & S_IXOTH;
}
void print_perm(perm* p) {
    const char* type[3] = {'r', 'w', 'x'};
    printf("%s\t", p->file);
    for(int i = 0; i < 3; i++) printf("%c", p->user[i] ? type[i] : '-');
    for(int i = 0; i < 3; i++) printf("%c", p->group[i] ? type[i] : '-');
    for(int i = 0; i < 3; i++) printf("%c", p->other[i] ? type[i] : '-');
    printf("\t");
    for(int i = 0; i < 3; i++) printf("%hhd", p->user[i]);
    for(int i = 0; i < 3; i++) printf("%hhd", p->group[i]);
    for(int i = 0; i < 3; i++) printf("%hhd", p->other[i]);
    printf("\n");
}