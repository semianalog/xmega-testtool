#include <stdio.h>
#include "main.h"
#include "testtool.h"
#include <esh.h>
#include <xmegaser.h>
#include <xmegaser_usb.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

static volatile bool cdc_en = false;

int cdc_putchar(char c, FILE *stream);
FILE uart_output = FDEV_SETUP_STREAM(&cdc_putchar, NULL, _FDEV_SETUP_WRITE);

struct esh esh;

static void print_callback(struct esh const * esh, char const * s)
{
    (void) esh;
    printf_P(PSTR("%s"), s);
}

int main(void)
{

    PMIC.CTRL = PMIC_LOLVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_HILVLEN_bm;
    sei();

    xmegaser_clock_fast_pll();
    xmegaser_enable_dfll(DFLL_EXTERNAL);
    xmegaser_usb_init();
    stdout = &uart_output;

    esh_init(&esh);
    esh_register_callback(&esh, &handle_command);
    esh_register_print(&esh, &print_callback);

    PORTF.DIRSET = 0xf0;

    for (;;) {
        int c = xmegaser_usb_getc();
        if (c <= 0 || c > 255) continue;
        if (c == '\r') c = '\n';
        esh_rx(&esh, c);
    }
}

int cdc_putchar(char c, FILE *stream)
{
    (void) stream;
    if (c == '\n') {
        cdc_putchar('\r', 0);
    }
    xmegaser_usb_putc(c);
    return 0;
}

void cdc_puts(char const __memx * s)
{
    while (*s) {
        cdc_putchar(*s++, 0);
    }
}
