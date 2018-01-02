/* cy8cmbr3108 Button Driver - (c) 2017 Blocks Wearables Ltd. */
#include <stdint.h>
#include <stdbool.h>

#define CY8CMBR3_IC2_ADDR_DEFAULT 0x37u

/**
 * Writes the configuration settings to the sensor.
 *
 * \param i2cAddress The I2C slave address of the sensor
 * \return true if succeded, false otherwise
 */
bool cy8cmbr3_write_config(uint8_t i2cAddress);

/**
 * Restarts the sensor. Wait ~400ms for ready.
 *
 * \param i2cAddress The I2C slave address of the sensor
 * \return true if succeded, false otherwise
 */
bool cy8cmbr3_restart(uint8_t i2cAddress);

/**
 * User-provided function for reading from I2C.
 *
 * \param i2cAddress The I2C slave address of the sensor
 * \param buffer The buffer into which to receive
 * \param size The number of bytes to receive
 * \return true if succeded, false otherwise
 */
bool cy8cmbr3_i2c_read(uint8_t i2cAddress, uint8_t* buffer, uint16_t size);

/**
 * User-provided function for writing to I2C.
 *
 * \param i2cAddress The I2C slave address of the sensor
 * \param buffer The data to send
 * \param size The number of bytes to send
 * \return true if succeded, false otherwise
 */
bool cy8cmbr3_i2c_write(uint8_t i2cAddress, const uint8_t* data, uint16_t size);
