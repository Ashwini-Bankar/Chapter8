
/*	When vfork is called, the parent’s stack pointer points to the stack frame for the f1 function that calls vfork.

	vfork causes the child to execute first, and the child returns from f1. The child then calls f2, and its stack frame overwrites the 
	previous stack frame for f1. The child then zeros out the automatic variable buf, setting 1,000 bytes of the stack frame to 0. The 
	child returns from f2 and then calls _exit, but the contents of the stack beneath the stack frame for main have been changed.

	The parent then resumes after the call to vfork and does a return from f1. The return information is often stored in the stack frame,
	and that information has probably been modified by the child. After the parent resumes, what happens with this example depends on 
	implementation features(where in the stack frame the return information is stored, what information in the stack frame is wiped out 
	when the automatic variables are modified, and so on). The normal result is a core file.
*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void Exit(char *string)
{
	printf("%s\n", string);
	exit(1);
}

static void f1()
{
	pid_t pid;
	if((pid = vfork()) < 0)
	{
		Exit("vfork error");
	}
}

static void f2()
{
	char buf[1000];
	for(int index = 0; index < sizeof(buf); ++index)
	{
		buf[index] = 0;
	}
}

int main()
{
	f1();
	f2();
	_exit(0);
}
