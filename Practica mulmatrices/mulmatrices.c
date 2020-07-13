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
    int Avector[N*O];
    int Bvector[O*M];
    int Cvector[N*M];


    // Get the number of processes
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Get the rank of the process
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank==0)
    { val=1;

      int z=0;
      for(i=0;i<N;i++)
      for(j=0;j<O;j++)
      {     A[i][j]=val++;    //llenado de la matriz A
            Avector[z++]=A[i][j];    // copia de matriz A a VectorA
      }

      printf("Matriz A\n" );
      for(i=0;i<N;i++)
      {
        for(j=0;j<O;j++)
          printf("%d ",A[i][j]);  //impresion de la matriz A
         printf("\n");
      }
      printf("\n");



      z=0;
      for(i=0;i<O;i++)
      for(j=0;j<M;j++)
      {     B[i][j]=val++;    //llenado de la matriz B
            Bvector[z++]=B[i][j];    // copia de matriz B a VectorB
      }

      printf("Matriz B \n" );
      for(i=0;i<O;i++)
      {
        for(j=0;j<M;j++)
          printf("%d ",B[i][j]);  //impresion de la matriz B
         printf("\n");
      }
      printf("\n" );



} //fin de si eres el rank 0



MPI_Bcast(Bvector,O*M,MPI_INT,0,MPI_COMM_WORLD);

MPI_Scatter(Avector,O,MPI_INT,Avector,O,MPI_INT,0,MPI_COMM_WORLD);

//      for(i=0;i<(N*O);i++)
//          printf("%d ",Avector[i]);  //impresion del vector A
//      printf("\n");

//      for(i=0;i<(O*M);i++)
//          printf("%d ",Bvector[i]);  //impresion del vector B
//      printf("\n");

for(j=0;j<M;j++)
{
  int parcial=0;
  for(i=0;i<O;i++)
       parcial= parcial + (Avector[i]*Bvector[(i*M)+j]);   //antes era O
  Cvector[j]=parcial;
}


//for(j=0;j<M;j++)
//  printf("soy el proceso %d mi Cvector es %d\n",rank,Cvector[j]);


MPI_Gather(Cvector,M,MPI_INT,Cvector,M,MPI_INT,0,MPI_COMM_WORLD);

if(rank==0)
{

//  for(j=0;j<(N*M);j++)
//   printf("soy el proceso %d mi Cvector es %d\n",rank,Cvector[j]);

    val=0;

      for(i=0;i<N;i++)
      for(j=0;j<M;j++)
         C[i][j]=Cvector[val++];

      printf("MATRIZ\n" );
      for(i=0;i<N;i++)
      {
        for(j=0;j<M;j++)
          printf("%d ",C[i][j]);  //impresion de la matriz A
         printf("\n");
      }
      printf("\n" );


}
    // Finalize the MPI environment.
    MPI_Finalize();
}
