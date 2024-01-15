import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c, switch
from esphome.const import CONF_ID

CODEOWNERS = ['@mkoval']
DEPENDENCIES = ['i2c']

DEFAULT_I2C_ADDR = 0x01

m5unit_ns = cg.esphome_ns.namespace('m5unit')
M5UnitRelay = m5unit_ns.class_('M5UnitRelay', cg.Component, i2c.I2CDevice)

CONFIG_SCHEMA = (
    switch.SWITCH_SCHEMA.extend({
        cv.GenerateID(): cv.declare_id(M5UnitRelay)
    })
    .extend(cv.COMPONENT_SCHEMA)
    .extend(i2c.i2c_device_schema(DEFAULT_I2C_ADDR))
)

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    yield i2c.register_i2c_device(var, config)