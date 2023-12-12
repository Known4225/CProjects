/* for testing various C features:
    - stack allocated array behaviour
    - string literal behaviour
    - memset


 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printArray(int *arr, int len) {
    printf("[");
    for (int i = 0; i < len - 1; i++) {
        printf("%d, ", arr[i]);
    }
    printf("%d]\n", arr[len - 1]);
}

void printString(char *arr, int len) {
    printf("[");
    for (int i = 0; i < len - 1; i++) {
        printf("%c, ", arr[i]);
    }
    printf("%c]\n", arr[len - 1]);
}

int main(int argc, char *argv[]) {
    /* stack allocated array initialisers:
    curly brace arrays, {0, 0, 0} do not make a global allocation. It is purely initialisation syntax
    string literals, "hello world" does make a global allocation. It is non-mutable, attempting to mutate this data will result in a seg fault

    creating an array with the array[] = {0, 1, 2} syntax will allocate as necessary

    
    memset(void *dest, int c, size_t num);
    */


    /* test 1: stack allocated arrays */
    int arrTest1[] = {0, 1, 2, 3, 4, 5};
    printArray(arrTest1, 6);
    int arrTest2[6] = {0, 1, 2, 3, 4, 5};
    printArray(arrTest2, 6);
    /* 
    int *arrTest3 = {0, 1, 2, 3, 4, 5}; // cannot do this
    int *arrTest4 = {0}; // does not work
    *arrTest4 = 5; // no int was stack allocated, so there is no valid area to put this
    printArray(arrTest4, 1);
    */

    int arrTest5 = 5;
    printArray(&arrTest5, 1);


    /* exception: string literals allocate themselves (in the .data section globally) */
    char *str1 = "hello world";
    printString(str1, 11);
    /* 
    str1[2] = 'p'; // illegal, segmentation fault (bad permissions). string literal allocations are non-mutable

    char *str2; // bad, must be allocated
    memcpy(str2, str1, 12);
    str2[2] = 'p';
    printString(str2, 11);
    */

    char str3[12]; // this is correct
    memcpy(str3, str1, 12);
    str3[2] = 'p';
    printString(str3, 11);

    char str4[] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '\0'}; // this is also correct
    memcpy(str4, str1, 12);
    str4[2] = 'p';
    printString(str4, 11);



    /* memset behaviour: the int argument is a char. */
    int memTest[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    memset(memTest, 255, 10 * sizeof(int));
    printArray(memTest, 10); // [-1, -1, -1, -1, -1, -1, -1, -1, -1, -1]
    memset(memTest, 1, 10 * sizeof(int));
    printArray(memTest, 10); // [16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009]
    // the correct way to use it is to 0 out data, or to set character data
    char memCTest[10] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '\0'};
    memset(memCTest, '_', 9);
    printString(memCTest, 9);

    int memTest2[10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    memset(memTest2, 0, 10 * sizeof(int));
    printArray(memTest2, 10); // [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]



    /* strings, strcpy, and strdup */
    char *noCopy = "hello"; // pointer to global memory
    char copy[] = "hello"; // creates a copy
    // noCopy[0] = 'g'; // illegal (segfault, bad permissions, cannot mutate)
    copy[0] = 'g'; // legal
    printf("%s\n%s\n", noCopy, copy);
}

/* extra: if function-hover/ctrl-click doesn't work:

    1. Go to Extensions
    2. Click "Disable All Installed Extensions"
    3. Close and Reopen VS Code
    4. Back to Extensions and "Enable All Extensions"

    Essentially enable/disable all extensions fixed the issue.

*/