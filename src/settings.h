#pragma once

// --- HX711 pins ---
#define HX1_DOUT 21
#define HX1_SCK  22
#define HX2_DOUT 19
#define HX2_SCK  23

// --- Servo ---
#define SERVO_PWM_PIN 18
#define SERVO_LEDC_CHANNEL 0
#define SERVO_LEDC_FREQ 50
#define SERVO_MIN_US 500
#define SERVO_MAX_US 2500
#define SERVO_NEUTRAL_US 1500

// --- Sampling ---
#define HX711_RATE_HZ 80
#define SEND_PERIOD_MS 200
#define CSV_FILENAME "/test.csv"

// --- Wi-Fi ---
#define WIFI_SSID "WebBancada"
#define WIFI_PASS "12345678"   // cria AP, SSID e senha simples

// --- Test defaults ---
#define DEFAULT_ANGLE_START 0
#define DEFAULT_ANGLE_END 60
#define DEFAULT_STEPS 5
#define DEFAULT_WAIT_MS 2000
#define DEFAULT_SPEED_DPS 15.0
