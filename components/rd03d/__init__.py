import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, uart
from esphome.const import CONF_ID, UNIT_METERS, ICON_RULER, DEVICE_CLASS_DISTANCE, STATE_CLASS_MEASUREMENT

rd03d_ns = cg.esphome_ns.namespace('rd03d')
RD03DSensor = rd03d_ns.class_('RD03DSensor', cg.PollingComponent, uart.UARTDevice)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(RD03DSensor),
    cv.Required("uart_id"): cv.use_id(uart.UARTComponent),
    cv.Required("name"): cv.string,
}).extend(sensor.sensor_schema(
    unit_of_measurement="m",
    icon=ICON_RULER,
    accuracy_decimals=2,
    device_class=DEVICE_CLASS_DISTANCE,
    state_class=STATE_CLASS_MEASUREMENT,
))

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID], config["uart_id"])
    await cg.register_component(var, config)
    sens = await sensor.new_sensor(config)
    cg.add(var.set_sensor(sens))
