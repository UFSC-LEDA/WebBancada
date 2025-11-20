let ws = new WebSocket(`ws://${location.host}/ws`);

// Referências aos novos elementos HTML
const statusElement = document.getElementById("status-message");
const cellDataElement = document.getElementById("cell-data");

ws.onopen = () => {
    console.log("WS conectado");
    statusElement.textContent = "Conectado ao ESP32";
};

// Funçao de recebimento de mensagens
ws.onmessage = (ev) => {
    try {
        const data = JSON.parse(ev.data);

        if (data.type === "status") {
            // Mensagens de confirmação de comando (calibra, ir, mover, tare, start)
            statusElement.textContent = data.message;
            console.log("Status recebido:", data.message);
        } else if (data.type === "data") {
            // Dados de força das células (envio periódico)
            cellDataElement.textContent = `
                C1: ${data.c1.toFixed(3)}, 
                C2: ${data.c2.toFixed(3)}, 
                C3: ${data.c3.toFixed(3)}, 
                C4: ${data.c4.toFixed(3)}
            `;
            // Opcionalmente, loga as forças calculadas
            console.log(`Forças: L=${data.lift.toFixed(2)}, D=${data.drag.toFixed(2)}, M=${data.moment.toFixed(2)}`);
        }
    } catch (e) {
        // Trata mensagens de texto simples (como a primeira mensagem de conexão)
        console.log("WS recebido (texto):", ev.data);
        if (ev.data.includes("Conectado")) {
            statusElement.textContent = ev.data;
        }
    }
};

ws.onerror = (e) => {
    console.log("WS erro:", e);
    statusElement.textContent = "Erro de conexão!";
};
ws.onclose = () => {
    console.log("WS desconectado");
    statusElement.textContent = "Desconectado. Tente recarregar a página.";
};


// ---------------------------
// Funções enviadas ao ESP32 (SEM MUDANÇAS)
// ---------------------------

// Calibrar zero
function sendCalibra() {
  ws.send(JSON.stringify({ cmd: "calibra" }));
}

// Movimento absoluto
function sendIr() {
  let val = parseInt(document.getElementById("irValue").value);
  ws.send(JSON.stringify({ cmd: "ir", value: val }));
}

// Movimento relativo
function sendMover() {
  let val = parseInt(document.getElementById("moverValue").value);
  ws.send(JSON.stringify({ cmd: "mover", value: val }));
}

// Tare do sensor
function sendTare() {
  ws.send(JSON.stringify({ cmd: "tare" }));
}

// Iniciar teste
function sendStart() {
  ws.send(JSON.stringify({ cmd: "start" }));
}