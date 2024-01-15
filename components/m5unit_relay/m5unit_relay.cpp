#include "esphome/core/log.h"
#include "m5unit_relay.h"

namespace esphome {
namespace m5unit {

static const char *TAG = "m5unit.switch";
static constexpr size_t NUM_CHANNELS = 4;
static constexpr uint8_t REG_CONTROL = 0x10;
static constexpr uint8_t REG_FIRMWARE = 0xFE;

M5UnitRelay::M5UnitRelay()
    : value{0x00}
{
}

void M5UnitRelay::setup()
{
    ESP_LOGI(TAG, "probing I2C reg %#04x for firmware", REG_FIRMWARE);
    if (this->read_register(REG_FIRMWARE, &this->firmware, 1) != i2c::ERROR_OK) {
        ESP_LOGE(TAG, "connection failed, unable to read firmware version");
        this->mark_failed();
        return;
    }
    ESP_LOGI(TAG, "found firmware version: %04x", this->firmware);
}

void M5UnitRelay::write_state(uint8_t channel, bool state)
{
    const uint8_t mask = 1 << channel;
    this->value = (this->value & ~mask) | mask;

    if (this->write_register(REG_CONTROL, &this->value, 1) != i2c::ERROR_OK) {
        ESP_LOGE(TAG, "failed to write to I2C reg %#04x", REG_CONTROL);
        this->mark_failed();
        return;
    }
}

void M5UnitRelay::dump_config()
{
    ESP_LOGCONFIG(TAG, "I2C address: %#04x", this->address_);
    ESP_LOGCONFIG(TAG, "I2C firmware register: %#04x", REG_FIRMWARE);
    ESP_LOGCONFIG(TAG, "I2C control register: %#04x", REG_CONTROL);
}

} //namespace m5unit 
} //namespace esphome