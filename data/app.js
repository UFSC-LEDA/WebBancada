let ws = new WebSocket(`ws://${location.host}/ws`);
ws.onopen = () => console.log("Conectado");
ws.onmessage = ev => console.log(ev.data);

const servo = document.getElementById('servo');
servo.oninput = () => {
  ws.send(JSON.stringify({servo: parseInt(servo.value)}));
};
