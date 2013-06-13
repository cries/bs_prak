
#include <stdio.h>
#include <stdlib.h>
#include "time.h"

#define PIPE_READ 0
#define PIPE_WRITE 1
#define MAX 128

int main() {

      char buf[128];
      char *day[] = {"Sonntag", "Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag"};
      struct tm *datum;
      time_t heute;
    
      time(&heute);
      datum = localtime(&heute);

      /* Dienstanforderung überprüfen */

      if(strcmp(buf,"day") == 0)
         {
         sprintf(buf,"%02d.%02d.%4d",datum->tm_mday,datum->tm_mon+1,datum->tm_year+1900);
         write(answerPipefd[PIPE_WRITE], buf, MAX);
         exit(0);
         }
      if(strcmp(buf,"time") == 0)
         {
         sprintf(buf,"%02d:%02d:%02d",datum->tm_hour,datum->tm_min,datum->tm_sec);
         write(answerPipefd[PIPE_WRITE], buf, MAX);
         exit(0);
         }
      if(strcmp(buf,"wday") == 0)
         {
         sprintf(buf,"%s",day[datum->tm_wday]);
         write(answerPipefd[PIPE_WRITE], buf, MAX);
         exit(0);
         }
      else
         {
         write(answerPipefd[PIPE_WRITE], err_msg, strlen(err_msg)+1);
         }
 }
