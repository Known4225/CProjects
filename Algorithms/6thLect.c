/*
22.09.23:
Discussion
Master Theorem recap:
T(n) = aT(n/b) + f(n)
compare n ^ (log base b of a) with f(n)
whichever is bigger is the runtime

and if they are the same then the runtime is f(n lg n)

And that's the master theorem

Take note of case 2's careful wording:
If there exists a constant k >= 0, such that f(n) = O(n ^ (log base b of a) * (lgn)^k), then
T(n) = O(n ^ (log base b of a) * (lgn)^(k + 1))

there is some nuance where in order to confirm the runtime for case 3, a >= b. You cannot have more branches than dividing factors
*/

int main(int argc, char *argv[]) {

}