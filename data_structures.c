#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* int heapsort */
int *int_sort(int *list, int length) { // heapsort, my favourite sort
    /* step 1: create max heap */
    for (int i = 1; i < length; i++) {
        int sub = i;
        while (sub > 0 && list[sub] > list[(sub - 1) / 2]) {
            int swap = list[sub];
            list[sub] = list[(sub - 1) / 2];
            list[(sub - 1) / 2] = swap;
            sub = (sub - 1) / 2;
        }
    }

    /* step 2: heapify */
    for (int i = 0; i < length; i++) {
        int swap = list[0];
        list[0] = list[length - 1 - i];
        list[length - 1 - i] = swap;
        int sub = 0;

        while ((sub + 1) * 2 <= length - 1 - i) {
            int can1 = list[(sub + 1) * 2 - 1]; // candidate 1: left child
            int can2 = list[(sub + 1) * 2]; // candidate 2: right child
            if ((sub + 1) * 2 == length - 1 - i) { // edge case: only the left child exists
                can2 = -2147483648;
            }
            if (can1 > can2) {
                if (can1 > list[sub]) {
                    swap = list[sub];
                    list[sub] = can1;
                    list[(sub + 1) * 2 - 1] = swap;
                    sub = (sub + 1) * 2 - 1;
                } else {
                    break;
                }
            } else {
                if (can2 > list[sub]) {
                    swap = list[sub];
                    list[sub] = can2;
                    list[(sub + 1) * 2] = swap;
                    sub = (sub + 1) * 2;
                } else {
                    break;
                }
            }
        }
    }
    printf("Sorted: [");
    for (int i = 0; i < length; i++) {
        printf("%d, ", list[i]);
    }
    printf("]\n");
    return list;
}


/* (int, int) priority que */
typedef struct { // max priority que (int, freq)
    int *IDArr;
    int *freqArr;
    int capacity;
    int length;
} prior_que_t;

prior_que_t *que_init() { // create a priority que
    prior_que_t *out = malloc(sizeof(prior_que_t));
    out -> IDArr = malloc(5 * sizeof(int));
    out -> freqArr = malloc(5 * sizeof(int));
    out -> length = 0;
    out -> capacity = 5;
    return out;
}

void que_free(prior_que_t *selfp) {
    free(selfp -> IDArr);
    free(selfp -> freqArr);
    free(selfp);
}

void que_add(prior_que_t *selfp, int ID, int freq) { // adds a node with ID and freq to the que
    if (selfp -> length >= selfp -> capacity) {
        selfp -> capacity *= 2;
        selfp -> IDArr = realloc(selfp -> IDArr, selfp -> capacity * sizeof(int));
        selfp -> freqArr = realloc(selfp -> freqArr, selfp -> capacity * sizeof(int));
    }
    selfp -> IDArr[selfp -> length] = ID;
    selfp -> freqArr[selfp -> length] = freq;
    selfp -> length++;
    /* build heap */
    int i = selfp -> length - 1;
    while (i > 0 && selfp -> freqArr[i] > selfp -> freqArr[(i - 1) / 2]) {
        int swap = selfp -> freqArr[i];
        int swapID = selfp -> IDArr[i];
        selfp -> freqArr[i] = selfp -> freqArr[(i - 1) / 2];
        selfp -> IDArr[i] = selfp -> IDArr[(i - 1) / 2];
        selfp -> freqArr[(i - 1) / 2] = swap;
        selfp -> IDArr[(i - 1) / 2] = swapID;
        i = (i - 1) / 2;
    }
}

int que_pop(prior_que_t *selfp) { // returns the ID of the max freq item and removes it from the que
    int ret = selfp -> IDArr[0];
    /* heapify */
    int swap = selfp -> freqArr[0];
    int swapID = selfp -> IDArr[0];
    selfp -> freqArr[0] = selfp -> freqArr[selfp -> length - 1];
    selfp -> IDArr[0] = selfp -> IDArr[selfp -> length - 1];
    selfp -> freqArr[selfp -> length - 1] = swap;
    selfp -> IDArr[selfp -> length - 1] = swapID;
    int sub = 0;
    while ((sub + 1) * 2 <= selfp -> length - 1) {
        int can1 = selfp -> freqArr[(sub + 1) * 2 - 1]; // candidate 1: left child
        int can2 = selfp -> freqArr[(sub + 1) * 2]; // candidate 2: right child
        if ((sub + 1) * 2 == selfp -> length - 1) { // edge case: only the left child exists
            can2 = -2147483648;
        }
        if (can1 > can2) {
            if (can1 > selfp -> freqArr[sub]) {
                swap = selfp -> freqArr[sub];
                swapID = selfp -> IDArr[sub];
                selfp -> freqArr[sub] = can1;
                selfp -> IDArr[sub] = selfp -> IDArr[(sub + 1) * 2 - 1];
                selfp -> freqArr[(sub + 1) * 2 - 1] = swap;
                selfp -> IDArr[(sub + 1) * 2 - 1] = swapID;
                sub = (sub + 1) * 2 - 1;
            } else {
                break;
            }
        } else {
            if (can2 > selfp -> freqArr[sub]) {
                swap = selfp -> freqArr[sub];
                swapID = selfp -> IDArr[sub];
                selfp -> freqArr[sub] = can2;
                selfp -> IDArr[sub] = selfp -> IDArr[(sub + 1) * 2];
                selfp -> freqArr[(sub + 1) * 2] = swap;
                selfp -> IDArr[(sub + 1) * 2] = swapID;
                sub = (sub + 1) * 2;
            } else {
                break;
            }
        }
    }
    selfp -> length--;
    return ret;
}

int pow2(int power) {
    int out = 1;
    for (int i = 0; i < power; i++) {
        out *= 2;
    }
    return out;
}

void printCenteredInt(int pr) {
    if (pr < 10) {
        printf(" %d ", pr);
    } else if (pr < 100) {
        printf("%d ", pr);
    } else if (pr > 999) {
        printf("999");
    } else {
        printf("%d", pr);
    }
}

void que_print(prior_que_t *selfp) {
    int height = 1;
    int hTest = 1;
    while (hTest <= selfp -> length) {
        hTest *= 2;
        height++;
    }
    height--;
    printf("height: %d\n", height);
    int marginLeft = 0;
    int marginRight = 1;
    int bracketLeft = 2;
    int bracketMid = 1;
    int bracketRight = 3;
    // do the pascal power of 2 algorithm
    for (int k = 0; k < height - 1; k++) {
        marginLeft += pow2(k + 1);
        marginRight += pow2(k + 1);
        bracketLeft += pow2(k + 1);
        bracketMid += pow2(k + 2);
        bracketRight += pow2(k + 1);
    }
    int next = 0;
    for (int h = 0; h < height; h++) {
        
        int k = height - 1 - h;
        int geniusLen = pow2(height - (k + 1));

        for (int i = 0; i < geniusLen / 2; i++) {
            for (int j = 0; j < bracketLeft; j++) {
                printf(" ");
            }
            printf("/");
            for (int j = 0; j < bracketMid; j++) {
                printf(" ");
            }
            printf("\\");
            for (int j = 0; j < bracketRight; j++) {
                printf(" ");
            }
        }
        printf("\n");

        for (int i = 0; i < geniusLen; i++) {
            for (int j = 0; j < marginLeft; j++) {
                printf(" ");
            }
            if (next >= selfp -> length) {
                    printf("nil");
            } else {
                printCenteredInt(selfp -> IDArr[next]);
            }
            for (int j = 0; j < marginRight; j++) {
                printf(" ");
            }
            next++;
        }
        printf("\n");
        
        
        marginLeft -= pow2(k);
        marginRight -= pow2(k);
        bracketLeft -= pow2(k);
        bracketMid -= pow2(k + 1);
        bracketRight -= pow2(k);
    }
}

/* int_hashmap */
typedef struct {
    int **map;
    int *mapCapacities;
    int *mapLengths;
    int length;
} int_hashmap_t;

int_hashmap_t *int_hashmap_init(int len) {
    int_hashmap_t *out = malloc(sizeof(int_hashmap_t));
    out -> length = len;
    out -> map = malloc(sizeof(int *) * len);
    out -> mapCapacities = malloc(sizeof(int) * len);
    out -> mapLengths = malloc(sizeof(int) * len);
    for (int i = 0; i < len; i++) {
        out -> mapLengths[i] = 0;
        out -> mapCapacities[i] = 1;
        out -> map[i] = malloc(sizeof(int));
        out -> map[i][0] = -1649223620;
    }
    return out;
}

void int_hashmap_free(int_hashmap_t *selfp) {
    for (int i = 0; i < selfp -> length; i++) {
        free(selfp -> map[i]);
    }
    free(selfp -> map);
    free(selfp -> mapLengths);
    free(selfp -> mapCapacities);
    free(selfp);
}

void int_hashmap_clear(int_hashmap_t *selfp) {
    for (int i = 0; i < selfp -> length; i++) {
        selfp -> mapLengths[i] = 0;
        // selfp -> mapCapacities[i] = 1;
        // selfp -> map[i] = realloc(selfp -> map[i], sizeof(int));
        selfp -> map[i][0] = -1649223620;
    }
}

void int_hashmap_add(int_hashmap_t *selfp, int toAdd) {
    /* hash function: f(x) = x % length */
    int mapped = toAdd % selfp -> length;
    // printf("map[%d][%d] = %d\n", mapped, selfp -> mapLengths[mapped], selfp -> map[mapped][selfp -> mapLengths[mapped]]);
    if (selfp -> mapLengths[mapped] == selfp -> mapCapacities[mapped]) {
        selfp -> mapCapacities[mapped] *= 2;
        selfp -> map[mapped] = realloc(selfp -> map[mapped], sizeof(int) * selfp -> mapCapacities[mapped]);
    }
    selfp -> map[mapped][selfp -> mapLengths[mapped]] = toAdd;
    selfp -> mapLengths[mapped]++;
}

char int_hashmap_check(int_hashmap_t *selfp, int toCheck) {
    int mapped = toCheck % selfp -> length;
    for (int i = 0; i < selfp -> mapLengths[mapped]; i++) {
        if (selfp -> map[mapped][i] == toCheck) {
            return 1;
        }
    }
    return 0;
}

void int_hashmap_print(int_hashmap_t *selfp) {
    printf("hashmap:\n");
    for (int i = 0; i < selfp -> length; i++) {
        printf(" [");
        for (int j = 0; j < selfp -> mapLengths[i] - 1; j++) {
            if (selfp -> map[i][j] == -1649223620)
                printf("null, \n");
            else
                printf("%d, ", selfp -> map[i][j]);
        }
        if (selfp -> mapLengths[i] == 0 || selfp -> map[i][selfp -> mapLengths[i] - 1] == -1649223620)
            printf("null]\n");
        else
            printf("%d]\n", selfp -> map[i][selfp -> mapLengths[i] - 1]);
    }
}

int main(int argc, char *argv[]) {
    int_hashmap_t *newMap = int_hashmap_init(20);
    int_hashmap_print(newMap);
    for (int i = 0; i < 100; i++) {
        int_hashmap_add(newMap, i);
    }
    int_hashmap_add(newMap, 169);
    for (int i = 0; i < 101; i++) {
        if (!int_hashmap_check(newMap, i)) {
            printf("could not find %d\n", i); // should say it could not find 100
        }
    }
    for (int i = 100; i < 200; i++) {
        if (int_hashmap_check(newMap, i)) {
            printf("found %d when it didn't exist\n", i); // should say it found 169
        }
    }
    int_hashmap_print(newMap);
    int_hashmap_free(newMap);

    prior_que_t *newQue = que_init();
    for (int i = 0; i < 50; i++) {
        que_add(newQue, i, i);
    }
    que_print(newQue);
}