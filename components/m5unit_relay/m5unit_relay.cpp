#include "esphome/core/helpers.h"
#include "esphome/core/log.h"
#include "m5unit_relay.h"
#include "m5unit_relay_channel.h"

namespace esphome {
namespace m5unit {

static const char *TAG = "m5unit.analog";

static constexpr uint8_t REG_CONTROL = 0x10;
static constexpr uint8_t REG_FIRMWARE_VERSION = 0xFE;
static constexpr uint8_t REG_I2C_ADDRESS = 0xFF;

M5UnitRelay::M5UnitRelay()
    : state_{0x00}
{
    for (size_t channel = 0; channel < NUM_CHANNELS; channel++) {
        this->channels_[channel] = make_unique<M5UnitRelayChannel>(this, channel);
    }
}

void M5UnitRelay::setup()
{
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

    if (this->read_register(REG_FIRMWARE_VERSION, &this->firmware_, 1) != i2c::ERROR_OK) {
        ESP_LOGE(TAG, "failed to read fw version from addr %#04x reg %#04x",
            this->address_, REG_FIRMWARE_VERSION);
        this->mark_failed();
        return;
    }

    // Initialize all channels to "off"
    state_ = 0x00;
    write_state();
}

void M5UnitRelay::dump_config()
{
    ESP_LOGCONFIG(TAG, "M5Unit Analog:");
    ESP_LOGCONFIG(TAG, "  I2C address: %#04x", this->address_);
    ESP_LOGCONFIG(TAG, "  I2C address register: %#04x", REG_I2C_ADDRESS);
    ESP_LOGCONFIG(TAG, "  I2C firmware version register: %#04x", REG_FIRMWARE_VERSION);
    ESP_LOGCONFIG(TAG, "  I2C control register: %#04x", REG_CONTROL);
}

void M5UnitRelay::set_channel_state(size_t channel, bool state)
{
    this->state_ &= ~(1 << channel); // clear the target bit
    this->state_ |= !!state << channel; // set the target bit to state

    // Repeat for the LED, which is in the upper 4 bits
    this->state_ &= ~(1 << (2 * channel));
    this->state_ |= !!state << (2 * channel);
}

void M5UnitRelay::write_state()
{ 
    if (this->write_register(REG_CONTROL, &this->state_, 1) != i2c::ERROR_OK) {
        ESP_LOGE(TAG, "failed to write state %#04x to control reg %#04x",
            this->state_, REG_CONTROL);
        this->mark_failed();
        return;
    }
}

} //namespace m5unit 
} //namespace esphome