#include <stdbool.h>
#include <util/delay.h>

#include "1602a_lcd.h"

uint8_t smiley[] = {
    0b01110,
    0b10001,
    0b11011,
    0b10001,
    0b10101,
    0b10001,
    0b01110,
    0b00000,
};

int main(void)
{
    // Set up outputs for shift register
    DDRB |= _BV(4) | _BV(5);
    DDRE |= _BV(6);

    // Set up outputs for E / RS
    DDRD |= _BV(0) | _BV(1);

    _delay_ms(200);
    function_set_1602a(true, true, false);
    clear_1602a();
    displayon_1602a(true, true);
    entrymode_1602a(true, false);

    set_cgaddress_1602a(0, 0);
    for (int8_t i = 0; i < 8; i++)
        putc_1602a(smiley[i]);

    set_address_1602a(0, 0);
    puts_1602a("Test");
    set_address_1602a(0, 1);
    puts_1602a("Line 2 ");
    putc_1602a(0);

    const char *spinner = "_oOo";
    const char *current = spinner;
    while (1) {
        set_address_1602a(10, 1);
        putc_1602a(*current++);
        if (!*current)
            current = spinner;
        _delay_ms(200);
    }
}
