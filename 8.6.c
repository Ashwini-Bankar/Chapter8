#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define PSCMD "ps -o pid,ppid,state,tty,command"

void Exit(char *string)
{
	printf("%s\n", string);
	exit(1);
}

int main(void)
{
	pid_t pid;
	if ((pid = fork()) < 0)
	{
		Exit("fork error");
	}
	else if (pid == 0)
	{
		exit(0);
	}

	sleep(4);
	system(PSCMD);
	exit(0);
}
