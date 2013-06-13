#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct text_message {
  long mtype;
  char mtext[100];
};

void main(int argc, char *argv[]) {
  int msid, v;
  struct text_message mess;
  if (argc != 4) {
    printf(2, "usage: msgsnd <key> <type> <text>\n");
    exit(1);
  }
  /* Get the message queue, creating it if necessary */
  msid = msgget((key_t)atoi(argv[1]), IPC_CREAT|0666);
  
  if (msid == -1) {
    printf("Cannot get message queue\n");
    exit(1);
  }
  
  /* Assemble the message */
  mess.mtype = atoi(argv[2]);
  strcpy(mess.mtext, argv[3]);
  
  /* Write message onto the queue */
  v = msgsnd(msid, &mess, strlen(argv[3])+1,0);
  if (v<0)
    printf("error writing to queue\n");
}
