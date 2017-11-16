/*----------------------------------------------------------------------------
 * Name:    LCD.h
 * Purpose: LCD function prototypes
 * Note(s): 
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2009-2013 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

extern void lcd_init       (void);
extern void lcd_clear      (void);
extern void lcd_putchar    (char c);
extern void set_cursor     (int column, int line);
extern void lcd_print      (char *string);
extern void lcd_bargraph   (int value, int size);
extern void lcd_bargraphXY (int pos_x, int pos_y, int value);

/******************************************************************************/

