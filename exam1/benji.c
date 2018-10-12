#include "header.h"

int main(int argc, char *argv[]) {
  int semid;
  key_t key;

  if( (key = ftok("/dev/null", 65)) == (key_t) - 1){
    perror(argv[0]);
    return -1;
  }
  if( (semid = semget(key, 4, 0666 | IPC_CREAT)) < 0 ){
    perror(argv[0]);
    return -1;
  }
  semctl(semid, BENJI, SETVAL, 0);
  semctl(semid, MUTEX  , SETVAL, 1);
  semctl(semid, BILLETE20  , SETVAL, 0);
  semctl(semid, BILLETE50, SETVAL, 0);
  semctl(semid, BILLETE100  , SETVAL, 0);
  return 0;
}
