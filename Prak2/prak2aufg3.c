#include <stdio.h>
#include <unistd.h>
int main() {
  int i, pid, n = 3;
  for(i=0; i<n; i++) {
    pid = fork();
    if(pid == 0) {
      printf("Kind %2d: %d von %d\n", i, getpid(), getppid());
      break;
    } else {
      printf("Vater %2d: %d von %d\n", i, getpid(), getppid());
    }
  }
  return 0;
}
