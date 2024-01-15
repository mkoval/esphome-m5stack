#pragma once

#include "esphome/core/component.h"
#include "esphome/components/switch/switch.h"
#include "../m5unit_relay.h"

namespace esphome {
namespace m5unit {

class M5UnitRelayComponentSwitch
    : public switch_::Switch
    , public Component
    , public Parented<M5UnitRelayComponent>
{
public:
    M5UnitRelayComponentSwitch();

    void set_channel(uint8_t channel);

    void write_state(bool state) override;

protected:
    uint8_t channel_;
};

} //namespace m5unit 
} //namespace esphome