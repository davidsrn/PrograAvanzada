#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
  int fd_in, fd_out;

  // Cuenta que las variables ingresadas sean 3
  if(argc != 3) {
    printf("usage: %s origin destination\n", argv[0]);
    return -1;
  }

  // Checa que el archivo recibido en el primer parámetro existe
  if ((fd_in = open(argv[1], O_RDONLY)) < 0) {
    perror(argv[0]);
    return -1;
  }

  // Checa que el archivo recibido en el segundo parámetro existe, si existe
  //   lo trunca a 0 y si no lo crea con todos los permisos
  if ((fd_in = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, 0666)) < 0) {
    perror(argv[0]);
    return -1;
  }

  char buffer;
  ssize_t nbytes;

  while ((nbytes = read(fd_in, &buffer, sizeof(buffer))) != 0) {
    write(fd_out, &buffer, nbytes);
  }

  close(fd_in);
  close(fd_out);

  return 0;
}
