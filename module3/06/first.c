#include "head.h"


int main(int argc, char *argv[]) {
    key_t chat_key;
    int queue_id, sem_id, msg_status;
    chat_key = ftok("chat", 'C');
    CHECK(chat_key, perror, "key", -1);
    queue_id = msgget(chat_key, 0666|IPC_CREAT);
    CHECK(queue_id,perror, "queue init", -1);
    
    struct msgbuf msg;
    while(1) {
        printf("Type: ");
        fgets(msg.msgtext, MSG_MAX, stdin);
        CHECK(msg.msgtext, printf, "fgets", NULL);
        msg.msgtext[strlen(msg.msgtext)-1] = '\0';
        msg.msgtype = 1;
        (strncmp(msg.msgtext, "q", strlen(msg.msgtext)) == 0) ? msg.msgtype = 255 : 0;
        msg_status = msgsnd(queue_id, &msg, sizeof(msg.msgtext), 0);
        CHECK(msg_status, perror, "msgsnd", -1);
        if(msg.msgtype == 255) {
            msg_status = msgctl(queue_id, IPC_RMID, NULL);
            CHECK(msg_status, perror, "msgctl", -1);
            break;
        }
        msg_status = msgrcv(queue_id, &msg, sizeof(msg.msgtext), 0, 0);
        CHECK(msg_status, perror, "msgrcv", -1);
        if(msg.msgtype == 255) break;
        printf("Recieved Message: %s\n", msg.msgtext);
    }
    exit(0);
}
