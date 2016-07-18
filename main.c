#include <stdio.h>
#include "main.h"
#include "testtool.h"
#include <esh.h>
#include <xmegaser.h>
#include <xmegaser_usb.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>

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

    PORTK.DIR = 0xff;
    PORTH.DIR = 0xff;
    PORTH.OUT = 0xff;

    // Full 32kB external SRAM. Has two limitations:
    //  - not contiguous with internal SRAM
    //  - extends past 0xffff boundary
    //
    // This is because for memory larger than 16kB, the base address is
    // required to be on a multiple of the memory size.
    /*
    EBI.CTRL = EBI_LPCMODE_ALE1_gc | EBI_IFMODE_3PORT_gc;
    EBI.CS0.CTRLA = EBI_CS_ASPACE_32KB_gc | EBI_CS_MODE_LPC_gc;
    EBI.CS0.CTRLB = EBI_CS_SRWS_7CLK_gc;
    EBI.CS0.BASEADDR = 0x8000 >> 8;
    */

    // Partial 16kB external SRAM, contiguous, fully with 16-bit address space
    PORTK.OUTCLR = (1 << 6);    // Address line 14
    PORTK.PIN6CTRL = PORT_OPC_PULLDOWN_gc;
    EBI.CTRL = EBI_LPCMODE_ALE1_gc | EBI_IFMODE_3PORT_gc;
    EBI.CS0.CTRLA = EBI_CS_ASPACE_16KB_gc | EBI_CS_MODE_LPC_gc;
    EBI.CS0.CTRLB = EBI_CS_SRWS_7CLK_gc;
    EBI.CS0.BASEADDR = 0x4000 >> 8;

    xmegaser_usb_init();
    stdout = &uart_output;

    esh_init(&esh);
    esh_register_callback(&esh, &handle_command);
    esh_register_print(&esh, &print_callback);

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
