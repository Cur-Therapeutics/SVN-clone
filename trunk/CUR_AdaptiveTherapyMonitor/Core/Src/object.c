/********************************************************************
*
*   object.c
*
*   Description:    Display objects
*
*   Copyright Arterex Medical, Inc. 2026 -- All rights reserved.
*
*--------------------------------------------------------------------
*
*   Revision History:
*
*   Rev.    | Date      | Name              | Description
*   1       | 09/27/19  | Brian Compter     | Created.
*
********************************************************************/

#include "object.h"
#include "lcd.h"
#include "colors.h"

/**
 * @brief Draw an object to the display without blending
 * @param obj The object to draw
 * @param windowOffset The window offset, used for double buffering
 * @param xOffset, top left of object. Screen (0, 0) at top left
 * @param yOffset, top left of object. Screen (0, 0) at top left
 * @return none
 */
void ObjectDraw(sDisplayObject obj, int8_t windowOffset, int16_t xOffset, int16_t yOffset)
{
	// Validate state
	if (obj.state > obj.maxState)
	{
		obj.state = obj.maxState;
	}

	// Adjust source address per state and memory pattern
	switch (obj.pattern)
	{
		case ePATTERN_Horizontal:
			obj.src.xPos += (obj.state * obj.shape.width);
			break;
		case ePATTERN_Vertical:
			obj.src.yPos += (obj.state * obj.shape.height);
			break;
		case ePATTERN_Box6:
			obj.src.xPos += (obj.state % 6 * obj.shape.width);
			obj.src.yPos += (obj.state / 6 * obj.shape.height);
			break;
		case ePATTERN_Box2:
			obj.src.xPos += (obj.state % 2 * obj.shape.width);
			obj.src.yPos += (obj.state / 2 * obj.shape.height);
			break;
		case ePATTERN_Box16:
			obj.src.xPos += (obj.state % 16 * obj.shape.width);
			obj.src.yPos += (obj.state / 16 * obj.shape.height);
			break;
		case ePATTERN_Box4:
			obj.src.xPos += (obj.state % 4 * obj.shape.width);
			obj.src.yPos += (obj.state / 4 * obj.shape.height);
			break;
		default:
			/* No adjustment */
			break;
	}

	// Adjust destination address per offsets
	obj.dst.window += windowOffset;
	obj.dst.xPos += xOffset;
	obj.dst.yPos += yOffset;

	// Write to the LCD
	LCD_Write(obj.src, obj.dst, obj.shape);
}

/**
 * @brief Draw an object to the display with blending
 * @param obj The object to draw
 * @param windowOffset The window offset, used for double buffering
 * @param xOffset, top left of object. Screen (0, 0) at top left
 * @param yOffset, top left of object. Screen (0, 0) at top left
 * @return none
 */
void ObjectDrawBlend(sDisplayObject obj, int8_t windowOffset, int16_t xOffset, int16_t yOffset)
{
	// Validate state
	if (obj.state > obj.maxState)
	{
		obj.state = obj.maxState;
	}

	// Adjust source address per state and memory pattern
	switch (obj.pattern)
	{
		case ePATTERN_Horizontal:
			obj.src.xPos += (obj.state * obj.shape.width);
			break;
		case ePATTERN_Vertical:
			obj.src.yPos += (obj.state * obj.shape.height);
			break;
		case ePATTERN_Box6:
			obj.src.xPos += (obj.state % 6 * obj.shape.width);
			obj.src.yPos += (obj.state / 6 * obj.shape.height);
			break;
		case ePATTERN_Box2:
			obj.src.xPos += (obj.state % 2 * obj.shape.width);
			obj.src.yPos += (obj.state / 2 * obj.shape.height);
			break;
		case ePATTERN_Box16:
			obj.src.xPos += (obj.state % 16 * obj.shape.width);
			obj.src.yPos += (obj.state / 16 * obj.shape.height);
			break;
		case ePATTERN_Box4:
			obj.src.xPos += (obj.state % 4 * obj.shape.width);
			obj.src.yPos += (obj.state / 4 * obj.shape.height);
			break;
		default:
			/* No adjustment */
			break;
	}

	// Adjust destination and background address per offsets
	obj.dst.window += windowOffset;
	obj.dst.xPos += xOffset;
	obj.dst.yPos += yOffset;

	obj.bkg.window += windowOffset;
	obj.bkg.xPos += xOffset;
	obj.bkg.yPos += yOffset;

	// Blend to the LCD
	LCD_Blend(obj.src, obj.bkg, obj.dst, obj.shape);
}

/**
 * @brief Clear an objects location
 * @param obj The object to clear
 * @return none
 */
void ObjectClear(sDisplayObject obj)
{
	LCD_FillLocation(obj.dst, obj.shape, colorBlack, 0);
}

/**
 * @brief Fill an objects location
 * @param obj The object to fill
 * @param color The color to fill with
 * @return none
 */
void ObjectFill(sDisplayObject obj, sColor color)
{
	LCD_FillLocation(obj.dst, obj.shape, color, 255);
}

/**
 * @brief Increment an objects state safely
 * @param obj The object whose state to increment
 * @return None
 */
void ObjectIncState(sDisplayObject * obj)
{
	obj->state++;
	if (obj->state > obj->maxState)
	{
		obj->state = 0;
	}
}
