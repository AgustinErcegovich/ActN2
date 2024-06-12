#include "MKL25Z.h"
#include "INTERRUPCIONES.h"

int btn [4] = {9, 10, 11, 12};
int a = 0;
int main () {
    PORTA -> PDDR |= 0xFFFFFFFF;
    for (int i=0;i<4;i++) {
        PORTA -> PCR[btn[i]] = PORT_PCR_MUX(1) | PORTA_PCR_IRQC(0b1101);
        NVIC -> ISER[i] = (1 << btn[i]);
    }
    for (int j=0;j<4;j++) {
        NVIC -> IPR[btn[j] >> 2] = (a << ((btn[0] & 0x3)*8+6));
    }
    while (1) {
    }
}

void ISR_BCD() {
    if (PORTA -> ISFR & (1 << btn[0])) {
        PORTA -> ISFR |= (1 << btn[0]);
        NVIC -> IPR[btn[1] >> 2] = ((a+1) << ((btn[0] & 0x3)*8+6));
        NVIC -> IPR[btn[2] >> 2] = ((a+1) << ((btn[0] & 0x3)*8+6));
        NVIC -> IPR[btn[3] >> 2] = ((a+1) << ((btn[0] & 0x3)*8+6));
        BCD();
    }
}

void ISR_Anillo() {
    if (PORTA -> ISFR & (1 << btn[1])) {
        PORTA -> ISFR |= (1 << btn[1]);
        NVIC -> IPR[btn[0] >> 2] = ((a+1) << ((btn[0] & 0x3)*8+6));
        NVIC -> IPR[btn[2] >> 2] = ((a+1) << ((btn[0] & 0x3)*8+6));
        NVIC -> IPR[btn[3] >> 2] = ((a+1) << ((btn[0] & 0x3)*8+6));
        Anillo();
    }
}

void ISR_Johnson() {
    if (PORTA -> ISFR & (1 << btn[2])) {
        PORTA -> ISFR |= (1 << btn[2]);
        NVIC -> IPR[btn[0] >> 2] = ((a+1) << ((btn[0] & 0x3)*8+6));
        NVIC -> IPR[btn[1] >> 2] = ((a+1) << ((btn[0] & 0x3)*8+6));
        NVIC -> IPR[btn[3] >> 2] = ((a+1) << ((btn[0] & 0x3)*8+6));
        Johnson();
    }
}

void ISR_BCD7seg() {
    if (PORTA -> ISFR & (1 << btn[3])) {
        PORTA -> ISFR |= (1 << btn[3]);
        NVIC -> IPR[btn[0] >> 2] = ((a+1) << ((btn[0] & 0x3)*8+6));
        NVIC -> IPR[btn[1] >> 2] = ((a+1) << ((btn[0] & 0x3)*8+6));
        NVIC -> IPR[btn[2] >> 2] = ((a+1) << ((btn[0] & 0x3)*8+6));
        BCD7seg();
    }
}
