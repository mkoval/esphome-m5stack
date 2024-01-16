import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import (
    i2c,
    sensor,
)
from esphome.const import (
    CONF_ID,
    CONF_SWITCHES,
    DEVICE_CLASS_CURRENT,
    ICON_FLASH,
    STATE_CLASS_MEASUREMENT,
    UNIT_AMPERE,
)

AUTO_LOAD = [ 'sensor' ]
CODEOWNERS = [ '@mkoval' ]
DEPENDENCIES = [ 'i2c' ]
MULTI_CONF = True

m5unit_ns = cg.esphome_ns.namespace('m5unit')
M5UnitAnalog = m5unit_ns.class_('M5UnitAnalog',
    cg.PollingComponent,
    i2c.I2CDevice,
)

CONFIG_SCHEMA = (
    cv.COMPONENT_SCHEMA
    .extend(
        i2c.i2c_device_schema(default_address=0x55)
    ).extend({
        cv.GenerateID(): cv.declare_id(M5UnitAnalog),
        cv.Required(CONF_SWITCHES): cv.All(
            cv.ensure_list(
                sensor.sensor_schema(
                    unit_of_measurement=UNIT_AMPERE,
                    icon=ICON_FLASH,
                    accuracy_decimals=5,
                    device_class=DEVICE_CLASS_CURRENT,
                    state_class=STATE_CLASS_MEASUREMENT,
                )
                .extend({
                    cv.GenerateID(): cv.declare_id(sensor.Sensor)
                })
            ),
            cv.Length(min=4, max=4)
        )
    })
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)

    for channel, sensor_config in enumerate(config[CONF_SENSORS]):
        sensor_var = cg.Pvariable(sensor_config[CONF_ID], var.get_sensor(channel))
        await sensor.register_sensor(sensor_var, sensor_config)