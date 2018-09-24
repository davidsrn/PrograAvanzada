/*----------------------------------------------------------------

*

* Programación avanzada: Problema del barbero.

* Fecha: 22-Sept-2018

* Autor: A01206423 davidsrn

*

*--------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <limits.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

#define SIZE  1000

float nums[SIZE];

int main(int argc, char *argv[]){

  if(argc !=5){
    printf("Usage: %s [working_directory] [log_filename] [number_of_files] [timeout]\n", argv[0]);
    return -1;
  }

  DIR* dir;

  if((dir=opendir(argv[1]))==NULL){
    perror(argv[0]);
    return -1;
  }

  char filename[PATH_MAX + NAME_MAX + 1];
  char newfilename[PATH_MAX + NAME_MAX + 1];
  char *extention="log", *name=argv[2];
  char str1[10], str2[10];

  int times = atoi(argv[3]), time=atoi(argv[4]), num;

  if(times <= 0 || time <= 0){
    printf("%s\n", "number_of_files and timeout should be greater than 0");
    return -1;
  }

  sprintf(filename, "%s/%s.%s", argv[1], name, extention);
  FILE *fd;
  fd=fopen(filename, "r");

  if(fd==NULL){
    printf("%s\n", "Log file does not exist");
    return -1;
  }

  fclose(fd);
  for(int i = 0; i<=times; i++){
    for(int lim = i; lim > 0; lim--){
      num = lim;
      sprintf(str1, "%d", num);
      sprintf(str2, "%d", num+1);
      sprintf(filename, "%s/%s.%s", argv[1], name, str1);
      sprintf(newfilename, "%s/%s.%s", argv[1], name, str2);
      rename(filename, newfilename);
    }
    sprintf(filename, "%s/%s.%s", argv[1], name, extention);
    sprintf(newfilename, "%s/%s.%s", argv[1], name, "1");
    rename(filename, newfilename);
    fd = fopen(filename, "w");
    fclose(fd);

    if(i == times){
      sprintf(str1, "%d", times+1);
      sprintf(filename, "%s/%s.%s", argv[1], name, str1);
      remove(filename);
    }

    sleep(time);
  }
}
