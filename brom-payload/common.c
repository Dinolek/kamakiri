#include "common.h"

void (*send_usb_response)(int, int, int) = (void*)0x4C8F;

int (*send_dword)() = (void*)0xE1B7;
int (*recv_dword)() = (void*)0xE183;
// addr, sz
int (*send_data)() = (void*)0xE287;
// addr, sz, flags (=0)
int (*recv_data)() = (void*)0xE1F9;

void low_uart_put(int ch) {
    volatile uint32_t *uart_reg0 = (volatile uint32_t*)0x11002014;
    volatile uint32_t *uart_reg1 = (volatile uint32_t*)0x11002000;

    while ( !((*uart_reg0) & 0x20) )
    {}

    *uart_reg1 = ch;
}

void _putchar(char character)
{
    if (character == '\n')
        low_uart_put('\r');
    low_uart_put(character);
}
