#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// Объявдения функций

int** generate(int h, int w);

void print(int** arr, int h, int w);

int** del_row(int** arr, int *hptr, int num);

int* del_col(int* row, int* wptr, int num);

int** del(int** arr, int* hptr, int* wptr, int num);


#endif

