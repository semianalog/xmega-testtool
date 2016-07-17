#define  USB_DEVICE_VENDOR_ID             USB_VID_ATMEL
#define  USB_DEVICE_PRODUCT_ID            USB_PID_ATMEL_ASF_CDC

#define  USB_DEVICE_MAJOR_VERSION         1
#define  USB_DEVICE_MINOR_VERSION         0
#define  USB_DEVICE_POWER                 100   // Consumption on Vbus line (mA)

#define  USB_DEVICE_ATTR                  \
	(USB_CONFIG_ATTR_BUS_POWERED)
// (USB_CONFIG_ATTR_SELF_POWERED)

//! USB Device string definitions (Optional)
#define  USB_DEVICE_MANUFACTURE_NAME      "ATMEL ASF"
#define  USB_DEVICE_PRODUCT_NAME          "CDC Virtual Com"
// #define  USB_DEVICE_SERIAL_NAME           "12...EF"

