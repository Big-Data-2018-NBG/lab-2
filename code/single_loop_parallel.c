#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "omp.h"


int main() {

    srand(time(NULL));

    int matrixSize ;
    int numberOfThreads;

    printf("Please enter the dimensions of the square matrix: \n");
    scanf("%d", &matrixSize);
    printf("\nPlease enter the no. of threads required: \n");
    scanf("%d", &numberOfThreads);


    int *mainArray[matrixSize];


    for (int k = 0; k < matrixSize; ++k) {
        mainArray[k] = (int *) malloc(matrixSize * sizeof(int));

    }

    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            mainArray[i][j] = (i*matrixSize) + j;
        }
    }
    //To print the orginal array
    /*
    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            printf("%d,\t", mainArray[i][j]);
        }
        printf("\n");
    }*/

    int temp = 0;
    omp_set_num_threads(numberOfThreads);
    double startTime = omp_get_wtime();


    int i, j;

#pragma omp parallel shared(matrixSize, mainArray) private(temp, i, j)
    {
#pragma omp for schedule(dynamic, 2) nowait
        for (i = 0; i < matrixSize - 1; i++) {
            for (j = i + 1; j < matrixSize; j++) {
                temp = mainArray[i][j];
                mainArray[i][j] = mainArray[j][i];
                mainArray[j][i] = temp;
            }
        }
    }

    double finalTime = omp_get_wtime() - startTime;


    //To print the transposed array
    /*
    printf("\n\n");
    for (i = 0; i < matrixSize; ++i) {
        for (j = 0; j < matrixSize; ++j) {
            printf("%d,\t", mainArray[i][j]);
        }
        printf("\n");
    }*/






    printf("\nThe time taken to transpose the matrix is: %lf\n ", finalTime);

    for (int l = 0; l < matrixSize; ++l) {
        free(mainArray[l]);
    }



}

