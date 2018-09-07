#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char *argv[]) {
  FILE *file;
  int aux, total, num, i;

  if(argc != 2) {
    fprintf(stderr, "Usage: %s filename \n", argv[0]);
    return -1;
  }

  file=fopen(argv[1], "r");
  if(!file){
    perror(argv[1]);
    return -1;
  }

  int maximum = 0;
  while(fscanf(file, "%i,%i", &aux, &total)!=EOF){
    fprintf(stdout, "aux = %i - total = %i\n", aux, total);
    total *= total;
    for(i=0;i<total;i++){
      fscanf(file, ",%i,", &num);
      if(maximum < num){
        maximum = num;
      }
    }
  }

  fprintf(stdout, "val = %i\n", num);

  fclose(file);

  return 0;
}
