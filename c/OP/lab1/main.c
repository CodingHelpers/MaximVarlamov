#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** generate(int h, int w){ // генерация массива случайных чисел, заданного размера h*w
    int i, j;
    int** arr = malloc(h * sizeof(int*)); // аллокация памяти под массив указетелей (строки)

    for(i = 0; i < h; i++){
        arr[i] = malloc(w * sizeof(int)); // аллокация памяти под столбцы строки i
        for(j = 0; j < w; j++){
            arr[i][j] = rand() % 10; // заполнение ячеек целыми числами от 0 до 9
        }
    }

    return arr;
}

void print(int** arr, int h, int w){ // вывод массива
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

int main(void)
{
    srand(time(NULL));
    int n;
    int width = 5, height = 5;

    int** array = generate(height, width);

    printf("Array:\n");
    print(array, height, width);

    printf("Number of row and col to delete: ");
    scanf("%i", &n);

    del(array, &height, &width, n);

    printf("\n");
    print(array, height, width);
    return 0;
}
