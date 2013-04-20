/*
  File: prak2aufg1.c
  Author: Christian Ries | mi968
  Date: 18.04.2013 
*/

#include <stdio.h>
#include <string.h>
  
// argc enthält Anzahl Argumente, *argv[] ist ein Pointer auf die Argumente
int main (int argc, char *argv[]){
  int i,j;
  // Anzahl Argumente ausgeben
  printf("%i Argumente gefunden.", argc);
  printf("\n");
  // Für alle Argumente
  for (i = 0; i < argc; i++){
    // Argument Nr, Start Adresse in Dezimal & Hexadezimal ausgeben
    printf("Argument %i: %d (%p)\n", i, &(argv[i]), &(argv[i])); 
    printf("--------------------------------\n");
    // Für jedes Character des Argumentes
    for (j = 0; j < strlen(argv[i]); j++){
      // Adresse des Zeichen in Dez & Hex ausgeben
      printf("\t Zeichen  %i: %d (%p)- %c\n", j, &(argv[i][j]), &(argv[i][j]), argv[i][j]);
    }
    printf("\n");
  }
  return(0);
}
