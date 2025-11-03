# 💻 Detalhes de Software

Esta seção aborda a arquitetura do firmware, as bibliotecas utilizadas e como o código está estruturado.

## Arquitetura do Projeto

O projeto é gerenciado pelo **PlatformIO** e utiliza o framework **Arduino** para o ESP32, o que simplifica o desenvolvimento. A estrutura de pastas segue o padrão do PlatformIO:

```WebBancada/
├─ platformio.ini      # Arquivo de configuração do projeto
├─ src/                  # Código-fonte principal (.cpp, .h)
│  ├─ main.cpp          # Ponto de entrada do programa
│  ├─ settings.h        # Definições de pinos e configurações
│  ├─ hx711_manager.h   # Classe para gerenciar os módulos HX711
│  ├─ servo_manager.h   # Classe para controle do servo
│  └─ web_server.h      # Classe para o servidor web e WebSocket
├─ data/                 # Arquivos da interface web (HTML, CSS, JS)
├─ lib/                  # Bibliotecas específicas do projeto
└─ test/                 # Testes unitários (se aplicável)
```

## Sistema Operacional de Tempo Real (RTOS)

O projeto utiliza o **FreeRTOS**, que vem integrado ao framework do ESP32. Isso permite a execução de tarefas concorrentes de forma suave e organizada. As principais tarefas são:

- **Leitura dos Sensores:** Uma tarefa dedicada lê continuamente as células de carga.
- **Servidor Web:** O servidor web assíncrono é executado em sua própria tarefa, respondendo a requisições HTTP e WebSocket sem bloquear o resto do sistema.
- **Loop Principal:** O `loop()` principal pode ser usado para tarefas de baixa prioridade.

## Bibliotecas Principais

As dependências são gerenciadas pelo PlatformIO e estão listadas em `platformio.ini`:

- `ESPAsyncWebServer`: Para criar um servidor web HTTP assíncrono e eficiente.
- `AsyncTCP`: Dependência do `ESPAsyncWebServer` para comunicação TCP.
- `HX711`: Biblioteca para comunicação com os módulos amplificadores HX711.
- `ArduinoJson`: Para criar e analisar objetos JSON, usado na comunicação WebSocket.

## Módulos do Código

O código é modularizado para facilitar a manutenção e a adição de novas funcionalidades.

### `main.cpp`

Inicializa os principais componentes do sistema: o gerenciador do servo, o gerenciador do HX711 e o servidor web.

### `settings.h`

Centraliza todas as configurações "hardcoded", como pinos de hardware, credenciais de Wi-Fi e parâmetros de teste, facilitando a customização.

### `hx711_manager.cpp`

Abstrai a leitura das quatro células de carga. O método `readForces` calcula as forças de sustentação, arrasto e momento a partir dos valores brutos das células. Futuramente, aqui pode ser implementado o procedimento de calibração com matriz.

### `servo_manager.cpp`

Controla o posicionamento do servo motor. O método `setAngle` converte um ângulo em graus para o valor de pulso PWM necessário.

### `web_server.cpp`

Configura o ponto de acesso Wi-Fi, o servidor de arquivos estáticos (para a interface web) e o endpoint WebSocket (`/ws`) para comunicação em tempo real com o cliente.

### `csv_logger.cpp`

Fornece uma função simples, `appendCSV`, para adicionar uma linha de dados ao arquivo `test.csv` no sistema de arquivos SPIFFS.
