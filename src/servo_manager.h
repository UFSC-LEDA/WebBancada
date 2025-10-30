#pragma once
#include <Arduino.h>
#include "settings.h"

class ServoManager {
public:
  void begin(int pin, int channel, int freq);
  void setAngle(float deg);
  float getAngle() const { return currentAngle; }

private:
  int pin, ch;
  float currentAngle = 0;
};
