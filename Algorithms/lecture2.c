/*
7.09.23:
ALGOL and Simula

Insertion sort:
Loop invariant
 - At the start of each iteration of the for loop, 
 the subarray A[1: i - 1] is sorted
 we need to show this holds for all i < n + 1
 where n is the length of the list


We can prove this with induction:
1. Base case: At the start of the first iteration, i = 1
A[1:1] contains just one element so it is sorted

2. Inductive step: Assume condition holds when i = k >= 2
We need to show that A[1:k] will be sorted priort to the (k + 1)th iteration
A[1 : (k + 1) - 1] is sorted

3. Terminated:
When i = n + 1, the loop terminates:
loop invariant confirms that A[1:n] will be sorted

Efficiency of Algorithms:
Use big O notation
and Omega
O(n) means as your input grows, the time that your algorithm takes grows linearly alongside
Ω(n) means that a problem's best case algorithm is O(n)

There is also a distinction between average and worst-case
Some algorithms, like quicksort, have a different average big O than it's theoretical worst case
so if the input was specifically designed to make it hardest for quicksort, it would do it in O(n^2)
but for a random list, it is expected to take on average O(n log n)

Also the linear speedup theorem says that O(50n) is equivalent to O(n)

Insertion best case: O(n)
Worst case: O(n ^ 2)
*/


#include "include/list.h"
#include "include/random.h"
#include <time.h>

/* exhibit A: Heapsort */

void *intHeapsort(list_t *list) { // heapsort, my favourite sort

    /* step 1: create max heap */
    for (int i = 1; i < list -> length; i++) {
        int sub = i;
        while (sub > -1 && list -> data[sub].i > list -> data[(sub - 1) / 2].i) {
            int swap = list -> data[sub].i;
            list -> data[sub] = list -> data[(sub - 1) / 2];
            list -> data[(sub - 1) / 2].i = swap;
            sub = (sub - 1) / 2;
        }
    }
    printf("Max Heap: ");
    list_print(list);

    /* step 2: heapify */
    for (int i = 0; i < list -> length; i++) {
        unitype swap = list -> data[0]; // swap the first and last items of the list (head of tree becomes out of place)
        list -> data[0] = list -> data[list -> length - 1 - i];
        list -> data[list -> length - 1 - i] = swap;
        int sub = 0;

        while ((sub + 1) * 2 <= list -> length - 1 - i) {
            int can1 = list -> data[(sub + 1) * 2 - 1].i; // candidate 1: left child
            int can2 = list -> data[(sub + 1) * 2].i; // candidate 2: right child
            if ((sub + 1) * 2 == list -> length - 1 - i) { // edge case: only the left child exists
                can2 = -2147483648;
            }
            if (can1 > can2) { // find which child is bigger (who will replace the parent)
                if (can1 > list -> data[sub].i) { // continue propagating the parent down until it is in its proper place (max heap preserved)
                    swap = list -> data[sub];
                    list -> data[sub].i = can1;
                    list -> data[(sub + 1) * 2 - 1] = swap;
                    sub = (sub + 1) * 2 - 1;
                } else {
                    break;
                }
            } else {
                if (can2 > list -> data[sub].i) {
                    swap = list -> data[sub];
                    list -> data[sub].i = can2;
                    list -> data[(sub + 1) * 2] = swap;
                    sub = (sub + 1) * 2;
                } else {
                    break;
                }
            }
        }
    }
    printf("HSorted : ");
    list_print(list);
}

/* exhibit B: Quicksort */

void intQuicksortEmb(list_t *list, int start, int length) {
    if (length - start < 2) {
        return;
    }
    int pivotIndex = start; // picks the first element as pivot
    int pivotSplitter = start + 1;
    unitype temp;
    for (int i = start + 1; i < length; i++) {
        if (list -> data[i].i < list -> data[pivotIndex].i) {
            temp = list -> data[i]; // swap
            list -> data[i] = list -> data[pivotSplitter];
            list -> data[pivotSplitter] = temp;
            pivotSplitter++;
        }
    }
    pivotSplitter--;
    temp = list -> data[pivotIndex]; // swap pivot to correct position
    list -> data[pivotIndex] = list -> data[pivotSplitter];
    list -> data[pivotSplitter] = temp;
    intQuicksortEmb(list, pivotSplitter + 1, length);
    intQuicksortEmb(list, 0, pivotSplitter);
}

void intQuicksort(list_t *list) {
    intQuicksortEmb(list, 0, list -> length);
    printf("QSorted : ");
    list_print(list);
}

/* exhibit C: Mergesort */

int *merge(int *list1, int *list2, int list1Length, int list2Length) {
    /* Merge */
    printf("merging: \n");
    printf("[");
    for (int i = 0; i < list1Length; i++) {
        printf("%d, ", list1[i]);
    }
    printf("]\n");
    printf("[");
    for (int i = 0; i < list2Length; i++) {
        printf("%d, ", list2[i]);
    }
    printf("]\n");
    int *listEnd = malloc(sizeof(int) * (list1Length + list2Length));
    int i = 0;
    int list1p = 0;
    int list2p = 0;
    while (i < list1Length + list2Length) {
        if (list1p >= list1Length) {
            listEnd[i] = list2[list2p];
            list2p++;
        } else if (list2p >= list2Length) {
            listEnd[i] = list1[list1p];
            list1p++;
        } else {
            //printf("tsting\n");
            if (list1[list1p] > list2[list2p]) {
                listEnd[i] = list2[list2p];
                list2p++;
                //printf("2\n");
            } else {
                listEnd[i] = list1[list1p];
                list1p++;
                //printf("1\n");
            }
        }
        i++;
    }
    printf("produced: \n");
    printf("[");
    for (int i = 0; i < list1Length + list2Length; i++) {
        printf("%d, ", listEnd[i]);
    }
    printf("]\n");
    return listEnd;
}

int *intMergesortEmb(int *list, int length) {
    if (length == 1) {
        return list;
    }
    printf("sorting: \n");
    printf("[");
    for (int i = 0; i < length; i++) {
        printf("%d, ", list[i]);
    }
    printf("]\n");
    int halfLen = length / 2;
    int *list1;
    int *list2;
    list1 = intMergesortEmb(list, halfLen);
    list2 = intMergesortEmb(list + halfLen, length - halfLen);
    list = merge(list1, list2, halfLen, length - halfLen);
    return list;
}

void intMergesort(list_t *list) {
    
    int *newList = malloc(sizeof(int) * list -> length);
    for (int i = 0; i < list -> length; i++) {
        newList[i] = list -> data[i].i;
    }
    newList = intMergesortEmb(newList, list -> length);
    for (int i = 0; i < list -> length; i++) {
        list -> data[i].i = newList[i];
    }
    printf("MSorted : ");
    list_print(list);
}

int main(int argc, char *argv[]) {
    list_t *toSort = list_init();
    srand(time(NULL)); // initialise random seed
    for (int i = 0; i < 10; i++) {
        list_append(toSort, (unitype) randomInt(0, 99), 'i');
    }
    printf("Unsorted: ");
    list_print(toSort);
    // intHeapsort(toSort);
    //intQuicksort(toSort);
    intMergesort(toSort);
}