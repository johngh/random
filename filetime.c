#define _POSIX_C_SOURCE 200809L
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#include <stdio.h> // for printf
#include <stdlib.h> // for EXIT_FAILURE

void usage(char *myname) {
	printf("Usage: %s [-e|-v] FILENAME]\n", myname);
	printf("  -e : epoch seconds\n");
	printf("  -v : verbose");
	exit (1);
}

int main(int argc, char *argv[]) {
	struct tm *filetime;

	int ret;
	char *myname = argv[0];

	struct stat st = {0};

	if ( argv[1][0] == '-' )  {

		switch (argv[1][1]) {
			case 'e':
				ret = stat(argv[2], &st);
				if (ret == -1) {
					perror(argv[2]);
					return EXIT_FAILURE;
				}
				printf("%s: %lld", argv[2], (long long) st.st_mtime);
				break;
			case 'v':
				ret = stat(argv[2], &st);
				if (ret == -1) {
					perror(argv[2]);
					return EXIT_FAILURE;
				}
				filetime = localtime(&st.st_mtime);
				printf ("%s.%04d%02d%02d%02d%02d", argv[2],
				        filetime->tm_year+1900, filetime->tm_mon+1, filetime->tm_mday,
				        filetime->tm_hour, filetime->tm_min);
				break;

			default:
				printf("Invalid switch '%s'\n", argv[1]);
				usage(myname);
		}
		return 0;

	}
	ret = stat(argv[1], &st);
	if (ret == -1) {
		perror(argv[1]);
		return EXIT_FAILURE;
	}
	filetime = localtime(&st.st_mtime);

	printf ("%04d%02d%02d%02d%02d",
	        filetime->tm_year+1900, filetime->tm_mon+1, filetime->tm_mday,
	        filetime->tm_hour, filetime->tm_min);

	return 0;
}

