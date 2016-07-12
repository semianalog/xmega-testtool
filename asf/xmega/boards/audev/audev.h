// Semianalog XMEGA AU development board definition

#ifndef AUDEV_H
#define AUDEV_H

#include <conf_board.h>
#include <compiler.h>

#ifdef __cplusplus
extern "C" {
#endif

void board_init(void);

#define BOARD_NAME              "SEMIANALOG_XMEGA_AU_DEVEL"
#define BOARD_XOSC_HZ           16000000
#define BOARD_XOSC_TYPE         XOSC_TYPE_XTAL
#define BOARD_XOSC_STARTUP_US   XOSC_STARTUP_16384

#ifdef __cplusplus
}
#endif

#endif  // AUDEV_H
