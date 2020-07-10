// Just blinking stm32f103c8t6 for fun
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h> // Just experimenting

#include "stm32f10x.h"

/* Prototypes */
void waitABit(int_fast8_t Moment);

int main(void) {

  RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
  
  GPIOC->CRH |= GPIO_CRH_MODE13;
  GPIOC->CRH &= ~(GPIO_CRH_CNF13);

  while(1) {
    GPIOC->BSRR = (1<<13); 
		waitABit(0xFFFFF);

    GPIOC->BSRR = (1<<29);
    waitABit(0xFFFFF);
  }
  return 0;
}

/* Like it says, wait a bit */
void waitABit(int_fast8_t Time) {
  volatile int i,j;
  for (i = 0; i < Time; ++i) {
    j++;
  }
}