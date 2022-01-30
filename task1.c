// Input / Output library.
#include <stdio.h>
// Calling OS functions libraries.
#include <unistd.h>
// Used only for uid_t type, currently this include is pointless.
#include <sys/types.h>

int main(int argc, char** argv) {
	printf("Process ID is %d, Process parent's ID is %d!\n", getpid(), getppid());
	return 0;
}

