import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, uart
from esphome.const import (
    CONF_ID,
    UNIT_METER,
    DEVICE_CLASS_DISTANCE,
    STATE_CLASS_MEASUREMENT,
    ICON_RULER,
)

DEPENDENCIES = ['uart']

rd03d_ns = cg.esphome_ns.namespace('rd03d')
RD03DSensor = rd03d_ns.class_('RD03DSensor', sensor.Sensor, cg.PollingComponent)

CONFIG_SCHEMA = (
    sensor.sensor_schema(
        unit_of_measurement=UNIT_METER,
        icon=ICON_RULER,
        accuracy_decimals=2,
        device_class=DEVICE_CLASS_DISTANCE,
        state_class=STATE_CLASS_MEASUREMENT,
    )
    .extend({
        cv.GenerateID(): cv.declare_id(RD03DSensor),
        cv.Required("uart_id"): cv.use_id(uart.UARTComponent),
    })
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await sensor.register_sensor(var, config)
    uart_comp = await cg.get_variable(config["uart_id"])
    cg.add(var.set_uart(uart_comp))
