#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>


void main()
{
	int tid;
    int i=0;
	int n=5;
	for(i=0;i<n;i++){
		tid=fork();
        if(tid!=0){
        	break;
        }

	}

	printf("i = %d soy %d mi papa es %d\n",i,getpid(),getppid());


	if(i==(n-1))
		system("./system");
	if(i==n)
		system("./system2");


	sleep(40);


}
