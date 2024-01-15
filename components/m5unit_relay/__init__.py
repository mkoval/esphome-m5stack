import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c, switch
from esphome.const import CONF_ID

CODEOWNERS = ['@mkoval']
DEPENDENCIES = ['i2c']
MULTI_CONF = True

CONF_M5UNIT_RELAY_ID = 'm5unit_relay_id'
""" Used by children to refer to the M5UnitRelayComponent parent. """

m5unit_ns = cg.esphome_ns.namespace('m5unit')
M5UnitRelayComponent = m5unit_ns.class_('M5UnitRelayComponent',
    cg.Component,
    i2c.I2CDevice
)

CONFIG_SCHEMA = (
    cv.COMPONENT_SCHEMA
    .extend(i2c.i2c_device_schema(0x26))
    .extend({
        cv.GenerateID(): cv.declare_id(M5UnitRelay)
    })
)

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    yield i2c.register_i2c_device(var, config)