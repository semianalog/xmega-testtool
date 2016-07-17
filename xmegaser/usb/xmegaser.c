#include <xmegaser_usb.h>
#include <inttypes.h>
#include <usb/asf/common/services/usb/udc/udc.h>
#include <usb/asf/common/services/usb/class/cdc/device/udi_cdc.h>

void xmegaser_usb_init(void)
{
    udc_start();
}


int xmegaser_usb_getc(void)
{
    return udi_cdc_getc();
}


bool xmegaser_usb_txready(void)
{
    return udi_cdc_is_tx_ready();
}


void xmegaser_usb_putc(char c)
{
    while (!xmegaser_usb_txready());
    udi_cdc_putc(c);
}


bool xmegaser__cdc_enable(uint8_t port)
{
    (void) port;
    return true;
}


void xmegaser__cdc_disable(uint8_t port)
{
    (void) port;
}


void xmegaser__sof_action(void)
{
}


void xmegaser__suspend_action(void)
{
}


void xmegaser__resume_action(void)
{
}


void xmegaser__cdc_set_dtr(uint8_t port, bool b_enable)
{
    (void) port;
    (void) b_enable;
}


void xmegaser__rx_notify(uint8_t port)
{
    (void) port;
}


void xmegaser__config(uint8_t port, usb_cdc_line_coding_t *cfg)
{
    (void) port;
    (void) cfg;
}
