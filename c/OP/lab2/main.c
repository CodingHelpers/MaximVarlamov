#include <stdio.h>
#include <string.h>
#include <stdarg.h>

int has_reps(int n, ...) {
    va_list lst;
    int i, j, len, count = 0;
    char last;
    char* word;

    va_start(lst, n);
    for(i = 0; i < n; i++) {
        word = va_arg(lst, char*);
        len = strlen(word);
        last = -1;
        for(j = 0; j < len; j++) {
            if(last == word[j]) {
                count++;
                break;
            }
            last = word[j];
        }
    }

    va_end(lst);

    return count;
}

int more_then_4(int n, ...) {
    va_list lst;
    int i, count = 0;

    va_start(lst, n);
    for(i = 0; i < n; i++) {
        if(strlen(va_arg(lst, char*)) > 4)
            count++;
    }

    va_end(lst);

    return count;
}

int main(void)
{
    int (*f1)(int, ...) = has_reps;
    int (*f2)(int, ...) = more_then_4;

    // answer: 2
    printf("has_reps: %i\n", f1(3, "aaaa", "toilet", "programmer"));

    // answer: 1
    printf("has_reps: %i\n", f1(5, "nasty", "chupa-chups", "SUAI", "paper", "noose"));

    // answer: 2
    printf("more_then_4: %i\n", f2(3, "aaaa", "toilet", "programmer"));

    // answer: 4
    printf("more_then_4: %i\n", f2(5, "nasty", "chupa-chups", "SUAI", "paper", "noose"));
    return 0;
}

