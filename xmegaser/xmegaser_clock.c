#include <xmegaser.h>
#include <usb/asf/xmega/drivers/nvm/nvm.h>

void xmegaser_clock_fast_nopll(void)
{
    // intRC at 48 MHz
    // div2 sysclk
    OSC.CTRL |= OSC_RC32MEN_bm;
    while (!(OSC.CTRL & OSC_RC32MRDY_bm));

    uint8_t msb = nvm_read_production_signature_row(
            nvm_get_production_signature_row_offset(USBRCOSC));
    uint8_t lsb = nvm_read_production_signature_row(
            nvm_get_production_signature_row_offset(USBRCOSCA));
    DFLLRC32M.CALA = lsb;
    DFLLRC32M.CALB = msb;
    OSC.DFLLCTRL = OSC_RC32MCREF_USBSOF_gc;
    DFLLRC32M.CTRL = DFLL_ENABLE_bm;

    _PROTECTED_WRITE(CLK.PSCTRL, CLK_PSADIV_2_gc | CLK_PSBCDIV_1_1_gc);
    _PROTECTED_WRITE(CLK.CTRL, CLK_SCLKSEL_RC32M_gc);
    CLK.USBCTRL = CLK_USBSRC_RC32M_gc;
}

void xmegaser_clock_fast_pll(void)
{
    // intRC at 32 MHz
    // *3, /2 for USB
    // direct for sysclk
    OSC.CTRL |= OSC_RC32MEN_bm;
    while (!(OSC.CTRL & OSC_RC32MRDY_bm));

    OSC.PLLCTRL = OSC_PLLSRC_RC32M_gc | /* multiplier */ 3;
    OSC.CTRL |= OSC_PLLEN_bm;
    while (!(OSC.STATUS & OSC_PLLRDY_bm));

    _PROTECTED_WRITE(CLK.PSCTRL, CLK_PSADIV_1_gc | CLK_PSBCDIV_1_1_gc);
    _PROTECTED_WRITE(CLK.CTRL, CLK_SCLKSEL_RC32M_gc);

    CLK.USBCTRL = CLK_USBSRC_PLL_gc | CLK_USBPSDIV_2_gc;
}

void xmegaser_enable_dfll(enum xmegaser_dfllsrc dfllsrc)
{
    if (dfllsrc == DFLL_INTERNAL) {
        OSC.DFLLCTRL = OSC_RC32MCREF_RC32K_gc;
    } else {
        OSC.XOSCCTRL = OSC_XOSCSEL_32KHz_gc;
        OSC.CTRL |= OSC_XOSCEN_bm;
        while (!(OSC.CTRL & OSC_XOSCRDY_bm));
        OSC.DFLLCTRL = OSC_RC32MCREF_XOSC32K_gc;
    }
    DFLLRC32M.CTRL = DFLL_ENABLE_bm;
}
