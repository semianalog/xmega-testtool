#include <asf.h>
#include "conf_usb.h"
#include "ui.h"

static volatile bool cdc_en = false;

int main(void)
{

	irq_initialize_vectors();
	cpu_irq_enable();

	sleepmgr_init();
	sysclk_init();
	board_init();
	ui_init();
	ui_powerdown();

	// Start USB stack to authorize VBus monitoring
	udc_start();

    static const __flash char str[] = "Hello, world!\r\n";
    const __flash char *p = &str[0];

    uint8_t count = 0;
    PORTF.DIRSET = 0xf0;

    for (;;) {
        if (*p) {
            ui_com_tx_start();
            if (udi_cdc_is_tx_ready()) {
                udi_cdc_putc(*p);
                ++p;
            }
            ui_com_tx_stop();
        } else {
            p = &str[0];
            ++count;
            PORTF.OUTCLR = 0xf0;
            PORTF.OUTSET = (count & 0x0f) << 4;
        }
    }
}

void main_suspend_action(void)
{
	ui_powerdown();
}

void main_resume_action(void)
{
	ui_wakeup();
}

void main_sof_action(void)
{
	if (!cdc_en)
		return;
	ui_process(udd_get_frame_number());
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
	if (b_enable) {
		// Host terminal has open COM
		ui_com_open(port);
	}else{
		// Host terminal has close COM
		ui_com_close(port);
	}
}

void main_config(uint8_t port, usb_cdc_line_coding_t *cfg)
{
}

void main_rx_notify(uint8_t port)
{
    PORTF.OUTSET = 0x40;
}
