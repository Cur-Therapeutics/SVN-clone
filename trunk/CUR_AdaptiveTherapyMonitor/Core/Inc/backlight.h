/********************************************************************
*
*   backlight.h
*
*   Description:    Manages the backlight through a PWM timer
*
*
*--------------------------------------------------------------------
*
*   Revision History:
*
*   Rev.    | Date      | Name              | Description
*   1       | 12/27/23  | Brian Compter     | Created.
*
********************************************************************/

#ifndef INC_BACKLIGHT_H_
#define INC_BACKLIGHT_H_

/**
 * Backlight values
 */
#define BACKLIGHT_FULL	300
#define BACKLIGHT_DIM	250 /* 750 */
#define BACKLIGHT_SPEED	100

/**
 * Timer delay
 */
#define BACKLIGHT_TIMER	10

extern uint16_t mBacklightTarget;

void BacklightInit(void);
void BacklightDrive(void);
void BacklightSet(uint16_t val);
void BacklightTarget(uint16_t val);
void BacklightOn(void);
void BacklightOff(void);
uint8_t BacklightAtTarget(void);

#endif /* INC_BACKLIGHT_H_ */
