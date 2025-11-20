#include "web_server.h"
#include "settings.h"
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include <WiFi.h>

HX711Manager* WebServerManager::hx = nullptr;
ServoManager* WebServerManager::servo = nullptr;

void WebServerManager::begin(HX711Manager *hx_, ServoManager *servo_) {
    hx = hx_;
    servo = servo_;

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

    Serial.println("WiFi AP iniciado.");
    Serial.println("SSID: " WIFI_SSID);
    Serial.println("Senha: " WIFI_PASS);
    Serial.println("Acesse: http://192.168.4.1/");
}


// IMPLEMENTAÇÃO DA FUNÇÃO PARA ENVIAR DADOS DOS SENSORES
void WebServerManager::sendSensorData() {
    if (ws.count() == 0) return;

    ForceData f;
    hx->readForces(f);

    // LOG DE DIAGNÓSTICO (Remova esta linha após confirmar a leitura)
    Serial.printf("Enviando Dados: C1=%.2f, C2=%.2f, Lift=%.2f\n", f.cells[0], f.cells[1], f.lift);


    StaticJsonDocument<256> doc;
    doc["type"] = "data";
    doc["c1"] = f.cells[0];
    doc["c2"] = f.cells[1];
    doc["c3"] = f.cells[2];
    doc["c4"] = f.cells[3];
    doc["lift"] = f.lift;
    doc["drag"] = f.drag;
    doc["moment"] = f.moment;

    String jsonString;
    serializeJson(doc, jsonString);

    ws.textAll(jsonString); // Envia para todos os clientes
}


// loop agora envia dados periodicamente (uso da constante SEND_PERIOD_MS)
void WebServerManager::loop() {
    ws.cleanupClients();

    if (millis() - lastSendTime >= SEND_PERIOD_MS) {
        sendSensorData();
        lastSendTime = millis();
    }
}


// FUNÇÃO ESTÁTICA COM O OPERADOR DE ESCOPO CORRETO
void WebServerManager::wsEvent(
    AsyncWebSocket *server,
    AsyncWebSocketClient *client,
    AwsEventType type,
    void *arg,
    uint8_t *data,
    size_t len
) {
    if (type == WS_EVT_CONNECT) {
        Serial.println("Cliente conectado");
        client->text("Conectado ao ESP32 WebBancada");
    }

    else if (type == WS_EVT_DISCONNECT) {
        Serial.println("Cliente desconectado");
    }

    else if (type == WS_EVT_DATA) {
        AwsFrameInfo *info = (AwsFrameInfo*)arg;

        if (!info->final || info->index != 0 || info->len != len)
            return;

        String msg = "";
        for (size_t i = 0; i < len; i++) msg += (char)data[i];

        Serial.print("WS recebido: ");
        Serial.println(msg);

        StaticJsonDocument<200> doc;
        DeserializationError err = deserializeJson(doc, msg);

        if (err) {
            Serial.println("Erro JSON");
            return;
        }

        const char *cmd = doc["cmd"];

        // --- Resposta JSON de Status ---
        StaticJsonDocument<100> res;
        res["type"] = "status";
        String resMsg;


        if (strcmp(cmd, "calibra") == 0) {
            servo->setAngle(0);
            Serial.println("Calibrado zero");
            res["message"] = "SUCESSO: Ângulo calibrado para 0°.";
        }

        else if (strcmp(cmd, "ir") == 0) {
            int val = doc["value"];
            servo->setAngle(val);
            Serial.printf("Ir para %d\n", val);
            res["message"] = "SUCESSO: Servo movido para " + String(servo->getAngle(), 1) + "°.";
        }

        else if (strcmp(cmd, "mover") == 0) {
            int val = doc["value"];
            float novo = servo->getAngle() + val;
            servo->setAngle(novo);
            Serial.printf("Mover %+d -> %.1f\n", val, novo);
            res["message"] = "SUCESSO: Servo movido relativamente para " + String(servo->getAngle(), 1) + "°.";
        }

        else if (strcmp(cmd, "tare") == 0) {
            hx->tare();
            Serial.println("Tare executado");
            res["message"] = "SUCESSO: Tare das células de carga executado.";
        }

        else if (strcmp(cmd, "start") == 0) {
            Serial.println("Iniciando teste...");
            res["message"] = "INFO: Iniciando teste...";
        }
        
        // Envia a resposta de status para o cliente
        serializeJson(res, resMsg);
        client->text(resMsg);
    }
}