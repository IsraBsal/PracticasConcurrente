#include <mpi.h>
#include <stdio.h>
#include <unistd.h>
#define TAM 100


int main (int argc, char *argv[]){
  int x[TAM];
  int z[TAM/2];
	int nprocs, tid;
  int i;
	int parcial=0;
  int total=0;
	MPI_Status estado;


	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&nprocs);
	MPI_Comm_rank(MPI_COMM_WORLD,&myrank);



	//printf("Hola, soy el proceso %d de un total de %d \n",myrank,nprocs);

	if(tid==0){
    //Llenamos el arreglo
    for(int j=0;i<TAM;j++){
      x[j]=1;
    }
    //Termina llenado de arreglo

    //Ahora enviamos la mitad de 0 a 49
    MPI_Send(x,TAM/2,MPI_INT,1,21,MPI_COMM_WORLD);
    //Ahora enviamos la mitad de 50 a 99
    MPI_Send(x+(TAM/2),TAM/2,MPI_INT,2,21,MPI_COMM_WORLD);

    //Recibimos la primera parte
    MPI_Recv(&parcial,1,MPI_INT,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&estado);
    printf("Soy el proceso 0 recibi la suma parcial %d del proceso %d con etiqueta %d",parcial,estado.MPI_SOURCE,estado.MPI_TAG);

    total=parcial;

		//Recibimos la segunda parte
    MPI_Recv(&parcial,1,MPI_INT,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&estado);
    printf("Soy el proceso 0 recibi la suma parcial %d del proceso %d con etiqueta %d",parcial,estado.MPI_SOURCE,estado.MPI_TAG);

    total=total+parcial;

    printf("El total de la suma del arreglo es %d \n",total);
	}

  //Entramos a los procesos 1 y 2
  else{
    //Recibo la mitad del arreglo
    MPI_Recv(z,TAM/2,MPI_INT,0,21,MPI_COMM_WORLD,&estado);
    //Hacer la suma de la mitad
    for(i=0;i<(TAM/2);i++){
      parcial=parcial+z[i];
    }
    //Termina suma

    //Envio mi mitad
		MPI_Send(&parcial,1,MPI_INT,0,28,MPI_COMM_WORLD);
		//printf("SOy el proceso %d envio el dato x %d al proceso 0 \n",myrank,x);
	}

	MPI_Finalize();
}
