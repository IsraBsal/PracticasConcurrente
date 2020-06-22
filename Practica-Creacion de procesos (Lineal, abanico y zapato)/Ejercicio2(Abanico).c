#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

int main(){

	int tid;
	int n=3;


	printf("Soy el proceso h1 %d \n",getpid());


	for(int i=0; i<n;i++){
	    tid=fork();

	    if(tid!=0){
            sleep(2);
        }
        else{
            printf("Soy el h%d: %d y mi papa es: %d \n",i+2,getpid(),getppid());
            sleep(2);
            exit(0);


        }
	}

sleep(30);
return 0;
}
