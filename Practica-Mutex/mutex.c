#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define NUM_THREADS	4
#define tam_array 1000
#define iteraciones tam_array/NUM_THREADS
//Contreras Villanueva Israel
// SE DECLARA EL ARREGLO A SUMAR
// SE DECLARA el arreglo total de tamaño 2
int x=0;
pthread_mutex_t m1;
int arr[tam_array];
int total=0;

void *PrintHello(void *threadid)
{
   long taskid;
   int inicio;
   int i;
   int fin;

   //se declara la variable parcial
	int parcial=0;
   taskid = (long) threadid;

	inicio=(taskid*iteraciones);
	fin=(inicio+iteraciones); //Calculamos la variable que nos marca desde donde empezamos
	printf ("\n[Thread %5ld] suma de la posicion \t%10d a \t%10d \n",taskid,inicio,fin-1);

   for(i=inicio;i<fin;i++)
   {

	  arr[i]=1;
	  //
	  parcial=parcial+arr[i];
   }


   pthread_mutex_lock(&m1);
   total=total+parcial;
   pthread_mutex_unlock(&m1);


pthread_exit(NULL);
}// fin del codigo que ejecuta cada uno de los N hilos

int main(int argc, char *argv[])
{
pthread_t threads[NUM_THREADS];
long taskids[NUM_THREADS];
int t;


pthread_mutex_init(&m1,NULL);


//LLENAR EL ARREGLO DE NUMEROS A SUMAR

for(t=0;t<NUM_THREADS;t++) {
  taskids[t] = t;
  pthread_create(&threads[t], NULL, PrintHello, (void *) taskids[t]);
  }


//printf("soy el hilo principal y me voy a un exit para esperar por mis hijos hilo\n");


//pthread_exit(NULL);  //es equivalente a un ciclo con instrucciones pthread_join  -ESPERAR POR TODOS LOS HILOS

for(t=0;t<NUM_THREADS;t++)
	pthread_join(threads[t],NULL);   //espera a que los hilos hijo terminen y despues CONTINUA

printf("el valor final es %d\n",total);



//quitar el pthreaD_exit y ajustarlo a un ciclo de pthread_join


//sumar del arreglo total de tamaño 2, las cantidades e  IMPRIMIR EL RESULTADO total


}
