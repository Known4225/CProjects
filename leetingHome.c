#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void printArray(int *arr, int len) {
    printf("[");
    for (int i = 0; i < len - 1; i++) {
        printf("%d, ", arr[i]);
    }
    printf("%d]\n", arr[len - 1]);
}

int numDistinctNaive(char *s, char *t) {
    /* naive solution */
    int out = 0;
    int slen = strlen(s);
    int tlen = strlen(t);
    int nonlen = slen - tlen + 1;
    int submap[tlen];
    for (int i = 0; i < tlen; i++) {
        submap[i] = 0;
    }
    
    for (int j = 0; j < tlen; j++) {
        char found = 1;
        for (int i = 0; i < tlen; i++) {
            if (s[nonlen + i - submap[i]] != t[i]) {
                found = 0;
                break;
            }
        }
        out += found;
        submap[j]++;
    }
    return out;
}

int numDistinct(char* s, char* t) {
    return numDistinctNaive(s, t);
}

void printMap(int *map, int num) {
    printf("[");
    for (int i = 0; i < num - 1; i++) {
        printf("%d, ", map[i]);
    }
    printf("%d]\n", map[num - 1]);
}

int nCrRep(int n, int r) {
    int fac1 = n + r - 1;
    int facTop = 1;
    for (int i = 1; i < fac1 + 1; i++) {
        facTop *= i;
    }

    int fac2 = n - 1;
    int facBot1 = 1;
    for (int i = 1; i < fac2 + 1; i++) {
        facBot1 *= i;
    }

    int fac3 = r;
    int facBot2 = 1;
    for (int i = 1; i < fac3 + 1; i++) {
        facBot2 *= i;
    }

    return facTop / (facBot1 * facBot2);
}

void pattern(int num, int sup) {
    int map[num];
    map[num] = 0;
    int genmap[num][num];
    for (int i = 0; i < num; i++) {
        map[i] = 0;
        for (int j = 0; j < i + 1; j++) {
            genmap[i][j] = 1;
        }
        for (int j = i + 1; j < num; j++) {
            genmap[i][j] = 0;
        }
        // printMap(genmap[i], num);
    }
    int pliter[num + 1];
    for (int i = 0; i < sup + 1; i++) {
        pliter[i] = nCrRep(num, i);
    }
    printMap(pliter, sup + 1);
    int iters = nCrRep(sup + 1, num);
    printf("iters: %d\n", iters);
    int next = 0;
    map[0] = 0;
    int r = 0;
    int j = 1;
    for (int k = 0; k < iters; k++) {
        if (map[j] < map[j - 1]) {
            map[j] += 1;
            for (int h = j + 1; h < num; h++) {
                map[h] = 0;
            }
        }
        if ((j < num - 1 && map[j] != map[j + 1]) || (map[j] == map[j - 1])) {
            do {
                j++;
                if (j >= num) {
                    j = 1;
                }
            } while (j < num - 1 && j > 0 && map[j] >= map[j - 1]);
        } else {

        }
        if (r == pliter[next]) {
            r = 0;
            j = 1;
            map[0]++;
            for (int h = 1; h < num; h++) {
                map[h] = 0;
            }
            next++;
        }
        r++;
        printMap(map, num);
    }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

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

int* topKFrequent(int* nums, int numsSize, int k, int* returnSize) {
    /* heapsort */
    nums = int_sort(nums, numsSize);
    for (int i = 0; i < numsSize; i++) {
        // printf("%d, ", nums[i]);
    }
    // printf("\n");
    /* running */
    prior_que_t *que = que_init();
    int mega = 1;
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] == nums[i - 1]) {
            mega++;
        } else {
            // printf("added %d %d\n", nums[i - 1], mega);
            que_add(que, nums[i - 1], mega);
            mega = 1;
        }
    }
    // printf("added %d %d\n", nums[numsSize - 1], mega);
    que_add(que, nums[numsSize - 1], mega);
    *returnSize = k;
    int *out = malloc(k * sizeof(int));
    for (int i = 0; i < k; i++) {
        out[i] = que_pop(que);
    }
    que_free(que);
    return out;
}

typedef struct {
    int *data;
    int length;
    int capacity;
} int_stack_t;

int_stack_t *stack_init() {
    int_stack_t *out = malloc(sizeof(int_stack_t));
    out -> data = malloc(5 * sizeof(int));
    out -> capacity = 5;
    out -> length = 0;
    return out;
}

void stack_add(int_stack_t *stack, int toAdd) {
    if (stack -> length >= stack -> capacity) {
        stack -> capacity *= 2;
        stack -> data = realloc(stack -> data, stack -> capacity * sizeof(int));
    }
    stack -> data[stack -> length] = toAdd;
    stack -> length++;
}

int stack_remove(int_stack_t *stack) {
    if (stack -> length > 0) {
        stack -> length--;
        return stack -> data[stack -> length];
    }
    return 0;
}


int trapFail(int* height, int heightSize) {
    /* two scenarios
    1. height[i + 1] >= height[i]
    2. height[i + 1] < height[i]

    in scenario 1, no water is added.
    in scenario 2, the difference is added.
    in either case, the previous maximum - height[i] is added.

    if the height never reaches the original height[i], then we subtract:
    (height[i] - max(after_i)) * 

    */
    int out = 0;
    int_stack_t *stack = stack_init();
    for (int i = 1; i < heightSize; i++) {
        if (height[i] < height[i - 1]) {
            stack_add(stack, height[i - 1] - height[i]);
        } else {
            out += stack_remove(stack);
        }
    }
    return out;
}

int findLeftMax(int *array, int length, int pivot) { // finds the index of the maximum of an array left of the pivot
    if (pivot < 1) {
        return -1;
    }
    int out = 0;
    int max = 0;
    for (int i = 0; i < pivot; i++) {
        if (array[i] > max) {
            max = array[i];
            out = i;
        }
    }
    return out;
}

int findRightMax(int *array, int length, int pivot) { // finds the index of the maximum of an array right of the pivot
    if (pivot > length - 2) {
        return length;
    }
    int out = pivot + 1;
    int max = 0;
    for (int i = pivot + 1; i < length; i++) {
        if (array[i] > max) {
            max = array[i];
            out = i;
        }
    }
    return out;
}


int trap(int* height, int heightSize) {
    /*
    Partition the array around the maximum

    */
    int partition = 0;
    int max = 0;
    for (int i = 0; i < heightSize; i++) {
        if (height[i] > max) {
            max = height[i];
            partition = i;
        }
    }
    int volume = max * heightSize;
    int leftMax = partition;
    int oldLeftMax = leftMax;
    int rightMax = partition;
    int oldRightMax = rightMax;
    leftMax = findLeftMax(height, heightSize, leftMax);
    while (leftMax > -1) {
        printf("lsubtracted %d\n", (height[oldLeftMax] - height[leftMax]) * (oldLeftMax));
        volume -= (height[oldLeftMax] - height[leftMax]) * (oldLeftMax);
        oldLeftMax = leftMax;
        leftMax = findLeftMax(height, heightSize, leftMax);
    }
    rightMax = findRightMax(height, heightSize, rightMax);
    while (rightMax < heightSize) {
        printf("rsubtracted %d\n", (height[oldRightMax] - height[rightMax]) * (heightSize - oldRightMax - 1));
        volume -= (height[oldRightMax] - height[rightMax]) * (heightSize - oldRightMax - 1);
        oldRightMax = rightMax;
        rightMax = findRightMax(height, heightSize, rightMax);
    }
    for (int i = 0; i < heightSize; i++) {
        volume -= height[i];
    }
    return volume;
}

int trapWorks(int* height, int heightSize) {
    /*
    Partition the array around the maximum
    */
    int partition = 0;
    int max = 0;
    int volume = 0;
    for (int i = 0; i < heightSize; i++) {
        volume -= height[i];
        if (height[i] > max) {
            max = height[i];
            partition = i;
        }
    }
    volume += max * heightSize;
    int leftMax = partition;
    int rightMax = partition;
    
    while (leftMax > -1) {
        int oldLeftMax = leftMax;

        if (leftMax < 1) {
            break;
        }
        int out = 0;
        max = 0;
        for (int i = 0; i < leftMax; i++) {
            if (height[i] > max) {
                max = height[i];
                out = i;
            }
        }
        leftMax = out;

        // printf("lsubtracted %d\n", (height[oldLeftMax] - height[leftMax]) * (oldLeftMax));
        volume -= (height[oldLeftMax] - height[leftMax]) * (oldLeftMax);
    }
    
    while (rightMax < heightSize) {
        int oldRightMax = rightMax;

        if (rightMax > heightSize - 2) {
            break;
        }
        int out = rightMax + 1;
        max = 0;
        for (int i = rightMax + 1; i < heightSize; i++) {
            if (height[i] > max) {
                max = height[i];
                out = i;
            }
        }
        rightMax = out;
        
        // printf("rsubtracted %d\n", (height[oldRightMax] - height[rightMax]) * (heightSize - oldRightMax - 1));
        volume -= (height[oldRightMax] - height[rightMax]) * (heightSize - oldRightMax - 1);
    }
    return volume;
}

char* largestOddNumber(char* num) {
    /* find first odd number from the right. Return the substring */
    int len = strlen(num);
    for (int i = len - 1; i > -1; i--) {
        if (num[i] % 2) {
            num[i + 1] = '\0';
            return num;
        }
    }
    return "";
}

int firstMissingPositive(int* nums, int numsSize) {
    int index = 0;
    int catch = nums[0];
    while (1) {
        /* swap */
        printf("%d %d\n", index, catch);
        if (catch < 0 || catch >= numsSize) {
            nums[0] = catch;
            index++;
            if (index >= numsSize) {
                break;
            }
            catch = nums[index];
        } else if (catch == index) {
            index++;
            if (index >= numsSize) {
                break;
            }
            catch = nums[index];
        } else {
            int temp = catch;
            if (nums[catch] == catch) {
                index++;
                if (index >= numsSize) {
                    break;
                }
                catch = nums[index];
            } else {
                index = catch;
                catch = nums[index];
                nums[index] = temp;
            }
        }
        
    }
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] != i) {
            if (nums[0] == i) {
                return i + 1;
            }
            return i;
        }
    }
    if (numsSize == 1 && nums[0] != 1) {
        return 1;
    }
    if (nums[numsSize - 1] + 1 == nums[0])
        return nums[0] + 1;
    return nums[numsSize - 1] + 1;
}

void itoa(int num, char* str) { // life is pain
    int index = 0;
    if (num < 0) {
        num *= -1;
        str[index] = '-';
        index++;
    }
    char flip[11];
    int next = 0;
    while (num > 0) {
        flip[next] = (num % 10) + 48;
        num /= 10;
        next++;
    }
    next--;
    for (; next > -1; next--) {
        str[index] = flip[next];
        index++;
    }
    str[index] = '\0';
}

int main(int argc, char *argv[]) {
    // int nums[6] = {1, 1, 1, 2, 2, 3};
    // int size;
    // int *freq = topKFrequent(nums, 6, 2, &size);
    // printf("[");
    // for (int i = 0; i < size; i++) {
    //     printf("%d, ", freq[i]);
    // }
    // printf("]\n");

    // int height[12] = {0,1,0,2,1,0,1,3,2,1,2,1};
    // int height2[3] = {0, 2, 0};
    // printf("trap: %d\n", trap(height, 12));
    // char test[] = "52"; // makes a copy
    // char *test2 = "52"; // does not make a copy
    // printf("%s\n", largestOddNumber(test));

    int nums[] = {-1,4,2,1,9,10};
    printf("first: %d\n", firstMissingPositive(nums, 6));
    printArray(nums, 6);
}