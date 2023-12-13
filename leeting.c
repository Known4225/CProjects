#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char* shortestPalindrome(char* s) {
    int len = strlen(s);
    if (len <= 1) {
        return s;
    }
    char maximum[len * 2];
    for (int i = 0; i < len - 1; i++) {
        maximum[i] = s[len - i - 1];
    }
    for (int i = 0; i < len + 1; i++) {
        maximum[i + len - 1] = s[i];
    }
    // printf("max: %s\n", maximum);
    for (int j = 0; j < len - 1; j++) {
        char pal = 1;
        int sublen = j;
        for (int i = 0; i < sublen; i++) {
            // printf("compare1 %c %c\n", maximum[i], maximum[len * 2 - i - 2]);
            if (maximum[i] != maximum[len * 2 - i - 2]) {
                // printf("diverged\n");
                pal = 0;
                break;
            }
        }
        for (int i = 0; i < len / 2 - sublen / 2 && pal == 1; i++) {
            // printf("compare2 %c %c\n", maximum[i + len - 1], maximum[len * 2 - sublen - i - 2]);
            if (maximum[i + len - 1] != maximum[len * 2 - sublen - i - 2]) {
                // printf("diverged\n");
                pal = 0;
            }
        }
        if (pal == 1) {
            char *submax = malloc(len + sublen + 1);
            for (int i = 0; i < sublen; i++) {
                submax[i] = maximum[i];
            }
            for (int i = 0; i < len + 1; i++) {
                submax[i + sublen] = maximum[i + len - 1];
            }
            return submax;
        }
        // printf("\n");
    }
    char *submax = malloc(len * 2);
    for (int i = 0; i < len * 2; i++) {
        submax[i] = maximum[i];
    }
    return submax;
}

struct node;
typedef struct node node_t;

struct node {
    int value;
    int index;
    node_t *next;
};

typedef struct {
    int setSize;
    int setCount;
    node_t **set;
} hashset_t;

bool isAnagram(char* s, char* t) {
    hashset_t shashset;
    shashset.setSize = 50;
    shashset.setCount = 0;
    node_t *harray[shashset.setSize];
    for (int i = 0; i < shashset.setSize; i++) {
        harray[i] = NULL;
    }
    shashset.set = harray;
    int sSize = strlen(s);
    for (int i = 0; i < sSize; i++) {
        int location = s[i] % shashset.setSize;
        if (location < 0) {
            location += shashset.setSize;
        }
        node_t *curNode = shashset.set[location];
        node_t *newNode = alloca(sizeof(node_t));
        newNode -> value = s[i];
        newNode -> next = curNode;
        shashset.setCount++;
        shashset.set[location] = newNode;
    }
    int tSize = strlen(t);
    for (int i = 0; i < tSize; i++) {
        int location = t[i] % shashset.setSize;
        if (location < 0) {
            location += shashset.setSize;
        }
        node_t *curNode = shashset.set[location];
        if (curNode == NULL) {
            return false;
        } else {
            char ret = 0;
            node_t *lastNode = shashset.set[location];
            while (curNode != NULL) {
                if (curNode -> value == t[i]) {
                    ret = 1;
                    if (lastNode == curNode) {
                        shashset.set[location] = curNode -> next;
                    } else {
                        lastNode -> next = curNode -> next;
                    }
                    shashset.setCount--;
                    break;
                }
                lastNode = curNode;
                curNode = curNode -> next;
            }
            if (ret == 0) {
                return false;
            }
        }
    }
    if (shashset.setCount == 0)
        return true;
    return false;
}

char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes) {
    hashset_t mainset;
    mainset.setSize = strsSize * 6;
    mainset.setCount = 0;
    node_t *marray[mainset.setSize];
    for (int i = 0; i < mainset.setSize; i++) {
        marray[i] = NULL;
    }
    mainset.set = marray;
    for (int i = 0; i < strsSize; i++) {
        // printf("str: %s\n", strs[i]);
        int sumC = 0;
        int curlen = strlen(strs[i]);
        for (int j = 0; j < curlen; j++) {
            sumC += strs[i][j];
        }
        int location = sumC % (mainset.setSize / 2);
        if (location < 0) {
            location += mainset.setSize;
        }
        node_t *curNode = mainset.set[location];
        node_t *newNode = malloc(sizeof(node_t));
        newNode -> value = sumC;
        newNode -> next = curNode;
        newNode -> index = i;
        mainset.setCount++;
        mainset.set[location] = newNode;
    }
    /* now we have a hashset of strings that are "presumably anagrams" */
    char ***ret = malloc(sizeof(char **) * strsSize);
    (*returnColumnSizes) = malloc(sizeof(int *) * strsSize);
    int nexti = 0;
    for (int i = 0; i < mainset.setSize; i++) {
        char foundNull = 0;
        int nextj = i;
        int any = 0;
        node_t *curNode = mainset.set[i];
        char **fullList = malloc(sizeof(char *) * strsSize);
        while (curNode != NULL) {
            if (isAnagram(strs[curNode -> index], strs[mainset.set[i] -> index])) {
                // printf("good\n");
                fullList[any] = strs[curNode -> index];
                curNode = curNode -> next;
                any += 1;
            } else {
                // printf("%s %s %d\n", strs[curNode -> index], strs[mainset.set[i] -> index], i);
                node_t *tempNext = curNode -> next;
                if (foundNull == 0) {
                    for (; nextj < mainset.setSize; nextj++) {
                        if (mainset.set[nextj] == NULL) {
                            foundNull = 1;
                            break;
                        }
                    }
                }
                if (foundNull == 0) {
                    nextj = i + 1;
                }
                curNode -> next = mainset.set[nextj];
                mainset.set[nextj] = curNode;
                curNode = tempNext;
            }
            
        }
        if (any) {
            char **listOfAnagrams = malloc(sizeof(char *) * any);
            for (int j = 0; j < any; j++) {
                listOfAnagrams[j] = fullList[j];
            }
            (*returnColumnSizes)[nexti] = any;
            ret[nexti] = listOfAnagrams;
            nexti++;
        }
    }
    *returnSize = nexti;
    return ret;
}

int main(int argc, char *argv[]) {
    char *c1 = "eat";
    char *c2 = "tea";
    char *c3 = "tan";
    char *c4 = "ate";
    char *c5 = "nat";
    char *c6 = "bat";
    char **inp = malloc(sizeof(char *) * 6);
    inp[0] = c1;
    inp[1] = c2;
    inp[2] = c3;
    inp[3] = c4;
    inp[4] = c5;
    inp[5] = c6;
    int returnSize;
    int *columns;
    char ***g = groupAnagrams(inp, 6, &returnSize, &columns);
    printf("%d\n", returnSize);
    for (int i = 0; i < returnSize; i++) {
        printf("[");
        for (int j = 0; j < columns[i]; j++) {
            printf("%s, ", g[i][j]);
        }
        printf("], ");
    }
    printf("\n");
}