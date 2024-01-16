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
AUTO_LOAD = [ 'switch' ]
MULTI_CONF = True

m5unit_ns = cg.esphome_ns.namespace('m5unit')
M5UnitRelay = m5unit_ns.class_('M5UnitRelay',
    cg.Component,
    i2c.I2CDevice,
)

M5UnitRelayChannel = m5unit_ns.class_('M5UnitRelayChannel',
    cg.Component,
    switch.Switch,
)

_NUM_CHANNELS = 4

CONFIG_SCHEMA = (
    cv.COMPONENT_SCHEMA
    .extend(
        i2c.i2c_device_schema(default_address=0x26)
    ).extend({
        cv.GenerateID(): cv.declare_id(M5UnitRelay),
        cv.Required(CONF_SWITCHES): cv.All(
            cv.ensure_list(
                switch.switch_schema()
                .extend({
                    cv.GenerateID(): cv.declare_id(M5UnitRelayChannel)
                })
            ),
            cv.Length(min=_NUM_CHANNELS, max=_NUM_CHANNELS),
        )
    })
)

async def to_code(config):
    main_var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(main_var, config)
    await i2c.register_i2c_device(main_var, config)

    for channel, switch_config in enumerate(config[CONF_SWITCHES]):
        switch_var = cg.Pvariable(
            switch_config[CONF_ID], main_var.get_switch(channel))
        await cg.register_component(switch_var, switch_config)
        await switch.register_switch(switch_var, switch_config)