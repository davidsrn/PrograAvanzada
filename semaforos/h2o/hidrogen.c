#include "header.h"

void a_hidrogen(char* program) {
	int semid, flag = 1;
	key_t key;

	if ( (key = ftok("/dev/null", 65)) == (key_t) -1 ) {
		perror(program);
		exit(-1);
	}

	if ( (semid = semget(key, 4, 0666))  < 0 ) {
		perror(program);
		exit(-1);
	}
	printf("Hidrogen %i trying to enter the barrier.\n", getpid());
	mutex_wait(semid, MUTEX);
	printf("Hidrogen %i trying to get in the barrier iwth %i space(s)\n", getpid(), semctl(semid, BARRIER, GETVAL, 0));
  sem_wait(semid, BARRIER, 1);

  if (semctl(semid, HIDROGEN, GETVAL, 0) == 2) {
    printf("Too many hidrogen molecules, more hidrogen not allowed.\n");
		// flag = 0;
    sem_signal(semid, BARRIER, 1);
  }
  else{
    sem_signal(semid, HIDROGEN, 1);
  	printf("Hidrogen %i entered the barrier.\n", getpid());
    printf("%i hidrogen molecule(s) in barrier, %i oxygen molecules in barrier\n", semctl(semid, HIDROGEN, GETVAL, 0), semctl(semid, OXYGEN, GETVAL, 0));
  }
	if(semctl(semid, BARRIER, GETVAL, 0) == 0) {
    sem_signal(semid, BARRIER, 3);
    printf("Water molecule created with  %i oxygen molecule and %i hidrogen molecules \n\n", semctl(semid, OXYGEN, GETVAL, 0), semctl(semid, HIDROGEN, GETVAL, 0));
		// sleep(3);
    // semctl(semid, OXYGEN, SETVAL, 0);
    // semctl(semid, HIDROGEN, SETVAL, 0);
		flag = 0;
  }
	sleep(3);
	mutex_signal(semid, MUTEX);


	exit(0);
}

int main(int argc, char* argv[]) {
	int amount = 0, i, pid;

	if (argc != 2) {
		printf("usage: %s amount\n", argv[0]);
		return -1;
	}

	amount = atoi(argv[1]);
	if (amount < 1) {
		printf("%s: The amount must be a positive number greater than zero.\n", argv[0]);
		return -1;
	}

	for (i = 0; i < amount; i++) {
		if ( (pid = fork()) < 0 ) {
			perror("fork");
			return -1;
		} else if (pid == 0) {
			a_hidrogen(argv[0]);
		} else {
		}
	}
	return 0;
}
