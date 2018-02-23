#include <unistd.h>	//dup
#include <stdio.h>	 //printf, stdout
#include <sys/types.h> //open, close
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h> //errno
/*
  Escribir   un   programa   que   redirija   la   salida   estándar   a   un   fichero,   cuya   ruta   se   pasa   como  
  primer argumento. Probar escribiendo varias cadenas en la salida estándar. 
*/
int main(int argc, char **argv)
{

	if (argc != 2)
    {
      printf("Uso: ./ej <nombre_archivo>\n");
      return -1;
    }

	int fd = open(argv[1], O_CREAT | O_RDWR, 00777);
	if (fd == -1)
    {
      printf("%i - %s\n", errno, strerror(errno));
      return -1;
    }
	//duplica el desciptor del archivo
	int old_stdout = dup2(fd, 1);
	if (old_stdout == -1)
    {
      printf("%i - %s\n", errno, strerror(errno));
      return -1;
    }

	printf("redirigiendo.\n");
	puts("redirect_puts");

	dup2(old_stdout, fd);

	return 0;
}
