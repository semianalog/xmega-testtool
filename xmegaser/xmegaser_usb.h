#ifndef XMEGASER_USB_XMEGASER_H
#define XMEGASER_USB_XMEGASER_H

#include <stdbool.h>

void xmegaser_usb_init(void);
int xmegaser_usb_getc(void);
bool xmegaser_usb_txready(void);
void xmegaser_usb_putc(char c);

#endif // XMEGASER_USB_XMEGASER_H
