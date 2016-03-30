#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "functions.h"

int main(int argc, char** argv)
{
    if(argc != 3) return 1;

    srand(time(NULL));
    int n;

    int width = atoi(argv[1]);
    int height = atoi(argv[2]);

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


