#include "ADXL345_Driver.h"

// Define SPI instance
struct SPI_Module spi;

void ADXL345_Init(void)
{
    // Initialize SPI instance
    spi.instance.Instance = SPI1;
    spi.instance.Init.Mode = SPI_MODE_MASTER;
    spi.instance.Init.Direction = SPI_DIRECTION_2LINES;
    spi.instance.Init.DataSize = SPI_DATASIZE_8BIT;
    spi.instance.Init.CLKPolarity = SPI_POLARITY_LOW;
    spi.instance.Init.CLKPhase = SPI_PHASE_1EDGE;
    spi.instance.Init.NSS = SPI_NSS_SOFT;
    spi.instance.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
    spi.instance.Init.FirstBit = SPI_FIRSTBIT_MSB;
    spi.instance.Init.TIMode = SPI_TIMODE_DISABLE;
    spi.instance.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    spi.instance.Init.CRCPolynomial = 10;
    HAL_SPI_Init(&spi.instance);

    GPIO_InitTypeDef GPIO_InitStruct;
    // Initialize CS pin
    spi.csPort = GPIOA;
    spi.csPin = GPIO_PIN_4;
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitStruct.Pin = spi.csPin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(spi.csPort, &GPIO_InitStruct);
}

// Read from the ADXL345: send the register address and read the data
HAL_StatusTypeDef ADXL345_ReadReg(uint8_t register_address, uint8_t *data, uint16_t size)
{
    // Check if the device is ready
    HAL_StatusTypeDef status = HAL_SPI_GetState(&spi.instance);
    if (status != HAL_OK)
    {
        return HAL_ERROR;
    }

    // Select the device
    HAL_GPIO_WritePin(spi.csPort, spi.csPin, GPIO_PIN_RESET);

    // Send the register address
    uint8_t txData = register_address | 0x80;
    HAL_SPI_Transmit(&spi.instance, &txData, 1, HAL_MAX_DELAY);

    // Receive the data
    HAL_SPI_Receive(&spi.instance, data, size, HAL_MAX_DELAY);

    // Deselect the device
    HAL_GPIO_WritePin(spi.csPort, spi.csPin, GPIO_PIN_SET);

    return HAL_OK;
}

// ADXL345_WriteReg: Write data to a register
HAL_StatusTypeDef ADXL345_WriteReg(uint8_t register_address, uint8_t *data, uint16_t size)
{
    // Check if the device is ready
    HAL_StatusTypeDef status = HAL_SPI_GetState(&spi.instance);
    if (status != HAL_OK)
    {
        return HAL_ERROR;
    }

    // Select the device
    HAL_GPIO_WritePin(spi.csPort, spi.csPin, GPIO_PIN_RESET);

    // Send the register address
    uint8_t txData = register_address & 0x7F;
    HAL_SPI_Transmit(&spi.instance, &txData, 1, HAL_MAX_DELAY);

    // Send the data
    HAL_SPI_Transmit(&spi.instance, data, size, HAL_MAX_DELAY);

    // Deselect the device
    HAL_GPIO_WritePin(spi.csPort, spi.csPin, GPIO_PIN_SET);

    return HAL_OK;
}

// Initial Configuration of the ADXL345
void ADXL345_Config(void)
{
    if (ADXL345_Check() != HAL_OK)
    {
        Error_Handler();
    }
    uint8_t value = 0;
    // Set the range to +/- 16g
    ADXL345_SetRange(ADXL345_RANGE_16G);
    // Put the ADXL345 into Measurement Mode by writing 0x08 to the POWER_CTL register
    value = 0x08;
    ADXL345_WriteReg(ADXL345_REG_POWER_CTL, &value, 1);
}

// Check if the ADXL345 is present
HAL_StatusTypeDef ADXL345_Check(void)
{
    uint8_t value;
    if (ADXL345_ReadReg(ADXL345_REG_DEVID, &value, 1) != HAL_OK)
    {
        return HAL_ERROR;
    }
    if (value != 0xE5)
    {
        return HAL_ERROR;
    }
    return HAL_OK;
}

// Set the range of the ADXL345 to range (0x00 = +/- 2g, 0x01 = +/- 4g, 0x02 = +/- 8g, 0x03 = +/- 16g)
void ADXL345_SetRange(uint8_t range)
{
    uint8_t value = 0;
    ADXL345_ReadReg(ADXL345_REG_DATA_FORMAT, &value, 1);
    value &= ~0x0F;
    value |= range;
    value |= 0x08;
    ADXL345_WriteReg(ADXL345_REG_DATA_FORMAT, &value, 1);
}

// Read the X, Y, and Z acceleration values
void ADXL345_ReadAccel(int16_t *x, int16_t *y, int16_t *z)
{
    HAL_StatusTypeDef status = ADXL345_Check();

    if (status != HAL_OK)
    {

        if (status == HAL_BUSY)
        {
            COM_printf("ADXL345 busy");
            return;
        }
        COM_printf("Error reading ADXL345 \n");
    }

    uint8_t data[6];
    status = ADXL345_ReadReg(ADXL345_REG_DATAX0, data, 6);
    if (status != HAL_OK)
    {
        // Error handling
        COM_printf("Error reading ADXL345 \n");
        return;
    }
    *x = (int16_t)(data[1] << 8 | data[0]);
    *y = (int16_t)(data[3] << 8 | data[2]);
    *z = (int16_t)(data[5] << 8 | data[4]);
}
