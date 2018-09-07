/*----------------------------------------------------------------

*

* Programación avanzada: Archivos y directorios

* Fecha: 30-Ago-2018

* Autor(es): A01206423 David Ramirez

*

*--------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

void get_info(char* name, char* path, char* file){
  struct stat info;
  char time[50];

  stat(file, &info);

  printf("--------------------------------------------------------\n");
  printf("Name: %s\n\n", name);
  printf("Path: %s\n\n", path);
  strftime(time, 50, "%a %b %d %H:%M:%S %Y", localtime(&info.st_atime));
  printf("Last Access: %s\n\n", time);
  strftime(time, 50, "%a %b %d %H:%M:%S %Y", localtime(&info.st_mtime));
  printf("Last Modification: %s\n", time);
}

void list(char* name, char* dir, int r, char* program){
  DIR* dir_pointer;
  dir_pointer = opendir(dir);

  if(dir_pointer == NULL){
    perror(program);
    exit(-1);
  }

  struct dirent* dir_entry;

  char filename[PATH_MAX + NAME_MAX + 1];

  while ((dir_entry = readdir(dir_pointer)) != NULL){
    if(strcmp(dir_entry->d_name, ".") != 0 && strcmp(dir_entry->d_name, "..") != 0){
      if(r == 0){
        if(strstr(dir_entry->d_name, name)){
          sprintf(filename, "%s/%s", dir, dir_entry->d_name);
          get_info(dir_entry->d_name, dir, filename);
        }
      }else{
        if(dir_entry->d_type == DT_DIR){
          char path[528];
          snprintf(path, sizeof(path), "%s/%s", dir, dir_entry->d_name);
          if(strstr(dir_entry->d_name, name)){
            get_info(dir_entry->d_name, dir, path);
          }
          list(name, path, r, program);
        }else{
          if(strstr(dir_entry->d_name, name)){
            sprintf(filename, "%s/%s", dir, dir_entry->d_name);
            get_info(dir_entry->d_name, dir, filename);
          }
        }
      }
    }
  }
}

int main(int argc, char* argv[]){
  char dir_name[NAME_MAX + 1];
  char *dir;
  int r = 0;

  if(argc<3 || argc>4){
    printf("usage: %s str directory [-r]\n", argv[0]);
    return -1;
  }

  if(argc == 4){
    if(strcmp(argv[3], "-r") == 0){
      r = 1;
    }else{
      printf("usage: %s str directory [-r]\n", argv[0]);
      return -1;
    }
  }

  getcwd(dir_name, NAME_MAX);

	dir = dir_name;
  dir = argv[2];

  list(argv[1], dir, r, argv[0]);
  return 0;
}
