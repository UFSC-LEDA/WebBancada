# 🚀 Primeiros Passos

Este guia irá ajudá-lo a configurar todo o ambiente necessário para montar e executar o projeto WebBancada.

## 1. Configuração do Hardware

O primeiro passo é conectar todos os componentes eletrônicos ao ESP32. Para uma descrição detalhada de cada componente, consulte a página **[Detalhes de Hardware](./hardware.md)**.

### Conexões dos Pinos

| Componente  | Função                            | Pinos Padrão no ESP32  |
| ----------- | ----------------------------------- | ----------------------- |
| HX711 #1    | Células de Carga (Sustentação)   | `DOUT=21`, `SCK=22` |
| HX711 #2    | Células de Carga (Arrasto/Momento) | `DOUT=19`, `SCK=23` |
| Servo Motor | Controle do Ângulo de Ataque       | `GPIO 18`             |

> **Nota:** Todos os pinos podem ser facilmente alterados no arquivo `src/settings.h`.

### Diagrama de Conexão (Exemplo)

<embed src="./WebBancada.pdf" type="application/pdf" width="100%" height="600px" />

**Importante:** O servo motor deve ser alimentado por uma fonte de energia externa que forneça a corrente necessária, não diretamente do pino 5V do ESP32. Lembre-se de conectar o GND da fonte externa ao GND do ESP32.

## 2. Configuração do Software

### Pré-requisitos

- **Visual Studio Code**: Editor de código principal.
- **Extensão PlatformIO IDE**: Para gerenciamento do projeto, compilação e upload.

### Passos de Instalação

1. **Clone o Repositório:**

   ```bash
   git clone [https://github.com/UFSC-LEDA/WebBancada.git](https://github.com/UFSC-LEDA/WebBancada.git)
   cd WebBancada
   ```
2. **Abra o Projeto no VS Code:**

   - Abra a pasta `WebBancada` no Visual Studio Code.
   - Aguarde o PlatformIO inicializar e carregar as dependências do projeto, listadas no arquivo `platformio.ini`.
3. **Selecione o Ambiente de Compilação:**

   - Na barra de status inferior do VS Code, clique no ambiente padrão do PlatformIO (geralmente `default_envs`).
   - Selecione o ambiente desejado. O principal é o `esp32dev_spiffs_servofb`. As opções de compilação permitem, por exemplo, usar ou não o feedback do servo.
4. **Faça o Upload da Interface Web:**

   - No menu do PlatformIO (ícone de formiga na barra lateral), navegue até `Project Tasks > esp32dev_spiffs_servofb > Platform`.
   - Clique em **`Upload Filesystem Image`**. Isso enviará os arquivos da pasta `data/` (`index.html`, `style.css`, `app.js`) para a memória flash do ESP32.
5. **Faça o Upload do Firmware:**

   - Ainda no menu do PlatformIO, clique na opção **`Upload`**. O PlatformIO irá compilar o código-fonte e gravá-lo no ESP32.

## 3. Utilização

1. **Conecte-se à Rede Wi-Fi:**

   - Após o ESP32 reiniciar, ele criará uma rede Wi-Fi.
   - **SSID:** `WebBancada`
   - **Senha:** `12345678`
2. **Acesse a Interface Web:**

   - Em um navegador, acesse o endereço: **`http://192.168.4.1`**.
   - A interface de controle será carregada, permitindo o controle manual do servo e a visualização dos dados em tempo real.
