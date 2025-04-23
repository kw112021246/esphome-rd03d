#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace rd03d {

static const char *const TAG = "rd03d";

class RD03DSensor : public Component, public uart::UARTDevice {
 public:
  RD03DSensor(uart::UARTComponent *parent);

  void setup() override;
  void update() override;

  void set_sensor(sensor::Sensor *sensor) { sensor_ = sensor; }

 protected:
  std::string buffer_;
  sensor::Sensor *sensor_{nullptr};

  float parse_data_(const std::string &data);
};

}  // namespace rd03d
}  // namespace esphome