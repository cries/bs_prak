#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void request(char* service){
  
  int parent_pipe[2];
  int child_pipe[2];
  char buff[50];
  char message[50];
  
  if ((pipe(parent_pipe) < 0) || (pipe(child_pipe) < 0)){
    printf("Pipe konnte nicht erzeugt werden!\n");
    exit(EXIT_FAILURE);
  }
  
  int pid = fork();
  
  if (pid == -1){
    printf("Prozess konnte nicht erzeugt werden!\n");
    exit(EXIT_FAILURE);
  }
  
  if (pid > 0){
    int in, out;
    
    in = parent_pipe[0];
    out = child_pipe[1];
    
    write(out, service, strlen(service) + 1);
    read(in, buff, 50);
    printf("Ergebnis: %s\n", buff);
  }
  
  if (pid == 0){
    int in, out;
    int max = 50;
    in = child_pipe[0];
    out = parent_pipe[1];
    read(in, buff, 50);
    printf("Dienst: %s\n", buff);
    
    char *day[] = {"Sonntag", "Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag"};
    struct tm *datum;
    time_t heute;
    
    time(&heute);
    datum = localtime(&heute);
    
    if (strcmp(buff, "day") == 0){
      sprintf(buff, "%02d.%02d.%4d", datum->tm_mday, datum->tm_mon+1, datum->tm_year+1900);
      write(out, buff, max);
    }
    if (strcmp(buff, "time") == 0){
      sprintf(buff, "%02d:%02d:%2d", datum->tm_hour, datum->tm_min, datum->tm_sec);
      write(out, buff, max);
    }
    if (strcmp(buff, "wday") == 0){
      sprintf(buff, "%s", day[datum->tm_wday]);
      write(out, buff, max);
    } else {
      char* err_msg = "Falscher Dienst!";
      write(out, err_msg, strlen(err_msg)+1);
    }
  }
}

int main(int argc, char *argv[]){
  if (argc!=2){
    printf("Falsche Anzahl an Diensten!\n");
    return EXIT_FAILURE;
  }
  
  request(argv[1]);
  
  return EXIT_SUCCESS;
}
