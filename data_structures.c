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
} priority_que_t;

/* create a priority que */
priority_que_t *que_init() {
    priority_que_t *out = malloc(sizeof(priority_que_t));
    out -> IDArr = malloc(5 * sizeof(int));
    out -> freqArr = malloc(5 * sizeof(int));
    out -> length = 0;
    out -> capacity = 5;
    return out;
}

void que_add(priority_que_t *selfp, int ID, int freq) { // adds a node with ID and freq to the que
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

/* pop from the priority que */
int que_pop(priority_que_t *selfp) { // returns the ID of the max freq item and removes it from the que
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

/* peep from top of que */
int que_peep(priority_que_t *selfp) { // returns the ID of the max freq item
    return selfp -> IDArr[0];
}

/* free the priority que */
void que_free(priority_que_t *selfp) {
    free(selfp -> IDArr);
    free(selfp -> freqArr);
    free(selfp);
}

/* helper function */
int pow2(int power) {
    int out = 1;
    for (int i = 0; i < power; i++) {
        out *= 2;
    }
    return out;
}

/* helper function */
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

/* print the priority que */
void que_print(priority_que_t *selfp) {
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

/* int_hashset */
typedef struct {
    int **map;
    int *mapCapacities;
    int *mapLengths;
    int length;
} int_hashset_t;

/* initialise a hashset */
int_hashset_t *int_hashset_init(int len) {
    int_hashset_t *out = malloc(sizeof(int_hashset_t));
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

/* add element to hashset */
void int_hashset_add(int_hashset_t *selfp, int toAdd) {
    /* hash function: f(x) = x % length */
    int mapped = toAdd % selfp -> length;
    if (selfp -> mapLengths[mapped] == selfp -> mapCapacities[mapped]) {
        selfp -> mapCapacities[mapped] *= 2;
        selfp -> map[mapped] = realloc(selfp -> map[mapped], sizeof(int) * selfp -> mapCapacities[mapped]);
    }
    selfp -> map[mapped][selfp -> mapLengths[mapped]] = toAdd;
    selfp -> mapLengths[mapped]++;
}

/* check if element is in hashset */
char int_hashset_check(int_hashset_t *selfp, int toCheck) {
    int mapped = toCheck % selfp -> length;
    for (int i = 0; i < selfp -> mapLengths[mapped]; i++) {
        if (selfp -> map[mapped][i] == toCheck) {
            return 1;
        }
    }
    return 0;
}

/* remove element from hashset */
char int_hashset_remove(int_hashset_t *selfp, int toRemove) {
    int mapped = toRemove % selfp -> length;
    for (int i = 0; i < selfp -> mapLengths[mapped]; i++) {
        if (selfp -> map[mapped][i] == toRemove) {
            selfp -> mapLengths[mapped]--;
            for (int j = i; j < selfp -> mapLengths[mapped]; j++) {
                selfp -> map[mapped][j] = selfp -> map[mapped][j + 1];
            }
            return 1;
        }
    }
    return 0;
}

/* free the hashset */
void int_hashset_free(int_hashset_t *selfp) {
    for (int i = 0; i < selfp -> length; i++) {
        free(selfp -> map[i]);
    }
    free(selfp -> map);
    free(selfp -> mapLengths);
    free(selfp -> mapCapacities);
    free(selfp);
}

/* clear hash set */
void int_hashset_clear(int_hashset_t *selfp) {
    for (int i = 0; i < selfp -> length; i++) {
        selfp -> mapLengths[i] = 0;
        // selfp -> mapCapacities[i] = 1;
        // selfp -> map[i] = realloc(selfp -> map[i], sizeof(int));
        selfp -> map[i][0] = -1649223620;
    }
}

/* print the hash set */
void int_hashset_print(int_hashset_t *selfp) {
    printf("int_hashset:\n");
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

/* (string, string) hashmap */
typedef struct {
    char ***map;
    int *mapCapacities;
    int *mapLengths;
    int length;
} str_hashmap_t;

/* create a hashmap */
str_hashmap_t *str_hashmap_init(int len) {
    str_hashmap_t *out = malloc(sizeof(str_hashmap_t));
    out -> length = len;
    out -> map = malloc(sizeof(char *) * len);
    out -> mapCapacities = malloc(sizeof(int) * len);
    out -> mapLengths = malloc(sizeof(int) * len);
    for (int i = 0; i < len; i++) {
        out -> mapLengths[i] = 0;
        out -> mapCapacities[i] = 2;
        out -> map[i] = malloc(sizeof(char *) * 2);
        out -> map[i][0] = NULL;
    }
    return out;
}

/* hashes str1, stores both string associated with each other in the table, only str1 is retrievable */
void str_hashmap_add(str_hashmap_t *selfp, char *str1, char *str2) {
    /* hash function: sum all letters % length */
    int mapped = 0;
    int sadd = strlen(str1);
    for (int i = 0; i < sadd; i++) {
        mapped += str1[i];
    }
    mapped %= selfp -> length;
    if (selfp -> mapLengths[mapped] + 1 >= selfp -> mapCapacities[mapped]) {
        selfp -> mapCapacities[mapped] *= 2;
        selfp -> map[mapped] = realloc(selfp -> map[mapped], sizeof(char *) * selfp -> mapCapacities[mapped]);
    }
    selfp -> map[mapped][selfp -> mapLengths[mapped]] = strdup(str1);
    selfp -> map[mapped][selfp -> mapLengths[mapped] + 1] = strdup(str2); 
    selfp -> mapLengths[mapped] += 2;
}

/* only checks for str1, returns str2 if str1 is found. Otherwise returns NULL */
char *str_hashmap_check(str_hashmap_t *selfp, char *str1) {
    int mapped = 0;
    int sadd = strlen(str1);
    for (int i = 0; i < sadd; i++) {
        mapped += str1[i];
    }
    mapped %= selfp -> length;
    for (int i = 0; i < selfp -> mapLengths[mapped]; i += 2) {
        if (strcmp(selfp -> map[mapped][i], str1) == 0) {
            return selfp -> map[mapped][i + 1];
        }
    }
    return NULL;
}

/* free the hashmap */
void str_hashmap_free(str_hashmap_t *selfp) {
    for (int i = 0; i < selfp -> length; i++) {
        for (int j = 0; j < selfp -> mapLengths[i]; j++) {
            free(selfp -> map[i][j]);
        }
        free(selfp -> map[i]);
    }
    free(selfp -> map);
    free(selfp -> mapLengths);
    free(selfp -> mapCapacities);
    free(selfp);
}

/* print the hashmap */
void str_hashmap_print(str_hashmap_t *selfp) {
    printf("str_hashmap:\n");
    for (int i = 0; i < selfp -> length; i++) {
        printf(" [");
        for (int j = 0; j < selfp -> mapLengths[i] - 1; j++) {
            if (selfp -> map[i][j] == NULL)
                printf("null, \n");
            else
                printf("%s, ", selfp -> map[i][j]);
        }
        if (selfp -> mapLengths[i] == 0 || selfp -> map[i][selfp -> mapLengths[i] - 1] == NULL)
            printf("null]\n");
        else
            printf("%s]\n", selfp -> map[i][selfp -> mapLengths[i] - 1]);
    }
}

/* bst nodes */
struct bstNode;
typedef struct bstNode bst_node_t;

struct bstNode {
    int value;
    bst_node_t *parent;
    bst_node_t *left;
    bst_node_t *right;
};

/* create a binary search tree */
bst_node_t *bst_init(int headVal) {
    bst_node_t *out = malloc(sizeof(bst_node_t));
    out -> value = headVal;
    out -> parent = NULL;
    out -> left = NULL;
    out -> right = NULL;
    return out;
}

/* add a value to a bst */
void bst_add(bst_node_t *head, int toAdd) {
    bst_node_t *newNode = malloc(sizeof(bst_node_t));
    newNode -> value = toAdd;
    newNode -> parent = NULL;
    newNode -> left = NULL;
    newNode -> right = NULL;
    char stop = 0;
    while (!stop) {
        if (toAdd > head -> value) {
            if (head -> right == NULL) {
                newNode -> parent = head;
                head -> right = newNode;
                stop = 1;
            } else {
                head = head -> right;
            }
        } else {
            if (head -> left == NULL) {
                newNode -> parent = head;
                head -> left = newNode;
                stop = 1;
            } else {
                head = head -> left;
            }
        }
    }
}

/* search for a value in a bst */
char bst_search(bst_node_t *head, int toFind) {
    while (1) {
        if (head == NULL) {
            return 0;
        }
        if (head -> value == toFind) {
            return 1;
        }
        if (toFind > head -> value) {
            head = head -> right;
        } else {
            head = head -> left;
        }
    }
}

/* find a value's successor */
bst_node_t *bst_successor(bst_node_t *head) {
    if (head -> right != NULL) {
        head = head -> right;
        while (head -> left != NULL) {
            head = head -> left;
        }
        return head;
    }
    bst_node_t *traverse = head -> parent;
    while (traverse != NULL && head != traverse -> right) {
        head = traverse;
        traverse = traverse -> parent;
    }
    return traverse;
}

/* transplant, taken from Introduction to Algorithms fourth edition page 324 */
void bst_transplant(bst_node_t **head, bst_node_t *node1, bst_node_t *node2) {
    if (node1 -> parent == NULL) {
        *head = node2;
    } else if (node1 == node1 -> parent -> left) {
        node1 -> parent -> left = node2;
    } else {
        node1 -> parent -> right = node2;
    }
    if (node2 != NULL) {
        node2 -> parent = node1 -> parent;
    }
}

/* remove a value from a bst - Introduction to Algorithms fourth edition page 325 */
char bst_remove(bst_node_t **head, int toRemove) {
    bst_node_t *traverse = *head;
    while (1) {
        if (traverse == NULL) {
            return 0;
        }
        if (traverse -> value == toRemove) {
            if (traverse -> left == NULL) {
                bst_transplant(head, traverse, traverse -> right);
            } else if (traverse -> right == NULL) {
                bst_transplant(head, traverse, traverse -> left);
            } else {
                bst_node_t *hold = traverse -> right;
                while (1) {
                    if (hold -> left == NULL) {
                        break;
                    }
                    hold = hold -> left;
                }
                if (hold != traverse -> right) {
                    bst_transplant(head, hold, hold -> right);
                    hold -> right = traverse -> right;
                    hold -> right -> parent = hold;
                }
                bst_transplant(head, traverse, hold);
                hold -> left = traverse -> left;
                hold -> left -> parent = hold;
            }
            free(traverse);
            return 1;
        }
        if (toRemove > traverse -> value) {
            traverse = traverse -> right;
        } else {
            traverse = traverse -> left;
        }
    }
}

void bst_in_order_print(bst_node_t *head) {
    if (head == NULL) {
        return;
    }
    bst_in_order_print(head -> left);
    printf("%d ", head -> value);
    bst_in_order_print(head -> right);
}

void bst_full_print(bst_node_t *head) {
    /* an incredibly tough task */
}

/* free a bst */
void bst_free(bst_node_t *head) {
    if (head == NULL) {
        return;
    }
    bst_free(head -> left);
    bst_free(head -> right);
    free(head);
}

struct disSetNode;
typedef struct disSetNode dj_node_t;

/* disjoint set node */
struct disSetNode {
    int value;
    int rank;
    dj_node_t *parent;
};

/* create a disjoint set */
dj_node_t *dj_init(int headVal) {
    dj_node_t *out = malloc(sizeof(dj_node_t));
    out -> parent = out;
    out -> value = headVal;
    out -> rank = 0;
    return out;
}

/* add an element to the set */
void dj_add(dj_node_t *set, int toAdd) {
    dj_node_t *newNode = malloc(sizeof(dj_node_t));
    newNode -> parent = set;
    newNode -> value = toAdd;
    newNode -> rank = 0;
}

dj_node_t *dj_find(dj_node_t *set) {
    if (set -> parent != set) {
        dj_find(set -> parent);
    }
    return set -> parent;
}

/* check if a node is part of the set */
char dj_check(dj_node_t *set, dj_node_t *toCheck) {
    if (dj_find(set) == dj_find(toCheck)) {
        return 1;
    }
    return 0;
}

/* link two disjoint sets */
void dj_link(dj_node_t *set1, dj_node_t *set2) {
    if (set1 -> rank >= set2 -> rank) {
        set2 -> parent = set1;
        if (set1 -> rank == set2 -> rank) {
            set1 -> rank++;
        }
    } else {
        set1 -> parent = set2;
    }
}

/* combine two disjoint sets */
void dj_union(dj_node_t *set1, dj_node_t *set2) {
    dj_link(dj_find(set1), dj_find(set2));
}

int main(int argc, char *argv[]) {
    int_hashset_t *intSet = int_hashset_init(20);
    // int_hashset_print(intSet);
    for (int i = 0; i < 100; i++) {
        int_hashset_add(intSet, i);
    }
    int_hashset_add(intSet, 169);
    for (int i = 56; i < 63; i++) {
        int_hashset_remove(intSet, i);
    }
    for (int i = 0; i < 100; i++) {
        if (!int_hashset_check(intSet, i)) {
            printf("could not find %d\n", i);
        }
    }
    for (int i = 100; i < 200; i++) {
        if (int_hashset_check(intSet, i)) {
            printf("found %d when it didn't exist\n", i); // should say it found 169
        }
    }
    int_hashset_print(intSet);
    int_hashset_free(intSet);

    priority_que_t *newQue = que_init();
    for (int i = 0; i < 50; i++) {
        que_add(newQue, i, i);
    }
    que_print(newQue);
    que_free(newQue);

    str_hashmap_t *strMap = str_hashmap_init(20);
    str_hashmap_add(strMap, "hello", "world");
    // str_hashmap_add(strMap, "world", "hello");
    printf("%s\n", str_hashmap_check(strMap, "hello"));
    if (str_hashmap_check(strMap, "world") == NULL) {
        printf("NULL\n");
    }
    str_hashmap_print(strMap);
    str_hashmap_free(strMap);

    bst_node_t *bstHead = bst_init(10);
    for (int i = 0; i < 10; i++) {
        bst_add(bstHead, i);
    }
    bst_remove(&bstHead, 5);
    bst_remove(&bstHead, 2);
    bst_remove(&bstHead, 10);
    bst_in_order_print(bstHead);
    printf("\n");
    bst_free(bstHead);
}