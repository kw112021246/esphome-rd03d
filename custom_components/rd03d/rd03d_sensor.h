
#pragma once

#include "esphome.h"

class RD03DSensor : public PollingComponent, public Sensor {
 public:
  RD03DSensor(UARTComponent *uart) : uart_(uart) {}

  void setup() override {}

  void update() override {
    while (uart_->available()) {
      int b = uart_->read();
      buffer_ += (char)b;
      if (b == '\n') {
        float value = parse_data(buffer_);
        if (!std::isnan(value)) {
          publish_state(value);
        }
        buffer_ = "";
      }
    }
  }

 private:
  UARTComponent *uart_;
  std::string buffer_;

  float parse_data(const std::string &raw) {
    if (raw.rfind("D:", 0) == 0) {
      try {
        int mm = std::stoi(raw.substr(2));
        return mm / 1000.0;
      } catch (...) {
        return NAN;
      }
    }
    return NAN;
  }
};
