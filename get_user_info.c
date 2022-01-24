// Input / Output library.
#include <stdio.h>
// Calling OS functions libraries.
#include <unistd.h>
// Used only for uid_t type, currently this include is pointless.
#include <sys/types.h>

int main(int argc, char** argv) {
	printf("User ID is %d and their Group ID is %d!\n", getuid(), getgid());
	return 0;
}
