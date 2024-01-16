#include "esphome/core/log.h"
#include "m5unit_analog.h"

namespace esphome {
namespace m5unit {

static const char *TAG = "m5unit.analog";

static constexpr uint8_t REG_CURRENT = 0x20;
static constexpr uint8_t REG_CAL_CURRENT = 0x20;
static constexpr uint8_t REG_FIRMWARE_VERSION = 0xFE;
static constexpr uint8_t REG_I2C_ADDRESS = 0xFF;

M5UnitAnalog::M5UnitAnalog()
{
    // Example code multiplies by 100 to convert to milliamps, so multiply by
    // another factor of 1000 to convert to amps.
    static sensor::MultiplyFilter default_filter{1e5};

    for (size_t channel = 0; channel < NUM_CHANNELS; channel++) {
        sensors_[channel].add_filter(&default_filter);
    }
}

void M5UnitAnalog::setup()
{
    ESP_LOGD(TAG, "Setting up...");
    set_timeout(500);

    uint8_t address;
    if (this->read_register(REG_I2C_ADDRESS, &address, 1) != i2c::ERROR_OK) {
        ESP_LOGE(TAG, "failed to read I2C address from addr %#04x reg %#04x",
            this->address_, REG_I2C_ADDRESS);
        this->mark_failed();
        return;
    } else if (address != this->address_) {
        ESP_LOGE(TAG, "value %04x in reg %#04x does not match I2C address %04x",
            address, REG_I2C_ADDRESS, this->address_);
        this->mark_failed();
        return;
    }
    ESP_LOGD(TAG, "Read I2C address: %04fx", address);

    if (this->read_register(REG_FIRMWARE_VERSION, &this->firmware_, 1) != i2c::ERROR_OK) {
        ESP_LOGE(TAG, "failed to read fw version from addr %#04x reg %#04x",
            this->address_, REG_FIRMWARE_VERSION);
        this->mark_failed();
        return;
    }
    ESP_LOGD(TAG, "Read firmware version: %#04x", this->firmware_);

    ESP_LOGD(TAG, "Setup complete");
}

void M5UnitAnalog::dump_config()
{
    ESP_LOGCONFIG(TAG, "M5Unit Analog:");
    ESP_LOGCONFIG(TAG, "  I2C address: %#04x", this->address_);
    ESP_LOGCONFIG(TAG, "  I2C address register: %#04x", REG_I2C_ADDRESS);
    ESP_LOGCONFIG(TAG, "  I2C firmware version register: %#04x", REG_FIRMWARE_VERSION);
    ESP_LOGCONFIG(TAG, "  I2C current register: %#04x", REG_CURRENT);
}

void M5UnitAnalog::update()
{
    std::array<uint8_t, 2 * NUM_CHANNELS> buffer;
    if (this->read_register(REG_CURRENT, buffer.data(), buffer.size()) != i2c::ERROR_OK) {
        ESP_LOGE(TAG, "failed to read current (%d bytes) from I2C addr %#04x reg %#04x",
            buffer.size(), this->address_, REG_CURRENT);
        this->mark_failed();
        return;
    }

    for (size_t channel = 0; channel < NUM_CHANNELS; channel++) {
        const uint16_t value = (
            buffer[2 * channel] + 256 * buffer[2 * channel + 1]);
        this->sensors_[channel].publish_state(value);
    }
}

} //namespace m5unit 
} //namespace esphome