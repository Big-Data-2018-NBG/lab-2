//
// Created by sailen on 2018/02/24.
//

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
            mainArray[i][j] = rand() % 15;
        }
    }


    /*
    for (int i = 0; i < matrixSize; ++i) {
         for (int j = 0; j < matrixSize; ++j) {
             printf("%d,\t", mainArray[i][j]);
         }
         printf("\n");
     }
    */


    int chunkSize = 4;
    omp_set_num_threads(numberOfThreads);


    int temp = 0;
    double startTime = omp_get_wtime();
    int m,i;
#pragma omp parallel shared(matrixSize, mainArray,chunkSize) private(temp, i, m)
    {
    #pragma omp for schedule(dynamic, chunkSize)  nowait
        for (m = 0; m < matrixSize / 2 - 1; ++m) {
            for (i = m + 1; i < matrixSize / 2; ++i) {
                temp = mainArray[m][i];
                mainArray[m][i] = mainArray[i][m];
                mainArray[i][m] = temp;
            }
        }
    }
#pragma omp parallel shared(matrixSize, mainArray,chunkSize) private(temp, i, m)
    {
    #pragma omp for schedule(dynamic, chunkSize)  nowait
        for (m = matrixSize / 2; m < matrixSize - 1; ++m) {
            for (i = m + 1; i < matrixSize; ++i) {
                temp = mainArray[m][i];
                mainArray[m][i] = mainArray[i][m];
                mainArray[i][m] = temp;
            }
        }
    }
#pragma omp parallel shared(matrixSize, mainArray,chunkSize) private(temp, i, m)
    {
    #pragma omp for schedule(dynamic, chunkSize)  nowait
        for (m = matrixSize / 2; m < matrixSize; ++m) {
            for (i = 0; i < matrixSize / 2; ++i) {
                temp = mainArray[m][i];
                mainArray[m][i] = mainArray[i][m];
                mainArray[i][m] = temp;
            }
        }
    }

    double finalTime = omp_get_wtime() - startTime;

    /*
    printf("\n\n");

    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            printf("%d,\t", mainArray[i][j]);
        }
        printf("\n");
    }
    */

    printf("\n%lf\n", finalTime);

    for (int l = 0; l < matrixSize; ++l) {
        free(mainArray[l]);
    }
}

