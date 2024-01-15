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
    M5UnitRelayChannel();

    void set_channel(size_t channel) { this->channel_ = channel; }

protected:
    void write_state(bool state) override;

    size_t channel_;
};

} //namespace m5unit 
} //namespace esphome