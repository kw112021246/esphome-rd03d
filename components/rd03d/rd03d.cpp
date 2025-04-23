#include "rd03d.h"
#include "esphome/core/log.h"

namespace esphome {
namespace rd03d {

static const char *const TAG = "rd03d";

RD03DSensor::RD03DSensor(uart::UARTComponent *parent) : uart::UARTDevice(parent) {}

void RD03DSensor::setup() {
  ESP_LOGI(TAG, "RD03D sensor setup complete");
}

void RD03DSensor::update() {
  while (available()) {
    char c = read();
    buffer_ += c;
    if (c == '\n') {
      float distance = parse_data_(buffer_);
      if (!std::isnan(distance) && sensor_ != nullptr) {
        ESP_LOGD(TAG, "Parsed distance: %.2f m", distance);
        sensor_->_
