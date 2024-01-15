#include "m5unit_relay_channel.h"

namespace esphome {
namespace m5unit {

M5UnitRelayChannel::M5UnitRelayChannel()
    : channel_{0}
{
}

void M5UnitRelayChannel::set_channel(uint8_t channel)
{
    channel_ = channel;
}

void M5UnitRelayChannel::write_state(bool state) override;
{
    parent_->write_state(channel_, state);
    publish_state(state);
}

} //namespace m5unit 
} //namespace esphome