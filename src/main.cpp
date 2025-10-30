#include "web_server.h"
#include "settings.h"
#include <SPIFFS.h>
#include <ArduinoJson.h>

HX711Manager hx;
ServoManager servo;
WebServerManager web;

void setup() {
  Serial.begin(115200);
  servo.begin(SERVO_PWM_PIN, SERVO_LEDC_CHANNEL, SERVO_LEDC_FREQ);
  hx.begin(HX1_DOUT, HX1_SCK, HX2_DOUT, HX2_SCK);
  web.begin(&hx, &servo);
}

void loop() {
  delay(1000);
}
