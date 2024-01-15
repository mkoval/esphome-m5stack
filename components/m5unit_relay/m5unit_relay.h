#pragma once

#include "esphome/core/component.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace m5unit {

class M5UnitRelay 
    : public i2c::I2CDevice
    , public Component
{
public:
    M5UnitRelay();

    void setup() override;
    void write_state(uint8_t channel, bool state);
    void dump_config() override;

protected:
    void set_state(uint8_t channel, bool state);

    uint8_t value;
    uint8_t version;
};

} //namespace m5unit 
} //namespace esphome