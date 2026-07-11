/********************************************************************
 *
 *   gpio.h
 *
 *   Description:
 *
 *   Copyright NextPhase Medical Devices, Inc. 2023 -- All rights reserved.
 *
 *--------------------------------------------------------------------
 *
 *   Revision History:
 *
 *   Rev.    | Date      | Name              | Description
 *   1       | 06/14/22  | Brian Compter     | Created.
 *
 ********************************************************************/
#ifndef INCLUDES_GPIO_H_
#define INCLUDES_GPIO_H_

#include "main.h"
#include "stm32u5xx_hal.h"
#include "stm32u5xx.h"

/**
 * Debounce value in millisecond
 */
#define GPIO_DEBOUNCE		100

/**
 * Structure of a GPIO port including event and debounce functionality
 */
typedef struct
{
	GPIO_TypeDef * port;
	uint16_t pin;
	uint8_t event;
	uint16_t debounce;
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
extern sGpio sGpioLedGreen;
extern sGpio sGpioLedRed;
extern sGpio sGpioSpi1Select;
extern sGpio sGpioSpi2Select;

#endif /* INCLUDES_GPIO_H_ */
