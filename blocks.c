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
    double startTime = omp_get_wtime();


   // int i, j;


    for (int m = 0; m <arraySize/2-1; ++m) {
        for (int i = m+1; i <arraySize/2 ; ++i) {
            temp = mainArray[m][i];
            mainArray[m][i]= mainArray[i][m];
            mainArray[i][m] = temp;
        }
    }

    for (int m = arraySize/2; m <arraySize ; ++m) {
        for (int i = arraySize/2; i <arraySize ; ++i) {
            temp = mainArray[m][i];
            mainArray[m][i]= mainArray[i][m];
            mainArray[i][m] = temp;
        }
    }


    for (int m = arraySize/2; m <arraySize-1 ; ++m) {
        for (int i = m+1; i <arraySize ; ++i) {
        temp = mainArray[m][i];
            mainArray[m][i]= mainArray[i][m];
            mainArray[i][m] = temp;
        }
    }


/*
    for (i = 0; i < arraySize - 1; i++) {
        for (j = i + 1; j < arraySize; j++) {
            temp = mainArray[i][j];
            mainArray[i][j] = mainArray[j][i];
            mainArray[j][i] = temp;
        }
    }
*/

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
