#include "rd03d.h"

namespace esphome {
namespace rd03d {

RD03DSensor::RD03DSensor(uart::UARTComponent *parent) : uart::UARTDevice(parent) {}

void RD03DSensor::setup() {
  // No setup logic needed
}

void RD03DSensor::update() {
  while (available()) {
    char c = read();
    if (c == '\n') {
      float distance = parse_data_(buffer_);
      if (!std::isnan(distance) && sensor_ != nullptr) {
        ESP_LOGD(TAG, "Parsed distance: %.2f m", distance);
        sensor_->publish_state(distance);
      }
      buffer_.clear();
    } else {
      buffer_ += c;
    }
  }
}

float RD03DSensor::parse_data_(const std::string &data) {
  if (data.rfind("DIST:", 0) == 0) {
    return std::stof(data.substr(5)) / 100.0f;
  }
  return NAN;
}

}  // namespace rd03d
}  // namespace esphome