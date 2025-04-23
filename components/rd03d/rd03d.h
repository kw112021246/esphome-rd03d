#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace rd03d {

class RD03DSensor : public PollingComponent, public uart::UARTDevice {
 public:
  RD03DSensor(uart::UARTComponent *parent) : UARTDevice(parent) {}

  void setup() override {}
  void update() override;

  void set_sensor(sensor::Sensor *sensor) { sensor_ = sensor; }

 protected:
  sensor::Sensor *sensor_{nullptr};
};

}  // namespace rd03d
}  // namespace esphome
