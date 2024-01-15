#include "m5unit_relay_channel.h"

// Only include in cpp file to break circular dependency
#include "../m5unit_relay.h"

namespace esphome {
namespace m5unit {

void M5UnitRelayChannel::write_state(bool state)
{
    this->parent_->set_channel_state(this->channel_, state);
    this->parent_->write_state();
    publish_state(state);
}

} //namespace m5unit 
} //namespace esphome