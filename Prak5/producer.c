#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSGSIZE 150

// Struktur zum Übertragen der Daten an die Message-Queue
struct message {
  long dienst;
  char text[MSGSIZE];
};

int main(int argc, char* argv[]) {
  
  int msg_id;
  struct message msg;
  // Beginn bei 1 (Dienste 1-3)
  char* dienste[] = {"", "Terminalausgabe", "Dateianhang", "Emailversand"};
  
  // Parameter Anzahl falsch
  if (argc != 4) {
    printf("Usage: %s <queueid> <dienst> <nachricht>\n", argv[0]);
    return 1;
  }

  // Dienst wurde nicht gefunden
  if (atoi(argv[2]) < 1 || atoi(argv[2]) > 3) {
    printf("Fehler: Dienst nicht vorhanden!\nVefuegbare Dienste:\n");
    // Liste der Dienste ausgeben
    for (int i=1; i<4; i++) {
      printf("%i - %s\n", i, dienste[i]);
    }
    return 3;
  }
  
  // Message-Queue anlegen mit id aus Parameter argv[1]
  msg_id = msgget((key_t)atoi(argv[1]), IPC_CREAT | 0600);
  // Fehler beim erstellen der Msg-Queue
  if (msg_id == -1) {
    printf("Nachrichtenwarteschlange mit dem Schlüssel '%s' konnte nicht angelegt werden\n");
    return 2;
  }
  
  // Dienst festlegen
  msg.dienst = atoi(argv[2]);
  // n*(MSGSIZE-1)-Chars aus Parameter argv[3] kopieren
  strncpy(msg.text, argv[3], MSGSIZE-1);
  // Message-Text mit \0-Steuerzeichen abschließen
  msg.text[MSGSIZE-1] = '\0';
  
  // Message an die Queue senden (id, pointer, length, flag)
  if(msgsnd(msg_id, &msg, MSGSIZE, IPC_NOWAIT) < 0) {
    printf("Fehler: Die Nachricht konnte nicht gesendet werden!\n");
    return 4;
  }

  printf("Die Nachricht '%s' wurde an die Nachrichtwarteschlange gesendet!\n", msg.text);
  
  return 0;
}

