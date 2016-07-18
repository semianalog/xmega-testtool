#ifndef XMEGASER_CONF_USB_H
#define XMEGASER_CONF_USB_H

#include <usb/xmegaser_usb_callbacks.h>
#include <usb/asf/udi_cdc_conf.h>

#define  UDI_CDC_ENABLE_EXT(port)         xmegaser__cdc_enable(port)
#define  UDI_CDC_DISABLE_EXT(port)        xmegaser__cdc_disable(port)
#define  UDI_CDC_RX_NOTIFY(port)          xmegaser__rx_notify(port)
#define  UDI_CDC_TX_EMPTY_NOTIFY(port)
#define  UDI_CDC_SET_CODING_EXT(port,cfg) xmegaser__config(port,cfg)
#define  UDI_CDC_SET_DTR_EXT(port,set)    xmegaser__cdc_set_dtr(port,set)
#define  UDI_CDC_SET_RTS_EXT(port,set)
#define  UDC_VBUS_EVENT(b_vbus_high)
#define  UDC_SOF_EVENT()                  xmegaser__sof_action()
#define  UDC_SUSPEND_EVENT()              xmegaser__suspend_action()
#define  UDC_RESUME_EVENT()               xmegaser__resume_action()

#define  UDI_CDC_PORT_NB            1
#define  UDI_CDC_DEFAULT_RATE       115200
#define  UDI_CDC_DEFAULT_STOPBITS   CDC_STOP_BITS_1
#define  UDI_CDC_DEFAULT_PARITY     CDC_PAR_NONE
#define  UDI_CDC_DEFAULT_DATABITS   8

#endif // XMEGASER_CONF_USB_H
