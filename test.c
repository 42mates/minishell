#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
	int pipefd[2];
	pid_t cat_pid, ls_pid;

	if (pipe(pipefd) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	cat_pid = fork();
	if (cat_pid == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	} else if (cat_pid == 0) {

		close(pipefd[0]);

		dup2(pipefd[1], STDOUT_FILENO);

		char *cat_args[] = {"cat", NULL};
		execve("/bin/cat", cat_args, NULL);

		perror("execve");
		exit(EXIT_FAILURE);
	}

	ls_pid = fork();
	if (ls_pid == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	} else if (ls_pid == 0) {

		close(pipefd[1]);

		dup2(pipefd[0], STDIN_FILENO);

		char *ls_args[] = {"ls", NULL};
		execve("/bin/ls", ls_args, NULL);

		perror("execve");
		exit(EXIT_FAILURE);
	}


	close(pipefd[0]);
	close(pipefd[1]);

	while (wait(NULL) > 0);

	return 0;
}