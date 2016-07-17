#ifndef XMEGASER_H
#define XMEGASER_H

void xmegaser_clock_fast_nopll(void);
void xmegaser_clock_fast_pll(void);

enum xmegaser_dfllsrc {
    DFLL_INTERNAL,
    DFLL_EXTERNAL
};

void xmegaser_enable_dfll(enum xmegaser_dfllsrc dfllsrc);

#endif // XMEGASER_H
