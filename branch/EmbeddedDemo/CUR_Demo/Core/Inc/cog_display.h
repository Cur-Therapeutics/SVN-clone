/*
 * cog_display.h
 *
 *  Created on: Mar 30, 2026
 *      Author: bcompter
 */

#ifndef INC_COG_DISPLAY_H_
#define INC_COG_DISPLAY_H_


#define LCD_CS_LOW()     HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET)
#define LCD_CS_HIGH()    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET)

#define LCD_A0_CMD()     HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET)
#define LCD_A0_DATA()    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET)

#define LCD_RST_LOW()    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_RESET)
#define LCD_RST_HIGH()   HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_SET)

extern SPI_HandleTypeDef hspi3;

void ChipOnGlassTest(void);
void lcd_init(void);
void lcd_update(void);
void lcd_all_on(void);
void lcd_all_off(void);
void lcd_checkerboard(void);
void lcd_horizontal_bands(void);
void lcd_vertical_bands(void);
void lcd_force_on(void);

void ChipOnGlassTest2(void);
void lcd_init2(void);


#endif /* INC_COG_DISPLAY_H_ */
