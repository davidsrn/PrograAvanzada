/*
  EXAMEN 2 POR DAVID A01206423
*/

#include "header.h"

int main(int argc, char *argv[]){
  int semid, shmid, i;
  key_t key;
  struct buffer *b;

  if((key=ftok("/dev/null", 65))==(key_t) -1){
	perror(argv[0]);
	return -1;
  }

  if((semid=semget(key, 5, 0666))  < 0){
  	perror(argv[0]);
  	return -1;
  }

  if((shmid=shmget(key, sizeof(struct buffer), 0666)) < 0){
  	perror("shmid");
  	return -1;
  }

  b=(struct buffer *) shmat(shmid,(void *) 0, 0);

  // if ( (pid = fork()) < 0 ) {
  //   perror("fork");
  //   return -1;
  // }

  srand( getpid());

  while(1){
  	i=rand() % 3;
    if(i==0){
      printf("Benji ha llegado al mostrador\n");
      b->billete100=1;
      printf("Benji puso un billete de 20\n");
      sem_signal(semid, BILLETE20, 1);
      sem_wait(semid, BENJI, 1);
    } else if(i==1){
      printf("Benji ha llegado al mostrador\n");
      b->billete50=1;
      printf("Benji puso un billete de 100\n");
      sem_signal(semid, BILLETE100, 1);
      sem_wait(semid, BENJI, 1);
    } else if(i==2){
      printf("Benji ha llegado al mostrador\n");
      b->billete20=1;
      printf("Benji puso un billete de 50\n");
      sem_signal(semid, BILLETE50, 1);
      sem_wait(semid, BENJI, 1);
    }
  	printf("Benji agarró más billetes\n");
  	sleep(2);
  }
  return 0;
}
