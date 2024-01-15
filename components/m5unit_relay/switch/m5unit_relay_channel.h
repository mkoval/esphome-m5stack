#pragma once

#include "esphome/core/component.h"
#include "esphome/components/switch/switch.h"

namespace esphome {
namespace m5unit {

// Forward declaration for parent pointer, to break circular dependency
class M5UnitRelay;

class M5UnitRelayChannel 
    : public switch_::Switch
    , public Component
{
protected:
    friend class M5UnitRelay;

    // Constructed by M5UnitRelay
    M5UnitRelayChannel(M5UnitRelay *parent, size_t channel);

    void write_state(bool state) override;

    M5UnitRelay *parent_;
    size_t channel_;
};

} //namespace m5unit 
} //namespace esphome