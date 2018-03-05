#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "omp.h"


int main() {

    srand(time(NULL));

    int arraySize = 8192;

    int *mainArray[arraySize];


    for (int k = 0; k < arraySize; ++k) {
        mainArray[k] = (int *) malloc(arraySize * sizeof(int));

    }

    for (int i = 0; i < arraySize; ++i) {
        for (int j = 0; j < arraySize; ++j) {
            mainArray[i][j] = rand() % 15;
        }
    }
/*
 for (int i = 0; i < arraySize; ++i) {
        for (int j = 0; j < arraySize; ++j) {
            printf("%d,\t", mainArray[i][j]);
        }
        printf("\n");
    }*/







    int temp = 0;
    omp_set_num_threads(4);
    double startTime = omp_get_wtime();


    int i, j;

#pragma omp parallel shared(arraySize, mainArray) private(temp, i, j)
    {
    #pragma omp for schedule(dynamic, 2) nowait
        for (i = 0; i < arraySize - 1; i++) {
            for (j = i + 1; j < arraySize; j++) {
                temp = mainArray[i][j];
                mainArray[i][j] = mainArray[j][i];
                mainArray[j][i] = temp;
            }
        }
    }

    double finalTime = omp_get_wtime() - startTime;



/*    printf("\n\n");

    for (i = 0; i < arraySize; ++i) {
        for (j = 0; j < arraySize; ++j) {
            printf("%d,\t", mainArray[i][j]);
        }
        printf("\n");
    }*/






    printf("\n%lf\n", finalTime);

    for (int l = 0; l < arraySize; ++l) {
        free(mainArray[l]);
    }


    printf("\nHello world!");

}

//General in-situ matrix transposition algorithm for massively parallel environments
