#include <mpi.h>
#include <stdio.h>
#define N 3     //define el numero de procesos
#define M 3
#define O 2
int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);
    int y;
    int i,j,val;
    int A[N][O];
    int B[O][M];
    int C[N][M];
    int Avec[N*O]; //Vector de la matriz A
    int Bvec[O*M]; //Vectpr de la matriz B
    int Cvec[N*M]; //Vector de la matriz C


    // Numero de procesos
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // rank (identificador) de los procesos
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank==0) //Si soy el proceso cero lleno la matriz A y B
    { val=1;

      int z=0;
      for(i=0;i<N;i++)
      for(j=0;j<O;j++){
        A[i][j]=val++;    //llenado de la matriz A
        Avec[z++]=A[i][j];    // hacemos copia de la matriz A a VectorA
      }

      printf("Matriz A\n" );
      for(i=0;i<N;i++){
        for(j=0;j<O;j++) //Imprime la matriz A
          printf("%d ",A[i][j]);
         printf("\n");
      }
      printf("\n");



      z=0;
      for(i=0;i<O;i++)
        for(j=0;j<M;j++){
          B[i][j]=val++;    //llenado de la matriz B
          Bvec[z++]=B[i][j];    // hacemos copia de la matriz B a VectorB
        }

      printf("Matriz B \n" );
      for(i=0;i<O;i++){
        for(j=0;j<M;j++)
          printf("%d ",B[i][j]);  //impresion de la matriz B
         printf("\n");
      }
      printf("\n" );
}



MPI_Bcast(Bvec,O*M,MPI_INT,0,MPI_COMM_WORLD); //Envio la informacion a todos los procesos

MPI_Scatter(Avec,O,MPI_INT,Avec,O,MPI_INT,0,MPI_COMM_WORLD); //Dividimos la informacion entre los procesos

//Codigo que haran todos los procesos--------------------------------------////////*********************

for(j=0;j<M;j++)
{
  int parcial=0;
  for(i=0;i<O;i++)
       parcial= parcial + (Avec[i]*Bvec[(i*M)+j]);   //antes era O
  Cvec[j]=parcial;
}

//Termina Codigo que haran todos los procesos--------------------------------------////////***************************

//Recibimos todo lo que hicieron los procesos con los pedazos de la matriz
MPI_Gather(Cvec,M,MPI_INT,Cvec,M,MPI_INT,0,MPI_COMM_WORLD);
//Termina Recibimos



//El proceso cero imprime el resultado
if(rank==0)
{

  //for(j=0;j<(N*M);j++)
   //printf("soy el proceso %d mi Cvec es %d\n",rank,Cvec[j]);

    val=0;

      for(i=0;i<N;i++)
      for(j=0;j<M;j++)
         C[i][j]=Cvec[val++];

      printf("MATRIZ\n" );
      for(i=0;i<N;i++)
      {
        for(j=0;j<M;j++)
          printf("%d ",C[i][j]);  //impresion de la matriz A
         printf("\n");
      }
      printf("\n" );


}
//Termina impresion de resultado

    MPI_Finalize();
}
