#include <stdio.h>
#include <stdlib.h>

/*
20.04.23:
access items of a list:
list -> data[0]

list functions:
create list (must be a pointer):
int_list_t *list = list_init();

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

sort the list (biggest to smallest):
list_sort(list);
*/

typedef struct {
    int length;
    int realLength;
    int *data;
} int_list_t;

int_list_t* list_init() { //initialise a list
    int_list_t *list = malloc(sizeof(int_list_t));
    list -> length = 0;
    list -> realLength = 1;
    list -> data = calloc(1, sizeof(int));
    return list;
}

void list_append(int_list_t *list, int data) { //appends an item to the end of the list
    if (list -> realLength  <= list -> length) {
        int tempData[list -> length];
        for (int i = 0; i < list -> length; i++) {
            tempData[i] = list -> data[i];
        }
        list -> realLength *= 2;
        list -> realLength += 1;
        free(list -> data);
        list -> data = calloc(list -> realLength, sizeof(int));
        for (int i = 0; i < list -> length; i++) {
            list -> data[i] = tempData[i];
        }
    }
    list -> data[list -> length] = data;
    list -> length += 1;
}

int list_pop(int_list_t *list) { //pops the last item of the list off and returns it
    if (list -> length <= 0) {
        list_init(list);
        return 0;
    } else {
        list -> length -= 1;
        int ret = list -> data[list -> length];
        list -> data[list -> length] = 0;
        return ret;
    }
}

int list_delete(int_list_t *list, int index) { //deletes the item at list[index] of the list and returns it
    while (index < 0) {index += list -> length;}
    index %= list -> length;
    int ret = list -> data[index];
    for (int i = index; i < list -> length - 1 ; i++) {
        list -> data[i] = list -> data[i + 1];
    }
    list -> length -= 1;
    return ret;
}

int list_find(int_list_t *list, int item) { //returns the index of the first instance of the item in the list, returns -1 if not found (python)
    for (int i = 0; i < list -> length; i++) {
        if (list -> data[i] == item) {
            return i;
        }
    }
    return -1;
}

int list_count(int_list_t *list, int item) { //counts how many instances of an item is found in the list
    int count = 0;
    for (int i = 0; i < list -> length; i++) {
        if (list -> data[i] == item) {count += 1;}
    }
    return count;
}

int list_remove(int_list_t *list, int item) { //deletes the first instance of the item from the list, returns the index the item was at, returns -1 and doesn't modify the list if not found (python but without ValueError)
    for (int i = 0; i < list -> length; i++) {
        if (list -> data[i] == item) {
            list_delete(list, i);
            return i;
        }
    }
    return -1;
}

void list_insert(int_list_t *list, int value, int index) { //inserts the item value at list[index] of the list
    while (index < 0) {index += list -> length;}
    index %= list -> length;
    list_append(list, 0);
    int i;
    for (i = list -> length - 1; i > index; i--) {
        list -> data[i] = list -> data[i - 1];
    }
    list -> data[i] = value;
}

void list_sort(int_list_t *list) { //sorts the list using heapsort (fuck you it's my favourite sorting algorithm) (sorts with index 0 as the biggest)
    //create min heap
    int temp;
    for (int i = 2; i < list -> length + 1; i++) {
        int j = i;
        while (j > 1 && list -> data[j / 2 - 1] > list -> data[j - 1]) {
            temp = list -> data[j / 2 - 1];
            list -> data[j / 2 - 1] = list -> data[j - 1];
            list -> data[j - 1] = temp;
            j /= 2;
        }
    }
    //heapsort
    for (int i = list -> length - 1; i > 0; i--) {
        temp = list -> data[0];
        list -> data[0] = list -> data[i];
        list -> data[i] = temp;
        int j = 1;
        while ((j * 2 - 1 < i && list -> data[j - 1] > list -> data[j * 2 - 1]) || (j * 2 < i && list -> data[j - 1] > list -> data[j * 2])) {
            if (list -> data[j * 2 - 1] < list -> data[j * 2] || j * 2 == i) {
                temp = list -> data[j - 1];
                list -> data[j - 1] = list -> data[j * 2 - 1];
                list -> data[j * 2 - 1] = temp;
                j = j * 2;
            } else {
                temp = list -> data[j - 1];
                list -> data[j - 1] = list -> data[j * 2];
                list -> data[j * 2] = temp;
                j *= 2 + 1;
            }
        }
    }
    return;
}

void list_print(int_list_t *list) { //prints the list (like python would)
    printf("[");
    for (int i = 0; i < list -> length; i++) {
        if (i == list -> length - 1) {
            printf("%d]\n", list -> data[i]);
        } else {
            printf("%d, ", list -> data[i]);
        }
    }
}

/* int main(int argc, char *argv[]) { // demo
    int_list_t *list1 = list_init();
    for (int i = 0; i < 10; i++) {
        list_append(list1, i);
    }
    printf("list:\n");
    list_print(list1);
    printf("delete element at index 5\n");
    list_delete(list1, 5);
    list_print(list1);
    printf("insert 8 at index 2\n");
    list_insert(list1, 8, 2);
    list_print(list1);
    printf("pop\n");
    list_pop(list1);
    list_print(list1);
    printf("delete item 4\n");
    list_remove(list1, 4);
    list_print(list1);
    printf("count number of instances of 8: ");
    printf("%d\n", list_count(list1, 8));
    printf("sort list\n");
    list_sort(list1);
    list_print(list1);
    free(list1 -> data);
    free(list1);
} */