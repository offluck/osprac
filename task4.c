// Input / Output library.
#include <stdio.h>
// Calling OS functions libraries.
#include <unistd.h>
// Used for pid_t type.
#include <sys/types.h>

int main(int argc, char** argv, char** envp) {
	pid_t pid;
	pid = fork();

	if (pid == -1) {
		printf("Something went wrong!\n");
		return 0;
	}
	
	if (pid == 0) {
		printf("Hey there, I am a child process!\n");
        	printf("And I will run ls command!\n");
		(void) execle("/bin/ls", "-al", 0, envp);
	} else {
		printf("Hello, I am a parent process!\n");
	}
	printf("Process ID is %d, process parent's ID is %d!\n", getpid(), getppid());
	return 0;
}

