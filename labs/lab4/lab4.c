/*----------------------------------------------------------------

 *

 * Programación avanzada: Normalización de un archivo

 * Fecha: 30-Ago-2018

 * Autor(es): A01206423 David Ramirez

 *

 *--------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <limits.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

#define SIZE  1000
#define WIDTH   68

float nums[SIZE];

int main(int argc, char *argv[]) {
  if(argc != 3) {
    printf("Usage: %s [input_directory] [output_directory]\n", argv[0]);
    return -1;
  }
  DIR* dir;
  DIR* dir2;
  struct dirent* direntry;
  char filename[PATH_MAX + NAME_MAX + 1];
  char out_filename[PATH_MAX + NAME_MAX + 1];
  FILE *fd_in;
  FILE *fd_out;
  int time, inter, size, i;
  float num;
  int min, max;
  min=INT_MAX;
  max=INT_MIN;


  if((dir = opendir(argv[1])) == NULL || (dir2 = opendir(argv[2])) == NULL ) {
    perror(argv[0]);
    return -1;
  }

  fd_out = fopen(argv[2], "w");

  while ((direntry = readdir(dir)) != NULL) {
    if(strcmp(direntry->d_name, ".") != 0 && strcmp(direntry->d_name, "..") != 0) {
      if(direntry->d_type != DT_DIR) {
        // printf("%s\n", direntry->d_name);
        sprintf(filename, "%s/%s", argv[1], direntry->d_name);
        sprintf(out_filename, "%s/%s", argv[2], direntry->d_name);
        // printf("%s\n", out_filename);
        fd_in = fopen(filename, "r");
        // char outputfile = strcat(argv[2], filename);
        if (fd_in == NULL) {
          perror(argv[0]);
          return -1;
        }
        memset(nums, 0, SIZE * sizeof(float));
        while(fscanf(fd_in, "%i,%i", &time, &inter) != EOF){
          size = inter * inter;
          for (i = 0; i < size; i++) {
            fscanf(fd_in, ",%f", &num);
            nums[i] = (float)num;
            if(nums[i] < min) {
              min = nums[i];
            }
            if(nums[i]> max) {
              max = nums[i];
            }
          }
        }
        fclose(fd_in);
        memset(nums, 0, SIZE * sizeof(float));
        fd_in = fopen(filename, "r");
        fd_out= fopen(out_filename, "w");
        // printf("Reading file %s\n", filename);
        // printf("Copying file %s to %s\n", filename, out_filename);
        // printf("MAX:%i MIN:%i\n", max, min);
        // fd_out = fopen(outputfile, "w");
        while ( fscanf(fd_in, "%i,%i", &time, &inter) != EOF ) {
          size = inter * inter;
          for (i = 0; i < size; i++) {
            // printf("%.2f\t", num);
            fscanf(fd_in, ",%f", &num);
            nums[i] = (float)num;
            nums[i] = (nums[i]-min)/(max-min);
            fprintf(fd_out, "%f,", nums[i]);
            // printf("%f", nums[i]);
          }
          fprintf(fd_out, "\n");

        }
        fclose(fd_in);
        fclose(fd_out);
        min=INT_MAX;
        max=INT_MIN;
      }
    }
  }
}
