/* cy8cmbr3108 Button Driver - (c) 2017 Blocks Wearables Ltd. */
#include "cy8cmbr3108.h"
#include "regs.h"

enum TouchStatus
{
    NoTouch,
    SingleTouch,
    DoubleTouch
};

typedef struct {
    uint8_t address; uint8_t value;
} cfg_t;

static const cfg_t configValues[] =
{
    // Ensure all non-zero registers are specified
    { REG_SENSOR_EN,                0x01u },
    { REG_FSS_EN,                   0x00u },
    { REG_TOGGLE_EN,                0x00u },
    { REG_SENSITIVITY_0,            0x03u },
    { REG_SENSITIVITY_1,            0x00u },
    { REG_BASE_THRESHOLD0,          0x80u },
    { REG_BASE_THRESHOLD1,          0x7Fu },
    { REG_FINGER_THRESHOLD2,        0x7Fu },
    { REG_FINGER_THRESHOLD3,        0x7Fu },
    { REG_FINGER_THRESHOLD4,        0x7Fu },
    { REG_FINGER_THRESHOLD5,        0x7Fu },
    { REG_FINGER_THRESHOLD6,        0x7Fu },
    { REG_FINGER_THRESHOLD7,        0x7Fu },
    { REG_SENSOR_DEBOUNCE,          0x03u },
    { REG_BUTTON_HYS,               0x00u },
    { REG_BUTTON_LBR,               0x00u },
    { REG_BUTTON_NNT,               0x00u },
    { REG_BUTTON_NT,                0x00u },
    { REG_PROX_EN,                  0x00u },
    { REG_PROX_CFG,                 0x80u },
    { REG_PROX_CFG2,                0x05u },
    { REG_PROX_TOUCH_TH0,           0x00u },
    { REG_PROX_TOUCH_TH0 + 1,       0x02u },
    { REG_PROX_TOUCH_TH1,           0x00u },
    { REG_PROX_TOUCH_TH1 + 1,       0x02u },
    { REG_PROX_RESOLUTION0,         0x00u },
    { REG_PROX_RESOLUTION1,         0x00u },
    { REG_PROX_HYS,                 0x00u },
    { REG_PROX_LBR,                 0x00u },
    { REG_PROX_NNT,                 0x00u },
    { REG_PROX_NT,                  0x00u },
    { REG_PROX_POSITIVE_TH0,        0x1Eu },
    { REG_PROX_POSITIVE_TH1,        0x00u },
    { REG_PROX_NEGATIVE_TH0,        0x1Eu },
    { REG_PROX_NEGATIVE_TH1,        0x00u },
    { REG_LED_ON_TIME,              0x00u },
    { REG_BUZZER_CFG,               0x01u },
    { REG_BUZZER_ON_TIME,           0x01u },
    { REG_GPO_CFG,                  0x00u },
    { REG_PWM_DUTYCYCLE_CFG0,       0xFFu },
    { REG_PWM_DUTYCYCLE_CFG1,       0xFFu },
    { REG_PWM_DUTYCYCLE_CFG2,       0xFFu },
    { REG_PWM_DUTYCYCLE_CFG3,       0xFFu },
    { REG_SPO_CFG,                  0x20u },
    { REG_DEVICE_CFG0,              0x00u },
    { REG_DEVICE_CFG1,              0x01u },
    { REG_DEVICE_CFG2,              0x49u },
    { REG_DEVICE_CFG3,              0x00u },
    { REG_I2C_ADDR,                 CY8CMBR3_IC2_ADDR_DEFAULT },
    { REG_REFRESH_CTRL,             0x05u },
    { REG_STATE_TIMEOUT,            0x0Au },
    { REG_SCRATCHPAD0,              0x00u },
    { REG_SCRATCHPAD1,              0x00u }
    // CRC computed automatically
};

static const uint16_t configCount =
    sizeof(configValues) / sizeof(configValues[0]);


/**
 * Updates a CCITT CRC16 checksum with the next byte value.
 *
 * \param value The byte value with which to update the checksum
 * \param currentCRC The CRC to update
 * \return The updated CRC
 */
static uint16_t compute_crc16(uint8_t value, uint16_t currentCRC)
{
    uint8_t x = ((value >> 4) & 0x0F) ^ (currentCRC >> (16 - 4));
    currentCRC = ((uint16_t)0x1021u * x) ^ (currentCRC << 4);

    x = (value & 0x0F) ^ (currentCRC >> (16 - 4));
    return ((uint16_t)0x1021u * x) ^ (currentCRC << 4);
}

/**
 * Reads the value of the register at the specified address.
 *
 * \param i2cAddress The I2C slave address of the sensor
 * \param regAddress The address of the register to write
 * \param value_out Valid pointer to which value will be written
 * \return true if succeded, false otherwise
 */
static bool read_register(uint8_t i2cAddress, uint8_t regAddress, uint8_t* value_out)
{
    // Send address
    if (!cy8cmbr3_i2c_write(i2cAddress, &regAddress, 1)) return false;

    // Receive data
    if (!cy8cmbr3_i2c_read(i2cAddress, value_out, 1)) return false;

    return true;
}

/**
 * Writes the given value to the register at the specified address.
 *
 * \param i2cAddress The I2C slave address of the sensor
 * \param regAddress The address of the register to write
 * \param value The value to write to the register
 * \return true if succeded, false otherwise
 */
static bool write_register(uint8_t i2cAddress, uint8_t regAddress, uint8_t value)
{
    uint8_t msg[] = { regAddress, value };
    return cy8cmbr3_i2c_write(i2cAddress, msg, sizeof(msg));
}

/**
 * Writes the configuration settings to the sensor.
 *
 * \param i2cAddress The I2C slave address of the sensor
 * \return 1 if succeded, 0 otherwise
 */
bool cy8cmbr3_write_config(uint8_t i2cAddress)
{
    uint16_t crc = 0xffff;

    // Write config values
    cfg_t* nextCfg = configValues;
    for (uint16_t addr = 0; addr < REG_CONFIG_CRC; addr++)
    {
        // Skip sending reserved/invalid registers, but update CRC as if zero
        if (addr != nextCfg->address) {
            //if (!write_register(i2cAddress, addr, 0)) return false;
            crc = compute_crc16(0, crc);
        }
        // Send & update CRC
        else if (addr == nextCfg->address)
        {
            if (!write_register(i2cAddress, addr, nextCfg->value)) return false;
            crc = compute_crc16(nextCfg->value, crc);
            nextCfg++;
        }
    }

    // Write CRC
    if (!write_register(i2cAddress, REG_CONFIG_CRC,
        (uint8_t)(crc & 0xFF))) return false;

    if (!write_register(i2cAddress, REG_CONFIG_CRC + 1,
        (uint8_t)((crc >> 4) & 0xFF))) return false;

    return true;
}


/**
 * Restarts the sensor. Wait ~400ms for ready.
 *
 * \param i2cAddress The I2C slave address of the sensor
 * \return 1 if succeded, 0 otherwise
 */
bool cy8cmbr3_restart(uint8_t i2cAddress)
{
    return write_register(i2cAddress, REG_CTRL_CMD, 255);
}
