#include "servo_manager.h"


void ServoManager::begin(int p) { // Parâmetros 'c' e 'f' removidos
    pin = p;
    ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
    servo.setPeriodHertz(50);
    servo.attach(pin, 1000, 2000);

    setAngle(0); // começa no zero
}

void ServoManager::setAngle(float deg) {
    deg = constrain(deg, 0.0f, 180.0f);

    // Substitui o cálculo manual complexo por servo.write()
    // A biblioteca Servo.h no ESP32 faz o cálculo de duty cycle automaticamente.
    servo.write((int)deg); 
    
    currentAngle = deg;
}