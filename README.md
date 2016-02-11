Example of how to drive a 1602a LCD from an AVR ATmega32u4 with a 74HC595
shift register.

## Wiring

```
32u4 D0 - 1602a E
32u4 D1 - 1602a RS
ground  - 1602a R/W
32u4 E6 - 74HC595 DS
32u4 B5 - 74HC595 SHCP
32u4 B4 - 74HC595 STCP
pull up - 74HC595 !MR
ground  - 74HC595 !OE
```

The 74HC595 should have Q0-Q7 wired to D0-D7 on the LCD board. 

## Example

![alt text](https://raw.githubusercontent.com/hollobon/1602a_lcd/master/breadboard.jpg "Wired up on a breadboard")

## Datasheet

[Hitachi HD44780U][https://www.sparkfun.com/datasheets/LCD/HD44780.pdf].


