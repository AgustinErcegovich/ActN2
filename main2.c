#include "MKL25Z.h"

int btn = 0;
int semaforoauto [3] = {1, 2, 3};
int semaforopeaton [3] = {4, 5, 6};
int trojo = 30000, tamarillo = 3000, tverde = 20000;

int main () {
    PORTA -> PDDR |= 0xFFFFFFFF;
    for (int e=0;e<3;e++) {
        PORTA -> PCR[semaforoauto[e]] |= PORT_PCR_MUX(1);
        PORTA -> PCR[semaforopeaton[e]] |= PORT_PCR_MUX(1);
    }
    PORTA -> PCR[btn] = PORT_PCR_MUX(1) | PORTA_PCR_IRQC(0b1101);
    NVIC -> ISER[0] = (1 << btn);
    NVIC -> IPR[btn >> 2] = (0 << ((btn & 0x3)*8+6));

    while (1) {
        PTA -> PSOR |= (1u << semaforoauto[0]);
        PTA -> PSOR |= (0u << semaforoauto[1]);
        PTA -> PSOR |= (0u << semaforoauto[2]);
        PTA -> PSOR |= (0u << semaforopeaton[0]);
        PTA -> PSOR |= (1u << semaforopeaton[1]);
        delay(trojo);
        PTA -> PSOR |= (1u << semaforoauto[0]);
        PTA -> PSOR |= (1u << semaforoauto[1]);
        PTA -> PSOR |= (1u << semaforopeaton[0]);
        PTA -> PSOR |= (0u << semaforopeaton[1]);
        delay(tamarillo);
        PTA -> PSOR |= (0u << semaforoauto[0]);
        PTA -> PSOR |= (0u << semaforoauto[1]);
        PTA -> PSOR |= (1u << semaforoauto[2]);
        PTA -> PSOR |= (1u << semaforopeaton[0]);
        delay(tverde);
        PTA -> PSOR |= (1u << semaforoauto[1]);
        PTA -> PSOR |= (0u << semaforoauto[2]);
        PTA -> PSOR |= (1u << semaforopeaton[0]);
        delay(tamarillo);
    }
}

void Peaton() {
    if (PORTA -> ISFR & (1 << btn)) {
        PORTA -> ISFR |= (1 << btn);
        PTA -> PSOR |= (0u << semaforoauto[0]);
        PTA -> PSOR |= (1u << semaforoauto[1]);
        PTA -> PSOR |= (0u << semaforoauto[2]);
        PTA -> PSOR |= (1u << semaforopeaton[0]);
        PTA -> PSOR |= (0u << semaforopeaton[1]);
        delay(tamarillo);
        PTA -> PSOR |= (1u << semaforoauto[0]);
        PTA -> PSOR |= (0u << semaforoauto[1]);
        PTA -> PSOR |= (0u << semaforopeaton[0]);
        PTA -> PSOR |= (1u << semaforopeaton[1]);
        delay(trojo);
    }
}