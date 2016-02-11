#include <stdbool.h>
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

#include "1602a_lcd.h"

// Write a value to the shift register and make available on outputs
void sr_write(uint8_t value)
{
    for (int8_t i = 7; i >= 0; i--) {
        // DS
        if (value & 0x80)
            PORTE |= _BV(6);
        else
            PORTE &= ~_BV(6);

        // SHCP - clock bit into shift register
        PORTB |= _BV(5);
        PORTB &= ~_BV(5);
        
        value <<= 1;
    }
    // STCP - clock byte into output register
    PORTB |= _BV(4);
    PORTB &= ~_BV(4);
}

void write_1602a(bool register_select, uint8_t value)
{
    if (register_select)
        PORTD |= _BV(1);        // data register
    else
        PORTD &= ~_BV(1);       // instruction register

    sr_write(value);

    // cycle E
    PORTD |= _BV(0);
    asm volatile("nop\n nop\n nop\n nop"); /* 4 cycles = ~250ns at 16MHz, tDSW is 195ns */
    PORTD &= ~_BV(0);

    _delay_us(37);
}

void puts_1602a(const char *str)
{
    while (*str)
        putc_1602a(*str++);
}
