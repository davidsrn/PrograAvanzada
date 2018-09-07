#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>

//MINMAX
void min_max(char *filename, char *program){
    struct stat info;
    //Checa que el archivo no este vacio:
    if(lstat(filename,&info)<0){
      perror(program);
      exit(-1);
    }

    //ABRE EL ARCHIVO EN MODO LECTURA:
    int fd;
    if((fd=open(filename, O_RDONLY))<0){
			perror(program);
			exit(-1);
		}

    int numero, min, max;
    min=INT_MIN;
    max=INT_MAX;

    //MIENTRAS LEAS TOODO EL ARCHIVO
    while(read(fd,&numero,sizeof(int))!=0){
        if(numero<min){
          min=numero;
        }
        if(numero>max){
          max=numero;
        }
    }

    printf("filename = %s - min = %i - max = %i\n", filename, min, max);
    close(fd);
}


//LIST
void list(char *directory, char *program){
  DIR* dir;
  struct dirent* direntry;
  struct stat info;
  char filename[PATH_MAX + NAME_MAX + 1];

  //ABRIR EL DIRECTORIO(MARCAR ERROR SI NO):
  if((dir = opendir(directory)) == NULL){
		perror(program);
		exit(-1);
	}

  while((direntry = readdir(dir)) != NULL){
    if(strcmp(direntry->d_name, ".") != 0 && strcmp(direntry->d_name, "..") != 0){
      sprintf(filename,"%s/%s",directory,direntry->d_name);
      lstat(filename, &info);
      if(S_ISDIR(info.st_mode)){
          list(filename,program);
      }else{
        min_max(filename, program);
      }
    }
  }
  printf("\n");
}

//MAIN
int main(int argc, char *argv[]){
  if(argc!=2){
    printf("Usage: %s [directory]\n", argv[0]);
    return -1;
  }
  char *directory;
  directory = argv[1];
  list(directory, argv[0]);
  return 0;
}
