#include <asf.h>
#include "conf_usb.h"

static volatile bool cdc_en = false;

#define FSTR(s) (__extension__({static char const __flash __c[] = (s); &__c[0];}))

void cdc_puts(char const __memx * s);

int main(void)
{

	irq_initialize_vectors();
	cpu_irq_enable();

	sleepmgr_init();
	sysclk_init();
	board_init();

	// Start USB stack to authorize VBus monitoring
	udc_start();

    PORTF.DIRSET = 0xf0;

    char cmdbuf[100] = "";
    uint8_t bufpos = 0;

    for (;;) {
        int c = udi_cdc_getc();
        if (c <= 0 || c > 255) continue;
        if (bufpos < sizeof(cmdbuf) - 2) {
            cmdbuf[bufpos++] = c;
        }

        if (c == '\n') {
            if (bufpos < sizeof(cmdbuf) - 2) {
                cmdbuf[bufpos++] = 0;
                cdc_puts(cmdbuf);
            } else {
                cdc_puts(FSTR("error: buffer overflow\r\n"));
            }
            bufpos = 0;
        }
    }
}

void cdc_puts(char const __memx * s)
{
    while (*s) {
        while (!udi_cdc_is_tx_ready());
        udi_cdc_putc(*s++);
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
