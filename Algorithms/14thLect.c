/*
19.10.23:

Binary search trees (BST)

Next week:
Red-black trees (briefly)
Starting greedy algorithms

Binary search trees
so it's a tree where the left child of a node is greater than or equal to the node (sometimes just greater than)
and the right child of a node is less than or equal to that node (sometimes just less than)

kinda wacky, but it works well enough especially for binary search.

So if your data is set up in a binary tree, you can easily do binary search by just asking:
is it greater or less than the current node?
Greater? Go right
Less? Go left
then just keep going until you find it
and if you hit a NULL then it's not there


A binary tree is considered to be "loosely sorted"
The BST property:

eh whatever imma just program it
how to print it?

           0
          / \
         0   0
        / \ / \
       0  0 0  0
      / \/ \ 
This seems ill-advised

          - 0
         /
143 154
        

        ----- 120 -----
        /             \
      124             900 
    /     \         /     \
  154     124     594     203
  / \     / \     / \     / \
142 124 165 123 142 124 165 123

we need some kind of pascal's numbers
the bottom has margins of 1 and bracket spacing of 3
then margins of 5
then 13

so it starts as 1
goes up by 4
then goes up by 8
then goes up by 16
etc

brackets starts at 3
goes up by 4
then goes up 8
then goes up by 16



*/
#include <stdio.h>
#include <stdlib.h>

struct Node;

typedef struct Node BSTNode;

struct Node {
    int value;
    BSTNode *left;
    BSTNode *right;
};

BSTNode *createBST(int *array, int length) { // creates a BST out of the array
    BSTNode *firstNode = malloc(sizeof(BSTNode));
    firstNode -> value = array[0];
    firstNode -> left = NULL;
    firstNode -> right = NULL;
    for (int i = 1; i < length; i++) {
        BSTNode *newNode = malloc(sizeof(BSTNode));
        newNode -> value = array[i];
        newNode -> left = NULL;
        newNode -> right = NULL;
        BSTNode *findNode = NULL;
        BSTNode *dummyNode = firstNode;
        while (dummyNode != NULL) {
            findNode = dummyNode;
            if (array[i] > dummyNode -> value) {
                dummyNode = dummyNode -> right;
            } else {
                dummyNode = dummyNode -> left;
            }
        }
        if (array[i] > findNode -> value) {
            findNode -> right = newNode;
        } else {
            findNode -> left = newNode;
        }
    }
    return firstNode;
}

int findHeightRec(BSTNode *head, int currentHeight) {
    if (head == NULL) {
        return currentHeight;
    }
    int leftHeight = findHeightRec(head -> left, currentHeight + 1);
    int rightHeight = findHeightRec(head -> right, currentHeight + 1);
    if (leftHeight > rightHeight) {
        return leftHeight;
    } else {
        return rightHeight;
    }
}

int findHeight(BSTNode *head) { // O(?), finds the height of a tree
    return findHeightRec(head, 0);
}

int pow2(int power) {
    int out = 1;
    for (int i = 0; i < power; i++) {
        out *= 2;
    }
    return out;
}

int query(BSTNode *head, int heightOfQuery, int query) {
    // we can use the binary value of the query to traverse the tree, eg 011 = go left, go right, go right
    BSTNode *outNode = head;
    unsigned int mask = 1;
    mask <<= heightOfQuery - 2;
    for (int i = 0; i < heightOfQuery - 1; i++) {
        if (outNode == NULL) {
            return -2958285;
        }
        if (query & mask) {
            outNode = outNode -> right;
        } else {
            outNode = outNode -> left;
        }
        mask >>= 1;
    }
    if (outNode == NULL) {
        return -2958285;
    }  
    return outNode -> value;
}

void printCenteredInt(int pr) {
    if (pr < 10) {
        printf(" %d ", pr);
    } else if (pr < 100) {
        printf("%d ", pr);
    } else if (pr > 999) {
        printf("999");
    } else {
        printf("%d", pr);
    }
}

void printBST(BSTNode *head, char renderAll) {
    // printf("%3d\n", 1);
    int height = findHeight(head);
    printf("height: %d\n", height);
    int marginLeft = 0;
    int marginRight = 1;
    int bracketLeft = 2;
    int bracketMid = 1;
    int bracketRight = 3;
    // do the pascal power of 2 algorithm
    for (int k = 0; k < height; k++) {
        int geniusLen = pow2(height - (k + 1));
        int *genius = malloc(sizeof(int) * geniusLen); // genius plan
        for (int i = 0; i < geniusLen; i++) {
            // -2958285; // reserved value
            genius[i] = query(head, height - k, i);
        }
        for (int i = 0; i < geniusLen; i++) {
            for (int j = 0; j < marginLeft; j++) {
                printf(" ");
            }
            if (genius[i] == -2958285) {
                if (renderAll && 0) { // disabled feature because it looks bad
                    printf("nil");
                } else {
                    printf("   ");
                }
            } else {
                printCenteredInt(genius[i]);
            }
            for (int j = 0; j < marginRight; j++) {
                printf(" ");
            }
        }
        printf("\n");
        for (int i = 0; i < geniusLen / 2; i++) {
            for (int j = 0; j < bracketLeft; j++) {
                printf(" ");
            }
            if (genius[i * 2] != -2958285 || renderAll) {
            printf("\\");
            } else {
                printf(" ");
            }
            for (int j = 0; j < bracketMid; j++) {
                printf(" ");
            }
            if (genius[i * 2 + 1] != -2958285 || renderAll) {
            printf("/");
            } else {
                printf(" ");
            }
            for (int j = 0; j < bracketRight; j++) {
                printf(" ");
            }
        }
        printf("\n");
        marginLeft += pow2(k + 1);
        marginRight += pow2(k + 1);
        bracketLeft += pow2(k + 1);
        bracketMid += pow2(k + 2);
        bracketRight += pow2(k + 1);
    }
}

void inOrderPrint(BSTNode *head) { // this is O(n) and Omega(n) (trust)
    if (head != NULL) {
        inOrderPrint(head -> left);
        printf("%d, ", head -> value);
        inOrderPrint(head -> right);
    }
}
// we can do tree traversal in linear time

char treeSearch(BSTNode *head, int searchFor) { // O(h) (where h is the height of the tree), searches for an element in a tree (sometimes trees are just linked lists)
    if (head == NULL) {
        return 0;
    }
    if (searchFor == head -> value) {
        return 1;
    }
    if (searchFor > head -> value) {
        treeSearch(head -> right, searchFor);
    } else {
        treeSearch(head -> left, searchFor);
    }
}

int main(int argc, char *argv[]) {
    int length = 14;
    int array[14] = {60, 5, 2, 80, 56, 17, 632, 84, 91, 39, 12, 72, 34, 89};
    
    BSTNode *head = createBST(array, length);
    char drawAll = 0;
    if (argc > 1) {
        if (argv[1][0] == '1') {
            drawAll = 1;
        }
    }
    printBST(head, drawAll);
    inOrderPrint(head);
    printf("\n");
    int find = 89;
    if (treeSearch(head, find)) {
        printf("found %d\n", find);
    } else {
        printf("%d not found\n", find);
    }
    find = 10;
    if (treeSearch(head, find)) {
        printf("found %d\n", find);
    } else {
        printf("%d not found\n", find);
    }
}
