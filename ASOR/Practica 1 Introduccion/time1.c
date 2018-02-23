

#include <time.h>
#include <errno.h>

#include <stdio.h>
#include <stdlib.h>

int main() {
	time_t t;
	time(&t);

	if (t == -1) {
		char error_msg[50];
		sprintf(error_msg, "An error (%i) ocurred", errno);
		perror(error_msg);
		return -1;
	}

	printf("Date: %s", ctime(&t));

	return 0;
}
