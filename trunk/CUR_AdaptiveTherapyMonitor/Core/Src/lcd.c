/********************************************************************
 *
 *   lcd.c
 *
 *   Description:    Control the LCD interface
 *
 *   Copyright NextPhase Medical, Inc. 2026 -- All rights reserved.
 *
 *--------------------------------------------------------------------
 *
 *   Revision History:
 *
 *   Rev.    | Date      | Name              | Description
 *   1       | 08/19/19  | Brian Compter     | Created.
 *
 ********************************************************************/

#include <string.h>
#include "main.h"
#include "lcd.h"
#include "health.h"
#include "faulthandler.h"

extern sColor sColorGrey;

/**
 * Collection of display frame buffer addresses
 */
uint32_t gDisplays[COUNTOF_gDisplays] =
{
		WINDOW_0, WINDOW_1, WINDOW_2, WINDOW_3, WINDOW_4, WINDOW_5,
		WINDOW_6, WINDOW_7, WINDOW_8, WINDOW_9, WINDOW_10, WINDOW_11,
		WINDOW_12, WINDOW_13, WINDOW_14, WINDOW_15
};

/**
 * The current display window
 */
uint8_t gCurrentDisplay;

/**
 * Count DMA2D transfer errors for diagnostics
 */
uint32_t gDMA2DTransferErrorCount = 0;

/**
 * Controls backlight
 */
uint16_t mDesiredBacklight = 1000;
uint16_t mActualBacklight = 1000;

extern uint8_t mBufferState;

/**
 * @brief  Process LCD health
 * @retval None
 */
void LCD_Drive()
{
	uint32_t stateLcd = HAL_LTDC_GetState(&hltdc);
	uint32_t stateDma = HAL_DMA2D_GetState(&hdma2d);
	if (stateLcd == HAL_LTDC_STATE_ERROR || stateLcd == HAL_LTDC_STATE_RESET)
	{
		HealthSubsystemBad(eSystemLcd);
	}
	else if (stateDma == HAL_DMA2D_STATE_ERROR || stateDma == HAL_DMA2D_STATE_RESET)
	{
		HealthSubsystemBad(eSystemLcd);
	}
	else
	{
		HealthSubsystemGood(eSystemLcd);
	}
}

/**
 * @brief  Set the frame buffer display window
 * @param window The desired window to display
 * @retval None
 */
void LCD_SetDisplayWindow(uint8_t window)
{
	gCurrentDisplay = window;
	HAL_StatusTypeDef result;

	result = HAL_LTDC_SetAddress(&hltdc, gDisplays[window], 0);

	if (result != HAL_OK)
	{
		FaultHandler(ERR_LCD_ADDRESS);
	}
}

/**
 * @brief  Set the overlay display window
 * @param window The desired window to overlay
 * @retval None
 */
void LCD_SetOverlayWindow(uint8_t window)
{
	HAL_StatusTypeDef result = HAL_LTDC_SetAddress(&hltdc, gDisplays[window], 1);
	if (result != HAL_OK)
	{
		FaultHandler(ERR_LCD_ADDRESS);
	}
}

/**
 * @brief  Get the current display index
 * @retval The current display index
 */
uint8_t LCD_GetDisplayIndex()
{
	return gCurrentDisplay;
}

/**
 * @brief  Get the frame buffer address of a given window
 * @param window The desired window
 * @retval None
 */
uint32_t LCD_GetWindowAddress(uint8_t window)
{
	if (window > WINDOW_INDEX_MAX)
		window = 0;
	return gDisplays[window];
}

/**
 * @brief  Write to the frame buffer
 * @param src The source location
 * @param dst The destination location
 * @param shape The shape of area to write
 * @retval None
 */
void LCD_Write(sLocation src, sLocation dst, sShape shape)
{
	// Calculate source and destination addresses
	uint32_t srcAddr = (gDisplays[src.window] + src.yPos * DISPLAY_WIDTH * BYTES_PER_PIXEL + src.xPos * BYTES_PER_PIXEL);
	uint32_t dstAddr = (gDisplays[dst.window] + dst.yPos * DISPLAY_WIDTH * BYTES_PER_PIXEL + dst.xPos * BYTES_PER_PIXEL);

	// Configure DMA2D
	hdma2d.Init.Mode = DMA2D_M2M;
	hdma2d.Init.ColorMode = DMA2D_OUTPUT_ARGB8888;
	hdma2d.Init.OutputOffset = (DISPLAY_WIDTH - shape.width);
	hdma2d.LayerCfg[1].InputColorMode = DMA2D_INPUT_ARGB8888;
	hdma2d.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
	hdma2d.LayerCfg[1].InputOffset = (DISPLAY_WIDTH - shape.width);
	uint8_t error = 1;
	uint8_t abortResult;

	UNUSED(abortResult);	// Suppress warning

	if(HAL_DMA2D_Init(&hdma2d) != HAL_OK)
	{
		FaultHandler(ERR_LCD_WRITE);
		return;
	}

	if(HAL_DMA2D_ConfigLayer(&hdma2d, 1) != HAL_OK)
	{
		FaultHandler(ERR_LCD_WRITE);
		return;
	}

	while (error != HAL_OK)
	{
		if (HAL_DMA2D_Start(&hdma2d, srcAddr, dstAddr, shape.width, shape.height) == HAL_OK)
		{
			/* Polling For DMA transfer */
			error = HAL_DMA2D_PollForTransfer(&hdma2d, DMA2D_TIMEOUT);
			if (error != HAL_OK)
			{
				abortResult = HAL_DMA2D_Abort(&hdma2d);
				gDMA2DTransferErrorCount++;
			}
		}
	}

	if (error != HAL_OK)
	{
		FaultHandler(ERR_LCD_WRITE);
	}
}

/**
 * @brief  Write to the frame buffer
 * @param src The source location
 * @param background The background location to blend with
 * @param dst The destination location
 * @param shape The shape of area to write
 * @retval None
 */
void LCD_Blend(sLocation src, sLocation background, sLocation dst, sShape shape)
{
    if ((LCD_WindowIsValid(src.window) == 0U) || (LCD_WindowIsValid(background.window) == 0U) || (LCD_WindowIsValid(dst.window) == 0U))
	{
		FaultHandler(ERR_LCD_BLEND);
		return;
	}

	if ((src.xPos + shape.width > DISPLAY_WIDTH) || (src.yPos + shape.height > DISPLAY_HEIGHT) ||
		(background.xPos + shape.width > DISPLAY_WIDTH) || (background.yPos + shape.height > DISPLAY_HEIGHT) ||
		(dst.xPos + shape.width > DISPLAY_WIDTH) || (dst.yPos + shape.height > DISPLAY_HEIGHT))
	{
		FaultHandler(ERR_LCD_BLEND);
		return;
	}

	// Calculate source and destination addresses
	uint32_t srcAddr 		= (gDisplays[src.window] + src.yPos * DISPLAY_WIDTH * BYTES_PER_PIXEL + src.xPos * BYTES_PER_PIXEL);
	uint32_t backgroundAddr = (gDisplays[background.window] + background.yPos * DISPLAY_WIDTH * BYTES_PER_PIXEL + background.xPos * BYTES_PER_PIXEL);
	uint32_t dstAddr 		= (gDisplays[dst.window] + dst.yPos * DISPLAY_WIDTH * BYTES_PER_PIXEL + dst.xPos * BYTES_PER_PIXEL);

	// Configure DMA2D
	hdma2d.Init.Mode = DMA2D_M2M_BLEND;
	hdma2d.Init.ColorMode = DMA2D_OUTPUT_ARGB8888;
	hdma2d.Init.OutputOffset = (DISPLAY_WIDTH - shape.width);
	hdma2d.LayerCfg[0].InputColorMode = DMA2D_INPUT_ARGB8888;
	hdma2d.LayerCfg[0].AlphaMode = DMA2D_NO_MODIF_ALPHA;
	hdma2d.LayerCfg[0].InputOffset = (DISPLAY_WIDTH - shape.width);
	hdma2d.LayerCfg[1].InputColorMode = DMA2D_INPUT_ARGB8888;
	hdma2d.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
	hdma2d.LayerCfg[1].InputOffset = (DISPLAY_WIDTH - shape.width);
	uint8_t error = 1;

	if(HAL_DMA2D_Init(&hdma2d) != HAL_OK)
	{
		FaultHandler(ERR_LCD_BLEND);
		return;
	}

	if(HAL_DMA2D_ConfigLayer(&hdma2d, 1) != HAL_OK)
	{
		FaultHandler(ERR_LCD_BLEND);
		return;
	}

	if(HAL_DMA2D_ConfigLayer(&hdma2d, 0) != HAL_OK)
	{
		FaultHandler(ERR_LCD_BLEND);
		return;
	}

	while (error != HAL_OK)
	{
		if (HAL_DMA2D_BlendingStart(&hdma2d, srcAddr, backgroundAddr, dstAddr, shape.width, shape.height) == HAL_OK)
		{
			/* Polling For DMA transfer */
			error = HAL_DMA2D_PollForTransfer(&hdma2d, DMA2D_TIMEOUT);
			if (error != HAL_OK)
				gDMA2DTransferErrorCount++;
		}
	}

	if (error != HAL_OK)
	{
		FaultHandler(ERR_LCD_BLEND);
	}
}

/**
 * @brief  Fill a window with a solid color
 * @param window The window to fill
 * @param color The color to fill with
 * @retval None
 */
void LCD_FillWindow(uint8_t window, sColor color)
{
	uint32_t * ptrFrameBuffer = (uint32_t*)(gDisplays[window]);
	uint32_t temp = (color.blue) + (color.green << 8) + (color.red << 16) + (0xFF000000);
	for (int i = 0; i < FRAMEBUFFER_SIZE / BYTES_PER_PIXEL; i++)
	{
		*ptrFrameBuffer++ = temp;
	}
}

/**
 * @brief  Fill a window with a gradient
 * @param window The window to apply the gradient to
 * @param gradData The color to fill with
 * @retval None
 */
void LCD_FillGradient(uint8_t window, uint32_t * gradData)
{
	uint32_t * ptrFrameBuffer = (uint32_t*)(gDisplays[window]);
	for (int y = 0; y < DISPLAY_HEIGHT; y++)
	{
		for (int x = 0; x < DISPLAY_WIDTH; x++)
		{
			*ptrFrameBuffer++ = gradData[DISPLAY_WIDTH - x - 1];
		}
	}
}

/**
 * @brief  Fill a window with a solid color
 * @param color The color to fill with
 * @retval None
 */
void LCD_FillGrey(uint8_t window)
{
	uint32_t * ptrFrameBuffer = (uint32_t*)(gDisplays[window]);
	uint32_t temp;

	uint32_t val = 255;

	for (int i = 0; i < FRAMEBUFFER_SIZE / BYTES_PER_PIXEL; i++)
	{
		if (i % LINE_SIZE == 0 && val > 0 && i > LINE_SIZE * 110)
			val-=2;

		temp = (val) + (val << 8) + (val << 16) + (0xFF000000);
		*ptrFrameBuffer++ = temp;
	}
}

/**
 * @brief  Fill a location with a solid color
 * @param loc 	The location to fill
 * @param sh 	The shape to fill
 * @param color The color to fill with
 * @param alpha The alpha component (should be 100 for blur)
 * @retval None
 */
void LCD_FillLocation(sLocation loc, sShape sh, sColor color, uint8_t alpha)
{
	if ( loc.window > sizeof(gDisplays))    // Sanity check
		return;

	// Set our window initial position
	uint8_t * ptrWindow = (uint8_t*)(gDisplays[loc.window]);

	// Convert our xy position
	uint16_t temp = loc.xPos;
	loc.xPos = DISPLAY_WIDTH - loc.yPos - sh.height;
	loc.yPos = temp;

	if (loc.xPos > DISPLAY_WIDTH)
		loc.xPos = DISPLAY_WIDTH;
	if (loc.yPos > DISPLAY_HEIGHT)
		loc.yPos = DISPLAY_HEIGHT;

	// Adjust position to our location
	ptrWindow += (loc.xPos * BYTES_PER_PIXEL) + (loc.yPos * DISPLAY_WIDTH * BYTES_PER_PIXEL);

	if ( alpha < 0 ) alpha = 0;
	if ( alpha > 255 ) alpha = 255;

	float mult1 = (float) alpha / 255.0;
	float mult2 = 1.0 - mult1;

	// Fill it up
	uint32_t size = sh.width * sh.height;
	uint32_t offset =  (DISPLAY_WIDTH - sh.height) * BYTES_PER_PIXEL;
	for (int i = 0; i < size; i++)
	{
		if (alpha != 100)
		{
			*ptrWindow++ = color.blue;
			*ptrWindow++ = color.green;
			*ptrWindow++ = color.red;
			*ptrWindow++ = alpha;
		}
		else
		{
			*ptrWindow = color.blue * mult1 + *ptrWindow * mult2;
			ptrWindow++;
			*ptrWindow = color.green * mult1 + *ptrWindow * mult2;
			ptrWindow++;
			*ptrWindow = color.red * mult1 + *ptrWindow * mult2;
			ptrWindow++;
			*ptrWindow = alpha;
			ptrWindow++;
		}
		// Handle width wrap
		if ((i+1) % sh.height == 0)
		{
			ptrWindow += offset;
		}
	}
}

/**
 * @brief  Clear a window including the alpha component
 * @retval None
 */
void LCD_ClearWindow(uint8_t window)
{
	memset((uint8_t*)(gDisplays[window]), 0, FRAMEBUFFER_SIZE);
}

/**
 * @brief  Fill a window with a test image
 * @param window The window to place the test image
 * @retval None
 */
void LCD_WriteTestImage(uint8_t window)
{

}

/**
 * @brief  Draw a pixel on the LCD red
 * @param	x coordinate of the pixel
 * @param	y coordinate of the pixel
 * @retval None
 */
void LCD_Draw(uint16_t x, uint16_t y, sColor color)
{
	uint16_t xPrime;
	uint16_t yPrime;

	xPrime = DISPLAY_WIDTH - y;
	yPrime = x;

	if (yPrime > DISPLAY_HEIGHT)
		yPrime = 0;
	if (xPrime > DISPLAY_WIDTH)
		xPrime = 0;

	uint8_t * ptrFrameBuffer = (uint8_t*)(gDisplays[gCurrentDisplay]);
	ptrFrameBuffer += xPrime * BYTES_PER_PIXEL + (yPrime * LINE_SIZE);

	*ptrFrameBuffer++ = color.red;
	*ptrFrameBuffer++ = color.green;
	*ptrFrameBuffer++ = color.blue;
	*ptrFrameBuffer++ = 255;
}

/**
 * @brief  Get the current back light value
 * @retval the actual back light value
 */
uint16_t LCD_GetBacklight()
{
	return mActualBacklight;
}

/**
 * @brief  Set the desired back light value
 * @param value Brightness from 0 to 1,000
 * @retval None
 */
void LCD_SetBacklight(uint16_t value)
{
	// Guard against bad values
	if (value > LCD_BACKLIGHT_FULL)
		value = LCD_BACKLIGHT_FULL;
	if (value < LCD_BACKLIGHT_MIN)
		value = LCD_BACKLIGHT_MIN;

	// Set desired value, this will be sent to the LCD on the next call to LCD_Drive.
	mDesiredBacklight = value;
}

/**
 * @brief Return true it window ID contains a valid address.
 * @param window
 * @return 1 if the window is valid, 0 otherwise
 */
uint8_t LCD_WindowIsValid(uint8_t window)
{
	if (window > WINDOW_INDEX_MAX)
	{
		return 0U;
	}

	return 1;
}
