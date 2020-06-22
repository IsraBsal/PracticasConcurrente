#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>


int main()
{
    int tid;
	int i=0;
	int n=7;

	for(i=0;i<n;i++){
		tid=fork();
        if(tid!=0)
	    break;
	}

	printf("i=%d soy %d mi papa es %d\n",i,getpid(),getppid());


        if(i==(n-1))
	{
		tid=fork();
		if(tid==0)
		  execl("./system","./system2",NULL);
	}
	if(i==n)
	{
		tid=fork();
		if(tid==0)
		  execl("./system2","otro",NULL);

	}
	sleep(40);

}
