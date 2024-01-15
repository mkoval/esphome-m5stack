#pragma once

#include "esphome/core/component.h"
#include "esphome/components/switch/switch.h"
#include "../m5unit_relay.h"

namespace esphome {
namespace m5unit {

class M5UnitRelayChannel 
    : public switch_::Switch
    , public Component
    , public Parented<M5UnitRelay>
{
public:
    void set_channel(uint8_t channel);

    void write_state(bool state) override;

protected:
    uint8_t channel_;
};

} //namespace m5unit 
} //namespace esphome