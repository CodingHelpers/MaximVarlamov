#include "functions.h"

#include <stdio.h>
#include <stdlib.h>

// Реализации функций

int** generate(int h, int w){
    int i, j;
    int** arr = malloc(h * sizeof(int*));
    for(i = 0; i < h; i++){
        arr[i] = malloc(w * sizeof(int));
        for(j = 0; j < w; j++){
            arr[i][j] = rand() % 10;
        }
    }
    return arr;
}
void print(int** arr, int h, int w){
    int i, j;
    for(i = 0; i < h; i++){
        for(j = 0; j < w; j++){
            printf("%i ", arr[i][j]);
        }
        printf("\n");
    }
}
int** del_row(int** arr, int *hptr, int num){
    free(arr[num]);
    arr[num] = arr[(*hptr) - 1];
    int** temp = realloc(arr, --(*hptr) * sizeof(int*));
    if(temp == NULL){
        printf("realloc error");
        return NULL;
    }
    arr = temp;
    return arr;
}
int* del_col(int* row, int* wptr, int num){
    int i;
    int w = *wptr;
    for(i = num+1; i < w; i++){
        row[i-1] = row[i];
    }
    int* temp = realloc(row, (w-1) * sizeof(int));
    if(temp == NULL){
        printf("realloc error");
        return NULL;
    }
    row = temp;
    return row;
}

int** del(int** arr, int* hptr, int* wptr, int num){
    int i;
    arr = del_row(arr, hptr, num);
    for(i = 0; i < *hptr; i++){
        arr[i] = del_col(arr[i], wptr, num);
    }
    (*wptr)--;
    return arr;
}
