/*
What will be on the midterm
Look at beginning exercises on the chapters covered
Question: Can you in technical detail describe how an algorithm works
    That's many of the true/false questions
Can you solve a basic recurrence relation?
Can you give a runtime?

Your ability to apply and understand the algorithms in a specific context
    Comparing algorithms and data structures
        Heap vs BST vs DSF?
        Greedy vs dynamic vs divide and conquer?
    Would a greedy algorithm produce the optimal solution in this case?

Can you write algorithms
    Write an algorithm for a novel problem
    Should be related to what you've seen
        Exhaustive search
        Divide and conquer (probably not on test)
        Greedy
        Dynamic (iterative or recursive)
        Similar to an existing algorithm

Content:
SELECT(A, k) algorithm (selects the kth largest item in a list)
Disjoint set forests
Binary search trees
Greedy algorithms
Dynamic programming

Matrix chain parenthesisation
A1 * A2 * A3 * ... * An
give a list of dimensions of length n + 1
A1 = p[1] * p[2]
A2 = p[2] * p[3]
An = p[n] * p[n + 1]

put parenthesis in so the number of multiplications in minimised

subproblem:
given a subset of the matrices, find the optimal parenthesisation of them

In an optimal solution from 1 to n there occurs a "split point" k which divides the chain
into two parts optimally for multiplations

then our problem has been reduced to a divide and conquer
We find k in 1-n, then we find k' in 1-k and in k-n
and we keep splitting until they are all in groups of one (i == j)

so we can try each of the 1-n points of k
calculate the number of multiplications using:
M[i, j] = M[i, k] + M[k + 1, j] + p[i - 1] * p[k] * p[j]
so given i and j, we can try each value of k between them to find the minimum for M[i, j]

so min(i, j) = if i == j then 0 else min(min(i, k) + min(k + 1, j) + p[i - 1] * p[k] * p[j])

so we need to solve the subproblems FIRST

which means we have a lot of duplicates

lets create the recursive definition first


*/
#include <stdio.h>
#include <stdlib.h>

int callsOrig = 0;
int callsDyn = 0;
int callsOut = 0;

int matrix_parenthesises(int *P, int i, int j) {
    callsOrig++;
    // printf("iter %d %d\n", i, j);
    if (i == j) {
        return 0;
    }
    unsigned long long min = -1;
    for (int k = i; k < j; k++) {
        unsigned long long test = matrix_parenthesises(P, i, k) + matrix_parenthesises(P, k + 1, j) + P[i - 1] * P[k] * P[j];
        if (test < min) {
            min = test;
        }
    }
    return min;
}

int matrix_parenthesises_dynamic(int *P, int i, int j, int **saved) {
    callsDyn++;
    // printf("saved[%d][%d] = %d\n", i - 1, j - 1, saved[i - 1][j - 1]);
    if (i == j) {
        return 0;
    }
    if (saved[i - 1][j - 1] != -1) {
        return saved[i - 1][j - 1];
    }
    unsigned long long min = -1;
    for (int k = i; k < j; k++) {
        unsigned long long test = matrix_parenthesises_dynamic(P, i, k, saved) + matrix_parenthesises_dynamic(P, k + 1, j, saved) + P[i - 1] * P[k] * P[j];
        if (test < min) {
            min = test;
        }
    }
    saved[i - 1][j - 1] = min;
    return min;
}

int matrix_parenthesises_output(int *P, int i, int j, int **saved, int **out) {
    callsOut++;
    if (i == j) {
        return 0;
    }
    if (saved[i - 1][j - 1] != -1) {
        return saved[i - 1][j - 1];
    }
    int minK = 0;
    unsigned long long min = -1;
    for (int k = i; k < j; k++) {
        unsigned long long test = matrix_parenthesises_output(P, i, k, saved, out) + matrix_parenthesises_output(P, k + 1, j, saved, out) + P[i - 1] * P[k] * P[j];
        if (test < min) {
            minK = k;
            min = test;
        }
    }
    saved[i - 1][j - 1] = min;
    out[i - 1][j - 1] = minK;
    return min;
}

int **init(int size) {
    int **S = malloc(sizeof(int *) * size);
    for (int i = 0; i < size; i++) {
        S[i] = malloc(sizeof(int) * size);
        for (int j = 0; j < size; j++) {
            S[i][j] = -1;
        }
    }
    return S;
}

void freeList(int **S) {
    for (int i = 0; i < 4; i++) {
        free(S[i]);
    }
    free(S);
}

void matrix_print_parenthesises(int **O, int i, int j) {
    if (i == j) {
        printf("A[%d]", i);
    } else {
        printf("(");
        matrix_print_parenthesises(O, i, O[i - 1][j - 1]);
        matrix_print_parenthesises(O, O[i - 1][j - 1] + 1, j);
        printf(")");
    }
}

int main(int argc, char *argv[]) {
    // int P[5] = {40, 20, 30, 10, 30};
    int P[6] = {9, 76, 64, 21, 97, 60};
    int res = matrix_parenthesises(P, 1, 5);
    printf("result: %d in %d calls\n", res, callsOrig);
    int **S = init(5);
    res = matrix_parenthesises_dynamic(P, 1, 5, S);
    printf("result_dynamic: %d in %d calls\n", res, callsDyn);
    
    // freeList(S);
    S = init(6);
    int **O = init(6);
    matrix_parenthesises_output(P, 1, 6, S, O);
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (O[i][j] == -1) {
                printf("0");
            } else {
                printf("%d", O[i][j]);
            }
        }
        printf("\n");
    }
    matrix_print_parenthesises(O, 1, 6);
    printf("\n");
}