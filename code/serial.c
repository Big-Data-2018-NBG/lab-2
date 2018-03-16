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

    int matrixSize;

    printf("Please enter the dimensions of the square matrix: \n");
    scanf("%d", &matrixSize);


    int *mainArray[matrixSize];


    for (int k = 0; k < matrixSize; ++k) {
        mainArray[k] = (int *) malloc(matrixSize * sizeof(int));

    }

    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            mainArray[i][j] = (i*matrixSize) + j;
        }
    }

    //Uncomment to print original matrix
    /*
    for (int i = 0; i < matrixSize; ++i) {
            for (int j = 0; j < matrixSize; ++j) {
                printf("%d,\t", mainArray[i][j]);
            }
            printf("\n");
    }*/







    int temp = 0;
    double startTime = omp_get_wtime();


    int i, j;

        for (i = 0; i < matrixSize - 1; i++) {
            for (j = i + 1; j < matrixSize; j++) {
                temp = mainArray[i][j];
                mainArray[i][j] = mainArray[j][i];
                mainArray[j][i] = temp;
            }
        }

    double finalTime = omp_get_wtime() - startTime;


    //Uncomment to print transposed matrix
    printf("\n\n");
    /*
    for (i = 0; i < matrixSize; ++i) {
        for (j = 0; j < matrixSize; ++j) {
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


