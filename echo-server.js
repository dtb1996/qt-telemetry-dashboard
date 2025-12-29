const WebSocket = require('ws');

const port = 8080;
const wss = new WebSocket.Server({ port });

wss.on('connection', ws => {
    console.log('Client connected');
    ws.on('message', message => {
        console.log('Received:', message.toString());
        ws.send(message.toString()); // Echo it back
    });
    ws.on('close', () => console.log('Client disconnected'));
});

console.log(`WebSocket echo server running at ws://localhost:${port}`);
