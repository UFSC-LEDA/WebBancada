#include "servo_manager.h"

void ServoManager::begin(int p, int c, int f) {
  pin = p; ch = c;
  ledcSetup(ch, f, 16);
  ledcAttachPin(pin, ch);
  setAngle(0);
}

void ServoManager::setAngle(float deg) {
  deg = constrain(deg, 0, 180);
  float us = SERVO_MIN_US + (deg / 180.0f) * (SERVO_MAX_US - SERVO_MIN_US);
  uint32_t duty = (us / 20000.0f) * 65535;
  ledcWrite(ch, duty);
  currentAngle = deg;
}
