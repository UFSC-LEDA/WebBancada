# 🧠 WebBancada

Sistema embarcado para **controle e aquisição de dados em testes de bancada aerodinâmica**, utilizando um **ESP32** como unidade central.
O projeto permite controlar o **ângulo de ataque** de um modelo (via servo motor), medir forças de **sustentação**, **arrasto** e **momento**, e acompanhar os dados em tempo real por meio de uma **interface web responsiva** hospedada no próprio microcontrolador.

---

## 🎯 Sobre o Projeto

O **WebBancada** é um sistema embarcado voltado para o **controle e aquisição de dados em testes de bancada aerodinâmica**, utilizando o microcontrolador **ESP32** como unidade central.
A plataforma permite controlar o **ângulo de ataque** de um modelo em túnel de vento, medir forças de **sustentação**, **arrasto** e **momento**, e visualizar todos os dados em **tempo real via navegador web**, sem necessidade de computador dedicado ou software externo.

---

## ⚙️ Funcionalidades Principais

- 🔧 Controle manual de **ângulo de ataque** via **servo motor**.
- 📈 Leitura de **4 células de carga** através de **2 módulos HX711**.
- 🌐 Interface web embarcada com **gráficos em tempo real** (WebSocket).
- 💾 Armazenamento de dados em **arquivo CSV** no SPIFFS.
- 📡 Operação autônoma via **Wi-Fi Access Point**.
- 🧩 Código modular com **FreeRTOS** e separação em tarefas independentes.

---

## 🧩 Arquitetura do Sistema

```text
ESP32
├── HX711Manager      → Leitura e calibração das células de carga
├── ServoManager      → Controle do ângulo de ataque via PWM
├── WebServerManager  → Servidor HTTP + WebSocket (Async)
├── CSVLogger         → Gravação de dados em SPIFFS/SD
└── FreeRTOS Tasks    → Execução paralela suave
```

Interface Web:

- `index.html` — Interface do usuário
- `app.js` — Comunicação via WebSocket
- `style.css` — Layout responsivo e leve

---

## 🛠️ Estrutura do Projeto

```
WebBancada/
├─ platformio.ini
├─ src/
│  ├─ main.cpp
│  ├─ settings.h
│  ├─ hx711_manager.{h,cpp}
│  ├─ servo_manager.{h,cpp}
│  ├─ webserver.{h,cpp}
│  ├─ csv_logger.{h,cpp}
└─ data/
   ├─ index.html
   ├─ app.js
   └─ style.css
```

---

## ⚙️ Configuração de Hardware

| Componente    | Função                    | Pinos Padrão                             |
| ------------- | --------------------------- | ----------------------------------------- |
| HX711 #1      | 2 células (sustentação)  | DOUT=D16, SCK=D17                           |
| HX711 #2      | 2 células (arrasto/torque) | DOUT=D2, SCK=D4                           |
| Servo Motor   | Controle de ângulo         | D15 (PWM 50 Hz)                       |
| SD (opcional) | Armazenamento externo       | CS=5, MISO=19, MOSI=23, SCK=18            |
| ESP32 Wi-Fi   | Ponto de acesso local       | SSID:`WebBancada` / Senha: `12345678` |

> Todos os pinos podem ser modificados em `settings.h`.

---

## 🧪 Como Executar

### 1️⃣ Clonar o repositório

```bash
git clone https://github.com/UFSC-LEDA/WebBancada.git
cd WebBancada
```

### 2️⃣ Abrir no VS Code / PlatformIO

Selecione o ambiente:

```
esp32dev_simple
```

### 3️⃣ Fazer upload da interface web

```
PlatformIO → Upload Filesystem Image
```

### 4️⃣ Fazer upload do firmware

```
PlatformIO → Upload
```

### 5️⃣ Conectar e acessar

- Conecte-se à rede Wi-Fi **WebBancada** (senha `12345678`)
- Abra [http://192.168.4.1](http://192.168.4.1) no navegador
- Controle o servo e visualize os dados em tempo real

---

## 📄 Formato do CSV

O arquivo `test.csv` é salvo no SPIFFS e contém colunas como:

```
timestamp_ms,angle_deg,lift_N,drag_N,moment_Nm,cell1,cell2,cell3,cell4
```

---

## 🧠 Autoria e Licença

Desenvolvido pelo
**Laboratório de Experimentos Didáticos Aplicados (LEDA)**
**Universidade Federal de Santa Catarina (UFSC)**

Licença: **MIT**

---

<p align="center">
  <sub>© 2025 LEDA — Universidade Federal de Santa Catarina</sub><br>
  <sub>Projeto em desenvolvimento contínuo, voltado à experimentação e ensino de engenharia aplicada.</sub>
</p>
