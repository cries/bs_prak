#include <stdio.h>
#include <string.h>

int main (int argc, char *argv[]){
  int i,j;
  
  printf("%i Argumente gefunden.", argc);
  printf("\n");
  for (i = 0; i < argc; i++){
    printf("Argument %i: %d (%p)\n", i, &(argv[i]), &(argv[i])); 
    printf("--------------------------------\n");
    for (j = 0; j < strlen(argv[i]); j++){
      printf("\t Zeichen  %i: %d (%p)- %c\n", j, &(argv[i][j]), &(argv[i][j]), argv[i][j]);
    }
    printf("\n");
  }
  return(0);
}
