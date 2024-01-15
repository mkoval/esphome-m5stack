import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import switch
from esphome.const import (
    ENTITY_CATEGORY_CONFIG,
    CONF_TYPE,
)

from .. import (
    CONF_M5UNIT_RELAY_ID,
    M5UnitRelayComponentComponent,
)

DEPENDENCIES = ['m5unit_relay']

CONF_M5UNIT_RELAY_CHANNEL = 'channel'

m5unit_ns = cg.esphome_ns.namespace('m5unit')
M5UnitRelayComponentSwitch= m5unit_ns.class_('M5UnitRelayComponentSwitch',
    switch.Switch,
    cg.Component,
    cg.Parented.template(M5UnitRelayComponent)
)

CONFIG_SCHEMA = (
    switch.switch_schema(
        M5UnitRelayComponentSwitch,
        entity_category=ENTITY_CATEGORY_CONFIG,
    )
    .extend(cv.COMPONENT_SCHEMA)
    .extend({
        cv.GenerateID(): cv.declare_id(M5UnitRelayComponentSwitch),
        cv.GenerateID(CONF_M5UNIT_RELAY_ID): cv.use_id(M5UnitRelayComponent),
        cv.Required(CONF_M5UNIT_RELAY_CHANNEL): cv.int_range(min=0, max=3),
    })
)

async def to_code(config):
    parent = await cg.get_variable(config[CONF_M5UNIT_RELAY_ID])
    var = await switch.new_switch(config)
    await cg.register_component(var, config)
    await cg.register_parented(var, parent)