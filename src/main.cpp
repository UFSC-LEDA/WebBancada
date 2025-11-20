#include "web_server.h"
#include "settings.h"
#include <SPIFFS.h>

HX711Manager hx;
ServoManager servo;
WebServerManager web;

void setup() {
    Serial.begin(115200);

    // Chamada simplificada
    servo.begin(SERVO_PWM_PIN); 

    hx.begin(HX1_DOUT, HX1_SCK, HX2_DOUT, HX2_SCK);

    web.begin(&hx, &servo);
}

void loop() {
    // Necessário para manter o WebSocket vivo
    web.loop();
}