#pragma once

#include "esphome/core/component.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace m5unit {

// Forward declaration of children, to break circular dependency
class M5UnitChannel;

class M5UnitRelay
    : public i2c::I2CDevice
    , public PollingComponent
{
public:
    static constexpr size_t NUM_CHANNELS = 4;

    M5UnitRelay();

    uint8_t get_firmware_version() const { return this->firmware; }

    void setup() override;
    void dump_config() override;

protected:
    friend class M5UnitChannel;

    // Updates internal state. Must be followed by a call to write_state() to take effect.
    void set_channel_state(size_t channel, bool state);

    // Writes the internal state over I2C to the device.
    void write_state();

    uint8_t firmware_;
    uint8_t state_;
};

} //namespace m5unit 
} //namespace esphome