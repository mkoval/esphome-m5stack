import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import (
    i2c,
    switch,
)
from esphome.const import (
    CONF_ID,
    CONF_SWITCHES,
)

CODEOWNERS = [ '@mkoval' ]
DEPENDENCIES = [ 'i2c' ]
MULTI_CONF = True

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
    main_component = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(main_component, config)
    await i2c.register_i2c_device(main_component, config)

    for channel, switch_config in enumerate(config[CONF_SWITCHES]):
        switch_var = cg.Pvariable(switch_config[CONF_ID], var.get_switch(channel))
        await cg.register_component(switch_component, switch_config)
        await switch.register_switch(switch_component, switch_config)