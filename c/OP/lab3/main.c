#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Нода дека */
typedef struct DequeElem {
    int   num;
    int   group;
    char  FIO[64];
    struct DequeElem *l; // Указатель на элемент слева
    struct DequeElem *r; // Указатель на элемент справа
} DequeElem;

typedef struct Dec {
    DequeElem* left;        // Крайняя левая нода дека
} Dec;

/* Добавление элемента слева */
void Add_Left(Dec *d, int num, int group, char* FIO) {
    printf("\nAdding node to left\n");

    DequeElem *nnode = malloc(sizeof(DequeElem));  // Создаем новую ноду в куче
    nnode->num = num;       // Присваиваем ей данные
    nnode->group = group;
    strcpy(nnode->FIO, FIO);

    nnode->l = NULL;
    nnode->r = NULL;

    if(!d->left) {             // Если дек пуст (указатель на первый элеиент - NULL)
        d->left = nnode;            // Делаем новую ноду первой
    } else {                        // Иначе (в деке уже есть первый элемент)
        nnode->r      = d->left; // Ставим предыдущую самую левую ноду справа от новой
        d->left->l  = nnode;     // Ставим новую ноду слева от предыдущей самой левой
        d->left     = nnode;  // Делаем новую ноду самой левой
    }
}

void Pop_Right(Dec *d) {
    printf("\nDeleting right node\n");
    if(!d->left) { // Если нет элементов, выходим с ошибкой
        printf("Error: deque is empty\n");
        exit(1);
    }

    /* Находим крайнюю правую ноду */
    DequeElem *right = d->left;
    while(right->r != NULL)
        right = right->r;

    if(right->l) {     // Если есть ноды сзади (слева)
        right = right->l; // Перемещаемся назад
        free(right->r);      // Удаляем самую правую ноду
        right->r = NULL;     // Зануляем указатель на next предпоследней ноды
    } else {                 // Иначе
        d->left = NULL;         // Так как оставшаяся нода - единственная, зануляем указатель на самую левую ноду
        free(right);            // Удаляем текущую ноду, так как она единственная
    }
}

void PopLeft(Dec *d) {
    printf("\nDeleting left node\n");
    if(!d->left) { // Если нет элементов, выходим с ошибкой
        printf("Error: deque is empty\n");
        exit(1);
    }

    DequeElem *left = d->left;   // сохраняем указатель на самую левую ноду

    d->left = d->left->r;    // делаем самой левой нодой следующую за ней справа
    d->left->l = NULL;

    free(left); // удаляем самую левую ноду
}

int Empty(Dec *deque) {
    printf("\nChecking if dec is empty\n");
    return (deque->left) ? 0 : 1;
}

void Add_N(Dec *d, int count) {
    int i;

    printf("\nAdding %i nods to dec\n", count);

    int num, group;
    char FIO[64];

    for(i = 0; i < count; i++) {
        printf("Student number: ");
        scanf("%i", &num);
        printf("Group:      ");
        scanf("%i", &group);
        printf("Student FIO:  ");
        do {
            fgets(FIO, 64, stdin);
        } while(FIO[0] == '\n');        // Читаем ввод пока в data.fio не окажется ввод (сначала вводится \n от предыдущей строки)
        FIO[strlen(FIO)-1] = '\0'; // Записываем на место символа переноса строки в конце \0 (конец строки)


        Add_Left(d, num, group, FIO);
    }
}

/* Вывод дека на экран */
void Print(Dec *deque) {
    DequeElem* node = deque->left;

    printf("\nPrinting dec\n");

    while(node) {
        /* Вывод полей структуры */
        printf("Student %s, group %i, code %i\n", node->FIO, node->group, node->num);
        /* Переход дальше по указателю */
        node = node->r;
    }
}

int main(void) {
    Dec deque;
    deque.left = NULL;

    Add_N(&deque, 2);
    Print(&deque);

    int ans = Empty(&deque);
    if(ans) {
        printf("Dec is empty");
    }
    else {
        printf("Dec is not empty");
    }

    Add_Left(&deque, 5, 1442, "Varlamov Maxim");
    Print(&deque);

    PopLeft(&deque);
    Print(&deque);

    PopLeft(&deque);
    Print(&deque);

    Pop_Right(&deque);
    Print(&deque);

    ans = Empty(&deque);
    if(ans) {
        printf("Dec is empty");
    }
    else {
        printf("Dec is not empty");
    }

    return 0;
}

