// Input / Output library.
#include <stdio.h>
// Calling OS functions library.
#include <unistd.h>

int main(int argc, char** argv) {
	printf("User ID is %d and their Group ID is %d!\n", getuid(), getgid());
	return 0;
}
