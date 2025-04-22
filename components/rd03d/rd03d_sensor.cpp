#include "rd03d_sensor.h"
#include "esphome/core/log.h"

namespace esphome {
namespace rd03d {

static const char *const TAG = "rd03d";

RD03DSensor::RD03DSensor(uart::UARTComponent *parent) : uart::UARTDevice(parent) {}

void RD03DSensor::setup() {
  ESP_LOGI(TAG, "RD03D sensor setup complete");
}

void RD03DSensor::update() {
  if (available()) {
    std::string response;
    while (available()) {
      char c = read();
      response += c;
    }

    // Example: extract float value from response string
    float distance = std::stof(response);  // You may need a more robust parser
    if (this->sensor_ != nullptr) {
      this->sensor_->publish_state(distance);
    }
  }
}

}  // namespace rd03d
}  // namespace esphome
