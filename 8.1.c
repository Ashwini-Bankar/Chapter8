
/*  	To simulate the behavior of the child closing the standard output when it exits, add fclose(stdout);
	before calling exit in the child.
	To see the effects of doing this, replace the call to printf with the lines

	char buf[MAXLINE];
	int i = printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), glob, var);
	sprintf(buf, "%d\n", i);
	write(STDOUT_FILENO, buf, strlen(buf));

	This assumes that the standard I/O stream stdout is closed when the child calls exit, not the file descriptor STDOUT_FILENO.
	Some versions of the standard I/O library close the file descriptor associated with standard output, which would cause the write to   	      standard output to also fail. In this case, dup standard output to another descriptor, and use this new descriptor for the write.*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int globvar = 0;

void Exit(char *string)
{
	printf("%s\n", string);
	exit(1);
}

int main()
{
	int var = 100;
	printf("Before fork\n");
	printf("pid = %ld, global_var = %d, var = %d\n", (long)getpid(), globvar, var);
	pid_t pid;
	if((pid = vfork()) < 0)
	{
		Exit("fork error");
	}
	else if(pid == 0)
	{
		++globvar;
		++var;
		printf("pid = %ld, global_var = %d, var = %d\n", (long)getpid(), globvar, var);
		fclose(stdout);
		exit(0);
	}

	char buf[16];
	int num = printf("pid = %ld, global_var = %d, var = %d\n", (long)getpid(), globvar, var);
	sprintf(buf, "%d\n", num);
	write(STDOUT_FILENO, buf, strlen(buf));
	exit(0);
}


