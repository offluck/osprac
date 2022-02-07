// Input / Output library.
#include <stdio.h>
// Calling OS functions libraries.
#include <unistd.h>
// Used for different types. For now is useless.
#include <sys/types.h>

int main(int argc, char **argv, char **envp) {
	// Outputting program's name.
	printf("Program name: %s\n", argv[0]);

	// Outputting program's arguments.
	for (int i = 1; i < argc; ++i) {
		printf("Argument %d: %s\n", i, argv[i]);
	}

	// Outptting environment parameters.
	char **it;
	it = envp;
	int counter = 0;
	while (1) {
		if (*it == 0) {
			break;
		}

		printf("Environment parameter %d: %s\n", ++counter, *it);
		++it;
	}

	return 0;
}
