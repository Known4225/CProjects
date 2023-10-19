/*
12.10.23:
Midterm tuesday:


Back to RANDOMISED-SELECT and its brother
SELECT.

SELECT(A, p, r, i)
while (r - p + 1) mod 5 != 0
    for (int j = p + 1; j < r; j++) // this eliminates up to 4 of the smallest elements
        if (A[p] > A[j])
            swap A[p], A[j]
        if (i == 1)
            return A[p]
        p += 1
        i -= 1
    
    g = (r - p + 1) / s // number of groups of 5
    for (int j = p; j < p + g - 1; j++)
        sort(A[j], A[j + g], A[j + 2g], A[j + 3g], A[j + 4g]) // in place sort
    y = SELECT(A, p + 2g, p + 3g - 1, ceil(g / 2))
    q = PARTITION-AROUND(A, p, r, x)
    k = q - p + 1
    if (i == k)
        return A[g]
    else if (i < k)
        return SELECT(A, p, q - 1, i)
    else
        return SELECT(A, q + 1, r, i - k)

Basically it's randomised select but our pivot is always decent.
We find a decent pivot by sorting 5 of the elements at a time and do that n / 5 times which is somehow still O(n)
and then we find the medians in the middle of the array and take the median of that and use it as the pivot
This ensures a decent pivot and therefore ensures an O(n) runtime

Because SELECT is O(n), we can use it to find a median to use it as a pivot in quicksort to ensure O(n lg n)
but nobody does that shit because in practice it's not faster

Disjoint set forest:
What is a disjoint set?
It's two or more sets that have no overlapping elements

With disjoint sets you can pick a representative of the set to represent the set
you can use it as an identifier of the set because theres no overlap
so you can in a way equate the representative with the set as a whole

theres also a sense in which all members of the set are equivalant to each other

Disjoint set forest - disjoint sets as trees
We want to do these things (fast):
Make a set
Find a set (From an element, find the representative of the set)
Unionize sets (combine sets)

Disjoint set forest has the root node as the representative
and all the children have pointers to their parents, and the root has a pointer to itself
This tree doesn't have to be binary btw

and basically when you want to unionize you just take the root of set 2 and have it point to the root of the set 1's tree instead of itself
or you take the root of set 1's tree and have it point to the root of set 2's tree. Probably just do whichever one has the smaller tree (max dist should be minimized)

union-by-rank:
each tree (set) has a rank which is the max distance to a leaf and we use that to determine which one is the smaller one
so they all start with a rank of 0 and for every time you unionize it grows by 1
and then you wanna unionize a tree of 1 and 1, then you get a tree with rank 2
then you wanna take trees of rank 2 and 1 and unionize? Well you just get rank 2 again because you take the min_rank(tree1, tree2) + 1
is the rank of the new tree as long as you use the min_rank(tree1, tree2) to change the pointer of the one with the min rank. So that's pretty cool

Okay now how do we find things?
Like if I have an element how do I find what set it's in?

well it has a pointer to some object and you just keep moving until the pointer points to itself. That's the set that the node belongs to
so thats pretty easy

but there's a better way:
as you move up the parents you can just be moving the original node's pointer up and up until it gets to the top.
actually you can do that to every object you find along the way.

it's a bit of a cleanup operation every time you find.
This makes it faster when you do subsequent calls with any of those previous parents

This is called path compression

check it out:
FIND-SET(x)
    if (x.ptr != x) { // check if parent
        x.ptr = FIND-SET(x.ptr);
    }
    return x; // return root (will be root cuz we just changed it)

bloody simple
*/

#include <stdio.h>

void printArray(int *A) {
    printf("A: [");
    for (int i = 0; i < 8; i++) {
        printf("%d, ", A[i]);
    }
    printf("]\n");
}

int randomisedPartition(int *A, int p, int r) { // A is array, p is start, r is end (+1)
    // the "random" pivot it chooses is always the middle
    int pivot = (p + r - 1) / 2; // choose pivot
    int swap = A[pivot]; // swap the pivot and the 0th element
    A[pivot] = A[p];
    A[p] = swap;
    int ptr = p; // the pointer keeps track of where the boundry is between less and more than the pivot
    for (int i = p + 1; i < r; i++) {
        if (A[i] > A[p]) { // is A[i] more than the original pivot selection
            if (ptr == p)
                ptr = i;
        } else {
            if (ptr != p) {
                swap = A[ptr]; // swap ptr and i
                A[ptr] = A[i];
                A[i] = swap;
                ptr++;
            }
            
        }
    }
    if (ptr == p)
        ptr = r;
    swap = A[p]; // swap the 0th and ptr - 1
    A[p] = A[ptr - 1];
    A[ptr - 1] = swap;
    return ptr - 1;
}

int randomisedSelect(int *A, int p, int r, int i) { // A is array, p is start of array, r is end of array (+1), i is which one you wanna find
    if (p == r) // it almost spells April
        return A[p];
    int q = randomisedPartition(A, p, r);
    if (q == i) {
        return A[q];
    } else if (i > q) {
        // printf("top case %d %d %d\n", q + 1, r, i);
        randomisedSelect(A, q + 1, r, i);
    } else {
        // printf("bottom case %d %d %d\n", p, q, i);
        randomisedSelect(A, p, q, i);
    }
}

int megaMedian(int *A, int length) {
    int median = randomisedSelect(A, 0, length, length / 2);
    printf("The median is %d\n", median);
    return median;
}

int main(int argc, char *argv[]) {
    int A[17] = {6, 4, 3, 9, 12, 2, 5, 7, 18, 255, 93, 13, 1, 45, 32, 899, 8};
    // {2, 3, 4, 5, 6, 7, 9, 12}
    for (int i = 0; i < 17; i++) {
        int index = i;
        int value = randomisedSelect(A, 0, 17, index);
        printf("The value of index %d of A is %d\n", index, value);
    }
    megaMedian(A, 17);
    // lets go it finally fucking works that took way longer than it should've
}