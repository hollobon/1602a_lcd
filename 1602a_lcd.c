#include <stdbool.h>
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

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
        write_1602a(true, *str++);
}

int main(void)
{
    // Set up outputs for shift register
    DDRB |= _BV(4) | _BV(5);
    DDRE |= _BV(6);

    // Set up outputs for E / RS
    DDRD |= _BV(0) | _BV(1); 

    _delay_ms(200);
    write_1602a(false, 0b00111000); // function set - 8 bit, 2 lines, 5x11
    write_1602a(false, 0b00000001); // clear display
    _delay_ms(2);
    write_1602a(false, 0b00001110); // display on
    write_1602a(false, 0b00000110); // entry mode set
    puts_1602a("Test");
    write_1602a(false, 0x80 + 0x40); // set DDRAM address - first char second line
    puts_1602a("Line 2");
    while (1);
}
