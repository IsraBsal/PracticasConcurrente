#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define M 2
#define N 3
#define L 2

int A[M][N];
int B[N][L];
int C[M][L];


void inicializa_Matrices()
{
   int i,j;

   for (i=0; i<M; i++){
     for (j=0; j<N; j++){
       A[i][j] =j+1;
     }
   }

   for (i=0; i<N; i++){
     for (j=0; j<L; j++){
       B[i][j] =j+1;
      }
   }

}



void imprime_Matriz()
{
   int i,j;
   printf("Matriz A\n");
   for (i=0; i<M; i++){
     for (j=0; j<N; j++){
       printf("%d \t", A[i][j]);
      }
      printf("\n");
    }

   printf("Matriz B\n");
   for (i=0; i<N; i++){
     for (j=0; j<L; j++){
       printf("%d \t", B[i][j]);
      }
     printf("\n");
   }
}



int main(int argc, char * argv[])
{
  //Variables
  int i;
  int j;
  int k;
  int multiplicacion_m;
  int sum;
  //Termina Variables

  inicializa_Matrices();
  imprime_Matriz();
  sum=0;

   for(i=0;i<M;i++){
   		for(j=0;j<L;j++){
			      for(k=0;k<N;k++){
              multiplicacion_m=(A[i][k])*(B[k][j]);
              sum=sum+multiplicacion_m;
            }
            C[i][j]=sum;
            sum=0;
        }
    }

	printf("Matriz C\n");
       for (i=0; i<M; i++){
           for (j=0; j<L; j++){
               printf("%d \t", C[i][j]);
        }
        printf("\n");
   }

    return 0;
}
