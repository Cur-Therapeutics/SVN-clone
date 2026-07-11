/********************************************************************
*
*   displaystructs.h
*
*   Description:    Helper header file with commonly used display structures
*
*   Copyright NextPhase Medical, Inc. 2026 -- All rights reserved.
*
*--------------------------------------------------------------------
*
*   Revision History:
*
*   Rev.    | Date      | Name              | Description
*   1       | 03/15/22  | Brian Compter     | Created.
*
********************************************************************/

#ifndef DISPLAY_STRUCTS_H
#define DISPLAY_STRUCTS_H

/**
 * Location object
 */
typedef struct
{
	uint16_t xPos;
	uint16_t yPos;
	uint16_t window;
}sLocation;

/**
 * @define Pixel data
 */
typedef struct
{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
}sPixel;

/**
 * Shape object
 */
typedef struct
{
	uint32_t width;
	uint32_t height;
}sShape;

#endif
