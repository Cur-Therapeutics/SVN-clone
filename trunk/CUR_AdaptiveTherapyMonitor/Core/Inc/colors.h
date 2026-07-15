/********************************************************************
*
*   colors.h
*
*   Description:    Collection of colors common across the system
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
#ifndef INC_COLORS_H_
#define INC_COLORS_H_

#include "main.h"

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
 * Externs
 */
extern sColor colorWhite;
extern sColor colorBlack;
extern sColor colorCurRed;
extern sColor colorCurBlue;
extern sColor colorRed;

#endif /* INC_COLORS_H_ */
