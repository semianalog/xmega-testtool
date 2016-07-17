#ifndef XMEGASER_USB_CALLBACKS
#define XMEGASER_USB_CALLBACKS

#include <stdbool.h>
#include <inttypes.h>
#include <usb/asf/common/services/usb/class/cdc/usb_protocol_cdc.h>

bool xmegaser__cdc_enable(uint8_t port);
void xmegaser__cdc_disable(uint8_t port);
void xmegaser__sof_action(void);
void xmegaser__suspend_action(void);
void xmegaser__resume_action(void);
void xmegaser__cdc_set_dtr(uint8_t port, bool b_enable);
void xmegaser__rx_notify(uint8_t port);
void xmegaser__config(uint8_t port, usb_cdc_line_coding_t *cfg);

#endif // XMEGASER_USB_CALLBACKS
