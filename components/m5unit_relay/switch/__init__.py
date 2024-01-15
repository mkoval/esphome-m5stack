import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import switch
from esphome.const import (
    ENTITY_CATEGORY_CONFIG,
    CONF_TYPE,
)

from .. import M5UnitRelay

"""
AUTO_LOAD = [ 'switch' ]
DEPENDENCIES = [ 'm5unit_relay' ]
CODEOWNERS = [ '@mkoval' ]
"""

m5unit_ns = cg.esphome_ns.namespace('m5unit')
M5UnitRelayChannel= m5unit_ns.class_('M5UnitRelayChannel',
    cg.Component,
    switch.Switch,
    cg.Parented(M5UnitRelay),
)

CONFIG_SCHEMA = (
    switch.switch_schema(M5UnitRelayChannel)
    .extend(cv.COMPONENT_SCHEMA)
    .extend({
        cv.GenerateID(): cv.declare_id(M5UnitRelayChannel),
    })
)

async def to_code(parent, channel, config):
    var = await switch.new_switch(config)
    await cg.register_component(var, config)
    await switch.register_switch(var, config)
    await cg.register_parented(var, parent)
    cg.add(var.set_channel(channel))