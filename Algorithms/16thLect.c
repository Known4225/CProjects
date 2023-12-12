/*
2.11.23:
Problem:
Given a list of non-negative integers. Rearrange the digits so they form the largest number

Examples:
[10, 2] -> 210

[3, 30, 34, 5, 9] -> 9543330

so this actually isn't very hard, all you do is parse the digits individually and simply sort them biggest to smallest

so for i in list:
    for digit in i
        newList.append(digit)

then sort(newList) (biggest to smallest)
newList.toString()

This is a GREEDY ALGORITHM, because it sorts simply from biggest to smallest

TLDR of lecture:
bottom up approach mutates a recursive solution to make it memoised
the iterative approach just rewrites the solution iteratively with memoisation

if you already have a working recursive solution you can use the bottom up approach fairly easily
if you're a real programmer you use the iterative approach
*/

#include "include/list.h"

struct huffNode;
typedef struct huffNode huff;

struct huffNode { // a huffman node
    int freq;
    list_t *symbols;
    huff *left;
    huff *right;
};

huff *nodeCopy(huff *node) {
    huff *out = malloc(sizeof(huff));
    out -> freq = node -> freq;
    out -> symbols = list_init();
    list_copy(node -> symbols, out -> symbols);
    out -> left = node -> left;
    out -> right = node -> right;
    return out;
}

void printNode(huff *node) {
    printf("------------------\n");
    printf("freq: %d\n", node -> freq);
    printf("symbols: ");
    list_print(node -> symbols);
    // printf("------------------\n");
}

list_t *huffmanCreateNodes(list_t *frequencyTable) {
    list_t *out = list_init();
    for (int i = 0; i < frequencyTable -> length; i += 2) {
        huff *newNode = malloc(sizeof(huff));
        newNode -> symbols = list_init();
        list_append(newNode -> symbols, (unitype) frequencyTable -> data[i].c, 'c');
        newNode -> freq = frequencyTable -> data[i + 1].i;
        newNode -> left = NULL;
        newNode -> right = NULL;
        list_append(out, (unitype) (void *) newNode, 'p');
    }
    return out;
}

huff *huffmanBuildTree(list_t *nodes) {
    // for (int i = 0; i < nodes -> length; i++) {
    //     printNode((huff *) nodes -> data[i].p);
    // }
    while (nodes -> length > 1) {
        // step 1: find smallest two nodes
        int minDex = 0;
        huff *min = (huff *) nodes -> data[0].p;
        for (int i = 0; i < nodes -> length; i++) {
            if (((huff *) nodes -> data[i].p) -> freq < min -> freq) {
                minDex = i;
                min = (huff *) nodes -> data[i].p;
            }
        }
        huff *smallest = min;
        list_delete_no_free(nodes, minDex);
        minDex = 0;
        min = (huff *) nodes -> data[0].p;
        for (int i = 0; i < nodes -> length; i++) {
            if (((huff *) nodes -> data[i].p) -> freq < min -> freq) {
                minDex = i;
                min = (huff *) nodes -> data[i].p;
            }
        }
        huff *secondSmallest = min;
        list_delete_no_free(nodes, minDex);
        // step 2: create parent node
        huff *newNode = malloc(sizeof(huff));
        newNode -> symbols = list_init();
        list_copy(smallest -> symbols, newNode -> symbols);
        for (int i = 0; i < secondSmallest -> symbols -> length; i++) {
            list_append(newNode -> symbols, secondSmallest -> symbols -> data[i], 'c');
        }
        newNode -> freq = smallest -> freq + secondSmallest -> freq;
        newNode -> left = smallest;
        newNode -> right = secondSmallest;
        printNode(newNode);
        list_append(nodes, (unitype) (void *) newNode, 'p');
    }
    return (huff *) nodes -> data[0].p;
}

int main(int argc, char *argv[]) {
    char filename[128] = "huffmanTest.txt";
    if (argc == 2) {
        strcpy(filename, argv[1]);
    }
    list_t *frequencyTable = list_init();
    FILE *fp = fopen(filename, "r");
    char read;
    while (fscanf(fp, "%c", &read) != EOF) {
        if (list_count_type_check(frequencyTable, (unitype) read, 'c') > 0) {
            frequencyTable -> data[list_index_type_check(frequencyTable, (unitype) read, 'c') + 1].i += 1;
        } else {
            // printf("%c\n", read);
            list_append(frequencyTable, (unitype) read, 'c');
            list_append(frequencyTable, (unitype) 1, 'i');
        }
    }
    list_print(frequencyTable);
    /* frequency table contains every ASCII character followed by an integer of the frequency */

    list_t *nodes = huffmanCreateNodes(frequencyTable);
    huff *head = huffmanBuildTree(nodes);
    printf("------------------\n");

    // head is now the head of the huffman tree
    // now we need to encode each of the characters in the file
    // im going to do this with a table

    
    list_t *encodeTable = list_init();
    for (int i = 0; i < head -> symbols -> length; i++) { // this contains all the characters in the file
        list_t *binary = list_init();
        int height = 1;
        char toFind = head -> symbols -> data[i].c;
        list_append(encodeTable, head -> symbols -> data[i], 'c');
        huff *travel = head;
        char leftRight = 0;
        while (travel -> symbols -> length > 1) {
            leftRight = 0;
            for (int j = 0; j < travel -> right -> symbols -> length; j++) {
                if (travel -> right -> symbols -> data[j].c == toFind) {
                    leftRight = 1;
                    break;
                }
            }
            if (leftRight) {
                travel = travel -> right;
                list_append(binary, (unitype) '1', 'c');
            } else {
                travel = travel -> left;
                list_append(binary, (unitype) '0', 'c');
            }
            height <<= 1;
        }
        list_append(encodeTable, (unitype) binary, 'r');
    }
    list_print(encodeTable);
    // now encoding
    list_t *originalBinary = list_init();
    list_t *huffmanBinary = list_init();
    int huffmanLength = 0;
    rewind(fp);
    while (fscanf(fp, "%c", &read) != EOF) {
        list_append(originalBinary, (unitype) list_init(), 'r');
        int mask = 128;
        for (int i = 0; i < 8; i++) {
            if (read & mask) {
                list_append(originalBinary -> data[originalBinary -> length - 1].r, (unitype) '1', 'c');
            } else {
                list_append(originalBinary -> data[originalBinary -> length - 1].r, (unitype) '0', 'c');
            }
            mask >>= 1;
        }
        list_t *coded = encodeTable -> data[list_index_type_check(encodeTable, (unitype) read, 'c') + 1].r;
        list_append(huffmanBinary, (unitype) list_init(), 'r');
        huffmanLength += coded -> length;
        for (int i = 0; i < coded -> length; i++) {
            list_append(huffmanBinary -> data[huffmanBinary -> length - 1].r, coded -> data[i], 'c');
        }
    }
    printf("\nOriginal Binary (length %d): ", originalBinary -> length * 8);
    list_print(originalBinary);
    printf("\nHuffman Binary (length %d): ", huffmanLength);
    list_print(huffmanBinary);

    char *origCond = malloc(originalBinary -> length * 8 + 1);
    int oNext = 0;
    char *huffCond = malloc(huffmanLength + 1);
    int hNext = 0;
    for (int i = 0; i < originalBinary -> length; i++) {
        for (int j = 0; j < 8; j++) {
            if (originalBinary -> data[i].r -> data[j].c == '0') {
                origCond[oNext] = '0';
            } else {
                origCond[oNext] = '1';
            }
            oNext++;
        }
        for (int j = 0; j < huffmanBinary -> data[i].r -> length; j++) {
            if (huffmanBinary -> data[i].r -> data[j].c == '0') {
                huffCond[hNext] = '0';
            } else {
                huffCond[hNext] = '1';
            }
            hNext++;
        }
    }
    origCond[oNext] = '\0';
    huffCond[hNext] = '\0';
    printf("\nOriginal Binary (%d bits): %s\n", originalBinary -> length * 8, origCond);
    printf("\nHuffman Binary (%d bits): %s\n", huffmanLength, huffCond);

    printf("the frequency table is %d bits\n", frequencyTable -> length / 2 * 8 * 2);
    printf("this means the full huffman scheme takes %d bits compared to %d bits of the original data\n", frequencyTable -> length * 8 + huffmanLength, originalBinary -> length * 8);
}