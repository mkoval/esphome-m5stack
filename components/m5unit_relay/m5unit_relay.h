#pragma once

#include "esphome/core/component.h"
#include "esphome/components/i2c/i2c.h"
#include "switch/m5unit_relay_channel.h"

namespace esphome {
namespace m5unit {

class M5UnitRelay
    : public i2c::I2CDevice
    , public PollingComponent
{
public:
    static constexpr size_t NUM_CHANNELS = 4;

    M5UnitRelay();

    uint8_t get_firmware_version() const { return this->firmware; }

    M5UnitRelayChannel *get_switch(size_t channel) { return &this->switches_[channel]; }

    void setup() override;
    void dump_config() override;

protected:
    // Updates internal state. Must be followed by a call to write_state() to take effect.
    void set_channel_state(size_t channel, bool state);

    // Writes the internal state over I2C to the device.
    void write_state();

    std::array<M5UnitRelayChannel, NUM_CHANNELS> switches_;
    uint8_t firmware_;
    uint8_t state_;
};

} //namespace m5unit 
} //namespace esphome