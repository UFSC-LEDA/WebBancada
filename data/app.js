let ws = new WebSocket(`ws://${location.host}/ws`);

ws.onopen = () => console.log("WS conectado");
ws.onmessage = (ev) => console.log("WS recebido:", ev.data);
ws.onerror = (e) => console.log("WS erro:", e);
ws.onclose = () => console.log("WS desconectado");


// ---------------------------
// Funções enviadas ao ESP32
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
