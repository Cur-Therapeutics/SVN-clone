#include "nhd_display.h"
#include "string.h"

extern I2C_HandleTypeDef hi2c1;

// Reset pin: PD5
#define NHD_RST_PORT GPIOD
#define NHD_RST_PIN  GPIO_PIN_5

void NHD_Reset(void)
{
    HAL_GPIO_WritePin(NHD_RST_PORT, NHD_RST_PIN, GPIO_PIN_RESET);
    HAL_Delay(10);
    HAL_GPIO_WritePin(NHD_RST_PORT, NHD_RST_PIN, GPIO_PIN_SET);
    HAL_Delay(10);
}

void NHD_SendCommand(uint8_t cmd)
{
    uint8_t buffer[2];
    buffer[0] = CMD_MODE;
    buffer[1] = cmd;

    HAL_I2C_Master_Transmit(&hi2c1, NHD_I2C_ADDR, buffer, 2, HAL_MAX_DELAY);
}

void NHD_SendData(uint8_t *data, uint16_t size)
{
    uint8_t buffer[129]; // 1 control + 128 data max chunk
    buffer[0] = DATA_MODE;

    while (size)
    {
        uint16_t chunk = (size > 128) ? 128 : size;

        memcpy(&buffer[1], data, chunk);

        HAL_I2C_Master_Transmit(&hi2c1, NHD_I2C_ADDR, buffer, chunk + 1, HAL_MAX_DELAY);

        data += chunk;
        size -= chunk;
    }
}

void NHD_Init(void)
{
    NHD_Reset();

    NHD_SendCommand(0xAE); // Display OFF

    // Bias & duty
    NHD_SendCommand(0xA2); // LCD bias
    NHD_SendCommand(0xA0); // ADC select

    // COM direction
    NHD_SendCommand(0xC8);

    // Power control
    NHD_SendCommand(0x2F); // Booster, regulator, follower ON

    // Contrast (Vop)
    NHD_SendCommand(0x81);
    NHD_SendCommand(0x08); // low byte
    NHD_SendCommand(0x03); // high byte

    // Display mode

    NHD_SendCommand(0xA5); // All pixels on!
    NHD_SendCommand(0xAF); // Display ON

    NHD_SendCommand(0xA4); // normal display

    NHD_SendCommand(0xAF); // Display ON
}

void NHD_Clear(void)
{
    uint8_t line[160] = {0x00}; // 160 columns

    // Set full display window
    NHD_SendCommand(0x75); // Set Row Address
    NHD_SendCommand(0x00); // Start row
    NHD_SendCommand(0x63); // End row (99 decimal)

    NHD_SendCommand(0x15); // Set Column Address
    NHD_SendCommand(0x00); // Start column
    NHD_SendCommand(0x9F); // End column (159 decimal)

    // Write zeros to entire display
    for (uint8_t row = 0; row < 100; row++)
    {
        NHD_SendData(line, 160);
    }
}

void NHD_TestPattern(void)
{
    uint8_t buf[160];

    // Set full window
    NHD_SendCommand(0x75); // row
    NHD_SendCommand(0);
    NHD_SendCommand(99);

    NHD_SendCommand(0x15); // column
    NHD_SendCommand(0);
    NHD_SendCommand(159);

    for (int i = 0; i < 160; i++)
        buf[i] = 0xFF; // all pixels ON (max gray)

    for (int row = 0; row < 100; row++)
        NHD_SendData(buf, 160);
}


void NHD_Test(void)
{
	NHD_Init();
	NHD_Clear();

	HAL_Delay(500);

	NHD_TestPattern();
}


void NHD_AddressSweep(void)
{
	uint8_t cmd = 0xAE;
	for (int i = 0x32; i < 0x40; i++)
	{
		uint8_t buffer[2];
		buffer[0] = CMD_MODE;
		buffer[1] = cmd;

		HAL_StatusTypeDef result = HAL_I2C_Master_Transmit(&hi2c1, i, buffer, 2, HAL_MAX_DELAY);
		if (result == HAL_OK)
			result++;
		HAL_Delay(500);
	}
}
