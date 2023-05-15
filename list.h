#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
21.04.23:
unitype list, supports a variety of types

access items of a list:
list -> data[0]

access length of list:
list -> length

list functions:

create list:
list_t *list = list_init();

access items of a list (as a void pointer):
void *item0 = list_item(list, 0);

append to list:
list_append(list, 0);

pop from list:
list_pop(list);

delete index from list:
list_delete(list, 4);

find element "7" in the list:
list_find(list, 7);

count how many "7"s are in the list:
list_count(list, 7);

find and delete element "7" in the list:
list_remove(list, 7);

print the list:
list_print(list);

free the list (when done using):
list_free(list);
*/

typedef union { //supported types
    int i;
    float f;
    double d;
    char c;
    char* s;
    void* p;
    long l;
    short h;
    bool b;
} unitype;

typedef struct {
    int length;
    int realLength;
    char *type;
    unitype *data;
} list_t;

list_t* list_init() { //initialise a list
    list_t *list = malloc(sizeof(list_t));
    list -> length = 0;
    list -> realLength = 1;
    list -> type = calloc(1, sizeof(char));
    list -> data = calloc(1, sizeof(unitype));
    return list;
}

void* list_item(list_t *list, int index) { //accesses an item of the list as a void pointer
    void *ret;
    switch (list -> type[index]) {
        case 'i':
            ret = malloc(sizeof(int));
            ret = &list -> data[index].i;
        break;
        case 'f':
            ret = malloc(sizeof(float));
            ret = &list -> data[index].f;
        break;
        case 'd':
            ret = malloc(sizeof(double));
            ret = &list -> data[index].d;
        break;
        case 'c':
            ret = malloc(sizeof(char));
            ret = &list -> data[index].c;
        break;
        case 's':
            ret = malloc(strlen(list -> data[index].s) * sizeof(char));
            ret = list -> data[index].s;
        break;
        case 'p':
            ret = malloc(sizeof(void*));
            ret = &list -> data[index].p;
        break;
        case 'l':
            ret = malloc(sizeof(long));
            ret = &list -> data[index].l;
        break;
        case 'h':
            ret = malloc(sizeof(short));
            ret = &list -> data[index].h;
        break;
        case 'b':
            ret = malloc(sizeof(bool));
            ret = &list -> data[index].b;
        break;
        default:
            printf("item - type not recognized\n");
            ret = calloc(1, sizeof(int));
    }
    return ret;
}

void list_free();

void list_append(list_t *list, unitype data, char type) { //append to list, must specify type
    if (list -> realLength  <= list -> length) {
        char tempType[list -> length];
        unitype tempData[list -> length];
        for (int i = 0; i < list -> length; i++) {
            tempType[i] = list -> type[i];
            tempData[i] = list -> data[i];
        }
        list -> realLength *= 2;
        list -> realLength += 1;
        free(list -> type);
        free(list -> data);
        list -> type = calloc(list -> realLength, sizeof(int));
        list -> data = calloc(list ->realLength, sizeof(unitype));
        for (int i = 0; i < list -> length; i++) {
            list -> type[i] = tempType[i];
            list -> data[i] = tempData[i];
        }
    }
    list -> type[list -> length] = type;
    if (type == 's') {
        list -> data[list -> length].s = strdup(data.s);
    } else {
        list -> data[list -> length] = data;
    }
    list -> length += 1;
}

unitype list_pop(list_t *list) { //pops the last item of the list off and returns it
    if (list -> length <= 0) {
        list_free(list);
        list_init(list);
        return (unitype) 0;
    } else {
        list -> length -= 1;
        unitype ret = list -> data[list -> length];
        if (list -> type[list -> length] == 's') {
            free(list -> data[list -> length].s);
        }
        list -> type[list -> length] = (char) 0;
        list -> data[list -> length] = (unitype) 0;
        return ret;
    }
}

unitype list_delete(list_t *list, int index) { //deletes the item at list[index] of the list and returns it
    while (index < 0) {index += list -> length;}
    index %= list -> length;
    unitype ret = list -> data[index];
    if (list -> type[index] == 's') {
        free(list -> data[index].s);
    }
    for (int i = index; i < list -> length - 1 ; i++) {
        list -> data[i] = list -> data[i + 1];
        list -> type[i] = list -> type[i + 1];
    }
    list -> length -= 1;
    list -> type[list -> length] = (char) 0;
    list -> data[list -> length] = (unitype) 0;
    return ret;
}

int unitype_check_equal (unitype item1, unitype item2, char type) { //checks if two unitype items are equal
    switch (type) {
        case 'i':
            if (item1.i == item2.i) {return 1;}
        break;
        case 'f':
            if (item1.f == item2.f) {return 1;}
        break;
        case 'd':
            if (item1.d == item2.d) {return 1;}
        break;
        case 'c':
            // if (item1.c == item2.c) {return 1;} //BROKEN (???) in some gcc settings on certain computer (???)
            if (strcmp(&item1.c, &item2.c) == 0) {return 1;}
        break;
        case 's':
            if (strcmp(item1.s, item2.s) == 0) {return 1;}
        break;
        case 'p':
            if (item1.p == item2.p) {return 1;} //questionable
        break;
        case 'l':
            if (item1.l == item2.l) {return 1;}
        break;
        case 'h':
            if (item1.h == item2.h) {return 1;}
        break;
        case 'b':
            if (item1.b == item2.b) {return 1;}
        break;
    }
    return 0;
}

int list_find(list_t *list, unitype item) { //returns the index of the first instance of the item in the list, returns -1 if not found (python)
    int trig = 0;
    for (int i = 0; i < list -> length; i++) {
        trig += unitype_check_equal(list -> data[i], item, list -> type[i]);
        if (trig == 1) {
            return i;
        }
    }
    return -1;
}

int list_count(list_t *list, unitype item) { //counts how many instances of an item is found in the list
    int count = 0;
    for (int i = 0; i < list -> length; i++) {
        count += unitype_check_equal(list -> data[i], item, list -> type[i]);
        if (unitype_check_equal(list -> data[i], item, list -> type[i]) == 1) {
            // printf("found at: %d\n", i);
        }
        // printf("%d\n", count);
    }
    return count;
}

int list_remove(list_t *list, unitype item) { //deletes the first instance of the item from the list, returns the index the item was at, returns -1 and doesn't modify the list if not found (python but without ValueError)
    int trig = 0;
    for (int i = 0; i < list -> length; i++) {
        trig += unitype_check_equal(list -> data[i], item, list -> type[i]);
        if (trig == 1) {
            list_delete(list, i);
            return i;
        }
    }
    return -1;
}

void unitype_print(unitype item, char type) { //prints a unitype item
    switch (type) {
        case 'i':
            printf("%d", item.i);
        break;
        case 'f':
            printf("%f", item.f);
        break;
        case 'd':
            printf("%lf", item.d);
        break;
        case 'c':
            printf("%c", item.c);
        break;
        case 's':
            printf("%s", item.s);
        break;
        case 'p':
            printf("%p", item.p);
        break;
        case 'l':
            printf("%ld", item.l);
        break;
        case 'h':
            printf("%hi", item.h);
        break;
        case 'b':
            printf("%hi", item.b);
        break;
        default:
            printf("print - type not recognized\n");
            return;
    }
}

void list_print(list_t *list) { //prints the list (like python would)
    printf("[");
    for (int i = 0; i < list -> length; i++) {
        unitype_print(list -> data[i], list -> type[i]);
        if (i == list -> length - 1) {
            printf("]\n");
        } else {
            printf(", ");
        }
    }
}

void list_free(list_t *list) { //frees the data used by the int list
    for (int i = 0; i < list -> length; i++) {
        if (list -> type[i] == 's') {
            free(list -> data[i].s);
        }
    }
    free(list -> type);
    free(list -> data);
    free(list);
}
