#pragma once
#include <Arduino.h>
#include <ESP32Servo.h> // NOVO: Usamos a biblioteca Servo padrão
#include "settings.h"

class ServoManager {
public:
    void begin(int pin = SERVO_PWM_PIN); // Função simplificada

    void setAngle(float deg);
    float getAngle() const { return currentAngle; }

private:
    Servo servo;
    u_int8_t pin = -1;
    float currentAngle = 0.0f;
    // As variáveis 'ch' (channel) e 'freq' foram removidas.
};