//
// Created by William on 2018/03/06.
//
#include <stdio.h>
#include<stdlib.h>
#include <omp.h>
#include <pthread.h>

#define DIAGONAL 4






// FUNCTION PROTOTYPES
void displayMatrix(int** matrix, int numberOfRows, int numberOfColumns);
void transpose(int** matrix, int numberOfRows, int i);
void initMatrix(int**  matrix, int numberOfRows, int numberOfColumns);
void freeMemory(int** matrix, int numberOfRows);



struct thread_data{
    int i;
    int numberOfColumns;
    int** matrix;
};

struct thread_data thread[DIAGONAL];

void *swap(void* threadVariables){
    struct thread_data *data;
    data = (struct thread_data*)threadVariables;

    int i = data->i;
    int numberOfColumns = data->numberOfColumns;
    int** matrix = data->matrix;
    int temp;
    for (int j = 0; j < i ; ++j) {
        temp = matrix[i][j];
        matrix[i][j] = matrix[j][i];
        matrix[j][i] = temp;
    }
    pthread_exit(NULL);
}





int main(int argc, char *argv[]) {

    int numberOfRows = DIAGONAL;
    int numberOfColumns = DIAGONAL;

    //Using 2D array of Pointers
    int** matrix = (int** )malloc(sizeof(int *) *numberOfRows);
    for(int i = 0; i < numberOfRows; i++) {
        matrix[i] = (int *) malloc(sizeof(int)*numberOfColumns);
    }
    initMatrix(matrix, numberOfRows, numberOfColumns);

// ==================================================
    pthread_t threads[DIAGONAL];
    int rc;
    printf("Original Matrix \n");
    displayMatrix(matrix, numberOfColumns, numberOfRows);
    for (int i = 0; i < numberOfRows; ++i){
        // transpose(matrix, numberOfRows, i);
        thread->i = i;
        thread->numberOfColumns = numberOfColumns;
        thread->matrix = matrix;
        rc = pthread_create(&threads[i], NULL, swap, (void*) &thread[i]);
    }
    printf("Transposed Matrix \n");
    displayMatrix(matrix, numberOfColumns, numberOfRows);

// ==================================================



    free(matrix);
    return 0;
}


// FUNCTION DEFINITIONS
void displayMatrix(int** matrix, int numberOfRows, int numberOfColumns){

    for (int i = 0; i < numberOfRows; ++i) {
        for (int j = 0; j < numberOfColumns; ++j) {
            printf("%d ", matrix[i][j]) ;
        }

        printf("\n");
    }
}

void transpose(int** matrix, int numberOfRows, int i){
        for (int j = 0; j < i ; ++j) {
            int temp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = temp;
        }
}

void initMatrix(int**  matrix, int numberOfRows, int numberOfColumns){
    int element = 0;
    for(int i = 0; i < numberOfRows; i++){
        for (int j = 0; j < numberOfColumns ; ++j) {
            matrix[i][j] = element;
            element++;
        }
    }
}

void freeMemory(int** matrix, int numberOfRows){
    for(int i = 0; i < numberOfRows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}