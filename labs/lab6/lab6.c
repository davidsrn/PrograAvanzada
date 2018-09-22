#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <limits.h>
#include <signal.h>

int i = 0, flag = 0, num;

void handler(int signal) {
    switch(signal) {
        case SIGUSR1 :
          if(flag == 0){
            printf("%s\n", "SIGUSR1 - SIGUSR2 is now ignored");
            flag = 1;
            break;
          }else{
            printf("%s\n", "SIGUSR1 - SIGUSR2 is now accepted");
            flag = 0;
            break;
          }
        case SIGUSR2 :
          if(flag != 1){
            printf("SIGUSR2 - cont = %i - n = %i\n", i++, num);
          }
    }
}

int main(int argc, char* argv[]) {
  if(argc>1){
    num = atoi(argv[1]);
  }else{
    num = 10;
  }
  signal(SIGUSR2, handler);
  signal(SIGUSR1, handler);
  while (i <= num){
    sleep(1);
  }
  printf("%s\n", "Exiting...");
  return 0;
}
