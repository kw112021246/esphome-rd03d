from esphome.components import sensor
import esphome.config_validation as cv
from esphome.const import CONF_ID, CONF_UART_ID, CONF_NAME
from esphome.core import coroutine_with_priority
import esphome.codegen as cg

DEPENDENCIES = ["uart"]

rd03d_ns = cg.esphome_ns.namespace("rd03d")
RD03DSensor = rd03d_ns.class_("RD03DSensor", sensor.Sensor, cg.PollingComponent, cg.UARTDevice)

CONFIG_SCHEMA = sensor.sensor_schema().extend({
    cv.GenerateID(): cv.declare_id(RD03DSensor),
    cv.GenerateID("uart"): cv.use_id(cg.UARTComponent),
}).extend(cv.polling_component_schema("1s"))

@coroutine_with_priority(40.0)
async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID], config["uart_id"])
    await cg.register_component(var, config)
    await sensor.register_sensor(var, config)
    await cg.register_uart_device(var, config["uart_id"])
