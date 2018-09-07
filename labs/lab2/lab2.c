/*----------------------------------------------------------------

*

* Programación avanzada: Cifrado de un archivo

* Fecha: 23-Ago-2018

* Autor(es): A01206423 David Ramirez

*

*--------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void rota(char array[]){
  int first = array[0];
  for(int i = 0; i < 129; i++){
    array[i] = array[i + 1];
  }
  array[127] = first;
}

int main(int argc, char *argv[]) {

  if ( argc != 4 ){
    printf("Usage: %s number origin destination\n", argv[0]);
    return -1;
  }

  int number =  atoi(argv[1]);

  if(number <= 0){
    printf("Primer parámetro debería ser un número entero mayor a 0\n");
    return -1;
  }

  FILE *file = fopen(argv[2], "r");


  if(file == NULL){
    printf("No existe el archivo ingresado\n");
    return -1;
  }

  char *array;
  long size;

  fseek(file, 0, SEEK_END);
  size = ftell(file);
  rewind(file);

  if(size < 129){
    printf("%s\n", "Done");
    return 0;
  }

  array = (char *)malloc((size+1)*sizeof(char));

  fread(array, size, 1, file);

  fclose(file);

  file=fopen(argv[3], "w");

  for(int i = 0; i < number; i++){
    rota(array);
  }

  fwrite(array, 1, size, file);

  fclose(file);

  printf("DONE\n");


  return 0;
}
