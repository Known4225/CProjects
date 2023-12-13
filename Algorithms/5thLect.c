/*
19.07.23

So here's how we've been solving recurrence relations to find the runtimes of algorithms
1. Recursion trees
2. Induction (impossible)
And today we're learning The Master Theorem.


Consider the recurrence relation:
T(n) = 3T(n / 4) + O(n^2)
What is the height of the corresponding recursion tree
(log4 n, log base 4 of n)
How many leaves does it have
3 ^ (log base 4 of n)

But we can't calculate the runtime without also knowing the cost of those non-leaf nodes
And the cost per level isn't constant

So the master theorem asks:
Does the leaf level contribute more cost,
or do the levels contribute more cost,
or are they equal?

with the form:
T(n) = aT(n / b) + f(n), where in the example T(n) = 3T(n / 4) + O(n^2), a = 3, b = 4, f(n) = O(n^2)
we ask if f(n) is greater than or less than n ^ (log base b of a)

case 1: the leaf cost (n ^ (log base b of a)) dominates -> leaf cost is the total runtime
case 2: the level cost f(n) dominates -> level cost is the total runtime
case 3: they are equal -> f(n) * (lg of n) ^ k of n is the total runtime, where k is ??? (still don't understand how to find k, but its probably 1 usually (???))

when we say "equal"
we also consider
O(n) = O(nlgn) AND O(n) = O(n(lgn) ^ 2)
BUT WHY?
who the fuck knows
just take the bigger one.
always.
if one is O(n) and one is O(nlgn) then the total runtime is O(nlgn), solved, not O(n * (lgn)^(k+1)) where k = 0, that makes no fucking sense

By the way, the master theorem isnt very master because it can only be used for things in the form
T(n) = aT(n / b) + f(n)

like T(n) = T(n - 1) + O(n) cannot have the master theorem applied
this one is presumably O(n^2)

or T(n) = T(n/3) + T((3n)/4) + O(n)
master theorem is fucking useless here

Another sorting algorithm? oh boy

Quicksort:
O(log n) space efficiency, but it is in place
O(n log n) average time
O(n^2) worst case time

I mean i made the visualisation, I understand how the algorithm works

but what about this whole space complexity thing

*/

#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[]) {
    double branchFactor;
    double dividor;
    printf("given a recurrence relation in the form T(n) = AT(n / B) + O(C)\n");
    printf("provide A and B:\n");
    printf("A: ");
    scanf("%lf", &branchFactor);
    printf("B: ");
    scanf("%lf", &dividor);
    printf("Number of leaves: %0.2lf ^ (log base %0.2lf of n)\n", branchFactor, dividor);
    printf("Which is about n ^ %0.2lf\n", (log(branchFactor) / log(dividor)));
    printf("Number of non-leaf nodes: \n");
}