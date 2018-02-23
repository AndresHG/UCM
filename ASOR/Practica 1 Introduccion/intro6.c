
#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {

	int uid = getuid();
	struct passwd *buf;

	buf = getpwuid(uid);

	printf("Nombre: %s\n", buf->pw_name);
	printf("Pass: %s\n", buf->pw_passwd);
	printf("Información: %s\n", buf->pw_gecos);
	printf("Directorio: %s\n", buf->pw_dir);

  return 0;
}
