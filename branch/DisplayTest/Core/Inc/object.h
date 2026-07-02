/********************************************************************
*
*   object.h
*
*   Description:    Display objects
*
*   Copyright PPMD, Inc. 2019 -- All rights reserved.
*
*--------------------------------------------------------------------
*
*   Revision History:
*
*   Rev.    | Date      | Name              | Description
*   1       | 09/27/19  | Brian Compter     | Created.
*
********************************************************************/

#ifndef OBJECT_H
#define OBJECT_H

#include "main.h"
#include "lcd.h"

/**
 * Store patterns in memory
 */
typedef enum
{
	ePATTERN_Horizontal,
	ePATTERN_Vertical,
	ePATTERN_Box6,
	ePATTERN_Box2,
	ePATTERN_Box16,
    ePATTERN_Box4,
	ePATTERN_None
}eStorePattern;

/**
 * Object operation type, can be draw or blend
 */
typedef enum
{
	eOpDraw,
	eOpBlend
} eOperationType;

/**
 * Display object
 */
typedef struct
{
	sLocation src;
	sLocation dst;
	sLocation bkg;

	sShape shape;

	uint8_t state;
	uint8_t maxState;
	eStorePattern pattern;
	uint8_t alpha;
} sDisplayObject;

/**
 * Display Queue Object
 * Used to store successive operations that make up a screen redraw
 */
typedef struct
{
	sDisplayObject object;
	eOperationType opType;
	int8_t windowOffset;
	int16_t xOffset;
	int16_t yOffset;
} sObjectQueueItem;

/**
 * Object functions
 */
void ObjectDraw(sDisplayObject obj, int8_t windowOffset, int16_t xOffset, int16_t yOffset);
void ObjectDrawBlend(sDisplayObject obj, int8_t windowOffset, int16_t xOffset, int16_t yOffset);
void ObjectClear(sDisplayObject obj);
void ObjectFill(sDisplayObject obj, sColor color);
void ObjectIncState(sDisplayObject * obj);

#endif
