import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import switch
from esphome.const import (
    ENTITY_CATEGORY_CONFIG,
    CONF_TYPE,
)

from .. import (
    CONF_M5UNIT_RELAY_ID,
    M5UnitRelayComponent,
)

AUTO_LOAD = [ 'switch' ]
CODEOWNERS = [ '@mkoval' ]
DEPENDENCIES = [ 'm5unit_relay' ]

m5unit_ns = cg.esphome_ns.namespace('m5unit')
M5UnitRelayChannel= m5unit_ns.class_('M5UnitRelayChannel',
    switch.Switch,
    cg.Component,
)

CONFIG_SCHEMA = (
    switch.switch_schema(M5UnitRelayChannel)
    .extend(cv.COMPONENT_SCHEMA)
    .extend({
        cv.GenerateID(): cv.declare_id(M5UnitRelayChannel),
    })
)

async def to_code(config):
    var = await switch.new_switch(config)
    await cg.register_component(var, config)