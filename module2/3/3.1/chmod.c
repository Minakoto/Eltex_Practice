#include "chmod.h"
void convert_perm(perm* p, mode_t mode) {
    p->permissions[0] = mode & S_IRUSR;
    p->permissions[1] = mode & S_IWUSR;
    p->permissions[2] = mode & S_IXUSR;

    p->permissions[3] = mode & S_IRGRP;
    p->permissions[4] = mode & S_IWGRP;
    p->permissions[5] = mode & S_IXGRP;

    p->permissions[6] = mode & S_IROTH;
    p->permissions[7] = mode & S_IWOTH;
    p->permissions[8] = mode & S_IXOTH;
}
void use_perm(perm* p, int args, char* perms) {
    struct stat cur_perms;
    stat(p->file, &cur_perms);
    printf("Current permissions:\n");
    convert_perm(p, cur_perms.st_mode);
    print_perm(p);
    if(perms != NULL) {   
        mode_t new_perms = parse_perms(perms, cur_perms.st_mode);
        printf("Modified permissions:\n");
        convert_perm(p, new_perms);
        print_perm(p);
    }
}
void print_perm(perm* p) {
    const char* type = "rwx";
    printf("%s\t", p->file);
    for(int i = 0; i < 3; i++) printf("%c", p->permissions[i] ? type[i] : '-');
    for(int i = 3; i < 6; i++) printf("%c", p->permissions[i] ? type[i - 3] : '-');
    for(int i = 6; i < 9; i++) printf("%c", p->permissions[i] ? type[i - 6] : '-');
    printf("\t");
    printf("\n");
}
mode_t mod_perm(char cat, char perms) {
    mode_t tmp = 0;
    if(cat == 0 || cat == 3) {
        perms&1 ? tmp |= S_IXUSR : 0;
        perms&2 ? tmp |= S_IWUSR : 0;
        perms&4 ? tmp |= S_IRUSR : 0;
    }
    if(cat == 1 || cat == 3) {
        perms&1 ? tmp |= S_IXGRP : 0;
        perms&2 ? tmp |= S_IWGRP : 0;
        perms&4 ? tmp |= S_IRGRP : 0;
    }
    if(cat == 2 || cat == 3) {
        perms&1 ? tmp |= S_IXOTH : 0;
        perms&2 ? tmp |= S_IWOTH : 0;
        perms&4 ? tmp |= S_IROTH : 0;
    }
    return tmp;
}
mode_t parse_perms(char* perms, mode_t tmp) {
    int len = strlen(perms);
    char cat = -1, op = 0;
    char prm;
    int str;
    if(len < 4 && (perms[0] < 58 && perms[0] > 47)) {
        if(len-- != 0) {
            if(perms[len]&1) tmp |= S_IXOTH;
            else tmp &= ~S_IXOTH;
            if(perms[len]&1) tmp |= S_IWOTH;
            else tmp &= ~S_IWOTH;
            if(perms[len]&1) tmp |= S_IROTH;
            else tmp &= ~S_IROTH;
        }
        if(len-- != 0) {
            if(perms[len]&1) tmp |= S_IXGRP;
            else tmp &= ~S_IXGRP;
            if(perms[len]&1) tmp |= S_IWGRP;
            else tmp &= ~S_IWGRP;
            if(perms[len]&1) tmp |= S_IRGRP;
            else tmp &= ~S_IRGRP;
        }
        if(len-- != 0) {
            if(perms[len]&1) tmp |= S_IXUSR;
            else tmp &= ~S_IXUSR;
            if(perms[len]&1) tmp |= S_IWUSR;
            else tmp &= ~S_IWUSR;
            if(perms[len]&1) tmp |= S_IRUSR;
            else tmp &= ~S_IRUSR;
        }
    }
    else if(perms[0] =='u' || perms[0] == 'g' || perms[0] == 'o' || perms[0] == 'a'){
        for(int i = 0; i < len; i++) {
            switch(perms[i]) {
                case 'u':
                    if(cat != -1) {
                        if(op > 0) tmp |= mod_perm(cat, prm);
                        else tmp &= ~mod_perm(cat, prm);
                        op = prm = 0;
                    }
                    cat = 0;
                    break;
                case 'g':
                    if(cat != -1) {
                        if(op > 0) tmp |= mod_perm(cat, prm);
                        else tmp &= ~mod_perm(cat, prm);
                        cat = -1;
                        op = prm = 0;
                    }
                    cat = 1;
                    break;
                case 'o':
                    if(cat != -1) {
                        if(op > 0) tmp |= mod_perm(cat, prm);
                        else tmp &= ~mod_perm(cat, prm);
                        cat = -1;
                        op = prm = 0;
                    }
                    cat = 2;
                    break;
                case 'a':
                    if(cat != -1) {
                        if(op > 0) tmp |= mod_perm(cat, prm);
                        else tmp &= ~mod_perm(cat, prm);
                        cat = -1;
                        op = prm = 0;
                    }
                    cat = 3;
                    break;
                case '+':
                    op = 1;
                    break;
                case '-':
                    op = -1;
                    break;
                case 'r':
                    prm += 4;
                    break;
                case 'w':
                    prm += 2;
                    break;
                case 'x':
                    prm += 1;
                    break;
            }
        }
        if(op > 0) tmp |= mod_perm(cat, prm);
        else tmp &= ~mod_perm(cat, prm);
    }
    else {
        printf("Error\n");
    }
    return tmp;
}
int main(int argc, char* argv[]) {
    perm p;
    if(argc == 2) {
        p.file = malloc(strlen(argv[1])*sizeof(char));
        strcpy(p.file, argv[1]);
        use_perm(&p, argc, NULL);
    }
    else if(argc == 3) {
        p.file = malloc(strlen(argv[2])*sizeof(char));
        strcpy(p.file, argv[2]);
        use_perm(&p, argc, argv[1]);
    }
    else p.file = malloc(sizeof(char));
    free(p.file);
}