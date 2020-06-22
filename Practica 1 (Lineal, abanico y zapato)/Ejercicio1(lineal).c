#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main(){

	int tid;
	int n=7;
	tid=fork();

	for(int i=0; i<n;i++){

	    //printf("Valor de tid %d \n",tid);

	    if(tid==0){

            printf("Soy el hijo: %d y mi papa es: %d \n",getpid(),getppid());
		   tid=fork();

        }
        else{
            //printf("Soy el papa %d \n",getpid());
            sleep(1);
        }

	}
sleep(40);

return 0;
}
