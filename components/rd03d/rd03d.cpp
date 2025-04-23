#include "rd03d.h"
#include "esphome/core/log.h"

namespace esphome {
namespace rd03d {

static const char *const TAG = "rd03d";

void RD03DSensor::update() {
  // Example: Send dummy distance or parse UART
  if (this->sensor_ != nullptr) {
    this->sensor_->publish_state(1.23);  // Simulated distance
  }
}

}  // namespace rd03d
}  // namespace esphome
