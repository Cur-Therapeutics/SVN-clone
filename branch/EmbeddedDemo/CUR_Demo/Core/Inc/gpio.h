/********************************************************************
*
*   gpio.h
*
*   Description:    Gpio interface
*
*   Copyright NextPhase Medical, Inc. 2025 -- All rights reserved.
*
*--------------------------------------------------------------------
*
*   Revision History:
*
*   Rev.    | Date      | Name              | Description
*   1       | 05/21/25  | Brian Compter     | Created.
*
********************************************************************/
#ifndef INCLUDES_GPIO_H_
#define INCLUDES_GPIO_H_

#include "main.h"
#include "stdint.h"

/**
 * Structure of a GPIO port including event and debounce functionality
 */
typedef struct
{
	GPIO_TypeDef * port;
	uint16_t pin;
} sGpio;

/**
 * Functions
 */
void GpioInit(void);
uint8_t GpioRead(sGpio * gpio);
void GpioWrite(sGpio * gpio, uint8_t value);
void GpioSet(sGpio * gpio);
void GpioClear(sGpio * gpio);
void GpioToggle(sGpio * gpio);
void GpioDrive();

/**
 * Externs used by other software units
 */
extern sGpio sGpioV1A;
extern sGpio sGpioV1B;
extern sGpio sGpioV2;
extern sGpio sGpioV3;

extern sGpio sGpioSpi1Select;
extern sGpio sGpioSpi2Select;
extern sGpio sGpioSpi3Select;

#endif /* INCLUDES_GPIO_H_ */
