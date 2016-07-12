#include <asf.h>
#include <stdio.h>
#include "conf_usb.h"
#include "main.h"
#include "testtool.h"

static volatile bool cdc_en = false;

int cdc_putchar(char c, FILE *stream);
FILE uart_output = FDEV_SETUP_STREAM(&cdc_putchar, NULL, _FDEV_SETUP_WRITE);

int main(void)
{

	irq_initialize_vectors();
	cpu_irq_enable();

	sleepmgr_init();
	sysclk_init();
	board_init();

	// Start USB stack to authorize VBus monitoring
	udc_start();
    stdout = &uart_output;

    PORTF.DIRSET = 0xf0;

    char cmdbuf[100] = "";
    uint8_t bufpos = 0;

    for (;;) {
        int c = udi_cdc_getc();
        if (c <= 0 || c > 255) continue;
        if (bufpos < sizeof(cmdbuf) - 2) {
            if (c == 8 || c == 127) {
                cmdbuf[bufpos--] = 0;
            } else {
                cmdbuf[bufpos++] = c;
            }
            udi_cdc_putc(c);
        }

        if (c == '\n' || c == '\r') {
            if (bufpos < sizeof(cmdbuf) - 2) {
                cmdbuf[bufpos++] = 0;
                handle_command(cmdbuf);
            } else {
                cdc_puts(FSTR("error: buffer overflow\r\n"));
            }
            bufpos = 0;
        }
    }
}

int cdc_putchar(char c, FILE *stream)
{
    if (c == '\n') {
        cdc_putchar('\r', 0);
    }
    while (!udi_cdc_is_tx_ready());
    udi_cdc_putc(c);
    return 0;
}

void cdc_puts(char const __memx * s)
{
    while (*s) {
        cdc_putchar(*s++, 0);
    }
}

void main_suspend_action(void)
{
}

void main_resume_action(void)
{
}

void main_sof_action(void)
{
	if (!cdc_en)
		return;
}

bool main_cdc_enable(uint8_t port)
{
	cdc_en = true;
	return true;
}

void main_cdc_disable(uint8_t port)
{
	cdc_en = false;
}

void main_cdc_set_dtr(uint8_t port, bool b_enable)
{
}

void main_config(uint8_t port, usb_cdc_line_coding_t *cfg)
{
}

void main_rx_notify(uint8_t port)
{
}
