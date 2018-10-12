/*
  EXAMEN 2 POR DAVID A01206423
*/

/*
	1.- Cigarrete Smokers
	En este caso benji es el agente que se va a encargar de poner dos billetes en el mostrador así que va a escocger dos al azar y los pondrpa en el mostrador.
	Después el otaku que tenga el bilete que falta lo tendrá que poner y el se queda con los pockys.
	Una vez que pase esto benji repetirá el proceso

	Benji empeiza escogiendo dos billetes y los demás esperan a ver si el billete que tienen ellos puede ser el que hace falta, en caso de
	que sí lo ponen y se lo quedan y vuelve a empezar. En caso de que no se quedan esperando a poner su billete.

	Ejecución:
	gcc main.c -o main && gcc benji.c -o benji && gcc billete20.c -o billete20 && gcc billete50.c -o billete50 && gcc billete100.c -o billete100

	En consolas separdas:

	./main
	./benji
	./billete20
	./billete50
	./billete100

*/
#ifndef SEMAFOROS_H
#define SEMAFOROS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

struct buffer{
	int billete100;
	int billete50;
	int billete20;
};


#define BILLETE100 	  0
#define BILLETE50    	1
#define BILLETE20   	2
#define BENJI         4

int sem_wait(int semid, int sem_num, int val){
	struct sembuf op;

	op.sem_num=sem_num;
	op.sem_op=-val;
	op.sem_flg=0;
	return semop(semid, &op, 1);
}

int sem_signal(int semid, int sem_num, int val){
	struct sembuf op;

	op.sem_num=sem_num;
	op.sem_op=val;
	op.sem_flg=0;
	return semop(semid, &op, 1);
}

int mutex_wait(int semid, int sem_num){
	return sem_wait(semid, sem_num, 1);
}

int mutex_signal(int semid, int sem_num){
	return sem_signal(semid, sem_num, 1);
}

#endif
