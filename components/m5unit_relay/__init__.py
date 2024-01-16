import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import (
    i2c,
    switch,
)
from esphome.const import (
    CONF_ID,
)

CODEOWNERS = [ '@mkoval' ]
DEPENDENCIES = [ 'i2c' ]
MULTI_CONF = True

CONF_RELAY_ID = 'relay_id'

m5unit_ns = cg.esphome_ns.namespace('m5unit')
M5UnitRelay = m5unit_ns.class_('M5UnitRelay',
    cg.Component,
    i2c.I2CDevice,
)

_NUM_CHANNELS = 4

CONFIG_SCHEMA = (
    cv.COMPONENT_SCHEMA
    .extend(
        i2c.i2c_device_schema(default_address=0x26)
    ).extend({
        cv.GenerateID(): cv.declare_id(M5UnitRelay),
    })
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)