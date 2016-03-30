#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <stddef.h>
#include <string.h>

#define BUFSIZE 64

/* Задание:
 * 1) Ввод массива структур
 * 2) Сортировка массива структур
 * 3) Поиск по параметру
 * 4) Изменение заданой структуры
 * 5) Удаление структуры из массива
 * 6) Вывод на экран массива структур
 * 7) Выход
 */

typedef unsigned char ubyte;

enum MENU {
    ENTER = 1,
    SORT,
    SEARCH,
    EDIT,
    DELETE,
    PRINT,
    EXIT
};

typedef struct data_s {
    char author[BUFSIZE];
    char title [BUFSIZE];
    char medium[BUFSIZE];
    uint size;
} Data;

typedef struct struct_array_s {
    Data *array;
    uint len;
} StructArray;

void enter (StructArray *sa);
void sort  (StructArray *sa);
void search(StructArray *sa);
void edit  (StructArray *sa);
void del   (StructArray *sa);
void print (StructArray *sa);
void finish(StructArray *sa);

void print_data(Data *d);

void menu(StructArray *sa) {
    static const char message[] = {
        "1) Enter structures\n"
        "2) Sort  structures\n"
        "3) Search by parameter\n"
        "4) Edit structure\n"
        "5) Delete structure\n"
        "6) Print structures\n"
        "7) Exit\n"
        "\n"
        "Your choise: "
    };

    int a = 0;

    system("cls");
    fflush(stdin);
    printf("%s", message);
    scanf("%i", &a);

    switch(a) {
    case ENTER:  enter(sa);  break;
    case SORT:   sort(sa);   break;
    case SEARCH: search(sa); break;
    case EDIT:   edit(sa);   break;
    case DELETE: del(sa);    break;
    case PRINT:  print(sa);  break;
    case EXIT:   finish(sa); break;
    default:
        printf("%i is undefinied, please enter %i-%i\n", (int)a, ENTER, EXIT);
        system("pause");
        return;
    }
}

int main(void) {
    StructArray sa = {NULL, 0};

    while(1) {
        menu(&sa);
        system("cls");
    }

    return 0;
}

inline void getstr(char* dst, int size, FILE* stream) {
    do {
        fgets(dst, size, stream);
    } while(dst[0] == '\n');
    dst[strlen(dst)-1] = '\0';
}

void enter(StructArray *sa) {
    if(sa->array) free(sa->array);

    printf("How many elements you want to enter? ");
    scanf("%i", &sa->len);

    system("cls");

    sa->array = malloc(sa->len * sizeof(Data));
    Data* current;
    char buff[BUFSIZE];

    uint i;
    for(i = 0; i < sa->len; i++) {
        current = sa->array + i;
        printf("Structure %i:\n", i+1);

        printf("FIO:\t\t");
        getstr(current->author, BUFSIZE, stdin);

        printf("Book Name:\t");
        getstr(current->title, BUFSIZE, stdin);

        printf("Vozvrat:\t");
        getstr(current->medium, BUFSIZE, stdin);

        printf("Bilet:\t\t");
        scanf("%i", &current->size);

        system("cls");
    }
}

void struct_menu(const char* header, int *offset, size_t *size) {
    assert(header != NULL && offset != NULL && size != NULL);
    int a, ofst = -1;
    size_t s;

    while(ofst < 0) {
        printf("%s:\n"
               "1) FIO\n"
               "2) Book Name\n"
               "3) Vozvrat\n"
               "4) Bilet\n"
               "\n"
               "Your choice: ", header);
        scanf("%i", &a);

        switch(a) {
        case 1: ofst = offsetof(Data, author); s = BUFSIZE;     break;
        case 2: ofst = offsetof(Data, title);  s = BUFSIZE;     break;
        case 3: ofst = offsetof(Data, medium); s = BUFSIZE;     break;
        case 4: ofst = offsetof(Data, size);   s = sizeof(uint); break;
        default:
            printf("%i is undefinied, please enter %i-%i\n", (int)a, 1, 4);
            system("pause");
        }

        system("cls");
    }

    *offset = ofst;
    *size   = s;
}

void sort(StructArray *sa) {
    assert(sa != NULL);
    int offset;
    size_t size;

    struct_menu("Sort by", &offset, &size);

#define swap(a, b) \
    Data swap_temp = a; \
    b = a; \
    a = swap_temp;

    uint i, j;
    for(i = 0; i < sa->len; i++) {
        for(j = 0; j < sa->len-1; j++) {
            if(offset != offsetof(Data, size)) {
                if(strcmp((char*)&sa->array[i] + offset,
                          (char*)&sa->array[j] + offset) < 0) {
                    swap(sa->array[i], sa->array[j]);
                }
            } else {
                if(sa->array[j].size < sa->array[i].size) {
                    swap(sa->array[i], sa->array[j]);
                }
            }
        }
    }

}

void search(StructArray *sa) {
    assert(sa != NULL);
    int offset, counter;
    size_t size;
    uint i;

    struct_menu("Search for", &offset, &size);

    printf("Enter value to search for: ");

    if(size == sizeof(uint)) {
        uint target;
        scanf("%u", &target);

        for(i = 0; i < sa->len; i++) {
            if(sa->array[i].size == target) {
                printf("Structure %i match!\n", i);
                print_data(&sa->array[i]);
                printf("\n");
                counter++;
            }
        }
    } else {
        char target[BUFSIZE];
        getstr(target, BUFSIZE, stdin);

        for(i = 0; i < sa->len; i++) {
            if(strcmp((char*)&sa->array[i]+offset, target) == 0) {
                printf("Structure %i match!\n", i);
                print_data(&sa->array[i]);
                printf("\n");
                counter++;
            }
        }
    }

    printf("%i structures matching\n", counter);
    system("pause");
}

void edit(StructArray *sa) {
    system("cls");
    if(!sa->len || !sa->array) {
        printf("There are no structures to edit");
    } else {
        int n = -1;
        while(n < 0){
            printf("What structure do you want to edit? ");
            scanf("%i", &n);
            if(n < 1 || n > sa->len+1) {
                printf("Wrong value, number %i-%i is expected\n", 1, sa->len+1);
                n = -1;
            }
        }

        int offset;
        size_t size;

        printf("Target structure:\n");
        print_data(&sa->array[n]);

        struct_menu("\nChoose field to edit:", &offset, &size);
        printf("New value: ");

        if(size == sizeof(uint)) {
            uint val;
            scanf("%u", &val);
            sa->array[n].size = val;
        } else {
            getstr((char*)&sa->array[n]+offset, size, stdin);
        }

        system("cls");
        printf("Edited structure:\n");
        print_data(&sa->array[n]);
    }

    system("pause");
}

void del(StructArray *sa) {
    system("cls");
    if(!sa->len || !sa->array) {
        printf("There are no structures to delete");
    } else {
        int n = -1;
        while(n < 0){
            printf("What structure do you want to delete? ");
            scanf("%i", &n);
            if(n < 1 || n > sa->len+1) {
                printf("Wrong value, number %i-%i is expected\n", 1, sa->len+1);
                n = -1;
            }
        }

        sa->array[n] = sa->array[sa->len];

        if(sa->len > 1) {
            Data* temp;
            temp = realloc(sa->array, (--sa->len) * sizeof(Data));
            assert(temp != NULL);
            sa->array = temp;
        } else {
            free(sa->array);
        }
        sa->len--;
    }
    system("pause");
}

void print_data(Data *d) {
    printf("FIO:      \t%s\n", d->author);
    printf("Book Name:\t%s\n", d->title);
    printf("Vozvrat:  \t%s\n", d->medium);
    printf("Bilet:    \t%u\n", d->size);
}

void print(StructArray *sa) {
    uint i;
    for(i = 0; i < sa->len; i++) {
        printf("Structure %i:\n", i+1);
        print_data(&sa->array[i]);
        printf("\n");
    }
    system("pause");
}

void finish(StructArray *sa) {
    if(sa->array) free(sa->array);
    exit(0);
}


