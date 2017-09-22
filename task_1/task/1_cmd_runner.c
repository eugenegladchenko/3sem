
/*
  Write a program which allow you to: 
- run another programs via command line.
- get exit codes of terminated programs

## TIPS:
1. Use "2_fork_wait_exit.c" and "4_exec_dir.c" from examples. Combine them.
2. Parse input string according to the type of exec* (see "man exec").
   a) if execvp is used, string splitting into "path" and "args" is all you need.
3. Collect exit codes via waitpid/WEXITSTATUS.
*/
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char** argv) {
	int st,i;
	pid_t p;
	char** newar = malloc (argc * sizeof (char**));
	newar[0] = argv[0];
	for (i = 2; i < argc; i++)
		newar[i-1] =argv[i];
		newar[argc-1] = NULL;
			p = fork();
			if (p < 0) {
				printf("can't fork\n");
				exit(1);
			} 
			if (p == 0) {
				// child
				execvp(argv[1], newar);
				printf("exec error: %s\n", strerror(errno));
				exit(1);
			}
			if (p > 0) {
				wait(&st);
				printf("pid %d finished with exit code %d\n", p, WEXITSTATUS (st));
			}
	return 0;
}
