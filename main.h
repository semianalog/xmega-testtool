#ifndef MAIN_H
#define MAIN_H

#include <stdbool.h>

// Like PSTR, but using avr-gcc __flash
#define FSTR(s) (__extension__({static char const __flash __c[] = (s); &__c[0];}))

void cdc_puts(char const __memx *s);

#endif // MAIN_H
