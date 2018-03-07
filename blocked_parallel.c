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

    int arraySize = 10;

    int *mainArray[arraySize];


    for (int k = 0; k < arraySize; ++k) {
        mainArray[k] = (int *) malloc(arraySize * sizeof(int));

    }

    for (int i = 0; i < arraySize; ++i) {
        for (int j = 0; j < arraySize; ++j) {
            mainArray[i][j] = rand() % 15;
        }
    }
  //  mainArray[2][0] = 28;
 for (int i = 0; i < arraySize; ++i) {
        for (int j = 0; j < arraySize; ++j) {
            printf("%d,\t", mainArray[i][j]);
        }
        printf("\n");
    }



int chunkSize = 4;
omp_set_num_threads(8);


    int temp = 0;
    double startTime = omp_get_wtime();
int m,i;
#pragma omp parallel shared(arraySize, mainArray,chunkSize) private(temp, i, m)
    {
    #pragma omp for schedule(dynamic, chunkSize)  nowait
        for (m = 0; m < arraySize / 2 - 1; ++m) {
            for (i = m + 1; i < arraySize / 2; ++i) {
                temp = mainArray[m][i];
                mainArray[m][i] = mainArray[i][m];
                mainArray[i][m] = temp;
            }
        }
    }

#pragma omp parallel shared(arraySize, mainArray,chunkSize) private(temp, i, m)
    {
    #pragma omp for schedule(dynamic, chunkSize)  nowait
        for (m = arraySize / 2; m < arraySize - 1; ++m) {
            for (i = m + 1; i < arraySize; ++i) {
                temp = mainArray[m][i];
                mainArray[m][i] = mainArray[i][m];
                mainArray[i][m] = temp;
            }
        }
    }
//    omp_set_num_threads(8);
#pragma omp parallel shared(arraySize, mainArray,chunkSize) private(temp, i, m)
    {
    #pragma omp for schedule(dynamic, chunkSize)  nowait
        for (m = arraySize / 2; m < arraySize; ++m) {
            for (i = 0; i < arraySize / 2; ++i) {
                temp = mainArray[m][i];
                mainArray[m][i] = mainArray[i][m];
                mainArray[i][m] = temp;
            }
        }
    }



    double finalTime = omp_get_wtime() - startTime;

/*

    printf("\n\n");

    for (int i = 0; i < arraySize; ++i) {
        for (int j = 0; j < arraySize; ++j) {
            printf("%d,\t", mainArray[i][j]);
        }
        printf("\n");
    }

*/





    printf("\n%lf\n", finalTime);

    for (int l = 0; l < arraySize; ++l) {
        free(mainArray[l]);
    }


}

//General in-situ matrix transposition algorithm for massively parallel environments
