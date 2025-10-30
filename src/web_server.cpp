#include "web_server.h"
#include "settings.h"
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include <WiFi.h>

void WebServerManager::begin(HX711Manager *hx_, ServoManager *servo_) {
  hx = hx_; servo = servo_;

  WiFi.mode(WIFI_AP);
  WiFi.softAP(WIFI_SSID, WIFI_PASS);
  SPIFFS.begin(true);

  ws.onEvent(wsEvent);
  server.addHandler(&ws);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *r){
    r->send(SPIFFS, "/index.html", "text/html");
  });
  server.serveStatic("/", SPIFFS, "/");

  server.begin();
  Serial.println("WiFi AP iniciado. Conecte em: WebBancada / 12345678");
  Serial.println("Acesse: http://192.168.4.1/");
}

void WebServerManager::wsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client,
  AwsEventType type, void *arg, uint8_t *data, size_t len) {
  if(type == WS_EVT_CONNECT) {
    Serial.println("Cliente conectado");
  }
}
