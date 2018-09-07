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

void info(char *filename, char *program){
  char permits[] = {'x', 'w', 'r'};
  char data[13];
  struct stat info;
  struct passwd *pw;
  struct group *gr;
  int i;
  time_t rawtime;
  struct tm* timeinfo;

  if(lstat(filename, &info)<0){
    perror(program);
    exit(-1);
  }

  switch(info.st_mode & S_IFMT){
    case S_IFDIR: printf("d\n", ); break;
    case S_IFLNK: printf("l\n", ); break;
    default: printf("-\n", ); break;
  }

}

void list(char *directory, char *program, int recursive){
  DIR* dir;
  struct dirent* direntry;
  char filename[NAME_MAX +1];
  struct stat info;

  if((dir = opendir(directory))==NULL){
    perror(program);
    exit(-1);
  }

  printf("DIRECTORY %s\n", directory);
  while((direntry = readdir(dir))!=NULL){
    if(strcmp(direntry->d_name, ".")!=0 &&
       strcmp(direntry->d_name, "..")!=0){
      printf("%s\n", direntry->d_name);
    }
  }
}

int main(int argc, char *argv[]) {

  char dir_name[NAME_MAX +1];
  char *directory;
  int recursive = 0;

  if(argc > 3){
    printf("Usage: %s [-r] [directory]\n", argv[0]);
    return -1;
  }

  getcwd(dir_name, NAME_MAX);
  directory = dir_name;

  if(argc == 2){
    if(strcmp(argv[1], "-r") == 0){
      recursive = 1;
    }else{
        directory = argv[1];
    }
  }else if(argc == 3){
    if(strcmp(argv[1], "-r") == 0){
      printf("Usage: %s [-r] [directory]\n", argv[0]);
      return -1;
    }
    recursive = 1;
    directory = argv[2];
  }

  list(directory, argv[0], recursive);

  return 0;
}
