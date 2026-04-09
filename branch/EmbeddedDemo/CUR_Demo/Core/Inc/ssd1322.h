#ifndef INC_SSD1322_H_
#define INC_SSD1322_H_

#include "main.h"

/* ─── Pin / peripheral configuration ──────────────────────────────────────── */

/* Change these to match your CubeMX-generated handle and GPIO labels */
#define OLED_SPI_HANDLE     hspi3

#define OLED_CS_PORT        GPIOB
#define OLED_CS_PIN         GPIO_PIN_9

#define OLED_DC_PORT        GPIOD
#define OLED_DC_PIN         GPIO_PIN_12

#define OLED_RST_PORT       GPIOD
#define OLED_RST_PIN        GPIO_PIN_5

/**
 *
 */
#define HAL_SPI_DELAY	5000

void oled_run_tests(void);

void tft_run_tests(void);

void oled_write_cmd(uint8_t cmd);

void oled_write_data(uint8_t data);

void oled_cs_low();
void oled_dc_command();
void oled_dc_data();
void oled_cs_high();
void oled_reset();

#endif /* INC_SSD1322_H_ */
