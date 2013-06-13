#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

#define MSGSIZE 150

struct message {
  long dienst;
  char text[MSGSIZE];
};

int main(int argc, char* argv[]) {
  
  int msg_id;
  struct message msg;
  struct msqid_ds buffer;
  char* dienste[] = {"", "Terminalausgabe", "Dateianhang", "Emailversand"};
  
  // Error Handling
  if (argc != 3) {
    printf("Usage: %s <warteschlange> <dienst>\n", argv[0]);
    return 1;
  }
  
  if (atoi(argv[1]) < 1 || atoi(argv[1] > 3)) {
    printf("Fehler: Unbekannter Dienst angegeben!\nVerfuegbare Dienste:\n");
    for (int i=1; i<4; i++){
      printf("%i - %s\n", dienste[i]);
    }
    return 2;
  }

  // Id der Message-Queue holen
  msg_id = msgget((key_t)atoi(argv[1]), 0);
  
  // Fehler
  if (msg_id == -1) {
    printf("Fehler: Auf die Nachrichtenwarteschlange mit dem Schlüssel '%s':\n", dienste[atoi(argv[2])]);
    return 3;
  }
  
  printf("Starte Verarbeitung aller Nachrichten fuer den Dienst '%s'\n", dienste[atoi(argv[2])]);
  
  // Datei-Pointer
  FILE *f;
  // Addressat der Mail
  char* TO = "mi968";
  char str[2*MSGSIZE];
  
  // Alle Messages mit dem angegebenen Dienst aus der Message-Queue holen
  while (msgrcv(msg_id, &msg, MSGSIZE, atoi(argv[2]), IPC_NOWAIT | MSG_NOERROR) != -1) {
    switch (atoi(argv[2])) {
      // Terminalausgabe
      case 1:
        printf("Eine Nachricht wird ausgegeben: %s\n", msg.text);
      break;
      // Dateianhang
      case 2:
        // Öffne Datei-Stream (a = append)
        f = fopen("queue_datei", "a");
        fprintf(f, "%s\n", msg.text);
        // Stream flushen
        fflush(f);
        // Datei-Stream schließen
        fclose(f);
        printf("Die Nachricht '%s' wurde in die Datei 'queue_datei' geschrieben.\n", msg.text);  
      break;
      // Emailversand
      case 3:
        sprintf(str, "echo %s | mail -s 'Nachricht aus der Warteschlange' %s@gm.fh-koeln.de", msg.text, TO);
        printf("Kommando wird ausgefuehrt: %s\n", str);
        system(str);
        printf("Die Nachricht '%s' wurde per Email an '%s@gm.fh-koeln.de' gesendet.\n", msg.text, TO);        
      break;
    }
  }
  if (errno == ENOMSG) {
    printf("Meldung: Keine Nachrichten (mehr) fuer den Dienst\n");
  } else {
    printf("Fehler: Nachricht konnte nicht gelesen werden!\n");
    return 4;
  } 
  
  if (msgctl(msg_id, IPC_STAT, &buffer) == 0) {
    if (buffer.msg_qnum <= 0) {
      if (msgctl(msg_id, IPC_RMID, &buffer) == 0) {
        printf("Meldung: Leere Warteschlange wurde geloescht.\n");
      }
    }
  }
  return 0;
}

