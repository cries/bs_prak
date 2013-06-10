#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/types.h>

#define NUM_OF_CHILDS 3
#define SEG_SIZE sizeof(int)

void main() {
  int i, pid, count, id1, id2, *shar_mem1, *shar_mem2;
  int arr_pid[NUM_OF_CHILDS];
  
  id1 = shmget(IPC_PRIVATE, SEG_SIZE, IPC_CREAT|0600);
  shar_mem1 = (int *)shmat(id1, 0, 0);
  *shar_mem1 = 20;
  
  id2 = shmget(IPC_PRIVATE, SEG_SIZE, IPC_CREAT|0600);
  shar_mem2 = (int *)shmat(id2, 0, 0);
  *shar_mem2 = 1;
  
  count = 0;
  
  
  for (i = 0; i < NUM_OF_CHILDS; i++){
    pid = fork();
    if (pid == -1){
      printf("Kindprozess konnte nicht erzeugt werden!\n");
      exit(1);
    }
    if (pid==0){
      printf("Kind-ID: %d\n", getpid());
      while(1==1){
        if (*shar_mem1 > 0){
          usleep(100000);
          *shar_mem1 = *shar_mem1 - 1;
        } else {
          usleep(100000);
        }

        if (*shar_mem2 == 0) {
          printf("Kennung ist 0\n");
          exit(0);
        }
      }      
    } else if (pid > 0){
      arr_pid[i] = pid;
    }  
  }
  
    while(count<60){
        usleep(100000);
        printf("Lagerbestand: %02d - %02d\n", *shar_mem1, count);
        if (*shar_mem1 <= 0) {
          *shar_mem1 = 20;
          printf("Lagerbestand aufgefuellt!\n");
        }
        count++;
  }
  
  *shar_mem2 = 0;
  
  for(i = 0; i < NUM_OF_CHILDS; i++){
    waitpid(arr_pid[i], NULL, 0);
  }
  
  printf("Vater-Prozess wird beendet! Shared-Memory wird freigegeben!\n");
  
  shmdt(shar_mem1);
  shmdt(shar_mem2);
  shmctl(id1, IPC_RMID, 0);
  shmctl(id2, IPC_RMID, 0);
}
