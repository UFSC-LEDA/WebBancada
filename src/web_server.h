#pragma once
#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include "hx711_manager.h"
#include "servo_manager.h"

class WebServerManager {
public:
    void begin(HX711Manager *hx, ServoManager *servo);

    // === ADICIONADO ===
    void loop();

    static void wsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client,
                        AwsEventType type, void *arg, uint8_t *data, size_t len);

private:
    static HX711Manager *hx;
    static ServoManager *servo;

    AsyncWebServer server{80};
    AsyncWebSocket ws{"/ws"};

    // NOVO: Para controle de envio periódico de dados
    unsigned long lastSendTime = 0; 
    
    // NOVO: Função para empacotar e enviar dados do sensor
    void sendSensorData();
};