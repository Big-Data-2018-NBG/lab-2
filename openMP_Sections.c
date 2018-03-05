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
    }
*/







    int temp = 0;
    omp_set_num_threads(8);
    double startTime = omp_get_wtime();


    int i, m;
/*
#pragma omp parallel shared(arraySize, mainArray) private(temp, i, j)
    {
    #pragma omp sections nowait
        {
        #pragma omp section
            for (i = 0; i < arraySize / 12; i++) {
                for (j = i + 1; j < arraySize; j++) {
                    temp = mainArray[i][j];
                    mainArray[i][j] = mainArray[j][i];
                    mainArray[j][i] = temp;
                }
            }
        #pragma omp section
            for (i = arraySize / 12; i < ((arraySize / 12) +(arraySize / 6)); i++) {
                for (j = i + 1; j < arraySize; j++) {
                    temp = mainArray[i][j];
                    mainArray[i][j] = mainArray[j][i];
                    mainArray[j][i] = temp;
                }
            }

        #pragma omp section
            for (i = ((arraySize / 12) +(arraySize / 6)); i < ((arraySize / 12) +(arraySize / 6) + (arraySize/4)); i++) {
                for (j = i + 1; j < arraySize; j++) {
                    temp = mainArray[i][j];
                    mainArray[i][j] = mainArray[j][i];
                    mainArray[j][i] = temp;
                }
            }
        #pragma omp section
            for (i = arraySize / 2; i < arraySize - 1; i++) {
                for (j = i + 1; j < arraySize; j++) {
                    temp = mainArray[i][j];
                    mainArray[i][j] = mainArray[j][i];
                    mainArray[j][i] = temp;
                }
            }
        }
    }


*/



#pragma omp parallel shared(arraySize, mainArray) private(temp, i, m)
    {
    #pragma omp sections nowait
        {
        #pragma omp section
            for (m = 0; m < arraySize / 2 - 1; ++m) {
            for (i = m + 1; i < arraySize / 2; ++i) {
                temp = mainArray[m][i];
                mainArray[m][i] = mainArray[i][m];
                mainArray[i][m] = temp;
            }
        }
        #pragma omp section
            for (m = arraySize / 2; m < arraySize - 1; ++m) {
            for (i = m + 1; i < arraySize; ++i) {
                temp = mainArray[m][i];
                mainArray[m][i] = mainArray[i][m];
                mainArray[i][m] = temp;
            }
        }

        #pragma omp section
             for (m = (arraySize / 2 ); m < arraySize; ++m) {
            for (i = arraySize / 4; i < arraySize / 2; ++i) {
                temp = mainArray[m][i];
                mainArray[m][i] = mainArray[i][m];
                mainArray[i][m] = temp;
            }
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


}

//General in-situ matrix transposition algorithm for massively parallel environments
