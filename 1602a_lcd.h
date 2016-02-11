#ifndef _1602a_LCD_H
#define _1602a_LCD_H

#include <avr/io.h>

#define putc_1602a(c) write_1602a(true, (c))

#define clear_1602a() do { write_1602a(false, 0b00000001); _delay_ms(2); } while (0)

#define setaddress_1602a(x, y) write_1602a(false, 0x80 + ((y) * 0x40) + (x))

#define displayon_1602a(cursor, cursor_blink) write_1602a(false, 8 | 4 | ((cursor) ? 2 : 0) | ((cursor_blink) ? 1 : 0))

#define displayoff_1602a() write_1602a(false, 8)

void puts_1602a(const char *str);

void write_1602a(bool register_select, uint8_t value);

#endif // _1602a_LCD_H
