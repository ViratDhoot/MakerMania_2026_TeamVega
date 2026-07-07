const { WebSocketServer } = require('ws');
const wss = new WebSocketServer({ port: 8080 });

console.log("Server Started");

wss.on('connection', (ws) => {
    console.log("Connection!")
})