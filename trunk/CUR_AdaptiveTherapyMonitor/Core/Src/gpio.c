/********************************************************************
 *
 *   gpio.c
 *
 *   Description:    Controls access to general purpose I/O
 *
 *   Copyright NextPhase Medical Devices, Inc. 2026 -- All rights reserved.
 *
 *--------------------------------------------------------------------
 *
 *   Revision History:
 *
 *   Rev.    | Date      | Name              | Description
 *   1       | 06/14/22  | Brian Compter     | Created.
 *
 ********************************************************************/

#include "main.h"
#include "gpio.h"
#include "faulthandler.h"

/**
 * GPIO Pins
 */
sGpio sGpioLedGreen 		= {LED_GREEN_GPIO_Port, LED_GREEN_Pin};
sGpio sGpioLedRed 			= {LED_RED_GPIO_Port, LED_RED_Pin};
sGpio sGpioLedGp1 			= {LED_GP1_GPIO_Port, LED_GP1_Pin};
sGpio sGpioLedGp2 			= {LED_GP2_GPIO_Port, LED_GP2_Pin};

sGpio sGpioAccelSelect		= {ACCEL_SELECT_GPIO_Port, ACCEL_SELECT_Pin};
sGpio sGpioSpi2Select		= {SPI2_SELECT_GPIO_Port, SPI2_SELECT_Pin};

/**
 * Internal functions
 */
void _GpioClearAllEvents(void);
void _GpioHandleGpioDown(sGpio* gpio);
void _GpioHandleGpioUp(sGpio* gpio);

/**
 * @brief Initialize the GPIO system and ports
 * @return None
 */
void GpioInit()
{
	/* Handled via CubeMX init */
}

/**
 * @brief Handle GPIO actions and debouncing
 * @return None
 */
void GpioDrive()
{

}

/**
 * @brief Set the Gpio Output
 * @param dio The Digital IO to set
 * @return None
 */
void GpioSet(sGpio * gpio)
{
	HAL_GPIO_WritePin(gpio->port, gpio->pin, GPIO_PIN_SET);
}

/**
 * @brief Clear the Gpio Output
 * @param dio The Digital IO to clear
 * @return None
 */
void GpioClear(sGpio * gpio)
{
	HAL_GPIO_WritePin(gpio->port, gpio->pin, GPIO_PIN_RESET);
}

/**
 * @brief Read a GPIO pin
 * @param dio The Digital IO to read
 * @return The read value of the gpio
 */
uint8_t GpioRead(sGpio * gpio)
{
	return HAL_GPIO_ReadPin(gpio->port, gpio->pin);
}

/**
 * @brief Write to a GPIO pin
 * @param dio The Digital IO to write
 * @param value The value to write
 * @return None
 */
void GpioWrite(sGpio * gpio, uint8_t value)
{
	if (value)
		GpioSet(gpio);
	else
		GpioClear(gpio);
}

/**
 * @brief Toggle a GPIO pin
 * @param dio The Digital IO to toggle
 * @return None
 */
void GpioToggle(sGpio * gpio)
{
	if (GpioRead(gpio))
		GpioClear(gpio);
	else
		GpioSet(gpio);
}
