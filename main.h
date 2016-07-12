#ifndef MAIN_H
#define MAIN_H

#include "usb_protocol_cdc.h"

// CDC callbacks
bool main_cdc_enable(uint8_t port);
void main_cdc_disable(uint8_t port);
void main_sof_action(void);
void main_suspend_action(void);
void main_resume_action(void);
void main_cdc_set_dtr(uint8_t port, bool b_enable);
void main_rx_notify(uint8_t port);
void main_config(uint8_t port, usb_cdc_line_coding_t *cfg);
void main_open(uint8_t port);
void main_close(uint8_t port);

// Like PSTR, but using avr-gcc __flash
#define FSTR(s) (__extension__({static char const __flash __c[] = (s); &__c[0];}))

void cdc_puts(char const __memx *s);

#endif // MAIN_H
