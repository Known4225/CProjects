/*
3.10.23:
What to know for test (thursday)
1. Basic understanding of algorithms (what does quicksort do?)
2. Basic runtime analysis of algorithms (what is the runtime of heapsort compared to insertion sort?)
3. Recurrence relations, solving and producing for novel algorithms (master theorem)
4. Create a novel algorithm to solve a problem ()
 - show correctness
 - evaluate runtime

Binary heap:
 - Data structure
  - Nearly complete binary tree
   - Loosely sorted
    - Each parent is greater than both of their children
     - max heap property:
        Every subtree is also a max heap

It's very easy to get the max element of a binary heap, so it's often used for priority queues (queues where the max value is at the top)
Heapify - O(lg n) this will take an item at the top and put it in the correct place (comparison of children)
Create max heap: O(n) this will add elements to the heap one by one, checking if the parent is greater and swapping if it is
Heapsort - sorts using heaps O(n lg n)

Priority queues:
lg n adding (put element at the bottom and then swap with parents until steady state, it's like heapsort when you add to heap)
lg n removing (calls heapify) (it's like heapsort when you remove a value)

Comparison sorts have a worst case -O-(n lg n)
Counting sorts can have worst cases of O(n)
Also best cases can be O(n), like insertion sort

*/
#include <stdio.h>
/* polymorphism in C */

typedef struct {
    char type; // specifies which inherited class this is (0 - parent, 1 - childClass1, etc)
    int x1;
    int y1;
    int x2;
    int y2;
    int y3;
} parentClass;

typedef struct {
    /* parent data */
    parentClass inherit; // so you can cast a childClass1 struct to a parentClass struct and it will just work

    /* child data */
    int childX;
    int childY;
} childClass1;

void parentConstruct(parentClass *selfp) { // constructs the parent
    parentClass self = *selfp;
    self.type = 0; // specifies that this is a parent
    self.x1 = 6;
    self.y1 = 9;
    self.x2 = 4;
    self.y2 = 7;
    *selfp = self;
}

void child1Construct(childClass1 *selfp, int childX, int childY) { // constructs child1
    childClass1 self = *selfp;
    self.inherit.type = 1; // specifies that this is child1
    self.inherit.x1 = 16;
    self.inherit.y1 = 19;
    self.inherit.x2 = 14;
    self.inherit.y2 = 17;
    self.childX = childX;
    self.childY = childY;
    *selfp = self;
}

int parentFunction1(parentClass *selfp) { // computes distance^2 between the two coordinates in parentClass
    parentClass self = *selfp;
    int out = (self.x2 - self.x1) * (self.x2 - self.x1) + (self.y2 - self.y1) * (self.y2 - self.y1);
    *selfp = self;
    return out;
}

void parentFunction2(parentClass *selfp) { // sets all parent fields to 1
    parentClass self = *selfp;
    self.x1 = 1;
    self.y1 = 1;
    self.x2 = 1;
    self.y2 = 1;
    *selfp = self;
}

void polymorphicFunction1(parentClass *selfp) { // this function is one who's definition differs in child classes (virtual, overridden)
    if (selfp -> type == 0) { // parent
        selfp -> x1 = 4;
        selfp -> y1 = 3;
        selfp -> x2 = 2;
        selfp -> y2 = 1;
    } else if (selfp -> type == 1) { // child1
        childClass1 *child1Self = (childClass1 *) selfp;
        selfp -> x1 = 1;
        selfp -> y1 = 2;
        selfp -> x2 = 3;
        selfp -> y2 = 4;
        child1Self -> childX = 5;
        child1Self -> childY = 6;
    } else if (selfp -> type == 2) { // child2

    }
    
}

void printParent(parentClass *selfp) {
    parentClass self = *selfp;
    if (selfp -> type == 0) {
        printf("parentObject: ");
    } else if (selfp -> type == 1) {
        printf("child1Object: ");
    }
    printf("x1: %d, ", self.x1);
    printf("y1: %d, ", self.y1);
    printf("x2: %d, ", self.x2);
    if (self.type == 0)
        printf("y2: %d\n", self.y2);
    else
        printf("y2: %d, ", self.y2);
}

void printChild1(childClass1 *selfp) {
    printParent((parentClass *) selfp);
    childClass1 self = *selfp;
    printf("childX: %d, ", self.childX);
    printf("childY: %d\n", self.childY);
}

int main(int argc, char *argv) {
    parentClass parentTest1;
    childClass1 childTest1;
    printf("Contsructor:\n");
    parentConstruct(&parentTest1);
    child1Construct(&childTest1, 0, 0);
    printParent(&parentTest1);
    printChild1(&childTest1);
    printf("\nCompute Distance^2:\n");
    printf("parent: %d\n", parentFunction1(&parentTest1));
    printf("child: %d\n", parentFunction1((parentClass *) &childTest1));

    printf("\nSet all parent fields to 1:\n");
    parentFunction2(&parentTest1);
    parentFunction2((parentClass *) &childTest1);

    printParent(&parentTest1);
    printChild1(&childTest1);

    printf("\nPolymorphic Function differs between parent and child:\n");
    polymorphicFunction1(&parentTest1);
    polymorphicFunction1((parentClass *) &childTest1);

    printParent(&parentTest1);
    printChild1(&childTest1);
}