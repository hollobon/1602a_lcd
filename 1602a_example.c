#include <stdbool.h>
#include <util/delay.h>

#include "1602a_lcd.h"

int main(void)
{
    // Set up outputs for shift register
    DDRB |= _BV(4) | _BV(5);
    DDRE |= _BV(6);

    // Set up outputs for E / RS
    DDRD |= _BV(0) | _BV(1); 

    _delay_ms(200);
    write_1602a(false, 0b00111000); // function set - 8 bit, 2 lines, 5x11
    clear_1602a();
    displayon_1602a(true, true);
    write_1602a(false, 0b00000110); // entry mode set
    puts_1602a("Test");
    setaddress_1602a(0, 1);
    puts_1602a("Line 2");

    const char *spinner = "_oOo";
    const char *current = spinner;
    while (1) {
        setaddress_1602a(10, 1);
        putc_1602a(*current++);
        if (!*current)
            current = spinner;
        _delay_ms(100);
    }
}
