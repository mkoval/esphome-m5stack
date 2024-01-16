#pragma once

#include "esphome/core/component.h"
#include "esphome/components/switch/switch.h"

namespace esphome {
namespace m5unit {

class M5UnitRelay;

class M5UnitRelayChannel 
    : public switch_::Switch
    , public Component
{
public:
    M5UnitRelayChannel();
    M5UnitRelayChannel(M5UnitRelay *parent, size_t channel);

    float get_setup_priority() const override { return setup_priority::LATE; }

protected:
    void write_state(bool state) override;

    M5UnitRelay *parent_;
    size_t channel_;
};

} //namespace m5unit 
} //namespace esphome