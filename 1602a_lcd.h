#ifndef _1602a_LCD_H
#define _1602a_LCD_H

#include <avr/io.h>

#define clear_1602a() do { write_1602a(false, 0x1); _delay_ms(2); } while (0)

#define home_1602a() do { write_1602a(false, 0x2); _delay_ms(2); } while (0)

#define entrymode_1602a(cursor_increment, shift_display) write_1602a(false, 0x4 | ((cursor_increment) ? 2 : 0) | ((shift_display) ? 1 : 0))

#define displayon_1602a(cursor, cursor_blink) write_1602a(false, 0xc | ((cursor) ? 2 : 0) | ((cursor_blink) ? 1 : 0))

#define displayoff_1602a() write_1602a(false, 0x8)

#define cursor_left_1602a write_1602a(false, 0b00010000)

#define cursor_right_1602a write_1602a(false, 0b00010100)

#define display_left_1602a write_1602a(false, 0b00011000)

#define display_right_1602a write_1602a(false, 0b00011100)

#define function_set_1602a(data_8bit, lines_2, large_font) write_1602a(false, 0x20 | ((data_8bit) ? 0x10 : 0) | ((lines_2) ? 0x8 : 0) | ((large_font) ? 0x4 : 0))

#define set_cgaddress_1602a(character, line) write_1602a(false, 0x40 | ((character) << 3) | ((line) & 0x7))

#define set_address_1602a(x, y) write_1602a(false, 0x80 + ((y) * 0x40) + (x))

#define putc_1602a(c) write_1602a(true, (c))

void puts_1602a(const char *str);

void write_1602a(bool register_select, uint8_t value);

#endif // _1602a_LCD_H
