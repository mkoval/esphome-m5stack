import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import switch
from esphome.const import (
    CONF_CHANNEL,
    CONF_TYPE,
)

from .. import (
    CONF_RELAY_ID
    M5UnitRelay,
)

AUTO_LOAD = [ 'switch' ]
DEPENDENCIES = [ 'm5unit_relay' ]
CODEOWNERS = [ '@mkoval' ]

m5unit_ns = cg.esphome_ns.namespace('m5unit')
M5UnitRelayChannel= m5unit_ns.class_('M5UnitRelayChannel',
    cg.Component,
    switch.Switch,
)

CONFIG_SCHEMA = (
    switch.switch_schema(M5UnitRelayChannel)
    .extend(cv.COMPONENT_SCHEMA)
    .extend({
        cv.GenerateID(): cv.declare_id(M5UnitRelayChannel),
        cv.Required(cv.GenerateID(CONF_RELAY_ID)): cv.use_id(M5UnitRelay),
        cv.Required(CONF_CHANNEL): cv.int_range(min=0, max=3),
    })
)

async def to_code(config):
    var = await switch.new_switch(config)
    await cg.register_component(var, config)
    await switch.register_switch(var, config)
    await cg.register_parented(var, config[CONF_RELAY_ID])
    cg.add(var.set_channel(config[CONF_CHANNEL]))