
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  int error = 0;
  printf("Prozess-ID: %2d", getpid());
  error = execlp("ps","ps-Test","-fu",getenv("USER"),NULL);
  if(error<0)
    printf("Error!!!!!!!!!!");
}
