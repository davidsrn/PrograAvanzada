/*
  EXAMEN 2 POR DAVID A01206423
*/

#include "header.h"

int main(int argc, char *argv[]){
  int semid, shmid;
  key_t key;
  struct buffer *b;

  if((key=ftok("/dev/null", 65))==(key_t) -1){
	  perror(argv[0]);
	  return -1;
	}

	if((semid=semget(key, 3, 0666))  < 0){
		perror(argv[0]);
		return -1;
	}

	if((shmid=shmget(key, sizeof(struct buffer), 0666)) < 0){
		perror("shmid");
		return -1;
	}
	b=(struct buffer *) shmat(shmid,(void *) 0, 0);

	int bandera=0;
	while(1){
    if(bandera==0){
      printf("Otaku con billetes de 20 quiere comprar y está esperando.\n");
      bandera=1;
    }
    sem_wait(semid, BILLETE100, 1);

    if(b->billete50){
      b->billete50=0;
      bandera=0;
      printf("Otaku con billetes de 20 compró los pockys\n");
      sleep(2);
      sem_signal(semid, BENJI, 1);
    }
	}
  return 0;
}
