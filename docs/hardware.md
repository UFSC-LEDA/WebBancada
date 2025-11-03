# 🛠️ Detalhes de Hardware

Esta seção descreve os componentes de hardware utilizados no projeto WebBancada e como eles interagem.

## Placa de Desenvolvimento: ESP32

O cérebro do projeto é uma placa de desenvolvimento **ESP32-DevKitC-32**. Suas principais características são:

- **Microcontrolador:** ESP32-DOWDQ6-V3 dual-core de 32 bits.
- **Conectividade:** Wi-Fi e Bluetooth integrados, essencial para hospedar o web server.
- **Memória:** 520 KB de SRAM e 4 MB de armazenamento flash, suficiente para o código e o sistema de arquivos da interface web (SPIFFS).

A escolha do ESP32 se deu por sua alta capacidade de processamento, memória e conectividade nativa, superando alternativas como o Arduino Uno para este tipo de aplicação.

## Sensores: Células de Carga e Módulo HX711

Para medir as forças aerodinâmicas, o sistema utiliza **quatro células de carga** conectadas a **dois módulos amplificadores HX711**.

- **Células de Carga:** São transdutores que convertem força em um sinal elétrico. Duas são usadas para medir sustentação, uma para arrasto e uma para momento.
- **Módulo HX711:** É um conversor analógico-digital de 24 bits de alta precisão, projetado para pontes de Wheatstone como as das células de carga. Ele amplifica o sinal e o converte para um formato digital que o ESP32 pode ler. O projeto configura o ganho do amplificador para 128 para máxima sensibilidade.

A taxa de amostragem dos dados pode ser configurada para até 80 Hz, permitindo um bom pós-processamento dos dados coletados.

## Atuador: Servo Motor

O controle do ângulo de ataque do modelo é realizado por um servo motor.

- **Controle:** PWM (Pulse Width Modulation).
- **Faixa de Pulso:** 500 a 2500 µs, correspondendo a uma rotação de 180°.
- **Frequência de Operação:** O ESP32 é configurado para gerar um sinal PWM de 50 Hz, que é um valor padrão para servos.

O código no `servo_manager.cpp` converte um ângulo em graus (0-180) para a largura de pulso correspondente em microssegundos (`us`) para controlar o servo.

## Pinos Padrão

As conexões padrão estão definidas em `src/settings.h`:

```cpp
// --- HX711 pins ---
#define HX1_DOUT 21
#define HX1_SCK  22
#define HX2_DOUT 19
#define HX2_SCK  23

// --- Servo ---
#define SERVO_PWM_PIN 18
```
