#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
	
	
	int fd1;
	
	fd1 = open("/dev/leds", O_WRONLY);
	int i;
	
	for (i = 0; i < 80; i++) {
		write(fd1, "2", 1);
		write(fd1, "1", 1);
		write(fd1, "3", 1);

	}
	
	/*
	for (i = 0; i <3; i++) {
		lseek(fd1, 0, SEEK_CUR);
		write(fd1, i, 1);
		sleep(1);
	}
	*/
	
	
	close(fd1);
	return 0;
}
