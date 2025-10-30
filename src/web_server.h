#pragma once
#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include "hx711_manager.h"
#include "servo_manager.h"

class WebServerManager {
public:
  void begin(HX711Manager *hx, ServoManager *servo);
  static void wsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);

private:
  HX711Manager *hx;
  ServoManager *servo;
  AsyncWebServer server{80};
  AsyncWebSocket ws{"/ws"};
};
