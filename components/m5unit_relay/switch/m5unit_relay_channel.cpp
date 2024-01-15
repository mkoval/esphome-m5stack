#include "m5unit_relay_channel.h"

namespace esphome {
namespace m5unit {

M5UnitRelayChannel::M5UnitRelayChannel(M5UnitRelay *parent, size_t channel)
    : parent_{parent}
    , channel_{channel}
{
}

void M5UnitRelayChannel::write_state(bool state)
{
    this->parent_->set_channel_state(this->channel_, state);
    this->parent_->write_state();
    publish_state(state);
}

} //namespace m5unit 
} //namespace esphome