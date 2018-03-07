#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <omp.h>
int main() 
{

for(int z = 0; z < 3; z++)
{
	int dimensionOfSquareMatrix;

        printf("Please enter the dimension of the square matrix:\n");
        
        scanf("%d", &dimensionOfSquareMatrix);
        
	printf("===============================================================================\n");

        int totalElementsInSquareMatrix = dimensionOfSquareMatrix*dimensionOfSquareMatrix;

        int *squareMatrix;

        squareMatrix = (int *) malloc(totalElementsInSquareMatrix * sizeof(int));
	int i,j,count = 0;

	for(i = 0; i < dimensionOfSquareMatrix; i++)
	{
		for(j = 0; j < dimensionOfSquareMatrix; j++)
		{
			*(squareMatrix + i*dimensionOfSquareMatrix + j) = ++count;

		}


	}

	/*printf("Original matrix in 1D:\n");
	for(i = 0; i < dimensionOfSquareMatrix; i++)
	{
		for(j = 0; j < dimensionOfSquareMatrix; j++)
		{
			printf("%d", *(squareMatrix + i*dimensionOfSquareMatrix + j));
			printf(" ");

		}


	}*/
	
	printf("\n");

    


	int temp;
	int index1;
	int index2;
	double begin;
    double end;
    double taken;
    
    for(int m = 4; m <= 128 ;m*=2)
{	
	if(m == 32){continue;}
	double begin;
	double end;
    	double taken;
	
	omp_set_num_threads(m);
	#pragma omp parallel
	{
		begin = omp_get_wtime();
		int id = omp_get_thread_num();
		int numberofthreads = omp_get_num_threads();
		//printf("%i", numberofthreads);
		//printf("\n\n");
		for (int i = id; i < dimensionOfSquareMatrix; i+=numberofthreads )
    		{
       			for (int j = i; j < dimensionOfSquareMatrix; j++ )
       			{
          			// Index in the original matrix.
          			index1 = i*dimensionOfSquareMatrix+j;
          			// Index in the transpose matrix.
          			index2 = j*dimensionOfSquareMatrix+i;
	
				temp = squareMatrix[index1];
				squareMatrix[index1] = squareMatrix[index2];
          			squareMatrix[index2] = temp;
       			}
    		}
		
		end = omp_get_wtime();	
	}

	
	taken = end - begin;
	printf("\n\nTime taken to compute the transpose of the "); 
	printf("%i", dimensionOfSquareMatrix);
	printf(" dimension square matrix with ");
	printf("%i", m);
	printf(" threads in seconds: ");
	printf("%f", taken);

	printf("\n");
	printf("\n\n");


}	
    

	/*printf("Transposed matrix in 1D:\n");
	for (int k=0; k<dimensionOfSquareMatrix*dimensionOfSquareMatrix; k++) 
	{
		printf("%i", squareMatrix[k]);
        	printf(" ");
		

	}*/











}
    return 0;
}
