#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
Enter a string to be hashed
Output: SHA256 hash of your string
Non-ASCII characters like ş and ö don't work, because of incorrect numerification of characters
Sadly doesn't generate primes and finds their cube roots for the initial constants, double float precision was unfortunately not precise enough
*/

double fabsM(double num) { //helper function for absolute value of a double (unused)
    if (num > 0) {
        return num;
    }
    return -num;
}

double sqrtM(double num, double tolerance) { //helper function for square root using newton's method (unused)
    double guess = num;
    double root = guess + tolerance * 2;
    while (fabsM(root - guess) > tolerance) {
        guess = root;
        root = 0.5 * (guess + (num / guess));
        // printf("%lf %lf %lf\n", root, guess, fabsM(root - guess));
    }
    return root;
}

double cubeM(double num, double tolerance) { //helper function for cube root using newton's method (unused)
    double guess = num;
    double proc;
    double root = guess + tolerance * 2;
    while (fabsM(root - guess) > tolerance) {
        guess = root;
        proc = guess * guess;
        root = (2 * proc * guess + num) / (3 * proc);
        // printf("%lf %lf %lf\n", root, guess, fabsM(root - guess));
    }
    return root;
}

int *generate_primes(int prim) {
    if (prim < 4) {
        prim = 4;
    }
    int *pr = malloc(sizeof(int) * prim);
    pr[0] = 2; pr[1] = 3; pr[2] = 5; pr[3] = 7;
    int next = 4;
    int check;
    int y;
    if (prim > 4) {
        check = 11;
        while (next < prim) {
            y = 0;
            while (pr[y] < sqrtM(check, 0.1) && check % pr[y] != 0) {
                y += 1;
            }
            if (check % pr[y] != 0) {
                pr[next] = check;
                next += 1;
            }
            check += 2;
        }
    }
    return pr;
}

typedef struct Constants {
    int cubeRoots[64];
    int squareRoots[8];
} constants_t;

constants_t generate_constants() {
    // int *primes = generate_primes(64);
    // double cub;
    // for (short i = 0; i < 64; i++) {
    //     printf("cuberoot(%d): ", primes[i]);
    //     cub = cubeM(primes[i], 1E-12);
    // }
    constants_t con;
    int localCon[64] = {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
                    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
                    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
                    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
                    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
                    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
                    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
                    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};
    int localInst[8] = {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};
    // int con.constants = malloc(sizeof(int) * 64);
    // int con.inst = malloc(sizeof(int) * 8);
    for (short i = 0; i < 64; i++) {
        con.cubeRoots[i] = localCon[i];
        
    }
    for (short i = 0; i < 8; i++) {
        con.squareRoots[i] = localInst[i];
    }
    return con;
}

bool *binary(unsigned long long num, int bitLength) {
    // printf("bitLength: %d\n", bitLength);
    // printf("Size of bool: %ld\n", sizeof(bool));
    bool *bin = malloc(bitLength * sizeof(bool));
    for (short i = bitLength - 1; i >= 0; i--) {
        if (num % 2 == 1) {
            bin[i] = 1;
        } else {
            bin[i] = 0;
        }
        // printf("%c\n", bin[i]);
        num /= 2;
        // printf("%hu\n", num);
    }
    return bin;
}

unsigned int toInt(bool *bits, int bitLength) {
    unsigned long long twoPower = 1;
    unsigned int out = 0;
    // printf("\n Bits: ");
    for (int i = bitLength - 1; i >= 0; i--) {
        // printf("%d", bits[i]);
        out += bits[i] * twoPower;
        twoPower *= 2;
    }
    // printf("\n");
    return out;
}

void pad(bool *inp, int len) {
    while (len % 512 != 448) {
        inp[len] = 0;
        len += 1;
        // printf("%d\n", len % 512);
    }
    // printf("len: %d\n", len);
}

void printBin(unsigned int num, int bitLength) {
    bool *throw;
    throw = binary(num, bitLength);
    for (int i = 0; i < bitLength; i++) {
        printf("%d", throw[i]);
    }
    // printf("\n");
    free(throw);
}

/* BASIC FUNCTIONS */

unsigned int shr(unsigned int inp, short iter) {
    return inp >> iter;
}

unsigned int rotr(unsigned int inp, short iter) {
    for (short i = 0; i < iter; i++) {
        if (inp % 2 == 1) {
            inp = inp >> 1;
            inp += 0x80000000;
        } else {
            inp = inp >> 1;
        }
    }
    return inp;
}

unsigned int xor(unsigned int inp1, unsigned int inp2) {
    return inp1 ^ inp2;
}

unsigned int choice(unsigned int inp1, unsigned int inp2, unsigned int inp3) { //will work on later (integer implementation)
    bool *inp1bool;
    inp1bool = binary(inp1, 32);
    bool *inp2bool;
    inp2bool = binary(inp2, 32);
    bool *inp3bool;
    inp3bool = binary(inp3, 32);
    bool outBool[32];
    for (short i = 0; i < 32; i++) {
        if (inp1bool[i] == 1) {
            outBool[i] = inp2bool[i];
        } else {
            outBool[i] = inp3bool[i];
        }
    }
    free(inp1bool);
    free(inp2bool);
    free(inp3bool);
    return toInt(outBool, 32);
}

unsigned int maj(unsigned int inp1, unsigned int inp2, unsigned int inp3) { //will work on later (integer implementation)
    bool *inp1bool;
    inp1bool = binary(inp1, 32);
    bool *inp2bool;
    inp2bool = binary(inp2, 32);
    bool *inp3bool;
    inp3bool = binary(inp3, 32);
    bool outBool[32];
    for (short i = 0; i < 32; i++) {
        if (inp1bool[i] + inp2bool[i] + inp3bool[i] >= 2) {
            outBool[i] = 1;
        } else {
            outBool[i] = 0;
        }
    }
    free(inp1bool);
    free(inp2bool);
    free(inp3bool);
    return toInt(outBool, 32);
}

/* SIGMA FUNCTIONS */

unsigned int sigma0(unsigned int input) {
    xor(xor(rotr(input, 7), rotr(input, 18)), shr(input, 3));
}

unsigned int sigma1(unsigned int input) {
    xor(xor(rotr(input, 17), rotr(input, 19)), shr(input, 10));
}

unsigned int SIGMA0(unsigned int input) {
    xor(xor(rotr(input, 2), rotr(input, 13)), rotr(input, 22));
}

unsigned int SIGMA1(unsigned int input) {
    xor(xor(rotr(input, 6), rotr(input, 11)), rotr(input, 25));
}

int *sha256(char *input, short print) {
    int *out = malloc(sizeof(int) * 8);
    int len = strlen(input);
    int ascii[len];
    constants_t constants = generate_constants();
    bool *binOut;
    if (print == 1) {printf("\nASCII: \n{");}
    for (short i = 0; i < len; i++) {
        ascii[i] = (int) input[i];
        if (print == 1) {printf("%d, ", ascii[i]);}
    }
    char bin8[8];
    int numBlocks = len / 64 + ((len % 64 > 55) ? 2 : 1);
    bool allBlock[numBlocks * 512];
    short next = 0;
    if (print == 1) {printf("\b\b}\n");}
    if (print == 1) {printf("\nBlocks used: %d\n", numBlocks);}
    for (short i = 0; i < len; i++) {
        binOut = binary(ascii[i], 8);
        for (short j = 0; j < 8; j++) {
            allBlock[next] = binOut[j];
            next += 1;
        }
        free(binOut);
    }
    allBlock[next] = 1;
    next += 1;
    for (short i = 0; i < 7; i++) {
        allBlock[next] = 0;
        next += 1;
    }
    pad(allBlock, next);
    // next += (next % 512 > 448) ? 512 : 0;
    // next += 448 - (next % 512);
    next += 448 - (next % 512) + ((next % 512 > 448) ? 512 : 0);
    // printf("next: %d\n", next);
    if (print == 1) {printf("\n");}
    unsigned int track[8];
    unsigned int compress[72];
    unsigned int T1;
    unsigned int T2;
    for (short i = 0; i < 8; i++) {
        track[i] = constants.squareRoots[8 - 1 - i];
        // printf("C%d: ", i);
        // printBin(track[i], 32);
        // printf("\n");
    }
    binOut = binary(len * 8, 64);
    for (short i = 0; i < 64; i++) {
        allBlock[next] = binOut[i];
        next += 1;
    }
    free(binOut);
    bool schedule[64][32];
    unsigned int schedint[64];
    for (short i = 0; i < next; i++) {
        if (print == 1) {printf("%d", allBlock[i]);}
    }
    if (print == 1) {printf("\n");}
    for (int m = 0; m < numBlocks; m++) {
        if (print == 1) {printf("\nBlock %d Schedule:\n", m + 1);}
        for (short i = 0; i < 16; i++) {
            for (short j = 0; j < 32; j++) {
                schedule[i][j] = allBlock[i * 32 + j + m * 512];
                // printf("%d", schedule[i][j]);
            }
            schedint[i] = toInt(schedule[i], 32);
            if (print == 1) {
                printf("W%-2u: ", i);
                printBin(schedint[i], 32);
                printf("   K%-2u: ", i);
                printBin(constants.cubeRoots[i], 32);
                if (m > 0) {printf("                      |");}
                printf("\n");
            }
            // printf("\n");
        }

        for (short i = 16; i < 64; i++) {
            schedint[i] = sigma1(schedint[i - 2]) + schedint[i - 7] + sigma0(schedint[i - 15]) + schedint[i - 16];
            if (print == 1) {
                printf("W%-2u: ", i);
                printBin(schedint[i], 32);
                printf("   K%-2u: ", i);
                printBin(constants.cubeRoots[i], 32);
                if (m > 0) {printf("                      |");}
                printf("\n");
            }
        }
        
        if (print == 1) {
            if (m > 0) {printf("                                                                                                   |");}
            printf("\n");
        }
        for (short i = 0; i < 8; i++) {
            compress[i] = track[i];
            // printBin(compress[i], 32);
        }
        // printf("K0: ");
        // printBin(constants.cubeRoots[0], 32);
        // printf("\n");
        for (short i = 0; i < 64; i++) {
            T1 = SIGMA1(compress[3 + i]) + choice(compress[3 + i], compress[2 + i], compress[1 + i]) + compress[0 + i] + constants.cubeRoots[i] + schedint[i];
            T2 = SIGMA0(compress[7 + i]) + maj(compress[7 + i], compress[6 + i], compress[5 + i]);
            compress[8 + i] = T1 + T2;
            compress[4 + i] += T1;
            if (print == 1) {
                printf("C%-2d: ", i);
                printBin(compress[i], 32);
                if (i < 8) {
                    printf("   H%-2d: ", i);
                    printBin(track[i], 32);
                    if (m > 0) {
                        if (i == 4) {
                            printf("   <------------------");
                        } else if (i < 4) {
                            printf("                      |");
                        }
                    }
                } else {
                    if (i > 9 && i < 62) {
                        printf("                      |");
                    }
                    if (i == 62) {
                        printf("                      V");
                    }
                }
                printf("\n");
            }
            // printf("T1: ");
            // printBin(T1, 32);
            // printf("\nT2: ");
            // printBin(T2, 32);
            // printf("\n");
            // break;
        }
        if (print == 1) {printf("\n");}
        for (short i = 0; i < 8; i++) {
            if (print == 1) {
                printf("C%d: ", 64 + i);
                printBin(compress[64 + i], 32);
                printf(" + H%d: ", i);
                printBin(track[i], 32);
                track[i] += compress[64 + i];
                printf(" = H%d: ", i);
                printBin(track[i], 32);
                printf("\n");
            } else {track[i] += compress[64 + i];}
        }

        // printf("\n");
        // for (short i = 0; i < 16; i++) {
        //     printf("W:%-2u: %i\n", i, schedint[i]);
        // }
        // printf("\n");
        // unsigned long long int test = 4294967295;
        // unsigned int test2 = 0xFFFFFFFF;
        // printf("%lli\n", test);
        // printf("%u\n", test2);
        // printf("Size of long: %d\n", sizeof(long long));

        // bool test3bool[32] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
        // unsigned int test3 = toInt(test3bool, 32);
        // test3 = 0x80000000;
        // unsigned int test3sigma = SIGMA1(toInt(test3bool, 32));
        // printBin(test3sigma, 32);
        // printf("\n");
    }
    if (print == 1) {
        printf("\n");
        for (short i = 0; i < 8; i++) {
            printf("F%d: ", i);
            printBin(track[7 - i], 32);
            if (i == 3) {
                printf("   <------------------ reversed (H0 = F7) ---------------------");
            } else if (i < 3) {
                printf("                                                               |");
            } else if (i == 4) {
                printf("   --------");
            } else {
               printf("           |"); 
            }
            printf("\n");
        }
        printf("                                               V");
        printf("\nFinal Hash:\n");
    }
    for (int i = 7; i >= 0; i--) {
        out[7 - i] = track[i];
        if (print >= 1) {printf("%x", track[i]);}
    }
    if (print >= 1) {printf("\n");}
    return out;
}

int main(int argc, char *argv[]) {
    char command[256];
    printf("Hash: ");
    scanf("%[^\n]%*c", command);
    int *hash = sha256(command, 1);
    // if (strcmp(command, "quit") == 0) {break;}
    free(hash);
    return 0;
}
