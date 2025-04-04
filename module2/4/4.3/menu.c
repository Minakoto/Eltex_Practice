#include "phonebook.h"
#include "tree.h"

btree* menu_l1(btree*, short*, char);
btree* menu_l2(btree*, short*, char);
void print_options();
void print_types();
void print_book(btree*);
void print_list(btree*);
void print_person(Person*);
char handle_error(char);
int is_empty(char*);

int main() {
    srand(time(NULL));
    btree* head = NULL;
    short current = 0;
    char big_cmd = 0;
    print_options();

    while(big_cmd != 6) {
        if(scanf("%hhd", &big_cmd))
            head = menu_l1(head, &current, big_cmd);
    }
    return 0;
}

btree* menu_l1(btree* head, short* cur, char cmd) {
    btree* tmp = head;
    char res = 1;
    short id;
    char* string1;
    char * string2;
    printf("\n");
    switch(cmd) {
        case 1:
            Entry t;
            string1 = (char*)malloc(ENT_SIZE * sizeof(char));
            string2 = (char*)malloc(ENT_SIZE * sizeof(char));
            printf("Input first and last names: ");
            if(scanf("%s", string1) && scanf("%s", string2)) {
                t = init_entry(string1, string2, cur);
                Add(t, &tmp);
            }
            else res = -3;
            if(res == 1) *cur += 1;
            free(string1);
            free(string2);
            break;
        case 2: //edit
            tmp = menu_l2(tmp, cur, cmd);
            break;
        case 3:
            printf("Which ID? ");
            scanf("%hd", &id);
            Del(id, &tmp);
            break;
        case 4:
            print_book(tmp);
            break;
        case 5:
            Print(tmp, 0);
            break;
        case 6:
            res = 6;
        default:
    }
    print_options();
    return tmp;
}
btree* menu_l2(btree* book, short* cur, char cmd) {
    btree* tmp = book;
    char res = 1;
    char cmd2;
    short val;
    char* string;
    short wrk;
    printf("Which ID? ");
    scanf("%hd", &wrk);
    print_types();
    // tmp = Find(wrk, tmp);
    tmp = Search(tmp, wrk);
    printf("%hd", tmp->val.id);
    if(wrk != -1 && scanf("%hhd", &cmd2)) {
        switch (cmd2) {
        case 1:
            if(cmd == 2) {
                printf("Choose field:\n1.First name\n2. Last name\n3. Middle name\n");
                scanf("%hhd", &cmd2);
                printf("New field: ");
                string = malloc(ENT_SIZE*sizeof(char));
                scanf("%s", string);
                res = edit_person(&(tmp->val.person), cmd2, string);
                free(string);
            }
            else if(cmd == 3)
                zero_person(&(tmp->val.person));
            break;
        case 2:
            printf("%hd", wrk);
            if(cmd == 2) {
                printf("Choose field:\n1. City\n2. Street\n3. Home number\n4. Apt number\n");
                scanf("%hhd", &cmd2);
                printf("New field: ");
                if(cmd2 == 1 || cmd2 == 2) {
                    string = malloc(ADR_SIZE*sizeof(char));
                    scanf("%s", string);
                    res = add_address_char(&(tmp->val.adress), cmd2, string);
                    free(string);
                }
                else if(cmd2 == 3 || cmd2 == 4) {
                    scanf("%hd", &val);
                    res = add_address_short(&(tmp->val.adress), cmd2, val);
                }
            }
            else if(cmd == 3)
                zero_address(&(tmp->val.adress));
            break;
        case 3:
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
                    res = add_job_char(&(tmp->val.job), cmd2, string);
                    free(string);
                }
                else if(cmd2 == 4 || cmd2 == 5 || cmd2 == 6) {
                    scanf("%hd", &val);
                    res = add_job_short(&(tmp->val.job), cmd2, val);
                }
            }
            else if(cmd == 3)
                zero_job(&(tmp->val.job));
            break;
        case 4:
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
                    res = add_contacts(&(tmp->val.contacts), cmd2, string);
                    free(string);
                }
            }
            else if(cmd == 3)
                zero_contacts(&(tmp->val.contacts));
            break;
        case 5:
        default:
        }
    }
    return tmp;
}
void print_options() {
    printf("\nMENU: \n");
    printf("1. Initiate entry\n");
    printf("2. Edit entry\n");
    printf("3. Delete entry\n");
    printf("4. View phonebook\n");
    printf("5. List IDs(tree style)\n");
    printf("6. Exit\n");
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

int is_empty(char* string) {
    return (string[0] == '0') ? 1: 0;
}

void print_book(btree* head) {
    btree* tmp = head;
    if(tmp == NULL) {
        printf("Phonebook empty!\n");
        return;
    }
    printf("%-5s|%-20s|%-20s|%-20s|%-20s|%-20s|\n", "ID", "First name", "Last name", "Address", "Job", "Contacts");
    for(int i =0; i < 5; i++) printf("-");
    printf("|");
    for(int i =0; i < 20; i++) printf("-");
    printf("|");
    for(int i =0; i < 20; i++) printf("-");
    printf("|");
    for(int i =0; i < 20; i++) printf("-");
    printf("|");
    for(int i =0; i < 20; i++) printf("-");
    printf("|");
    for(int i =0; i < 20; i++) printf("-");
    printf("|");
    printf("\n");
    print_list(head);
    // while(tmp != NULL) {
    //     printf("%-5d|%-20s|%-20s|", tmp->val.id, tmp->val.person.firstname, tmp->val.person.lastname);
    //     printf("%-20s|", !is_empty(tmp->val.adress.city) ? tmp->val.adress.city : "0");
    //     printf("%-20s|", !is_empty(tmp->val.job.position) ? tmp->val.job.position : "0");
    //     printf("%-20s|", !is_empty(tmp->val.contacts.email) ? tmp->val.contacts.email : "0");
    //     printf("\n");
    //     tmp = tmp->next;
    // }
    
}
void print_list(btree* tmp) {
    if(tmp == NULL) return;
    print_list(tmp->left);
    print_list(tmp->right);
    printf("%-5d|%-20s|%-20s|", tmp->val.id, tmp->val.person.firstname, tmp->val.person.lastname);
    printf("%-20s|", !is_empty(tmp->val.adress.city) ? tmp->val.adress.city : "0");
    printf("%-20s|", !is_empty(tmp->val.job.position) ? tmp->val.job.position : "0");
    printf("%-20s|", !is_empty(tmp->val.contacts.email) ? tmp->val.contacts.email : "0");
    printf("\n");
}