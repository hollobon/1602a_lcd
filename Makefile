F_CPU = 16000000
ARCH = AVR8
MCU = atmega32u4

TARGET = 1602a_lcd

SRC = 1602a_lcd.c

include rules.mk
