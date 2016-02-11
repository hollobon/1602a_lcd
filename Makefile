F_CPU = 16000000
ARCH = AVR8
MCU = atmega32u4

TARGET = 1602a_example

SRC = 1602a_lcd.c 1602a_example.c

include rules.mk
