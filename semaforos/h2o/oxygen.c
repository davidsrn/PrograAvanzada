#include "header.h"

void a_oxygen(char* program) {
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

  printf("Oxygen %i trying to enter the barrier.\n", getpid());
	mutex_wait(semid, MUTEX);
	printf("Oxygen %i trying to get in the barrier with %i space(s)\n", getpid(), semctl(semid, BARRIER, GETVAL, 0));
  sem_wait(semid, BARRIER, 1);

  if (semctl(semid, OXYGEN, GETVAL, 0) == 1) {
    printf("Too many oxygen molecules, more oxygen not allowed.\n");
		// flag = 0;
    sem_signal(semid, BARRIER, 1);
  }
  else{
    sem_signal(semid, OXYGEN, 1);
  	printf("Oxygen %i entered the barrier.\n", getpid());
    printf("%i oxygen molecule(s) in barrier, %i hidrogen molecules in barrier\n", semctl(semid, OXYGEN, GETVAL, 0), semctl(semid, HIDROGEN, GETVAL, 0));
  }
  if(semctl(semid, BARRIER, GETVAL, 0) == 0) {
    sem_signal(semid, BARRIER, 3);
    printf("Water molecule created with  %i oxygen molecule and %i hidrogen molecules \n\n", semctl(semid, OXYGEN, GETVAL, 0), semctl(semid, HIDROGEN, GETVAL, 0));
		// sleep(3);
    semctl(semid, OXYGEN, SETVAL, 0);
    semctl(semid, HIDROGEN, SETVAL, 0);
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
			a_oxygen(argv[0]);
		} else {
		}
	}
	return 0;
}
