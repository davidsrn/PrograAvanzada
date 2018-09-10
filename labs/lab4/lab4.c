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

float nums[SIZE];

int main(int argc, char *argv[]){
        if(argc !=3){
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
        int time, inter, i, line=0;
        float num;
        float min, max;
        min=INT_MAX;
        max=INT_MIN;
        float minarg[SIZE], maxarg[SIZE];


        if((dir=opendir(argv[1]))==NULL || (dir2=opendir(argv[2]))==NULL){
                perror(argv[0]);
                return -1;
        }

        fd_out=fopen(argv[2], "w");

        while ((direntry=readdir(dir)) !=NULL){
                if(strcmp(direntry->d_name, ".") !=0 && strcmp(direntry->d_name, "..") !=0){
                        if(direntry->d_type !=DT_DIR){
                                // printf("%s\n", direntry->d_name);
                                sprintf(filename, "%s/%s", argv[1], direntry->d_name);
                                sprintf(out_filename, "%s/%s", argv[2], direntry->d_name);
                                // printf("%s\n", out_filename);
                                fd_in=fopen(filename, "r");
                                // char outputfile=strcat(argv[2], filename);
                                if (fd_in==NULL){
                                        perror(argv[0]);
                                        return -1;
                                }
                                // printf("%s\n", filename);
                                memset(nums, 0, SIZE * sizeof(float));
                                line=0;
                                while(fscanf(fd_in, "%i,%i", &time, &inter) !=EOF){
                                        // while(fscanf(fd_in, "%i,%i", &time, &inter) !=EOF){
                                        line++;
                                        min=INT_MAX;
                                        max=INT_MIN;
                                        // printf("%i\n", line);
                                        for (i=0; i < 625; i++){
                                                fscanf(fd_in, ",%f", &num);
                                                nums[i]=(float)num;
                                                if(nums[i] < min){
                                                        min=nums[i];
                                                }
                                                if(nums[i]> max){
                                                        max=nums[i];
                                                }
                                                minarg[line]=min;
                                                maxarg[line]=max;
                                        }
                                        // printf("%s\n","working");
                                }
                                fclose(fd_in);
                                line=0;
                                memset(nums, 0, SIZE * sizeof(float));
                                fd_in=fopen(filename, "r");
                                fd_out=fopen(out_filename, "w");
                                // printf("Reading file %s\n", filename);
                                // printf("Copying file %s to %s\n", filename, out_filename);
                                // fd_out=fopen(outputfile, "w");
                                while (fscanf(fd_in, "%i,%i", &time, &inter) !=EOF){
                                        fprintf(fd_out, "%i,%i", time, inter);
                                        // printf("%s\n", "working");
                                        line++;
                                        for (i=0; i < 625; i++){
                                                // printf("MAX:%f MIN:%f\n", maxarg[line], minarg[line]);
                                                // printf("%.2f\t", num);
                                                fscanf(fd_in, ",%f", &num);
                                                nums[i]=(float)num;
                                                nums[i]=(nums[i]-minarg[line])/(maxarg[line]-minarg[line]);
                                                // printf("%f\n", nums[i]);
                                                fprintf(fd_out, ",%f", nums[i]);
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
