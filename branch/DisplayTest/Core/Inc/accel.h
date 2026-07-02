/********************************************************************
*
*   accel.h
*
*   Description:    Manages the Accelerometer
*
*   Copyright NextPhase Medical, Inc. 2026 -- All rights reserved.
*
*--------------------------------------------------------------------
*
*   Revision History:
*
*   Rev.    | Date      | Name              | Description
*   1       | 06/17/26  | Brian Compter     | Created.
*
********************************************************************/

#ifndef INC_ACCEL_H_
#define INC_ACCEL_H_

/**
 * Functions
 */
void AccelInit(void);
void AccelDrive(void);

uint32_t AccelReadX(void);
uint32_t AccelReadY(void);
uint32_t AccelReadZ(void);

#endif /* INC_ACCEL_H_ */
