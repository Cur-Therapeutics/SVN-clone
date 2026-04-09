/*
 * cog_display.c
 *
 *  Created on: Mar 30, 2026
 *      Author: bcompter
 */

#include "main.h"
#include "cog_display.h"
#include "string.h"

uint8_t framebuffer[1024]; // 128x64 / 8

static void lcd_write(uint8_t data, uint8_t is_data)
{
    if (is_data)
        LCD_A0_DATA();
    else
        LCD_A0_CMD();

    LCD_CS_LOW();
    HAL_SPI_Transmit(&hspi3, &data, 1, HAL_MAX_DELAY);
    LCD_CS_HIGH();
}

void lcd_init(void)
{
	LCD_RST_HIGH();
	HAL_Delay(150);
    LCD_RST_LOW();
    HAL_Delay(150);
    LCD_RST_HIGH();

    lcd_write(0xAE, 0); // Display OFF
    lcd_write(0xA2, 0); // Bias 1/9
    lcd_write(0xA0, 0); // ADC normal
    lcd_write(0xC8, 0); // COM scan reverse
    lcd_write(0x22, 0); // Resistor ratio
    lcd_write(0x2F, 0); // Power control (booster, regulator, follower)
    lcd_write(0x40, 0); // Start line = 0

    lcd_write(0xAF, 0); // Display ON
}

void lcd_init2(void)
{
	LCD_RST_HIGH();
	HAL_Delay(150);
    LCD_RST_LOW();
    HAL_Delay(150);
    LCD_RST_HIGH();

    lcd_write(0xA0, 0); // ADC normal
    lcd_write(0xAE, 0); // Display OFF
    lcd_write(0xC0, 0); //

    lcd_write(0xA2, 0); //
    lcd_write(0x2F, 0); //
    lcd_write(0x21, 0); //
    lcd_write(0x81, 0); //

    lcd_write(0x3F, 0); //

    lcd_write(0xAF, 0);
    lcd_write(0xA5, 0);



}

void lcd_update(void)
{
    for (uint8_t page = 0; page < 8; page++)
    {
        lcd_write(0xB0 | page, 0); // Set page
        lcd_write(0x10, 0);        // Column high
        lcd_write(0x00, 0);        // Column low

        for (uint8_t col = 0; col < 128; col++)
        {
            lcd_write(framebuffer[page * 128 + col], 1);
        }
    }
}

void lcd_force_on(void)
{
    lcd_write(0xA5, 0); // Entire display ON (ignores RAM)
}

void lcd_all_on(void)
{
    memset(framebuffer, 0xFF, sizeof(framebuffer));
}

void lcd_all_off(void)
{
    memset(framebuffer, 0x00, sizeof(framebuffer));
}

void lcd_checkerboard(void)
{
    for (int i = 0; i < 1024; i++)
    {
        framebuffer[i] = (i & 1) ? 0xAA : 0x55;
    }
}

void lcd_horizontal_bands(void)
{
    for (int page = 0; page < 8; page++)
    {
        uint8_t val = (page % 2) ? 0xFF : 0x00;

        for (int col = 0; col < 128; col++)
        {
            framebuffer[page * 128 + col] = val;
        }
    }
}

void lcd_vertical_bands(void)
{
    for (int page = 0; page < 8; page++)
    {
        for (int col = 0; col < 128; col++)
        {
            if ((col / 8) % 2)
                framebuffer[page * 128 + col] = 0xFF;
            else
                framebuffer[page * 128 + col] = 0x00;
        }
    }
}

void ChipOnGlassTest()
{
	lcd_init();

	lcd_write(0xA5, 0);
	lcd_write(0xA4, 0);
	lcd_write(0xAF, 0);

	lcd_write(0xAE, 0);

	lcd_force_on();

	while (1)
	{
		lcd_checkerboard();
		lcd_update();
		HAL_Delay(1000);

		lcd_vertical_bands();
		lcd_update();
		HAL_Delay(1000);

		lcd_horizontal_bands();
		lcd_update();
		HAL_Delay(1000);

		lcd_all_on();
		lcd_update();
		HAL_Delay(1000);

		lcd_all_off();
		lcd_update();
		HAL_Delay(1000);
	}
}

void ChipOnGlassTest2()
{
	lcd_init2();

	/*
	lcd_write(0xA5, 0);
	lcd_write(0xA4, 0);
	lcd_write(0xAF, 0);

	lcd_write(0xAE, 0);

	lcd_force_on();
*/
	while (1)
	{
		lcd_checkerboard();
		lcd_update();
		HAL_Delay(1000);

		lcd_vertical_bands();
		lcd_update();
		HAL_Delay(1000);

		lcd_horizontal_bands();
		lcd_update();
		HAL_Delay(1000);

		lcd_all_on();
		lcd_update();
		HAL_Delay(1000);

		lcd_all_off();
		lcd_update();
		HAL_Delay(1000);
	}
}
