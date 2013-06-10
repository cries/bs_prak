#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/sem.h>

#define NUM_OF_CHILDS 3
#define SEG_SIZE sizeof(int)

void main() {
  int i, pid, count, semid, id1, id2, *shar_mem1, *shar_mem2;
  int arr_pid[NUM_OF_CHILDS];
  unsigned short marker[1];
  struct sembuf semaphore_lock;
  struct sembuf semaphore_unlock;
  marker[0] = 1;
  
  semaphore_lock.sem_num = 0;
  semaphore_lock.sem_op = -1;
  semaphore_lock.sem_flg = SEM_UNDO;
  
  semaphore_unlock.sem_num = 0;
  semaphore_unlock.sem_op = 1;
  semaphore_unlock.sem_flg = SEM_UNDO;
  
  semid = semget(IPC_PRIVATE, 1, IPC_CREAT|0600);
  semctl(semid, 0, SETALL, marker);
  
  id1 = shmget(IPC_PRIVATE, SEG_SIZE, IPC_CREAT|0600);
  shar_mem1 = (int *)shmat(id1, 0, 0);
  *shar_mem1 = 20;
  
  id2 = shmget(IPC_PRIVATE, SEG_SIZE, IPC_CREAT|0600);
  shar_mem2 = (int *)shmat(id2, 0, 0);
  *shar_mem2 = 1;
  
  
  count = 0;
  
  // Erzeuge NUM_OF_CHILDS-Anzahl Kinder
  for (i = 0; i < NUM_OF_CHILDS; i++){
    // Kind erzeugen
    pid = fork();
    // Kind konnte nicht erzeugt werden
    if (pid == -1){
      printf("Kindprozess konnte nicht erzeugt werden!\n");
      exit(1);
    }
    // Im Kind-Prozess
    if (pid==0){
      printf("Kind (%d) erzeugt!\n", getpid());
      // Endlosschleife
      while(1){
        // Kritischen Bereich sperren
        semop(semid, &semaphore_lock, 1);
        // Lagerbestand > 0
        if(*shar_mem1 > 0) {
          usleep(100000);
          // Lagerbestand um 1 dekrementieren
          *shar_mem1 = *shar_mem1 - 1;
        } else {
          usleep(100000);
        }
        // Kritischen Bereich entsperren
        semop(semid, &semaphore_unlock, 1); 
        
        // Kind-Prozess beenden wenn Killsignal gesetzt
        if (*shar_mem2 == 0) {
          printf("Killsignal erhalten! Kind (%d) beendet.\n", getpid());
          exit(0);
        }
      }      
    } // Vaterprozess sammelt die Kind-PID's
      else if (pid > 0){
      arr_pid[i] = pid;  
    }  
  }
    // Vater-Prozess wiederholt 60 mal 
    while(count<60){
        usleep(100000);
        printf("Lagerbestand: %02d\n", *shar_mem1);
        // semop(semid, &semaphore_lock, 1);
        // Lagerbestand prüfen 
        if (*shar_mem1 <= 0) {
          // Frisch auffüllen
          *shar_mem1 = 20;
          printf("Lagerbestand aufgefuellt!\n"); 
        }
        // semop(semid, &semaphore_unlock, 1);
        count++;
    }
  
  // Killsignal setzen
  *shar_mem2 = 0;
  
  // Auf Kind-Prozesse warten
  for(i = 0; i < NUM_OF_CHILDS; i++){
    waitpid(arr_pid[i], NULL, 0);
  }
  
  printf("Vater-Prozess wird beendet! Shared-Memory wird freigegeben!\n");
  
  // Shared Memory vom Speicherbereich lösen
  shmdt(shar_mem1);
  shmdt(shar_mem2);
  // Shared Memory wieder freigeben (löschen)
  shmctl(id1, IPC_RMID, 0);
  shmctl(id2, IPC_RMID, 0);
  // Semaphore löschen
  semctl(semid, 0, IPC_RMID, 0);
}
