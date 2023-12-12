/* 
28.09.23
Max heap:
To turn an array into a heap, read from left to right and fill nodes into the tree structure

a max heap means that every parent is larger than both of its children

Heaps are good for priority queues because it's very easy to access the largest element (as long as you preserve the structure after popping)

To find children when first index = 1, multiply by 2 for the left child and multiply by 2 and add 1 for the right child

for first index = 0,
left = (n + 1) * 2 - 1
right = (n + 1) * 2

heaps dont have left right order, like theres no guarentees about whether the left or right child will be larger
The only property is that the parents have to be larger than the children
(in a min heap the parent has to be smaller than the children)

How to fix a broken heap?
You have to check recursively if each parent is larger than both of its children, and swap the larger of the children if they aren't
but that's not all, every time you swap you then need to check the node that you just swapped downward and check if it is larger than both of it's children
and if it isn't you need to do it again recursively until you don't need to swap again
but that's not all, you then need to go back to the original child you swapped upward and check the parent of the one, and keep moving
upward until you don't need to swap again (but every time you do swap you need to do the downward swap again)

The heapify algorithm:
Check the children,
if either child is bigger, swap the parent with the larger of the two children
then check the children of that one,
loop until you don't need to swap, or reach the bottom.
Also if there's only one child that's super annoying.

In sudo-code:
Heapify(array A, int i):
    if (A[(i + 1) * 2 - 1] > A[(i + 1) * 2] || (i + 2) * 2 >= A.size)
        biggerChild = (i + 1) * 2 - 1
    else
        biggerChild = (i + 1) * 2
    while (i < A.size && A[biggerChild] > A[i])
        temp = A[i]
        A[i] = A[biggerChild]
        A[biggerChild] = temp
        i = biggerChild
        if ((i + 1) * 2 < A.size)
            if (A[(i + 1) * 2 - 1] > A[(i + 1) * 2] || (i + 2) * 2 >= A.size)
                biggerChild = (i + 1) * 2 - 1
            else
                biggerChild = (i + 1) * 2

CreateHeapClassic(array A):
    for (int i = 0; i < A.size; i++)
        j = i
        while (A[(j - 1) / 2] < A[j])
            temp = A[j]
            A[j] = A[(j - 1) / 2]
            A[(j - 1) / 2] = A[i]
            j = (j - 1) / 2



One way to create a max heap is to call Heapify on every member of the array, starting at the END and going backward to the front

but heapsort employs a method where you only need to check the parent for every node in the array (and propagate upward)

I think they are computationally equivalent (O(n log n)), but I don't know
Because in the classic case, you have N nodes that you call log n parent checks on (at worst case)
and in the heapify one, you actually call heapify n / 2 times, and heapify is a log n algorithm
But heapify has two checks, the child and parent check
whereas the parent check has just one check, so the number of checks is exactly the same

CreateHeapWithHeapify(array A):
    for (int i = A.size / 2; i > -1; i++)
        Heapify(A, i)

runtime of Heapify: O(log n)
It's binary search basically

T(n) = T(2n/3) + O(1)

There are at most 2n/3 nodes in any subtree of an almost full tree - proof exists somewhere

master theorem, O(n ^ (log base 3/2 of 1)) == O(1)
thats weird
oh wait the master theorem uses k = 0
therefore lg^(k + 1) n = lg n
therefore the runtime is lg n
boom easy, not even a challenge, wasn't even confused once

So build max heap is O(n lg n)
cuz we do n / 2 * lg n
boom
easy
BUT............

Each node the cost of heapify is O(h), where h is the height of the node (leaves are 0, parents are 1, grandparents are 2, etc)
there are n / 2 level 0 nodes
n / 4 level 1 nodes
n / 8 level 2 nodes
etc
etc

so really lets take this sum
0 * (n / 2) + 1 * (n / 4) + 2 * (n / 8) + 4 * (n / 16) + etc
so that's just 1/4 for however many terms it takes for n / 2^x to be 1, or 0, idk
either way

summation from h = 0 to floor(lg n) of h * floor(n / 2^(h + 1))
rewrite it, and whatever, use an infinte series, and it's an inequality and math hilbert ramanujan etc
n * (1/2) / (1 - 1/2)^2
so it's actually O(n), that's fucking crazy
I dont know if i believe that
but i guess thats a proof
create max heap is O(n)

Heapsort is therefore O(n) + O(n lg n)

Heapsort is just create max heap then swap the ends and heapify until finished


*/

#include <stdio.h>

int main(int argc, char *argv[]) {
    
}