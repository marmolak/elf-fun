#include <stdio.h>
#include <sys/mman.h>
#include <sys/ptrace.h>
#include <string.h>
#include <stdlib.h>

void myfce (void)
{
	int p = 10;
	printf ("hello world %d\n", p);
}

int main (int argc, char **argv, char **envp)
{
    if ( getenv ("LD_BIND_NOW") != NULL ) {
        printf ("Binary is called with binding!\n");
    }

	if (ptrace (PTRACE_TRACEME, 0, 0, 0) != 0) {
		abort ();
	}   
     /* defined in linker.ld script */
	long p = 0x000000601000;
	mprotect ((void *)p, 4096, PROT_READ);

	printf ("hello buddy!\n");
	myfce ();

	mprotect ((void *)p, 4096, PROT_WRITE|PROT_READ);

    return 0;
}
