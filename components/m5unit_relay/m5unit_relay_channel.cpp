#include "m5unit_relay_channel.h"

// Only include in cpp file to break circular dependency
#include "m5unit_relay.h"

namespace esphome {
namespace m5unit {

M5UnitRelayChannel::M5UnitRelayChannel()
    : parent_{nullptr}
    , channel_{0}
{
}

M5UnitRelayChannel::M5UnitRelayChannel(M5UnitRelay *parent, size_t channel)
    : parent_{parent}
    , channel_{channel}
{
}

void M5UnitRelayChannel::write_state(bool state)
{
    if (!this->parent_) {
        return;
    }

    this->parent_->set_channel_state(this->channel_, state);
    this->parent_->write_state();
    publish_state(state);
}

} //namespace m5unit 
} //namespace esphome