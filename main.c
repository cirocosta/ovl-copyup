#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

static const char* filename = "./merged/a";

int
open_file(int flag)
{
	int fd = openat(AT_FDCWD, filename, flag);

	if (!~fd) {
		perror("openat");
		return 1;
	}

	return close(fd);
}

int
change_owner()
{
	if (!~chown(filename, getuid(), getgid())) {
		perror("chown");
		return 1;
	}

	return 0;
}

int
main(int argc, char** argv)
{
	if (argc != 2) {
		printf("usage: %s (r|w|c)\n", argv[0]);
		return 1;
	}

	switch (*argv[1]) {
		case 'r':
			return open_file(O_RDONLY);
		case 'w':
			return open_file(O_RDWR);
		case 'c': // chown
			return change_owner();
	}

	printf("unknown flag '%s'\n", argv[1]);
	return 1;
}
