#pragma once

#include "esphome/core/component.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace m5unit {

class M5UnitRelayChannel;

class M5UnitRelayComponent 
    : public i2c::I2CDevice
    , public Component
{
public:
    M5UnitRelay();

    void setup() override;
    void dump_config() override;

protected:
    void write_state(uint8_t channel, bool state);

    friend class M5UnitRelayChannel;

    uint8_t value;
    uint8_t firmware;
};

} //namespace m5unit 
} //namespace esphome