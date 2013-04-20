/*
  File: prak2aufg3.c
  Author: Christian Ries | mi968
  Date: 19.04.2013 
*/

#include <stdio.h>
#include <unistd.h>

int main() {
  int i, pid, n = 3;
  for(i=0; i<n; i++) {
    // Prozess erzeugen
    pid = fork();
    // pid == 0 wenn es ein Kindprozess ist
    if(pid == 0) {
      // Prozess-ID & Vater-Prozess-ID ausgeben
      printf("Kind %2d: %d von %d\n", i, getpid(), getppid());
      // Break ausführen wenn im Kindprozess
      // damit nicht noch weitere Prozesse vom Kindprozess erzeugt werden
      break;
    } else {
      // Prozess-ID & Vater-Prozess-ID ausgeben
      printf("Vater %2d: %d von %d\n", i, getpid(), getppid());
    }
  }
  return 0;
}
