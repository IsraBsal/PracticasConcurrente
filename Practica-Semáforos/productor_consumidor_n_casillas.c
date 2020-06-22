#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>


#define Num_casillas 100 //Numero de casillas que va a tener el arreglo
#define R 100 //Constante de la produccion
int casillas[Num_casillas]; //Arregglo de casillas
sem_t full,empthy;
int ultimo=0;


void * productor()
{
	int dato, i;
	for(i=0; i < R; i++ )  //R en for
	{
		dato = i;
		sem_wait(&empthy);
		casillas[ultimo] = i;
		printf("soy el productor ingreso el valor %d en la posicion %d\n", casillas[ultimo],ultimo);
		sem_post(&full); //Para un elemento mas
		ultimo = ultimo + 1;
		//sleep(1);
	}
	pthread_exit(0);
}
//
void * consumidor()
{

	int dato,i;
	for(i=0; i < R; i++ )  //R en for
	{
		if(ultimo!=0){
			ultimo = ultimo - 1;
		}

		sem_wait(&full);
		dato = casillas[ultimo];
		printf("soy el consumidor saco el valor %d de la posicion %d\n", dato,ultimo);
		sem_post(&empthy);
		sleep(1);
	}
	pthread_exit(0);
}

int main()
{
  pthread_t p1,c1;

  sem_init(&full,0,0);  //el tercer argumento es el valor del semaforo
  sem_init(&empthy,0,Num_casillas);

  pthread_create(&p1,NULL,productor,NULL);
  pthread_create(&c1,NULL,consumidor,NULL);

  pthread_join(c1,NULL);
  pthread_join(p1,NULL);

  printf("fin del programa soy el hilo principal\n");

return 0;
}
