#include<stdio.h>
#include<unistd.h>
#include"header.h"
#include<stdlib.h>
static void charatatime(char *);
int main(void)
{
	pid_t pid;
	TELL_WAIT();
	if ((pid = fork()) < 0) 
	{
		printf("fork error");
	} 
	else if (pid == 0) 
	{
		WAIT_PARENT();
		/* parent goes first */
		charatatime("output from child\n");
		TELL_PARENT(getppid());
	} 
	else 
	{
		charatatime("output from parent\n");
		TELL_CHILD(pid);
		WAIT_CHILD();
	}
	exit(0);

}

static void charatatime(char *str)
{
	char *ptr;
	int c;
	setbuf(stdout, NULL);
	/* set unbuffered */
	for (ptr = str; (c = *ptr++) != 0; )
		putc(c, stdout);
}
