#pragma once

#include "esphome/core/component.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace m5unit {

class M5UnitAnalog
    : public i2c::I2CDevice
    , public PollingComponent
{
public:
    static constexpr size_t NUM_CHANNELS = 4;

    M5UnitAnalogComponent();

    uint8_t get_firmware_version() const { return this->firmware; }

    Sensor *get_sensor(size_t channel) const { return &this->sensors_[channel]; }

    void setup() override;
    void dump_config() override;
    void update() override;

protected:
    i2c::ErrorCode read_channels(uint8_t reg,
        std::array<uint16_t, NUM_CHANNELS> *output);

    std::array<Sensor, NUM_CHANNELS> sensors_;
    uint8_t firmware;
};

} //namespace m5unit 
} //namespace esphome