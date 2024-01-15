#include "m5unit_relay_channel.h"

namespace esphome {
namespace m5unit {

M5UnitRelayComponentSwitch::M5UnitRelayComponentSwitch()
    : channel_{0}
{
}

void M5UnitRelayComponentSwitch::set_channel(uint8_t channel)
{
    this->channel_ = channel;
}

void M5UnitRelayComponentSwitch::write_state(bool state)
{
    this->parent_->write_state(this->channel_, state);
    publish_state(state);
}

} //namespace m5unit 
} //namespace esphome