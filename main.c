#include "MKL25Z.h"
#include "INTERRUPCIONES.h"

int btn [4] = {9, 10, 11, 12};

int main () {
    PORTA -> PDDR |= 0xFFFFFFFF;
    for (int i=0;i<4;i++) {
        PORTA -> PCR[btn[i]] = PORT_PCR_MUX(1) | PORTA_PCR_IRQC(0b1101);
        NVIC -> ISER[i] = (1 << btn[i]);
    }
    for (int j=0;j<4;j++) {
        NVIC -> IPR[btn[j] >> 2] = (0 << ((btn[0] & 0x3)*8+6));
    }
    while (1) {
    }
}

void ISR_BCD() {
    if (PORTA -> ISFR & (1 << btn[0])) {
        PORTA -> ISFR |= (1 << btn[0]);
        BCD();
    }
}

void ISR_Anillo() {
    if (PORTA -> ISFR & (1 << btn[1])) {
        PORTA -> ISFR |= (1 << btn[1]);
        Anillo();
    }
}

void ISR_Johnson() {
    if (PORTA -> ISFR & (1 << btn[2])) {
        PORTA -> ISFR |= (1 << btn[2]);
        Johnson();
    }
}

void ISR_BCD7seg() {
    if (PORTA -> ISFR & (1 << btn[3])) {
        PORTA -> ISFR |= (1 << btn[3]);
        BCD7seg();
    }
}