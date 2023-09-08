/*
5.09.23: First day
Professor: Kate Jensen (katej@umn.edu)
The goal of an algorithm is to solve a computational problem
The goal of this class is to design solutions that are
1. Correct
2. Reasonably Efficient

2 paths forward:
Reduce problem to something familiar
Design own solution

Assignments: 11 assignments
- grades 10, 25% total
- no late assignments

Midterm exams:
- there are 2
- Each worth 20% of course grade

Final Exam:
- December 16th, 8-10 am
- 35% of course grade
- Open note
- No electronics or calculators


What is a computational problem:
    It means a problem whose solution can be calculated
    Given an input, the algorithm can produce an output
    So an algorithm is a computational process that takes input and produces output, but it has to solve a problem

So basically in this class we're going to devise a process to take inputs and produce CORRECT outputs
 - How can we ensure correctness
 - How can we ensure efficiency


problem: determine if a set of n students contains a pair of students with the same name
one approach: O(n^2) where you check the first name and search the rest for that name, then do that for the second name, etc
another approach: O(n log n) you do the same thing but you sort the list (O(n log n) and use binary search (O(log n))
a strange approach: O(n) use a cryptographic hash function as a table function and if there's a collision 
then you know there are two students with the same name, but your table size cant be shrunk past the max size of the function output
a sensible approach: use a normal hash table and if you get a collision then you check manually if they are the same same
so this is worst case O(n^2) but probably average case O(n)




inductive approach: in a group of 0 or 1 students, no two students have the same name
the inductive hypothesis is that no two students have the same name in a group of k students
for k + 1 students, umm im confused already

Loop invariants (inductions)
- A condition that is satisfied at every step

Efficiency
- Time
    - Number of operations
    - Linear speedup theorem


The Sorting Problem:
Given an unsorted collection of data, 
put it in order from smallest to largest
This class starts lists at index 1? What is this, Lua?
We also write solutions in 'Pseudocode', RAM model
*/

/* this file contains three common O(n²) sorting algorithms */

#include "include/list.h"
#include "include/random.h"
#include <time.h>

list_t *randomList(int length) { // generates a list of n random integers (bounded by 5n)
    list_t *out = list_init();
    for (int i = 0; i < length; i++) {
        list_append(out, (unitype) randomInt(0, length * 5), 'i');
    }
    return out;
}

list_t *randomUniqueList(int length) { // generates a list of n random integers, where no two integers are the same (bounded by 5n)
    list_t *out = list_init();
    for (int i = 0; i < length; i++) {
        int temp = randomInt(0, length * 5);
        while (list_count(out, (unitype) temp, 'i') < 1) {
            temp = randomInt(0, length * 5);
        }
        list_append(out, (unitype) randomInt(0, length * 5), 'i');
    }
    return out;
}

void selectionSort(list_t *list) { // runtime: O(n^2), in place sort, I like this one
    for (int i = 0; i < list -> length - 1; i++) {
        int minInd = i;
        int min = list -> data[i].i;
        for (int j = i; j < list -> length; j++) {
            if (list -> data[j].i < min) {
                min = list -> data[j].i;
                minInd = j;
            }
        }
        list -> data[minInd] = list -> data[i];
        list -> data[i].i = min;
    }
}

void bubbleSort(list_t *list) {
    for (int i = 0; i < list -> length - 1; i++) {
        for (int j = i; j > -1; j--) {
            if (list -> data[j].i > list -> data[j + 1].i) {
                unitype temp = list -> data[j + 1];
                list -> data[j + 1] = list -> data[j];
                list -> data[j] = temp;
            }
        }
    }
}

void insertionSort(list_t *list) { // runtime: O(n^2), in place sort, generally considered as one of the best n² sorts
    for (int i = 1; i < list -> length; i++) { // go through each number
        int j = i;
        while (list -> data[j].i < list -> data[j - 1].i && j > 0) { // continue moving the newest one back until it's no longer smaller than the one that precedes it or until it hits the front
            unitype temp = list -> data[j - 1];
            list -> data[j - 1] = list -> data[j];
            list -> data[j] = temp;
            j--;
        }
        if (i != list -> length - 1) { // don't print the last one cuz it'll get printed twice if you do
            //printf("insertion%2d: ", i);
            //list_print(list);
        }
    }
}

int main(int argc, char *argv[]) {
    srand(time(NULL)); // randomiser init seed

    /* insertion sort */
    list_t *toSort = randomList(10);
    printf("\nUnsorted: ");
    list_print(toSort);
    selectionSort(toSort);
    printf("Selected: ");
    list_print(toSort);
    free(toSort);
    toSort = randomList(10);
    printf("\nUnsorted: ");
    list_print(toSort);
    bubbleSort(toSort);
    printf("Bubbled : ");
    list_print(toSort);
    free(toSort);
    toSort = randomList(10);
    printf("\nUnsorted: ");
    list_print(toSort);
    insertionSort(toSort);
    printf("Inserted: ");
    list_print(toSort);
    printf("\n");
    free(toSort);
}