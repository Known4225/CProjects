#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char indexNumbers[37];
    char indexLower[37];
    // indexNumbers = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    // indexLower = "0123456789abcdefghijklmnopqrstuvwxyz";
} data;

data init() {
    data op;
    strcpy(op.indexNumbers, "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    strcpy(op.indexLower, "0123456789abcdefghijklmnopqrstuvwxyz");
    return op;
}

int power(int x, int y) {
    int out = 1;
    for (int i = 0; i < y; i++) {
        out *= x;
    }
    return out;
}

int turnToInteger(char figure) {
    data newData = init();
    for (int i = 0; i < 36; i++) {
        if (figure == newData.indexNumbers[i]) {
            return i;
        }
    }
    return 0;
}

int rockyAlgorithm(char *num, int base) { //turns a number from the given base to base 10
    int out = 0;
    // printf("%s\n", num);
    // printf("%d\n", base);
    for (int i = 0; i < strlen(num); i++) {
        out += turnToInteger(num[i]) * power(base, strlen(num) - i - 1);
        // printf("%d\n", turnToInteger(num[i]));
        // printf("%d\n", out);
    }
    return out;
}

char* zgutowiczMethod(int num, int base) { //turns a number from base 10 to the given base (copied from my ti84 program)
    data newData = init();
    int list1[128];
    int next = 0;
    int varA;
    int varH;
    char *out = malloc(sizeof(char) * 256);
    for (int i = 0; i < 128; i++) {
        out[i] = '\0';
    }
    while (num >= base && next < 128) {
        varA = num/base;
        list1[next] = num % base;
        next += 1;
        num = varA;
    }
    list1[next] = num % base;
    for (int i = 0; i < (next + 1)/ 2; i++) {
        varH = list1[i];
        list1[i] = list1[next - i];
        list1[next - i] = varH;
    }
    next += 1;
    for (int i = 0; i < next; i++) {
        out[i] = newData.indexNumbers[list1[i]];
    }
    return out;
}

char* makeUpper(char *list) {
    data newData = init();
    char *out = malloc(sizeof(char) * 128);
    for (int i = 0; i < 128; i++) {
        out[i] = '\0';
    }
    int next = 0;
    for (int i = 0; i < strlen(list); i++) {
        for (int j = 0; j < 36; j++) {
            if (list[i] == newData.indexLower[j]) {
                out[next] = newData.indexNumbers[j];
                break;
            }
        }
        if (out[next] == '\0') {
            out[next] = list[i];
        }
        next++;
    }
    return out;
}

int main(int argc, char *argv[]) {
    char *upperPointer;
    char *zgutowiczPointer;
    char baseNum[128];
    char input[128];
    char inputUpper[128];
    for (int i = 0; i < 128; i++) {
        inputUpper[i] = '\0';
    }
    char baseResult[128];
    int baseGiven;
    int base10;
    int baseOut;
    char output[256];
    char base2[256];
    char base8[256];
    char base16[256];
    printf("\n");
    printf("Welcome to BaseConverter!\n\n");
    while (1) {
        printf("input given base: ");
        scanf("%s", baseNum);
        if (strcmp(baseNum, "quit") == 0) {break;}
        printf("input number: ");
        scanf("%s", input);
        if (strcmp(input, "quit") == 0) {break;}
        printf("input desired base: ");
        scanf("%s", baseResult);
        if (strcmp(baseResult, "quit") == 0) {break;}

        if ((strcmp(baseNum, "2") == 0 && input[0] == '0' && input[1] == 'b') || (strcmp(baseNum, "16") == 0 && input[0] == '0' && input[1] == 'x')) {
            for (int i = 2; i < strlen(input); i++) {
                inputUpper[i - 2] = input[i];
            }
            strcpy(input, inputUpper);
            // printf("%s\n", input);
        }
        upperPointer = makeUpper(input);
        strcpy(inputUpper, upperPointer);
        // printf("%s %s %s\n", baseNum, inputUpper, baseResult);
        baseGiven = 0;
        for (int i = 0; i < strlen(baseNum); i++) {
            baseGiven += turnToInteger(baseNum[i]) * power(10, strlen(baseNum) - i - 1);
        }
        baseOut = 0;
        for (int i = 0; i < strlen(baseResult); i++) {
            baseOut += turnToInteger(baseResult[i]) * power(10, strlen(baseResult) - i - 1);
        }
        // printf("Base Given: %d\n", baseGiven);
        base10 = rockyAlgorithm(inputUpper, baseGiven);
        // printf("Base 10: %d\n", base10);
        zgutowiczPointer = zgutowiczMethod(base10, baseOut);
        strcpy(output, zgutowiczPointer);
        zgutowiczPointer = zgutowiczMethod(base10, 2);
        strcpy(base2, zgutowiczPointer);
        zgutowiczPointer = zgutowiczMethod(base10, 8);
        strcpy(base8, zgutowiczPointer);
        zgutowiczPointer = zgutowiczMethod(base10, 16);
        strcpy(base16, zgutowiczPointer);
        printf("\n%s (base %d) in base %d is: %s\n\n", input, baseGiven, baseOut, output);
        printf("Binary: 0b%s\n", base2);
        printf("Octal: 0%s\n", base8);
        printf("Hex: 0x%s\n", base16);
        printf("Unsigned Decimal: %d\n\n", base10);
        free(upperPointer);
        free(zgutowiczPointer);
    }
}
