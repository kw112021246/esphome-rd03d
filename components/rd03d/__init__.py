from esphome.components import sensor, uart
import esphome.config_validation as cv
from esphome.const import CONF_ID, CONF_UART_ID, CONF_NAME
from esphome.core import coroutine_with_priority
import esphome.codegen as cg

DEPENDENCIES = ["uart"]

rd03d_ns = cg.esphome_ns.namespace("rd03d")
RD03DSensor = rd03d_ns.class_("RD03DSensor", sensor.Sensor, cg.PollingComponent, uart.UARTDevice)

CONFIG_SCHEMA = sensor.sensor_schema().extend({
    cv.GenerateID(): cv.declare_id(RD03DSensor),
    cv.GenerateID(CONF_UART_ID): cv.use_id(uart.UARTComponent),
}).extend(cv.polling_component_schema("1s"))

@coroutine_with_priority(40.0)
async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID], config[CONF_UART_ID])
    await cg.register_component(var, config)
    await sensor.register_sensor(var, config)
    await uart.register_uart_device(var, config[CONF_UART_ID])
