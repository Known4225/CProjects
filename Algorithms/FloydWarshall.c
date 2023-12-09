#include "include/list.h"

void PREDECESS(int O[4][4], int G[4][4], int L[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                if (L[i][k] + G[k][j] == L[i][j]) {
                    O[i][j] = k;
                }
            }
        }
    }
}


int main(int argc, char *argv[]) {
    int G[4][4];
    int L[4][4];
    int O[4][4];
    int Gtemp1[4] = {1000, 6, 5, 1000};
    memcpy(G[0], Gtemp1, 4 * sizeof(int));
    int Gtemp2[4] = {6, 1000, 4, 1};
    memcpy(G[1], Gtemp2, 4 * sizeof(int));
    int Gtemp3[4] = {5, 4, 1000, 1000};
    memcpy(G[2], Gtemp3, 4 * sizeof(int));
    int Gtemp4[4] = {0, 1, 1000, 1000};
    memcpy(G[3], Gtemp4, 4 * sizeof(int));

    int Ltemp1[4] = {1000, 6, 5, 7};
    memcpy(L[0], Ltemp1, 4 * sizeof(int));
    int Ltemp2[4] = {6, 1000, 4, 1};
    memcpy(L[1], Ltemp2, 4 * sizeof(int));
    int Ltemp3[4] = {5, 4, 1000, 5};
    memcpy(L[2], Ltemp3, 4 * sizeof(int));
    int Ltemp4[4] = {7, 1, 5, 1000};
    memcpy(L[3], Ltemp4, 4 * sizeof(int));

    int Otemp[4] = {-1, -1, -1, -1};
    for (int i = 0; i < 4; i++) {
        memcpy(O[i], Otemp, 4 * sizeof(int));
    }
    // list_t *G = list_init();
    // for (int i = 0; i < 4; i++) {
    //     list_append(G, (unitype) list_init(), 'r');
    //     int 
    //     for (int j = 0; j < 4; j++) {
    //         list_append(G -> data[i].r, (unitype) temp[j], )
    //     }
    // }
    PREDECESS(O, G, L);
    // for (int i = 0; i < 4; i++) {
    //     for (int j = 0; j < 4; j++) {
    //         for (int k = 0; k < 4; k++) {
    //             if (L[i][k] + G[k][j] == L[i][j]) {
    //                 O[i][j] = k;
    //             }
    //         }
    //     }
    // }
    for (int i = 0; i < 4; i++) {
        printf("[");
        for (int j = 0; j < 4; j++) {
            printf("%d, ", O[i][j]);
        }
        printf("]\n");
    }
}