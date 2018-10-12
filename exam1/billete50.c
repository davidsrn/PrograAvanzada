#include "header.h"

void a_hidrogen(char* program) {
	int semid;
	key_t key;

	if ( (key = ftok("/dev/null", 65)) == (key_t) -1 ) {
		perror(program);
		exit(-1);
	}

	if ( (semid = semget(key, 4, 0666))  < 0 ) {
		perror(program);
		exit(-1);
	}
	printf("Billete de 50  %i intentando dar su billete.\n", getpid());
	mutex_wait(semid, MUTEX);
	printf("Billete de 50 %i intentando dar el billete a benji quien ha dado %i\n", getpid(), semctl(semid, BENJI, GETVAL, 0));
  sem_wait(semid, BENJI, 1);

  if (semctl(semid, BILLETE50, GETVAL, 0) == 1) {
    printf("Ya hay un billeted de 50 en la mesa.\n");
		// flag = 0;
    sem_signal(semid, BENJI, 1);
  }
  else{
    sem_signal(semid, BILLETE50, 1);
  	printf("%i dio un billete de 50.\n", getpid());
  }
	if(semctl(semid, BENJI, GETVAL, 0) == 0) {
    sem_signal(semid, BENJI, 3);
    printf("Se han podido comprar una caja de pocky");
		// sleep(3);
    semctl(semid, BILLETE20, SETVAL, 0);
    semctl(semid, BILLETE50, SETVAL, 0);
    semctl(semid, BILLETE100, SETVAL, 0);

  }
	sleep(3);
	mutex_signal(semid, MUTEX);

	exit(0);
}

int main(int argc, char* argv[]) {

	if (argc != 1) {
		printf("usage: %s\n", argv[0]);
		return -1;
	}

	a_hidrogen(argv[0]);
	return 0;
}
