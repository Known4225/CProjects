/*
Problem: Bowling pins
Given a list V
you can choose to knock over a pin, which gives you V[i] * V[i + 1] points
pins can only be knocked down once

give V = [-3, -4, -4, -3]
optimal is -3 * -4 + -4 * -3
greedy choice yields -4 * -4

so this problem cannot be solved by greedy algorithm (greedy choice counterexample)


Given an optimisation problem:
try

1. Exhaustive search

2. Greedy?
Greedy choice property - any optimal solution can be modified to contain the greedy choice
    - can be disproven by counterexample
optimal substructure - can be solved via recursion

3. Dynamic programming
locally optimal choices are not necessarily globally optimal

subproblem:
    we can think about the best store starting at the end.

so if we start at the end we can choose to knock the pin over or not. And it's just -3 so we choose to skip
then we consider starting at -4, with the list [-4, -3] so we choose to knock the pin over for a score of 12

what about [-4, -4, -3], the best score is 16

then [-3, -4, -4, -3] is EITHER 0 + 16 OR 12 + 12, we used the memoized values to "rebuild" our options



*/