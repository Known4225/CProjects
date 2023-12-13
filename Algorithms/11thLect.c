/*
10.10.23:
Homework 5 is due Thursday
Homework 6 will not be due next week (yay)

Alright
Omega vs O vs Theta: What's the difference?
Omega is the lower bound (best case)
 - any algorithm that solves this problem cannot be faster than Omega, Omega usually applies to a problem not a specific algorithm
 - like "addition is Omega(n)" saying that the best possible algorithm for adding two numbers is Theta(n) (any algorithm for addition is at least Theta(n))
 - but it can apply to a specific algorithm like "Insertion sort is Omega(n)" saying insertion sort has a lower bound of Theta(n)
 - in this way it's the best case
O is the upper bound (worst case)
 - Insertion sort is O(n^2) because the worst case of insertion sort is Theta(n^2)
Theta is "runtime in general"
 - Theta is the "generic type". When talking about runtimes in the general case, we use theta. Like "this algorithm has a best case of Theta(n)"
 - It is the only one that can be used for average case, like quicksort is on average Theta(n lg n) (though most people just say average O(n lg n) because vernacular is different in casual and academic settings also you can't type theta without switching to the greek keyboard so it's way more convenient to just use O)

Selection in linear time:

Given a sorted array A

A[1] is the smallest element
A[n] is the largest element (where the size of the array is n)
A[3] is the third smallest element
A[floor((n + 1) / 2)] is the median (we use the lower median when n is even)
Okay so we can SELECT any of these quantities in Theta(1) time

But if A is not sorted...
Then to SELECT any of these quantities takes linear time

How to find the smallest element? Well that's easy
    FIND-MIN(A, n)
        min = 1
        for (i, 2 -> n)
            if (A[min] > A[i])
                min = i
        return min

How to find the largest element? Well that's easy
How to find the third smallest element? Well that's harder...
Here's how you do it:
find the minimum
remove it
find the minimum
remove it
find the minimum

boom. Done in Theta(n) lol cuz it was just FIND-MIN times 3
But obviously this isn't super ideal and also won't work when 3 is some fraction of n

What about the median?
It's kinda like quicksort
Randomised-Select:
suppose we want to find the index of the element that we would like to find (index meaning position in the sorted array)
So we partition the array with whatever as the pivot.
Now we know the position of our pivot in the array.
That was pretty easy

So if we were trying to find a specific index
and we chose the right pivot the first time then we did it.
And if we didn't we can just keep doing it until we do.
But like this has a worst case of Theta(n^2)

So instead we can use the information we gained to make a better guess. Like if the first pivot we chose
is more than the one we want, then we know we have to search the left half of the array.
And also if we only partition the half* of the array that we know the answer is in, we actually have less work to do
and also we can update the index we are looking for (to our true answer - the last pivot's, and we can also just ignore the half*
of the array we know the answer isn't in)
This still has a worst case of Theta(n^2), but on average it's actually Theta(n)
*won't actually be half, it could be anything from 1 to n - 1, which is unfortunate

RANDOMISED-SELECT(A, p, r, i) // A is array, p is left endpoint, r is length, and i is the index we're searching for
    if (p == r)
        return A[p]
    q = RANDOMISED-PARTITION(A, p, r) // q is the index of the pivot element (when assuming p is 1)
    k = q - p + 1 // k is the index of the pivot element (in our starting A)
    if (k == i)
        return A[q]
    elif i < k // this means that the answer is to our left
        RANDOMISED-SELECT(A, p, q - 1, i) // search from p up to q - 1
    else // this means that the answer is to our right
        RANDOMISED-SELECT(A, q + 1, r, i - k) // search from q + 1 up to r

To use:
RANDOMISED-SELECT(A, 1, n, i) // where n is length of A, and i is index you wanna find (so for median it's floor((n + 1) / 2))

So what's the runtime
It's worst case is Theta(n^2)
But the average is Theta(n)

Cool.

T(n) = (3n)/4 * O(n) = O(n) via master theorem (log base 4 of 3 is less than 1)

But there is one with a worst case of O(n)
Here it is:
Throw away the X < 5 smallest elements of A until the length of A is a multiple of 5 (???) (remove up to 4 elements)
Imagine dividing A into groups of 5 and sort in place within those groups (???)
A = 9 8 7 100 52 35 40 3 7 9 11 201 0 3 15
first pass moves to
A = 0 8 7 9 52 35 9 3 7 40 11 201 100 3 15
second pass moves to
A = 0 3 7 9 3 35 9 8 7 40 11 201 100 52 15
third pass moves to
A = 0 3 7 9 3 7 9 8 15 40 11 35 100 52 201
Then we know that the median for each group is in the middle 5
so we find each of those medians (there are 3 in this case cuz we had 3 passes)
and then we find the median of those 3
and then we use that thing we just found as the partition for not-so-randomised-anymore partition (???)
this will partition the array well
and then we have the same issue as random select, so we'll need to partition again
and then every time we do this we have to do this shit again are you joking
but this technically guarentees O(n), even though like this is batshit insane
*/

#include <stdio.h>

void printArray(int *A) {
    printf("A: [");
    for (int i = 0; i < 8; i++) {
        printf("%d, ", A[i]);
    }
    printf("]\n");
}

int randomisedPartition(int *A, int p, int r) {
    printArray(A);
    // the "random" pivot it chooses is always the middle
    int pivot = (p + r - 1) / 2; // choose pivot
    // printf("pivot: A[%d] = %d\n", pivot, A[pivot]);
    int swap = A[pivot]; // swap the pivot and the 0th element
    A[pivot] = A[p];
    A[p] = swap;
    printArray(A);
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
                printf("inc\n");
                ptr++;
            }
        }
        printArray(A);
    }
    printf("%d %d\n", p, ptr - 1);
    if (ptr != p) {
        swap = A[p]; // swap the 0th and ptr - 1
        A[p] = A[ptr - 1];
        A[ptr - 1] = swap;
    }
    printf("A[%d] is %d\n", ptr - 1, A[ptr - 1]);
    return ptr - 1;
}

int randomisedSelect(int *A, int p, int r, int i) {
    if (p == r)
        return A[p];
    int q = randomisedPartition(A, p, r);
    int k = q - p + 0;
    if (k == i) {
        return A[q];
    } else if (i < k) {
        randomisedSelect(A, p, q, i);
    } else {
        randomisedSelect(A, q + 2, r, i - k);
    }
}

int main(int argc, char *argv[]) {
    int A[8] = {6, 4, 3, 9, 12, 2, 5, 7};
    // {2, 3, 4, 5, 6, 7, 9, 12}
    // randomisedPartition(A, 3, 8);
    printArray(A);
    int index = 3;
    int value = randomisedSelect(A, 0, 8, index);
    printf("The value of index %d of A is %d\n", index, value);
    // it doesn't work but I don't know why
}