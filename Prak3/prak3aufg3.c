#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main (int argc, char *argv[]){
  // pipe_connection[0] -> Lesen
  // pipe_connection[1] -> Schreiben
  int pipe_connection[2];
  
  // Anzahl Argumente überprüfen
  if ((argc < 3) || (argc > 3)){
    printf("Falsche Anzahl von Parametern!\n");
    printf("Aufruf %s <prog1> <prog2>\n", argv[0]);
    return EXIT_FAILURE;
  }
  
  // Pipe erzeugen
  if (pipe(pipe_connection) < 0){
    printf("Pipe konnte nicht erzeugt werden!\n");
    return EXIT_FAILURE;
  }
  
  // Kindprozess erzeugen
  if (fork() == 0){
    // mit dup2 wird der Filedeskriptor der Pipe 
    // mit dem Filedeskriptor der Standardausgabe verbunden
    dup2(pipe_connection[1],1);
    
    // Das Leseende muss geschlossen werden da dieser Prozess nicht liest
    close(pipe_connection[0]);
    
    // Das erste übergebene Kommando ausführen
    // Die StdAusgabe des Kommandos ist mit dem Eingang der Pipe verbunden
    execlp(argv[1],argv[1],NULL);
  } 
  // zweiten Kindprozess erzeugen
  else if (fork()==0){
    // Filedeskriptoren verbinden
    dup2(pipe_connection[0],0);
    // Schreibeende muss geschlossen werden
    close(pipe_connection[1]);
    // Das zweite Kommando ausführen (StdIn mit Ausgang der Pipe verbunden)
    execlp(argv[2],argv[2],NULL);
  }
  // Vater-Prozess
  else {
    // Pipe-Enden schließen  
    close(pipe_connection[0]);
    close(pipe_connection[1]);
    // Auf beide Kindprozesse warten
    wait(0);
    wait(0);
  }
}
