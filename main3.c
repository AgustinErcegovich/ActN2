#include "MKL25Z.h"
#include "INTERRUPCIONES3.h"

int BCD1 [4] = {0, 1, 2, 3};
int BCD2 [4] = {4, 5, 6, 7};
int BCD = 0;
char puerto = 8;
int btn [3] = {9, 10, 11};

int main() {
    BCD7seg_Init();
    for (int i=0;i<3;i++) {
        PORTA -> PCR[btn[i]] = PORT_PCR_MUX(1) | PORTA_PCR_IRQC(0b1101);
        NVIC -> ISER[i] = (1 << btn[i]);
    }
    for (int j=0;j<3;j++) {
        NVIC -> IPR[btn[j] >> 2] = (0 << ((btn[j] & 0x3)*8+6));
    }
    while(1) {
        for (int e=0;e<4;e++) {
                PTA -> PSOR |= (BCD << BCD1[e]);
                PTA -> PSOR |= (BCD << BCD2[e]);
        }
    }
}

void btn1() {
    if (PORTA -> ISFR & (1 << btn[0])) {
        PORTA -> ISFR |= (1 << btn[0]);
        BCD7seg(A);
    }
}
void btn2() {
    if (PORTA -> ISFR & (1 << btn[1])) {
        PORTA -> ISFR |= (1 << btn[1]);
        BCD7seg(B);
    }
}
void btn3() {
    if (PORTA -> ISFR & (1 << btn[2])) {
        PORTA -> ISFR |= (1 << btn[2]);
        BCD7seg(C);
    }
}