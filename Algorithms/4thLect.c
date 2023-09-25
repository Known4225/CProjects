/*
14.09.23

Give two matrices

A = {a(1, 1) a(1, 2)
     a(2, 1) a(2, 2)}

B = {b(1, 1) b(1, 2)
     b(2, 1) b(2, 2)}

C = AB

what is c(1, 1)

c(1, 1) = a(1, 1) * b(1, 1) + a(1, 2) * b(2, 1)

for A and B as arbitrary square matrices
c(1, 1) = a(1, 1) * b(1, 1) + a(1, 2) * b(2, 1) + ... + a(1, n) * b(n, 1)

for (int k = 1; k < n; k++) {
    for (int j = 1; j < n; j++) {
        c(k, j) = 0;
        for (int i = 1; i < n; i++) {
            c(k, j) += a(k, i) * b(i, j)
        }
    }
}

What if we did a divide and conquer algorithm (Karastuba?)
The scalars a(1, 1) and etc are thought of as 1 x 1 matrices

multiply(A, B, C, n)
    if (n == 1) { // base case
        C(1, 1) = A(1, 1) * B(1, 1) + C(1, 1)
        return
    }
    partition A, B into 4 quadrants of half the dimensions
    multiply(A(1, 1), B(1, 1), C(1, 1), n/2)
    multiply(A(1, 2), (B(2, 1), C(1, 1), n/2)
    multiply(A(1, 1), (B(1, 2), C(1, 2), n/2)
    multiply(A(1, 2), (B(2, 2), C(1, 2), n/2)
    multiply(A(2, 1), (B(1, 1), C(2, 1), n/2)
    multiply(A(2, 2), (B(2, 1), C(2, 1), n/2)
    multiply(A(2, 1), (B(1, 2), C(2, 2), n/2)
    multiply(A(2, 2), (B(2, 2), C(2, 2), n/2)

runtime:
(cost to divide) + (cost to solve subproblems) + (cost to combine solutions)
partition(?) + 8T(n/2) + 0 (no cost to combine/add)
We assume partition is O(1)

T(n) = O(1) + 8T(n/2)
buildng the recursion tree allows us to see there are
lg n levels of the tree
each new level has 8 times the leaves as the last
so basically 8^levels is how many leaves at the bottom
8^lg(n) = n^lg(8) (logarithmic identity)
n^3
well this shit wasn't even better than the way more intuitive version what the fuck
i'm not implementing this shit

Strassen the gigachad that came up with the FFT multiplication algorithm was able
to do this matrix multiplication with 7 recursive calls instead of 8

which is n^2.807

but, much like the Schönhage–Strassen algorithm, 
the Strassen matrix multiplication algorithm is usually not recommended unless n is very large

then it's n^lg(7)

We are going to use a better way to calculate runtime
The substitution method:
Consider this runtime
T(n) = 2T(floor(n/2)) + O(n)
and we assume that a base case is reached at small values of n

This is very similar to the runtime of mergesort:
T(n) = 2T(n/2) + O(n), which equates to O(n lg n)
the only difference is the floor of n/2 instead of just n/2
which to me doesn't seem like it would make any runtime difference but we shall see

so instead of using a recursion tree, just use prior knowledge and induction

The Substitution Method:
Prove that there exists a constant C > 0 such that T(n) <= C(n lg n) for all values of n
aka prove T(n) = O(n lg n)

start with the inductive hypothesis:
suppose a C > 0 exists such that T(i) <= C(i lg i) for n(0) <= i <= n
where i is sufficiently far out but not as far as n is

T(n) <= 2c(floor(n/2) * lg(floor(n/2))) + O(n)
we can remove the floor, and then idk whats happening
if we remove the floor this inequality will still hold

idk mate this one seems tougher than most
hard as nails
brady

i mean if we remove the floor then we can basically be done no?
cuz then its just the same as mergesort
thats what I think at least

so the substitution method is basically:
make a guess as to what the runtime is
prove your guess is true using induction
base case is wishy washy
inductive case is super fucking confusing
idk whats happening
i hope i dont ever have to do this
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "include/random.h"

typedef struct {
    int rows;
    int cols;
    int **lookup;
} Matrix;

typedef struct {
    Matrix *A11;
    Matrix *A12;
    Matrix *A21;
    Matrix *A22;
    Matrix *B11;
    Matrix *B12;
    Matrix *B21;
    Matrix *B22;
    Matrix *C11;
    Matrix *C12;
    Matrix *C21;
    Matrix *C22;
} MatrixStorage;

Matrix *matrixInit(int rows, int cols) {
    Matrix *out = malloc(sizeof(Matrix));
    out -> rows = rows;
    out -> cols = cols;
    out -> lookup = malloc(sizeof(int *) * rows);
    for (int i = 0; i < rows; i++) {
        out -> lookup[i] = malloc(sizeof(int) * cols);
        for (int j = 0; j < cols; j++) {
            out -> lookup[i][j] = randomInt(0, rows * cols * 2);
        }
    }
    return out;
}

void printMat(Matrix *mat) {
    printf("[");
    for (int i = 0; i < mat -> rows; i++) {
        for (int j = 0; j < mat -> cols; j++) {
            if (j == mat -> cols - 1)
            printf("%d", mat -> lookup[i][j]);
            else
            printf("%d, ", mat -> lookup[i][j]);
        }
        if (i != mat -> rows - 1)
            printf("]\n[");
    }
    printf("]\n");
}

Matrix *matrixMulIter(Matrix *mat1, Matrix *mat2) { // assume both inputs are square
    Matrix *out = matrixInit(mat1 -> rows, mat1 -> rows);
    for (int i = 0; i < mat1 -> rows; i++) {
        for (int j = 0; j < mat1 -> rows; j++) {
            out -> lookup[i][j] = 0;
            for (int k = 0; k < mat1 -> rows; k++) {
                out -> lookup[i][j] += mat1 -> lookup[i][k] * mat2 -> lookup[k][j];
            }
        }
    }
    return out;
}

void matrixPad(MatrixStorage *glob) {

}

void matrixPartition(MatrixStorage *glob, Matrix *A, Matrix *B) {
    return;
}

void matrixMulRecEmb(MatrixStorage *glob, Matrix *C, Matrix *A, Matrix *B, int dimension) {
    if (dimension == 1) { // base case
        glob -> C11 -> lookup[0][0] = glob -> A11 -> lookup[1][1] * glob -> B11 -> lookup[0][0] + glob -> C11 -> lookup[0][0];
        return;
    }
    matrixPartition(glob, A, B); // partition A, B into 4 quadrants of half the dimensions
    matrixMulRecEmb(glob, glob -> A11, glob -> B11, glob -> C11, dimension / 2);
    matrixMulRecEmb(glob, glob -> A12, glob -> B21, glob -> C11, dimension / 2);
    matrixMulRecEmb(glob, glob -> A11, glob -> B12, glob -> C12, dimension / 2);
    matrixMulRecEmb(glob, glob -> A12, glob -> B22, glob -> C12, dimension / 2);
    matrixMulRecEmb(glob, glob -> A21, glob -> B11, glob -> C21, dimension / 2);
    matrixMulRecEmb(glob, glob -> A22, glob -> B21, glob -> C21, dimension / 2);
    matrixMulRecEmb(glob, glob -> A21, glob -> B12, glob -> C22, dimension / 2);
    matrixMulRecEmb(glob, glob -> A22, glob -> B22, glob -> C22, dimension / 2);
    return;
}

Matrix *matrixMulRec(Matrix *mat1, Matrix *mat2) { // assume both inputs are square
    MatrixStorage *glob;
    matrixPad(glob);
    Matrix *out = matrixInit(mat1 -> rows, mat1 -> rows);
    matrixMulRecEmb(glob, out, mat1, mat2, mat1 -> rows);
    return out;
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    Matrix *newMat1 = matrixInit(3, 3);
    Matrix *newMat2 = matrixInit(3, 3);
    Matrix *newProd = matrixMulIter(newMat1, newMat2);
    //Matrix *newProdRec = matrixMulRec(newMat1, newMat2);
    printf("A = \n");
    printMat(newMat1);
    printf("\nB = \n");
    printMat(newMat2);
    printf("\nA * B = \n");
    printMat(newProd);
    // printf("A * B = \n");
    // printMat(newProdRec);
}