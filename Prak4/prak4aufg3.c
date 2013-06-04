#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/sem.h>

#define NUM_OF_CHILDS 3
#define SEGSIZE sizeof(int)

void main() {
  int i, count, semid, id1, id2, *shar_mem1, *shar_mem2;
  int pid[NUM_OF_CHILDS];
  struct sembuf semaphore_lock[1] = { 0, -1, SEM_UNDO };
  struct sembuf semaphore_unlock[1] = { 0, 1, SEM_UNDO };
  
  semid = semget(IPC_PRIVATE, 1, IPC_CREAT|0600);
  semctl(semid, 0, SETALL, (int) 1);
  id1 = shmget(IPC_PRIVATE, SEGSIZE, IPC_CREAT|0600);
  shar_mem1 = (int *)shmat(id1, 0, 0);
  *shar_mem1 = 20;
  
  id2 = shmget(IPC_PRIVATE, SEGSIZE, IPC_CREAT|0600);
  shar_mem2 = (int *)shmat(id2, 0, 0);
  *shar_mem2 = 1;
  
  
  count = 0;
  
  
  for (i = 0; i < NUM_OF_CHILDS; i++){
    pid[i] = fork();
    if (pid[i] == -1){
      printf("Kindprozess konnte nicht erzeugt werden!\n");
      exit(1);
    }
    if (pid[i]==0){
      printf("Kind-ID: %d\n", getpid());
      while(1==1){
        if (*shar_mem2 == 0) {
          printf("Kennung ist 0\n");
          exit(0);
        }
        if(*shar_mem1 > 0) {
          semop(semid, &(semaphore_lock[0]), 1);
          usleep(100000);
          *shar_mem1 = *shar_mem1 - 1;
          semop(semid, &semaphore_unlock[0], 1);
        } else {
          usleep(100000);
        }
      }      
    }  
  }
  
    while(count<60){
        usleep(100000);
        if (*shar_mem1 <= 0) {
          *shar_mem1 = 20;
          printf("Lagerbestand aufgefuellt!\n");
        }
        printf("Lagerbestand: %02d - %02d\n", *shar_mem1, count);
        count++;
  }
  
  *shar_mem2 = 0;
  
  for(i = 0; i < NUM_OF_CHILDS; i++){
    waitpid(pid[i], NULL, 0);
  }
  
  printf("Vater-Prozess wird beendet! Shared-Memory wird freigegeben!\n");
  
  semctl(semid, 0, IPC_RMID, 0);
  shmdt(shar_mem1);
  shmdt(shar_mem2);
  shmctl(id1, IPC_RMID, 0);
  shmctl(id2, IPC_RMID, 0);
}
