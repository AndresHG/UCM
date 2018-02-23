

#include <time.h>
#include <errno.h>
#include <xlocale.h>

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

	struct tm *timedata = localtime(&t);

	if (timedata == NULL) {
		char error_msg[50];
		sprintf(error_msg, "An error (%i) ocurred", errno);
		perror(error_msg);
		return -1;
	}

	char buf[100];
	strftime(buf, 100, "%A - %B - %C,  %H:%M", timedata);
	printf("Hoy es %s\n", buf);

	return 0;
}
