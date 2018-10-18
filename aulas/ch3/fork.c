#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int main()
{
	pid_t pid;

	pid = fork();

	printf("Oi\n");
	

	if(pid < 0)
	{
		fprintf(stderr, "Fork Failed");
		return 1;
	}
	else if(pid == 0)
	{
		//printf("Sou o filho\n");
		execlp("ls", "ls", NULL);
		//execlp("sleep", "sleep", "5", NULL);
	}
	else
	{
		//printf("Sou o pai\n");
		wait(NULL);
		printf("Child Complete\n");
	}

	return 0;
}
