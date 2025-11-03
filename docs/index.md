# ⚖️ WebBancada

Bem-vindo à documentação oficial do **WebBancada**, um sistema embarcado para controle e aquisição de dados em testes de bancada aerodinâmica.

## Visão Geral

O **WebBancada** foi desenvolvido no Laboratório de Experimentos Didáticos Aplicados (LEDA) da Universidade Federal de Santa Catarina (UFSC). Utilizando um microcontrolador **ESP32**, o sistema permite controlar o ângulo de ataque de um modelo, medir forças aerodinâmicas (sustentação, arrasto e momento) e visualizar os dados em tempo real através de uma interface web.

A comunicação em tempo real é feita via **WebSockets**, e os dados dos ensaios são armazenados localmente em formato **CSV**. O sistema opera de forma autônoma, criando seu próprio ponto de acesso Wi-Fi.

## Navegação

- **[Primeiros Passos](./getting-started.md)**: Um guia completo para configurar o hardware e o software do projeto.
- **[Detalhes de Hardware](./hardware.md)**: Informações aprofundadas sobre os componentes eletrônicos e suas conexões.
- **[Detalhes de Software](./software.md)**: Uma visão detalhada da arquitetura do firmware, bibliotecas e como customizar o código.

---

<p align="center">
  <sub>© 2025 LEDA — Universidade Federal de Santa Catarina</sub><br>
  <sub>Projeto em desenvolvimento contínuo, voltado à experimentação e ensino de engenharia aplicada.</sub>
</p>
