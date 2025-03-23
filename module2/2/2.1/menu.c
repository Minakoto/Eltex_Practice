#include "phonebook.h"


char menu_l1(Entry*, short*, char);
char menu_l2(Entry*, short*, char);
void print_options();
void print_types();
void print_book(Entry*, short);
void print_person(Person*);
void print_adr(Address*);
void print_job(Job*);
void print_contacts(Contacts*);
void print_id(Entry*, short);
char handle_error(char);
int is_empty(char*);

int main() {
    srand(time(NULL));
    Entry Phonebook[SIZE];
    short current = 0;
    char big_cmd = 0;
    print_options();
    while(big_cmd != 7) {
        if(scanf("%hhd", &big_cmd))
            big_cmd = handle_error(menu_l1(Phonebook, &current, big_cmd));
    }
    return 0;
}

char menu_l1(Entry* book, short* cur, char cmd) {
    char res = 1;
    short id;
    char* string1;
    char * string2;
    printf("\n");
    switch(cmd) {
        case 1:
            string1 = (char*)malloc(ENT_SIZE * sizeof(char));
            string2 = (char*)malloc(ENT_SIZE * sizeof(char));
            printf("Input first and last names: ");
            if(scanf("%s", string1) && scanf("%s", string2))
                res = init_entry(book, string1, string2, cur);
            else res = -3;
            if(res == 1) *cur += 1;
            free(string1);
            free(string2);
            break;
        case 2: //edit
            res = menu_l2(book, cur, cmd);
            break;
        case 3: //del
            res = menu_l2(book, cur, cmd);
            break;
        case 4:
            printf("Which ID?");
            scanf("%hd", &id);
            res = del(book, cur, id);
            break;
        case 5:
            print_book(book, *cur);
            break;
        case 6:
            print_id(book, *cur);
            break;
        case 7:
            res = 7;
        default:
    }
    printf("Avalalbe IDs: ");
    print_id(book, *cur);
    print_options();
    return res;
}
char menu_l2(Entry* book, short* cur, char cmd) {
    char res = 1;
    char cmd2;
    short val;
    char* string;
    short wrk;
    printf("Which ID? ");
    scanf("%hd", &wrk);
    print_types();
    wrk = find(book, wrk, *cur);
    if(wrk != -1 && scanf("%hhd", &cmd2)) {
        printf("Current:\n");
        switch (cmd2) {
        case 1:
            print_person(&(book + wrk)->person);
            if(cmd == 2) {
                printf("Choose field:\n1.First name\n2. Last name\n3. Middle name\n");
                scanf("%hhd", &cmd2);
                printf("New field: ");
                string = malloc(ENT_SIZE*sizeof(char));
                scanf("%s", string);
                res = edit_person(&(book + wrk)->person, cmd2, string);
                free(string);
                printf("New:\n");
                print_person(&(book + wrk)->person);
            }
            else if(cmd == 3)
                zero_person(&(book + wrk)->person);
            break;
        case 2:
            print_adr(&(book + wrk)->adress);
            printf("%hd", wrk);
            if(cmd == 2) {
                printf("Choose field:\n1. City\n2. Street\n3. Home number\n4. Apt number\n");
                scanf("%hhd", &cmd2);
                printf("New field: ");
                if(cmd2 == 1 || cmd2 == 2) {
                    string = malloc(ADR_SIZE*sizeof(char));
                    scanf("%s", string);
                    res = add_address_char(&(book + wrk)->adress, cmd2, string);
                    free(string);
                }
                else if(cmd2 == 3 || cmd2 == 4) {
                    scanf("%hd", &val);
                    res = add_address_short(&(book + wrk)->adress, cmd2, val);
                }
                printf("New:\n");
                print_adr(&(book + wrk)->adress);
            }
            else if(cmd == 3)
                zero_address(&(book + wrk)->adress);
            break;
        case 3:
            print_job(&(book + wrk)->job);
            if(cmd == 2) {
                printf("Choose field:\n1. Office city\n2.Office street\n3. Position\n");
                printf("4. Office number\n5. Office room number\n6. Salary\n");
                scanf("%hhd", &cmd2);
                printf("New field: ");
                if(cmd2 == 1 || cmd2 == 2 || cmd2 == 3) {
                    if(cmd == 3)
                        string = malloc(ENT_SIZE*sizeof(char));
                    else
                        string = malloc(ADR_SIZE*sizeof(char));
                    scanf("%s", string);
                    res = add_job_char(&(book + wrk)->job, cmd2, string);
                    free(string);
                }
                else if(cmd2 == 4 || cmd2 == 5 || cmd2 == 6) {
                    scanf("%hd", &val);
                    res = add_job_short(&(book + wrk)->job, cmd2, val);
                }
                printf("New:\n");
                print_job(&(book + wrk)->job);
            }
            else if(cmd == 3)
                zero_job(&(book + wrk)->job);
            break;
        case 4:
            print_job(&(book + wrk)->job);
            if(cmd == 2) {
                printf("Choose field:\n1. Email\n2.Phone number\n3. Telegram\n4. VK\n");
                scanf("%hhd", &cmd2);
                printf("New field: ");
                if(cmd <= 4) {
                    if(cmd2 == 1) string = malloc(EMAIL_SIZE*sizeof(char));
                    else if(cmd2 == 2) string = malloc(PHONE_SIZE*sizeof(char));
                    else if(cmd2 == 3) string = malloc(TG_SIZE*sizeof(char));
                    else string = malloc(VK_SIZE*sizeof(char));
                    scanf("%s", string);
                    res = add_contacts(&(book + wrk)->contacts, cmd2, string);
                    free(string);
                    printf("New:\n");
                    print_contacts(&(book + wrk)->contacts);
                }
            }
            else if(cmd == 3)
                zero_job(&(book + wrk)->job);
            break;
        case 5:
        default:
        }
    }
}
void print_options() {
    printf("\nMENU: \n");
    printf("1. Initiate entry\n");
    printf("2. Edit entry\n");
    printf("3. Delete from entry\n");
    printf("4. Delete Entry\n");
    printf("5. View phonebook\n");
    printf("6. List IDs\n");
    printf("7. Exit\n");
    printf("Input command: ");
}
void print_types() {
    printf("\nCategory:\n");
    printf("1. Person\n");
    printf("2. Address\n");
    printf("3. Job\n");
    printf("4. Contacts\n");
    printf("5. Back\n");
}
void print_book(Entry* book, short cur) {
    if(cur == 0) printf("Phonebook empty!\n");
    else {
        for(int i = 0; i < cur; i++) {
            printf("ID: %hd\n", (book + i)->id);
            print_person(&(book+i)->person);
            print_adr(&(book+i)->adress);
            print_job(&(book+i)->job);
            print_contacts(&(book+i)->contacts);
        }
    }
}
void print_person(Person* p) {
    printf("Full name: ");
    if(!is_empty(p->firstname)) printf("%s ", p->firstname);
    if(!is_empty(p->lastname)) printf("%s ", p->lastname);
    if(!is_empty(p->middlename)) printf("%s", p->middlename);
    printf("\n");
}
void print_adr(Address* a) {
    printf("Address\n");
    if(!is_empty(a->city)) printf("City: %s", a->city);
    if (!is_empty(a->street)) printf("Adr: %s",a->street);
    if(a->adr != 0) printf(",%hd", a->adr);
    if(a->apt != 0) printf(", %hd", a->apt);
    printf("\n");
}
void print_job(Job* j) {
    printf("Job\n");
    print_adr(&j->office);
    if(!is_empty(j->position))
        printf("Description: %s, %hd", j->position, j->salary);
    printf("\n");
}
void print_contacts(Contacts* c) {
    printf("Contacts: ");
    if(!is_empty(c->email)) printf("Email: %s\n", c->email);
    if(!is_empty(c->phone)) printf("Phone: %s\n", c->phone);
    if(!is_empty(c->social_t)) printf("TG: %s\n", c->social_t);
    if(!is_empty(c->social_vk)) printf("VK: %s", c->social_vk);
    printf("\n");
}
void print_id(Entry* book, short cur) {
    if(cur == 0) printf("Phonebook empty!\n");
    else {
        for(int i = 0; i < cur - 1; i++) {
            printf("%hd, ", (book + i)->id);
        }
        printf("%hd", (book + cur - 1)->id);
    }
}
int is_empty(char* string) {
    return (string[0] == '0') ? 1: 0;
}

char handle_error(char res) {
    char r = res;
    if(r == -1) printf("Initialization error!\n");
    else if (r == -2) printf("Editing/Adding error!\n");
    else if (r == -3) printf("Input error!\n");
    return r;
}