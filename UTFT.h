/*
  UTFT.h - Multi-Platform library support for Color TFT LCD Boards
  Copyright (C)2015-2018 Rinky-Dink Electronics, Henning Karlsen. All right reserved
  
  This library is the continuation of my ITDB02_Graph, ITDB02_Graph16
  and RGB_GLCD libraries for Arduino and chipKit. As the number of 
  supported display modules and controllers started to increase I felt 
  it was time to make a single, universal library as it will be much 
  easier to maintain in the future.

  Basic functionality of this library was origianlly based on the 
  demo-code provided by ITead studio (for the ITDB02 modules) and 
  NKC Electronics (for the RGB GLCD module/shield).

  This library supports a number of 8bit, 16bit and serial graphic 
  displays, and will work with both Arduino, chipKit boards and select 
  TI LaunchPads. For a full list of tested display modules and controllers,
  see the document UTFT_Supported_display_modules_&_controllers.pdf.

  When using 8bit and 16bit display modules there are some 
  requirements you must adhere to. These requirements can be found 
  in the document UTFT_Requirements.pdf.
  There are no special requirements when using serial displays.

  You can find the latest version of the library at 
  http://www.RinkyDinkElectronics.com/

  This library is free software; you can redistribute it and/or
  modify it under the terms of the CC BY-NC-SA 3.0 license.
  Please see the included documents for further information.

  Commercial use of this library requires you to buy a license that
  will allow commercial use. This includes using the library,
  modified or not, as a tool to sell products.

  The license applies to all part of the library including the 
  examples and tools supplied with the library.
*/

#ifndef UTFT_h
#define UTFT_h

#define UTFT_VERSION	283

#define LEFT 0
#define RIGHT 9999
#define CENTER 9998

#define PORTRAIT 0
#define LANDSCAPE 1

#define NOTINUSE		255

//*********************************
// COLORS
//*********************************
// VGA color palette
#define VGA_BLACK		0x0000
#define VGA_WHITE		0xFFFF
#define VGA_RED			0xF800
#define VGA_GREEN		0x0400
#define VGA_BLUE		0x001F
#define VGA_SILVER		0xC618
#define VGA_GRAY		0x8410
#define VGA_MAROON		0x8000
#define VGA_YELLOW		0xFFE0
#define VGA_OLIVE		0x8400
#define VGA_LIME		0x07E0
#define VGA_AQUA		0x07FF
#define VGA_TEAL		0x0410
#define VGA_NAVY		0x0010
#define VGA_FUCHSIA		0xF81F
#define VGA_PURPLE		0x8010
#define VGA_TRANSPARENT	0xFFFFFFFF

#include <avr/pgmspace.h>
#include <stdbool.h>
#include "HW_AVR_defines.h"

typedef uint8_t byte;
typedef unsigned int word;

struct _current_font
{
	uint8_t* font;
	uint8_t x_size;
	uint8_t y_size;
	uint8_t offset;
	uint8_t numchars;
};

void setupLCDPorts(byte model, int RS, int WR, int CS, int RST, int SER);
void	InitLCD(byte orientation);
void	clrScr();
void	drawPixel(int x, int y);
void	drawLine(int x1, int y1, int x2, int y2);
void	fillScr_rgb(byte r, byte g, byte b);
void	fillScr(word color);
void	drawRect(int x1, int y1, int x2, int y2);
void	drawRoundRect(int x1, int y1, int x2, int y2);
void	fillRect(int x1, int y1, int x2, int y2);
void	fillRoundRect(int x1, int y1, int x2, int y2);
void	drawCircle(int x, int y, int radius);
void	fillCircle(int x, int y, int radius);
void	setColor_rgb(byte r, byte g, byte b);
void	setColor(word color);
word	getColor();
void	setBackColor_rgb(byte r, byte g, byte b);
void	setBackColor(uint32_t color);
word	getBackColor();
void	print(char *st, int x, int y, int deg);
void	printNumI(long num, int x, int y, int length, char filler);
void	printNumF(double num, byte dec, int x, int y, char divider, int length, char filler);
void	setFont(uint8_t* font);
uint8_t* getFont();
uint8_t	getFontXsize();
uint8_t	getFontYsize();
void	lcdOff();
void	lcdOn();
void	setContrast(char c);
int		getDisplayXSize();
int		getDisplayYSize();
void	setBrightness(byte br);
void	setDisplayPage(byte page);
void	setWritePage(byte page);

/*
The functions and variables below should not normally be used.
They have been left publicly available for use in add-on libraries
that might need access to the lower level functions of UTFT.

Please note that these functions and variables are not documented
and I do not provide support on how to use them.
*/
byte			fch, fcl, bch, bcl;
byte			orient;
long			disp_x_size, disp_y_size;
byte			display_model, display_transfer_mode, display_serial_mode;
regtype			*P_RS, *P_WR, *P_CS, *P_RST, *P_SDA, *P_SCL, *P_ALE;
regsize			B_RS, B_WR, B_CS, B_RST, B_SDA, B_SCL, B_ALE;
byte			__p1, __p2, __p3, __p4, __p5;
struct _current_font	cfont;
bool			_transparent;

void LCD_Writ_Bus(char VH,char VL, byte mode);
void LCD_Write_COM(char VL);
void LCD_Write_DATA(char VH,char VL);
void LCD_Write_DATA_vl(char VL);
void LCD_Write_COM_DATA(char com1,int dat1);
void LCD_Write_Bus_8(char VL);
void LCD_Write_DATA_8(char VL);		
void _hw_special_init();
void setPixel(word color);
void drawHLine(int x, int y, int l);
void drawVLine(int x, int y, int l);
void printChar(byte c, int x, int y);
void setXY(word x1, word y1, word x2, word y2);
void clrXY();
void rotateChar(byte c, int x, int y, int pos, int deg);
void _set_direction_registers(byte mode);
void _fast_fill_16(int ch, int cl, long pix);
void _fast_fill_8(int ch, long pix);
void _convert_float(char *buf, double num, int width, byte prec);

#endif