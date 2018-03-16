#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "omp.h"


void initMatrix(int **matrix, int numberOfRows, int numberOfColumns);

void displayMatrix(int **matrix, int numberOfRows, int numberOfColumns);

void freeMemory(int **matrix, int numberOfRows);


struct thread_data {
    int i;
    int numberOfColumns;
    int **matrix;
    int arrStart;
    int arrEnd;
};


void *swap(void *threadVariables) {

    struct thread_data *data;
    data = (struct thread_data *) threadVariables;
    int i = data->i;
    int numberOfColumns = data->numberOfColumns;
    int **matrix = data->matrix;
    int temp;
    int k = data->arrStart;
    int j = data->arrEnd;
    for (int l = k; l < j; ++l) {
        for (int m = l + 1; m < numberOfColumns; ++m) {
            temp = matrix[l][m];
            matrix[l][m] = matrix[m][l];
            matrix[m][l] = temp;
        }
    }

    pthread_exit(NULL);
}


int main() {
    struct thread_data *m;

    srand(time(NULL));
    int matrixSize;
    int numberOfThreads;

    printf("Please enter the dimensions of the square matrix: \n");
    scanf("%d", &matrixSize);
    printf("\nPlease enter the no. of threads required: \n");
    scanf("%d", &numberOfThreads);


    double mSize = matrixSize;


    int **matrix = (int **) malloc(sizeof(int *) * matrixSize);
    for (int i = 0; i < matrixSize; i++) {
        matrix[i] = (int *) malloc(sizeof(int) * matrixSize);
    }
    initMatrix(matrix, matrixSize, matrixSize);


    // Uncomment section to see original matrix
    // displayMatrix(matrix, matrixSize, matrixSize);

    int x;


    // Uncomment for loop to see the sections the array is broken down to
    /*
      for (int i = 0; i < numberOfThreads; i++) {
         x = ((mSize / numberOfThreads) * (i + 1));
         printf("%d\n", x);
     }
    */

    double startTime = omp_get_wtime();
    pthread_t threads[numberOfThreads];
    for (int i = 0; i < numberOfThreads; ++i) {
        m = malloc(sizeof(struct Matrix *));
        m->matrix = matrix;
        m->i = i;
        m->numberOfColumns = matrixSize;
        //This method is not the most optimised, as it just breaks up the array almost evenly in terms of,
        //number of rows it transposes, However some rows will have more blocks to transpose than others, due to the diagonals
        //Hence a higher than normal thread count is faster than the actual thread count of the computer
        m->arrStart = (mSize / numberOfThreads) * i;
        m->arrEnd = (mSize / numberOfThreads) * (i + 1);

        pthread_create(&threads[i], NULL, swap, (void *) m);

    }

    //  Uncommet section to see transposed matrix
    
    /*printf("\nTransposed Matrix is: \n");
    displayMatrix(matrix, matrixSize, matrixSize);*/
    


    for (int j = 0; j < numberOfThreads; ++j) {
        (void) pthread_join(threads[j], NULL);
    }


    double endTime = omp_get_wtime();
    double finaltime = endTime - startTime;
    printf("\nThe total time taken to transpose is: %lf\n", finaltime);

    freeMemory(matrix, matrixSize);


    return 0;
}


void initMatrix(int **matrix, int numberOfRows, int numberOfColumns) {
    for (int i = 0; i < numberOfRows; i++) {
        for (int j = 0; j < numberOfColumns; ++j) {
            matrix[i][j] = (i*numberOfRows) + j;
        }
    }
}

void displayMatrix(int **matrix, int numberOfRows, int numberOfColumns) {

    for (int i = 0; i < numberOfRows; ++i) {
        for (int j = 0; j < numberOfColumns; ++j) {
            printf("%d\t", matrix[i][j]);
        }

        printf("\n");
    }
}

void freeMemory(int **matrix, int numberOfRows) {
    for (int i = 0; i < numberOfRows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}
