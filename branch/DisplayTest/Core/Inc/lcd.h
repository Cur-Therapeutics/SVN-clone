/********************************************************************
*
*   lcd.h
*
*   Description:    Controls the LCD interface
*
*   Copyright NextPhase Medical, Inc. 2019 -- All rights reserved.
*
*--------------------------------------------------------------------
*
*   Functions:	LCD_Drive()
*				LCD_SetDisplayWindow()
*				LCD_Write()
*				LCD_FillWindow()
*
*--------------------------------------------------------------------
*
*   Revision History:
*
*   Rev.    | Date      | Name              | Description
*   1       | 08/19/19  | Brian Compter     | Created.
*
********************************************************************/

#ifndef LCD_H
#define LCD_H

#include "main.h"
#include "displaystructs.h"

#define COUNTOF_gDisplays 16

extern uint32_t gDisplays[COUNTOF_gDisplays];
extern int32_t gDisplaysCRC[COUNTOF_gDisplays];          // CRC for gdisplay[]
extern int32_t gDisplaysSize[COUNTOF_gDisplays];         // Size for gdisplay[]

/**
 * Frame buffer addresses
 */
#define RAMBUFF_START_ADDR	((uint32_t)0x90000000)
#define DISPLAY_WIDTH		(320)
#define DISPLAY_HEIGHT		(240)
#define BYTES_PER_PIXEL		(4)
#define BYTES_PER_RGB		(3)
#define LINE_SIZE			(DISPLAY_WIDTH*BYTES_PER_PIXEL)
#define FRAMEBUFFER_SIZE	(DISPLAY_WIDTH * DISPLAY_HEIGHT * BYTES_PER_PIXEL)  // Equal to two (2) sectors  (0x7F800)
#define WINDOW_0 			((uint32_t)RAMBUFF_START_ADDR)
#define WINDOW_1 			((uint32_t)WINDOW_0 + FRAMEBUFFER_SIZE)
#define WINDOW_2 			((uint32_t)WINDOW_1 + FRAMEBUFFER_SIZE)
#define WINDOW_3 			((uint32_t)WINDOW_2 + FRAMEBUFFER_SIZE)
#define WINDOW_4 			((uint32_t)WINDOW_3 + FRAMEBUFFER_SIZE)
#define WINDOW_5 			((uint32_t)WINDOW_4 + FRAMEBUFFER_SIZE)
#define WINDOW_6 			((uint32_t)WINDOW_5 + FRAMEBUFFER_SIZE)
#define WINDOW_7 			((uint32_t)WINDOW_6 + FRAMEBUFFER_SIZE)
#define WINDOW_8 			((uint32_t)WINDOW_7 + FRAMEBUFFER_SIZE)
#define WINDOW_9 			((uint32_t)WINDOW_8 + FRAMEBUFFER_SIZE)
#define WINDOW_10 			((uint32_t)WINDOW_9 + FRAMEBUFFER_SIZE)
#define WINDOW_11 			((uint32_t)WINDOW_10 + FRAMEBUFFER_SIZE)
#define WINDOW_12 			((uint32_t)WINDOW_11 + FRAMEBUFFER_SIZE)
#define WINDOW_13 			((uint32_t)WINDOW_12 + FRAMEBUFFER_SIZE)
#define WINDOW_14 			((uint32_t)WINDOW_13 + FRAMEBUFFER_SIZE)
#define WINDOW_15 			((uint32_t)WINDOW_14 + FRAMEBUFFER_SIZE)
#define WINDOW_INDEX_MAX	15

/**
 * Timeout for polled operations
 */
#define DMA2D_TIMEOUT	64

/**
 * Backlight settings
 */
#define LCD_BACKLIGHT_FULL 1000
#define LCD_BACKLIGHT_DIM	500
#define LCD_BACKLIGHT_MIN	 50

/**
 * Color object
 */
typedef struct
{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
}sColor;

/**
 * Reference to lcd and dma2d objects
 */
extern LTDC_HandleTypeDef hltdc;
extern DMA2D_HandleTypeDef hdma2d;

void BlurScreen(sLocation * loc);
void BlurScreenRect(sLocation * loc, sShape shape);

void LCD_Drive();
void LCD_SetDisplayWindow(uint8_t window);
void LCD_SetOverlayWindow(uint8_t window);
uint8_t LCD_GetDisplayIndex();
uint32_t LCD_GetWindowAddress(uint8_t window);
void LCD_Write(sLocation src, sLocation dst, sShape shape);
void LCD_Blend(sLocation src, sLocation background, sLocation dst, sShape shape, uint8_t alpha);
void LCD_BlendFont(sLocation src, sLocation background, sLocation dst, sShape shape, sColor color);
void LCD_StartTransfer(void);
//void LCD_QueueTransfer(sDisplayObject *obj);
void HAL_DMA2D_XferCpltCallback(DMA2D_HandleTypeDef *hdma2d);
void LCD_FillWindow(uint8_t window, sColor color);
void LCD_ClearWindow(uint8_t window);
void LCD_WriteTestImage(uint8_t window);
void LCD_Draw(uint16_t x, uint16_t y, sColor color);
uint16_t LCD_GetBacklight();
void LCD_SetBacklight(uint16_t value);
void LCD_FillLocation(sLocation loc, sShape sh, sColor color, uint8_t alpha);
void LCD_FillLocation_Queue(sLocation loc, sShape sh, uint16_t color, uint8_t alpha);
void LCD_DrawBox(sLocation loc, sShape sh, uint16_t thickness, sColor color, uint8_t alpha);

void LCD_FillGrey(uint8_t window);
void LCD_FillGradient(uint8_t window, uint32_t * gradData);

extern uint32_t gDisplays[];

#endif
