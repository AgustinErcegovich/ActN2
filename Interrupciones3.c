#include "MKL25Z.h"
#include "INTERRUPCIONES3.h"
#include "CType.h"

int BCD1 [4] = {0, 1, 2, 3};
int BCD2 [4] = {4, 5, 6, 7};
int BCD3 [4] = {8, 9, 10, 11};

int BCD [10] [4] =  {
                    {0, 0, 0, 0},
                    {0, 0, 0, 1},
                    {0, 0, 1, 0},
                    {0, 0, 1, 1},
                    {0, 1, 0, 0},
                    {0, 1, 0, 1},
                    {0, 1, 1, 0},
                    {0, 1, 1, 1},
                    {1, 0, 0, 0},
                    {1, 0, 0, 1}
                    };

void BCD7seg_Init() {
    SIM -> SCGC5 |= SIM_SCGC5_PORTA_MASK;
    PORTA -> PDDR |= 0xFFFFFFFF;
}

void BCDseg(char letra) {
    char caracter = toUpper(letra);
    switch (caracter) {
        case 'A':
            for (int i=0;i<10;i++) {
                for (int e=0;e<4;e++) {
                    PTA -> PSOR |= (BCD[i][e] << BCD1[e]);
                }
                for (int j=0;j<10;j++) {
                    for (int a=0;a<4;a++) {
                        PTA -> PSOR |= (BCD[j][a] << BCD2[a]);
                    }
                    for (int s=0;s<10;s++) {
                        for (int d=0;d<4;d++) {
                            PTA -> PSOR |= (BCD[s][d] << BCD3[d]);
                            delay(1000);
                        }
                    }
                }
            }
        break;
        case 'B':
            for (int i=10;i>0;i--) {
                for (int e=0;e<4;e++) {
                    PTA -> PSOR |= (BCD[i][e] << BCD1[e]);
                }
                for (int j=10;j>0;j--) {
                    for (int a=0;a<4;a++) {
                        PTA -> PSOR |= (BCD[j][a] << BCD2[a]);
                    }
                    for (int s=10;s>0;s--) {
                        for (int d=0;d<4;d++) {
                            PTA -> PSOR |= (BCD[s][d] << BCD3[d]);
                            delay(1000);
                        }
                    }
                }
            }
        break;
        case 'C':
            for (int i=0;i<4;i++) {
                PTA -> PSOR |= (BCD[0][i] << BCD1[i]);
                PTA -> PSOR |= (BCD[0][i] << BCD2[i]);
                PTA -> PSOR |= (BCD[0][i] << BCD3[i]);
                }
        break;
    }
}