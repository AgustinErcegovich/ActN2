#include "MKL25Z.h"
#include "INTERRUPCIONES.h"

int leds [8] = {0, 1, 2, 3, 4, 5, 6, 7, 8};

int BCDM [10][4] =  {
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

int AnilloM [4][4] ={
                    {0, 0, 0, 1},
                    {0, 0, 1, 0},
                    {0, 1, 0, 0},
                    {1, 0, 0, 0}
                    };

int JohnsonM [6][4] =   {
                        {0, 0, 0, 1},
                        {0, 0, 1, 0},
                        {0, 1, 0, 0},
                        {1, 0, 0, 0},
                        {0, 1, 0, 0},
                        {0, 0, 1, 0},
                        };

int BCD7segM [10][7] =  {
                        {1, 1, 1, 1, 1, 1, 0},
                        {0, 1, 1, 0, 0, 0, 0},
                        {1, 1, 0, 1, 1, 0, 1},
                        {1, 1, 1, 1, 0, 0, 1},
                        {0, 1, 1, 0, 0, 1, 1},
                        {1, 0, 1, 1, 0, 1, 1},
                        {1, 0, 1, 1, 1, 1, 1},
                        {1, 1, 1, 0, 0, 0, 0},
                        {1, 1, 1, 1, 1, 1, 1},
                        {1, 1, 1, 1, 0, 1, 1}                  
                        };   
                
int BCD() {
    for (int i=0;i<10;i++) {
        for (int j=0;j<4;j++) {
            PTA -> PSOR |= (BCDM[i][j] << leds[j]);
        }
    }
}

int Anillo() {
    for (int i=0;i<4;i++) {
        for (int j=0;j<4;j++) {
            PTA -> PSOR |= (AnilloM[i][j] << leds[j]);
        }
    }
}

int Johnson() {
    for (int i=0;i<6;i++) {
        for (int j=0;j<4;j++) {
            PTA -> PSOR |= (JohnsonM[i][j] << leds[j]);
        }
    }
}

int BCD7seg () {
    for (int i=0;i<10;i++) {
        for (int j=0;j<7;j++) {
            PTA -> PSOR |= (BCD7segM[i][j] << leds[j]);
        }
    }
}