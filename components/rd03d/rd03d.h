#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace rd03d {

class RD03DSensor : public PollingComponent, public uart::UARTDevice {
 public:
  RD03DSensor(uart::UARTComponent *parent) : uart::UARTDevice(parent) {}

  void set_sensor(sensor::Sensor *sensor) { this->sensor_ = sensor; }

  void setup() override {}

  void update() override;

 protected:
  sensor::Sensor *sensor_;
  std::string buffer_;

  float parse_data_(const std::string &raw) {
    if (raw.rfind("D:", 0) == 0) {
      try {
        int mm = std::stoi(raw.substr(2));
        return mm / 1000.0f;
      } catch (...) {
        return NAN;
      }
    }
    return NAN;
  }
};

namespace esphome {
namespace rd03d {

// class definition here
}  // namespace rd03d
}  // namespace esphome
