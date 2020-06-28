//Contreras Villanueva Israel 2163047829
#include <unistd.h>
#include <stdio.h>
#include <omp.h>
#include <math.h>
#define TAM 8 //Modificar al tamano del arreglo deseado
#define PASOS log10(TAM)/log10(2) //Cclulamos los pasos

int A[TAM];
int B[TAM];
int z=1;

int main()
{
  for(int j=0;j<TAM;j++){
      A[j]=j+1;
  } //For en donde llenamos el arreglo por primera vez


    //Hilos en total incluyendo al hilo principal

  for(int i=0;i<PASOS;i++){ //Inicia for de pasos

    z=pow(2,(i));
    printf("Valor de z= %d \n",z);
    omp_set_num_threads(TAM-z);

    //Inicia pragma
    #pragma omp parallel
    {
      int tid;
      tid=omp_get_thread_num();
      B[(tid)+z]=A[(tid)]+A[(tid)+z];

      //inicia omp barrier
      #pragma omp barrier
      {
        A[(tid)+z]=B[(tid)+z];
        printf("Soy el hilo %d y dejo un %d en la posicion %d \n",tid,A[(tid)+z],(tid)+z );
      }
      //Termina barrier
    }
    //Termina pragma

  }//Termina for de pasos






printf("Asi queda el arreglo A \n");
for(int j=0;j<TAM;j++){
    printf("%d ",A[j]);

}
printf("\n");
return 0;
}//Termina main
