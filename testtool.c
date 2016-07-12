#include "testtool.h"

#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/pgmspace.h>

void upcase(char *s);
int16_t parse_number(char *num);
void cmd_parse(char *arg);
void cmd_port(char *arg);
void cmd_help(char *arg);

void handle_command(char *cmd)
{
    // Remove \r\n
    char *term;
    term = strchr(cmd, '\r');
    if (term) *term = 0;
    term = strchr(cmd, '\n');
    if (term) *term = 0;

    // Split cmd and arg
    char *arg = strchr(cmd, ' ');
    while (arg && isspace(*arg)) {
        *arg = 0;
        ++arg;
    }

    printf_P(PSTR("\n"));
    if (!strcmp_P(cmd, PSTR("parse"))) {
        cmd_parse(arg);
    } else if (!strcmp_P(cmd, PSTR("port"))) {
        cmd_port(arg);
    } else if (!strcmp_P(cmd, PSTR("help"))) {
        cmd_help(arg);
    } else {
        printf_P(PSTR("unknown command: %s\ntry 'help'\n"), cmd);
    }
}

int16_t parse_number(char *num)
{
    int base = 10;

    if (num[0] == '0') {
        switch(num[1]) {
        case 'X':
        case 'x':
            base = 16;
            break;
        case 'B':
        case 'b':
            base = 2;
            break;
        default:
            base = 8;
        }
    }

    return strtol(num, NULL, base);
}

void upcase(char *s)
{
    while (s && *s) {
        *s = toupper(*s);
        ++s;
    }
}

void cmd_parse(char *arg)
{
    printf_P(PSTR("%d\n"), parse_number(arg));
}

void cmd_port(char *arg)
{
    // port F dirset 0xff
    char *port, *field, *value;

    port = strtok(arg, " ");
    field = strtok(NULL, " ");
    value = strtok(NULL, " ");
    upcase(port);
    upcase(field);
    upcase(value);

    if (!port || !field || !value) {
        printf_P(PSTR("expected arguments: PORT FIELD VALUE\n"));
        return;
    }

    PORT_t *p;
    switch(*port) {
        case 'A': p = &PORTA; break;
        case 'B': p = &PORTB; break;
        case 'C': p = &PORTC; break;
        case 'D': p = &PORTD; break;
        case 'E': p = &PORTE; break;
        case 'F': p = &PORTF; break;
        default: goto err;
    }

    uint8_t v = parse_number(value);

    if (!strcmp_P(field, PSTR("OUTSET"))) {
        p->OUTSET = v;
    } else if (!strcmp_P(field, PSTR("OUTCLR"))) {
        p->OUTCLR = v;
    } else if (!strcmp_P(field, PSTR("OUTTGL"))) {
        p->OUTTGL = v;
    } else if (!strcmp_P(field, PSTR("OUT"))) {
        p->OUT = v;
    } else if (!strcmp_P(field, PSTR("DIRSET"))) {
        p->DIRSET = v;
    } else if (!strcmp_P(field, PSTR("DIRCLR"))) {
        p->DIRCLR = v;
    } else if (!strcmp_P(field, PSTR("DIRTGL"))) {
        p->DIRTGL = v;
    } else if (!strcmp_P(field, PSTR("DIR"))) {
        p->DIR = v;
    } else {
        goto err;
    }

    printf_P(PSTR("\n"));
    return;
err:
    printf_P(PSTR("unknown error\n"));
}

void cmd_help(char *arg)
{
    printf_P(PSTR("parse VALUE              parse VALUE as integer and print (debug)\n"));
    printf_P(PSTR("                       > parse 0x12\n"));
    printf_P(PSTR("                      >> 18\n"));
    printf_P(PSTR("\n"));
    printf_P(PSTR("port PORT FIELD VALUE    set PORT.FIELD = VALUE\n"));
    printf_P(PSTR("                         supported FIELDs: {OUT,DIR}{,SET,CLR,TGL}\n"));
    printf_P(PSTR("                       > port F OUTSET 0xf0\n"));
    printf_P(PSTR("\n"));
}
